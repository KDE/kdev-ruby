##
# This file is part of KDevelop
# Copyright (C) 2012-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
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


# Returns a String containing the absolute path to the ruby parser.
def parser
  File.join(File.dirname(__FILE__), '../ruby-parser')
end

describe 'Parser' do
  base = File.dirname(__FILE__)

  # Regular tests
  files = Dir[File.join(base, 'tests/*.rb')]
  files.each do |file|
    name = file.match(/.*\/(.+)+\.rb$/)[1]

    it "test: `#{name}'" do
      expected = File.read "#{base}/tests/#{name}.txt"
      expect(`#{parser} #{base}/tests/#{name}.rb`).to eq(expected)
    end
  end

  # Testing that the comments are stored properly.
  it 'test: `comments\'' do
    expected = File.read "#{base}/tests/comments/expected.txt"
    expect(`#{parser} #{base}/tests/comments/test.rb 2`).to eq(expected)
  end

  # Testing the warnings on incompatible Ruby versions.
  context 'Ruby versions:' do
    it '1.8.x -> 1.9.x transition' do
      output = `#{parser} #{base}/tests/errors/from18to19.rb 0`
      expect(output).to eq(<<-HEREDOC.gsub(/^\s+/, '')
        Line: 1, Column: 16; This syntax is only available in Ruby 1.9.x or higher.
        Line: 2, Column: 4; "->" syntax is only available in Ruby 1.9.x or higher.
        Line: 3, Column: 15; Block local variables are only available in Ruby 1.9.x or higher.
      HEREDOC
      )
    end

    it '1.9.x -> 2.0.x transition' do
      output = `#{parser} #{base}/tests/errors/from19to20.rb 0`
      expect(output).to eq(<<-HEREDOC.gsub(/^\s+/, '')
        Line: 1, Column: 22; Keyword arguments are only available in Ruby 2.0.x or higher.
        Line: 4, Column: 21; Keyword arguments are only available in Ruby 2.0.x or higher.
        Line: 9, Column: 9; This syntax is only available in Ruby 1.9.x or higher.
        Line: 9, Column: 15; This syntax is only available in Ruby 1.9.x or higher.
        Line: 11, Column: 25; Keyword arguments are only available in Ruby 2.0.x or higher.
        Line: 14, Column: 46; Keyword arguments are only available in Ruby 2.0.x or higher.
        Line: 17, Column: 2; This shortcut is only available in Ruby 2.0.x or higher.
      HEREDOC
      )
    end

    it '2.0.x -> 2.1.x transition' do
      output = `#{parser} #{base}/tests/errors/from20to21.rb 0`
      expect(output).to eq(<<-HEREDOC.gsub(/^\s+/, '')
        Line: 2, Column: 8; Imaginary literals are only available in Ruby 2.1.x or higher.
        Line: 3, Column: 8; Rational literals are only available in Ruby 2.1.x or higher.
      HEREDOC
      )
    end
  end
end
