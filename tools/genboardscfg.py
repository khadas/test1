#!/usr/bin/env python
#
# Author: Masahiro Yamada <yamada.m@jp.panasonic.com>
#
# SPDX-License-Identifier:	GPL-2.0+
#

"""
Converter from Kconfig and MAINTAINERS to boards.cfg

Run 'tools/genboardscfg.py' to create boards.cfg file.

Run 'tools/genboardscfg.py -h' for available options.
"""

import errno
import fnmatch
import glob
import optparse
import os
import re
import shutil
import subprocess
import sys
import tempfile
import time

BOARD_FILE = 'boards.cfg'
CONFIG_DIR = 'configs'
REFORMAT_CMD = [os.path.join('tools', 'reformat.py'),
                '-i', '-d', '-', '-s', '8']
SHOW_GNU_MAKE = 'scripts/show-gnu-make'
SLEEP_TIME=0.03

COMMENT_BLOCK = '''#
# List of boards
#   Automatically generated by %s: don't edit
#
# Status, Arch, CPU, SoC, Vendor, Board, Target, Options, Maintainers

''' % __file__

### helper functions ###
def get_terminal_columns():
    """Get the width of the terminal.

    Returns:
      The width of the terminal, or zero if the stdout is not
      associated with tty.
    """
    try:
        return shutil.get_terminal_size().columns # Python 3.3~
    except AttributeError:
        import fcntl
        import termios
        import struct
        arg = struct.pack('hhhh', 0, 0, 0, 0)
        try:
            ret = fcntl.ioctl(sys.stdout.fileno(), termios.TIOCGWINSZ, arg)
        except IOError as exception:
            # If 'Inappropriate ioctl for device' error occurs,
            # stdout is probably redirected. Return 0.
            return 0
        return struct.unpack('hhhh', ret)[1]

def get_devnull():
    """Get the file object of '/dev/null' device."""
    try:
        devnull = subprocess.DEVNULL # py3k
    except AttributeError:
        devnull = open(os.devnull, 'wb')
    return devnull

def check_top_directory():
    """Exit if we are not at the top of source directory."""
    for f in ('README', 'Licenses'):
        if not os.path.exists(f):
            sys.exit('Please run at the top of source directory.')

def get_make_cmd():
    """Get the command name of GNU Make."""
    process = subprocess.Popen([SHOW_GNU_MAKE], stdout=subprocess.PIPE)
    ret = process.communicate()
    if process.returncode:
        sys.exit('GNU Make not found')
    return ret[0].rstrip()

### classes ###
class MaintainersDatabase:

    """The database of board status and maintainers."""

    def __init__(self):
        """Create an empty database."""
        self.database = {}

    def get_status(self, target):
        """Return the status of the given board.

        Returns:
          Either 'Active' or 'Orphan'
        """
        if not target in self.database:
            print >> sys.stderr, "WARNING: no status info for '%s'" % target
            return '-'

        tmp = self.database[target][0]
        if tmp.startswith('Maintained'):
            return 'Active'
        elif tmp.startswith('Orphan'):
            return 'Orphan'
        else:
            print >> sys.stderr, ("WARNING: %s: unknown status for '%s'" %
                                  (tmp, target))
            return '-'

    def get_maintainers(self, target):
        """Return the maintainers of the given board.

        If the board has two or more maintainers, they are separated
        with colons.
        """
        if not target in self.database:
            print >> sys.stderr, "WARNING: no maintainers for '%s'" % target
            return ''

        return ':'.join(self.database[target][1])

    def parse_file(self, file):
        """Parse the given MAINTAINERS file.

        This method parses MAINTAINERS and add board status and
        maintainers information to the database.

        Arguments:
          file: MAINTAINERS file to be parsed
        """
        targets = []
        maintainers = []
        status = '-'
        for line in open(file):
            tag, rest = line[:2], line[2:].strip()
            if tag == 'M:':
                maintainers.append(rest)
            elif tag == 'F:':
                # expand wildcard and filter by 'configs/*_defconfig'
                for f in glob.glob(rest):
                    front, match, rear = f.partition('configs/')
                    if not front and match:
                        front, match, rear = rear.rpartition('_defconfig')
                        if match and not rear:
                            targets.append(front)
            elif tag == 'S:':
                status = rest
            elif line == '\n':
                for target in targets:
                    self.database[target] = (status, maintainers)
                targets = []
                maintainers = []
                status = '-'
        if targets:
            for target in targets:
                self.database[target] = (status, maintainers)

