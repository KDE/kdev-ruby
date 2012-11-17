##
# This file is part of KDevelop
#
# Copyright (C) 2012 Miquel Sabaté <mikisabate@gmail.com>
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


#!/usr/bin/env ruby


# This script is the responsible of extracting all the info from the Ruby
# source code (MRI) in order to generate a file containing all the builtin
# modules, classes and methods. You should call this script like this:
#
#   $ ruby kdevruby_doc.rb /absolute/path/to/mri builtins.rb
#
# This may take a while, but then you'll get a brand new builtins.rb file
# containing all the Ruby's builtins.
#
# NOTE: Brace yourselves, this script is a complete hack. It re-opens
# RDoc::RDoc and retrieves everything from it with black magic and unicorns.


require 'rdoc/rdoc'


# Re-open the RDoc::RDoc class. This way, we can extract all the info of
# builtin classes, modules and methods. The method to be called is
# RDoc::RDoc#parse_files that, in short parses all the given directory to
# fetch info. After that, you can call the kdev_classes & kdev_modules methods
# in order to retrieve hashes with all the extracted info.
class RDoc::RDoc
  attr_reader :kdev_classes, :kdev_modules

  # Public: Just call super and create a dummy value for @options.
  def initialize
    super
    @options = RDoc::Options.new
    @kdev_classes, @kdev_modules = {}, {}
  end

  # Public: Re-implemented from RDoc::RDoc. Parse all the files from
  # a directory.
  #
  # directory - a String containing the path to the directory.
  def parse_files(directory)
    files = get_files_from directory
    @stats = RDoc::Stats.new files.size, @options.verbosity
    files.each { |f| parse_file(f) }
  end

  # Public: Parse a file.
  #
  # name - a String containing the path to the file to be parsed.
  def parse_file(name)
    content = IO.read name
    top_level = RDoc::TopLevel.new name
    puts "Parsing: #{top_level.relative_name}"
    parser = RDoc::Parser.for top_level, name, content, @options, @stats
    return unless parser

    parser.scan
    @kdev_classes = eclasses(top_level.classes_hash, @kdev_classes)
    @kdev_modules = emodules(top_level.modules_hash, @kdev_modules)
  end

  private

  # Internal: Get the files from the given directory.
  #
  # d - A String containing the given directory.
  #
  # Returns an Array containing all the files inside the given directory.
  def get_files_from(d)
    files = []
    Dir.glob(File.join(d, "*.{c, rb}")).each { |f| files << f if File.file? f }
    files
  end

  # Internal: Extract all the classes from the given parameters.
  #
  # hash    - A Hash containing all the info on classes.
  # initial - A Hash containing calculations from previous calls.
  #
  # Returns a Hash containing the extracted results.
  def eclasses(hash, initial)
    final = initial || {}
    hash.each do |h|
      next if h.empty?
      h = h.last
      who = h.name.to_sym
      element = { comment: h.comment, ancestors: {} }
      ancestors = []
      if h.superclass.nil?
        h.ancestors.each do |a|
          ancestors << (a.is_a? String) ? a.to_sym : a.name.to_sym
        end
      else
        base = (h.superclass.is_a? String) ? h.superclass : h.superclass.name
        element[:superclass] = base.to_sym
        who = (h.name == h.name.downcase) ? h.name.capitalize : h.name
        who = who.to_sym
        (h.ancestors - [h.superclass]).each do |a|
          if a.is_a? String
            ancestors << a.to_sym
          else
            ancestors << a.name.to_sym
          end
        end
      end
      if final.include? who
        final[who] = fmerge(final[who], ancestors, h)
      else
        element[:ancestors] = ancestors || {}
        element[:classes] = eclasses(h.classes_hash, {})
        element[:methods] = emethods(h.methods_hash, {})
        final[who] = element
      end
    end
    final
  end

  # Internal: Extract all the modules from the given parameters.
  #
  # hash    - A Hash containing all the info on modules.
  # initial - A Hash containing calculations from previous calls.
  #
  # Returns a Hash containing the extracted results.
  def emodules(hash, initial)
    final = initial || {}
    hash.each do |h|
      next if h.empty?
      h = h.last
      who = h.name.to_sym
      ancestors = h.ancestors.map { |a| a.name.to_sym }
      if final.include? who
        final[who] = fmerge(final[who], ancestors, h)
      else
        element = { comment: h.comment }
        element[:ancestors] = ancestors
        element[:classes] = eclasses(h.classes_hash, {})
        element[:methods] = emethods(h.methods_hash, {})
        final[who] = element
      end
    end
    final
  end

  # Internal: Extract all the methods from the given parameters.
  #
  # hash    - A Hash containing all the info on methods.
  # initial - A Hash containing calculations from previous calls.
  #
  # Returns a Hash containing the extracted results.
  def emethods(hash, initial)
    final = initial || {}
    hash.each do |m|
      method = m.last
      call_seq = method.call_seq
      unless call_seq.nil?
        call_seq.split(/\n\s*/).each { |k| final = get_method_string(method, k, final) }
      end
    end
    final
  end

  # Internal: Extract all what we can from the call_seq string of a method.
  #
  # method - The method object from RDoc.
  # str    - The call_seq string from the documentation of the method.
  # hash   - A Hash containing calculations from previous calls.
  #
  # Returns a Hash containing the extracted results.
  def get_method_string(method, str, hash)
    final = hash || {}

    # Extract block
    str = str.gsub(/\{(.+)\}/, '')
    block = !$1.nil? ? '&block' : nil
    str = str.gsub(/(\[\s*\])/, '')
    block = nil if !$1.nil?

    # +per_se+ is the signature itself, and +ret+ the expected return type
    arrow = str.include?('=>') ? '=>' : '->'
    per_se, ret = str.split(arrow).map(&:strip)
    return final if per_se.nil?

    # Extract name and arguments of the method
    name, args = per_se.split('(')
    name = name.split('.')
    name = if (name.size > 1)
      name.last
    else
      method.name
    end
    name = filter_name(name).to_sym

    # Method arguments
    args_str = '';
    if args.nil?
      args_str = "(#{block})" unless block.nil?
      if final.include? name
        if final[name][:args].split(',').size < args_str.split(',').size && method.singleton != final[name][:singleton]
          final[name][:args] = args_str
        end
      else
        final[name] = { comment: method.comment, args: args_str, singleton: method.singleton }
      end
    else
      # Separate between normal parameters and optional parameters ...
      args = args.chop.gsub(/\[(.+)\]/, '')
      opts = $1.scan(/\w+/) unless $1.nil?

      # ... and join them again but now with the proper format.
      res = ''
      if args.empty?
        res = opts.join('=0, ') + '=0' unless opts.nil?
      else
        res = args.gsub(/nil/, 'null')
        res += ', ' + opts.join('=0, ') + '=0' unless opts.nil?
      end
      res = strip_reserved(res)
      res = fix_typos(res)
      if res.include?('arg*more')
        args_str = "(#{block})"
      elsif res =~ /\+|\*/
        args_str = '()'
      else
        res.gsub!('  , string=0', 'string=0')
        res.gsub!(/filename=$/, "filename=''")
        args_str = block.nil? ? "(#{res})" : "(#{res}, #{block})"
      end

      if final.include? name
        if final[name][:args].split(',').size < args_str.split(',').size && method.singleton != final[name][:singleton]
          final[name][:args] = args_str
        end
      else
        final[name] = { comment: method.comment, args: args_str, singleton: method.singleton }
      end
    end
    final
  end

  # Internal: Force merge. Forces the merge of internal hashes.
  #
  # element   - The element to be updated.
  # ancestors - The ancestors of the given element.
  # h         - The RDoc object of the Class/Module.
  #
  # Returns the same element but with some entries updated.
  def fmerge(element, ancestors, h)
    if element[:ancestors].nil?
      element[:ancestors] = ancestors
    else
      element[:ancestors] |= (ancestors)
    end
    if element[:classes].nil?
      element[:classes] = eclasses(h.classes_hash, element[:classes])
    else
      element[:classes].merge!(eclasses(h.classes_hash, element[:classes]))
    end
    if element[:methods].nil?
      element[:methods] = emethods(h.methods_hash, element[:methods])
    else
      element[:methods].merge!(emethods(h.methods_hash, element[:methods]))
    end
    element
  end

  # Internal: The following are some methods to clean typos
  # from Ruby's documentation.
  #
  # Clean the given name.
  #
  # name - A String containing the name to clean.
  def filter_name(name)
    name = name.gsub(/(\w+) = (\w+)/) { "#{$1}= #{$2}" }
    name.gsub!('enc or nil', 'enc_or_nil')
    name.gsub!('proc_obj or nil', 'proc_or_nil')
    name = '[]' if name == ']' or name == ' ] ]' or name == '] ]' or name == ' ]'
    name
  end

  # Internal: Fix random typos from the documentation by hand.
  #
  # res - A String containing the documentation to clean.
  def fix_typos(res)
    res.gsub!(/,\s*,/, ',')
    res.gsub!('"ext_enc:int_enc"', 'enc')
    res.gsub!('"root"', 'root')
    res.gsub!(/\w*: \w*/, 'random')
    res.gsub!(/\.\.\.?/, '*more') # arg1, ...  =>  arg1, *more
    res.gsub!(/\+|\*/, '*more')
    res
  end

  # Internal: Clean the given string from reserved words.
  #
  # str - The given string.
  def strip_reserved(str)
    str = str.gsub(/module/, 'modul').gsub(/class/, 'klass')
    str.gsub(/end/, '_end').gsub(/begin/, '_begin')
  end
