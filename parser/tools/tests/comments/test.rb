#
# This comment will be ignored by the parser.
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


# This comment is not useful.
if ARGV[0].nil
  exit
end

##
# However, now we're talking about a documentation comment.
# We want to store this comment
class Klass
  # There's nothing to do here, therefore this comment will
  # not be stored.
end

#
# This is also a documentation comment, store it!
#
class Clas < Klass
  # I'm a useful comment
  def foo; end

  # this is useless

  # But this one is not
  def foo1; end
end

# Store this comment
module Aa
  # and this one too.
  module Bb
  end

  # but not this one.
end