class DotConfigParser:

    """A parser of .config file.

    Each line of the output should have the form of:
    Status, Arch, CPU, SoC, Vendor, Board, Target, Options, Maintainers
    Most of them are extracted from .config file.
    MAINTAINERS files are also consulted for Status and Maintainers fields.
    """

    re_arch = re.compile(r'CONFIG_SYS_ARCH="(.*)"')
    re_cpu = re.compile(r'CONFIG_SYS_CPU="(.*)"')
    re_soc = re.compile(r'CONFIG_SYS_SOC="(.*)"')
    re_vendor = re.compile(r'CONFIG_SYS_VENDOR="(.*)"')
    re_board = re.compile(r'CONFIG_SYS_BOARD="(.*)"')
    re_config = re.compile(r'CONFIG_SYS_CONFIG_NAME="(.*)"')
    re_options = re.compile(r'CONFIG_SYS_EXTRA_OPTIONS="(.*)"')
    re_list = (('arch', re_arch), ('cpu', re_cpu), ('soc', re_soc),
               ('vendor', re_vendor), ('board', re_board),
               ('config', re_config), ('options', re_options))
    must_fields = ('arch', 'config')

    def __init__(self, build_dir, output, maintainers_database):
        """Create a new .config perser.

        Arguments:
          build_dir: Build directory where .config is located
          output: File object which the result is written to
          maintainers_database: An instance of class MaintainersDatabase
        """
        self.dotconfig = os.path.join(build_dir, '.config')
        self.output = output
        self.database = maintainers_database

    def parse(self, defconfig):
        """Parse .config file and output one-line database for the given board.

        Arguments:
          defconfig: Board (defconfig) name
        """
        fields = {}
        for line in open(self.dotconfig):
            if not line.startswith('CONFIG_SYS_'):
                continue
            for (key, pattern) in self.re_list:
                m = pattern.match(line)
                if m and m.group(1):
                    fields[key] = m.group(1)
                    break

        # sanity check of '.config' file
        for field in self.must_fields:
            if not field in fields:
                print >> sys.stderr, (
                    "WARNING: '%s' is not defined in '%s'. Skip." %
                    (field, defconfig))
                return

        # fix-up for aarch64
        if fields['arch'] == 'arm' and 'cpu' in fields:
            if fields['cpu'] == 'armv8':
                fields['arch'] = 'aarch64'

        target, match, rear = defconfig.partition('_defconfig')
        assert match and not rear, \
                                '%s : invalid defconfig file name' % defconfig

        fields['status'] = self.database.get_status(target)
        fields['maintainers'] = self.database.get_maintainers(target)

        if 'options' in fields:
            options = fields['config'] + ':' + \
                      fields['options'].replace(r'\"', '"')
        elif fields['config'] != target:
            options = fields['config']
        else:
            options = '-'

        self.output.write((' '.join(['%s'] * 9) + '\n')  %
                          (fields['status'],
                           fields['arch'],
                           fields.get('cpu', '-'),
                           fields.get('soc', '-'),
                           fields.get('vendor', '-'),
                           fields.get('board', '-'),
                           target,
                           options,
                           fields['maintainers']))

class Slot:

    """A slot to store a subprocess.

    Each instance of this class handles one subprocess.
    This class is useful to control multiple processes
    for faster processing.
    """

    def __init__(self, output, maintainers_database, devnull, make_cmd):
        """Create a new slot.

        Arguments:
          output: File object which the result is written to
          maintainers_database: An instance of class MaintainersDatabase
        """
        self.occupied = False
        self.build_dir = tempfile.mkdtemp()
        self.devnull = devnull
        self.make_cmd = make_cmd
        self.parser = DotConfigParser(self.build_dir, output,
                                      maintainers_database)

    def __del__(self):
        """Delete the working directory"""
        if not self.occupied:
            while self.ps.poll() == None:
                pass
        shutil.rmtree(self.build_dir)

    def add(self, defconfig):
        """Add a new subprocess to the slot.

        Fails if the slot is occupied, that is, the current subprocess
        is still running.

        Arguments:
          defconfig: Board (defconfig) name

        Returns:
          Return True on success or False on fail
        """
        if self.occupied:
            return False
        o = 'O=' + self.build_dir
        self.ps = subprocess.Popen([self.make_cmd, o, defconfig],
                                   stdout=self.devnull)
        self.defconfig = defconfig
        self.occupied = True
        return True

    def poll(self):
        """Check if the subprocess is running and invoke the .config
        parser if the subprocess is terminated.

        Returns:
          Return True if the subprocess is terminated, False otherwise
        """
        if not self.occupied:
            return True
        if self.ps.poll() == None:
            return False
        if self.ps.poll() == 0:
            self.parser.parse(self.defconfig)
        else:
            print >> sys.stderr, ("WARNING: failed to process '%s'. skip." %
                                  self.defconfig)
        self.occupied = False
        return True

