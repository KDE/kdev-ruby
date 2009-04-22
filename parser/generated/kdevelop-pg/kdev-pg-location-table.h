/*
  This file is part of kdev-pg
  Copyright 2002-2006 Roberto Raggi <roberto@kdevelop.org>

  Permission to use, copy, modify, distribute, and sell this software and its
  documentation for any purpose is hereby granted without fee, provided that
  the above copyright notice appear in all copies and that both that
  copyright notice and this permission notice appear in supporting
  documentation.

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
  KDEVELOP TEAM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
  AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

//krazy:exclude-all=inline
#ifndef KDEV_PG_LOCATION_TABLE_H
#define KDEV_PG_LOCATION_TABLE_H

#include <algorithm>
#include <cstdlib>
#include <cassert>

struct kdev_pg_location_table
{
  inline kdev_pg_location_table(std::size_t size = 1024)
    : lines(0), line_count(0), current_line(0)
  {
    resize(size);
    lines[current_line++] = 0;
  }

  inline ~kdev_pg_location_table()
  {
    free(lines);
  }

  inline std::size_t size() const
  { return line_count; }

  void resize(std::size_t size)
  {
    assert(size > 0);
    lines = (std::size_t*) ::realloc(lines, sizeof(std::size_t) * size);
    line_count = size;
  }

  /**
   * Returns the \a line and \a column of the given \a offset in this table.
   */
  void position_at(std::size_t offset, size_t *line, size_t *column) const
  {
    std::size_t idx = 0;
    for( std::size_t i = 0; i < current_line; i++ )
    {
      if( lines[i] > offset )
      {
        idx = i-1;
	break;
      }else if( lines[i] == offset )
      {
        idx = i;
        break;
      }

    }

    *line = idx;
    *column = offset - lines[idx];
  }

  /**
   * Marks an \a offset as the character before the first one in the next line.
   * The position_at() function relies on newline() being called properly.
   */
  inline void newline(std::size_t offset)
  {
    if (current_line == line_count)
      resize(current_line * 2);

    lines[current_line++] = offset+1;
  }

  inline std::size_t &operator[](int index)
  { return lines[index]; }

private:
  /// An array of input buffer offsets
  std::size_t *lines;
  /// The size of the allocated array
  std::size_t line_count;
  /// The index to the next index in the lines array
  std::size_t current_line;

private:
  kdev_pg_location_table(kdev_pg_location_table const &other);
  void operator=(kdev_pg_location_table const &other);
};


#endif // KDEV_PG_LOCATION_TABLE_H

