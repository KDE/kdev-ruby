#
# This file is part of KDevelop
# Copyright (C) 2011  Alexander Dymo <adymo@kdevelop.org>
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


require 'test/unit'
require File.dirname(__FILE__) + '/assert_same/init'

CDIR = "#{File.dirname(__FILE__)}/tests/comments"


class AssertSameTest < Test::Unit::TestCase
  Dir["#{File.dirname(__FILE__)}/tests/*.rb"].each do |ruby_file|
    define_method "test_#{File.basename(ruby_file, ".rb")}" do
      log_file = ruby_file.gsub(/rb$/, 'txt')
      ast = get_ast(ruby_file)
      assert_same ast, :log => log_file
    end
  end

  def test_comments_fetching
    comments = get_ast("#{CDIR}/test.rb", true)
    assert_same comments, :log => "#{CDIR}/expected.txt"
  end

private

  def get_ast(filename, opt = nil)
    # FIXME: adymo: properly find ruby-parser executable
    `#{File.dirname(__FILE__)}/../ruby-parser #{filename} #{opt}`
  end
end
