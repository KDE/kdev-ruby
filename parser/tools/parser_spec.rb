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
#


# Returns: a String containing the absolute path to the ruby parser.
def parser
  File.join(File.dirname(__FILE__), '../ruby-parser')
end

describe 'Parser' do
  files = Dir[File.join(File.dirname(__FILE__), 'tests/*.rb')]
  files.each do |file|
    name = file.match(/.*\/(.+)+\.rb$/)[1]

    it "test: `#{name}'" do
      expected = File.read "tests/#{name}.txt"
      `#{parser} tests/#{name}.rb`.should == expected
    end
  end

  it 'test: `comments\'' do
    expected = File.read 'tests/comments/expected.txt'
    `#{parser} tests/comments/test.rb true`.should == expected
  end
end
