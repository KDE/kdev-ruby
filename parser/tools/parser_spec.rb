##
# This file is part of KDevelop
# Copyright (C) 2012  Miquel Sabaté <mikisabate@gmail.com>
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


# Returns a String containing the absolute path to the ruby parser.
def parser
  File.join(File.dirname(__FILE__), '../ruby-parser')
end

describe 'Parser' do
  base = File.dirname(__FILE__)
  files = Dir[File.join(base, 'tests/*.rb')]
  files.each do |file|
    name = file.match(/.*\/(.+)+\.rb$/)[1]

    it "test: `#{name}'" do
      expected = File.read "#{base}/tests/#{name}.txt"
      `#{parser} #{base}/tests/#{name}.rb`.should == expected
    end
  end

  it 'test: `comments\'' do
    expected = File.read "#{base}/tests/comments/expected.txt"
    `#{parser} #{base}/tests/comments/test.rb 2`.should == expected
  end

  context 'Ruby versions:' do
    it '1.8.x -> 1.9.x transition' do
      output = `#{parser} #{base}/tests/errors/from18to19.rb 0`.split("\n")
      output.first.should == 'Line: 1, Column: 8; This syntax is only available in Ruby 1.9.x or higher.'
      output.last.should == 'Line: 2, Column: 3; "->" syntax is only available in Ruby 1.9.x or higher.'
    end

    pending '1.9.x -> 2.0.x transition'
  end
end