class Slots:

    """Controller of the array of subprocess slots."""

    def __init__(self, jobs, output, maintainers_database):
        """Create a new slots controller.

        Arguments:
          jobs: A number of slots to instantiate
          output: File object which the result is written to
          maintainers_database: An instance of class MaintainersDatabase
        """
        self.slots = []
        devnull = get_devnull()
        make_cmd = get_make_cmd()
        for i in range(jobs):
            self.slots.append(Slot(output, maintainers_database,
                                   devnull, make_cmd))

    def add(self, defconfig):
        """Add a new subprocess if a vacant slot is available.

        Arguments:
          defconfig: Board (defconfig) name

        Returns:
          Return True on success or False on fail
        """
        for slot in self.slots:
            if slot.add(defconfig):
                return True
        return False

    def available(self):
        """Check if there is a vacant slot.

        Returns:
          Return True if a vacant slot is found, False if all slots are full
        """
        for slot in self.slots:
            if slot.poll():
                return True
        return False

    def empty(self):
        """Check if all slots are vacant.

        Returns:
          Return True if all slots are vacant, False if at least one slot
          is running
        """
        ret = True
        for slot in self.slots:
            if not slot.poll():
                ret = False
        return ret

class Indicator:

    """A class to control the progress indicator."""

    MIN_WIDTH = 15
    MAX_WIDTH = 70

    def __init__(self, total):
        """Create an instance.

        Arguments:
          total: A number of boards
        """
        self.total = total
        self.cur = 0
        width = get_terminal_columns()
        width = min(width, self.MAX_WIDTH)
        width -= self.MIN_WIDTH
        if width > 0:
            self.enabled = True
        else:
            self.enabled = False
        self.width = width

    def inc(self):
        """Increment the counter and show the progress bar."""
        if not self.enabled:
            return
        self.cur += 1
        arrow_len = self.width * self.cur // self.total
        msg = '%4d/%d [' % (self.cur, self.total)
        msg += '=' * arrow_len + '>' + ' ' * (self.width - arrow_len) + ']'
        sys.stdout.write('\r' + msg)
        sys.stdout.flush()

def __gen_boards_cfg(jobs):
    """Generate boards.cfg file.

    Arguments:
      jobs: The number of jobs to run simultaneously

    Note:
      The incomplete boards.cfg is left over when an error (including
      the termination by the keyboard interrupt) occurs on the halfway.
    """
    check_top_directory()
    print 'Generating %s ...  (jobs: %d)' % (BOARD_FILE, jobs)

    # All the defconfig files to be processed
    defconfigs = []
    for (dirpath, dirnames, filenames) in os.walk(CONFIG_DIR):
        dirpath = dirpath[len(CONFIG_DIR) + 1:]
        for filename in fnmatch.filter(filenames, '*_defconfig'):
            if fnmatch.fnmatch(filename, '.*'):
                continue
            defconfigs.append(os.path.join(dirpath, filename))

    # Parse all the MAINTAINERS files
    maintainers_database = MaintainersDatabase()
    for (dirpath, dirnames, filenames) in os.walk('.'):
        if 'MAINTAINERS' in filenames:
            maintainers_database.parse_file(os.path.join(dirpath,
                                                         'MAINTAINERS'))

    # Output lines should be piped into the reformat tool
    reformat_process = subprocess.Popen(REFORMAT_CMD, stdin=subprocess.PIPE,
                                        stdout=open(BOARD_FILE, 'w'))
    pipe = reformat_process.stdin
    pipe.write(COMMENT_BLOCK)

    indicator = Indicator(len(defconfigs))
    slots = Slots(jobs, pipe, maintainers_database)

    # Main loop to process defconfig files:
    #  Add a new subprocess into a vacant slot.
    #  Sleep if there is no available slot.
    for defconfig in defconfigs:
        while not slots.add(defconfig):
            while not slots.available():
                # No available slot: sleep for a while
                time.sleep(SLEEP_TIME)
        indicator.inc()

    # wait until all the subprocesses finish
    while not slots.empty():
        time.sleep(SLEEP_TIME)
    print ''

    # wait until the reformat tool finishes
    reformat_process.communicate()
    if reformat_process.returncode != 0:
        sys.exit('"%s" failed' % REFORMAT_CMD[0])

def gen_boards_cfg(jobs):
    """Generate boards.cfg file.

    The incomplete boards.cfg is deleted if an error (including
    the termination by the keyboard interrupt) occurs on the halfway.

    Arguments:
      jobs: The number of jobs to run simultaneously
    """
    try:
        __gen_boards_cfg(jobs)
    except:
        # We should remove incomplete boards.cfg
        try:
            os.remove(BOARD_FILE)
        except OSError as exception:
            # Ignore 'No such file or directory' error
            if exception.errno != errno.ENOENT:
                raise
        raise

def main():
    parser = optparse.OptionParser()
    # Add options here
    parser.add_option('-j', '--jobs',
                      help='the number of jobs to run simultaneously')
    (options, args) = parser.parse_args()
    if options.jobs:
        try:
            jobs = int(options.jobs)
        except ValueError:
            sys.exit('Option -j (--jobs) takes a number')
    else:
        try:
            jobs = int(subprocess.Popen(['getconf', '_NPROCESSORS_ONLN'],
                                     stdout=subprocess.PIPE).communicate()[0])
        except (OSError, ValueError):
            print 'info: failed to get the number of CPUs. Set jobs to 1'
            jobs = 1
    gen_boards_cfg(jobs)

if __name__ == '__main__':
    main()