end

# Re-open the File class so we can print the results of the RDoc::TopLevel's
# hashes into files in an easier way.
class File
  # Public: Print a comment.
  #
  # comment - A String containing the comment.
  def print_comment(comment)
    return if comment.empty?
    puts '##'
    puts comment.split("\n").each { |c| c.insert(0, '# ') << "\n" }.join
  end

  # Public: Print all the modules.
  #
  # hash - A Hash containing all the info of all the modules.
  def print_modules(hash)
    hash.each do |k, v|
      print_comment v[:comment]
      puts "module #{k}"
      v[:ancestors].each { |m| puts "include #{m}" unless m.empty? }
      print_classes v[:classes]
      print_methods v[:methods]
      puts "end\n\n"
    end
  end

  # Public: Print all the classes.
  #
  # hash - A Hash containing all the info of all the classes.
  def print_classes(hash)
    hash.each do |k, v|
      print_comment v[:comment]
      if v[:superclass].nil?
        puts "class #{k}"
      else
        puts "class #{k} < #{v[:superclass]}"
      end
      v[:ancestors].each { |m| puts "include #{m}" unless m.empty? }
      print_classes v[:classes]
      print_methods v[:methods]
      puts "end\n\n"
    end
  end

  # Public: Print all the methods.
  #
  # hash - A Hash containing all the info of all the methods.
  def print_methods(hash)
    hash.each do |k, v|
      print_comment v[:comment]
      if v[:singleton]
        print "def self.#{k}"
      else
        print "def #{k}"
      end
      print v[:args]
      puts "; end\n"
    end
  end
