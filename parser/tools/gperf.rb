##
# This file is part of KDevelop
# Copyright (C) 2011  Miquel Sabaté <mikisabate@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
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

##
# This script just calls gperf with the correct arguments in order
# to generate the hash.c file.


##
# Check if the given program exists on your system
#
# @param *String* program The name of the program.
#
# @return *Boolean* True if the program exists on your system,
# false otherwise.
def exists? program
  ENV['PATH'].split(File::PATH_SEPARATOR).any? do |directory|
    File.executable?(File.join(directory, program.to_s))
  end
end

# Check if exists gperf on your system
unless exists? 'gperf'
  puts 'You need gperf to run this script'
  exit
end

# Let's execute gperf with the appropiate arguments.

GFLAGS = '-C -p -j1 -i 1 -g -o -t -N rb_reserved_word -k1,3,$ gperf.txt > ../hash.c'

puts 'Using gperf to generate hash.c'
`gperf #{GFLAGS}`
text = File.read('../hash.c').gsub /{""}/, '{"", {0,0}, 0}'
File.open('../hash.c', 'w') { |file| file.puts text }
