##
# This file is part of KDevelop
# Copyright (C) 2013-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


require 'find'
require 'fileutils'
require 'benchmark'


# This script can be called as follows:
#   --syntax -> check that there's no syntax error when parsing the Ruby
#               standard library.
#   --valgrind -> generate files inside the /tmp/kdev-ruby directory containing
#                 the results as given by memcheck, massif and callgrind.
# There's also the --memcheck, --massif and --callgrind options to run only the
# specified tool instead of all of them.


# Public: Print beautifully
#
# msg   - A String containing the message to be printed.
# error - True if this is an error message, false otherwise (Default: false)
def putb(msg, error = false)
  num = error ? 31 : 32
  puts "\033[#{num}m#{msg}\033[0m"
end

# Returns true if our beloved user requested some candy from valgrind.
#
# param - A String containing the name of the tool.
def valgrind(param)
  ARGV.include?("--#{param}") || ARGV.include?('--valgrind')
end

# Public: execute a valgrind tool.
#
# tool - A String containing the name of the Valgrind's tool.
# opts - A String containing the options to be passed to Valgrind.
# file - A String containing the path to the log file.
def execute(tool, opts, file)
  FileUtils.rm_rf file
  putb "Calling Valgrind\'s #{tool} tool with: #{opts}"
  `valgrind #{opts} #{PARSER} #{TMP} 1`
  putb "#{tool.capitalize} output left at #{file}" unless file.empty?
end


# Setup some basic constants
TMP_D = '/tmp/kdev-ruby'
TMP = File.join(TMP_D, 'stdlib.rb')
PARSER = '../ruby-parser'
if ENV['MRI'].nil?
  putb 'You have to set the MRI environment variable.', true
  exit
end
LIB = File.join(ENV['MRI'], 'lib/')


# If the -c parameter has been passed, just check the syntax for each of
# the files inside the MRI lib/ directory.
if ARGV.include? '--syntax'
  res = { fails: 0, oks: 0 }
  Find.find(LIB) do |path|
    if path.end_with? '.rb'
      print "#{path.gsub(LIB, '')} "
      got = `#{PARSER} #{path}`

      if got.include? 'syntax error'
        puts '=> Fail!'
        res[:fails] += 1
      else
        puts '=> OK'
        res[:oks] += 1
      end
    end
  end

  totals = (res[:oks] + res[:fails]).to_f
  win = (100 * res[:oks].to_f/ totals).round(2)
  damn = (100 * res[:fails].to_f/ totals).round(2)
  puts "Holy says: Oks: #{res[:oks]} (#{win}%), Fails: #{res[:fails]} (#{damn}%)"
  exit
end

# Generate the stdlib file
putb "Generating temporary file '#{TMP}' from '#{LIB}'"
FileUtils.mkdir_p TMP_D
FileUtils.rm_rf TMP
File.open(TMP, 'a+', 0644) do |f|
  Find.find(LIB) do |path|
    next unless path.end_with? '.rb'
    # Writing to the file. Note that we remove __END__ so it doesn't stop
    # at the middle of the script.
    f.write IO.read(path).gsub('__END__', '')
  end
end
ok = false

#
# Valgrind is in da house !
#

if valgrind 'memcheck'
  file = File.join(TMP_D, 'memcheck.txt')
  opts = "--track-origins=yes --tool=memcheck --leak-check=full --show-reachable=yes -v --log-file=#{file}"
  execute 'memcheck', opts, file
  ok = true
end

if valgrind 'callgrind'
  callgrind = File.join(TMP_D, 'callgrind.out')
  opts = '--tool=callgrind -q -v --dump-instr=yes'
  execute 'callgrind', opts, callgrind
  out = Dir.glob("#{File.expand_path(File.dirname(__FILE__))}/callgrind*").first
  FileUtils.mv out, callgrind
  ok = true
end

if valgrind 'massif'
  massif = File.join(TMP_D, 'massif.out')
  opts = '--tool=massif --tool=massif -q -v --stacks=yes'
  execute 'massif', opts, massif
  out = Dir.glob("#{File.expand_path(File.dirname(__FILE__))}/massif*").first
  FileUtils.mv out, massif
  ok = true
end

#
# Benchmarking like a boss
#

if ARGV.include? '--bench'
  Benchmark.bm do |x|
    x.report('parser: ') { 10.times { `#{PARSER} #{TMP}` } }
  end
  ok = true
end

# Try to GTFO !
exit if ok

#
# Wow ! You're a looser !!
#
puts <<-USAGE
Usage: ruby holy.rb [options]
  --syntax \t Just check the syntax parsing.
  --bench \t Let's benchmark this thing !
  --valgrind \t Execute all the tools from Valgrind that we're able to execute.
  --memcheck \t Just call Valgrind's memcheck tool.
  --massif \t Just call Valgrind's massif tool.
  --callgrind \t Just call Valgrind's callgrind tool.
USAGE