end


##
# Here starts the main program


if ARGV.size != 2
  print <<-USAGE
KDevelop Ruby Documentation generator.
Usage:
  ruby kdevruby_doc.rb source_dir output_file
  USAGE
  exit
end
ruby_dir, ruby_out = ARGV

# Parse all the files contained inside the +ruby_dir+ directory.
doc = RDoc::RDoc.new
puts 'Generating documentation. Please be patient, this may take a while.'
doc.parse_files ruby_dir

# Print everything into the +ruby_out+ file.
output = File.open(ruby_out, 'w')
ruby_version = File.open("#{ruby_dir}/version.h", &:readline)
ruby_version.match(/\"(.+)\"/)
output.puts <<HEADER
##
# Ruby Version: #{$1}
# This file is generated, all changes made in this file will be lost!\n\n
HEADER
output.print_modules doc.kdev_modules
output.print_classes doc.kdev_classes


# Print all the pre-defined global variables.
{
  '$! = Exception.new' => "The exception information message set by 'raise'. ",
  "$@ = ['']" => 'Array of backtrace of the last exception thrown.',
  "$& = ''" => 'The string matched by the last successful match.',
  "$` = ''" => 'The string to the left  of the last successful match.',
  "$' = ''" => 'The string to the right of the last successful match.',
  "$+ = ''" => 'The highest group matched by the last successful match.',
  '$~ = MatchData.new' => 'The information about the last match in the current scope.',
  '$= = true || false' => 'The flag for case insensitive, nil by default.',
  "$/ = ''" => 'The input record separator, newline by default.',
  "$\\ = ''"=> 'The output record separator for the print and IO#write. Default is nil.',
  "$, = ''" => 'The output field separator for the print and Array#join.',
  "$; = ''" => 'The default separator for String#split.',
  '$. = 0' => 'The current input line number of the last file that was read.',
  '$< = IO.new' => 'The virtual concatenation file of the files given on command line (or from $stdin if no files were given).',
  '$> = IO.new' => 'The default output for print, printf. $stdout by default.',
  "$_ = ''" => 'The last input line of string by gets or readline.',
  "$0 = ''" => 'Contains the name of the script being executed. May be assignable.',
  "$* = ['']" => 'Command line arguments given for the script sans args.',
  '$$ = 0' => 'The process number of the Ruby running this script.',
  '$? = 0' => 'The status of the last executed child process.',
  "$: = ['']" => 'Load path for scripts and binary modules by load or require.',
  "$\" = ['']" => 'The array contains the module names loaded by require.',
  '$DEBUG = true || false' => 'The status of the -d switch.',
  "$FILENAME = ''" =>  'Current input file from $<. Same as $<.filename.',
  '$LOAD_PATH = $:' => 'The alias to the $:.',
  '$stderr = IO.new' => 'The current standard error output.',
  '$stdin = IO.new'  => 'The current standard input.',
  '$stdout = IO.new' => 'The current standard output.',
  '$VERBOSE = true || false'=> 'The verbose flag, which is set by the -v switch.',
  '$-0 = $/' => 'The alias to $/.',
  '$-a = true || false' => 'True if option -a is set. Read-only variable.',
  '$-d = $DEBUG' => 'The alias to $DEBUG.',
  '$-F = $;' => 'The alias to $;.',
  '$-i = nil' => 'In in-place-edit mode, this variable holds the extension, otherwise nil.',
  '$-I = $:' => 'The alias to $:.',
  '$-l = true || false' => 'True if option -l is set. Read-only variable.',
  '$-p = true || false' => 'True if option -p is set. Read-only variable.',
  '$-v = $VERBOSE' => 'The alias to $VERBOSE.',
  '$-w = true || false' => 'True if option -w is set.'
}.each { |k, v| output.puts "# #{v}\n#{k}\n\n" }

# Print all the pre-defined constants.
{
  'TRUE = true' => 'The typical true value.',
  'FALSE = false' => 'The false itself.',
  'NIL = nil' => 'The nil itself.',
  'STDIN = $stdin' => 'The standard input. The default value for $stdin.',
  'STDOUT = $stdout' => 'The standard output. The default value for $stdout.',
  'STDERR = $stderr' => 'The standard error output. The default value for $stderr.',
  "ENV = {''=>''}" => 'The hash contains current environment variables.',
  'ARGF = $<' => 'The alias to the $<.',
  'ARGV = $*' => 'The alias to the $*.',
  'DATA = File.new' => 'The file object of the script, pointing just after __END__.',
  "RUBY_VERSION = ''" => 'The ruby version string (VERSION was deprecated).',
  "RUBY_RELEASE_DATE = ''" => 'The release date string.',
  "RUBY_PLATFORM = ''" => 'The platform identifier.'
}.each { |k, v| output.puts "# #{v}\n#{k}\n\n" }
