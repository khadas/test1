# SPDX-License-Identifier: GPL-2.0+
# Copyright (c) 2018 Google, Inc
# Written by Simon Glass <sjg@chromium.org>
#

# Support for a Chromium OS verified boot block, used to sign a read-write
# section of the image.

from collections import OrderedDict
import os

from entry import Entry, EntryArg

import fdt_util
import tools

class Entry_vblock(Entry):
    """An entry which contains a Chromium OS verified boot block

    Properties / Entry arguments:
        - keydir: Directory containing the public keys to use
        - keyblock: Name of the key file to use (inside keydir)
        - signprivate: Name of provide key file to use (inside keydir)
        - version: Version number of the vblock (typically 1)
        - kernelkey: Name of the kernel key to use (inside keydir)
        - preamble-flags: Value of the vboot preamble flags (typically 0)

    Chromium OS signs the read-write firmware and kernel, writing the signature
    in this block. This allows U-Boot to verify that the next firmware stage
    and kernel are genuine.
    """
    def __init__(self, section, etype, node):
        Entry.__init__(self, section, etype, node)
        self.content = fdt_util.GetPhandleList(self._node, 'content')
        if not self.content:
            self.Raise("Vblock must have a 'content' property")
        (self.keydir, self.keyblock, self.signprivate, self.version,
         self.kernelkey, self.preamble_flags) = self.GetEntryArgsOrProps([
            EntryArg('keydir', str),
            EntryArg('keyblock', str),
            EntryArg('signprivate', str),
            EntryArg('version', int),
            EntryArg('kernelkey', str),
            EntryArg('preamble-flags', int)])

    def ObtainContents(self):
        # Join up the data files to be signed
        input_data = ''
        for entry_phandle in self.content:
            data = self.section.GetContentsByPhandle(entry_phandle, self)
            if data is None:
                # Data not available yet
                return False
            input_data += data

        output_fname = tools.GetOutputFilename('vblock.%s' % self.name)
        input_fname = tools.GetOutputFilename('input.%s' % self.name)
        tools.WriteFile(input_fname, input_data)
        prefix = self.keydir + '/'
        args = [
            'vbutil_firmware',
            '--vblock', output_fname,
            '--keyblock', prefix + self.keyblock,
            '--signprivate', prefix + self.signprivate,
            '--version', '%d' % self.version,
            '--fv', input_fname,
            '--kernelkey', prefix + self.kernelkey,
            '--flags', '%d' % self.preamble_flags,
        ]
        #out.Notice("Sign '%s' into %s" % (', '.join(self.value), self.label))
        stdout = tools.Run('futility', *args)
        #out.Debug(stdout)
        self.SetContents(tools.ReadFile(output_fname))
        return True
