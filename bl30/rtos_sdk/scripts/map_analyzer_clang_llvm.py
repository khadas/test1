#!/usr/bin/python3
#coding:utf-8
#
# Copyright (c) 2021-2022 Amlogic, Inc. All rights reserved.
#
# SPDX-License-Identifier: MIT
#


from __future__ import print_function

import sys
import os
import argparse
import operator

parser = argparse.ArgumentParser(description='total size of each object file in an ld linker map.')
parser.add_argument('map_file', help="A map file generated by passing -M/--print-map to ld during linking.")
parser.add_argument('--combine', action='store_true',
                    help="All object files in an .a archive or in a directory are combined")
args = parser.parse_args()

class SectionSize():
    text = 0
    data = 0  # Including metadata like import tables
    bss = 0
    customize = 0
    def rom(self):
        return self.text + self.data
    def ram(self):
        return self.data + self.bss
    def total(self):
        return self.text + self.data + self.bss
    def add_clang_llvm_section(self, section, size):
        if section == ".text":
            self.text += size
        elif section == ".bss":
            self.bss += size
        elif section == ".data" or section == ".rodata":
            self.data += size
        else:
            if (size > 0):
                print("customer section:%s, size:%d" % (section, size))
                self.customize += size

size_by_source = {}
current_section = None
last_section = None
last_source = None
current_addr = 0x00;
last_addr = "0"
size = 0x00;
last_size = 0x00;
last_real_size = 0x00;
heap = 0
stack = 0
with open(args.map_file) as f:
    print("clang+llvm toolchain map analyzer")
    lines = iter(f)
    for line in lines:
        line = line.strip('\n')

        if operator.contains(line, ":(.debug_") or operator.contains(line, ":(.comment"):
            continue
        elif operator.contains(line, ":(.shstrtab") or operator.contains(line, ":(.symtab") or operator.contains(line, ":(.strtab"):
            continue
        elif (line.endswith(".text")) or (line.endswith(".data")) or (line.endswith(".rodata")) or (line.endswith(".bss")):
            pieces = line.split(None, 5)
            current_section = pieces[4]
        elif operator.contains(line, ":(.") \
            or operator.contains(line, ".heap") \
            or operator.contains(line, ".stack") \
            or operator.contains(line, ":(.text") \
            or operator.contains(line, ":(.data") \
            or operator.contains(line, ":(.bss") \
            or operator.contains(line, ":(.rodata."):
            pieces = line.split(None, 5)  # Don't split paths containing spaces
            size = int(pieces[2], 16)
            source = pieces[4]
            current_addr = pieces[1]
            if operator.contains(line, '.heap'):
                heap += size
            elif operator.contains(line, '.stack'):
                stack += size

            if args.combine:
                if '.a(' in source:
                    source = source[:source.index('.a(') + 2]
                elif '.dir' in source:
                    source = source[:source.find(".dir")]
                elif '<internal>' in source:
                    source = last_source
                else:
                    source = os.path.basename(source)

            if source not in size_by_source:
                size_by_source[source] = SectionSize()

            last_real_size =  operator.sub(int(current_addr, 16), int(last_addr, 16))
            if operator.ne(last_size, 0x00) and operator.gt(last_real_size, last_size):
                #fixed the last size from address by the size not from last section
                if (last_section != None) and (current_section != last_section ):
                    #fixed the last size from last source
                    if (last_source != None) and (source != last_source):
                        size_by_source[last_source].add_clang_llvm_section(last_section, (last_real_size - last_size))
                    else:
                        size_by_source[source].add_clang_llvm_section(last_section, (last_real_size - last_size))
                else:
                    if (last_source != None) and (source != last_source):
                        size_by_source[last_source].add_clang_llvm_section(current_section, (last_real_size - last_size))
                    else:
                        size_by_source[source].add_clang_llvm_section(current_section, (last_real_size - last_size))
            size_by_source[source].add_clang_llvm_section(current_section, size)

            last_addr = current_addr
            last_size = size
            last_section = current_section;
            last_source = source;

# Print out summary
sources = list(size_by_source.keys())
sources.sort(key = lambda x: size_by_source[x].total())
sumrom = sumram = sumcode = sumdata = sumbss = sumcustomize = 0

print('---------------------------------------------------------------------------------------------------')
col_format = "%-20s\t%-12s\t%-12s\t%-7s\t%-12s\t%-12s\t%-7s"
print(col_format % ("module file", "ROM(text+data)", "RAM(data+bss)", ".text", ".data", ".bss", "customize"))
for source in sources:
    size = size_by_source[source]
    sumcode += size.text
    sumdata += size.data
    sumbss  += size.bss
    sumrom += size.rom()
    sumram += size.ram()
    sumcustomize += size.customize
    print(col_format % (os.path.basename(source), size.rom(), size.ram(), size.text, size.data, size.bss, size.customize))

print('---------------------------------------------------------------------------------------------------')
col_format = "%-5s\t%-12s\t%-12s\t%-7s\t%-12s\t%-12s\t%-7s\t%-7s\t%-7s"
print(col_format % ("    ", "ROM(text+data)", "RAM(data+bss)", ".text", ".data", ".bss", "cust", "stack", "heap" ))
print(col_format % ("total", sumrom, sumram, sumcode, sumdata, sumbss, sumcustomize, stack, heap))
print('---------------------------------------------------------------------------------------------------')
