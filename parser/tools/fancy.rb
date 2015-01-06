##
# This file is part of KDevelop
# Copyright (C) 2011-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
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


#!/usr/bin/env ruby

#
# Prints the output of the parser in a "fancy" way, translating the numbers
# shown at the expected output of the tests to words for mere mortals. This
# script does the job by executing the parser on a given test and flushing
# its output to a temporary file. Then it does the transalation in a simple way
# and shows the output to the user.
# NOTE: To use it, for example, just type "ruby fancy.rb test.rb"
# to execute "tests/test.rb" ;)
#

# Only execute this script if the user provided a name
exit if ARGV[0].nil?

translate = [
  'whitespace', 'comment', 'plus', 'minus', 'mul', 'pow', 'div', 'mod', 'bit_and', 'bit_or', 'bit_xor',
  'kw_and', 'kw_or', 'kw_not', 'or', 'and', 'lshift', 'rshift', 'neg', 'not', 'unary_plus',
  'unay_minus', 'assign', 'op_assign', 'assoc', 'cmp', 'eq', 'neq', 'eqq', 'match', 'nmatch',
  'greater', 'geq', 'lesser', 'leq', 'dot2', 'dot3', 'ternary', 'if', 'unless', 'while',
  'until', 'case', 'when', 'BEGIN', 'END', 'for', 'begin', 'rescue_arg', 'rescue', 'ensure',
  'object', 'numeric', 'symbol', 'body', 'function', 'module', 'class', 'singleton_class', 'super', 'string',
  'regexp', 'key', 'array', 'hash', 'block', 'method_call', 'heredoc', 'break', 'redo', 'retry',
  'next', 'return', 'yield', 'alias', 'defined', 'undef', 'array_value', '__END__', 'true', 'false',
  'nil', 'self', '__ENCODING__', '__FILE__', '__LINE__'
]

output = `../ruby-parser tests/#{ARGV.first}.rb`
output.split("\n").each do |l|
  line = l.gsub(/[0-9]+(\[)/) 	{ |m| "#{translate[m.to_i]}[" }
  puts line.gsub(/[0-9]+(\()/)	{ |m| "#{translate[m.to_i]}(" }
end
