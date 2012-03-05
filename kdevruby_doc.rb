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


##
# Re-open the RDoc::RDoc class in order to re-implement some key methods.
class RDoc::RDoc
  ##
  # Constructor. Just call super and create a dummy value for @options.
  def initialize
    super
    @options = RDoc::Options.new
  end

  ##
  # Re-implemented from RDoc::RDoc. Parse the files from the given +directory+.
  def parse_files(directory)
    files = get_files_from directory
    @stats = RDoc::Stats.new files.size, @options.verbosity
    top_levels = []
    files.each { |f| top_levels << parse_file(f) }
  end

  ##
  # Re-implemented from RDoc::RDoc. Given a file +name+, parse it.
  #
  # @return *RDoc::TopLevel* that represents the parsed file.
  def parse_file(name)
    content = IO.read name
    top_level = RDoc::TopLevel.new name
    puts "Parsing: #{top_level.relative_name}"
    parser = RDoc::Parser.for top_level, name, content, @options, @stats
    return unless parser

    parser.scan
    top_level
  end

  private

  ##
  # @internal
  # @return *Array* containing all the files inside the directory +d+.
  def get_files_from(d)
    files = []
    Dir.glob(File.join(d, "*.{c, rb}")).each { |f| files << f if File.file? f }
    files
  end
end

##
# Re-open the File class so we can print the results of the RDoc::TopLevel's
# into files in an easier way.
class File
  ##
  # Print the given +comment+.
  def print_comment(comment)
    return if comment.empty?
    puts '##'
    puts comment.split("\n").each { |c| c.insert(0, '# ') << "\n" }.join
  end

  ##
  # Print the given +hash+ of modules that we can retrieve by
  # calling RDoc::TopLevel#modules_hash.
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

  ##
  # Print the given +hash+ of classes that we can retrieve by
  # calling RDoc::TopLevel#classes_hash.
  def print_classes(hash)
    hash.each do |o|
      next if o.empty?
      o = o.last
      print_comment o.comment
      if o.superclass.nil?
        puts "class #{o.name}"
        o.ancestors.each { |a| puts "include #{a.name}" }
      else
        puts "class #{o.name} < #{o.superclass}"
        (o.ancestors - [o.superclass]).each { |a| puts "include #{a.name}" }
      end
      print_classes o.classes_hash
      print_methods o.methods_hash
      puts "end\n\n"
    end
  end

  ##
  # Print the given +hash+ of methods that we can retrieve by
  # calling RDoc::TopLevel#methods_hash.
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


##
# Here starts the main program


if ARGV.size != 2
  print <<-USAGE
KDevelop Ruby Documentation generator.
Usage:
  ruby_doc source_dir   # source_dir => ruby source code root directory
  USAGE
  exit
end
ruby_dir, ruby_out = ARGV

# Parse all the files contained inside the +ruby_dir+ directory.
doc = RDoc::RDoc.new
puts 'Generating documentation. Please be patient, this may take a while.'
doc.parse_files ruby_dir

# Print everything into the +ruby_out+ file.
output = File.open ruby_out, 'w'
output.print_modules RDoc::TopLevel.modules_hash
output.print_classes RDoc::TopLevel.classes_hash


# Print all the pre-defined global variables.
{
  '$!' => "The exception information message set by 'raise'. ",
  '$@' => 'Array of backtrace of the last exception thrown.',
  '$&' => 'The string matched by the last successful match.',
  '$`' => 'The string to the left  of the last successful match.',
  "$'" => 'The string to the right of the last successful match.',
  '$+' => 'The highest group matched by the last successful match.',
  '$~' => 'The information about the last match in the current scope.',
  '$=' => 'The flag for case insensitive, nil by default.',
  '$/' => 'The input record separator, newline by default.',
  '$\\'=> 'The output record separator for the print and IO#write. Default is nil.',
  '$,' => 'The output field separator for the print and Array#join.',
  '$;' => 'The default separator for String#split.',
  '$.' => 'The current input line number of the last file that was read.',
  '$<' => 'The virtual concatenation file of the files given on command line (or from $stdin if no files were given).',
  '$>' => 'The default output for print, printf. $stdout by default.',
  '$_' => 'The last input line of string by gets or readline.',
  '$0' => 'Contains the name of the script being executed. May be assignable.',
  '$*' => 'Command line arguments given for the script sans args.',
  '$$' => 'The process number of the Ruby running this script.',
  '$?' => 'The status of the last executed child process.',
  '$:' => 'Load path for scripts and binary modules by load or require.',
  '$"' => 'The array contains the module names loaded by require.',
  '$DEBUG' => 'The status of the -d switch.',
  '$FILENAME' =>  'Current input file from $<. Same as $<.filename.',
  '$LOAD_PATH' => 'The alias to the $:.',
  '$stderr' => 'The current standard error output.',
  '$stdin'  => 'The current standard input.',
  '$stdout' => 'The current standard output.',
  '$VERBOSE'=> 'The verbose flag, which is set by the -v switch.',
  '$-0' => 'The alias to $/.',
  '$-a' => 'True if option -a is set. Read-only variable.',
  '$-d' => 'The alias to $DEBUG.',
  '$-F' => 'The alias to $;.',
  '$-i' => 'In in-place-edit mode, this variable holds the extension, otherwise nil.',
  '$-I' => 'The alias to $:.',
  '$-l' => 'True if option -l is set. Read-only variable.',
  '$-p' => 'True if option -p is set. Read-only variable.',
  '$-v' => 'The alias to $VERBOSE.',
  '$-w' => 'True if option -w is set.'
}.each { |k, v| output.puts "# #{v}\n#{k}\n\n" }

# Print all the pre-defined constants.
{
  'TRUE' => 'The typical true value.',
  'FALSE' => 'The false itself.',
  'NIL' => 'The nil itself.',
  'STDIN' => 'The standard input. The default value for $stdin.',
  'STDOUT' => 'The standard output. The default value for $stdout.',
  'STDERR' => 'The standard error output. The default value for $stderr.',
  'ENV' => 'The hash contains current environment variables.',
  'ARGF' => 'The alias to the $<.',
  'ARGV' => 'The alias to the $*.',
  'DATA' => 'The file object of the script, pointing just after __END__.',
  'RUBY_VERSION' => 'The ruby version string (VERSION was deprecated).',
  'RUBY_RELEASE_DATE' => 'The release date string.',
  'RUBY_PLATFORM' => 'The platform identifier.'
}.each { |k, v| output.puts "# #{v}\n#{k}\n\n" }
