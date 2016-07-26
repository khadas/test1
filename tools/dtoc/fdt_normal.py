#!/usr/bin/python
#
# Copyright (C) 2016 Google, Inc
# Written by Simon Glass <sjg@chromium.org>
#
# SPDX-License-Identifier:      GPL-2.0+
#

import struct
import sys

import fdt
from fdt import Fdt, NodeBase, PropBase
import fdt_util
import libfdt

# This deals with a device tree, presenting it as a list of Node and Prop
# objects, representing nodes and properties, respectively.
#
# This implementation uses a libfdt Python library to access the device tree,
# so it is fairly efficient.

class Prop(PropBase):
    """A device tree property

    Properties:
        name: Property name (as per the device tree)
        value: Property value as a string of bytes, or a list of strings of
            bytes
        type: Value type
    """
    def __init__(self, node, offset, name, bytes):
        PropBase.__init__(self, node, offset, name)
        self.bytes = bytes
        if not bytes:
            self.type = fdt.TYPE_BOOL
            self.value = True
            return
        self.type, self.value = self.BytesToValue(bytes)

class Node(NodeBase):
    """A device tree node

    Properties:
        offset: Integer offset in the device tree
        name: Device tree node tname
        path: Full path to node, along with the node name itself
        _fdt: Device tree object
        subnodes: A list of subnodes for this node, each a Node object
        props: A dict of properties for this node, each a Prop object.
            Keyed by property name
    """
    def __init__(self, fdt, offset, name, path):
        NodeBase.__init__(self, fdt, offset, name, path)

    def Offset(self):
        """Returns the offset of a node, after checking the cache

        This should be used instead of self._offset directly, to ensure that
        the cache does not contain invalid offsets.
        """
        self._fdt.CheckCache()
        return self._offset

    def Scan(self):
        """Scan a node's properties and subnodes

        This fills in the props and subnodes properties, recursively
        searching into subnodes so that the entire tree is built.
        """
        self.props = self._fdt.GetProps(self, self.path)

        offset = libfdt.fdt_first_subnode(self._fdt.GetFdt(), self.Offset())
        while offset >= 0:
            sep = '' if self.path[-1] == '/' else '/'
            name = libfdt.Name(self._fdt.GetFdt(), offset)
            path = self.path + sep + name
            node = Node(self._fdt, offset, name, path)
            self.subnodes.append(node)

            node.Scan()
            offset = libfdt.fdt_next_subnode(self._fdt.GetFdt(), offset)

    def Refresh(self, my_offset):
        """Fix up the _offset for each node, recursively

        Note: This does not take account of property offsets - these will not
        be updated.
        """
        if self._offset != my_offset:
            #print '%s: %d -> %d\n' % (self.path, self._offset, my_offset)
            self._offset = my_offset
        offset = libfdt.fdt_first_subnode(self._fdt.GetFdt(), self._offset)
        for subnode in self.subnodes:
            subnode.Refresh(offset)
            offset = libfdt.fdt_next_subnode(self._fdt.GetFdt(), offset)

class FdtNormal(Fdt):
    """Provides simple access to a flat device tree blob using libfdt.

    Properties:
        _fdt: Device tree contents (bytearray)
        _cached_offsets: True if all the nodes have a valid _offset property,
            False if something has changed to invalidate the offsets
    """
    def __init__(self, fname):
        Fdt.__init__(self, fname)
        self._cached_offsets = False
        if self._fname:
            self._fname = fdt_util.EnsureCompiled(self._fname)

            with open(self._fname) as fd:
                self._fdt = fd.read()

    def GetFdt(self):
        """Get the contents of the FDT

        Returns:
            The FDT contents as a string of bytes
        """
        return self._fdt

    def GetProps(self, node, path):
        """Get all properties from a node.

        Args:
            node: Full path to node name to look in.

        Returns:
            A dictionary containing all the properties, indexed by node name.
            The entries are Prop objects.

        Raises:
            ValueError: if the node does not exist.
        """
        offset = libfdt.fdt_path_offset(self._fdt, path)
        if offset < 0:
            libfdt.Raise(offset)
        props_dict = {}
        poffset = libfdt.fdt_first_property_offset(self._fdt, offset)
        while poffset >= 0:
            dprop, plen = libfdt.fdt_get_property_by_offset(self._fdt, poffset)
            prop = Prop(node, poffset, libfdt.String(self._fdt, dprop.nameoff),
                        libfdt.Data(dprop))
            props_dict[prop.name] = prop

            poffset = libfdt.fdt_next_property_offset(self._fdt, poffset)
        return props_dict

    def Invalidate(self):
        """Mark our offset cache as invalid"""
        self._cached_offsets = False

    def CheckCache(self):
        """Refresh the offset cache if needed"""
        if self._cached_offsets:
            return
        self.Refresh()
        self._cached_offsets = True

    def Refresh(self):
        """Refresh the offset cache"""
        self._root.Refresh(0)

    @classmethod
    def Node(self, fdt, offset, name, path):
        """Create a new node

        This is used by Fdt.Scan() to create a new node using the correct
        class.

        Args:
            fdt: Fdt object
            offset: Offset of node
            name: Node name
            path: Full path to node
        """
        node = Node(fdt, offset, name, path)
        return node
