#
# This file is part of KDevelop
# Copyright (C) 2010  Miquel Sabaté <mikisabate@gmail.com>
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

##
# This script executes "ruby-parser" to test every *.rb file
# located in parser/tests/ and outputs in a file. Then it makes
# a diff with the generated files against the expected results.
# Finally it outputs the results and it cleans the parser/tests
# directory.
# You can also pass the name of a test as a parameter so you
# can run it.

require 'find'


##
# This function does the dirty job. Basically it executes the parser to create
# a file containing the output of the parser. The next step is to make a diff
# between the expected results and the generated output. It detects this cases:
#   - Test OK if all was ok.
#   - Test Failed: if something went wrong
#       -> Bad Syntax if the parser "disliked" our code.
#
def do_diff(str)
  res = :fail
  pid = fork do
    exec("cd .. && ./ruby-parser tests/#{str} > tests/#{str}.out")
  end
  Process.waitpid(pid)
  pid = fork do
    exec("cd ../tests && diff -swu #{str.gsub('.rb', '.txt')} #{str}.out > output.txt")
  end
  Process.waitpid(pid)
  error = 0
  lines = []
  IO.foreach('../tests/output.txt') do |line|
    if line.include?('Error:')
      error = 1
      puts "Test Failed: #{str}. Bad Syntax."
      res = :fail
      break
    end
    lines << line
  end
  if error == 0
    if lines.size == 1
      puts "Test OK: #{str}"
      res = :ok
    else
      puts "Test Failed: #{str}. Generated diff:\n"
      puts lines
      res = :fail
    end
  end
  exec("rm -rf ../tests/#{str}.out ../tests/output.txt") if fork.nil?
  return res
end

# We just want to run a single test, so run it and then exit
unless ARGV[0].nil?
  res = do_diff('../tests/' + ARGV[0])
  if res == :fail
    puts "Test #{ARGV[0]} failed!"
  else
    puts "Passed test #{ARGV[0]}!"
  end
  exit
end

# Counting the results obtained
fails = 0
oks = 0

# Main procedure. It calls do_diff for all *.rb files located in parser/tests/
Find.find('../tests') do |f|
  str = f.gsub(/..\/tests\/?/, '')
  unless str.nil?
    if str.end_with?('rb')
      res = do_diff(str)
      res == :fail ? fails += 1 : oks += 1
    end
  end
end
puts "Number of tests ok: #{oks}\nNumber of tests failed: #{fails}"
