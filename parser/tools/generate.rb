#
# This file is part of KDevelop
# Copyright (C) 2011  Miquel Sabaté <mikisabate@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#

#!/usr/bin/env ruby

#
# This script is able to: generate the necessary files for the parser
# in order to compile and remove these files if wanted. In order to do
# so, this script accepts four rules:
#  - bison: call bison to generate parser.h and parser.c
#  - gperf: call gperf to generate hash.c
#  - all: bison & gperf
#  - purge: remove parser.h, parser.c and hash.c from the root directory.
#

# Check if the given program exists on your system
def exists? program
  ENV['PATH'].split(File::PATH_SEPARATOR).any? do |directory|
    File.executable?(File.join(directory, program.to_s))
  end
end

# Check if exist bison & gperf on your system
unless exists? 'bison'
  puts 'You need bison to run this script'
end
unless exists? 'gperf'
  puts 'You need gperf to run this script'
end

#
# At this point, the script will execute the given order. The given
# output is as pretty as possible ;)
#

YFLAGS = '-d -o ../parser.c'
GRAMMAR = '../parser.y'
GFLAGS = '-C -p -j1 -i 1 -g -o -t -N rb_reserved_word -k1,3,$ ../tools/gperf.txt > ../hash.c'
FILES = '../parser.h ../parser.c ../hash.c'

# Call bison and beautify the output
def bison
  puts 'Using bison to generate parser.h and parser.c'
  `bison #{GRAMMAR} #{YFLAGS} &> temp.txt`
  IO.foreach 'temp.txt' do |line|
    index = line.index('conflicts:') + 10
    str = line.slice(index, line.length - index)
    puts "Conflicts:#{str}"
  end
  `rm temp.txt`
end

# Just call gperf
def gperf
  puts 'Using gperf to generate hash.c'
  `gperf #{GFLAGS}`
  text = (File.read '../hash.c').gsub /{""}/, '{"", -1}'
  File.open('../hash.c', 'w') { |file| file.puts text }
end

case ARGV[0]
when 'all'
  bison
  gperf
when 'bison'
  bison
when 'gperf'
  gperf
when 'purge'
  `rm -f #{FILES}`
else
  puts 'You have to pass \'all\', \'bison\', \'gperf\' or \'purge\' as a parameter'
end

