#! /usr/bin/env python3
#
# Copyright 2017 Linaro Limited
# Copyright (c) 2017-2018, Arm Limited.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""
Assemble multiple images into a single image that can be flashed on the device.
"""

import argparse
import errno
import io
import re
import os
import shutil

offset_re = re.compile(r"^#define ([0-9A-Z_]+)_IMAGE_OFFSET\s+((0x)?[0-9a-fA-F]+)")
size_re   = re.compile(r"^#define ([0-9A-Z_]+)_IMAGE_MAX_SIZE\s+((0x)?[0-9a-fA-F]+)")

class Assembly():
    def __init__(self, layout_path, output):
        self.output = output
        self.layout_path = layout_path
        self.find_slots()
        try:
            os.unlink(output)
        except OSError as e:
            if e.errno != errno.ENOENT:
                raise

    def find_slots(self):
        offsets = {}
        sizes = {}

        if os.path.isabs(self.layout_path):
            configFile = self.layout_path
        else:
            scriptsDir = os.path.dirname(os.path.abspath(__file__))
            configFile = os.path.join(scriptsDir, self.layout_path)

        with open(configFile, 'r') as fd:
            for line in fd:
                m = offset_re.match(line)
                if m is not None:
                    offsets[m.group(1)] = int(m.group(2), 0)
                m = size_re.match(line)
                if m is not None:
                    sizes[m.group(1)] = int(m.group(2), 0)

        if 'SECURE' not in offsets:
            raise Exception("Image config does not have secure partition")

        if 'NON_SECURE' not in offsets:
            raise Exception("Image config does not have non-secure partition")

        self.offsets = offsets
        self.sizes = sizes

    def add_image(self, source, partition):
        with open(self.output, 'ab') as ofd:
            ofd.seek(0, os.SEEK_END)
            pos = ofd.tell()
            if pos > self.offsets[partition]:
                raise Exception("Partitions not in order, unsupported")
            if pos < self.offsets[partition]:
                ofd.write(b'\xFF' * (self.offsets[partition] - pos))
            statinfo = os.stat(source)
            if statinfo.st_size > self.sizes[partition]:
                raise Exception("Image {} is too large for partition".format(source))
            with open(source, 'rb') as rfd:
                shutil.copyfileobj(rfd, ofd, 0x10000)

def main():
    parser = argparse.ArgumentParser()

    parser.add_argument('-l', '--layout', required=True,
            help='Location of the memory layout file')
    parser.add_argument('-s', '--secure', required=True,
            help='Unsigned secure image')
    parser.add_argument('-n', '--non_secure',
            help='Unsigned non-secure image')
    parser.add_argument('-o', '--output', required=True,
            help='Filename to write full image to')

    args = parser.parse_args()
    output = Assembly(args.layout, args.output)


    output.add_image(args.secure, "SECURE")
    output.add_image(args.non_secure, "NON_SECURE")

if __name__ == '__main__':
    main()
