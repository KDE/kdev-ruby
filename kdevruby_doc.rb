#
# This file is part of KDevelop
# Author:: Copyright (C) 2012  Miquel Sabaté (mikisabate@gmail.com)
# License::
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


require 'rdoc/rdoc'


class KDevRubyDoc < RDoc::RDoc
  def initialize
    super
    @options = RDoc::Options.new
  end

  def parse_files(dir)
    files = get_files_from dir
    @stats = RDoc::Stats.new files.size, @options.verbosity
    top_levels = []
    files.each { |f| top_levels << parse_file(f) }
    top_levels
  end

  def parse_file(filename)
    content = IO.read filename
    top_level = RDoc::TopLevel.new filename
    puts "Parsing: #{top_level.relative_name}"
    parser = RDoc::Parser.for top_level, filename, content, @options, @stats
    return unless parser

    parser.scan
    top_level
  end

  private

  def get_files_from(dir)
    files = []
    Dir.glob(File.join(dir, "*.{c, rb}")).each { |f| files << f if File.file? f }
    files
  end
end

class File
  def print_comment(comment)
    return if comment.empty?
    puts '##'
    puts comment.split("\n").each { |c| c.insert(0, '# ') << "\n" }.join
  end

  def print_modules(hash)
    hash.each do |o|
      next if o.empty?
      o = o.last
      print_comment o.comment
      puts "module #{o.name}"
      o.ancestors.each { |a| puts "include #{a.name}" }
      print_classes o.classes_hash
      print_methods o.methods_hash
      puts "end\n\n"
    end
  end

  def print_classes(hash)
    hash.each do |o|
      next if o.empty?
      o = o.last
      print_comment o.comment
      if o.superclass.nil?
        puts "class #{o.name}"
        o.ancestors.each { |a| puts "include #{a.name}" }
      else
        puts "class #{o.name} < #{o.superclass.name}"
        (o.ancestors - [o.superclass]).each { |a| puts "include #{a.name}" }
      end
      print_classes o.classes_hash
      print_methods o.methods_hash
      puts "end\n\n"
    end
  end

  def print_methods(hash)
    hash.each do |o|
      next if o.empty?
      o = o.last
      print_comment o.comment
      if o.singleton
        puts "def self.#{o.name}; end\n\n"
      else
        puts "def #{o.name}; end\n\n"
      end
    end
  end
end


if ARGV.size != 2
  print <<-USAGE
KDevelop Ruby Documentation generator.
Usage:
  ruby_doc source_dir   # source_dir => ruby source code root directory
  USAGE
  exit
end
ruby_dir, ruby_out = ARGV


doc = KDevRubyDoc.new
puts 'Generating documentation. Please be patient, this may take a while.'
results = doc.parse_files ruby_dir
output = File.open ruby_out, 'w'
results.each do |r|
  unless r.nil?
    output.print_modules(r.modules_hash)
    output.print_classes(r.classes_hash)
    output.print_methods(r.methods_hash)
  end
end



