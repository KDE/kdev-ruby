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

#
# Prints the output of the parser in a "fancy" way, translating the numbers
# shown at the expected output of the tests to words for mere mortals. This
# script does the job by executing the parser on a given test and flushing
# its output to a temporary file. Then it does the transalation in a simple way
# and show the output to the user.
# NOTE: To use it, for example, just type "ruby fancy.rb test.rb"
# to execute "tests/test.rb" ;)
#

# Only execute this script if the user provided a name
exit if ARGV[0].nil?

exec("cd .. && ./ruby-parser tests/#{ARGV[0]} > tools/fancy.txt") if fork.nil?
Process.wait

# Array of available tokens
translate = ['whitespace', 'comment', 'plus', 'minus', 'product', 'exp',
             'divide', 'module', 'bit_and', 'bit_or', 'bit_xor', 'keyword_and',
             'keyword_or', 'keyword_not', 'logical_or', 'logical_and',
             'left_shift', 'right_shift', 'negate', 'logical_not',
             'unary_plus', 'unary_minus', 'assign', 'operation_assign',
             'assoc', 'compare', 'equal?', 'not_equal?', 'within_equal',
             'match', 'not_match', 'greater', 'greater_equal', 'lesser',
             'lesser_equal', 'dot2', 'dot3', 'ternary', 'if', 'unless', 'while',
             'until', 'case', 'when', 'BEGIN', 'END', 'for', 'exception',
             'rescue_arg', 'rescue', 'ensure', 'object', 'numeric', 'symbol',
             'body', 'function', 'module', 'class', 'singleton_class',
             'superclass', 'string', 'regexp', 'key', 'array', 'hash', 'lambda',
             'block', 'method_call', 'heredoc', 'break', 'redo', 'retry',
             'next', 'return', 'yield', 'alias', 'defined?', 'undef',
             'array_value', 'backtick']


# This piece of code really does to job
IO.foreach('fancy.txt') do |line|
  print '-- Blank line --' if line == "\n"
  puts line.gsub(/[0-9]+/) { |m| translate[m.to_i] }
end
exec('rm -rf fancy.txt')
