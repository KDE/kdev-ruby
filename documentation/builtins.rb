##
# Ruby Version: 2.1.0
# This file is generated, all changes made in this file will be lost!


##
# The marshaling library converts collections of Ruby objects into a
# byte stream, allowing them to be stored outside the currently
# active script. This data may subsequently be read and the original
# objects reconstituted.
# 
# Marshaled data has major and minor version numbers stored along
# with the object information. In normal use, marshaling can only
# load data written with the same major version number and an equal
# or lower minor version number. If Ruby's ``verbose'' flag is set
# (normally using -d, -v, -w, or --verbose) the major and minor
# numbers must match exactly. Marshal versioning is independent of
# Ruby's version numbers. You can extract the version by reading the
# first two bytes of marshaled data.
# 
#     str = Marshal.dump("thing")
#     RUBY_VERSION   #=> "1.9.0"
#     str[0].ord     #=> 4
#     str[1].ord     #=> 8
# 
# Some objects cannot be dumped: if the objects to be dumped include
# bindings, procedure or method objects, instances of class IO, or
# singleton objects, a TypeError will be raised.
# 
# If your class has special serialization needs (for example, if you
# want to serialize in some specific format), or if it contains
# objects that would otherwise not be serializable, you can implement
# your own serialization strategy.
# 
# There are two methods of doing this, your object can define either
# marshal_dump and marshal_load or _dump and _load.  marshal_dump will take
# precedence over _dump if both are defined.  marshal_dump may result in
# smaller Marshal strings.
# 
# == Security considerations
# 
# By design, Marshal.load can deserialize almost any class loaded into the
# Ruby process. In many cases this can lead to remote code execution if the
# Marshal data is loaded from an untrusted source.
# 
# As a result, Marshal.load is not suitable as a general purpose serialization
# format and you should never unmarshal user supplied input or other untrusted
# data.
# 
# If you need to deserialize untrusted data, use JSON or another serialization
# format that is only able to load simple, 'primitive' types such as String,
# Array, Hash, etc. Never allow user input to specify arbitrary types to
# deserialize into.
# 
# == marshal_dump and marshal_load
# 
# When dumping an object the method marshal_dump will be called.
# marshal_dump must return a result containing the information necessary for
# marshal_load to reconstitute the object.  The result can be any object.
# 
# When loading an object dumped using marshal_dump the object is first
# allocated then marshal_load is called with the result from marshal_dump.
# marshal_load must recreate the object from the information in the result.
# 
# Example:
# 
#   class MyObj
#     def initialize name, version, data
#       @name    = name
#       @version = version
#       @data    = data
#     end
# 
#     def marshal_dump
#       [@name, @version]
#     end
# 
#     def marshal_load array
#       @name, @version = array
#     end
#   end
# 
# == _dump and _load
# 
# Use _dump and _load when you need to allocate the object you're restoring
# yourself.
# 
# When dumping an object the instance method _dump is called with an Integer
# which indicates the maximum depth of objects to dump (a value of -1 implies
# that you should disable depth checking).  _dump must return a String
# containing the information necessary to reconstitute the object.
# 
# The class method _load should take a String and use it to return an object
# of the same class.
# 
# Example:
# 
#   class MyObj
#     def initialize name, version, data
#       @name    = name
#       @version = version
#       @data    = data
#     end
# 
#     def _dump level
#       [@name, @version].join ':'
#     end
# 
#     def self._load args
#       new(*args.split(':'))
#     end
#   end
# 
# Since Marhsal.dump outputs a string you can have _dump return a Marshal
# string which is Marshal.loaded in _load for complex objects.
module Marshal
##
# Serializes obj and all descendant objects. If anIO is
# specified, the serialized data will be written to it, otherwise the
# data will be returned as a String. If limit is specified, the
# traversal of subobjects will be limited to that depth. If limit is
# negative, no checking of depth will be performed.
# 
#     class Klass
#       def initialize(str)
#         @str = str
#       end
#       def say_hello
#         @str
#       end
#     end
# 
# (produces no output)
# 
#     o = Klass.new("hello\n")
#     data = Marshal.dump(o)
#     obj = Marshal.load(data)
#     obj.say_hello  #=> "hello\n"
# 
# Marshal can't dump following objects:
# * anonymous Class/Module.
# * objects which related to its system (ex: Dir, File::Stat, IO, File, Socket
#   and so on)
# * an instance of MatchData, Data, Method, UnboundMethod, Proc, Thread,
#   ThreadGroup, Continuation
# * objects which defines singleton methods
def self.dump( obj  , limit=-1 , anIO=0); ''; end
##
# Returns the result of converting the serialized data in source into a
# Ruby object (possibly with associated subordinate objects). source
# may be either an instance of IO or an object that responds to
# to_str. If proc is specified, it will be passed each object as it
# is deserialized.
# 
# Never pass untrusted data (including user supplied input) to this method.
# Please see the overview for further details.
def self.load( source  , proc=0); Object.new; end
##
# Returns the result of converting the serialized data in source into a
# Ruby object (possibly with associated subordinate objects). source
# may be either an instance of IO or an object that responds to
# to_str. If proc is specified, it will be passed each object as it
# is deserialized.
# 
# Never pass untrusted data (including user supplied input) to this method.
# Please see the overview for further details.
def self.restore( source  , proc=0); Object.new; end
end

module Kernel
##
# Equivalent to <code>Proc.new</code>.
def proc(&block); Proc.new; end
##
# Equivalent to <code>Proc.new</code>, except the resulting Proc objects
# check the number of parameters passed when called.
def lambda(&block); Proc.new; end
##
# Returns a +Binding+ object, describing the variable and
# method bindings at the point of call. This object can be used when
# calling +eval+ to execute the evaluated command in this
# environment. See also the description of class +Binding+.
# 
#    def get_binding(param)
#      return binding
#    end
#    b = get_binding("hello")
#    eval("param", b)   #=> "hello"
def binding; Binding.new; end
##
# Returns x/y;
# 
#    Rational(1, 2)   #=> (1/2)
#    Rational('1/2')  #=> (1/2)
# 
# Syntax of string form:
# 
#   string form = extra spaces , rational , extra spaces ;
#   rational = [ sign ] , unsigned rational ;
#   unsigned rational = numerator | numerator , "/" , denominator ;
#   numerator = integer part | fractional part | integer part , fractional part ;
#   denominator = digits ;
#   integer part = digits ;
#   fractional part = "." , digits , [ ( "e" | "E" ) , [ sign ] , digits ] ;
#   sign = "-" | "+" ;
#   digits = digit , { digit | "_" , digit } ;
#   digit = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
#   extra spaces = ? \s* ? ;
# 
# See String#to_r.
def Rational(x, y=0); 0; end
##
# Seeds the system pseudo-random number generator, Random::DEFAULT, with
# +number+.  The previous seed value is returned.
# 
# If +number+ is omitted, seeds the generator using a source of entropy
# provided by the operating system, if available (/dev/urandom on Unix systems
# or the RSA cryptographic provider on Windows), which is then combined with
# the time, the process id, and a sequence number.
# 
# srand may be used to ensure repeatable sequences of pseudo-random numbers
# between different runs of the program. By setting the seed to a known value,
# programs can be made deterministic during testing.
# 
#   srand 1234               # => 268519324636777531569100071560086917274
#   [ rand, rand ]           # => [0.1915194503788923, 0.6221087710398319]
#   [ rand(10), rand(1000) ] # => [4, 664]
#   srand 1234               # => 1234
#   [ rand, rand ]           # => [0.1915194503788923, 0.6221087710398319]
def srand(number = Random.new_seed); 1; end
##
# If called without an argument, or if <tt>max.to_i.abs == 0</tt>, rand
# returns a pseudo-random floating point number between 0.0 and 1.0,
# including 0.0 and excluding 1.0.
# 
#   rand        #=> 0.2725926052826416
# 
# When +max.abs+ is greater than or equal to 1, +rand+ returns a pseudo-random
# integer greater than or equal to 0 and less than +max.to_i.abs+.
# 
#   rand(100)   #=> 12
# 
# When +max+ is a Range, +rand+ returns a random number where
# range.member?(number) == true.
# 
# Negative or floating point values for +max+ are allowed, but may give
# surprising results.
# 
#   rand(-100) # => 87
#   rand(-0.5) # => 0.8130921818028143
#   rand(1.9)  # equivalent to rand(1), which is always 0
# 
# Kernel.srand may be used to ensure that sequences of random numbers are
# reproducible between different runs of a program.
# 
# See also Random.rand.
def rand(max=0); 0; end
##
# Evaluates the Ruby expression(s) in <em>string</em>. If
# <em>binding</em> is given, which must be a <code>Binding</code>
# object, the evaluation is performed in its context. If the
# optional <em>filename</em> and <em>lineno</em> parameters are
# present, they will be used when reporting syntax errors.
# 
#    def get_binding(str)
#      return binding
#    end
#    str = "hello"
#    eval "str + ' Fred'"                      #=> "hello Fred"
#    eval "str + ' Fred'", get_binding("bye")  #=> "bye Fred"
def eval(string , binding=0, filename=0, lineno=0); Object.new; end
##
# Returns the names of the current local variables.
# 
#    fred = 1
#    for i in 1..10
#       # ...
#    end
#    local_variables   #=> [:fred, :i]
def local_variables; []; end
##
# Returns <code>true</code> if <code>yield</code> would execute a
# block in the current context. The <code>iterator?</code> form
# is mildly deprecated.
# 
#    def try
#      if block_given?
#        yield
#      else
#        "no block"
#      end
#    end
#    try                  #=> "no block"
#    try { "hello" }      #=> "hello"
#    try do "hello" end   #=> "hello"
def iterator?; true || false; end
##
# Returns <code>true</code> if <code>yield</code> would execute a
# block in the current context. The <code>iterator?</code> form
# is mildly deprecated.
# 
#    def try
#      if block_given?
#        yield
#      else
#        "no block"
#      end
#    end
#    try                  #=> "no block"
#    try { "hello" }      #=> "hello"
#    try do "hello" end   #=> "hello"
def block_given?; true || false; end
##
# +catch+ executes its block. If a +throw+ is
# executed, Ruby searches up its stack for a +catch+ block
# with a tag corresponding to the +throw+'s
# _tag_. If found, that block is terminated, and
# +catch+ returns the value given to +throw+. If
# +throw+ is not called, the block terminates normally, and
# the value of +catch+ is the value of the last expression
# evaluated. +catch+ expressions may be nested, and the
# +throw+ call need not be in lexical scope.
# 
#    def routine(n)
#      puts n
#      throw :done if n <= 0
#      routine(n-1)
#    end
# 
#    catch(:done) { routine(3) }
# 
# <em>produces:</em>
# 
#    3
#    2
#    1
#    0
# 
# when _arg_ is given, +catch+ yields it as is, or when no
# _arg_ is given, +catch+ assigns a new unique object to
# +throw+.  this is useful for nested +catch+.  _arg_ can
# be an arbitrary object, not only Symbol.
def catch(arg=0, &block); Object.new; end
##
# Transfers control to the end of the active +catch+ block
# waiting for _tag_. Raises +ArgumentError+ if there
# is no +catch+ block for the _tag_. The optional second
# parameter supplies a return value for the +catch+ block,
# which otherwise defaults to +nil+. For examples, see
# <code>Kernel::catch</code>.
def throw(tag , obj=0); end
##
# Repeatedly executes the block.
# 
# If no block is given, an enumerator is returned instead.
# 
#    loop do
#      print "Input: "
#      line = gets
#      break if !line or line =~ /^qQ/
#      # ...
#    end
# 
# StopIteration raised in the block breaks the loop.
def loop(&block); Enumerator.new; end
##
# Equivalent to <code>$_.sub(<i>args</i>)</code>, except that
# <code>$_</code> will be updated if substitution occurs.
# Available only when -p/-n command line option specified.
def sub(pattern, replacement); $_; end
##
# Equivalent to <code>$_.gsub...</code>, except that <code>$_</code>
# receives the modified result.
# Available only when -p/-n command line option specified.
def gsub(pattern, replacement); ''; end
##
# Equivalent to <code>($_.dup).chop!</code>, except <code>nil</code>
# is never returned. See <code>String#chop!</code>.
# Available only when -p/-n command line option specified.
def chop; ''; end
##
# Equivalent to <code>$_ = $_.chomp(<em>string</em>)</code>. See
# <code>String#chomp</code>.
# Available only when -p/-n command line option specified.
def chomp; $_; end
##
# With no arguments, raises the exception in <code>$!</code> or raises
# a <code>RuntimeError</code> if <code>$!</code> is +nil+.
# With a single +String+ argument, raises a
# +RuntimeError+ with the string as a message. Otherwise,
# the first parameter should be the name of an +Exception+
# class (or an object that returns an +Exception+ object when sent
# an +exception+ message). The optional second parameter sets the
# message associated with the exception, and the third parameter is an
# array of callback information. Exceptions are caught by the
# +rescue+ clause of <code>begin...end</code> blocks.
# 
#    raise "Failed to create socket"
#    raise ArgumentError, "No parameters", caller
def raise; end
##
# With no arguments, raises the exception in <code>$!</code> or raises
# a <code>RuntimeError</code> if <code>$!</code> is +nil+.
# With a single +String+ argument, raises a
# +RuntimeError+ with the string as a message. Otherwise,
# the first parameter should be the name of an +Exception+
# class (or an object that returns an +Exception+ object when sent
# an +exception+ message). The optional second parameter sets the
# message associated with the exception, and the third parameter is an
# array of callback information. Exceptions are caught by the
# +rescue+ clause of <code>begin...end</code> blocks.
# 
#    raise "Failed to create socket"
#    raise ArgumentError, "No parameters", caller
def fail; end
##
# Returns an array of the names of global variables.
# 
#    global_variables.grep /std/   #=> [:$stdin, :$stdout, :$stderr]
def global_variables; []; end
##
# Returns the name of the current method as a Symbol.
# If called outside of a method, it returns <code>nil</code>.
def __method__; :a; end
##
# Returns the canonicalized absolute path of the directory of the file from
# which this method is called. It means symlinks in the path is resolved.
# If <code>__FILE__</code> is <code>nil</code>, it returns <code>nil</code>.
# The return value equals to <code>File.dirname(File.realpath(__FILE__))</code>.
def __dir__; ''; end
##
# Controls tracing of assignments to global variables. The parameter
# +symbol_ identifies the variable (as either a string name or a
# symbol identifier). _cmd_ (which may be a string or a
# +Proc+ object) or block is executed whenever the variable
# is assigned. The block or +Proc+ object receives the
# variable's new value as a parameter. Also see
# <code>Kernel::untrace_var</code>.
# 
#    trace_var :$_, proc {|v| puts "$_ is now '#{v}'" }
#    $_ = "hello"
#    $_ = ' there'
# 
# <em>produces:</em>
# 
#    $_ is now 'hello'
#    $_ is now ' there'
def trace_var(symbol, cmd ); end
##
# Removes tracing for the specified command on the given global
# variable and returns +nil+. If no command is specified,
# removes all tracing for that variable and returns an array
# containing the commands actually removed.
def untrace_var(symbol  , cmd=0); [] || nil; end
##
# Displays each of the given messages followed by a record separator on
# STDERR unless warnings have been disabled (for example with the
# <code>-W0</code> flag).
# 
#    warn("warning 1", "warning 2")
# 
#  <em>produces:</em>
# 
#    warning 1
#    warning 2
def warn(); end
##
# Returns the current execution stack---an array containing strings in
# the form <code>file:line</code> or <code>file:line: in
# `method'</code>.
# 
# The optional _start_ parameter determines the number of initial stack
# entries to omit from the top of the stack.
# 
# A second optional +length+ parameter can be used to limit how many entries
# are returned from the stack.
# 
# Returns +nil+ if _start_ is greater than the size of
# current execution stack.
# 
# Optionally you can pass a range, which will return an array containing the
# entries within the specified range.
# 
#    def a(skip)
#      caller(skip)
#    end
#    def b(skip)
#      a(skip)
#    end
#    def c(skip)
#      b(skip)
#    end
#    c(0)   #=> ["prog:2:in `a'", "prog:5:in `b'", "prog:8:in `c'", "prog:10:in `<main>'"]
#    c(1)   #=> ["prog:5:in `b'", "prog:8:in `c'", "prog:11:in `<main>'"]
#    c(2)   #=> ["prog:8:in `c'", "prog:12:in `<main>'"]
#    c(3)   #=> ["prog:13:in `<main>'"]
#    c(4)   #=> []
#    c(5)   #=> nil
def caller(start=1, length=null); [] || nil; end
##
# Returns the current execution stack---an array containing
# backtrace location objects.
# 
# See Thread::Backtrace::Location for more information.
# 
# The optional _start_ parameter determines the number of initial stack
# entries to omit from the top of the stack.
# 
# A second optional +length+ parameter can be used to limit how many entries
# are returned from the stack.
# 
# Returns +nil+ if _start_ is greater than the size of
# current execution stack.
# 
# Optionally you can pass a range, which will return an array containing the
# entries within the specified range.
def caller_locations(start=1, length=null); [] || nil; end
##
# Uses the integer +int_cmd+ to perform various tests on +file1+ (first
# table below) or on +file1+ and +file2+ (second table).
# 
# File tests on a single file:
# 
#   Test   Returns   Meaning
#   "A"  | Time    | Last access time for file1
#   "b"  | boolean | True if file1 is a block device
#   "c"  | boolean | True if file1 is a character device
#   "C"  | Time    | Last change time for file1
#   "d"  | boolean | True if file1 exists and is a directory
#   "e"  | boolean | True if file1 exists
#   "f"  | boolean | True if file1 exists and is a regular file
#   "g"  | boolean | True if file1 has the \CF{setgid} bit
#        |         | set (false under NT)
#   "G"  | boolean | True if file1 exists and has a group
#        |         | ownership equal to the caller's group
#   "k"  | boolean | True if file1 exists and has the sticky bit set
#   "l"  | boolean | True if file1 exists and is a symbolic link
#   "M"  | Time    | Last modification time for file1
#   "o"  | boolean | True if file1 exists and is owned by
#        |         | the caller's effective uid
#   "O"  | boolean | True if file1 exists and is owned by
#        |         | the caller's real uid
#   "p"  | boolean | True if file1 exists and is a fifo
#   "r"  | boolean | True if file1 is readable by the effective
#        |         | uid/gid of the caller
#   "R"  | boolean | True if file is readable by the real
#        |         | uid/gid of the caller
#   "s"  | int/nil | If file1 has nonzero size, return the size,
#        |         | otherwise return nil
#   "S"  | boolean | True if file1 exists and is a socket
#   "u"  | boolean | True if file1 has the setuid bit set
#   "w"  | boolean | True if file1 exists and is writable by
#        |         | the effective uid/gid
#   "W"  | boolean | True if file1 exists and is writable by
#        |         | the real uid/gid
#   "x"  | boolean | True if file1 exists and is executable by
#        |         | the effective uid/gid
#   "X"  | boolean | True if file1 exists and is executable by
#        |         | the real uid/gid
#   "z"  | boolean | True if file1 exists and has a zero length
# 
# Tests that take two files:
# 
#   "-"  | boolean | True if file1 and file2 are identical
#   "="  | boolean | True if the modification times of file1
#        |         | and file2 are equal
#   "<"  | boolean | True if the modification time of file1
#        |         | is prior to that of file2
#   ">"  | boolean | True if the modification time of file1
#        |         | is after that of file2
def test(int_cmd, file1  , file2=0); Object.new; end
##
# Establishes _proc_ as the handler for tracing, or disables
# tracing if the parameter is +nil+.
# 
# *Note:* this method is obsolete, please use TracePoint instead.
# 
# _proc_ takes up to six parameters:
# 
# *   an event name
# *   a filename
# *   a line number
# *   an object id
# *   a binding
# *   the name of a class
# 
# _proc_ is invoked whenever an event occurs.
# 
# Events are:
# 
# +c-call+:: call a C-language routine
# +c-return+:: return from a C-language routine
# +call+:: call a Ruby method
# +class+:: start a class or module definition),
# +end+:: finish a class or module definition),
# +line+:: execute code on a new line
# +raise+:: raise an exception
# +return+:: return from a Ruby method
# 
# Tracing is disabled within the context of _proc_.
# 
#     class Test
#     def test
#       a = 1
#       b = 2
#     end
#     end
# 
#     set_trace_func proc { |event, file, line, id, binding, classname|
#        printf "%8s %s:%-2d %10s %8s\n", event, file, line, id, classname
#     }
#     t = Test.new
#     t.test
# 
#       line prog.rb:11               false
#     c-call prog.rb:11        new    Class
#     c-call prog.rb:11 initialize   Object
#   c-return prog.rb:11 initialize   Object
#   c-return prog.rb:11        new    Class
#       line prog.rb:12               false
#       call prog.rb:2        test     Test
#       line prog.rb:3        test     Test
#       line prog.rb:4        test     Test
#     return prog.rb:4        test     Test
def set_trace_func(proc); end
##
# Replaces the current process by running the given external _command_.
# _command..._ is one of following forms.
# 
#   commandline                 : command line string which is passed to the standard shell
#   cmdname, arg1, ...          : command name and one or more arguments (no shell)
#   [cmdname, argv0], arg1, ... : command name, argv[0] and zero or more arguments (no shell)
# 
# If single string is given as the command,
# it is taken as a command line that is subject to shell expansion before being executed.
# 
# The standard shell means always <code>"/bin/sh"</code> on Unix-like systems,
# <code>ENV["RUBYSHELL"]</code> or <code>ENV["COMSPEC"]</code> on Windows NT series, and
# similar.
# 
# If two or more +string+ given,
# the first is taken as a command name and
# the rest are passed as parameters to command with no shell expansion.
# 
# If a two-element array at the beginning of the command,
# the first element is the command to be executed,
# and the second argument is used as the <code>argv[0]</code> value,
# which may show up in process listings.
# 
# In order to execute the command, one of the <code>exec(2)</code>
# system calls is used, so the running command may inherit some of the environment
# of the original program (including open file descriptors).
# This behavior is modified by env and options.
# See <code>spawn</code> for details.
# 
# Raises SystemCallError if the command couldn't execute (typically
# <code>Errno::ENOENT</code> when it was not found).
# 
# This method modifies process attributes according to _options_
# (details described in <code>spawn</code>)
# before <code>exec(2)</code> system call.
# The modified attributes may be retained when <code>exec(2)</code> system call fails.
# For example, hard resource limits is not restorable.
# If it is not acceptable, consider to create a child process using <code>spawn</code> or <code>system</code>.
# 
#    exec "echo *"       # echoes list of files in current directory
#    # never get here
# 
#    exec "echo", "*"    # echoes an asterisk
#    # never get here
def exec(env=0, command=0, options=0); end
##
# Creates a subprocess. If a block is specified, that block is run
# in the subprocess, and the subprocess terminates with a status of
# zero. Otherwise, the +fork+ call returns twice, once in
# the parent, returning the process ID of the child, and once in
# the child, returning _nil_. The child process can exit using
# <code>Kernel.exit!</code> to avoid running any
# <code>at_exit</code> functions. The parent process should
# use <code>Process.wait</code> to collect the termination statuses
# of its children or use <code>Process.detach</code> to register
# disinterest in their status; otherwise, the operating system
# may accumulate zombie processes.
# 
# The thread calling fork is the only thread in the created child process.
# fork doesn't copy other threads.
# 
# If fork is not usable, Process.respond_to?(:fork) returns false.
def fork; 1 || nil; end
##
# Exits the process immediately. No exit handlers are
# run. <em>status</em> is returned to the underlying system as the
# exit status.
# 
#    Process.exit!(true)
def exit!(status=false); end
##
# Executes _command..._ in a subshell.
# _command..._ is one of following forms.
# 
#   commandline                 : command line string which is passed to the standard shell
#   cmdname, arg1, ...          : command name and one or more arguments (no shell)
#   [cmdname, argv0], arg1, ... : command name, argv[0] and zero or more arguments (no shell)
# 
# system returns +true+ if the command gives zero exit status,
# +false+ for non zero exit status.
# Returns +nil+ if command execution fails.
# An error status is available in <code>$?</code>.
# The arguments are processed in the same way as
# for <code>Kernel.spawn</code>.
# 
# The hash arguments, env and options, are same as
# <code>exec</code> and <code>spawn</code>.
# See <code>Kernel.spawn</code> for details.
# 
#    system("echo *")
#    system("echo", "*")
# 
# <em>produces:</em>
# 
#    config.h main.rb
#    *
# 
# See <code>Kernel.exec</code> for the standard shell.
def system(env=0, command=0, options=0); true || false || nil; end
##
# spawn executes specified command and return its pid.
# 
# This method doesn't wait for end of the command.
# The parent process should
# use <code>Process.wait</code> to collect
# the termination status of its child or
# use <code>Process.detach</code> to register
# disinterest in their status;
# otherwise, the operating system may accumulate zombie processes.
# 
# spawn has bunch of options to specify process attributes:
# 
#   env: hash
#     name => val : set the environment variable
#     name => nil : unset the environment variable
#   command...:
#     commandline                 : command line string which is passed to the standard shell
#     cmdname, arg1, ...          : command name and one or more arguments (no shell)
#     [cmdname, argv0], arg1, ... : command name, argv[0] and zero or more arguments (no shell)
#   options: hash
#     clearing environment variables:
#       :unsetenv_others => true   : clear environment variables except specified by env
#       :unsetenv_others => false  : don't clear (default)
#     process group:
#       :pgroup => true or 0 : make a new process group
#       :pgroup => pgid      : join to specified process group
#       :pgroup => nil       : don't change the process group (default)
#     create new process group: Windows only
#       :new_pgroup => true  : the new process is the root process of a new process group
#       :new_pgroup => false : don't create a new process group (default)
#     resource limit: resourcename is core, cpu, data, etc.  See Process.setrlimit.
#       :rlimit_resourcename => limit
#       :rlimit_resourcename => [cur_limit, max_limit]
#     umask:
#       :umask => int
#     redirection:
#       key:
#         FD              : single file descriptor in child process
#         [FD, FD, ...]   : multiple file descriptor in child process
#       value:
#         FD                        : redirect to the file descriptor in parent process
#         string                    : redirect to file with open(string, "r" or "w")
#         [string]                  : redirect to file with open(string, File::RDONLY)
#         [string, open_mode]       : redirect to file with open(string, open_mode, 0644)
#         [string, open_mode, perm] : redirect to file with open(string, open_mode, perm)
#         [:child, FD]              : redirect to the redirected file descriptor
#         :close                    : close the file descriptor in child process
#       FD is one of follows
#         :in     : the file descriptor 0 which is the standard input
#         :out    : the file descriptor 1 which is the standard output
#         :err    : the file descriptor 2 which is the standard error
#         integer : the file descriptor of specified the integer
#         io      : the file descriptor specified as io.fileno
#     file descriptor inheritance: close non-redirected non-standard fds (3, 4, 5, ...) or not
#       :close_others => true  : don't inherit
#     current directory:
#       :chdir => str
# 
# If a hash is given as +env+, the environment is
# updated by +env+ before <code>exec(2)</code> in the child process.
# If a pair in +env+ has nil as the value, the variable is deleted.
# 
#   # set FOO as BAR and unset BAZ.
#   pid = spawn({"FOO"=>"BAR", "BAZ"=>nil}, command)
# 
# If a hash is given as +options+,
# it specifies
# process group,
# create new process group,
# resource limit,
# current directory,
# umask and
# redirects for the child process.
# Also, it can be specified to clear environment variables.
# 
# The <code>:unsetenv_others</code> key in +options+ specifies
# to clear environment variables, other than specified by +env+.
# 
#   pid = spawn(command, :unsetenv_others=>true) # no environment variable
#   pid = spawn({"FOO"=>"BAR"}, command, :unsetenv_others=>true) # FOO only
# 
# The <code>:pgroup</code> key in +options+ specifies a process group.
# The corresponding value should be true, zero or positive integer.
# true and zero means the process should be a process leader of a new
# process group.
# Other values specifies a process group to be belongs.
# 
#   pid = spawn(command, :pgroup=>true) # process leader
#   pid = spawn(command, :pgroup=>10) # belongs to the process group 10
# 
# The <code>:new_pgroup</code> key in +options+ specifies to pass
# +CREATE_NEW_PROCESS_GROUP+ flag to <code>CreateProcessW()</code> that is
# Windows API. This option is only for Windows.
# true means the new process is the root process of the new process group.
# The new process has CTRL+C disabled. This flag is necessary for
# <code>Process.kill(:SIGINT, pid)</code> on the subprocess.
# :new_pgroup is false by default.
# 
#   pid = spawn(command, :new_pgroup=>true)  # new process group
#   pid = spawn(command, :new_pgroup=>false) # same process group
# 
# The <code>:rlimit_</code><em>foo</em> key specifies a resource limit.
# <em>foo</em> should be one of resource types such as <code>core</code>.
# The corresponding value should be an integer or an array which have one or
# two integers: same as cur_limit and max_limit arguments for
# Process.setrlimit.
# 
#   cur, max = Process.getrlimit(:CORE)
#   pid = spawn(command, :rlimit_core=>[0,max]) # disable core temporary.
#   pid = spawn(command, :rlimit_core=>max) # enable core dump
#   pid = spawn(command, :rlimit_core=>0) # never dump core.
# 
# The <code>:umask</code> key in +options+ specifies the umask.
# 
#   pid = spawn(command, :umask=>077)
# 
# The :in, :out, :err, a fixnum, an IO and an array key specifies a redirection.
# The redirection maps a file descriptor in the child process.
# 
# For example, stderr can be merged into stdout as follows:
# 
#   pid = spawn(command, :err=>:out)
#   pid = spawn(command, 2=>1)
#   pid = spawn(command, STDERR=>:out)
#   pid = spawn(command, STDERR=>STDOUT)
# 
# The hash keys specifies a file descriptor
# in the child process started by <code>spawn</code>.
# :err, 2 and STDERR specifies the standard error stream (stderr).
# 
# The hash values specifies a file descriptor
# in the parent process which invokes <code>spawn</code>.
# :out, 1 and STDOUT specifies the standard output stream (stdout).
# 
# In the above example,
# the standard output in the child process is not specified.
# So it is inherited from the parent process.
# 
# The standard input stream (stdin) can be specified by :in, 0 and STDIN.
# 
# A filename can be specified as a hash value.
# 
#   pid = spawn(command, :in=>"/dev/null") # read mode
#   pid = spawn(command, :out=>"/dev/null") # write mode
#   pid = spawn(command, :err=>"log") # write mode
#   pid = spawn(command, 3=>"/dev/null") # read mode
# 
# For stdout and stderr,
# it is opened in write mode.
# Otherwise read mode is used.
# 
# For specifying flags and permission of file creation explicitly,
# an array is used instead.
# 
#   pid = spawn(command, :in=>["file"]) # read mode is assumed
#   pid = spawn(command, :in=>["file", "r"])
#   pid = spawn(command, :out=>["log", "w"]) # 0644 assumed
#   pid = spawn(command, :out=>["log", "w", 0600])
#   pid = spawn(command, :out=>["log", File::WRONLY|File::EXCL|File::CREAT, 0600])
# 
# The array specifies a filename, flags and permission.
# The flags can be a string or an integer.
# If the flags is omitted or nil, File::RDONLY is assumed.
# The permission should be an integer.
# If the permission is omitted or nil, 0644 is assumed.
# 
# If an array of IOs and integers are specified as a hash key,
# all the elements are redirected.
# 
#   # stdout and stderr is redirected to log file.
#   # The file "log" is opened just once.
#   pid = spawn(command, [:out, :err]=>["log", "w"])
# 
# Another way to merge multiple file descriptors is [:child, fd].
# \[:child, fd] means the file descriptor in the child process.
# This is different from fd.
# For example, :err=>:out means redirecting child stderr to parent stdout.
# But :err=>[:child, :out] means redirecting child stderr to child stdout.
# They differ if stdout is redirected in the child process as follows.
# 
#   # stdout and stderr is redirected to log file.
#   # The file "log" is opened just once.
#   pid = spawn(command, :out=>["log", "w"], :err=>[:child, :out])
# 
# \[:child, :out] can be used to merge stderr into stdout in IO.popen.
# In this case, IO.popen redirects stdout to a pipe in the child process
# and [:child, :out] refers the redirected stdout.
# 
#   io = IO.popen(["sh", "-c", "echo out; echo err >&2", :err=>[:child, :out]])
#   p io.read #=> "out\nerr\n"
# 
# The <code>:chdir</code> key in +options+ specifies the current directory.
# 
#   pid = spawn(command, :chdir=>"/var/tmp")
# 
# spawn closes all non-standard unspecified descriptors by default.
# The "standard" descriptors are 0, 1 and 2.
# This behavior is specified by :close_others option.
# :close_others doesn't affect the standard descriptors which are
# closed only if :close is specified explicitly.
# 
#   pid = spawn(command, :close_others=>true)  # close 3,4,5,... (default)
#   pid = spawn(command, :close_others=>false) # don't close 3,4,5,...
# 
# :close_others is true by default for spawn and IO.popen.
# 
# Note that fds which close-on-exec flag is already set are closed
# regardless of :close_others option.
# 
# So IO.pipe and spawn can be used as IO.popen.
# 
#   # similar to r = IO.popen(command)
#   r, w = IO.pipe
#   pid = spawn(command, :out=>w)   # r, w is closed in the child process.
#   w.close
# 
# :close is specified as a hash value to close a fd individually.
# 
#   f = open(foo)
#   system(command, f=>:close)        # don't inherit f.
# 
# If a file descriptor need to be inherited,
# io=>io can be used.
# 
#   # valgrind has --log-fd option for log destination.
#   # log_w=>log_w indicates log_w.fileno inherits to child process.
#   log_r, log_w = IO.pipe
#   pid = spawn("valgrind", "--log-fd=#{log_w.fileno}", "echo", "a", log_w=>log_w)
#   log_w.close
#   p log_r.read
# 
# It is also possible to exchange file descriptors.
# 
#   pid = spawn(command, :out=>:err, :err=>:out)
# 
# The hash keys specify file descriptors in the child process.
# The hash values specifies file descriptors in the parent process.
# So the above specifies exchanging stdout and stderr.
# Internally, +spawn+ uses an extra file descriptor to resolve such cyclic
# file descriptor mapping.
# 
# See <code>Kernel.exec</code> for the standard shell.
def spawn(env=0, command=0, options=0); 0; end
##
# Suspends the current thread for _duration_ seconds (which may be any number,
# including a +Float+ with fractional seconds). Returns the actual number of
# seconds slept (rounded), which may be less than that asked for if another
# thread calls <code>Thread#run</code>. Called without an argument, sleep()
# will sleep forever.
# 
#    Time.new    #=> 2008-03-08 19:56:19 +0900
#    sleep 1.2   #=> 1
#    Time.new    #=> 2008-03-08 19:56:20 +0900
#    sleep 1.9   #=> 2
#    Time.new    #=> 2008-03-08 19:56:22 +0900
def sleep(duration=0); 0; end
##
# Initiates the termination of the Ruby script by raising the
# <code>SystemExit</code> exception. This exception may be caught. The
# optional parameter is used to return a status code to the invoking
# environment.
# +true+ and +FALSE+ of _status_ means success and failure
# respectively.  The interpretation of other integer values are
# system dependent.
# 
#    begin
#      exit
#      puts "never get here"
#    rescue SystemExit
#      puts "rescued a SystemExit exception"
#    end
#    puts "after begin block"
# 
# <em>produces:</em>
# 
#    rescued a SystemExit exception
#    after begin block
# 
# Just prior to termination, Ruby executes any <code>at_exit</code> functions
# (see Kernel::at_exit) and runs any object finalizers (see
# ObjectSpace::define_finalizer).
# 
#    at_exit { puts "at_exit function" }
#    ObjectSpace.define_finalizer("string",  proc { puts "in finalizer" })
#    exit
# 
# <em>produces:</em>
# 
#    at_exit function
#    in finalizer
def exit(status=true); end
##
# Terminate execution immediately, effectively by calling
# <code>Kernel.exit(false)</code>. If _msg_ is given, it is written
# to STDERR prior to terminating.
def abort; end
##
# Converts _block_ to a +Proc+ object (and therefore
# binds it at the point of call) and registers it for execution when
# the program exits. If multiple handlers are registered, they are
# executed in reverse order of registration.
# 
#    def do_at_exit(str1)
#      at_exit { print str1 }
#    end
#    at_exit { puts "cruel world" }
#    do_at_exit("goodbye ")
#    exit
# 
# <em>produces:</em>
# 
#    goodbye cruel world
def at_exit(&block); Proc.new; end
##
# Loads and executes the Ruby
# program in the file _filename_. If the filename does not
# resolve to an absolute path, the file is searched for in the library
# directories listed in <code>$:</code>. If the optional _wrap_
# parameter is +true+, the loaded script will be executed
# under an anonymous module, protecting the calling program's global
# namespace. In no circumstance will any local variables in the loaded
# file be propagated to the loading environment.
def load(filename, wrap=false); true; end
##
# Loads the given +name+, returning +true+ if successful and +false+ if the
# feature is already loaded.
# 
# If the filename does not resolve to an absolute path, it will be searched
# for in the directories listed in <code>$LOAD_PATH</code> (<code>$:</code>).
# 
# If the filename has the extension ".rb", it is loaded as a source file; if
# the extension is ".so", ".o", or ".dll", or the default shared library
# extension on the current platform, Ruby loads the shared library as a
# Ruby extension.  Otherwise, Ruby tries adding ".rb", ".so", and so on
# to the name until found.  If the file named cannot be found, a LoadError
# will be raised.
# 
# For Ruby extensions the filename given may use any shared library
# extension.  For example, on Linux the socket extension is "socket.so" and
# <code>require 'socket.dll'</code> will load the socket extension.
# 
# The absolute path of the loaded file is added to
# <code>$LOADED_FEATURES</code> (<code>$"</code>).  A file will not be
# loaded again if its path already appears in <code>$"</code>.  For example,
# <code>require 'a'; require './a'</code> will not load <code>a.rb</code>
# again.
# 
#   require "my-library.rb"
#   require "db-driver"
# 
# Any constants or globals within the loaded source file will be available
# in the calling program's global namespace. However, local variables will
# not be propagated to the loading environment.
def require(name); true || false; end
##
# Ruby tries to load the library named _string_ relative to the requiring
# file's path.  If the file's path cannot be determined a LoadError is raised.
# If a file is loaded +true+ is returned and false otherwise.
def require_relative(string); true || false; end
##
# Registers _filename_ to be loaded (using <code>Kernel::require</code>)
# the first time that _module_ (which may be a <code>String</code> or
# a symbol) is accessed.
# 
#    autoload(:MyModule, "/usr/local/lib/modules/my_module.rb")
def autoload(modul, filename); end
##
# Returns _filename_ to be loaded if _name_ is registered as
# +autoload+.
# 
#    autoload(:B, "b")
#    autoload?(:B)            #=> "b"
def autoload?(name); '' || nil; end
##
# Specifies the handling of signals. The first parameter is a signal
# name (a string such as ``SIGALRM'', ``SIGUSR1'', and so on) or a
# signal number. The characters ``SIG'' may be omitted from the
# signal name. The command or block specifies code to be run when the
# signal is raised.
# If the command is the string ``IGNORE'' or ``SIG_IGN'', the signal
# will be ignored.
# If the command is ``DEFAULT'' or ``SIG_DFL'', the Ruby's default handler
# will be invoked.
# If the command is ``EXIT'', the script will be terminated by the signal.
# If the command is ``SYSTEM_DEFAULT'', the operating system's default
# handler will be invoked.
# Otherwise, the given command or block will be run.
# The special signal name ``EXIT'' or signal number zero will be
# invoked just prior to program termination.
# trap returns the previous handler for the given signal.
# 
#     Signal.trap(0, proc { puts "Terminating: #{$$}" })
#     Signal.trap("CLD")  { puts "Child died" }
#     fork && Process.wait
# 
# produces:
#     Terminating: 27461
#     Child died
#     Terminating: 27460
def trap( signal, command ); Object.new; end
##
# Returns the string resulting from applying <i>format_string</i> to
# any additional arguments.  Within the format string, any characters
# other than format sequences are copied to the result.
# 
# The syntax of a format sequence is follows.
# 
#   %[flags][width][.precision]type
# 
# A format
# sequence consists of a percent sign, followed by optional flags,
# width, and precision indicators, then terminated with a field type
# character.  The field type controls how the corresponding
# <code>sprintf</code> argument is to be interpreted, while the flags
# modify that interpretation.
# 
# The field type characters are:
# 
#     Field |  Integer Format
#     ------+--------------------------------------------------------------
#       b   | Convert argument as a binary number.
#           | Negative numbers will be displayed as a two's complement
#           | prefixed with `..1'.
#       B   | Equivalent to `b', but uses an uppercase 0B for prefix
#           | in the alternative format by #.
#       d   | Convert argument as a decimal number.
#       i   | Identical to `d'.
#       o   | Convert argument as an octal number.
#           | Negative numbers will be displayed as a two's complement
#           | prefixed with `..7'.
#       u   | Identical to `d'.
#       x   | Convert argument as a hexadecimal number.
#           | Negative numbers will be displayed as a two's complement
#           | prefixed with `..f' (representing an infinite string of
#           | leading 'ff's).
#       X   | Equivalent to `x', but uses uppercase letters.
# 
#     Field |  Float Format
#     ------+--------------------------------------------------------------
#       e   | Convert floating point argument into exponential notation
#           | with one digit before the decimal point as [-]d.dddddde[+-]dd.
#           | The precision specifies the number of digits after the decimal
#           | point (defaulting to six).
#       E   | Equivalent to `e', but uses an uppercase E to indicate
#           | the exponent.
#       f   | Convert floating point argument as [-]ddd.dddddd,
#           | where the precision specifies the number of digits after
#           | the decimal point.
#       g   | Convert a floating point number using exponential form
#           | if the exponent is less than -4 or greater than or
#           | equal to the precision, or in dd.dddd form otherwise.
#           | The precision specifies the number of significant digits.
#       G   | Equivalent to `g', but use an uppercase `E' in exponent form.
#       a   | Convert floating point argument as [-]0xh.hhhhp[+-]dd,
#           | which is consisted from optional sign, "0x", fraction part
#           | as hexadecimal, "p", and exponential part as decimal.
#       A   | Equivalent to `a', but use uppercase `X' and `P'.
# 
#     Field |  Other Format
#     ------+--------------------------------------------------------------
#       c   | Argument is the numeric code for a single character or
#           | a single character string itself.
#       p   | The valuing of argument.inspect.
#       s   | Argument is a string to be substituted.  If the format
#           | sequence contains a precision, at most that many characters
#           | will be copied.
#       %   | A percent sign itself will be displayed.  No argument taken.
# 
# The flags modifies the behavior of the formats.
# The flag characters are:
# 
#   Flag     | Applies to    | Meaning
#   ---------+---------------+-----------------------------------------
#   space    | bBdiouxX      | Leave a space at the start of
#            | aAeEfgG       | non-negative numbers.
#            | (numeric fmt) | For `o', `x', `X', `b' and `B', use
#            |               | a minus sign with absolute value for
#            |               | negative values.
#   ---------+---------------+-----------------------------------------
#   (digit)$ | all           | Specifies the absolute argument number
#            |               | for this field.  Absolute and relative
#            |               | argument numbers cannot be mixed in a
#            |               | sprintf string.
#   ---------+---------------+-----------------------------------------
#    #       | bBoxX         | Use an alternative format.
#            | aAeEfgG       | For the conversions `o', increase the precision
#            |               | until the first digit will be `0' if
#            |               | it is not formatted as complements.
#            |               | For the conversions `x', `X', `b' and `B'
#            |               | on non-zero, prefix the result with ``0x'',
#            |               | ``0X'', ``0b'' and ``0B'', respectively.
#            |               | For `a', `A', `e', `E', `f', `g', and 'G',
#            |               | force a decimal point to be added,
#            |               | even if no digits follow.
#            |               | For `g' and 'G', do not remove trailing zeros.
#   ---------+---------------+-----------------------------------------
#   +        | bBdiouxX      | Add a leading plus sign to non-negative
#            | aAeEfgG       | numbers.
#            | (numeric fmt) | For `o', `x', `X', `b' and `B', use
#            |               | a minus sign with absolute value for
#            |               | negative values.
#   ---------+---------------+-----------------------------------------
#   -        | all           | Left-justify the result of this conversion.
#   ---------+---------------+-----------------------------------------
#   0 (zero) | bBdiouxX      | Pad with zeros, not spaces.
#            | aAeEfgG       | For `o', `x', `X', `b' and `B', radix-1
#            | (numeric fmt) | is used for negative numbers formatted as
#            |               | complements.
#   ---------+---------------+-----------------------------------------
#   *        | all           | Use the next argument as the field width.
#            |               | If negative, left-justify the result. If the
#            |               | asterisk is followed by a number and a dollar
#            |               | sign, use the indicated argument as the width.
# 
# Examples of flags:
# 
#  # `+' and space flag specifies the sign of non-negative numbers.
#  sprintf("%d", 123)  #=> "123"
#  sprintf("%+d", 123) #=> "+123"
#  sprintf("% d", 123) #=> " 123"
# 
#  # `#' flag for `o' increases number of digits to show `0'.
#  # `+' and space flag changes format of negative numbers.
#  sprintf("%o", 123)   #=> "173"
#  sprintf("%#o", 123)  #=> "0173"
#  sprintf("%+o", -123) #=> "-173"
#  sprintf("%o", -123)  #=> "..7605"
#  sprintf("%#o", -123) #=> "..7605"
# 
#  # `#' flag for `x' add a prefix `0x' for non-zero numbers.
#  # `+' and space flag disables complements for negative numbers.
#  sprintf("%x", 123)   #=> "7b"
#  sprintf("%#x", 123)  #=> "0x7b"
#  sprintf("%+x", -123) #=> "-7b"
#  sprintf("%x", -123)  #=> "..f85"
#  sprintf("%#x", -123) #=> "0x..f85"
#  sprintf("%#x", 0)    #=> "0"
# 
#  # `#' for `X' uses the prefix `0X'.
#  sprintf("%X", 123)  #=> "7B"
#  sprintf("%#X", 123) #=> "0X7B"
# 
#  # `#' flag for `b' add a prefix `0b' for non-zero numbers.
#  # `+' and space flag disables complements for negative numbers.
#  sprintf("%b", 123)   #=> "1111011"
#  sprintf("%#b", 123)  #=> "0b1111011"
#  sprintf("%+b", -123) #=> "-1111011"
#  sprintf("%b", -123)  #=> "..10000101"
#  sprintf("%#b", -123) #=> "0b..10000101"
#  sprintf("%#b", 0)    #=> "0"
# 
#  # `#' for `B' uses the prefix `0B'.
#  sprintf("%B", 123)  #=> "1111011"
#  sprintf("%#B", 123) #=> "0B1111011"
# 
#  # `#' for `e' forces to show the decimal point.
#  sprintf("%.0e", 1)  #=> "1e+00"
#  sprintf("%#.0e", 1) #=> "1.e+00"
# 
#  # `#' for `f' forces to show the decimal point.
#  sprintf("%.0f", 1234)  #=> "1234"
#  sprintf("%#.0f", 1234) #=> "1234."
# 
#  # `#' for `g' forces to show the decimal point.
#  # It also disables stripping lowest zeros.
#  sprintf("%g", 123.4)   #=> "123.4"
#  sprintf("%#g", 123.4)  #=> "123.400"
#  sprintf("%g", 123456)  #=> "123456"
#  sprintf("%#g", 123456) #=> "123456."
# 
# The field width is an optional integer, followed optionally by a
# period and a precision.  The width specifies the minimum number of
# characters that will be written to the result for this field.
# 
# Examples of width:
# 
#  # padding is done by spaces,       width=20
#  # 0 or radix-1.             <------------------>
#  sprintf("%20d", 123)   #=> "                 123"
#  sprintf("%+20d", 123)  #=> "                +123"
#  sprintf("%020d", 123)  #=> "00000000000000000123"
#  sprintf("%+020d", 123) #=> "+0000000000000000123"
#  sprintf("% 020d", 123) #=> " 0000000000000000123"
#  sprintf("%-20d", 123)  #=> "123                 "
#  sprintf("%-+20d", 123) #=> "+123                "
#  sprintf("%- 20d", 123) #=> " 123                "
#  sprintf("%020x", -123) #=> "..ffffffffffffffff85"
# 
# For
# numeric fields, the precision controls the number of decimal places
# displayed.  For string fields, the precision determines the maximum
# number of characters to be copied from the string.  (Thus, the format
# sequence <code>%10.10s</code> will always contribute exactly ten
# characters to the result.)
# 
# Examples of precisions:
# 
#  # precision for `d', 'o', 'x' and 'b' is
#  # minimum number of digits               <------>
#  sprintf("%20.8d", 123)  #=> "            00000123"
#  sprintf("%20.8o", 123)  #=> "            00000173"
#  sprintf("%20.8x", 123)  #=> "            0000007b"
#  sprintf("%20.8b", 123)  #=> "            01111011"
#  sprintf("%20.8d", -123) #=> "           -00000123"
#  sprintf("%20.8o", -123) #=> "            ..777605"
#  sprintf("%20.8x", -123) #=> "            ..ffff85"
#  sprintf("%20.8b", -11)  #=> "            ..110101"
# 
#  # "0x" and "0b" for `#x' and `#b' is not counted for
#  # precision but "0" for `#o' is counted.  <------>
#  sprintf("%#20.8d", 123)  #=> "            00000123"
#  sprintf("%#20.8o", 123)  #=> "            00000173"
#  sprintf("%#20.8x", 123)  #=> "          0x0000007b"
#  sprintf("%#20.8b", 123)  #=> "          0b01111011"
#  sprintf("%#20.8d", -123) #=> "           -00000123"
#  sprintf("%#20.8o", -123) #=> "            ..777605"
#  sprintf("%#20.8x", -123) #=> "          0x..ffff85"
#  sprintf("%#20.8b", -11)  #=> "          0b..110101"
# 
#  # precision for `e' is number of
#  # digits after the decimal point           <------>
#  sprintf("%20.8e", 1234.56789) #=> "      1.23456789e+03"
# 
#  # precision for `f' is number of
#  # digits after the decimal point               <------>
#  sprintf("%20.8f", 1234.56789) #=> "       1234.56789000"
# 
#  # precision for `g' is number of
#  # significant digits                          <------->
#  sprintf("%20.8g", 1234.56789) #=> "           1234.5679"
# 
#  #                                         <------->
#  sprintf("%20.8g", 123456789)  #=> "       1.2345679e+08"
# 
#  # precision for `s' is
#  # maximum number of characters                    <------>
#  sprintf("%20.8s", "string test") #=> "            string t"
# 
# Examples:
# 
#    sprintf("%d %04x", 123, 123)               #=> "123 007b"
#    sprintf("%08b '%4s'", 123, 123)            #=> "01111011 ' 123'"
#    sprintf("%1$*2$s %2$d %1$s", "hello", 8)   #=> "   hello 8 hello"
#    sprintf("%1$*2$s %2$d", "hello", -8)       #=> "hello    -8"
#    sprintf("%+g:% g:%-g", 1.23, 1.23, 1.23)   #=> "+1.23: 1.23:1.23"
#    sprintf("%u", -123)                        #=> "-123"
# 
# For more complex formatting, Ruby supports a reference by name.
# %<name>s style uses format style, but %{name} style doesn't.
# 
# Exapmles:
#   sprintf("%<foo>d : %<bar>f", { :foo => 1, :bar => 2 })
#     #=> 1 : 2.000000
#   sprintf("%{foo}f", { :foo => 1 })
#     # => "1f"
def sprintf(format_string  , arguments=0); ''; end
##
# Returns the string resulting from applying <i>format_string</i> to
# any additional arguments.  Within the format string, any characters
# other than format sequences are copied to the result.
# 
# The syntax of a format sequence is follows.
# 
#   %[flags][width][.precision]type
# 
# A format
# sequence consists of a percent sign, followed by optional flags,
# width, and precision indicators, then terminated with a field type
# character.  The field type controls how the corresponding
# <code>sprintf</code> argument is to be interpreted, while the flags
# modify that interpretation.
# 
# The field type characters are:
# 
#     Field |  Integer Format
#     ------+--------------------------------------------------------------
#       b   | Convert argument as a binary number.
#           | Negative numbers will be displayed as a two's complement
#           | prefixed with `..1'.
#       B   | Equivalent to `b', but uses an uppercase 0B for prefix
#           | in the alternative format by #.
#       d   | Convert argument as a decimal number.
#       i   | Identical to `d'.
#       o   | Convert argument as an octal number.
#           | Negative numbers will be displayed as a two's complement
#           | prefixed with `..7'.
#       u   | Identical to `d'.
#       x   | Convert argument as a hexadecimal number.
#           | Negative numbers will be displayed as a two's complement
#           | prefixed with `..f' (representing an infinite string of
#           | leading 'ff's).
#       X   | Equivalent to `x', but uses uppercase letters.
# 
#     Field |  Float Format
#     ------+--------------------------------------------------------------
#       e   | Convert floating point argument into exponential notation
#           | with one digit before the decimal point as [-]d.dddddde[+-]dd.
#           | The precision specifies the number of digits after the decimal
#           | point (defaulting to six).
#       E   | Equivalent to `e', but uses an uppercase E to indicate
#           | the exponent.
#       f   | Convert floating point argument as [-]ddd.dddddd,
#           | where the precision specifies the number of digits after
#           | the decimal point.
#       g   | Convert a floating point number using exponential form
#           | if the exponent is less than -4 or greater than or
#           | equal to the precision, or in dd.dddd form otherwise.
#           | The precision specifies the number of significant digits.
#       G   | Equivalent to `g', but use an uppercase `E' in exponent form.
#       a   | Convert floating point argument as [-]0xh.hhhhp[+-]dd,
#           | which is consisted from optional sign, "0x", fraction part
#           | as hexadecimal, "p", and exponential part as decimal.
#       A   | Equivalent to `a', but use uppercase `X' and `P'.
# 
#     Field |  Other Format
#     ------+--------------------------------------------------------------
#       c   | Argument is the numeric code for a single character or
#           | a single character string itself.
#       p   | The valuing of argument.inspect.
#       s   | Argument is a string to be substituted.  If the format
#           | sequence contains a precision, at most that many characters
#           | will be copied.
#       %   | A percent sign itself will be displayed.  No argument taken.
# 
# The flags modifies the behavior of the formats.
# The flag characters are:
# 
#   Flag     | Applies to    | Meaning
#   ---------+---------------+-----------------------------------------
#   space    | bBdiouxX      | Leave a space at the start of
#            | aAeEfgG       | non-negative numbers.
#            | (numeric fmt) | For `o', `x', `X', `b' and `B', use
#            |               | a minus sign with absolute value for
#            |               | negative values.
#   ---------+---------------+-----------------------------------------
#   (digit)$ | all           | Specifies the absolute argument number
#            |               | for this field.  Absolute and relative
#            |               | argument numbers cannot be mixed in a
#            |               | sprintf string.
#   ---------+---------------+-----------------------------------------
#    #       | bBoxX         | Use an alternative format.
#            | aAeEfgG       | For the conversions `o', increase the precision
#            |               | until the first digit will be `0' if
#            |               | it is not formatted as complements.
#            |               | For the conversions `x', `X', `b' and `B'
#            |               | on non-zero, prefix the result with ``0x'',
#            |               | ``0X'', ``0b'' and ``0B'', respectively.
#            |               | For `a', `A', `e', `E', `f', `g', and 'G',
#            |               | force a decimal point to be added,
#            |               | even if no digits follow.
#            |               | For `g' and 'G', do not remove trailing zeros.
#   ---------+---------------+-----------------------------------------
#   +        | bBdiouxX      | Add a leading plus sign to non-negative
#            | aAeEfgG       | numbers.
#            | (numeric fmt) | For `o', `x', `X', `b' and `B', use
#            |               | a minus sign with absolute value for
#            |               | negative values.
#   ---------+---------------+-----------------------------------------
#   -        | all           | Left-justify the result of this conversion.
#   ---------+---------------+-----------------------------------------
#   0 (zero) | bBdiouxX      | Pad with zeros, not spaces.
#            | aAeEfgG       | For `o', `x', `X', `b' and `B', radix-1
#            | (numeric fmt) | is used for negative numbers formatted as
#            |               | complements.
#   ---------+---------------+-----------------------------------------
#   *        | all           | Use the next argument as the field width.
#            |               | If negative, left-justify the result. If the
#            |               | asterisk is followed by a number and a dollar
#            |               | sign, use the indicated argument as the width.
# 
# Examples of flags:
# 
#  # `+' and space flag specifies the sign of non-negative numbers.
#  sprintf("%d", 123)  #=> "123"
#  sprintf("%+d", 123) #=> "+123"
#  sprintf("% d", 123) #=> " 123"
# 
#  # `#' flag for `o' increases number of digits to show `0'.
#  # `+' and space flag changes format of negative numbers.
#  sprintf("%o", 123)   #=> "173"
#  sprintf("%#o", 123)  #=> "0173"
#  sprintf("%+o", -123) #=> "-173"
#  sprintf("%o", -123)  #=> "..7605"
#  sprintf("%#o", -123) #=> "..7605"
# 
#  # `#' flag for `x' add a prefix `0x' for non-zero numbers.
#  # `+' and space flag disables complements for negative numbers.
#  sprintf("%x", 123)   #=> "7b"
#  sprintf("%#x", 123)  #=> "0x7b"
#  sprintf("%+x", -123) #=> "-7b"
#  sprintf("%x", -123)  #=> "..f85"
#  sprintf("%#x", -123) #=> "0x..f85"
#  sprintf("%#x", 0)    #=> "0"
# 
#  # `#' for `X' uses the prefix `0X'.
#  sprintf("%X", 123)  #=> "7B"
#  sprintf("%#X", 123) #=> "0X7B"
# 
#  # `#' flag for `b' add a prefix `0b' for non-zero numbers.
#  # `+' and space flag disables complements for negative numbers.
#  sprintf("%b", 123)   #=> "1111011"
#  sprintf("%#b", 123)  #=> "0b1111011"
#  sprintf("%+b", -123) #=> "-1111011"
#  sprintf("%b", -123)  #=> "..10000101"
#  sprintf("%#b", -123) #=> "0b..10000101"
#  sprintf("%#b", 0)    #=> "0"
# 
#  # `#' for `B' uses the prefix `0B'.
#  sprintf("%B", 123)  #=> "1111011"
#  sprintf("%#B", 123) #=> "0B1111011"
# 
#  # `#' for `e' forces to show the decimal point.
#  sprintf("%.0e", 1)  #=> "1e+00"
#  sprintf("%#.0e", 1) #=> "1.e+00"
# 
#  # `#' for `f' forces to show the decimal point.
#  sprintf("%.0f", 1234)  #=> "1234"
#  sprintf("%#.0f", 1234) #=> "1234."
# 
#  # `#' for `g' forces to show the decimal point.
#  # It also disables stripping lowest zeros.
#  sprintf("%g", 123.4)   #=> "123.4"
#  sprintf("%#g", 123.4)  #=> "123.400"
#  sprintf("%g", 123456)  #=> "123456"
#  sprintf("%#g", 123456) #=> "123456."
# 
# The field width is an optional integer, followed optionally by a
# period and a precision.  The width specifies the minimum number of
# characters that will be written to the result for this field.
# 
# Examples of width:
# 
#  # padding is done by spaces,       width=20
#  # 0 or radix-1.             <------------------>
#  sprintf("%20d", 123)   #=> "                 123"
#  sprintf("%+20d", 123)  #=> "                +123"
#  sprintf("%020d", 123)  #=> "00000000000000000123"
#  sprintf("%+020d", 123) #=> "+0000000000000000123"
#  sprintf("% 020d", 123) #=> " 0000000000000000123"
#  sprintf("%-20d", 123)  #=> "123                 "
#  sprintf("%-+20d", 123) #=> "+123                "
#  sprintf("%- 20d", 123) #=> " 123                "
#  sprintf("%020x", -123) #=> "..ffffffffffffffff85"
# 
# For
# numeric fields, the precision controls the number of decimal places
# displayed.  For string fields, the precision determines the maximum
# number of characters to be copied from the string.  (Thus, the format
# sequence <code>%10.10s</code> will always contribute exactly ten
# characters to the result.)
# 
# Examples of precisions:
# 
#  # precision for `d', 'o', 'x' and 'b' is
#  # minimum number of digits               <------>
#  sprintf("%20.8d", 123)  #=> "            00000123"
#  sprintf("%20.8o", 123)  #=> "            00000173"
#  sprintf("%20.8x", 123)  #=> "            0000007b"
#  sprintf("%20.8b", 123)  #=> "            01111011"
#  sprintf("%20.8d", -123) #=> "           -00000123"
#  sprintf("%20.8o", -123) #=> "            ..777605"
#  sprintf("%20.8x", -123) #=> "            ..ffff85"
#  sprintf("%20.8b", -11)  #=> "            ..110101"
# 
#  # "0x" and "0b" for `#x' and `#b' is not counted for
#  # precision but "0" for `#o' is counted.  <------>
#  sprintf("%#20.8d", 123)  #=> "            00000123"
#  sprintf("%#20.8o", 123)  #=> "            00000173"
#  sprintf("%#20.8x", 123)  #=> "          0x0000007b"
#  sprintf("%#20.8b", 123)  #=> "          0b01111011"
#  sprintf("%#20.8d", -123) #=> "           -00000123"
#  sprintf("%#20.8o", -123) #=> "            ..777605"
#  sprintf("%#20.8x", -123) #=> "          0x..ffff85"
#  sprintf("%#20.8b", -11)  #=> "          0b..110101"
# 
#  # precision for `e' is number of
#  # digits after the decimal point           <------>
#  sprintf("%20.8e", 1234.56789) #=> "      1.23456789e+03"
# 
#  # precision for `f' is number of
#  # digits after the decimal point               <------>
#  sprintf("%20.8f", 1234.56789) #=> "       1234.56789000"
# 
#  # precision for `g' is number of
#  # significant digits                          <------->
#  sprintf("%20.8g", 1234.56789) #=> "           1234.5679"
# 
#  #                                         <------->
#  sprintf("%20.8g", 123456789)  #=> "       1.2345679e+08"
# 
#  # precision for `s' is
#  # maximum number of characters                    <------>
#  sprintf("%20.8s", "string test") #=> "            string t"
# 
# Examples:
# 
#    sprintf("%d %04x", 123, 123)               #=> "123 007b"
#    sprintf("%08b '%4s'", 123, 123)            #=> "01111011 ' 123'"
#    sprintf("%1$*2$s %2$d %1$s", "hello", 8)   #=> "   hello 8 hello"
#    sprintf("%1$*2$s %2$d", "hello", -8)       #=> "hello    -8"
#    sprintf("%+g:% g:%-g", 1.23, 1.23, 1.23)   #=> "+1.23: 1.23:1.23"
#    sprintf("%u", -123)                        #=> "-123"
# 
# For more complex formatting, Ruby supports a reference by name.
# %<name>s style uses format style, but %{name} style doesn't.
# 
# Exapmles:
#   sprintf("%<foo>d : %<bar>f", { :foo => 1, :bar => 2 })
#     #=> 1 : 2.000000
#   sprintf("%{foo}f", { :foo => 1 })
#     # => "1f"
def format(format_string  , arguments=0); ''; end
##
# Converts <i>arg</i> to a <code>Fixnum</code> or <code>Bignum</code>.
# Numeric types are converted directly (with floating point numbers
# being truncated).    <i>base</i> (0, or between 2 and 36) is a base for
# integer string representation.  If <i>arg</i> is a <code>String</code>,
# when <i>base</i> is omitted or equals to zero, radix indicators
# (<code>0</code>, <code>0b</code>, and <code>0x</code>) are honored.
# In any case, strings should be strictly conformed to numeric
# representation. This behavior is different from that of
# <code>String#to_i</code>.  Non string values will be converted using
# <code>to_int</code>, and <code>to_i</code>.
# 
#    Integer(123.999)    #=> 123
#    Integer("0x1a")     #=> 26
#    Integer(Time.new)   #=> 1204973019
#    Integer("0930", 10) #=> 930
#    Integer("111", 2)   #=> 7
def Integer(arg,base=0); 0; end
##
# Returns <i>arg</i> converted to a float. Numeric types are converted
# directly, the rest are converted using <i>arg</i>.to_f. As of Ruby
# 1.8, converting <code>nil</code> generates a <code>TypeError</code>.
# 
#    Float(1)           #=> 1.0
#    Float("123.456")   #=> 123.456
def Float(arg); 0.0; end
##
# Converts <i>arg</i> to a <code>String</code> by calling its
# <code>to_s</code> method.
# 
#    String(self)        #=> "main"
#    String(self.class)  #=> "Object"
#    String(123456)      #=> "123456"
def String(arg); ''; end
##
# Returns +arg+ as an Array.
# 
# First tries to call Array#to_ary on +arg+, then Array#to_a.
# 
#    Array(1..5)   #=> [1, 2, 3, 4, 5]
def Array(arg); []; end
##
# Converts <i>arg</i> to a <code>Hash</code> by calling
# <i>arg</i><code>.to_hash</code>. Returns an empty <code>Hash</code> when
# <i>arg</i> is <tt>nil</tt> or <tt>[]</tt>.
# 
#    Hash([])          #=> {}
#    Hash(nil)         #=> nil
#    Hash(key: :value) #=> {:key => :value}
#    Hash([1, 2, 3])   #=> TypeError
def Hash(arg); {}; end
##
# Generates a Continuation object, which it passes to
# the associated block. You need to <code>require
# 'continuation'</code> before using this method. Performing a
# <em>cont</em><code>.call</code> will cause the #callcc
# to return (as will falling through the end of the block). The
# value returned by the #callcc is the value of the
# block, or the value passed to <em>cont</em><code>.call</code>. See
# class Continuation for more details. Also see
# Kernel#throw for an alternative mechanism for
# unwinding a call stack.
def callcc(&block); Object.new; end
##
# Returns x+i*y;
# 
#    Complex(1, 2)    #=> (1+2i)
#    Complex('1+2i')  #=> (1+2i)
# 
# Syntax of string form:
# 
#   string form = extra spaces , complex , extra spaces ;
#   complex = real part | [ sign ] , imaginary part
#           | real part , sign , imaginary part
#           | rational , "@" , rational ;
#   real part = rational ;
#   imaginary part = imaginary unit | unsigned rational , imaginary unit ;
#   rational = [ sign ] , unsigned rational ;
#   unsigned rational = numerator | numerator , "/" , denominator ;
#   numerator = integer part | fractional part | integer part , fractional part ;
#   denominator = digits ;
#   integer part = digits ;
#   fractional part = "." , digits , [ ( "e" | "E" ) , [ sign ] , digits ] ;
#   imaginary unit = "i" | "I" | "j" | "J" ;
#   sign = "-" | "+" ;
#   digits = digit , { digit | "_" , digit };
#   digit = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
#   extra spaces = ? \s* ? ;
# 
# See String#to_c.
def Complex(x, y=0); 0; end
##
#  Calls the operating system function identified by _num_ and
#  returns the result of the function or raises SystemCallError if
#  it failed.
# 
#  Arguments for the function can follow _num_. They must be either
#  +String+ objects or +Integer+ objects. A +String+ object is passed
#  as a pointer to the byte sequence. An +Integer+ object is passed
#  as an integer whose bit size is same as a pointer.
#  Up to nine parameters may be passed (14 on the Atari-ST).
# 
#  The function identified by _num_ is system
#  dependent. On some Unix systems, the numbers may be obtained from a
#  header file called <code>syscall.h</code>.
# 
#     syscall 4, 1, "hello\n", 6   # '4' is write(2) on our box
# 
#  <em>produces:</em>
# 
#     hello
# 
#  Calling +syscall+ on a platform which does not have any way to
#  an arbitrary system function just fails with NotImplementedError.
# 
# Note::
#   +syscall+ is essentially unsafe and unportable. Feel free to shoot your foot.
#   DL (Fiddle) library is preferred for safer and a bit more portable programming.
def syscall(num , args=0); 0; end
##
# Creates an IO object connected to the given stream, file, or subprocess.
# 
# If +path+ does not start with a pipe character (<code>|</code>), treat it
# as the name of a file to open using the specified mode (defaulting to
# "r").
# 
# The +mode+ is either a string or an integer.  If it is an integer, it
# must be bitwise-or of open(2) flags, such as File::RDWR or File::EXCL.  If
# it is a string, it is either "fmode", "fmode:ext_enc", or
# "fmode:ext_enc:int_enc".
# 
# See the documentation of IO.new for full documentation of the +mode+ string
# directives.
# 
# If a file is being created, its initial permissions may be set using the
# +perm+ parameter.  See File.new and the open(2) and chmod(2) man pages for
# a description of permissions.
# 
# If a block is specified, it will be invoked with the IO object as a
# parameter, and the IO will be automatically closed when the block
# terminates.  The call returns the value of the block.
# 
# If +path+ starts with a pipe character (<code>"|"</code>), a subprocess is
# created, connected to the caller by a pair of pipes.  The returned IO
# object may be used to write to the standard input and read from the
# standard output of this subprocess.
# 
# If the command following the pipe is a single minus sign
# (<code>"|-"</code>), Ruby forks, and this subprocess is connected to the
# parent.  If the command is not <code>"-"</code>, the subprocess runs the
# command.
# 
# When the subprocess is ruby (opened via <code>"|-"</code>), the +open+
# call returns +nil+.  If a block is associated with the open call, that
# block will run twice --- once in the parent and once in the child.
# 
# The block parameter will be an IO object in the parent and +nil+ in the
# child. The parent's +IO+ object will be connected to the child's $stdin
# and $stdout.  The subprocess will be terminated at the end of the block.
# 
# === Examples
# 
# Reading from "testfile":
# 
#    open("testfile") do |f|
#      print f.gets
#    end
# 
# Produces:
# 
#    This is line one
# 
# Open a subprocess and read its output:
# 
#    cmd = open("|date")
#    print cmd.gets
#    cmd.close
# 
# Produces:
# 
#    Wed Apr  9 08:56:31 CDT 2003
# 
# Open a subprocess running the same Ruby program:
# 
#    f = open("|-", "w+")
#    if f == nil
#      puts "in Child"
#      exit
#    else
#      puts "Got: #{f.gets}"
#    end
# 
# Produces:
# 
#    Got: in Child
# 
# Open a subprocess using a block to receive the IO object:
# 
#    open "|-" do |f|
#      if f then
#        # parent process
#        puts "Got: #{f.gets}"
#      else
#        # child process
#        puts "in Child"
#      end
#    end
# 
# Produces:
# 
#    Got: in Child
def open(path , mode=0, perm=0, opt=0); Object.new; end
##
# Equivalent to:
#    io.write(sprintf(string, obj, ...)
# or
#    $stdout.write(sprintf(string, obj, ...)
def printf(io, string , obj=0); end
##
# Prints each object in turn to <code>$stdout</code>. If the output
# field separator (<code>$,</code>) is not +nil+, its
# contents will appear between each field. If the output record
# separator (<code>$\\</code>) is not +nil+, it will be
# appended to the output. If no arguments are given, prints
# <code>$_</code>. Objects that aren't strings will be converted by
# calling their <code>to_s</code> method.
# 
#    print "cat", [1,2,3], 99, "\n"
#    $, = ", "
#    $\ = "\n"
#    print "cat", [1,2,3], 99
# 
# <em>produces:</em>
# 
#    cat12399
#    cat, 1, 2, 3, 99
def print(); end
##
#  Equivalent to:
# 
#    $stdout.putc(int)
# 
# Refer to the documentation for IO#putc for important information regarding
# multi-byte characters.
def putc(int); 0; end
##
# Equivalent to
# 
#     $stdout.puts(obj, ...)
def puts(); end
##
# Returns (and assigns to <code>$_</code>) the next line from the list
# of files in +ARGV+ (or <code>$*</code>), or from standard input if
# no files are present on the command line. Returns +nil+ at end of
# file. The optional argument specifies the record separator. The
# separator is included with the contents of each record. A separator
# of +nil+ reads the entire contents, and a zero-length separator
# reads the input one paragraph at a time, where paragraphs are
# divided by two consecutive newlines.  If the first argument is an
# integer, or optional second argument is given, the returning string
# would not be longer than the given value in bytes.  If multiple
# filenames are present in +ARGV+, +gets(nil)+ will read the contents
# one file at a time.
# 
#    ARGV << "testfile"
#    print while gets
# 
# <em>produces:</em>
# 
#    This is line one
#    This is line two
#    This is line three
#    And so on...
# 
# The style of programming using <code>$_</code> as an implicit
# parameter is gradually losing favor in the Ruby community.
def gets(sep=$/); '' || nil; end
##
# Equivalent to <code>Kernel::gets</code>, except
# +readline+ raises +EOFError+ at end of file.
def readline(sep=$/); ''; end
##
# Calls select(2) system call.
# It monitors given arrays of <code>IO</code> objects, waits one or more
# of <code>IO</code> objects ready for reading, are ready for writing,
# and have pending exceptions respectively, and returns an array that
# contains arrays of those IO objects.  It will return <code>nil</code>
# if optional <i>timeout</i> value is given and no <code>IO</code> object
# is ready in <i>timeout</i> seconds.
# 
# === Parameters
# read_array:: an array of <code>IO</code> objects that wait until ready for read
# write_array:: an array of <code>IO</code> objects that wait until ready for write
# error_array:: an array of <code>IO</code> objects that wait for exceptions
# timeout:: a numeric value in second
# 
# === Example
# 
#     rp, wp = IO.pipe
#     mesg = "ping "
#     100.times {
#       rs, ws, = IO.select([rp], [wp])
#       if r = rs[0]
#         ret = r.read(5)
#         print ret
#         case ret
#         when /ping/
#           mesg = "pong\n"
#         when /pong/
#           mesg = "ping "
#         end
#       end
#       if w = ws[0]
#         w.write(mesg)
#       end
#     }
# 
# <em>produces:</em>
# 
#     ping pong
#     ping pong
#     ping pong
#     (snipped)
#     ping
def select(read_arra); [] || nil; end
##
# Returns an array containing the lines returned by calling
# <code>Kernel.gets(<i>sep</i>)</code> until the end of file.
def readlines(sep=$/); []; end
##
# Returns the standard output of running _cmd_ in a subshell.
# The built-in syntax <code>%x{...}</code> uses
# this method. Sets <code>$?</code> to the process status.
# 
#    `date`                   #=> "Wed Apr  9 08:56:30 CDT 2003\n"
#    `ls testdir`.split[1]    #=> "main.rb"
#    `echo oops && exit 99`   #=> "oops\n"
#    $?.exitstatus            #=> 99
def `; ''; end
##
# For each object, directly writes _obj_.+inspect+ followed by a
# newline to the program's standard output.
# 
#    S = Struct.new(:name, :state)
#    s = S['dave', 'TX']
#    p s
# 
# <em>produces:</em>
# 
#    #<S name="dave", state="TX">
def p(obj); end
end

##
# Ruby exception objects are subclasses of <code>Exception</code>.
# However, operating systems typically report errors using plain
# integers. Module <code>Errno</code> is created dynamically to map
# these operating system errors to Ruby classes, with each error
# number generating its own subclass of <code>SystemCallError</code>.
# As the subclass is created in module <code>Errno</code>, its name
# will start <code>Errno::</code>.
# 
# The names of the <code>Errno::</code> classes depend on
# the environment in which Ruby runs. On a typical Unix or Windows
# platform, there are <code>Errno</code> classes such as
# <code>Errno::EACCES</code>, <code>Errno::EAGAIN</code>,
# <code>Errno::EINTR</code>, and so on.
# 
# The integer operating system error number corresponding to a
# particular error is available as the class constant
# <code>Errno::</code><em>error</em><code>::Errno</code>.
# 
#    Errno::EACCES::Errno   #=> 13
#    Errno::EAGAIN::Errno   #=> 11
#    Errno::EINTR::Errno    #=> 4
# 
# The full list of operating system errors on your particular platform
# are available as the constants of <code>Errno</code>.
# 
#    Errno.constants   #=> :E2BIG, :EACCES, :EADDRINUSE, :EADDRNOTAVAIL, ...
module Errno
end

##
# The <code>Math</code> module contains module functions for basic
# trigonometric and transcendental functions. See class
# <code>Float</code> for a list of constants that
# define Ruby's floating point accuracy.
module Math
##
# Raised when a mathematical function is evaluated outside of its
# domain of definition.
# 
# For example, since +cos+ returns values in the range -1..1,
# its inverse function +acos+ is only defined on that interval:
# 
#    Math.acos(42)
# 
# <em>produces:</em>
# 
#    Math::DomainError: Numerical argument is out of domain - "acos"
class DomainError < StandardError
end

##
# Computes the arc tangent given <i>y</i> and <i>x</i>. Returns
# -PI..PI.
# 
#   Math.atan2(-0.0, -1.0) #=> -3.141592653589793
#   Math.atan2(-1.0, -1.0) #=> -2.356194490192345
#   Math.atan2(-1.0, 0.0)  #=> -1.5707963267948966
#   Math.atan2(-1.0, 1.0)  #=> -0.7853981633974483
#   Math.atan2(-0.0, 1.0)  #=> -0.0
#   Math.atan2(0.0, 1.0)   #=> 0.0
#   Math.atan2(1.0, 1.0)   #=> 0.7853981633974483
#   Math.atan2(1.0, 0.0)   #=> 1.5707963267948966
#   Math.atan2(1.0, -1.0)  #=> 2.356194490192345
#   Math.atan2(0.0, -1.0)  #=> 3.141592653589793
def self.atan2(y, x); 0.0; end
##
# Computes the cosine of <i>x</i> (expressed in radians). Returns
# -1..1.
def self.cos(x); 0.0; end
##
# Computes the sine of <i>x</i> (expressed in radians). Returns
# -1..1.
def self.sin(x); 0.0; end
##
# Returns the tangent of <i>x</i> (expressed in radians).
def self.tan(x); 0.0; end
##
# Computes the arc cosine of <i>x</i>. Returns 0..PI.
def self.acos(x); 0.0; end
##
# Computes the arc sine of <i>x</i>. Returns -{PI/2} .. {PI/2}.
def self.asin(x); 0.0; end
##
# Computes the arc tangent of <i>x</i>. Returns -{PI/2} .. {PI/2}.
def self.atan(x); 0.0; end
##
# Computes the hyperbolic cosine of <i>x</i> (expressed in radians).
def self.cosh(x); 0.0; end
##
# Computes the hyperbolic sine of <i>x</i> (expressed in
# radians).
def self.sinh(x); 0.0; end
##
# Computes the hyperbolic tangent of <i>x</i> (expressed in
# radians).
def self.tanh(); 0.0; end
##
# Computes the inverse hyperbolic cosine of <i>x</i>.
def self.acosh(x); 0.0; end
##
# Computes the inverse hyperbolic sine of <i>x</i>.
def self.asinh(x); 0.0; end
##
# Computes the inverse hyperbolic tangent of <i>x</i>.
def self.atanh(x); 0.0; end
##
# Returns e**x.
# 
#   Math.exp(0)       #=> 1.0
#   Math.exp(1)       #=> 2.718281828459045
#   Math.exp(1.5)     #=> 4.4816890703380645
def self.exp(x); 0.0; end
##
# Returns the natural logarithm of <i>numeric</i>.
# If additional second argument is given, it will be the base
# of logarithm.
# 
#   Math.log(1)          #=> 0.0
#   Math.log(Math::E)    #=> 1.0
#   Math.log(Math::E**3) #=> 3.0
#   Math.log(12,3)       #=> 2.2618595071429146
def self.log(numeric); 0.0; end
##
# Returns the base 2 logarithm of <i>numeric</i>.
# 
#   Math.log2(1)      #=> 0.0
#   Math.log2(2)      #=> 1.0
#   Math.log2(32768)  #=> 15.0
#   Math.log2(65536)  #=> 16.0
def self.log2(numeric); 0.0; end
##
# Returns the base 10 logarithm of <i>numeric</i>.
# 
#   Math.log10(1)       #=> 0.0
#   Math.log10(10)      #=> 1.0
#   Math.log10(10**100) #=> 100.0
def self.log10(numeric); 0.0; end
##
# Returns the non-negative square root of <i>numeric</i>.
# 
#   0.upto(10) {|x|
#     p [x, Math.sqrt(x), Math.sqrt(x)**2]
#   }
#   #=>
#   [0, 0.0, 0.0]
#   [1, 1.0, 1.0]
#   [2, 1.4142135623731, 2.0]
#   [3, 1.73205080756888, 3.0]
#   [4, 2.0, 4.0]
#   [5, 2.23606797749979, 5.0]
#   [6, 2.44948974278318, 6.0]
#   [7, 2.64575131106459, 7.0]
#   [8, 2.82842712474619, 8.0]
#   [9, 3.0, 9.0]
#   [10, 3.16227766016838, 10.0]
def self.sqrt(numeric); 0.0; end
##
# Returns the cube root of <i>numeric</i>.
# 
#   -9.upto(9) {|x|
#     p [x, Math.cbrt(x), Math.cbrt(x)**3]
#   }
#   #=>
#   [-9, -2.0800838230519, -9.0]
#   [-8, -2.0, -8.0]
#   [-7, -1.91293118277239, -7.0]
#   [-6, -1.81712059283214, -6.0]
#   [-5, -1.7099759466767, -5.0]
#   [-4, -1.5874010519682, -4.0]
#   [-3, -1.44224957030741, -3.0]
#   [-2, -1.25992104989487, -2.0]
#   [-1, -1.0, -1.0]
#   [0, 0.0, 0.0]
#   [1, 1.0, 1.0]
#   [2, 1.25992104989487, 2.0]
#   [3, 1.44224957030741, 3.0]
#   [4, 1.5874010519682, 4.0]
#   [5, 1.7099759466767, 5.0]
#   [6, 1.81712059283214, 6.0]
#   [7, 1.91293118277239, 7.0]
#   [8, 2.0, 8.0]
#   [9, 2.0800838230519, 9.0]
def self.cbrt(numeric); 0.0; end
##
# Returns a two-element array containing the normalized fraction (a
# <code>Float</code>) and exponent (a <code>Fixnum</code>) of
# <i>numeric</i>.
# 
#    fraction, exponent = Math.frexp(1234)   #=> [0.6025390625, 11]
#    fraction * 2**exponent                  #=> 1234.0
def self.frexp(numeric); []; end
##
# Returns the value of <i>flt</i>*(2**<i>int</i>).
# 
#    fraction, exponent = Math.frexp(1234)
#    Math.ldexp(fraction, exponent)   #=> 1234.0
def self.ldexp(flt, int); 0.0; end
##
# Returns sqrt(x**2 + y**2), the hypotenuse of a right-angled triangle
# with sides <i>x</i> and <i>y</i>.
# 
#    Math.hypot(3, 4)   #=> 5.0
def self.hypot(x, y); 0.0; end
##
# Calculates the error function of x.
def self.erf(x); 0.0; end
##
# Calculates the complementary error function of x.
def self.erfc(x); 0.0; end
##
# Calculates the gamma function of x.
# 
# Note that gamma(n) is same as fact(n-1) for integer n > 0.
# However gamma(n) returns float and can be an approximation.
# 
#  def fact(n) (1..n).inject(1) {|r,i| r*i } end
#  1.upto(26) {|i| p [i, Math.gamma(i), fact(i-1)] }
#  #=> [1, 1.0, 1]
#  #   [2, 1.0, 1]
#  #   [3, 2.0, 2]
#  #   [4, 6.0, 6]
#  #   [5, 24.0, 24]
#  #   [6, 120.0, 120]
#  #   [7, 720.0, 720]
#  #   [8, 5040.0, 5040]
#  #   [9, 40320.0, 40320]
#  #   [10, 362880.0, 362880]
#  #   [11, 3628800.0, 3628800]
#  #   [12, 39916800.0, 39916800]
#  #   [13, 479001600.0, 479001600]
#  #   [14, 6227020800.0, 6227020800]
#  #   [15, 87178291200.0, 87178291200]
#  #   [16, 1307674368000.0, 1307674368000]
#  #   [17, 20922789888000.0, 20922789888000]
#  #   [18, 355687428096000.0, 355687428096000]
#  #   [19, 6.402373705728e+15, 6402373705728000]
#  #   [20, 1.21645100408832e+17, 121645100408832000]
#  #   [21, 2.43290200817664e+18, 2432902008176640000]
#  #   [22, 5.109094217170944e+19, 51090942171709440000]
#  #   [23, 1.1240007277776077e+21, 1124000727777607680000]
#  #   [24, 2.5852016738885062e+22, 25852016738884976640000]
#  #   [25, 6.204484017332391e+23, 620448401733239439360000]
#  #   [26, 1.5511210043330954e+25, 15511210043330985984000000]
def self.gamma(x); 0.0; end
##
# Calculates the logarithmic gamma of x and
# the sign of gamma of x.
# 
# Math.lgamma(x) is same as
#  [Math.log(Math.gamma(x).abs), Math.gamma(x) < 0 ? -1 : 1]
# but avoid overflow by Math.gamma(x) for large x.
def self.lgamma(x); [0.0, 0]; end
end

##
# The GC module provides an interface to Ruby's mark and
# sweep garbage collection mechanism.
# 
# Some of the underlying methods are also available via the ObjectSpace
# module.
# 
# You may obtain information about the operation of the GC through
# GC::Profiler.
module GC
##
# Initiates garbage collection, unless manually disabled.
def self.start; end
##
# Initiates garbage collection, unless manually disabled.
def self.garbage_collect; end
##
# Enables garbage collection, returning +true+ if garbage
# collection was previously disabled.
# 
#    GC.disable   #=> false
#    GC.enable    #=> true
#    GC.enable    #=> false
def self.enable; true || false; end
##
# Disables garbage collection, returning +true+ if garbage
# collection was already disabled.
# 
#    GC.disable   #=> false
#    GC.disable   #=> true
def self.disable; true || false; end
##
# Returns current status of GC stress mode.
def self.stress; true || false; end
##
# Updates the GC stress mode.
# 
# When stress mode is enabled, the GC is invoked at every GC opportunity:
# all memory and object allocations.
# 
# Enabling stress mode will degrade performance, it is only for debugging.
def self.stress= bool; true || false; end
##
# The number of times GC occurred.
# 
# It returns the number of times GC occurred since the process started.
def self.count; 0; end
##
# Returns a Hash containing information about the GC.
# 
# The hash includes information about internal statistics about GC such as:
# 
#     {
#         :count=>0,
#         :heap_used=>12,
#         :heap_length=>12,
#         :heap_increment=>0,
#         :heap_live_num=>7539,
#         :heap_free_num=>88,
#         :heap_final_num=>0,
#         :total_allocated_object=>7630,
#         :total_freed_object=>88
#     }
# 
# The contents of the hash are implementation specific and may be changed in
# the future.
# 
# This method is only expected to work on C Ruby.
def self.stat; {}; end
##
# Returns the size of memory allocated by malloc().
# 
# Only available if ruby was built with +CALC_EXACT_MALLOC_SIZE+.
def self.malloc_allocated_size; 0; end
##
# Returns the number of malloc() allocations.
# 
# Only available if ruby was built with +CALC_EXACT_MALLOC_SIZE+.
def self.malloc_allocations; 0; end
end

##
# The ObjectSpace module contains a number of routines
# that interact with the garbage collection facility and allow you to
# traverse all living objects with an iterator.
# 
# ObjectSpace also provides support for object finalizers, procs that will be
# called when a specific object is about to be destroyed by garbage
# collection.
# 
#    include ObjectSpace
# 
#    a = "A"
#    b = "B"
#    c = "C"
# 
#    define_finalizer(a, proc {|id| puts "Finalizer one on #{id}" })
#    define_finalizer(a, proc {|id| puts "Finalizer two on #{id}" })
#    define_finalizer(b, proc {|id| puts "Finalizer three on #{id}" })
# 
# _produces:_
# 
#    Finalizer three on 537763470
#    Finalizer one on 537763480
#    Finalizer two on 537763480
module ObjectSpace
##
# An ObjectSpace::WeakMap object holds references to
# any objects, but those objects can get garbage collected.
# 
# This class is mostly used internally by WeakRef, please use
# +lib/weakref.rb+ for the public interface.
class WeakMap < Object
end

##
# Calls the block once for each living, nonimmediate object in this
# Ruby process. If <i>module</i> is specified, calls the block
# for only those classes or modules that match (or are a subclass of)
# <i>module</i>. Returns the number of objects found. Immediate
# objects (<code>Fixnum</code>s, <code>Symbol</code>s
# <code>true</code>, <code>false</code>, and <code>nil</code>) are
# never returned. In the example below, <code>each_object</code>
# returns both the numbers we defined and several constants defined in
# the <code>Math</code> module.
# 
# If no block is given, an enumerator is returned instead.
# 
#    a = 102.7
#    b = 95       # Won't be returned
#    c = 12345678987654321
#    count = ObjectSpace.each_object(Numeric) {|x| p x }
#    puts "Total count: #{count}"
# 
# <em>produces:</em>
# 
#    12345678987654321
#    102.7
#    2.71828182845905
#    3.14159265358979
#    2.22044604925031e-16
#    1.7976931348623157e+308
#    2.2250738585072e-308
#    Total count: 7
def self.each_object(modul=0, &block); Enumerator.new; end
##
# Initiates garbage collection, unless manually disabled.
def self.start; end
##
# Initiates garbage collection, unless manually disabled.
def self.garbage_collect; end
##
# Adds <i>aProc</i> as a finalizer, to be called after <i>obj</i>
# was destroyed.
def self.define_finalizer(obj, aProc=pro); end
##
# Removes all finalizers for <i>obj</i>.
def self.undefine_finalizer(obj); end
##
# Converts an object id to a reference to the object. May not be
# called on an object id passed as a parameter to a finalizer.
# 
#    s = "I am a string"                    #=> "I am a string"
#    r = ObjectSpace._id2ref(s.object_id)   #=> "I am a string"
#    r == s                                 #=> true
def self._id2ref(object_id); Object.new; end
##
# Counts objects for each type.
# 
# It returns a hash, such as:
#     {
#       :TOTAL=>10000,
#       :FREE=>3011,
#       :T_OBJECT=>6,
#       :T_CLASS=>404,
#       # ...
#     }
# 
# The contents of the returned hash are implementation specific.
# It may be changed in future.
# 
# If the optional argument +result_hash+ is given,
# it is overwritten and returned. This is intended to avoid probe effect.
# 
# This method is only expected to work on C Ruby.
def self.count_objects(result_hash=0); {}; end
end

##
# <code>FileTest</code> implements file test operations similar to
# those used in <code>File::Stat</code>. It exists as a standalone
# module, and its methods are also insinuated into the <code>File</code>
# class. (Note that this is not done by inclusion: the interpreter cheats).
module FileTest
##
# Returns <code>true</code> if the named file is a directory,
# or a symlink that points at a directory, and <code>false</code>
# otherwise.
# 
#    File.directory?(".")
def directory?(file_name); true || false; end
##
# Return <code>true</code> if the named file exists.
def exist?(file_name); true || false; end
##
# Return <code>true</code> if the named file exists.
def exists?(file_name); true || false; end
##
# Returns <code>true</code> if the named file is readable by the effective
# user id of this process.
def readable?(file_name); true || false; end
##
# Returns <code>true</code> if the named file is readable by the real
# user id of this process.
def readable_real?(file_name); true || false; end
##
# If <i>file_name</i> is readable by others, returns an integer
# representing the file permission bits of <i>file_name</i>. Returns
# <code>nil</code> otherwise. The meaning of the bits is platform
# dependent; on Unix systems, see <code>stat(2)</code>.
# 
#    File.world_readable?("/etc/passwd")           #=> 420
#    m = File.world_readable?("/etc/passwd")
#    sprintf("%o", m)                              #=> "644"
def world_readable?(file_name); 1 || nil; end
##
# Returns <code>true</code> if the named file is writable by the effective
# user id of this process.
def writable?(file_name); true || false; end
##
# Returns <code>true</code> if the named file is writable by the real
# user id of this process.
def writable_real?(file_name); true || false; end
##
# If <i>file_name</i> is writable by others, returns an integer
# representing the file permission bits of <i>file_name</i>. Returns
# <code>nil</code> otherwise. The meaning of the bits is platform
# dependent; on Unix systems, see <code>stat(2)</code>.
# 
#    File.world_writable?("/tmp")                  #=> 511
#    m = File.world_writable?("/tmp")
#    sprintf("%o", m)                              #=> "777"
def world_writable?(file_name); 1 || nil; end
##
# Returns <code>true</code> if the named file is executable by the effective
# user id of this process.
def executable?(file_name); true || false; end
##
# Returns <code>true</code> if the named file is executable by the real
# user id of this process.
def executable_real?(file_name); true || false; end
##
# Returns <code>true</code> if the named file exists and is a
# regular file.
def file?(file_name); true || false; end
##
# Returns <code>true</code> if the named file exists and has
# a zero size.
def zero?(file_name); true || false; end
##
# Returns +nil+ if +file_name+ doesn't exist or has zero size, the size of the
# file otherwise.
def size?(file_name); 0 || nil; end
##
# Returns the size of <code>file_name</code>.
def size(file_name); 0; end
##
# Returns <code>true</code> if the named file exists and the
# effective used id of the calling process is the owner of
# the file.
def owned?(file_name); true || false; end
##
# Returns <code>true</code> if the named file exists and the
# effective group id of the calling process is the owner of
# the file. Returns <code>false</code> on Windows.
def grpowned?(file_name); true || false; end
##
# Returns <code>true</code> if the named file is a pipe.
def pipe?(file_name); true || false; end
##
# Returns <code>true</code> if the named file is a symbolic link.
def symlink?(file_name); true || false; end
##
# Returns <code>true</code> if the named file is a socket.
def socket?(file_name); true || false; end
##
# Returns <code>true</code> if the named file is a block device.
def blockdev?(file_name); true || false; end
##
# Returns <code>true</code> if the named file is a character device.
def chardev?(file_name); true || false; end
##
# Returns <code>true</code> if the named file has the setuid bit set.
def setuid?(file_name); true || false; end
##
# Returns <code>true</code> if the named file has the setgid bit set.
def setgid?(file_name); true || false; end
##
# Returns <code>true</code> if the named file has the sticky bit set.
def sticky?(file_name); true || false; end
##
# Returns <code>true</code> if the named files are identical.
# 
#     open("a", "w") {}
#     p File.identical?("a", "a")      #=> true
#     p File.identical?("a", "./a")    #=> true
#     File.link("a", "b")
#     p File.identical?("a", "b")      #=> true
#     File.symlink("a", "c")
#     p File.identical?("a", "c")      #=> true
#     open("d", "w") {}
#     p File.identical?("a", "d")      #=> false
def identical?(file_1, file_2); true || false; end
end

##
# The <code>Comparable</code> mixin is used by classes whose objects
# may be ordered. The class must define the <code><=></code> operator,
# which compares the receiver against another object, returning -1, 0,
# or +1 depending on whether the receiver is less than, equal to, or
# greater than the other object. If the other object is not comparable
# then the <code><=></code> operator should return nil.
# <code>Comparable</code> uses
# <code><=></code> to implement the conventional comparison operators
# (<code><</code>, <code><=</code>, <code>==</code>, <code>>=</code>,
# and <code>></code>) and the method <code>between?</code>.
# 
#    class SizeMatters
#      include Comparable
#      attr :str
#      def <=>(anOther)
#        str.size <=> anOther.str.size
#      end
#      def initialize(str)
#        @str = str
#      end
#      def inspect
#        @str
#      end
#    end
# 
#    s1 = SizeMatters.new("Z")
#    s2 = SizeMatters.new("YY")
#    s3 = SizeMatters.new("XXX")
#    s4 = SizeMatters.new("WWWW")
#    s5 = SizeMatters.new("VVVVV")
# 
#    s1 < s2                       #=> true
#    s4.between?(s1, s3)           #=> false
#    s4.between?(s3, s5)           #=> true
#    [ s3, s2, s5, s4, s1 ].sort   #=> [Z, YY, XXX, WWWW, VVVVV]
module Comparable
##
# Compares two objects based on the receiver's <code><=></code>
# method, returning true if it returns 0. Also returns true if
# _obj_ and _other_ are the same object.
# 
# Even if _obj_ <=> _other_ raised an exception, the exception
# is ignoread and returns false.
def ==; true || false; end
##
# Compares two objects based on the receiver's <code><=></code>
# method, returning true if it returns 1.
def >; true || false; end
##
# Compares two objects based on the receiver's <code><=></code>
# method, returning true if it returns 0 or 1.
def >=; true || false; end
##
# Compares two objects based on the receiver's <code><=></code>
# method, returning true if it returns -1.
def <; true || false; end
##
# Compares two objects based on the receiver's <code><=></code>
# method, returning true if it returns -1 or 0.
def <=; true || false; end
##
# Returns <code>false</code> if <i>obj</i> <code><=></code>
# <i>min</i> is less than zero or if <i>anObject</i> <code><=></code>
# <i>max</i> is greater than zero, <code>true</code> otherwise.
# 
#    3.between?(1, 5)               #=> true
#    6.between?(1, 5)               #=> false
#    'cat'.between?('ant', 'dog')   #=> true
#    'gnu'.between?('ant', 'dog')   #=> false
def between?(min, max); true || false; end
end

##
# The <code>Process</code> module is a collection of methods used to
# manipulate processes.
module Process
##
# <code>Process::Status</code> encapsulates the information on the
# status of a running or terminated system process. The built-in
# variable <code>$?</code> is either +nil+ or a
# <code>Process::Status</code> object.
# 
#    fork { exit 99 }   #=> 26557
#    Process.wait       #=> 26557
#    $?.class           #=> Process::Status
#    $?.to_i            #=> 25344
#    $? >> 8            #=> 99
#    $?.stopped?        #=> false
#    $?.exited?         #=> true
#    $?.exitstatus      #=> 99
# 
# Posix systems record information on processes using a 16-bit
# integer.  The lower bits record the process status (stopped,
# exited, signaled) and the upper bits possibly contain additional
# information (for example the program's return code in the case of
# exited processes). Pre Ruby 1.8, these bits were exposed directly
# to the Ruby program. Ruby now encapsulates these in a
# <code>Process::Status</code> object. To maximize compatibility,
# however, these objects retain a bit-oriented interface. In the
# descriptions that follow, when we talk about the integer value of
# _stat_, we're referring to this 16 bit value.
class Status < Object
##
# Returns +true+ if the integer value of _stat_
# equals <em>other</em>.
def ==; true || false; end
##
# Logical AND of the bits in _stat_ with <em>num</em>.
# 
#    fork { exit 0x37 }
#    Process.wait
#    sprintf('%04x', $?.to_i)       #=> "3700"
#    sprintf('%04x', $? & 0x1e00)   #=> "1600"
def &; 0; end
##
# Shift the bits in _stat_ right <em>num</em> places.
# 
#    fork { exit 99 }   #=> 26563
#    Process.wait       #=> 26563
#    $?.to_i            #=> 25344
#    $? >> 8            #=> 99
def >>; 0; end
##
# Returns the bits in _stat_ as a <code>Fixnum</code>. Poking
# around in these bits is platform dependent.
# 
#    fork { exit 0xab }         #=> 26566
#    Process.wait               #=> 26566
#    sprintf('%04x', $?.to_i)   #=> "ab00"
def to_i; 0; end
##
# Returns the bits in _stat_ as a <code>Fixnum</code>. Poking
# around in these bits is platform dependent.
# 
#    fork { exit 0xab }         #=> 26566
#    Process.wait               #=> 26566
#    sprintf('%04x', $?.to_i)   #=> "ab00"
def to_int; 0; end
##
# Show pid and exit status as a string.
# 
#   system("false")
#   p $?.to_s         #=> "pid 12766 exit 1"
def to_s; ''; end
##
# Override the inspection method.
# 
#   system("false")
#   p $?.inspect #=> "#<Process::Status: pid 12861 exit 1>"
def inspect; ''; end
##
# Returns the process ID that this status object represents.
# 
#    fork { exit }   #=> 26569
#    Process.wait    #=> 26569
#    $?.pid          #=> 26569
def pid; 0; end
##
# Returns +true+ if this process is stopped. This is only
# returned if the corresponding <code>wait</code> call had the
# <code>WUNTRACED</code> flag set.
def stopped?; true || false; end
##
# Returns the number of the signal that caused _stat_ to stop
# (or +nil+ if self is not stopped).
def stopsig; 1 || nil; end
##
# Returns +true+ if _stat_ terminated because of
# an uncaught signal.
def signaled?; true || false; end
##
# Returns the number of the signal that caused _stat_ to
# terminate (or +nil+ if self was not terminated by an
# uncaught signal).
def termsig; 1 || nil; end
##
# Returns +true+ if _stat_ exited normally (for
# example using an <code>exit()</code> call or finishing the
# program).
def exited?; true || false; end
##
# Returns the least significant eight bits of the return code of
# _stat_. Only available if <code>exited?</code> is
# +true+.
# 
#    fork { }           #=> 26572
#    Process.wait       #=> 26572
#    $?.exited?         #=> true
#    $?.exitstatus      #=> 0
# 
#    fork { exit 99 }   #=> 26573
#    Process.wait       #=> 26573
#    $?.exited?         #=> true
#    $?.exitstatus      #=> 99
def exitstatus; 1 || nil; end
##
# Returns +true+ if _stat_ is successful, +false+ if not.
# Returns +nil+ if <code>exited?</code> is not +true+.
def success?; true || false || nil; end
##
# Returns +true+ if _stat_ generated a coredump
# when it terminated. Not available on all platforms.
def coredump?; true || false; end
end

##
# Replaces the current process by running the given external _command_.
# _command..._ is one of following forms.
# 
#   commandline                 : command line string which is passed to the standard shell
#   cmdname, arg1, ...          : command name and one or more arguments (no shell)
#   [cmdname, argv0], arg1, ... : command name, argv[0] and zero or more arguments (no shell)
# 
# If single string is given as the command,
# it is taken as a command line that is subject to shell expansion before being executed.
# 
# The standard shell means always <code>"/bin/sh"</code> on Unix-like systems,
# <code>ENV["RUBYSHELL"]</code> or <code>ENV["COMSPEC"]</code> on Windows NT series, and
# similar.
# 
# If two or more +string+ given,
# the first is taken as a command name and
# the rest are passed as parameters to command with no shell expansion.
# 
# If a two-element array at the beginning of the command,
# the first element is the command to be executed,
# and the second argument is used as the <code>argv[0]</code> value,
# which may show up in process listings.
# 
# In order to execute the command, one of the <code>exec(2)</code>
# system calls is used, so the running command may inherit some of the environment
# of the original program (including open file descriptors).
# This behavior is modified by env and options.
# See <code>spawn</code> for details.
# 
# Raises SystemCallError if the command couldn't execute (typically
# <code>Errno::ENOENT</code> when it was not found).
# 
# This method modifies process attributes according to _options_
# (details described in <code>spawn</code>)
# before <code>exec(2)</code> system call.
# The modified attributes may be retained when <code>exec(2)</code> system call fails.
# For example, hard resource limits is not restorable.
# If it is not acceptable, consider to create a child process using <code>spawn</code> or <code>system</code>.
# 
#    exec "echo *"       # echoes list of files in current directory
#    # never get here
# 
#    exec "echo", "*"    # echoes an asterisk
#    # never get here
def self.exec(env=0, command=0, options=0); end
##
# Creates a subprocess. If a block is specified, that block is run
# in the subprocess, and the subprocess terminates with a status of
# zero. Otherwise, the +fork+ call returns twice, once in
# the parent, returning the process ID of the child, and once in
# the child, returning _nil_. The child process can exit using
# <code>Kernel.exit!</code> to avoid running any
# <code>at_exit</code> functions. The parent process should
# use <code>Process.wait</code> to collect the termination statuses
# of its children or use <code>Process.detach</code> to register
# disinterest in their status; otherwise, the operating system
# may accumulate zombie processes.
# 
# The thread calling fork is the only thread in the created child process.
# fork doesn't copy other threads.
# 
# If fork is not usable, Process.respond_to?(:fork) returns false.
def self.fork; 1 || nil; end
##
# spawn executes specified command and return its pid.
# 
# This method doesn't wait for end of the command.
# The parent process should
# use <code>Process.wait</code> to collect
# the termination status of its child or
# use <code>Process.detach</code> to register
# disinterest in their status;
# otherwise, the operating system may accumulate zombie processes.
# 
# spawn has bunch of options to specify process attributes:
# 
#   env: hash
#     name => val : set the environment variable
#     name => nil : unset the environment variable
#   command...:
#     commandline                 : command line string which is passed to the standard shell
#     cmdname, arg1, ...          : command name and one or more arguments (no shell)
#     [cmdname, argv0], arg1, ... : command name, argv[0] and zero or more arguments (no shell)
#   options: hash
#     clearing environment variables:
#       :unsetenv_others => true   : clear environment variables except specified by env
#       :unsetenv_others => false  : don't clear (default)
#     process group:
#       :pgroup => true or 0 : make a new process group
#       :pgroup => pgid      : join to specified process group
#       :pgroup => nil       : don't change the process group (default)
#     create new process group: Windows only
#       :new_pgroup => true  : the new process is the root process of a new process group
#       :new_pgroup => false : don't create a new process group (default)
#     resource limit: resourcename is core, cpu, data, etc.  See Process.setrlimit.
#       :rlimit_resourcename => limit
#       :rlimit_resourcename => [cur_limit, max_limit]
#     umask:
#       :umask => int
#     redirection:
#       key:
#         FD              : single file descriptor in child process
#         [FD, FD, ...]   : multiple file descriptor in child process
#       value:
#         FD                        : redirect to the file descriptor in parent process
#         string                    : redirect to file with open(string, "r" or "w")
#         [string]                  : redirect to file with open(string, File::RDONLY)
#         [string, open_mode]       : redirect to file with open(string, open_mode, 0644)
#         [string, open_mode, perm] : redirect to file with open(string, open_mode, perm)
#         [:child, FD]              : redirect to the redirected file descriptor
#         :close                    : close the file descriptor in child process
#       FD is one of follows
#         :in     : the file descriptor 0 which is the standard input
#         :out    : the file descriptor 1 which is the standard output
#         :err    : the file descriptor 2 which is the standard error
#         integer : the file descriptor of specified the integer
#         io      : the file descriptor specified as io.fileno
#     file descriptor inheritance: close non-redirected non-standard fds (3, 4, 5, ...) or not
#       :close_others => true  : don't inherit
#     current directory:
#       :chdir => str
# 
# If a hash is given as +env+, the environment is
# updated by +env+ before <code>exec(2)</code> in the child process.
# If a pair in +env+ has nil as the value, the variable is deleted.
# 
#   # set FOO as BAR and unset BAZ.
#   pid = spawn({"FOO"=>"BAR", "BAZ"=>nil}, command)
# 
# If a hash is given as +options+,
# it specifies
# process group,
# create new process group,
# resource limit,
# current directory,
# umask and
# redirects for the child process.
# Also, it can be specified to clear environment variables.
# 
# The <code>:unsetenv_others</code> key in +options+ specifies
# to clear environment variables, other than specified by +env+.
# 
#   pid = spawn(command, :unsetenv_others=>true) # no environment variable
#   pid = spawn({"FOO"=>"BAR"}, command, :unsetenv_others=>true) # FOO only
# 
# The <code>:pgroup</code> key in +options+ specifies a process group.
# The corresponding value should be true, zero or positive integer.
# true and zero means the process should be a process leader of a new
# process group.
# Other values specifies a process group to be belongs.
# 
#   pid = spawn(command, :pgroup=>true) # process leader
#   pid = spawn(command, :pgroup=>10) # belongs to the process group 10
# 
# The <code>:new_pgroup</code> key in +options+ specifies to pass
# +CREATE_NEW_PROCESS_GROUP+ flag to <code>CreateProcessW()</code> that is
# Windows API. This option is only for Windows.
# true means the new process is the root process of the new process group.
# The new process has CTRL+C disabled. This flag is necessary for
# <code>Process.kill(:SIGINT, pid)</code> on the subprocess.
# :new_pgroup is false by default.
# 
#   pid = spawn(command, :new_pgroup=>true)  # new process group
#   pid = spawn(command, :new_pgroup=>false) # same process group
# 
# The <code>:rlimit_</code><em>foo</em> key specifies a resource limit.
# <em>foo</em> should be one of resource types such as <code>core</code>.
# The corresponding value should be an integer or an array which have one or
# two integers: same as cur_limit and max_limit arguments for
# Process.setrlimit.
# 
#   cur, max = Process.getrlimit(:CORE)
#   pid = spawn(command, :rlimit_core=>[0,max]) # disable core temporary.
#   pid = spawn(command, :rlimit_core=>max) # enable core dump
#   pid = spawn(command, :rlimit_core=>0) # never dump core.
# 
# The <code>:umask</code> key in +options+ specifies the umask.
# 
#   pid = spawn(command, :umask=>077)
# 
# The :in, :out, :err, a fixnum, an IO and an array key specifies a redirection.
# The redirection maps a file descriptor in the child process.
# 
# For example, stderr can be merged into stdout as follows:
# 
#   pid = spawn(command, :err=>:out)
#   pid = spawn(command, 2=>1)
#   pid = spawn(command, STDERR=>:out)
#   pid = spawn(command, STDERR=>STDOUT)
# 
# The hash keys specifies a file descriptor
# in the child process started by <code>spawn</code>.
# :err, 2 and STDERR specifies the standard error stream (stderr).
# 
# The hash values specifies a file descriptor
# in the parent process which invokes <code>spawn</code>.
# :out, 1 and STDOUT specifies the standard output stream (stdout).
# 
# In the above example,
# the standard output in the child process is not specified.
# So it is inherited from the parent process.
# 
# The standard input stream (stdin) can be specified by :in, 0 and STDIN.
# 
# A filename can be specified as a hash value.
# 
#   pid = spawn(command, :in=>"/dev/null") # read mode
#   pid = spawn(command, :out=>"/dev/null") # write mode
#   pid = spawn(command, :err=>"log") # write mode
#   pid = spawn(command, 3=>"/dev/null") # read mode
# 
# For stdout and stderr,
# it is opened in write mode.
# Otherwise read mode is used.
# 
# For specifying flags and permission of file creation explicitly,
# an array is used instead.
# 
#   pid = spawn(command, :in=>["file"]) # read mode is assumed
#   pid = spawn(command, :in=>["file", "r"])
#   pid = spawn(command, :out=>["log", "w"]) # 0644 assumed
#   pid = spawn(command, :out=>["log", "w", 0600])
#   pid = spawn(command, :out=>["log", File::WRONLY|File::EXCL|File::CREAT, 0600])
# 
# The array specifies a filename, flags and permission.
# The flags can be a string or an integer.
# If the flags is omitted or nil, File::RDONLY is assumed.
# The permission should be an integer.
# If the permission is omitted or nil, 0644 is assumed.
# 
# If an array of IOs and integers are specified as a hash key,
# all the elements are redirected.
# 
#   # stdout and stderr is redirected to log file.
#   # The file "log" is opened just once.
#   pid = spawn(command, [:out, :err]=>["log", "w"])
# 
# Another way to merge multiple file descriptors is [:child, fd].
# \[:child, fd] means the file descriptor in the child process.
# This is different from fd.
# For example, :err=>:out means redirecting child stderr to parent stdout.
# But :err=>[:child, :out] means redirecting child stderr to child stdout.
# They differ if stdout is redirected in the child process as follows.
# 
#   # stdout and stderr is redirected to log file.
#   # The file "log" is opened just once.
#   pid = spawn(command, :out=>["log", "w"], :err=>[:child, :out])
# 
# \[:child, :out] can be used to merge stderr into stdout in IO.popen.
# In this case, IO.popen redirects stdout to a pipe in the child process
# and [:child, :out] refers the redirected stdout.
# 
#   io = IO.popen(["sh", "-c", "echo out; echo err >&2", :err=>[:child, :out]])
#   p io.read #=> "out\nerr\n"
# 
# The <code>:chdir</code> key in +options+ specifies the current directory.
# 
#   pid = spawn(command, :chdir=>"/var/tmp")
# 
# spawn closes all non-standard unspecified descriptors by default.
# The "standard" descriptors are 0, 1 and 2.
# This behavior is specified by :close_others option.
# :close_others doesn't affect the standard descriptors which are
# closed only if :close is specified explicitly.
# 
#   pid = spawn(command, :close_others=>true)  # close 3,4,5,... (default)
#   pid = spawn(command, :close_others=>false) # don't close 3,4,5,...
# 
# :close_others is true by default for spawn and IO.popen.
# 
# Note that fds which close-on-exec flag is already set are closed
# regardless of :close_others option.
# 
# So IO.pipe and spawn can be used as IO.popen.
# 
#   # similar to r = IO.popen(command)
#   r, w = IO.pipe
#   pid = spawn(command, :out=>w)   # r, w is closed in the child process.
#   w.close
# 
# :close is specified as a hash value to close a fd individually.
# 
#   f = open(foo)
#   system(command, f=>:close)        # don't inherit f.
# 
# If a file descriptor need to be inherited,
# io=>io can be used.
# 
#   # valgrind has --log-fd option for log destination.
#   # log_w=>log_w indicates log_w.fileno inherits to child process.
#   log_r, log_w = IO.pipe
#   pid = spawn("valgrind", "--log-fd=#{log_w.fileno}", "echo", "a", log_w=>log_w)
#   log_w.close
#   p log_r.read
# 
# It is also possible to exchange file descriptors.
# 
#   pid = spawn(command, :out=>:err, :err=>:out)
# 
# The hash keys specify file descriptors in the child process.
# The hash values specifies file descriptors in the parent process.
# So the above specifies exchanging stdout and stderr.
# Internally, +spawn+ uses an extra file descriptor to resolve such cyclic
# file descriptor mapping.
# 
# See <code>Kernel.exec</code> for the standard shell.
def self.spawn(env=0, command=0, options=0); 0; end
##
# Exits the process immediately. No exit handlers are
# run. <em>status</em> is returned to the underlying system as the
# exit status.
# 
#    Process.exit!(true)
def self.exit!(status=false); end
##
# Initiates the termination of the Ruby script by raising the
# <code>SystemExit</code> exception. This exception may be caught. The
# optional parameter is used to return a status code to the invoking
# environment.
# +true+ and +FALSE+ of _status_ means success and failure
# respectively.  The interpretation of other integer values are
# system dependent.
# 
#    begin
#      exit
#      puts "never get here"
#    rescue SystemExit
#      puts "rescued a SystemExit exception"
#    end
#    puts "after begin block"
# 
# <em>produces:</em>
# 
#    rescued a SystemExit exception
#    after begin block
# 
# Just prior to termination, Ruby executes any <code>at_exit</code> functions
# (see Kernel::at_exit) and runs any object finalizers (see
# ObjectSpace::define_finalizer).
# 
#    at_exit { puts "at_exit function" }
#    ObjectSpace.define_finalizer("string",  proc { puts "in finalizer" })
#    exit
# 
# <em>produces:</em>
# 
#    at_exit function
#    in finalizer
def self.exit(status=true); end
##
# Terminate execution immediately, effectively by calling
# <code>Kernel.exit(false)</code>. If _msg_ is given, it is written
# to STDERR prior to terminating.
def self.abort; end
##
# Sends the given signal to the specified process id(s) if _pid_ is positive.
# If _pid_ is zero _signal_ is sent to all processes whose group ID is equal
# to the group ID of the process. _signal_ may be an integer signal number or
# a POSIX signal name (either with or without a +SIG+ prefix). If _signal_ is
# negative (or starts with a minus sign), kills process groups instead of
# processes. Not all signals are available on all platforms.
# 
#    pid = fork do
#       Signal.trap("HUP") { puts "Ouch!"; exit }
#       # ... do some work ...
#    end
#    # ...
#    Process.kill("HUP", pid)
#    Process.wait
# 
# <em>produces:</em>
# 
#    Ouch!
# 
# If _signal_ is an integer but wrong for signal,
# <code>Errno::EINVAL</code> or +RangeError+ will be raised.
# Otherwise unless _signal_ is a +String+ or a +Symbol+, and a known
# signal name, +ArgumentError+ will be raised.
# 
# Also, <code>Errno::ESRCH</code> or +RangeError+ for invalid _pid_,
# <code>Errno::EPERM</code> when failed because of no privilege,
# will be raised.  In these cases, signals may have been sent to
# preceding processes.
def self.kill(); 0; end
##
# Waits for a child process to exit, returns its process id, and
# sets <code>$?</code> to a <code>Process::Status</code> object
# containing information on that process. Which child it waits on
# depends on the value of _pid_:
# 
# > 0::   Waits for the child whose process ID equals _pid_.
# 
# 0::     Waits for any child whose process group ID equals that of the
#         calling process.
# 
# -1::    Waits for any child process (the default if no _pid_ is
#         given).
# 
# < -1::  Waits for any child whose process group ID equals the absolute
#         value of _pid_.
# 
# The _flags_ argument may be a logical or of the flag values
# <code>Process::WNOHANG</code> (do not block if no child available)
# or <code>Process::WUNTRACED</code> (return stopped children that
# haven't been reported). Not all flags are available on all
# platforms, but a flag value of zero will work on all platforms.
# 
# Calling this method raises a SystemCallError if there are no child
# processes. Not available on all platforms.
# 
#    include Process
#    fork { exit 99 }                 #=> 27429
#    wait                             #=> 27429
#    $?.exitstatus                    #=> 99
# 
#    pid = fork { sleep 3 }           #=> 27440
#    Time.now                         #=> 2008-03-08 19:56:16 +0900
#    waitpid(pid, Process::WNOHANG)   #=> nil
#    Time.now                         #=> 2008-03-08 19:56:16 +0900
#    waitpid(pid, 0)                  #=> 27440
#    Time.now                         #=> 2008-03-08 19:56:19 +0900
def self.wait(); 0; end
##
# Waits for a child process to exit, returns its process id, and
# sets <code>$?</code> to a <code>Process::Status</code> object
# containing information on that process. Which child it waits on
# depends on the value of _pid_:
# 
# > 0::   Waits for the child whose process ID equals _pid_.
# 
# 0::     Waits for any child whose process group ID equals that of the
#         calling process.
# 
# -1::    Waits for any child process (the default if no _pid_ is
#         given).
# 
# < -1::  Waits for any child whose process group ID equals the absolute
#         value of _pid_.
# 
# The _flags_ argument may be a logical or of the flag values
# <code>Process::WNOHANG</code> (do not block if no child available)
# or <code>Process::WUNTRACED</code> (return stopped children that
# haven't been reported). Not all flags are available on all
# platforms, but a flag value of zero will work on all platforms.
# 
# Calling this method raises a SystemCallError if there are no child
# processes. Not available on all platforms.
# 
#    include Process
#    fork { exit 99 }                 #=> 27429
#    wait                             #=> 27429
#    $?.exitstatus                    #=> 99
# 
#    pid = fork { sleep 3 }           #=> 27440
#    Time.now                         #=> 2008-03-08 19:56:16 +0900
#    waitpid(pid, Process::WNOHANG)   #=> nil
#    Time.now                         #=> 2008-03-08 19:56:16 +0900
#    waitpid(pid, 0)                  #=> 27440
#    Time.now                         #=> 2008-03-08 19:56:19 +0900
def self.waitpid(pid=-1, flags=0); 0; end
##
# Waits for a child process to exit (see Process::waitpid for exact
# semantics) and returns an array containing the process id and the
# exit status (a <code>Process::Status</code> object) of that
# child. Raises a SystemCallError if there are no child processes.
# 
#    Process.fork { exit 99 }   #=> 27437
#    pid, status = Process.wait2
#    pid                        #=> 27437
#    status.exitstatus          #=> 99
def self.wait2(pid=-1, flags=0); [1]; end
##
# Waits for a child process to exit (see Process::waitpid for exact
# semantics) and returns an array containing the process id and the
# exit status (a <code>Process::Status</code> object) of that
# child. Raises a SystemCallError if there are no child processes.
# 
#    Process.fork { exit 99 }   #=> 27437
#    pid, status = Process.wait2
#    pid                        #=> 27437
#    status.exitstatus          #=> 99
def self.waitpid2(pid=-1, flags=0); [1]; end
##
# Waits for all children, returning an array of
# _pid_/_status_ pairs (where _status_ is a
# <code>Process::Status</code> object).
# 
#    fork { sleep 0.2; exit 2 }   #=> 27432
#    fork { sleep 0.1; exit 1 }   #=> 27433
#    fork {            exit 0 }   #=> 27434
#    p Process.waitall
# 
# <em>produces</em>:
# 
#    [[30982, #<Process::Status: pid 30982 exit 0>],
#     [30979, #<Process::Status: pid 30979 exit 1>],
#     [30976, #<Process::Status: pid 30976 exit 2>]]
def self.waitall; []; end
##
# Some operating systems retain the status of terminated child
# processes until the parent collects that status (normally using
# some variant of <code>wait()</code>. If the parent never collects
# this status, the child stays around as a <em>zombie</em> process.
# <code>Process::detach</code> prevents this by setting up a
# separate Ruby thread whose sole job is to reap the status of the
# process _pid_ when it terminates. Use <code>detach</code>
# only when you do not intent to explicitly wait for the child to
# terminate.
# 
# The waiting thread returns the exit status of the detached process
# when it terminates, so you can use <code>Thread#join</code> to
# know the result.  If specified _pid_ is not a valid child process
# ID, the thread returns +nil+ immediately.
# 
# The waiting thread has <code>pid</code> method which returns the pid.
# 
# In this first example, we don't reap the first child process, so
# it appears as a zombie in the process status display.
# 
#    p1 = fork { sleep 0.1 }
#    p2 = fork { sleep 0.2 }
#    Process.waitpid(p2)
#    sleep 2
#    system("ps -ho pid,state -p #{p1}")
# 
# <em>produces:</em>
# 
#    27389 Z
# 
# In the next example, <code>Process::detach</code> is used to reap
# the child automatically.
# 
#    p1 = fork { sleep 0.1 }
#    p2 = fork { sleep 0.2 }
#    Process.detach(p1)
#    Process.waitpid(p2)
#    sleep 2
#    system("ps -ho pid,state -p #{p1}")
# 
# <em>(produces no output)</em>
def self.detach(pid); Thread.new; end
##
# Returns the process id of this process. Not available on all
# platforms.
# 
#    Process.pid   #=> 27415
def self.pid; 0; end
##
# Returns the process id of the parent of this process. Returns
# untrustworthy value on Win32/64. Not available on all platforms.
# 
#    puts "I am #{Process.pid}"
#    Process.fork { puts "Dad is #{Process.ppid}" }
# 
# <em>produces:</em>
# 
#    I am 27417
#    Dad is 27417
def self.ppid; 0; end
##
# Returns the process group ID for this process. Not available on
# all platforms.
# 
#    Process.getpgid(0)   #=> 25527
#    Process.getpgrp      #=> 25527
def self.getpgrp; 0; end
##
# Equivalent to <code>setpgid(0,0)</code>. Not available on all
# platforms.
def self.setpgrp; 0; end
##
# Returns the process group ID for the given process id. Not
# available on all platforms.
# 
#    Process.getpgid(Process.ppid())   #=> 25527
def self.getpgid(pid); 0; end
##
# Sets the process group ID of _pid_ (0 indicates this
# process) to <em>integer</em>. Not available on all platforms.
def self.setpgid(pid, integer); 0; end
##
# Returns the session ID for for the given process id. If not give,
# return current process sid. Not available on all platforms.
# 
#    Process.getsid()                #=> 27422
#    Process.getsid(0)               #=> 27422
#    Process.getsid(Process.pid())   #=> 27422
def self.getsid(); 0; end
##
# Establishes this process as a new session and process group
# leader, with no controlling tty. Returns the session id. Not
# available on all platforms.
# 
#    Process.setsid   #=> 27422
def self.setsid; 0; end
##
# Gets the scheduling priority for specified process, process group,
# or user. <em>kind</em> indicates the kind of entity to find: one
# of <code>Process::PRIO_PGRP</code>,
# <code>Process::PRIO_USER</code>, or
# <code>Process::PRIO_PROCESS</code>. _integer_ is an id
# indicating the particular process, process group, or user (an id
# of 0 means _current_). Lower priorities are more favorable
# for scheduling. Not available on all platforms.
# 
#    Process.getpriority(Process::PRIO_USER, 0)      #=> 19
#    Process.getpriority(Process::PRIO_PROCESS, 0)   #=> 19
def self.getpriority(kind, integer); 0; end
##
# See <code>Process#getpriority</code>.
# 
#    Process.setpriority(Process::PRIO_USER, 0, 19)      #=> 0
#    Process.setpriority(Process::PRIO_PROCESS, 0, 19)   #=> 0
#    Process.getpriority(Process::PRIO_USER, 0)          #=> 19
#    Process.getpriority(Process::PRIO_PROCESS, 0)       #=> 19
def self.setpriority(kind, integer, priority); 0; end
##
# Gets the resource limit of the process.
# _cur_limit_ means current (soft) limit and
# _max_limit_ means maximum (hard) limit.
# 
# _resource_ indicates the kind of resource to limit.
# It is specified as a symbol such as <code>:CORE</code>,
# a string such as <code>"CORE"</code> or
# a constant such as <code>Process::RLIMIT_CORE</code>.
# See Process.setrlimit for details.
# 
# _cur_limit_ and _max_limit_ may be <code>Process::RLIM_INFINITY</code>,
# <code>Process::RLIM_SAVED_MAX</code> or
# <code>Process::RLIM_SAVED_CUR</code>.
# See Process.setrlimit and the system getrlimit(2) manual for details.
def self.getrlimit(resource); []; end
##
# Sets the resource limit of the process.
# _cur_limit_ means current (soft) limit and
# _max_limit_ means maximum (hard) limit.
# 
# If _max_limit_ is not given, _cur_limit_ is used.
# 
# _resource_ indicates the kind of resource to limit.
# It should be a symbol such as <code>:CORE</code>,
# a string such as <code>"CORE"</code> or
# a constant such as <code>Process::RLIMIT_CORE</code>.
# The available resources are OS dependent.
# Ruby may support following resources.
# 
# [AS] total available memory (bytes) (SUSv3, NetBSD, FreeBSD, OpenBSD but 4.4BSD-Lite)
# [CORE] core size (bytes) (SUSv3)
# [CPU] CPU time (seconds) (SUSv3)
# [DATA] data segment (bytes) (SUSv3)
# [FSIZE] file size (bytes) (SUSv3)
# [MEMLOCK] total size for mlock(2) (bytes) (4.4BSD, GNU/Linux)
# [MSGQUEUE] allocation for POSIX message queues (bytes) (GNU/Linux)
# [NICE] ceiling on process's nice(2) value (number) (GNU/Linux)
# [NOFILE] file descriptors (number) (SUSv3)
# [NPROC] number of processes for the user (number) (4.4BSD, GNU/Linux)
# [RSS] resident memory size (bytes) (4.2BSD, GNU/Linux)
# [RTPRIO] ceiling on the process's real-time priority (number) (GNU/Linux)
# [RTTIME] CPU time for real-time process (us) (GNU/Linux)
# [SBSIZE] all socket buffers (bytes) (NetBSD, FreeBSD)
# [SIGPENDING] number of queued signals allowed (signals) (GNU/Linux)
# [STACK] stack size (bytes) (SUSv3)
# 
# _cur_limit_ and _max_limit_ may be
# <code>:INFINITY</code>, <code>"INFINITY"</code> or
# <code>Process::RLIM_INFINITY</code>,
# which means that the resource is not limited.
# They may be <code>Process::RLIM_SAVED_MAX</code>,
# <code>Process::RLIM_SAVED_CUR</code> and
# corresponding symbols and strings too.
# See system setrlimit(2) manual for details.
# 
# The following example raises the soft limit of core size to
# the hard limit to try to make core dump possible.
# 
#   Process.setrlimit(:CORE, Process.getrlimit(:CORE)[1])
def self.setrlimit(resource, cur_limit, max_limit); end
##
# Returns the (real) user ID of this process.
# 
#    Process.uid   #=> 501
def self.uid; 0; end
##
# Returns the (real) user ID of this process.
# 
#    Process.uid   #=> 501
def self.rid; 0; end
##
# Returns the (real) user ID of this process.
# 
#    Process.uid   #=> 501
def self.getuid; 0; end
##
# Sets the (user) user ID for this process. Not available on all
# platforms.
def self.uid= user; 0; end
##
# Returns the (real) group ID for this process.
# 
#    Process.gid   #=> 500
def self.gid; 0; end
##
# Returns the (real) group ID for this process.
# 
#    Process.gid   #=> 500
def self.getgid; 0; end
##
# Sets the group ID for this process.
def self.gid= fixnum; 0; end
##
# Returns the effective user ID for this process.
# 
#    Process.euid   #=> 501
def self.euid; 0; end
##
# Returns the effective user ID for this process.
# 
#    Process.euid   #=> 501
def self.eid; 0; end
##
# Returns the effective user ID for this process.
# 
#    Process.euid   #=> 501
def self.geteuid; 0; end
##
# Sets the effective user ID for this process. Not available on all
# platforms.
def self.euid= user; end
##
# Returns the effective group ID for this process. Not available on
# all platforms.
# 
#    Process.egid   #=> 500
def self.egid; 0; end
##
# Returns the effective group ID for this process. Not available on
# all platforms.
# 
#    Process.egid   #=> 500
def self.geteid; 0; end
##
# Sets the effective group ID for this process. Not available on all
# platforms.
def self.egid= fixnum; 0; end
##
# Initializes the supplemental group access list by reading the
# system group database and using all groups of which the given user
# is a member. The group with the specified <em>gid</em> is also
# added to the list. Returns the resulting <code>Array</code> of the
# gids of all the groups in the supplementary group access list. Not
# available on all platforms.
# 
#    Process.groups   #=> [0, 1, 2, 3, 4, 6, 10, 11, 20, 26, 27]
#    Process.initgroups( "mgranger", 30 )   #=> [30, 6, 10, 11]
#    Process.groups   #=> [30, 6, 10, 11]
def self.initgroups(username, gid); []; end
##
# Get an <code>Array</code> of the gids of groups in the
# supplemental group access list for this process.
# 
#    Process.groups   #=> [27, 6, 10, 11]
def self.groups; []; end
##
# Set the supplemental group access list to the given
# <code>Array</code> of group IDs.
# 
#    Process.groups   #=> [0, 1, 2, 3, 4, 6, 10, 11, 20, 26, 27]
#    Process.groups = [27, 6, 10, 11]   #=> [27, 6, 10, 11]
#    Process.groups   #=> [27, 6, 10, 11]
def self.groups= array; []; end
##
# Returns the maximum number of gids allowed in the supplemental
# group access list.
# 
#    Process.maxgroups   #=> 32
def self.maxgroups; 0; end
##
# Sets the maximum number of gids allowed in the supplemental group
# access list.
def self.maxgroups= fixnum; 0; end
##
# Detach the process from controlling terminal and run in
# the background as system daemon.  Unless the argument
# nochdir is true (i.e. non false), it changes the current
# working directory to the root ("/"). Unless the argument
# noclose is true, daemon() will redirect standard input,
# standard output and standard error to /dev/null.
# Return zero on success, or raise one of Errno::*.
def self.daemon(); 0; end
##
# Returns a <code>Tms</code> structure (see <code>Struct::Tms</code>)
# that contains user and system CPU times for this process,
# and also for children processes.
# 
#    t = Process.times
#    [ t.utime, t.stime, t.cutime, t.cstime ]   #=> [0.0, 0.02, 0.00, 0.00]
def self.times; Struct::Tms.new; end
end

##
# Many operating systems allow signals to be sent to running
# processes. Some signals have a defined effect on the process, while
# others may be trapped at the code level and acted upon. For
# example, your process may trap the USR1 signal and use it to toggle
# debugging, and may use TERM to initiate a controlled shutdown.
# 
#     pid = fork do
#       Signal.trap("USR1") do
#         $debug = !$debug
#         puts "Debug now: #$debug"
#       end
#       Signal.trap("TERM") do
#         puts "Terminating..."
#         shutdown()
#       end
#       # . . . do some work . . .
#     end
# 
#     Process.detach(pid)
# 
#     # Controlling program:
#     Process.kill("USR1", pid)
#     # ...
#     Process.kill("USR1", pid)
#     # ...
#     Process.kill("TERM", pid)
# 
# produces:
#     Debug now: true
#     Debug now: false
#    Terminating...
# 
# The list of available signal names and their interpretation is
# system dependent. Signal delivery semantics may also vary between
# systems; in particular signal delivery may not always be reliable.
module Signal
##
# Specifies the handling of signals. The first parameter is a signal
# name (a string such as ``SIGALRM'', ``SIGUSR1'', and so on) or a
# signal number. The characters ``SIG'' may be omitted from the
# signal name. The command or block specifies code to be run when the
# signal is raised.
# If the command is the string ``IGNORE'' or ``SIG_IGN'', the signal
# will be ignored.
# If the command is ``DEFAULT'' or ``SIG_DFL'', the Ruby's default handler
# will be invoked.
# If the command is ``EXIT'', the script will be terminated by the signal.
# If the command is ``SYSTEM_DEFAULT'', the operating system's default
# handler will be invoked.
# Otherwise, the given command or block will be run.
# The special signal name ``EXIT'' or signal number zero will be
# invoked just prior to program termination.
# trap returns the previous handler for the given signal.
# 
#     Signal.trap(0, proc { puts "Terminating: #{$$}" })
#     Signal.trap("CLD")  { puts "Child died" }
#     fork && Process.wait
# 
# produces:
#     Terminating: 27461
#     Child died
#     Terminating: 27460
def self.trap( signal, command ); Object.new; end
##
# Returns a list of signal names mapped to the corresponding
# underlying signal numbers.
# 
#   Signal.list   #=> {"EXIT"=>0, "HUP"=>1, "INT"=>2, "QUIT"=>3, "ILL"=>4, "TRAP"=>5, "IOT"=>6, "ABRT"=>6, "FPE"=>8, "KILL"=>9, "BUS"=>7, "SEGV"=>11, "SYS"=>31, "PIPE"=>13, "ALRM"=>14, "TERM"=>15, "URG"=>23, "STOP"=>19, "TSTP"=>20, "CONT"=>18, "CHLD"=>17, "CLD"=>17, "TTIN"=>21, "TTOU"=>22, "IO"=>29, "XCPU"=>24, "XFSZ"=>25, "VTALRM"=>26, "PROF"=>27, "WINCH"=>28, "USR1"=>10, "USR2"=>12, "PWR"=>30, "POLL"=>29}
def self.list; {}; end
##
# convert signal number to signal name
# 
#    Signal.trap("INT") { |signo| puts Signal.signame(signo) }
#    Process.kill("INT", 0)
# 
# <em>produces:</em>
# 
#    INT
def self.signame(signo); ''; end
end

module Enumerable
##
# Returns a lazy enumerator, whose methods map/collect,
# flat_map/collect_concat, select/find_all, reject, grep, zip, take,
# take_while, drop, drop_while, and cycle enumerate values only on an
# as-needed basis.  However, if a block is given to zip or cycle, values
# are enumerated immediately.
# 
# === Example
# 
# The following program finds pythagorean triples:
# 
#   def pythagorean_triples
#     (1..Float::INFINITY).lazy.flat_map {|z|
#       (1..z).flat_map {|x|
#         (x..z).select {|y|
#           x**2 + y**2 == z**2
#         }.map {|y|
#           [x, y, z]
#         }
#       }
#     }
#   end
#   # show first ten pythagorean triples
#   p pythagorean_triples.take(10).force # take is lazy, so force is needed
#   p pythagorean_triples.first(10)      # first is eager
#   # show pythagorean triples less than 100
#   p pythagorean_triples.take_while { |*, z| z < 100 }.force
def lazy; Enumerator::Lazy.new; end
##
# Returns an array containing the items in <i>enum</i>.
# 
#    (1..7).to_a                       #=> [1, 2, 3, 4, 5, 6, 7]
#    { 'a'=>1, 'b'=>2, 'c'=>3 }.to_a   #=> [["a", 1], ["b", 2], ["c", 3]]
def to_a; []; end
##
# Returns an array containing the items in <i>enum</i>.
# 
#    (1..7).to_a                       #=> [1, 2, 3, 4, 5, 6, 7]
#    { 'a'=>1, 'b'=>2, 'c'=>3 }.to_a   #=> [["a", 1], ["b", 2], ["c", 3]]
def entries; []; end
##
# Returns an array containing the items in <i>enum</i> sorted,
# either according to their own <code><=></code> method, or by using
# the results of the supplied block. The block should return -1, 0, or
# +1 depending on the comparison between <i>a</i> and <i>b</i>. As of
# Ruby 1.8, the method <code>Enumerable#sort_by</code> implements a
# built-in Schwartzian Transform, useful when key computation or
# comparison is expensive.
# 
#    %w(rhea kea flea).sort          #=> ["flea", "kea", "rhea"]
#    (1..10).sort { |a, b| b <=> a }  #=> [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]
def sort; []; end
##
# Sorts <i>enum</i> using a set of keys generated by mapping the
# values in <i>enum</i> through the given block.
# 
# If no block is given, an enumerator is returned instead.
# 
#    %w{apple pear fig}.sort_by { |word| word.length}
#                  #=> ["fig", "pear", "apple"]
# 
# The current implementation of <code>sort_by</code> generates an
# array of tuples containing the original collection element and the
# mapped value. This makes <code>sort_by</code> fairly expensive when
# the keysets are simple.
# 
#    require 'benchmark'
# 
#    a = (1..100000).map { rand(100000) }
# 
#    Benchmark.bm(10) do |b|
#      b.report("Sort")    { a.sort }
#      b.report("Sort by") { a.sort_by { |a| a } }
#    end
# 
# <em>produces:</em>
# 
#    user     system      total        real
#    Sort        0.180000   0.000000   0.180000 (  0.175469)
#    Sort by     1.980000   0.040000   2.020000 (  2.013586)
# 
# However, consider the case where comparing the keys is a non-trivial
# operation. The following code sorts some files on modification time
# using the basic <code>sort</code> method.
# 
#    files = Dir["*"]
#    sorted = files.sort { |a, b| File.new(a).mtime <=> File.new(b).mtime }
#    sorted   #=> ["mon", "tues", "wed", "thurs"]
# 
# This sort is inefficient: it generates two new <code>File</code>
# objects during every comparison. A slightly better technique is to
# use the <code>Kernel#test</code> method to generate the modification
# times directly.
# 
#    files = Dir["*"]
#    sorted = files.sort { |a, b|
#      test(?M, a) <=> test(?M, b)
#    }
#    sorted   #=> ["mon", "tues", "wed", "thurs"]
# 
# This still generates many unnecessary <code>Time</code> objects. A
# more efficient technique is to cache the sort keys (modification
# times in this case) before the sort. Perl users often call this
# approach a Schwartzian Transform, after Randal Schwartz. We
# construct a temporary array, where each element is an array
# containing our sort key along with the filename. We sort this array,
# and then extract the filename from the result.
# 
#    sorted = Dir["*"].collect { |f|
#       [test(?M, f), f]
#    }.sort.collect { |f| f[1] }
#    sorted   #=> ["mon", "tues", "wed", "thurs"]
# 
# This is exactly what <code>sort_by</code> does internally.
# 
#    sorted = Dir["*"].sort_by { |f| test(?M, f) }
#    sorted   #=> ["mon", "tues", "wed", "thurs"]
def sort_by(&block); Enumerator.new; end
##
# Returns an array of every element in <i>enum</i> for which
# <code>Pattern === element</code>. If the optional <em>block</em> is
# supplied, each matching element is passed to it, and the block's
# result is stored in the output array.
# 
#    (1..100).grep 38..44   #=> [38, 39, 40, 41, 42, 43, 44]
#    c = IO.constants
#    c.grep(/SEEK/)         #=> [:SEEK_SET, :SEEK_CUR, :SEEK_END]
#    res = c.grep(/SEEK/) { |v| IO.const_get(v) }
#    res                    #=> [0, 1, 2]
def grep(pattern); []; end
##
# Returns the number of items in +enum+ through enumeration.
# If an argument is given, the number of items in +enum+ that
# are equal to +item+ are counted.  If a block is given, it
# counts the number of elements yielding a true value.
# 
#    ary = [1, 2, 4, 2]
#    ary.count               #=> 4
#    ary.count(2)            #=> 2
#    ary.count{ |x| x%2==0 } #=> 3
def count; 0; end
##
# Passes each entry in <i>enum</i> to <em>block</em>. Returns the
# first for which <em>block</em> is not false.  If no
# object matches, calls <i>ifnone</i> and returns its result when it
# is specified, or returns <code>nil</code> otherwise.
# 
# If no block is given, an enumerator is returned instead.
# 
#    (1..10).detect  { |i| i % 5 == 0 and i % 7 == 0 }   #=> nil
#    (1..100).detect { |i| i % 5 == 0 and i % 7 == 0 }   #=> 35
def detect(ifnone = null, &block); Enumerator.new; end
##
# Passes each entry in <i>enum</i> to <em>block</em>. Returns the
# first for which <em>block</em> is not false.  If no
# object matches, calls <i>ifnone</i> and returns its result when it
# is specified, or returns <code>nil</code> otherwise.
# 
# If no block is given, an enumerator is returned instead.
# 
#    (1..10).detect  { |i| i % 5 == 0 and i % 7 == 0 }   #=> nil
#    (1..100).detect { |i| i % 5 == 0 and i % 7 == 0 }   #=> 35
def find(ifnone = null, &block); Enumerator.new; end
##
# Compares each entry in <i>enum</i> with <em>value</em> or passes
# to <em>block</em>.  Returns the index for the first for which the
# evaluated value is non-false.  If no object matches, returns
# <code>nil</code>
# 
# If neither block nor argument is given, an enumerator is returned instead.
# 
#    (1..10).find_index  { |i| i % 5 == 0 and i % 7 == 0 }  #=> nil
#    (1..100).find_index { |i| i % 5 == 0 and i % 7 == 0 }  #=> 34
#    (1..100).find_index(50)                                #=> 49
def find_index(value); Enumerator.new; end
##
# Returns an array containing all elements of +enum+
# for which the given +block+ returns a true value.
# 
# If no block is given, an Enumerator is returned instead.
# 
#    (1..10).find_all { |i|  i % 3 == 0 }   #=> [3, 6, 9]
# 
#    [1,2,3,4,5].select { |num|  num.even?  }   #=> [2, 4]
# 
# See also Enumerable#reject.
def find_all(&block); Enumerator.new; end
##
# Returns an array containing all elements of +enum+
# for which the given +block+ returns a true value.
# 
# If no block is given, an Enumerator is returned instead.
# 
#    (1..10).find_all { |i|  i % 3 == 0 }   #=> [3, 6, 9]
# 
#    [1,2,3,4,5].select { |num|  num.even?  }   #=> [2, 4]
# 
# See also Enumerable#reject.
def select(&block); Enumerator.new; end
##
# Returns an array for all elements of +enum+ for which the given
# +block+ returns false.
# 
# If no block is given, an Enumerator is returned instead.
# 
#    (1..10).reject { |i|  i % 3 == 0 }   #=> [1, 2, 4, 5, 7, 8, 10]
# 
#    [1, 2, 3, 4, 5].reject { |num| num.even? } #=> [1, 3, 5]
# 
# See also Enumerable#find_all.
def reject(&block); Enumerator.new; end
##
# Returns a new array with the results of running <em>block</em> once
# for every element in <i>enum</i>.
# 
# If no block is given, an enumerator is returned instead.
# 
#    (1..4).collect { |i| i*i }  #=> [1, 4, 9, 16]
#    (1..4).collect { "cat"  }   #=> ["cat", "cat", "cat", "cat"]
def collect(&block); Enumerator.new; end
##
# Returns a new array with the results of running <em>block</em> once
# for every element in <i>enum</i>.
# 
# If no block is given, an enumerator is returned instead.
# 
#    (1..4).collect { |i| i*i }  #=> [1, 4, 9, 16]
#    (1..4).collect { "cat"  }   #=> ["cat", "cat", "cat", "cat"]
def map(&block); Enumerator.new; end
##
# Returns a new array with the concatenated results of running
# <em>block</em> once for every element in <i>enum</i>.
# 
# If no block is given, an enumerator is returned instead.
# 
#    [1, 2, 3, 4].flat_map { |e| [e, -e] } #=> [1, -1, 2, -2, 3, -3, 4, -4]
#    [[1, 2], [3, 4]].flat_map { |e| e + [100] } #=> [1, 2, 100, 3, 4, 100]
def flat_map(&block); Enumerator.new; end
##
# Returns a new array with the concatenated results of running
# <em>block</em> once for every element in <i>enum</i>.
# 
# If no block is given, an enumerator is returned instead.
# 
#    [1, 2, 3, 4].flat_map { |e| [e, -e] } #=> [1, -1, 2, -2, 3, -3, 4, -4]
#    [[1, 2], [3, 4]].flat_map { |e| e + [100] } #=> [1, 2, 100, 3, 4, 100]
def collect_concat(&block); Enumerator.new; end
##
# Combines all elements of <i>enum</i> by applying a binary
# operation, specified by a block or a symbol that names a
# method or operator.
# 
# If you specify a block, then for each element in <i>enum</i>
# the block is passed an accumulator value (<i>memo</i>) and the element.
# If you specify a symbol instead, then each element in the collection
# will be passed to the named method of <i>memo</i>.
# In either case, the result becomes the new value for <i>memo</i>.
# At the end of the iteration, the final value of <i>memo</i> is the
# return value for the method.
# 
# If you do not explicitly specify an <i>initial</i> value for <i>memo</i>,
# then the first element of collection is used as the initial value
# of <i>memo</i>.
# 
#    # Sum some numbers
#    (5..10).reduce(:+)                             #=> 45
#    # Same using a block and inject
#    (5..10).inject { |sum, n| sum + n }            #=> 45
#    # Multiply some numbers
#    (5..10).reduce(1, :*)                          #=> 151200
#    # Same using a block
#    (5..10).inject(1) { |product, n| product * n } #=> 151200
#    # find the longest word
#    longest = %w{ cat sheep bear }.inject do |memo, word|
#       memo.length > word.length ? memo : word
#    end
#    longest                                        #=> "sheep"
def inject(initial, sym); Object.new; end
##
# Combines all elements of <i>enum</i> by applying a binary
# operation, specified by a block or a symbol that names a
# method or operator.
# 
# If you specify a block, then for each element in <i>enum</i>
# the block is passed an accumulator value (<i>memo</i>) and the element.
# If you specify a symbol instead, then each element in the collection
# will be passed to the named method of <i>memo</i>.
# In either case, the result becomes the new value for <i>memo</i>.
# At the end of the iteration, the final value of <i>memo</i> is the
# return value for the method.
# 
# If you do not explicitly specify an <i>initial</i> value for <i>memo</i>,
# then the first element of collection is used as the initial value
# of <i>memo</i>.
# 
#    # Sum some numbers
#    (5..10).reduce(:+)                             #=> 45
#    # Same using a block and inject
#    (5..10).inject { |sum, n| sum + n }            #=> 45
#    # Multiply some numbers
#    (5..10).reduce(1, :*)                          #=> 151200
#    # Same using a block
#    (5..10).inject(1) { |product, n| product * n } #=> 151200
#    # find the longest word
#    longest = %w{ cat sheep bear }.inject do |memo, word|
#       memo.length > word.length ? memo : word
#    end
#    longest                                        #=> "sheep"
def reduce(initial, sym); Object.new; end
##
# Returns two arrays, the first containing the elements of
# <i>enum</i> for which the block evaluates to true, the second
# containing the rest.
# 
# If no block is given, an enumerator is returned instead.
# 
#    (1..6).partition { |v| v.even? }  #=> [[2, 4, 6], [1, 3, 5]]
def partition(&block); Enumerator.new; end
##
# Groups the collection by result of the block.  Returns a hash where the
# keys are the evaluated result from the block and the values are
# arrays of elements in the collection that correspond to the key.
# 
# If no block is given an enumerator is returned.
# 
#    (1..6).group_by { |i| i%3 }   #=> {0=>[3, 6], 1=>[1, 4], 2=>[2, 5]}
def group_by(&block); Enumerator.new; end
##
# Returns the first element, or the first +n+ elements, of the enumerable.
# If the enumerable is empty, the first form returns <code>nil</code>, and the
# second form returns an empty array.
# 
#   %w[foo bar baz].first     #=> "foo"
#   %w[foo bar baz].first(2)  #=> ["foo", "bar"]
#   %w[foo bar baz].first(10) #=> ["foo", "bar", "baz"]
#   [].first                  #=> nil
def first; []; end
##
# Passes each element of the collection to the given block. The method
# returns <code>true</code> if the block never returns
# <code>false</code> or <code>nil</code>. If the block is not given,
# Ruby adds an implicit block of <code>{ |obj| obj }</code> which will
# cause #all? to return +true+ when none of the collection members are
# +false+ or +nil+.
# 
#    %w[ant bear cat].all? { |word| word.length >= 3 } #=> true
#    %w[ant bear cat].all? { |word| word.length >= 4 } #=> false
#    [nil, true, 99].all?                              #=> false
def all?; true || false; end
##
# Passes each element of the collection to the given block. The method
# returns <code>true</code> if the block ever returns a value other
# than <code>false</code> or <code>nil</code>. If the block is not
# given, Ruby adds an implicit block of <code>{ |obj| obj }</code> that
# will cause #any? to return +true+ if at least one of the collection
# members is not +false+ or +nil+.
# 
#    %w[ant bear cat].any? { |word| word.length >= 3 } #=> true
#    %w[ant bear cat].any? { |word| word.length >= 4 } #=> true
#    [nil, true, 99].any?                              #=> true
def any?; true || false; end
##
# Passes each element of the collection to the given block. The method
# returns <code>true</code> if the block returns <code>true</code>
# exactly once. If the block is not given, <code>one?</code> will return
# <code>true</code> only if exactly one of the collection members is
# true.
# 
#    %w{ant bear cat}.one? { |word| word.length == 4 }  #=> true
#    %w{ant bear cat}.one? { |word| word.length > 4 }   #=> false
#    %w{ant bear cat}.one? { |word| word.length < 4 }   #=> false
#    [ nil, true, 99 ].one?                             #=> false
#    [ nil, true, false ].one?                          #=> true
def one?; true || false; end
##
# Passes each element of the collection to the given block. The method
# returns <code>true</code> if the block never returns <code>true</code>
# for all elements. If the block is not given, <code>none?</code> will return
# <code>true</code> only if none of the collection members is true.
# 
#    %w{ant bear cat}.none? { |word| word.length == 5 } #=> true
#    %w{ant bear cat}.none? { |word| word.length >= 4 } #=> false
#    [].none?                                           #=> true
#    [nil].none?                                        #=> true
#    [nil, false].none?                                 #=> true
def none?; true || false; end
##
# Returns the object in <i>enum</i> with the minimum value. The
# first form assumes all objects implement <code>Comparable</code>;
# the second uses the block to return <em>a <=> b</em>.
# 
#    a = %w(albatross dog horse)
#    a.min                                   #=> "albatross"
#    a.min { |a, b| a.length <=> b.length }  #=> "dog"
def min; Object.new; end
##
# Returns the object in _enum_ with the maximum value. The
# first form assumes all objects implement <code>Comparable</code>;
# the second uses the block to return <em>a <=> b</em>.
# 
#    a = %w(albatross dog horse)
#    a.max                                   #=> "horse"
#    a.max { |a, b| a.length <=> b.length }  #=> "albatross"
def max; Object.new; end
##
# Returns two elements array which contains the minimum and the
# maximum value in the enumerable.  The first form assumes all
# objects implement <code>Comparable</code>; the second uses the
# block to return <em>a <=> b</em>.
# 
#    a = %w(albatross dog horse)
#    a.minmax                                  #=> ["albatross", "horse"]
#    a.minmax { |a, b| a.length <=> b.length } #=> ["dog", "albatross"]
def minmax; []; end
##
# Returns the object in <i>enum</i> that gives the minimum
# value from the given block.
# 
# If no block is given, an enumerator is returned instead.
# 
#    a = %w(albatross dog horse)
#    a.min_by { |x| x.length }   #=> "dog"
def min_by(&block); Enumerator.new; end
##
# Returns the object in <i>enum</i> that gives the maximum
# value from the given block.
# 
# If no block is given, an enumerator is returned instead.
# 
#    a = %w(albatross dog horse)
#    a.max_by { |x| x.length }   #=> "albatross"
def max_by(&block); Enumerator.new; end
##
# Returns a two element array containing the objects in
# <i>enum</i> that correspond to the minimum and maximum values respectively
# from the given block.
# 
# If no block is given, an enumerator is returned instead.
# 
#    a = %w(albatross dog horse)
#    a.minmax_by { |x| x.length }   #=> ["dog", "albatross"]
def minmax_by(&block); Enumerator.new; end
##
# Returns <code>true</code> if any member of <i>enum</i> equals
# <i>obj</i>. Equality is tested using <code>==</code>.
# 
#    IO.constants.include? :SEEK_SET          #=> true
#    IO.constants.include? :SEEK_NO_FURTHER   #=> false
def include?(obj); true || false; end
##
# Returns <code>true</code> if any member of <i>enum</i> equals
# <i>obj</i>. Equality is tested using <code>==</code>.
# 
#    IO.constants.include? :SEEK_SET          #=> true
#    IO.constants.include? :SEEK_NO_FURTHER   #=> false
def member?(obj); true || false; end
##
# Calls <em>block</em> with two arguments, the item and its index,
# for each item in <i>enum</i>.  Given arguments are passed through
# to #each().
# 
# If no block is given, an enumerator is returned instead.
# 
#    hash = Hash.new
#    %w(cat dog wombat).each_with_index { |item, index|
#      hash[item] = index
#    }
#    hash   #=> {"cat"=>0, "dog"=>1, "wombat"=>2}
def each_with_index(); Enumerator.new; end
##
# Builds a temporary array and traverses that array in reverse order.
# 
# If no block is given, an enumerator is returned instead.
# 
#     (1..3).reverse_each { |v| p v }
# 
#   produces:
# 
#     3
#     2
#     1
def reverse_each(); Enumerator.new; end
##
# Calls <i>block</i> once for each element in +self+, passing that
# element as a parameter, converting multiple values from yield to an
# array.
# 
# If no block is given, an enumerator is returned instead.
# 
#    class Foo
#      include Enumerable
#      def each
#        yield 1
#        yield 1, 2
#        yield
#      end
#    end
#    Foo.new.each_entry{ |o| p o }
# 
# produces:
# 
#    1
#    [1, 2]
#    nil
def each_entry(&block); Enumerator.new; end
##
# Iterates the given block for each slice of <n> elements.  If no
# block is given, returns an enumerator.
# 
#     (1..10).each_slice(3) { |a| p a }
#     # outputs below
#     [1, 2, 3]
#     [4, 5, 6]
#     [7, 8, 9]
#     [10]
def each_slice(n, &block); Enumerator.new; end
##
# Iterates the given block for each array of consecutive <n>
# elements.  If no block is given, returns an enumerator.
# 
# e.g.:
#     (1..10).each_cons(3) { |a| p a }
#     # outputs below
#     [1, 2, 3]
#     [2, 3, 4]
#     [3, 4, 5]
#     [4, 5, 6]
#     [5, 6, 7]
#     [6, 7, 8]
#     [7, 8, 9]
#     [8, 9, 10]
def each_cons(n, &block); Enumerator.new; end
##
# Iterates the given block for each element with an arbitrary
# object given, and returns the initially given object.
# 
# If no block is given, returns an enumerator.
# 
#     evens = (1..10).each_with_object([]) { |i, a| a << i*2 }
#     #=> [2, 4, 6, 8, 10, 12, 14, 16, 18, 20]
def each_with_object(obj, &block); Enumerator.new; end
##
# Takes one element from <i>enum</i> and merges corresponding
# elements from each <i>args</i>.  This generates a sequence of
# <em>n</em>-element arrays, where <em>n</em> is one more than the
# count of arguments.  The length of the resulting sequence will be
# <code>enum#size</code>.  If the size of any argument is less than
# <code>enum#size</code>, <code>nil</code> values are supplied. If
# a block is given, it is invoked for each output array, otherwise
# an array of arrays is returned.
# 
#    a = [ 4, 5, 6 ]
#    b = [ 7, 8, 9 ]
# 
#    [1, 2, 3].zip(a, b)      #=> [[1, 4, 7], [2, 5, 8], [3, 6, 9]]
#    [1, 2].zip(a, b)         #=> [[1, 4, 7], [2, 5, 8]]
#    a.zip([1, 2], [8])       #=> [[4, 1, 8], [5, 2, nil], [6, nil, nil]]
def zip(); end
##
# Returns first n elements from <i>enum</i>.
# 
#    a = [1, 2, 3, 4, 5, 0]
#    a.take(3)             #=> [1, 2, 3]
def take(n); []; end
##
# Passes elements to the block until the block returns +nil+ or +false+,
# then stops iterating and returns an array of all prior elements.
# 
# If no block is given, an enumerator is returned instead.
# 
#    a = [1, 2, 3, 4, 5, 0]
#    a.take_while { |i| i < 3 }   #=> [1, 2]
def take_while(&block); Enumerator.new; end
##
# Drops first n elements from <i>enum</i>, and returns rest elements
# in an array.
# 
#    a = [1, 2, 3, 4, 5, 0]
#    a.drop(3)             #=> [4, 5, 0]
def drop(n); []; end
##
# Drops elements up to, but not including, the first element for
# which the block returns +nil+ or +false+ and returns an array
# containing the remaining elements.
# 
# If no block is given, an enumerator is returned instead.
# 
#    a = [1, 2, 3, 4, 5, 0]
#    a.drop_while { |i| i < 3 }   #=> [3, 4, 5, 0]
def drop_while(&block); Enumerator.new; end
##
# Calls <i>block</i> for each element of <i>enum</i> repeatedly _n_
# times or forever if none or +nil+ is given.  If a non-positive
# number is given or the collection is empty, does nothing.  Returns
# +nil+ if the loop has finished without getting interrupted.
# 
# Enumerable#cycle saves elements in an internal array so changes
# to <i>enum</i> after the first pass have no effect.
# 
# If no block is given, an enumerator is returned instead.
# 
#    a = ["a", "b", "c"]
#    a.cycle { |x| puts x }  # print, a, b, c, a, b, c,.. forever.
#    a.cycle(2) { |x| puts x }  # print, a, b, c, a, b, c.
def cycle(n=null, &block); Enumerator.new; end
##
# Enumerates over the items, chunking them together based on the return
# value of the block.
# 
# Consecutive elements which return the same block value are chunked together.
# 
# For example, consecutive even numbers and odd numbers can be
# chunked as follows.
# 
#   [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5].chunk { |n|
#     n.even?
#   }.each { |even, ary|
#     p [even, ary]
#   }
#   #=> [false, [3, 1]]
#   #   [true, [4]]
#   #   [false, [1, 5, 9]]
#   #   [true, [2, 6]]
#   #   [false, [5, 3, 5]]
# 
# This method is especially useful for sorted series of elements.
# The following example counts words for each initial letter.
# 
#   open("/usr/share/dict/words", "r:iso-8859-1") { |f|
#     f.chunk { |line| line.ord }.each { |ch, lines| p [ch.chr, lines.length] }
#   }
#   #=> ["\n", 1]
#   #   ["A", 1327]
#   #   ["B", 1372]
#   #   ["C", 1507]
#   #   ["D", 791]
#   #   ...
# 
# The following key values have special meaning:
# - +nil+ and +:_separator+ specifies that the elements should be dropped.
# - +:_alone+ specifies that the element should be chunked by itself.
# 
# Any other symbols that begin with an underscore will raise an error:
# 
#   items.chunk { |item| :_underscore }
#   #=> RuntimeError: symbol begins with an underscore is reserved
# 
# +nil+ and +:_separator+ can be used to ignore some elements.
# 
# For example, the sequence of hyphens in svn log can be eliminated as follows:
# 
#   sep = "-"*72 + "\n"
#   IO.popen("svn log README") { |f|
#     f.chunk { |line|
#       line != sep || nil
#     }.each { |_, lines|
#       pp lines
#     }
#   }
#   #=> ["r20018 | knu | 2008-10-29 13:20:42 +0900 (Wed, 29 Oct 2008) | 2 lines\n",
#   #    "\n",
#   #    "* README, README.ja: Update the portability section.\n",
#   #    "\n"]
#   #   ["r16725 | knu | 2008-05-31 23:34:23 +0900 (Sat, 31 May 2008) | 2 lines\n",
#   #    "\n",
#   #    "* README, README.ja: Add a note about default C flags.\n",
#   #    "\n"]
#   #   ...
# 
# Paragraphs separated by empty lines can be parsed as follows:
# 
#   File.foreach("README").chunk { |line|
#     /\A\s*\z/ !~ line || nil
#   }.each { |_, lines|
#     pp lines
#   }
# 
# +:_alone+ can be used to force items into their own chunk.
# For example, you can put lines that contain a URL by themselves,
# and chunk the rest of the lines together, like this:
# 
#   pattern = /http/
#   open(filename) { |f|
#     f.chunk { |line| line =~ pattern ? :_alone : true }.each { |key, lines|
#       pp lines
#     }
#   }
# 
# If the block needs to maintain state over multiple elements,
# an +initial_state+ argument can be used.
# If a non-nil value is given,
# a reference to it is passed as the 2nd argument of the block for the
# +chunk+ method, so state-changes to it persist across block calls.
def chunk(&block); Enumerator.new; end
##
# Creates an enumerator for each chunked elements.
# The beginnings of chunks are defined by _pattern_ and the block.
# 
# If <code>_pattern_ === _elt_</code> returns <code>true</code> or the block
# returns <code>true</code> for the element, the element is beginning of a
# chunk.
# 
# The <code>===</code> and _block_ is called from the first element to the last
# element of _enum_.  The result for the first element is ignored.
# 
# The result enumerator yields the chunked elements as an array.
# So +each+ method can be called as follows:
# 
#   enum.slice_before(pattern).each { |ary| ... }
#   enum.slice_before { |elt| bool }.each { |ary| ... }
#   enum.slice_before(initial_state) { |elt, state| bool }.each { |ary| ... }
# 
# Other methods of the Enumerator class and Enumerable module,
# such as map, etc., are also usable.
# 
# For example, iteration over ChangeLog entries can be implemented as
# follows:
# 
#   # iterate over ChangeLog entries.
#   open("ChangeLog") { |f|
#     f.slice_before(/\A\S/).each { |e| pp e }
#   }
# 
#   # same as above.  block is used instead of pattern argument.
#   open("ChangeLog") { |f|
#     f.slice_before { |line| /\A\S/ === line }.each { |e| pp e }
#   }
# 
# "svn proplist -R" produces multiline output for each file.
# They can be chunked as follows:
# 
#   IO.popen([{"LC_ALL"=>"C"}, "svn", "proplist", "-R"]) { |f|
#     f.lines.slice_before(/\AProp/).each { |lines| p lines }
#   }
#   #=> ["Properties on '.':\n", "  svn:ignore\n", "  svk:merge\n"]
#   #   ["Properties on 'goruby.c':\n", "  svn:eol-style\n"]
#   #   ["Properties on 'complex.c':\n", "  svn:mime-type\n", "  svn:eol-style\n"]
#   #   ["Properties on 'regparse.c':\n", "  svn:eol-style\n"]
#   #   ...
# 
# If the block needs to maintain state over multiple elements,
# local variables can be used.
# For example, three or more consecutive increasing numbers can be squashed
# as follows:
# 
#   a = [0, 2, 3, 4, 6, 7, 9]
#   prev = a[0]
#   p a.slice_before { |e|
#     prev, prev2 = e, prev
#     prev2 + 1 != e
#   }.map { |es|
#     es.length <= 2 ? es.join(",") : "#{es.first}-#{es.last}"
#   }.join(",")
#   #=> "0,2-4,6,7,9"
# 
# However local variables are not appropriate to maintain state
# if the result enumerator is used twice or more.
# In such a case, the last state of the 1st +each+ is used in the 2nd +each+.
# The _initial_state_ argument can be used to avoid this problem.
# If non-nil value is given as _initial_state_,
# it is duplicated for each +each+ method invocation of the enumerator.
# The duplicated object is passed to 2nd argument of the block for
# +slice_before+ method.
# 
#   # Word wrapping.  This assumes all characters have same width.
#   def wordwrap(words, maxwidth)
#     # if cols is a local variable, 2nd "each" may start with non-zero cols.
#     words.slice_before(cols: 0) { |w, h|
#       h[:cols] += 1 if h[:cols] != 0
#       h[:cols] += w.length
#       if maxwidth < h[:cols]
#         h[:cols] = w.length
#         true
#       else
#         false
#       end
#     }
#   end
#   text = (1..20).to_a.join(" ")
#   enum = wordwrap(text.split(/\s+/), 10)
#   puts "-"*10
#   enum.each { |ws| puts ws.join(" ") }
#   puts "-"*10
#   #=> ----------
#   #   1 2 3 4 5
#   #   6 7 8 9 10
#   #   11 12 13
#   #   14 15 16
#   #   17 18 19
#   #   20
#   #   ----------
# 
# mbox contains series of mails which start with Unix From line.
# So each mail can be extracted by slice before Unix From line.
# 
#   # parse mbox
#   open("mbox") { |f|
#     f.slice_before { |line|
#       line.start_with? "From "
#     }.each { |mail|
#       unix_from = mail.shift
#       i = mail.index("\n")
#       header = mail[0...i]
#       body = mail[(i+1)..-1]
#       body.pop if body.last == "\n"
#       fields = header.slice_before { |line| !" \t".include?(line[0]) }.to_a
#       p unix_from
#       pp fields
#       pp body
#     }
#   }
# 
#   # split mails in mbox (slice before Unix From line after an empty line)
#   open("mbox") { |f|
#     f.slice_before(emp: true) { |line, h|
#       prevemp = h[:emp]
#       h[:emp] = line == "\n"
#       prevemp && line.start_with?("From ")
#     }.each { |mail|
#       mail.pop if mail.last == "\n"
#       pp mail
#     }
#   }
def slice_before(pattern); Enumerator.new; end
end

##
# Bignum objects hold integers outside the range of
# Fixnum. Bignum objects are created
# automatically when integer calculations would otherwise overflow a
# Fixnum. When a calculation involving
# Bignum objects returns a result that will fit in a
# Fixnum, the result is automatically converted.
# 
# For the purposes of the bitwise operations and <code>[]</code>, a
# Bignum is treated as if it were an infinite-length
# bitstring with 2's complement representation.
# 
# While Fixnum values are immediate, Bignum
# objects are not---assignment and parameter passing work with
# references to objects, not the objects themselves.
class Bignum < Integer
##
# Returns a string containing the representation of <i>big</i> radix
# <i>base</i> (2 through 36).
# 
#    12345654321.to_s         #=> "12345654321"
#    12345654321.to_s(2)      #=> "1011011111110110111011110000110001"
#    12345654321.to_s(8)      #=> "133766736061"
#    12345654321.to_s(16)     #=> "2dfdbbc31"
#    78546939656932.to_s(36)  #=> "rubyrules"
def to_s(base=10); ''; end
##
# Unary minus (returns an integer whose value is 0-big)
def -@; 0; end
##
# Adds big and other, returning the result.
def +; 0; end
##
# Subtracts other from big, returning the result.
def -; 0; end
##
# Multiplies big and other, returning the result.
def *; 0; end
##
# Performs division: the class of the resulting object depends on
# the class of <code>numeric</code> and on the magnitude of the
# result.
def /; 0; end
##
# Returns big modulo other. See Numeric.divmod for more
# information.
def %; 0; end
##
# Returns big modulo other. See Numeric.divmod for more
# information.
def modulo(other); 0; end
##
# Performs integer division: returns integer value.
def div(other); 0; end
##
# See <code>Numeric#divmod</code>.
def divmod(numeric); []; end
##
# Returns the remainder after dividing <i>big</i> by <i>numeric</i>.
# 
#    -1234567890987654321.remainder(13731)      #=> -6966
#    -1234567890987654321.remainder(13731.24)   #=> -9906.22531493148
def remainder(numeric); 0; end
##
# Returns the floating point result of dividing <i>big</i> by
# <i>numeric</i>.
# 
#    -1234567890987654321.fdiv(13731)      #=> -89910996357705.5
#    -1234567890987654321.fdiv(13731.24)   #=> -89909424858035.7
def fdiv(numeric); 0.0; end
##
# Raises _big_ to the _exponent_ power (which may be an integer, float,
# or anything that will coerce to a number). The result may be
# a Fixnum, Bignum, or Float
# 
#   123456789 ** 2      #=> 15241578750190521
#   123456789 ** 1.2    #=> 5126464716.09932
#   123456789 ** -2     #=> 6.5610001194102e-17
def **; 0; end
##
# Performs bitwise +and+ between _big_ and _numeric_.
def &; 0; end
##
# Performs bitwise +or+ between _big_ and _numeric_.
def |; 0; end
##
# Performs bitwise +exclusive or+ between _big_ and _numeric_.
def ^; 0; end
##
# Inverts the bits in big. As Bignums are conceptually infinite
# length, the result acts as if it had an infinite number of one
# bits to the left. In hex representations, this is displayed
# as two periods to the left of the digits.
# 
#   sprintf("%X", ~0x1122334455)    #=> "..FEEDDCCBBAA"
def ~; 0; end
##
# Shifts big left _numeric_ positions (right if _numeric_ is negative).
def <<; 0; end
##
# Shifts big right _numeric_ positions (left if _numeric_ is negative).
def >>; 0; end
##
# Bit Reference---Returns the <em>n</em>th bit in the (assumed) binary
# representation of <i>big</i>, where <i>big</i>[0] is the least
# significant bit.
# 
#    a = 9**15
#    50.downto(0) do |n|
#      print a[n]
#    end
# 
# <em>produces:</em>
# 
#    000101110110100000111000011110010100111100010111001
def []; 0; end
##
# Comparison---Returns -1, 0, or +1 depending on whether +big+ is
# less than, equal to, or greater than +numeric+. This is the
# basis for the tests in Comparable.
# 
# +nil+ is returned if the two values are incomparable.
def <=>; 1 || nil; end
##
# Returns <code>true</code> only if <i>obj</i> has the same value
# as <i>big</i>. Contrast this with <code>Bignum#eql?</code>, which
# requires <i>obj</i> to be a <code>Bignum</code>.
# 
#    68719476736 == 68719476736.0   #=> true
def ==; true || false; end
##
# Returns <code>true</code> if the value of <code>big</code> is
# greater than that of <code>real</code>.
def >; true || false; end
##
# Returns <code>true</code> if the value of <code>big</code> is
# greater than or equal to that of <code>real</code>.
def >=; true || false; end
##
# Returns <code>true</code> if the value of <code>big</code> is
# less than that of <code>real</code>.
def <; true || false; end
##
# Returns <code>true</code> if the value of <code>big</code> is
# less than or equal to that of <code>real</code>.
def <=; true || false; end
##
# Returns <code>true</code> only if <i>obj</i> has the same value
# as <i>big</i>. Contrast this with <code>Bignum#eql?</code>, which
# requires <i>obj</i> to be a <code>Bignum</code>.
# 
#    68719476736 == 68719476736.0   #=> true
def ===; true || false; end
##
# Returns <code>true</code> only if <i>obj</i> is a
# <code>Bignum</code> with the same value as <i>big</i>. Contrast this
# with <code>Bignum#==</code>, which performs type conversions.
# 
#    68719476736.eql?(68719476736.0)   #=> false
def eql?(obj); true || false; end
##
# Compute a hash based on the value of _big_.
def hash; 0; end
##
# Converts <i>big</i> to a <code>Float</code>. If <i>big</i> doesn't
# fit in a <code>Float</code>, the result is infinity.
def to_f; 0.0; end
##
# Returns the absolute value of <i>big</i>.
# 
#    -1234567890987654321.abs   #=> 1234567890987654321
def abs; Bignum.new; end
##
# Returns the number of bytes in the machine representation of
# <i>big</i>.
# 
#    (256**10 - 1).size   #=> 12
#    (256**20 - 1).size   #=> 20
#    (256**40 - 1).size   #=> 40
def size; 0; end
##
# Returns <code>true</code> if <i>big</i> is an odd number.
def odd?; true || false; end
##
# Returns <code>true</code> if <i>big</i> is an even number.
def even?; true || false; end
end

##
# Time is an abstraction of dates and times. Time is stored internally as
# the number of seconds with fraction since the _Epoch_, January 1, 1970
# 00:00 UTC. Also see the library module Date. The Time class treats GMT
# (Greenwich Mean Time) and UTC (Coordinated Universal Time) as equivalent.
# GMT is the older way of referring to these baseline times but persists in
# the names of calls on POSIX systems.
# 
# All times may have fraction. Be aware of this fact when comparing times
# with each other -- times that are apparently equal when displayed may be
# different when compared.
# 
# Since Ruby 1.9.2, Time implementation uses a signed 63 bit integer,
# Bignum or Rational.
# The integer is a number of nanoseconds since the _Epoch_ which can
# represent 1823-11-12 to 2116-02-20.
# When Bignum or Rational is used (before 1823, after 2116, under
# nanosecond), Time works slower as when integer is used.
# 
# = Examples
# 
# All of these examples were done using the EST timezone which is GMT-5.
# 
# == Creating a new Time instance
# 
# You can create a new instance of Time with Time::new. This will use the
# current system time. Time::now is an alias for this. You can also
# pass parts of the time to Time::new such as year, month, minute, etc. When
# you want to construct a time this way you must pass at least a year. If you
# pass the year with nothing else time will default to January 1 of that year
# at 00:00:00 with the current system timezone. Here are some examples:
# 
#   Time.new(2002)         #=> 2002-01-01 00:00:00 -0500
#   Time.new(2002, 10)     #=> 2002-10-01 00:00:00 -0500
#   Time.new(2002, 10, 31) #=> 2002-10-31 00:00:00 -0500
#   Time.new(2002, 10, 31, 2, 2, 2, "+02:00") #=> 2002-10-31 02:02:02 -0200
# 
# You can also use #gm, #local and
# #utc to infer GMT, local and UTC timezones instead of using
# the current system setting.
# 
# You can also create a new time using Time::at which takes the number of
# seconds (or fraction of seconds) since the {Unix
# Epoch}[http://en.wikipedia.org/wiki/Unix_time].
# 
#   Time.at(628232400) #=> 1989-11-28 00:00:00 -0500
# 
# == Working with an instance of Time
# 
# Once you have an instance of Time there is a multitude of things you can
# do with it. Below are some examples. For all of the following examples, we
# will work on the assumption that you have done the following:
# 
#   t = Time.new(1993, 02, 24, 12, 0, 0, "+09:00")
# 
# Was that a monday?
# 
#   t.monday? #=> false
# 
# What year was that again?
# 
#   t.year #=> 1993
# 
# Was is daylight savings at the time?
# 
#   t.dst? #=> false
# 
# What's the day a year later?
# 
#   t + (60*60*24*365) #=> 1994-02-24 12:00:00 +0900
# 
# How many seconds was that since the Unix Epoch?
# 
#   t.to_i #=> 730522800
# 
# You can also do standard functions like compare two times.
# 
#   t1 = Time.new(2010)
#   t2 = Time.new(2011)
# 
#   t1 == t2 #=> false
#   t1 == t1 #=> true
#   t1 <  t2 #=> true
#   t1 >  t2 #=> false
# 
#   Time.new(2010,10,31).between?(t1, t2) #=> true
class Time < Object
include Comparable
##
# Creates a new Time object with the value given by +time+,
# the given number of +seconds_with_frac+, or
# +seconds+ and +microseconds_with_frac+ since the Epoch.
# +seconds_with_frac+ and +microseconds_with_frac+
# can be an Integer, Float, Rational, or other Numeric.
# non-portable feature allows the offset to be negative on some systems.
# 
# If a numeric argument is given, the result is in local time.
# 
#    Time.at(0)                           #=> 1969-12-31 18:00:00 -0600
#    Time.at(Time.at(0))                  #=> 1969-12-31 18:00:00 -0600
#    Time.at(946702800)                   #=> 1999-12-31 23:00:00 -0600
#    Time.at(-284061600)                  #=> 1960-12-31 00:00:00 -0600
#    Time.at(946684800.2).usec            #=> 200000
#    Time.at(946684800, 123456.789).nsec  #=> 123456789
def self.at(time); Time.new; end
##
# Creates a Time object based on given values, interpreted as UTC (GMT). The
# year must be specified. Other values default to the minimum value
# for that field (and may be +nil+ or omitted). Months may
# be specified by numbers from 1 to 12, or by the three-letter English
# month names. Hours are specified on a 24-hour clock (0..23). Raises
# an ArgumentError if any values are out of range. Will
# also accept ten arguments in the order output by Time#to_a.
# 
# +sec_with_frac+ and +usec_with_frac+ can have a fractional part.
# 
#    Time.utc(2000,"jan",1,20,15,1)  #=> 2000-01-01 20:15:01 UTC
#    Time.gm(2000,"jan",1,20,15,1)   #=> 2000-01-01 20:15:01 UTC
def self.utc(year); Time.new; end
##
# Creates a Time object based on given values, interpreted as UTC (GMT). The
# year must be specified. Other values default to the minimum value
# for that field (and may be +nil+ or omitted). Months may
# be specified by numbers from 1 to 12, or by the three-letter English
# month names. Hours are specified on a 24-hour clock (0..23). Raises
# an ArgumentError if any values are out of range. Will
# also accept ten arguments in the order output by Time#to_a.
# 
# +sec_with_frac+ and +usec_with_frac+ can have a fractional part.
# 
#    Time.utc(2000,"jan",1,20,15,1)  #=> 2000-01-01 20:15:01 UTC
#    Time.gm(2000,"jan",1,20,15,1)   #=> 2000-01-01 20:15:01 UTC
def self.gm(year); Time.new; end
##
# Same as Time::gm, but interprets the values in the
# local time zone.
# 
#    Time.local(2000,"jan",1,20,15,1)   #=> 2000-01-01 20:15:01 -0600
def self.local(year); Time.new; end
##
# Same as Time::gm, but interprets the values in the
# local time zone.
# 
#    Time.local(2000,"jan",1,20,15,1)   #=> 2000-01-01 20:15:01 -0600
def self.mktime(year); Time.new; end
##
# Returns the value of _time_ as an integer number of seconds
# since the Epoch.
# 
#    t = Time.now
#    "%10.5f" % t.to_f   #=> "1270968656.89607"
#    t.to_i              #=> 1270968656
def to_i; 0; end
##
# Returns the value of _time_ as an integer number of seconds
# since the Epoch.
# 
#    t = Time.now
#    "%10.5f" % t.to_f   #=> "1270968656.89607"
#    t.to_i              #=> 1270968656
def tv_sec; 0; end
##
# Returns the value of _time_ as a floating point number of
# seconds since the Epoch.
# 
#    t = Time.now
#    "%10.5f" % t.to_f   #=> "1270968744.77658"
#    t.to_i              #=> 1270968744
# 
# Note that IEEE 754 double is not accurate enough to represent
# the number of nanoseconds since the Epoch.
def to_f; 0.0; end
##
# Returns the value of _time_ as a rational number of seconds
# since the Epoch.
# 
#    t = Time.now
#    p t.to_r            #=> (1270968792716287611/1000000000)
# 
# This methods is intended to be used to get an accurate value
# representing the nanoseconds since the Epoch. You can use this method
# to convert _time_ to another Epoch.
def to_r; Rational.new; end
##
# Comparison---Compares +time+ with +other_time+.
# 
# -1, 0, +1 or nil depending on whether +time+ is less  than, equal to, or
# greater than +other_time+.
# 
# +nil+ is returned if the two values are incomparable.
# 
#    t = Time.now       #=> 2007-11-19 08:12:12 -0600
#    t2 = t + 2592000   #=> 2007-12-19 08:12:12 -0600
#    t <=> t2           #=> -1
#    t2 <=> t           #=> 1
# 
#    t = Time.now       #=> 2007-11-19 08:13:38 -0600
#    t2 = t + 0.1       #=> 2007-11-19 08:13:38 -0600
#    t.nsec             #=> 98222999
#    t2.nsec            #=> 198222999
#    t <=> t2           #=> -1
#    t2 <=> t           #=> 1
#    t <=> t            #=> 0
def <=>; 1 || nil; end
##
# Returns +true+ if _time_ and +other_time+ are
# both Time objects with the same seconds and fractional seconds.
def eql?(other_time); end
##
# Returns a hash code for this Time object.
def hash; 0; end
##
# Returns a Time object.
# 
# It is initialized to the current system time if no argument is given.
# 
# *Note:* The new object will use the resolution available on your
# system clock, and may include fractional seconds.
# 
# If one or more arguments specified, the time is initialized to the specified
# time.
# 
# +sec+ may have fraction if it is a rational.
# 
# +utc_offset+ is the offset from UTC.
# It can be a string such as "+09:00" or a number of seconds such as 32400.
# 
#    a = Time.new      #=> 2007-11-19 07:50:02 -0600
#    b = Time.new      #=> 2007-11-19 07:50:02 -0600
#    a == b            #=> false
#    "%.6f" % a.to_f   #=> "1195480202.282373"
#    "%.6f" % b.to_f   #=> "1195480202.283415"
# 
#    Time.new(2008,6,21, 13,30,0, "+09:00") #=> 2008-06-21 13:30:00 +0900
# 
#    # A trip for RubyConf 2007
#    t1 = Time.new(2007,11,1,15,25,0, "+09:00") # JST (Narita)
#    t2 = Time.new(2007,11,1,12, 5,0, "-05:00") # CDT (Minneapolis)
#    t3 = Time.new(2007,11,1,13,25,0, "-05:00") # CDT (Minneapolis)
#    t4 = Time.new(2007,11,1,16,53,0, "-04:00") # EDT (Charlotte)
#    t5 = Time.new(2007,11,5, 9,24,0, "-05:00") # EST (Charlotte)
#    t6 = Time.new(2007,11,5,11,21,0, "-05:00") # EST (Detroit)
#    t7 = Time.new(2007,11,5,13,45,0, "-05:00") # EST (Detroit)
#    t8 = Time.new(2007,11,6,17,10,0, "+09:00") # JST (Narita)
#    p((t2-t1)/3600.0)                          #=> 10.666666666666666
#    p((t4-t3)/3600.0)                          #=> 2.466666666666667
#    p((t6-t5)/3600.0)                          #=> 1.95
#    p((t8-t7)/3600.0)                          #=> 13.416666666666666
def self.new; end
##
# Converts _time_ to local time (using the local time zone in
# effect for this process) modifying the receiver.
# 
# If +utc_offset+ is given, it is used instead of the local time.
# 
#    t = Time.utc(2000, "jan", 1, 20, 15, 1) #=> 2000-01-01 20:15:01 UTC
#    t.utc?                                  #=> true
# 
#    t.localtime                             #=> 2000-01-01 14:15:01 -0600
#    t.utc?                                  #=> false
# 
#    t.localtime("+09:00")                   #=> 2000-01-02 05:15:01 +0900
#    t.utc?                                  #=> false
def localtime; Time.new; end
##
# Converts _time_ to UTC (GMT), modifying the receiver.
# 
#    t = Time.now   #=> 2007-11-19 08:18:31 -0600
#    t.gmt?         #=> false
#    t.gmtime       #=> 2007-11-19 14:18:31 UTC
#    t.gmt?         #=> true
# 
#    t = Time.now   #=> 2007-11-19 08:18:51 -0600
#    t.utc?         #=> false
#    t.utc          #=> 2007-11-19 14:18:51 UTC
#    t.utc?         #=> true
def gmtime; Time.new; end
##
# Returns a new Time object representing _time_ in
# local time (using the local time zone in effect for this process).
# 
# If +utc_offset+ is given, it is used instead of the local time.
# 
#    t = Time.utc(2000,1,1,20,15,1)  #=> 2000-01-01 20:15:01 UTC
#    t.utc?                          #=> true
# 
#    l = t.getlocal                  #=> 2000-01-01 14:15:01 -0600
#    l.utc?                          #=> false
#    t == l                          #=> true
# 
#    j = t.getlocal("+09:00")        #=> 2000-01-02 05:15:01 +0900
#    j.utc?                          #=> false
#    t == j                          #=> true
def getlocal; Time.new; end
##
# Returns a new Time object representing _time_ in UTC.
# 
#    t = Time.local(2000,1,1,20,15,1)   #=> 2000-01-01 20:15:01 -0600
#    t.gmt?                             #=> false
#    y = t.getgm                        #=> 2000-01-02 02:15:01 UTC
#    y.gmt?                             #=> true
#    t == y                             #=> true
def getgm; Time.new; end
##
# Returns a new Time object representing _time_ in UTC.
# 
#    t = Time.local(2000,1,1,20,15,1)   #=> 2000-01-01 20:15:01 -0600
#    t.gmt?                             #=> false
#    y = t.getgm                        #=> 2000-01-02 02:15:01 UTC
#    y.gmt?                             #=> true
#    t == y                             #=> true
def getutc; Time.new; end
##
# Returns a canonical string representation of _time_.
# 
#    Time.now.asctime   #=> "Wed Apr  9 08:56:03 2003"
def asctime; ''; end
##
# Returns a canonical string representation of _time_.
# 
#    Time.now.asctime   #=> "Wed Apr  9 08:56:03 2003"
def ctime; ''; end
##
# Returns a string representing _time_. Equivalent to calling
# #strftime with the appropriate format string.
# 
#    t = Time.now
#    t.to_s                              => "2012-11-10 18:16:12 +0100"
#    t.strftime "%Y-%m-%d %H:%M:%S %z"   => "2012-11-10 18:16:12 +0100"
# 
#    t.utc.to_s                          => "2012-11-10 17:16:12 UTC"
#    t.strftime "%Y-%m-%d %H:%M:%S UTC"  => "2012-11-10 17:16:12 UTC"
def inspect; ''; end
##
# Returns a string representing _time_. Equivalent to calling
# #strftime with the appropriate format string.
# 
#    t = Time.now
#    t.to_s                              => "2012-11-10 18:16:12 +0100"
#    t.strftime "%Y-%m-%d %H:%M:%S %z"   => "2012-11-10 18:16:12 +0100"
# 
#    t.utc.to_s                          => "2012-11-10 17:16:12 UTC"
#    t.strftime "%Y-%m-%d %H:%M:%S UTC"  => "2012-11-10 17:16:12 UTC"
def to_s; ''; end
##
# Returns a ten-element _array_ of values for _time_:
# 
#    [sec, min, hour, day, month, year, wday, yday, isdst, zone]
# 
# See the individual methods for an explanation of the
# valid ranges of each value. The ten elements can be passed directly
# to Time::utc or Time::local to create a
# new Time object.
# 
#    t = Time.now     #=> 2007-11-19 08:36:01 -0600
#    now = t.to_a     #=> [1, 36, 8, 19, 11, 2007, 1, 323, false, "CST"]
def to_a; []; end
##
# Addition --- Adds some number of seconds (possibly fractional) to
# _time_ and returns that value as a new Time object.
# 
#    t = Time.now         #=> 2007-11-19 08:22:21 -0600
#    t + (60 * 60 * 24)   #=> 2007-11-20 08:22:21 -0600
def +; Time.new; end
##
# Difference --- Returns a new Time object that represents the difference
# between _time_ and +other_time+, or subtracts the given number
# of seconds in +numeric+ from _time_.
# 
#    t = Time.now       #=> 2007-11-19 08:23:10 -0600
#    t2 = t + 2592000   #=> 2007-12-19 08:23:10 -0600
#    t2 - t             #=> 2592000.0
#    t2 - 2592000       #=> 2007-11-19 08:23:10 -0600
def -; Time.new; end
##
# Returns a new Time object, one second later than _time_.
# Time#succ is obsolete since 1.9.2 for time is not a discrete value.
# 
#     t = Time.now       #=> 2007-11-19 08:23:57 -0600
#     t.succ             #=> 2007-11-19 08:23:58 -0600
# 
# Use instead <code>time + 1</code>
# 
#     t + 1              #=> 2007-11-19 08:23:58 -0600
def succ; Time.new; end
##
# Rounds sub seconds to a given precision in decimal digits (0 digits by default).
# It returns a new Time object.
# +ndigits+ should be zero or positive integer.
# 
#     require 'time'
# 
#     t = Time.utc(2010,3,30, 5,43,"25.123456789".to_r)
#     p t.iso8601(10)           #=> "2010-03-30T05:43:25.1234567890Z"
#     p t.round.iso8601(10)     #=> "2010-03-30T05:43:25.0000000000Z"
#     p t.round(0).iso8601(10)  #=> "2010-03-30T05:43:25.0000000000Z"
#     p t.round(1).iso8601(10)  #=> "2010-03-30T05:43:25.1000000000Z"
#     p t.round(2).iso8601(10)  #=> "2010-03-30T05:43:25.1200000000Z"
#     p t.round(3).iso8601(10)  #=> "2010-03-30T05:43:25.1230000000Z"
#     p t.round(4).iso8601(10)  #=> "2010-03-30T05:43:25.1235000000Z"
#     p t.round(5).iso8601(10)  #=> "2010-03-30T05:43:25.1234600000Z"
#     p t.round(6).iso8601(10)  #=> "2010-03-30T05:43:25.1234570000Z"
#     p t.round(7).iso8601(10)  #=> "2010-03-30T05:43:25.1234568000Z"
#     p t.round(8).iso8601(10)  #=> "2010-03-30T05:43:25.1234567900Z"
#     p t.round(9).iso8601(10)  #=> "2010-03-30T05:43:25.1234567890Z"
#     p t.round(10).iso8601(10) #=> "2010-03-30T05:43:25.1234567890Z"
# 
#     t = Time.utc(1999,12,31, 23,59,59)
#     p((t + 0.4).round.iso8601(3))    #=> "1999-12-31T23:59:59.000Z"
#     p((t + 0.49).round.iso8601(3))   #=> "1999-12-31T23:59:59.000Z"
#     p((t + 0.5).round.iso8601(3))    #=> "2000-01-01T00:00:00.000Z"
#     p((t + 1.4).round.iso8601(3))    #=> "2000-01-01T00:00:00.000Z"
#     p((t + 1.49).round.iso8601(3))   #=> "2000-01-01T00:00:00.000Z"
#     p((t + 1.5).round.iso8601(3))    #=> "2000-01-01T00:00:01.000Z"
# 
#     t = Time.utc(1999,12,31, 23,59,59)
#     p (t + 0.123456789).round(4).iso8601(6)  #=> "1999-12-31T23:59:59.123500Z"
def round(ndigits=0); Time.new; end
##
# Returns the second of the minute (0..60) for _time_.
# 
# *Note:* Seconds range from zero to 60 to allow the system to inject
# leap seconds. See http://en.wikipedia.org/wiki/Leap_second for further
# details.
# 
#    t = Time.now   #=> 2007-11-19 08:25:02 -0600
#    t.sec          #=> 2
def sec; 0; end
##
# Returns the minute of the hour (0..59) for _time_.
# 
#    t = Time.now   #=> 2007-11-19 08:25:51 -0600
#    t.min          #=> 25
def min; 0; end
##
# Returns the hour of the day (0..23) for _time_.
# 
#    t = Time.now   #=> 2007-11-19 08:26:20 -0600
#    t.hour         #=> 8
def hour; 0; end
##
# Returns the day of the month (1..n) for _time_.
# 
#    t = Time.now   #=> 2007-11-19 08:27:03 -0600
#    t.day          #=> 19
#    t.mday         #=> 19
def day; 0; end
##
# Returns the day of the month (1..n) for _time_.
# 
#    t = Time.now   #=> 2007-11-19 08:27:03 -0600
#    t.day          #=> 19
#    t.mday         #=> 19
def mday; 0; end
##
# Returns the month of the year (1..12) for _time_.
# 
#    t = Time.now   #=> 2007-11-19 08:27:30 -0600
#    t.mon          #=> 11
#    t.month        #=> 11
def mon; 0; end
##
# Returns the month of the year (1..12) for _time_.
# 
#    t = Time.now   #=> 2007-11-19 08:27:30 -0600
#    t.mon          #=> 11
#    t.month        #=> 11
def month; 0; end
##
# Returns the year for _time_ (including the century).
# 
#    t = Time.now   #=> 2007-11-19 08:27:51 -0600
#    t.year         #=> 2007
def year; 0; end
##
# Returns an integer representing the day of the week, 0..6, with
# Sunday == 0.
# 
#    t = Time.now   #=> 2007-11-20 02:35:35 -0600
#    t.wday         #=> 2
#    t.sunday?      #=> false
#    t.monday?      #=> false
#    t.tuesday?     #=> true
#    t.wednesday?   #=> false
#    t.thursday?    #=> false
#    t.friday?      #=> false
#    t.saturday?    #=> false
def wday; 0; end
##
# Returns an integer representing the day of the year, 1..366.
# 
#    t = Time.now   #=> 2007-11-19 08:32:31 -0600
#    t.yday         #=> 323
def yday; 0; end
##
# Returns +true+ if _time_ occurs during Daylight
# Saving Time in its time zone.
# 
#  # CST6CDT:
#    Time.local(2000, 1, 1).zone    #=> "CST"
#    Time.local(2000, 1, 1).isdst   #=> false
#    Time.local(2000, 1, 1).dst?    #=> false
#    Time.local(2000, 7, 1).zone    #=> "CDT"
#    Time.local(2000, 7, 1).isdst   #=> true
#    Time.local(2000, 7, 1).dst?    #=> true
# 
#  # Asia/Tokyo:
#    Time.local(2000, 1, 1).zone    #=> "JST"
#    Time.local(2000, 1, 1).isdst   #=> false
#    Time.local(2000, 1, 1).dst?    #=> false
#    Time.local(2000, 7, 1).zone    #=> "JST"
#    Time.local(2000, 7, 1).isdst   #=> false
#    Time.local(2000, 7, 1).dst?    #=> false
def isdst; true || false; end
##
# Returns +true+ if _time_ occurs during Daylight
# Saving Time in its time zone.
# 
#  # CST6CDT:
#    Time.local(2000, 1, 1).zone    #=> "CST"
#    Time.local(2000, 1, 1).isdst   #=> false
#    Time.local(2000, 1, 1).dst?    #=> false
#    Time.local(2000, 7, 1).zone    #=> "CDT"
#    Time.local(2000, 7, 1).isdst   #=> true
#    Time.local(2000, 7, 1).dst?    #=> true
# 
#  # Asia/Tokyo:
#    Time.local(2000, 1, 1).zone    #=> "JST"
#    Time.local(2000, 1, 1).isdst   #=> false
#    Time.local(2000, 1, 1).dst?    #=> false
#    Time.local(2000, 7, 1).zone    #=> "JST"
#    Time.local(2000, 7, 1).isdst   #=> false
#    Time.local(2000, 7, 1).dst?    #=> false
def dst?; true || false; end
##
# Returns the name of the time zone used for _time_. As of Ruby
# 1.8, returns ``UTC'' rather than ``GMT'' for UTC times.
# 
#    t = Time.gm(2000, "jan", 1, 20, 15, 1)
#    t.zone   #=> "UTC"
#    t = Time.local(2000, "jan", 1, 20, 15, 1)
#    t.zone   #=> "CST"
def zone; ''; end
##
# Returns the offset in seconds between the timezone of _time_
# and UTC.
# 
#    t = Time.gm(2000,1,1,20,15,1)   #=> 2000-01-01 20:15:01 UTC
#    t.gmt_offset                    #=> 0
#    l = t.getlocal                  #=> 2000-01-01 14:15:01 -0600
#    l.gmt_offset                    #=> -21600
def gmt_offset; 0; end
##
# Returns the offset in seconds between the timezone of _time_
# and UTC.
# 
#    t = Time.gm(2000,1,1,20,15,1)   #=> 2000-01-01 20:15:01 UTC
#    t.gmt_offset                    #=> 0
#    l = t.getlocal                  #=> 2000-01-01 14:15:01 -0600
#    l.gmt_offset                    #=> -21600
def gmtoff; 0; end
##
# Returns the offset in seconds between the timezone of _time_
# and UTC.
# 
#    t = Time.gm(2000,1,1,20,15,1)   #=> 2000-01-01 20:15:01 UTC
#    t.gmt_offset                    #=> 0
#    l = t.getlocal                  #=> 2000-01-01 14:15:01 -0600
#    l.gmt_offset                    #=> -21600
def utc_offset; 0; end
##
# Returns +true+ if _time_ represents a time in UTC (GMT).
# 
#    t = Time.now                        #=> 2007-11-19 08:15:23 -0600
#    t.utc?                              #=> false
#    t = Time.gm(2000,"jan",1,20,15,1)   #=> 2000-01-01 20:15:01 UTC
#    t.utc?                              #=> true
# 
#    t = Time.now                        #=> 2007-11-19 08:16:03 -0600
#    t.gmt?                              #=> false
#    t = Time.gm(2000,1,1,20,15,1)       #=> 2000-01-01 20:15:01 UTC
#    t.gmt?                              #=> true
def utc?; true || false; end
##
# Returns +true+ if _time_ represents a time in UTC (GMT).
# 
#    t = Time.now                        #=> 2007-11-19 08:15:23 -0600
#    t.utc?                              #=> false
#    t = Time.gm(2000,"jan",1,20,15,1)   #=> 2000-01-01 20:15:01 UTC
#    t.utc?                              #=> true
# 
#    t = Time.now                        #=> 2007-11-19 08:16:03 -0600
#    t.gmt?                              #=> false
#    t = Time.gm(2000,1,1,20,15,1)       #=> 2000-01-01 20:15:01 UTC
#    t.gmt?                              #=> true
def gmt?; true || false; end
##
# Returns +true+ if _time_ represents Sunday.
# 
#    t = Time.local(1990, 4, 1)       #=> 1990-04-01 00:00:00 -0600
#    t.sunday?                        #=> true
def sunday?; true || false; end
##
# Returns +true+ if _time_ represents Monday.
# 
#    t = Time.local(2003, 8, 4)       #=> 2003-08-04 00:00:00 -0500
#    p t.monday?                      #=> true
def monday?; true || false; end
##
# Returns +true+ if _time_ represents Tuesday.
# 
#    t = Time.local(1991, 2, 19)      #=> 1991-02-19 00:00:00 -0600
#    p t.tuesday?                     #=> true
def tuesday?; true || false; end
##
# Returns +true+ if _time_ represents Wednesday.
# 
#    t = Time.local(1993, 2, 24)      #=> 1993-02-24 00:00:00 -0600
#    p t.wednesday?                   #=> true
def wednesday?; true || false; end
##
# Returns +true+ if _time_ represents Thursday.
# 
#    t = Time.local(1995, 12, 21)     #=> 1995-12-21 00:00:00 -0600
#    p t.thursday?                    #=> true
def thursday?; true || false; end
##
# Returns +true+ if _time_ represents Friday.
# 
#    t = Time.local(1987, 12, 18)     #=> 1987-12-18 00:00:00 -0600
#    t.friday?                        #=> true
def friday?; true || false; end
##
# Returns +true+ if _time_ represents Saturday.
# 
#    t = Time.local(2006, 6, 10)      #=> 2006-06-10 00:00:00 -0500
#    t.saturday?                      #=> true
def saturday?; true || false; end
##
# Returns the number of microseconds for _time_.
# 
#    t = Time.now        #=> 2007-11-19 08:03:26 -0600
#    "%10.6f" % t.to_f   #=> "1195481006.775195"
#    t.usec              #=> 775195
def usec; 0; end
##
# Returns the number of microseconds for _time_.
# 
#    t = Time.now        #=> 2007-11-19 08:03:26 -0600
#    "%10.6f" % t.to_f   #=> "1195481006.775195"
#    t.usec              #=> 775195
def tv_usec; 0; end
##
# Returns the number of nanoseconds for _time_.
# 
#    t = Time.now        #=> 2007-11-17 15:18:03 +0900
#    "%10.9f" % t.to_f   #=> "1195280283.536151409"
#    t.nsec              #=> 536151406
# 
# The lowest digits of #to_f and #nsec are different because
# IEEE 754 double is not accurate enough to represent
# the exact number of nanoseconds since the Epoch.
# 
# The more accurate value is returned by #nsec.
def nsec; 0; end
##
# Returns the number of nanoseconds for _time_.
# 
#    t = Time.now        #=> 2007-11-17 15:18:03 +0900
#    "%10.9f" % t.to_f   #=> "1195280283.536151409"
#    t.nsec              #=> 536151406
# 
# The lowest digits of #to_f and #nsec are different because
# IEEE 754 double is not accurate enough to represent
# the exact number of nanoseconds since the Epoch.
# 
# The more accurate value is returned by #nsec.
def tv_nsec; 0; end
##
# Returns the fraction for _time_.
# 
# The return value can be a rational number.
# 
#    t = Time.now        #=> 2009-03-26 22:33:12 +0900
#    "%10.9f" % t.to_f   #=> "1238074392.940563917"
#    t.subsec            #=> (94056401/100000000)
# 
# The lowest digits of #to_f and #subsec are different because
# IEEE 754 double is not accurate enough to represent
# the rational number.
# 
# The more accurate value is returned by #subsec.
def subsec; 0; end
##
# Formats _time_ according to the directives in the given format string.
# 
# The directives begin with a percent (%) character.
# Any text not listed as a directive will be passed through to the
# output string.
# 
# The directive consists of a percent (%) character,
# zero or more flags, optional minimum field width,
# optional modifier and a conversion specifier
# as follows:
# 
#   %<flags><width><modifier><conversion>
# 
# Flags:
#   -  don't pad a numerical output
#   _  use spaces for padding
#   0  use zeros for padding
#   ^  upcase the result string
#   #  change case
#   :  use colons for %z
# 
# The minimum field width specifies the minimum width.
# 
# The modifiers are "E" and "O".
# They are ignored.
# 
# Format directives:
# 
#   Date (Year, Month, Day):
#     %Y - Year with century (can be negative, 4 digits at least)
#             -0001, 0000, 1995, 2009, 14292, etc.
#     %C - year / 100 (rounded down such as 20 in 2009)
#     %y - year % 100 (00..99)
# 
#     %m - Month of the year, zero-padded (01..12)
#             %_m  blank-padded ( 1..12)
#             %-m  no-padded (1..12)
#     %B - The full month name (``January'')
#             %^B  uppercased (``JANUARY'')
#     %b - The abbreviated month name (``Jan'')
#             %^b  uppercased (``JAN'')
#     %h - Equivalent to %b
# 
#     %d - Day of the month, zero-padded (01..31)
#             %-d  no-padded (1..31)
#     %e - Day of the month, blank-padded ( 1..31)
# 
#     %j - Day of the year (001..366)
# 
#   Time (Hour, Minute, Second, Subsecond):
#     %H - Hour of the day, 24-hour clock, zero-padded (00..23)
#     %k - Hour of the day, 24-hour clock, blank-padded ( 0..23)
#     %I - Hour of the day, 12-hour clock, zero-padded (01..12)
#     %l - Hour of the day, 12-hour clock, blank-padded ( 1..12)
#     %P - Meridian indicator, lowercase (``am'' or ``pm'')
#     %p - Meridian indicator, uppercase (``AM'' or ``PM'')
# 
#     %M - Minute of the hour (00..59)
# 
#     %S - Second of the minute (00..60)
# 
#     %L - Millisecond of the second (000..999)
#     %N - Fractional seconds digits, default is 9 digits (nanosecond)
#             %3N  milli second (3 digits)
#             %6N  micro second (6 digits)
#             %9N  nano second (9 digits)
#             %12N pico second (12 digits)
#             %15N femto second (15 digits)
#             %18N atto second (18 digits)
#             %21N zepto second (21 digits)
#             %24N yocto second (24 digits)
# 
#   Time zone:
#     %z - Time zone as hour and minute offset from UTC (e.g. +0900)
#             %:z - hour and minute offset from UTC with a colon (e.g. +09:00)
#             %::z - hour, minute and second offset from UTC (e.g. +09:00:00)
#     %Z - Abbreviated time zone name or similar information.
# 
#   Weekday:
#     %A - The full weekday name (``Sunday'')
#             %^A  uppercased (``SUNDAY'')
#     %a - The abbreviated name (``Sun'')
#             %^a  uppercased (``SUN'')
#     %u - Day of the week (Monday is 1, 1..7)
#     %w - Day of the week (Sunday is 0, 0..6)
# 
#   ISO 8601 week-based year and week number:
#   The first week of YYYY starts with a Monday and includes YYYY-01-04.
#   The days in the year before the first week are in the last week of
#   the previous year.
#     %G - The week-based year
#     %g - The last 2 digits of the week-based year (00..99)
#     %V - Week number of the week-based year (01..53)
# 
#   Week number:
#   The first week of YYYY that starts with a Sunday or Monday (according to %U
#   or %W). The days in the year before the first week are in week 0.
#     %U - Week number of the year. The week starts with Sunday. (00..53)
#     %W - Week number of the year. The week starts with Monday. (00..53)
# 
#   Seconds since the Epoch:
#     %s - Number of seconds since 1970-01-01 00:00:00 UTC.
# 
#   Literal string:
#     %n - Newline character (\n)
#     %t - Tab character (\t)
#     %% - Literal ``%'' character
# 
#   Combination:
#     %c - date and time (%a %b %e %T %Y)
#     %D - Date (%m/%d/%y)
#     %F - The ISO 8601 date format (%Y-%m-%d)
#     %v - VMS date (%e-%^b-%4Y)
#     %x - Same as %D
#     %X - Same as %T
#     %r - 12-hour time (%I:%M:%S %p)
#     %R - 24-hour time (%H:%M)
#     %T - 24-hour time (%H:%M:%S)
# 
# This method is similar to strftime() function defined in ISO C and POSIX.
# 
# While all directives are locale independant since Ruby 1.9 %Z is platform
# dependant.
# So, the result may differ even if the same format string is used in other
# systems such as C.
# 
# %z is recommended over %Z.
# %Z doesn't identify the timezone.
# For example, "CST" is used at America/Chicago (-06:00),
# America/Havana (-05:00), Asia/Harbin (+08:00), Australia/Darwin (+09:30)
# and Australia/Adelaide (+10:30).
# Also, %Z is highly dependent on the operating system.
# For example, it may generate a non ASCII string on Japanese Windows.
# i.e. the result can be different to "JST".
# So the numeric time zone offset, %z, is recommended.
# 
# Examples:
# 
#   t = Time.new(2007,11,19,8,37,48,"-06:00") #=> 2007-11-19 08:37:48 -0600
#   t.strftime("Printed on %m/%d/%Y")   #=> "Printed on 11/19/2007"
#   t.strftime("at %I:%M%p")            #=> "at 08:37AM"
# 
# Various ISO 8601 formats:
#   %Y%m%d           => 20071119                  Calendar date (basic)
#   %F               => 2007-11-19                Calendar date (extended)
#   %Y-%m            => 2007-11                   Calendar date, reduced accuracy, specific month
#   %Y               => 2007                      Calendar date, reduced accuracy, specific year
#   %C               => 20                        Calendar date, reduced accuracy, specific century
#   %Y%j             => 2007323                   Ordinal date (basic)
#   %Y-%j            => 2007-323                  Ordinal date (extended)
#   %GW%V%u          => 2007W471                  Week date (basic)
#   %G-W%V-%u        => 2007-W47-1                Week date (extended)
#   %GW%V            => 2007W47                   Week date, reduced accuracy, specific week (basic)
#   %G-W%V           => 2007-W47                  Week date, reduced accuracy, specific week (extended)
#   %H%M%S           => 083748                    Local time (basic)
#   %T               => 08:37:48                  Local time (extended)
#   %H%M             => 0837                      Local time, reduced accuracy, specific minute (basic)
#   %H:%M            => 08:37                     Local time, reduced accuracy, specific minute (extended)
#   %H               => 08                        Local time, reduced accuracy, specific hour
#   %H%M%S,%L        => 083748,000                Local time with decimal fraction, comma as decimal sign (basic)
#   %T,%L            => 08:37:48,000              Local time with decimal fraction, comma as decimal sign (extended)
#   %H%M%S.%L        => 083748.000                Local time with decimal fraction, full stop as decimal sign (basic)
#   %T.%L            => 08:37:48.000              Local time with decimal fraction, full stop as decimal sign (extended)
#   %H%M%S%z         => 083748-0600               Local time and the difference from UTC (basic)
#   %T%:z            => 08:37:48-06:00            Local time and the difference from UTC (extended)
#   %Y%m%dT%H%M%S%z  => 20071119T083748-0600      Date and time of day for calendar date (basic)
#   %FT%T%:z         => 2007-11-19T08:37:48-06:00 Date and time of day for calendar date (extended)
#   %Y%jT%H%M%S%z    => 2007323T083748-0600       Date and time of day for ordinal date (basic)
#   %Y-%jT%T%:z      => 2007-323T08:37:48-06:00   Date and time of day for ordinal date (extended)
#   %GW%V%uT%H%M%S%z => 2007W471T083748-0600      Date and time of day for week date (basic)
#   %G-W%V-%uT%T%:z  => 2007-W47-1T08:37:48-06:00 Date and time of day for week date (extended)
#   %Y%m%dT%H%M      => 20071119T0837             Calendar date and local time (basic)
#   %FT%R            => 2007-11-19T08:37          Calendar date and local time (extended)
#   %Y%jT%H%MZ       => 2007323T0837Z             Ordinal date and UTC of day (basic)
#   %Y-%jT%RZ        => 2007-323T08:37Z           Ordinal date and UTC of day (extended)
#   %GW%V%uT%H%M%z   => 2007W471T0837-0600        Week date and local time and difference from UTC (basic)
#   %G-W%V-%uT%R%:z  => 2007-W47-1T08:37-06:00    Week date and local time and difference from UTC (extended)
def strftime( string ); ''; end
end

##
# ::RubyVM   
class RubyVM < Object
class Env < Object
end

end

##
# Threads are the Ruby implementation for a concurrent programming model.
# 
# Programs that require multiple threads of execution are a perfect
# candidate for Ruby's Thread class.
# 
# For example, we can create a new thread separate from the main thread's
# execution using ::new.
# 
#     thr = Thread.new { puts "Whats the big deal" }
# 
# Then we are able to pause the execution of the main thread and allow
# our new thread to finish, using #join:
# 
#     thr.join #=> "Whats the big deal"
# 
# If we don't call +thr.join+ before the main thread terminates, then all
# other threads including +thr+ will be killed.
# 
# Alternatively, you can use an array for handling multiple threads at
# once, like in the following example:
# 
#     threads = []
#     threads << Thread.new { puts "Whats the big deal" }
#     threads << Thread.new { 3.times { puts "Threads are fun!" } }
# 
# After creating a few threads we wait for them all to finish
# consecutively.
# 
#     threads.each { |thr| thr.join }
# 
# === Thread initialization
# 
# In order to create new threads, Ruby provides ::new, ::start, and
# ::fork. A block must be provided with each of these methods, otherwise
# a ThreadError will be raised.
# 
# When subclassing the Thread class, the +initialize+ method of your
# subclass will be ignored by ::start and ::fork. Otherwise, be sure to
# call super in your +initialize+ method.
# 
# === Thread termination
# 
# For terminating threads, Ruby provides a variety of ways to do this.
# 
# The class method ::kill, is meant to exit a given thread:
# 
#     thr = Thread.new { ... }
#     Thread.kill(thr) # sends exit() to thr
# 
# Alternatively, you can use the instance method #exit, or any of its
# aliases #kill or #terminate.
# 
#     thr.exit
# 
# === Thread status
# 
# Ruby provides a few instance methods for querying the state of a given
# thread. To get a string with the current thread's state use #status
# 
#     thr = Thread.new { sleep }
#     thr.status # => "sleep"
#     thr.exit
#     thr.status # => false
# 
# You can also use #alive? to tell if the thread is running or sleeping,
# and #stop? if the thread is dead or sleeping.
# 
# === Thread variables and scope
# 
# Since threads are created with blocks, the same rules apply to other
# Ruby blocks for variable scope. Any local variables created within this
# block are accessible to only this thread.
# 
# ==== Fiber-local vs. Thread-local
# 
# Each fiber has its own bucket for Thread#[] storage. When you set a
# new fiber-local it is only accessible within this Fiber. To illustrate:
# 
#     Thread.new {
#       Thread.current[:foo] = "bar"
#       Fiber.new {
#         p Thread.current[:foo] # => nil
#       }.resume
#     }.join
# 
# This example uses #[] for getting and #[]= for setting fiber-locals,
# you can also use #keys to list the fiber-locals for a given
# thread and #key? to check if a fiber-local exists.
# 
# When it comes to thread-locals, they are accessible within the entire
# scope of the thread. Given the following example:
# 
#     Thread.new{
#       Thread.current.thread_variable_set(:foo, 1)
#       p Thread.current.thread_variable_get(:foo) # => 1
#       Fiber.new{
#         Thread.current.thread_variable_set(:foo, 2)
#         p Thread.current.thread_variable_get(:foo) # => 2
#       }.resume
#       p Thread.current.thread_variable_get(:foo)   # => 2
#     }.join
# 
# You can see that the thread-local +:foo+ carried over into the fiber
# and was changed to +2+ by the end of the thread.
# 
# This example makes use of #thread_variable_set to create new
# thread-locals, and #thread_variable_get to reference them.
# 
# There is also #thread_variables to list all thread-locals, and
# #thread_variable? to check if a given thread-local exists.
# 
# === Exception handling
# 
# Any thread can raise an exception using the #raise instance method,
# which operates similarly to Kernel#raise.
# 
# However, it's important to note that an exception that occurs in any
# thread except the main thread depends on #abort_on_exception. This
# option is +false+ by default, meaning that any unhandled exception will
# cause the thread to terminate silently when waited on by either #join
# or #value. You can change this default by either #abort_on_exception=
# +true+ or setting $DEBUG to +true+.
# 
# With the addition of the class method ::handle_interrupt, you can now
# handle exceptions asynchronously with threads.
# 
# === Scheduling
# 
# Ruby provides a few ways to support scheduling threads in your program.
# 
# The first way is by using the class method ::stop, to put the current
# running thread to sleep and schedule the execution of another thread.
# 
# Once a thread is asleep, you can use the instance method #wakeup to
# mark your thread as eligible for scheduling.
# 
# You can also try ::pass, which attempts to pass execution to another
# thread but is dependent on the OS whether a running thread will switch
# or not. The same goes for #priority, which lets you hint to the thread
# scheduler which threads you want to take precedence when passing
# execution. This method is also dependent on the OS and may be ignored
# on some platforms.
class Thread < Object
class Backtrace < Object
class Location < Object
end

end

##
# Establishes _proc_ on _thr_ as the handler for tracing, or
# disables tracing if the parameter is +nil+.
# 
# See Kernel#set_trace_func.
def set_trace_func(proc); end
##
# Adds _proc_ as a handler for tracing.
# 
# See Thread#set_trace_func and Kernel#set_trace_func.
def add_trace_func(proc); Proc.new; end
##
# Creates a new thread executing the given block.
# 
# Any +args+ given to ::new will be passed to the block:
# 
#     arr = []
#     a, b, c = 1, 2, 3
#     Thread.new(a,b,c) { |d,e,f| arr << d << e << f }.join
#     arr #=> [1, 2, 3]
# 
# A ThreadError exception is raised if ::new is called without a block.
# 
# If you're going to subclass Thread, be sure to call super in your
# +initialize+ method, otherwise a ThreadError will be raised.
def self.new(&block); end
##
# Basically the same as ::new. However, if class Thread is subclassed, then
# calling +start+ in that subclass will not invoke the subclass's
# +initialize+ method.
def self.start(); Thread.new; end
##
# Basically the same as ::new. However, if class Thread is subclassed, then
# calling +start+ in that subclass will not invoke the subclass's
# +initialize+ method.
def self.fork(); Thread.new; end
##
# Returns the main thread.
def self.main; Thread.new; end
##
# Returns the currently executing thread.
# 
#    Thread.current   #=> #<Thread:0x401bdf4c run>
def self.current; Thread.new; end
##
# Stops execution of the current thread, putting it into a ``sleep'' state,
# and schedules execution of another thread.
# 
#    a = Thread.new { print "a"; Thread.stop; print "c" }
#    sleep 0.1 while a.status!='sleep'
#    print "b"
#    a.run
#    a.join
#    #=> "abc"
def self.stop; end
##
# Causes the given +thread+ to exit, see also Thread::exit.
# 
#    count = 0
#    a = Thread.new { loop { count += 1 } }
#    sleep(0.1)       #=> 0
#    Thread.kill(a)   #=> #<Thread:0x401b3d30 dead>
#    count            #=> 93947
#    a.alive?         #=> false
def self.kill(thread); nil || Thread.new; end
##
# Terminates the currently running thread and schedules another thread to be
# run.
# 
# If this thread is already marked to be killed, ::exit returns the Thread.
# 
# If this is the main thread, or the last  thread, exit the process.
def self.exit; nil || Thread.new; end
##
# Give the thread scheduler a hint to pass execution to another thread.
# A running thread may or may not switch, it depends on OS and processor.
def self.pass; end
##
# Returns an array of Thread objects for all threads that are either runnable
# or stopped.
# 
#    Thread.new { sleep(200) }
#    Thread.new { 1000000.times {|i| i*i } }
#    Thread.new { Thread.stop }
#    Thread.list.each {|t| p t}
# 
# This will produce:
# 
#    #<Thread:0x401b3e84 sleep>
#    #<Thread:0x401b3f38 run>
#    #<Thread:0x401b3fb0 sleep>
#    #<Thread:0x401bdf4c run>
def self.list; []; end
##
# Returns the status of the global ``abort on exception'' condition.
# 
# The default is +false+.
# 
# When set to +true+, all threads will abort (the process will
# <code>exit(0)</code>) if an exception is raised in any thread.
# 
# Can also be specified by the global $DEBUG flag or command line option
# +-d+.
# 
# See also ::abort_on_exception=.
# 
# There is also an instance level method to set this for a specific thread,
# see #abort_on_exception.
def self.abort_on_exception; true || false; end
##
# When set to +true+, all threads will abort if an exception is raised.
# Returns the new state.
# 
#    Thread.abort_on_exception = true
#    t1 = Thread.new do
#      puts  "In new thread"
#      raise "Exception from thread"
#    end
#    sleep(1)
#    puts "not reached"
# 
# This will produce:
# 
#    In new thread
#    prog.rb:4: Exception from thread (RuntimeError)
#     from prog.rb:2:in `initialize'
#     from prog.rb:2:in `new'
#     from prog.rb:2
# 
# See also ::abort_on_exception.
# 
# There is also an instance level method to set this for a specific thread,
# see #abort_on_exception=.
def self.abort_on_exception= boolean; true || false; end
##
# Returns the thread debug level.  Available only if compiled with
# THREAD_DEBUG=-1.
def self.DEBUG; 0; end
##
# Sets the thread debug level.  Available only if compiled with
# THREAD_DEBUG=-1.
def self.DEBUG= num; end
##
# Changes asynchronous interrupt timing.
# 
# _interrupt_ means asynchronous event and corresponding procedure
# by Thread#raise, Thread#kill, signal trap (not supported yet)
# and main thread termination (if main thread terminates, then all
# other thread will be killed).
# 
# The given +hash+ has pairs like <code>ExceptionClass =>
# :TimingSymbol</code>. Where the ExceptionClass is the interrupt handled by
# the given block. The TimingSymbol can be one of the following symbols:
# 
# [+:immediate+]   Invoke interrupts immediately.
# [+:on_blocking+] Invoke interrupts while _BlockingOperation_.
# [+:never+]       Never invoke all interrupts.
# 
# _BlockingOperation_ means that the operation will block the calling thread,
# such as read and write.  On CRuby implementation, _BlockingOperation_ is any
# operation executed without GVL.
# 
# Masked asynchronous interrupts are delayed until they are enabled.
# This method is similar to sigprocmask(3).
# 
# === NOTE
# 
# Asynchronous interrupts are difficult to use.
# 
# If you need to communicate between threads, please consider to use another way such as Queue.
# 
# Or use them with deep understanding about this method.
# 
# === Usage
# 
# In this example, we can guard from Thread#raise exceptions.
# 
# Using the +:never+ TimingSymbol the RuntimeError exception will always be
# ignored in the first block of the main thread. In the second
# ::handle_interrupt block we can purposefully handle RuntimeError exceptions.
# 
#   th = Thread.new do
#     Thead.handle_interrupt(RuntimeError => :never) {
#       begin
#         # You can write resource allocation code safely.
#         Thread.handle_interrupt(RuntimeError => :immediate) {
#           # ...
#         }
#       ensure
#         # You can write resource deallocation code safely.
#       end
#     }
#   end
#   Thread.pass
#   # ...
#   th.raise "stop"
# 
# While we are ignoring the RuntimeError exception, it's safe to write our
# resource allocation code. Then, the ensure block is where we can safely
# deallocate your resources.
# 
# ==== Guarding from TimeoutError
# 
# In the next example, we will guard from the TimeoutError exception. This
# will help prevent from leaking resources when TimeoutError exceptions occur
# during normal ensure clause. For this example we use the help of the
# standard library Timeout, from lib/timeout.rb
# 
#   require 'timeout'
#   Thread.handle_interrupt(TimeoutError => :never) {
#     timeout(10){
#       # TimeoutError doesn't occur here
#       Thread.handle_interrupt(TimeoutError => :on_blocking) {
#         # possible to be killed by TimeoutError
#         # while blocking operation
#       }
#       # TimeoutError doesn't occur here
#     }
#   }
# 
# In the first part of the +timeout+ block, we can rely on TimeoutError being
# ignored. Then in the <code>TimeoutError => :on_blocking</code> block, any
# operation that will block the calling thread is susceptible to a
# TimeoutError exception being raised.
# 
# ==== Stack control settings
# 
# It's possible to stack multiple levels of ::handle_interrupt blocks in order
# to control more than one ExceptionClass and TimingSymbol at a time.
# 
#   Thread.handle_interrupt(FooError => :never) {
#     Thread.handle_interrupt(BarError => :never) {
#        # FooError and BarError are prohibited.
#     }
#   }
# 
# ==== Inheritance with ExceptionClass
# 
# All exceptions inherited from the ExceptionClass parameter will be considered.
# 
#   Thread.handle_interrupt(Exception => :never) {
#     # all exceptions inherited from Exception are prohibited.
#   }
def self.handle_interrupt(hash, &block); Object.new; end
##
# Returns whether or not the asynchronous queue is empty.
# 
# Since Thread::handle_interrupt can be used to defer asynchronous events.
# This method can be used to determine if there are any deferred events.
# 
# If you find this method returns true, then you may finish +:never+ blocks.
# 
# For example, the following method processes deferred asynchronous events
# immediately.
# 
#   def Thread.kick_interrupt_immediately
#     Thread.handle_interrupt(Object => :immediate) {
#       Thread.pass
#     }
#   end
# 
# If +error+ is given, then check only for +error+ type deferred events.
# 
# === Usage
# 
#   th = Thread.new{
#     Thread.handle_interrupt(RuntimeError => :on_blocking){
#       while true
#         ...
#         # reach safe point to invoke interrupt
#         if Thread.pending_interrupt?
#           Thread.handle_interrupt(Object => :immediate){}
#         end
#         ...
#       end
#     }
#   }
#   ...
#   th.raise # stop thread
# 
# This example can also be written as the following, which you should use to
# avoid asynchronous interrupts.
# 
#   flag = true
#   th = Thread.new{
#     Thread.handle_interrupt(RuntimeError => :on_blocking){
#       while true
#         ...
#         # reach safe point to invoke interrupt
#         break if flag == false
#         ...
#       end
#     }
#   }
#   ...
#   flag = false # stop thread
def self.pending_interrupt?(error = null); true || false; end
##
# Raises an exception from the given thread. The caller does not have to be
# +thr+. See Kernel#raise for more information.
# 
#    Thread.abort_on_exception = true
#    a = Thread.new { sleep(200) }
#    a.raise("Gotcha")
# 
# This will produce:
# 
#    prog.rb:3: Gotcha (RuntimeError)
#     from prog.rb:2:in `initialize'
#     from prog.rb:2:in `new'
#     from prog.rb:2
def raise; end
##
# The calling thread will suspend execution and run this +thr+.
# 
# Does not return until +thr+ exits or until the given +limit+ seconds have
# passed.
# 
# If the time limit expires, +nil+ will be returned, otherwise this +thr+ is
# returned.
# 
# Any threads not joined will be killed when the main program exits.
# 
# If +thr+ had previously raised an exception and the ::abort_on_exception or
# $DEBUG flags are not set, (so the exception has not yet been processed), it
# will be processed at this time.
# 
#    a = Thread.new { print "a"; sleep(10); print "b"; print "c" }
#    x = Thread.new { print "x"; Thread.pass; print "y"; print "z" }
#    x.join # Let x thread finish, a will be killed on exit.
#    #=> "axyz"
# 
# The following example illustrates the +limit+ parameter.
# 
#    y = Thread.new { 4.times { sleep 0.1; puts 'tick... ' }}
#    puts "Waiting" until y.join(0.15)
# 
# This will produce:
# 
#    tick...
#    Waiting
#    tick...
#    Waiting
#    tick...
#    tick...
def join; Thread.new; end
##
# Waits for +thr+ to complete, using #join, and returns its value.
# 
#    a = Thread.new { 2 + 2 }
#    a.value   #=> 4
def value; Object.new; end
##
# Terminates +thr+ and schedules another thread to be run.
# 
# If this thread is already marked to be killed, #exit returns the Thread.
# 
# If this is the main thread, or the last thread, exits the process.
def terminate; nil || Thread.new; end
##
# Wakes up +thr+, making it eligible for scheduling.
# 
#    a = Thread.new { puts "a"; Thread.stop; puts "c" }
#    sleep 0.1 while a.status!='sleep'
#    puts "Got here"
#    a.run
#    a.join
# 
# This will produce:
# 
#    a
#    Got here
#    c
# 
# See also the instance method #wakeup.
def run; Thread.new; end
##
# Marks a given thread as eligible for scheduling, however it may still
# remain blocked on I/O.
# 
# *Note:* This does not invoke the scheduler, see #run for more information.
# 
#    c = Thread.new { Thread.stop; puts "hey!" }
#    sleep 0.1 while c.status!='sleep'
#    c.wakeup
#    c.join
#    #=> "hey!"
def wakeup; Thread.new; end
##
# Attribute Reference---Returns the value of a fiber-local variable (current thread's root fiber
# if not explicitely inside a Fiber), using either a symbol or a string name.
# If the specified variable does not exist, returns +nil+.
# 
#    [
#      Thread.new { Thread.current["name"] = "A" },
#      Thread.new { Thread.current[:name]  = "B" },
#      Thread.new { Thread.current["name"] = "C" }
#    ].each do |th|
#      th.join
#      puts "#{th.inspect}: #{th[:name]}"
#    end
# 
# This will produce:
# 
#    #<Thread:0x00000002a54220 dead>: A
#    #<Thread:0x00000002a541a8 dead>: B
#    #<Thread:0x00000002a54130 dead>: C
# 
# Thread#[] and Thread#[]= are not thread-local but fiber-local.
# This confusion did not exist in Ruby 1.8 because
# fibers were only available since Ruby 1.9.
# Ruby 1.9 chooses that the methods behaves fiber-local to save
# following idiom for dynamic scope.
# 
#   def meth(newvalue)
#     begin
#       oldvalue = Thread.current[:name]
#       Thread.current[:name] = newvalue
#       yield
#     ensure
#       Thread.current[:name] = oldvalue
#     end
#   end
# 
# The idiom may not work as dynamic scope if the methods are thread-local
# and a given block switches fiber.
# 
#   f = Fiber.new {
#     meth(1) {
#       Fiber.yield
#     }
#   }
#   meth(2) {
#     f.resume
#   }
#   f.resume
#   p Thread.current[:name]
#   #=> nil if fiber-local
#   #=> 2 if thread-local (The value 2 is leaked to outside of meth method.)
# 
# For thread-local variables, please see #thread_variable_get and
# #thread_variable_set.
def []; Object.new || nil; end
##
# Attribute Assignment---Sets or creates the value of a fiber-local variable,
# using either a symbol or a string.
# 
# See also Thread#[].
# 
# For thread-local variables, please see #thread_variable_set and
# #thread_variable_get.
def []=; Object.new; end
##
# Returns +true+ if the given string (or symbol) exists as a fiber-local
# variable.
# 
#    me = Thread.current
#    me[:oliver] = "a"
#    me.key?(:oliver)    #=> true
#    me.key?(:stanley)   #=> false
def key?(sym); true || false; end
##
# Returns an an array of the names of the fiber-local variables (as Symbols).
# 
#    thr = Thread.new do
#      Thread.current[:cat] = 'meow'
#      Thread.current["dog"] = 'woof'
#    end
#    thr.join   #=> #<Thread:0x401b3f10 dead>
#    thr.keys   #=> [:dog, :cat]
def keys; []; end
##
# Returns the priority of <i>thr</i>. Default is inherited from the
# current thread which creating the new thread, or zero for the
# initial main thread; higher-priority thread will run more frequently
# than lower-priority threads (but lower-priority threads can also run).
# 
# This is just hint for Ruby thread scheduler.  It may be ignored on some
# platform.
# 
#    Thread.current.priority   #=> 0
def priority; 0; end
##
# Sets the priority of <i>thr</i> to <i>integer</i>. Higher-priority threads
# will run more frequently than lower-priority threads (but lower-priority
# threads can also run).
# 
# This is just hint for Ruby thread scheduler.  It may be ignored on some
# platform.
# 
#    count1 = count2 = 0
#    a = Thread.new do
#          loop { count1 += 1 }
#        end
#    a.priority = -1
# 
#    b = Thread.new do
#          loop { count2 += 1 }
#        end
#    b.priority = -2
#    sleep 1   #=> 1
#    count1    #=> 622504
#    count2    #=> 5832
def priority= integer; Thread.new; end
##
# Returns the status of +thr+.
# 
# [<tt>"sleep"</tt>]
#     Returned if this thread is sleeping or waiting on I/O
# [<tt>"run"</tt>]
#     When this thread is executing
# [<tt>"aborting"</tt>]
#     If this thread is aborting
# [+false+]
#     When this thread is terminated normally
# [+nil+]
#     If terminated with an exception.
# 
#    a = Thread.new { raise("die now") }
#    b = Thread.new { Thread.stop }
#    c = Thread.new { Thread.exit }
#    d = Thread.new { sleep }
#    d.kill                  #=> #<Thread:0x401b3678 aborting>
#    a.status                #=> nil
#    b.status                #=> "sleep"
#    c.status                #=> false
#    d.status                #=> "aborting"
#    Thread.current.status   #=> "run"
# 
# See also the instance methods #alive? and #stop?
def status; '' || false || nil; end
##
# Returns the value of a thread local variable that has been set.  Note that
# these are different than fiber local values.  For fiber local values,
# please see Thread#[] and Thread#[]=.
# 
# Thread local values are carried along with threads, and do not respect
# fibers.  For example:
# 
#   Thread.new {
#     Thread.current.thread_variable_set("foo", "bar") # set a thread local
#     Thread.current["foo"] = "bar"                    # set a fiber local
# 
#     Fiber.new {
#       Fiber.yield [
#         Thread.current.thread_variable_get("foo"), # get the thread local
#         Thread.current["foo"],                     # get the fiber local
#       ]
#     }.resume
#   }.join.value # => ['bar', nil]
# 
# The value "bar" is returned for the thread local, where nil is returned
# for the fiber local.  The fiber is executed in the same thread, so the
# thread local values are available.
# 
# See also Thread#[]
def thread_variable_get(key); Object.new || nil; end
##
# Sets a thread local with +key+ to +value+.  Note that these are local to
# threads, and not to fibers.  Please see Thread#thread_variable_get and
# Thread#[] for more information.
def thread_variable_set(key, value); end
##
# Returns an an array of the names of the thread-local variables (as Symbols).
# 
#    thr = Thread.new do
#      Thread.current.thread_variable_set(:cat, 'meow')
#      Thread.current.thread_variable_set("dog", 'woof')
#    end
#    thr.join               #=> #<Thread:0x401b3f10 dead>
#    thr.thread_variables   #=> [:dog, :cat]
# 
# Note that these are not fiber local variables.  Please see Thread#[] and
# Thread#thread_variable_get for more details.
def thread_variables; []; end
##
# Returns +true+ if the given string (or symbol) exists as a thread-local
# variable.
# 
#    me = Thread.current
#    me.thread_variable_set(:oliver, "a")
#    me.thread_variable?(:oliver)    #=> true
#    me.thread_variable?(:stanley)   #=> false
# 
# Note that these are not fiber local variables.  Please see Thread#[] and
# Thread#thread_variable_get for more details.
def thread_variable?(key); true || false; end
##
# Returns +true+ if +thr+ is running or sleeping.
# 
#    thr = Thread.new { }
#    thr.join                #=> #<Thread:0x401b3fb0 dead>
#    Thread.current.alive?   #=> true
#    thr.alive?              #=> false
# 
# See also #stop? and #status.
def alive?; true || false; end
##
# Returns +true+ if +thr+ is dead or sleeping.
# 
#    a = Thread.new { Thread.stop }
#    b = Thread.current
#    a.stop?   #=> true
#    b.stop?   #=> false
# 
# See also #alive? and #status.
def stop?; true || false; end
##
# Returns the safe level in effect for <i>thr</i>. Setting thread-local safe
# levels can help when implementing sandboxes which run insecure code.
# 
#    thr = Thread.new { $SAFE = 3; sleep }
#    Thread.current.safe_level   #=> 0
#    thr.safe_level              #=> 3
def safe_level; 0; end
##
# Returns the ThreadGroup which contains the given thread, or returns +nil+
# if +thr+ is not a member of any group.
# 
#    Thread.main.group   #=> #<ThreadGroup:0x4029d914>
def group; ThreadGroup.new || nil; end
##
# Returns the current backtrace of the target thread.
def backtrace; []; end
##
# Returns the execution stack for the target thread---an array containing
# backtrace location objects.
# 
# See Thread::Backtrace::Location for more information.
# 
# This method behaves similarly to Kernel#caller_locations except it applies
# to a specific thread.
def backtrace_locations(); [] || nil; end
##
# Dump the name, id, and status of _thr_ to a string.
def inspect; ''; end
end

class Object < BasicObject
include Kernel
##
# Looks up the named method as a receiver in <i>obj</i>, returning a
# <code>Method</code> object (or raising <code>NameError</code>). The
# <code>Method</code> object acts as a closure in <i>obj</i>'s object
# instance, so instance variables and the value of <code>self</code>
# remain available.
# 
#    class Demo
#      def initialize(n)
#        @iv = n
#      end
#      def hello()
#        "Hello, @iv = #{@iv}"
#      end
#    end
# 
#    k = Demo.new(99)
#    m = k.method(:hello)
#    m.call   #=> "Hello, @iv = 99"
# 
#    l = Demo.new('Fred')
#    m = l.method("hello")
#    m.call   #=> "Hello, @iv = Fred"
def method(sym); Method.new; end
##
# Similar to _method_, searches public method only.
def public_method(sym); Method.new; end
##
# Defines a singleton method in the receiver. The _method_
# parameter can be a +Proc+, a +Method+ or an +UnboundMethod+ object.
# If a block is specified, it is used as the method body.
# 
#    class A
#      class << self
#        def class_name
#          to_s
#        end
#      end
#    end
#    A.define_singleton_method(:who_am_i) do
#      "I am: #{class_name}"
#    end
#    A.who_am_i   # ==> "I am: A"
# 
#    guy = "Bob"
#    guy.define_singleton_method(:hello) { "#{self}: Hello there!" }
#    guy.hello    #=>  "Bob: Hello there!"
def define_singleton_method(symbol, method); Proc.new; end
##
# Invokes the method identified by _symbol_, passing it any
# arguments specified. You can use <code>__send__</code> if the name
# +send+ clashes with an existing method in _obj_.
# When the method is identified by a string, the string is converted
# to a symbol.
# 
#    class Klass
#      def hello(*args)
#        "Hello " + args.join(' ')
#      end
#    end
#    k = Klass.new
#    k.send :hello, "gentle", "readers"   #=> "Hello gentle readers"
def send(symbol , args=0); Object.new; end
##
# Invokes the method identified by _symbol_, passing it any
# arguments specified. You can use <code>__send__</code> if the name
# +send+ clashes with an existing method in _obj_.
# When the method is identified by a string, the string is converted
# to a symbol.
# 
#    class Klass
#      def hello(*args)
#        "Hello " + args.join(' ')
#      end
#    end
#    k = Klass.new
#    k.send :hello, "gentle", "readers"   #=> "Hello gentle readers"
def __send__(symbol , args=0); Object.new; end
##
# Invokes the method identified by _symbol_, passing it any
# arguments specified. Unlike send, public_send calls public
# methods only.
# When the method is identified by a string, the string is converted
# to a symbol.
# 
#    1.public_send(:puts, "hello")  # causes NoMethodError
def public_send(symbol , args=0); Object.new; end
##
# Adds to _obj_ the instance methods from each module given as a
# parameter.
# 
#    module Mod
#      def hello
#        "Hello from Mod.\n"
#      end
#    end
# 
#    class Klass
#      def hello
#        "Hello from Klass.\n"
#      end
#    end
# 
#    k = Klass.new
#    k.hello         #=> "Hello from Klass.\n"
#    k.extend(Mod)   #=> #<Klass:0x401b3bc8>
#    k.hello         #=> "Hello from Mod.\n"
def extend(); Object.new; end
##
# Returns an integer identifier for +obj+.
# 
# The same number will be returned on all calls to +id+ for a given object,
# and no two active objects will share an id.
# 
# Object#object_id is a different concept from the +:name+ notation, which
# returns the symbol id of +name+.
# 
# Replaces the deprecated Object#id.
def __id__; 0; end
##
# Returns an integer identifier for +obj+.
# 
# The same number will be returned on all calls to +id+ for a given object,
# and no two active objects will share an id.
# 
# Object#object_id is a different concept from the +:name+ notation, which
# returns the symbol id of +name+.
# 
# Replaces the deprecated Object#id.
def object_id; 0; end
##
# Returns +true+ if _obj_ responds to the given method.  Private and
# protected methods are included in the search only if the optional
# second parameter evaluates to +true+.
# 
# If the method is not implemented,
# as Process.fork on Windows, File.lchmod on GNU/Linux, etc.,
# false is returned.
# 
# If the method is not defined, <code>respond_to_missing?</code>
# method is called and the result is returned.
# 
# When the method name parameter is given as a string, the string is
# converted to a symbol.
def respond_to?(symbol, include_all=false); true || false; end
##
# DO NOT USE THIS DIRECTLY.
# 
# Hook method to return whether the _obj_ can respond to _id_ method
# or not.
# 
# When the method name parameter is given as a string, the string is
# converted to a symbol.
# 
# See #respond_to?.
def respond_to_missing?(symbol, include_all); true || false; end
##
# Case Equality -- For class Object, effectively the same as calling
# <code>#==</code>, but typically overridden by descendants to provide
# meaningful semantics in +case+ statements.
def ===; true || false; end
##
# Pattern Match---Overridden by descendants (notably
# <code>Regexp</code> and <code>String</code>) to provide meaningful
# pattern-match semantics.
def =~; end
##
# Returns true if two objects do not match (using the <i>=~</i>
# method), otherwise false.
def !~; true || false; end
##
# Equality --- At the <code>Object</code> level, <code>==</code> returns
# <code>true</code> only if +obj+ and +other+ are the same object.
# Typically, this method is overridden in descendant classes to provide
# class-specific meaning.
# 
# Unlike <code>==</code>, the <code>equal?</code> method should never be
# overridden by subclasses as it is used to determine object identity
# (that is, <code>a.equal?(b)</code> if and only if <code>a</code> is the
# same object as <code>b</code>):
# 
#   obj = "a"
#   other = obj.dup
# 
#   a == other      #=> true
#   a.equal? other  #=> false
#   a.equal? a      #=> true
# 
# The <code>eql?</code> method returns <code>true</code> if +obj+ and
# +other+ refer to the same hash key.  This is used by Hash to test members
# for equality.  For objects of class <code>Object</code>, <code>eql?</code>
# is synonymous with <code>==</code>.  Subclasses normally continue this
# tradition by aliasing <code>eql?</code> to their overridden <code>==</code>
# method, but there are exceptions.  <code>Numeric</code> types, for
# example, perform type conversion across <code>==</code>, but not across
# <code>eql?</code>, so:
# 
#    1 == 1.0     #=> true
#    1.eql? 1.0   #=> false
def eql?; true || false; end
##
# Equality --- At the <code>Object</code> level, <code>==</code> returns
# <code>true</code> only if +obj+ and +other+ are the same object.
# Typically, this method is overridden in descendant classes to provide
# class-specific meaning.
# 
# Unlike <code>==</code>, the <code>equal?</code> method should never be
# overridden by subclasses as it is used to determine object identity
# (that is, <code>a.equal?(b)</code> if and only if <code>a</code> is the
# same object as <code>b</code>):
# 
#   obj = "a"
#   other = obj.dup
# 
#   a == other      #=> true
#   a.equal? other  #=> false
#   a.equal? a      #=> true
# 
# The <code>eql?</code> method returns <code>true</code> if +obj+ and
# +other+ refer to the same hash key.  This is used by Hash to test members
# for equality.  For objects of class <code>Object</code>, <code>eql?</code>
# is synonymous with <code>==</code>.  Subclasses normally continue this
# tradition by aliasing <code>eql?</code> to their overridden <code>==</code>
# method, but there are exceptions.  <code>Numeric</code> types, for
# example, perform type conversion across <code>==</code>, but not across
# <code>eql?</code>, so:
# 
#    1 == 1.0     #=> true
#    1.eql? 1.0   #=> false
def equal?(other); true || false; end
##
# Returns 0 if obj === other, otherwise nil.
# 
# The <=> is used by various methods to compare objects, for example
# Enumerable#sort, Enumerable#max etc.
# 
# Your implementation of <=> should return one of the following values: -1, 0,
# 1 or nil. -1 means self is smaller than other. 0 means self is equal to other.
# 1 means self is bigger than other. Nil means the two values could not be
# compared.
# 
# When you defined <=>, you can include Comparable to gain the methods <=, <,
# ==, >=, > and between?.
def <=>; 0 || nil; end
##
# Returns the class of <i>obj</i>. This method must always be
# called with an explicit receiver, as <code>class</code> is also a
# reserved word in Ruby.
# 
#    1.class      #=> Fixnum
#    self.class   #=> Object
def class; Class.new; end
##
# Returns the singleton class of <i>obj</i>.  This method creates
# a new singleton class if <i>obj</i> does not have it.
# 
# If <i>obj</i> is <code>nil</code>, <code>true</code>, or
# <code>false</code>, it returns NilClass, TrueClass, or FalseClass,
# respectively.
# If <i>obj</i> is a Fixnum or a Symbol, it raises a TypeError.
# 
#    Object.new.singleton_class  #=> #<Class:#<Object:0xb7ce1e24>>
#    String.singleton_class      #=> #<Class:String>
#    nil.singleton_class         #=> NilClass
def singleton_class; Class.new; end
##
# Produces a shallow copy of <i>obj</i>---the instance variables of
# <i>obj</i> are copied, but not the objects they reference. Copies
# the frozen and tainted state of <i>obj</i>. See also the discussion
# under <code>Object#dup</code>.
# 
#    class Klass
#       attr_accessor :str
#    end
#    s1 = Klass.new      #=> #<Klass:0x401b3a38>
#    s1.str = "Hello"    #=> "Hello"
#    s2 = s1.clone       #=> #<Klass:0x401b3998 @str="Hello">
#    s2.str[1,4] = "i"   #=> "i"
#    s1.inspect          #=> "#<Klass:0x401b3a38 @str=\"Hi\">"
#    s2.inspect          #=> "#<Klass:0x401b3998 @str=\"Hi\">"
# 
# This method may have class-specific behavior.  If so, that
# behavior will be documented under the #+initialize_copy+ method of
# the class.
def clone; Object.new; end
##
# Produces a shallow copy of <i>obj</i>---the instance variables of
# <i>obj</i> are copied, but not the objects they reference.
# <code>dup</code> copies the tainted state of <i>obj</i>. See also
# the discussion under <code>Object#clone</code>. In general,
# <code>clone</code> and <code>dup</code> may have different semantics
# in descendant classes. While <code>clone</code> is used to duplicate
# an object, including its internal state, <code>dup</code> typically
# uses the class of the descendant object to create the new instance.
# 
# This method may have class-specific behavior.  If so, that
# behavior will be documented under the #+initialize_copy+ method of
# the class.
def dup; Object.new; end
##
# Marks <i>obj</i> as tainted---if the <code>$SAFE</code> level is
# set appropriately, many method calls which might alter the running
# programs environment will refuse to accept tainted strings.
def taint; Object.new; end
##
# Returns <code>true</code> if the object is tainted.
def tainted?; true || false; end
##
# Removes the taint from <i>obj</i>.
def untaint; Object.new; end
##
# Marks <i>obj</i> as untrusted.
def untrust; Object.new; end
##
# Returns <code>true</code> if the object is untrusted.
def untrusted?; true || false; end
##
# Removes the untrusted mark from <i>obj</i>.
def trust; Object.new; end
##
# Prevents further modifications to <i>obj</i>. A
# <code>RuntimeError</code> will be raised if modification is attempted.
# There is no way to unfreeze a frozen object. See also
# <code>Object#frozen?</code>.
# 
# This method returns self.
# 
#    a = [ "a", "b", "c" ]
#    a.freeze
#    a << "z"
# 
# <em>produces:</em>
# 
#    prog.rb:3:in `<<': can't modify frozen array (RuntimeError)
#     from prog.rb:3
def freeze; Object.new; end
##
# Returns the freeze status of <i>obj</i>.
# 
#    a = [ "a", "b", "c" ]
#    a.freeze    #=> ["a", "b", "c"]
#    a.frozen?   #=> true
def frozen?; true || false; end
##
# Returns a string representing <i>obj</i>. The default
# <code>to_s</code> prints the object's class and an encoding of the
# object id. As a special case, the top-level object that is the
# initial execution context of Ruby programs returns ``main.''
def to_s; ''; end
##
# Returns a string containing a human-readable representation of <i>obj</i>.
# By default, show the class name and the list of the instance variables and
# their values (by calling #inspect on each of them).
# User defined classes should override this method to make better
# representation of <i>obj</i>.  When overriding this method, it should
# return a string whose encoding is compatible with the default external
# encoding.
# 
#     [ 1, 2, 3..4, 'five' ].inspect   #=> "[1, 2, 3..4, \"five\"]"
#     Time.new.inspect                 #=> "2008-03-08 19:43:39 +0900"
# 
#     class Foo
#     end
#     Foo.new.inspect                  #=> "#<Foo:0x0300c868>"
# 
#     class Bar
#       def initialize
#         @bar = 1
#       end
#     end
#     Bar.new.inspect                  #=> "#<Bar:0x0300c868 @bar=1>"
# 
#     class Baz
#       def to_s
#         "baz"
#       end
#     end
#     Baz.new.inspect                  #=> "#<Baz:0x0300c868>"
def inspect; ''; end
##
# Returns a list of the names of public and protected methods of
# <i>obj</i>. This will include all the methods accessible in
# <i>obj</i>'s ancestors.
# If the <i>all</i> parameter is set to <code>false</code>, only those methods
# in the receiver will be listed.
# 
#    class Klass
#      def klass_method()
#      end
#    end
#    k = Klass.new
#    k.methods[0..9]    #=> [:klass_method, :nil?, :===,
#                       #    :==~, :!, :eql?
#                       #    :hash, :<=>, :class, :singleton_class]
#    k.methods.length   #=> 57
def methods(all=true); []; end
##
# Returns an array of the names of singleton methods for <i>obj</i>.
# If the optional <i>all</i> parameter is true, the list will include
# methods in modules included in <i>obj</i>.
# Only public and protected singleton methods are returned.
# 
#    module Other
#      def three() end
#    end
# 
#    class Single
#      def Single.four() end
#    end
# 
#    a = Single.new
# 
#    def a.one()
#    end
# 
#    class << a
#      include Other
#      def two()
#      end
#    end
# 
#    Single.singleton_methods    #=> [:four]
#    a.singleton_methods(false)  #=> [:two, :one]
#    a.singleton_methods         #=> [:two, :one, :three]
def singleton_methods(all=true); []; end
##
# Returns the list of protected methods accessible to <i>obj</i>. If
# the <i>all</i> parameter is set to <code>false</code>, only those methods
# in the receiver will be listed.
def protected_methods(all=true); []; end
##
# Returns the list of private methods accessible to <i>obj</i>. If
# the <i>all</i> parameter is set to <code>false</code>, only those methods
# in the receiver will be listed.
def private_methods(all=true); []; end
##
# Returns the list of public methods accessible to <i>obj</i>. If
# the <i>all</i> parameter is set to <code>false</code>, only those methods
# in the receiver will be listed.
def public_methods(all=true); []; end
##
# Returns an array of instance variable names for the receiver. Note
# that simply defining an accessor does not create the corresponding
# instance variable.
# 
#    class Fred
#      attr_accessor :a1
#      def initialize
#        @iv = 3
#      end
#    end
#    Fred.new.instance_variables   #=> [:@iv]
def instance_variables; []; end
##
# Returns the value of the given instance variable, or nil if the
# instance variable is not set. The <code>@</code> part of the
# variable name should be included for regular instance
# variables. Throws a <code>NameError</code> exception if the
# supplied symbol is not valid as an instance variable name.
# String arguments are converted to symbols.
# 
#    class Fred
#      def initialize(p1, p2)
#        @a, @b = p1, p2
#      end
#    end
#    fred = Fred.new('cat', 99)
#    fred.instance_variable_get(:@a)    #=> "cat"
#    fred.instance_variable_get("@b")   #=> 99
def instance_variable_get(symbol); Object.new; end
##
# Sets the instance variable names by <i>symbol</i> to
# <i>object</i>, thereby frustrating the efforts of the class's
# author to attempt to provide proper encapsulation. The variable
# did not have to exist prior to this call.
# If the instance variable name is passed as a string, that string
# is converted to a symbol.
# 
#    class Fred
#      def initialize(p1, p2)
#        @a, @b = p1, p2
#      end
#    end
#    fred = Fred.new('cat', 99)
#    fred.instance_variable_set(:@a, 'dog')   #=> "dog"
#    fred.instance_variable_set(:@c, 'cat')   #=> "cat"
#    fred.inspect                             #=> "#<Fred:0x401b3da8 @a=\"dog\", @b=99, @c=\"cat\">"
def instance_variable_set(symbol, obj); Object.new; end
##
# Returns <code>true</code> if the given instance variable is
# defined in <i>obj</i>.
# String arguments are converted to symbols.
# 
#    class Fred
#      def initialize(p1, p2)
#        @a, @b = p1, p2
#      end
#    end
#    fred = Fred.new('cat', 99)
#    fred.instance_variable_defined?(:@a)    #=> true
#    fred.instance_variable_defined?("@b")   #=> true
#    fred.instance_variable_defined?("@c")   #=> false
def instance_variable_defined?(symbol); true || false; end
##
# Removes the named instance variable from <i>obj</i>, returning that
# variable's value.
# 
#    class Dummy
#      attr_reader :var
#      def initialize
#        @var = 99
#      end
#      def remove
#        remove_instance_variable(:@var)
#      end
#    end
#    d = Dummy.new
#    d.var      #=> 99
#    d.remove   #=> 99
#    d.var      #=> nil
def remove_instance_variable(symbol); Object.new; end
##
# Returns <code>true</code> if <i>obj</i> is an instance of the given
# class. See also <code>Object#kind_of?</code>.
# 
#    class A;     end
#    class B < A; end
#    class C < B; end
# 
#    b = B.new
#    b.instance_of? A   #=> false
#    b.instance_of? B   #=> true
#    b.instance_of? C   #=> false
def instance_of?(klass); true || false; end
##
# Returns <code>true</code> if <i>class</i> is the class of
# <i>obj</i>, or if <i>class</i> is one of the superclasses of
# <i>obj</i> or modules included in <i>obj</i>.
# 
#    module M;    end
#    class A
#      include M
#    end
#    class B < A; end
#    class C < B; end
# 
#    b = B.new
#    b.is_a? A          #=> true
#    b.is_a? B          #=> true
#    b.is_a? C          #=> false
#    b.is_a? M          #=> true
# 
#    b.kind_of? A       #=> true
#    b.kind_of? B       #=> true
#    b.kind_of? C       #=> false
#    b.kind_of? M       #=> true
def is_a?(klass); true || false; end
##
# Returns <code>true</code> if <i>class</i> is the class of
# <i>obj</i>, or if <i>class</i> is one of the superclasses of
# <i>obj</i> or modules included in <i>obj</i>.
# 
#    module M;    end
#    class A
#      include M
#    end
#    class B < A; end
#    class C < B; end
# 
#    b = B.new
#    b.is_a? A          #=> true
#    b.is_a? B          #=> true
#    b.is_a? C          #=> false
#    b.is_a? M          #=> true
# 
#    b.kind_of? A       #=> true
#    b.kind_of? B       #=> true
#    b.kind_of? C       #=> false
#    b.kind_of? M       #=> true
def kind_of?(klass); true || false; end
##
# Yields <code>x</code> to the block, and then returns <code>x</code>.
# The primary purpose of this method is to "tap into" a method chain,
# in order to perform operations on intermediate results within the chain.
# 
#     (1..10)                .tap {|x| puts "original: #{x.inspect}"}
#       .to_a                .tap {|x| puts "array: #{x.inspect}"}
#       .select {|x| x%2==0} .tap {|x| puts "evens: #{x.inspect}"}
#       .map { |x| x*x }     .tap {|x| puts "squares: #{x.inspect}"}
def tap(&block); Object.new; end
##
# Creates a new Enumerator which will enumerate by calling +method+ on
# +obj+, passing +args+ if any.
# 
# If a block is given, it will be used to calculate the size of
# the enumerator without the need to iterate it (see Enumerator#size).
# 
# === Examples
# 
#   str = "xyz"
# 
#   enum = str.enum_for(:each_byte)
#   enum.each { |b| puts b }
#   # => 120
#   # => 121
#   # => 122
# 
#   # protect an array from being modified by some_method
#   a = [1, 2, 3]
#   some_method(a.to_enum)
# 
# It is typical to call to_enum when defining methods for
# a generic Enumerable, in case no block is passed.
# 
# Here is such an example, with parameter passing and a sizing block:
# 
#   module Enumerable
#     # a generic method to repeat the values of any enumerable
#     def repeat(n)
#       raise ArgumentError, "#{n} is negative!" if n < 0
#       unless block_given?
#         return to_enum(__method__, n) do # __method__ is :repeat here
#           sz = size     # Call size and multiply by n...
#           sz * n if sz  # but return nil if size itself is nil
#         end
#       end
#       each do |*val|
#         n.times { yield *val }
#       end
#     end
#   end
# 
#   %i[hello world].repeat(2) { |w| puts w }
#     # => Prints 'hello', 'hello', 'world', 'world'
#   enum = (1..14).repeat(3)
#     # => returns an Enumerator when called without a block
#   enum.first(4) # => [1, 1, 1, 2]
#   enum.size # => 42
def to_enum(); Enumerator.new; end
##
# Creates a new Enumerator which will enumerate by calling +method+ on
# +obj+, passing +args+ if any.
# 
# If a block is given, it will be used to calculate the size of
# the enumerator without the need to iterate it (see Enumerator#size).
# 
# === Examples
# 
#   str = "xyz"
# 
#   enum = str.enum_for(:each_byte)
#   enum.each { |b| puts b }
#   # => 120
#   # => 121
#   # => 122
# 
#   # protect an array from being modified by some_method
#   a = [1, 2, 3]
#   some_method(a.to_enum)
# 
# It is typical to call to_enum when defining methods for
# a generic Enumerable, in case no block is passed.
# 
# Here is such an example, with parameter passing and a sizing block:
# 
#   module Enumerable
#     # a generic method to repeat the values of any enumerable
#     def repeat(n)
#       raise ArgumentError, "#{n} is negative!" if n < 0
#       unless block_given?
#         return to_enum(__method__, n) do # __method__ is :repeat here
#           sz = size     # Call size and multiply by n...
#           sz * n if sz  # but return nil if size itself is nil
#         end
#       end
#       each do |*val|
#         n.times { yield *val }
#       end
#     end
#   end
# 
#   %i[hello world].repeat(2) { |w| puts w }
#     # => Prints 'hello', 'hello', 'world', 'world'
#   enum = (1..14).repeat(3)
#     # => returns an Enumerator when called without a block
#   enum.first(4) # => [1, 1, 1, 2]
#   enum.size # => 42
def enum_for(); Enumerator.new; end
##
# Prints <i>obj</i> on the given port (default <code>$></code>).
# Equivalent to:
# 
#    def display(port=$>)
#      port.write self
#    end
# 
# For example:
# 
#    1.display
#    "cat".display
#    [ 4, 5, 6 ].display
#    puts
# 
# <em>produces:</em>
# 
#    1cat456
def display(port=$>); end
end

##
# A <code>String</code> object holds and manipulates an arbitrary sequence of
# bytes, typically representing characters. String objects may be created
# using <code>String::new</code> or as literals.
# 
# Because of aliasing issues, users of strings should be aware of the methods
# that modify the contents of a <code>String</code> object.  Typically,
# methods with names ending in ``!'' modify their receiver, while those
# without a ``!'' return a new <code>String</code>.  However, there are
# exceptions, such as <code>String#[]=</code>.
class String < Object
include Comparable
##
# Try to convert <i>obj</i> into a String, using to_str method.
# Returns converted string or nil if <i>obj</i> cannot be converted
# for any reason.
# 
#    String.try_convert("str")     #=> "str"
#    String.try_convert(/re/)      #=> nil
def self.try_convert(obj); '' || nil; end
##
# Returns a new string object containing a copy of <i>str</i>.
def self.new(str=""); end
##
# Replaces the contents and taintedness of <i>str</i> with the corresponding
# values in <i>other_str</i>.
# 
#    s = "hello"         #=> "hello"
#    s.replace "world"   #=> "world"
def replace(other_str); ''; end
##
# Comparison---Returns -1, 0, +1 or nil depending on whether +string+ is less
# than, equal to, or greater than +other_string+.
# 
# +nil+ is returned if the two values are incomparable.
# 
# If the strings are of different lengths, and the strings are equal when
# compared up to the shortest length, then the longer string is considered
# greater than the shorter one.
# 
# <code><=></code> is the basis for the methods <code><</code>,
# <code><=</code>, <code>></code>, <code>>=</code>, and
# <code>between?</code>, included from module Comparable. The method
# String#== does not use Comparable#==.
# 
#    "abcdef" <=> "abcde"     #=> 1
#    "abcdef" <=> "abcdef"    #=> 0
#    "abcdef" <=> "abcdefg"   #=> -1
#    "abcdef" <=> "ABCDEF"    #=> 1
def <=>; 1 || nil; end
##
# Equality---If <i>obj</i> is not a <code>String</code>, returns
# <code>false</code>. Otherwise, returns <code>true</code> if <i>str</i>
# <code><=></code> <i>obj</i> returns zero.
def ==; true || false; end
##
# Equality---If <i>obj</i> is not a <code>String</code>, returns
# <code>false</code>. Otherwise, returns <code>true</code> if <i>str</i>
# <code><=></code> <i>obj</i> returns zero.
def ===; true || false; end
##
# Two strings are equal if they have the same length and content.
def eql?(other); true || false; end
##
# Return a hash based on the string's length and content.
def hash; 0; end
##
# Case-insensitive version of <code>String#<=></code>.
# 
#    "abcdef".casecmp("abcde")     #=> 1
#    "aBcDeF".casecmp("abcdef")    #=> 0
#    "abcdef".casecmp("abcdefg")   #=> -1
#    "abcdef".casecmp("ABCDEF")    #=> 0
def casecmp(other_str); 1 || nil; end
##
# Concatenation---Returns a new <code>String</code> containing
# <i>other_str</i> concatenated to <i>str</i>.
# 
#    "Hello from " + self.to_s   #=> "Hello from main"
def +; ''; end
##
# Copy --- Returns a new String containing +integer+ copies of the receiver.
# +integer+ must be greater than or equal to 0.
# 
#    "Ho! " * 3   #=> "Ho! Ho! Ho! "
#    "Ho! " * 0   #=> ""
def *; ''; end
##
# Format---Uses <i>str</i> as a format specification, and returns the result
# of applying it to <i>arg</i>. If the format specification contains more than
# one substitution, then <i>arg</i> must be an <code>Array</code> or <code>Hash</code>
# containing the values to be substituted. See <code>Kernel::sprintf</code> for
# details of the format string.
# 
#    "%05d" % 123                              #=> "00123"
#    "%-5s: %08x" % [ "ID", self.object_id ]   #=> "ID   : 200e14d6"
#    "foo = %{foo}" % { :foo => 'bar' }        #=> "foo = bar"
def %; ''; end
##
# Element Reference --- If passed a single +index+, returns a substring of
# one character at that index. If passed a +start+ index and a +length+,
# returns a substring containing +length+ characters starting at the
# +index+. If passed a +range+, its beginning and end are interpreted as
# offsets delimiting the substring to be returned.
# 
# In these three cases, if an index is negative, it is counted from the end
# of the string.  For the +start+ and +range+ cases the starting index
# is just before a character and an index matching the string's size.
# Additionally, an empty string is returned when the starting index for a
# character range is at the end of the string.
# 
# Returns +nil+ if the initial index falls outside the string or the length
# is negative.
# 
# If a +Regexp+ is supplied, the matching portion of the string is
# returned.  If a +capture+ follows the regular expression, which may be a
# capture group index or name, follows the regular expression that component
# of the MatchData is returned instead.
# 
# If a +match_str+ is given, that string is returned if it occurs in
# the string.
# 
# Returns +nil+ if the regular expression does not match or the match string
# cannot be found.
# 
#    a = "hello there"
# 
#    a[1]                   #=> "e"
#    a[2, 3]                #=> "llo"
#    a[2..3]                #=> "ll"
# 
#    a[-3, 2]               #=> "er"
#    a[7..-2]               #=> "her"
#    a[-4..-2]              #=> "her"
#    a[-2..-4]              #=> ""
# 
#    a[11, 0]               #=> ""
#    a[11]                  #=> nil
#    a[12, 0]               #=> nil
#    a[12..-1]              #=> nil
# 
#    a[/[aeiou](.)\1/]      #=> "ell"
#    a[/[aeiou](.)\1/, 0]   #=> "ell"
#    a[/[aeiou](.)\1/, 1]   #=> "l"
#    a[/[aeiou](.)\1/, 2]   #=> nil
# 
#    a[/(?<vowel>[aeiou])(?<non_vowel>[^aeiou])/, "non_vowel"] #=> "l"
#    a[/(?<vowel>[aeiou])(?<non_vowel>[^aeiou])/, "vowel"]     #=> "e"
# 
#    a["lo"]                #=> "lo"
#    a["bye"]               #=> nil
def []; '' || nil; end
##
# Element Reference --- If passed a single +index+, returns a substring of
# one character at that index. If passed a +start+ index and a +length+,
# returns a substring containing +length+ characters starting at the
# +index+. If passed a +range+, its beginning and end are interpreted as
# offsets delimiting the substring to be returned.
# 
# In these three cases, if an index is negative, it is counted from the end
# of the string.  For the +start+ and +range+ cases the starting index
# is just before a character and an index matching the string's size.
# Additionally, an empty string is returned when the starting index for a
# character range is at the end of the string.
# 
# Returns +nil+ if the initial index falls outside the string or the length
# is negative.
# 
# If a +Regexp+ is supplied, the matching portion of the string is
# returned.  If a +capture+ follows the regular expression, which may be a
# capture group index or name, follows the regular expression that component
# of the MatchData is returned instead.
# 
# If a +match_str+ is given, that string is returned if it occurs in
# the string.
# 
# Returns +nil+ if the regular expression does not match or the match string
# cannot be found.
# 
#    a = "hello there"
# 
#    a[1]                   #=> "e"
#    a[2, 3]                #=> "llo"
#    a[2..3]                #=> "ll"
# 
#    a[-3, 2]               #=> "er"
#    a[7..-2]               #=> "her"
#    a[-4..-2]              #=> "her"
#    a[-2..-4]              #=> ""
# 
#    a[11, 0]               #=> ""
#    a[11]                  #=> nil
#    a[12, 0]               #=> nil
#    a[12..-1]              #=> nil
# 
#    a[/[aeiou](.)\1/]      #=> "ell"
#    a[/[aeiou](.)\1/, 0]   #=> "ell"
#    a[/[aeiou](.)\1/, 1]   #=> "l"
#    a[/[aeiou](.)\1/, 2]   #=> nil
# 
#    a[/(?<vowel>[aeiou])(?<non_vowel>[^aeiou])/, "non_vowel"] #=> "l"
#    a[/(?<vowel>[aeiou])(?<non_vowel>[^aeiou])/, "vowel"]     #=> "e"
# 
#    a["lo"]                #=> "lo"
#    a["bye"]               #=> nil
def slice(index); '' || nil; end
##
# Element Assignment---Replaces some or all of the content of <i>str</i>. The
# portion of the string affected is determined using the same criteria as
# <code>String#[]</code>. If the replacement string is not the same length as
# the text it is replacing, the string will be adjusted accordingly. If the
# regular expression or string is used as the index doesn't match a position
# in the string, <code>IndexError</code> is raised. If the regular expression
# form is used, the optional second <code>Fixnum</code> allows you to specify
# which portion of the match to replace (effectively using the
# <code>MatchData</code> indexing rules. The forms that take a
# <code>Fixnum</code> will raise an <code>IndexError</code> if the value is
# out of range; the <code>Range</code> form will raise a
# <code>RangeError</code>, and the <code>Regexp</code> and <code>String</code>
# will raise an <code>IndexError</code> on negative match.
def []=; end
##
# Inserts <i>other_str</i> before the character at the given
# <i>index</i>, modifying <i>str</i>. Negative indices count from the
# end of the string, and insert <em>after</em> the given character.
# The intent is insert <i>aString</i> so that it starts at the given
# <i>index</i>.
# 
#    "abcd".insert(0, 'X')    #=> "Xabcd"
#    "abcd".insert(3, 'X')    #=> "abcXd"
#    "abcd".insert(4, 'X')    #=> "abcdX"
#    "abcd".insert(-3, 'X')   #=> "abXcd"
#    "abcd".insert(-1, 'X')   #=> "abcdX"
def insert(index, other_str); ''; end
##
# Returns the character length of <i>str</i>.
def length; 0; end
##
# Returns the character length of <i>str</i>.
def size; 0; end
##
# Returns the length of +str+ in bytes.
# 
#   "\x80\u3042".bytesize  #=> 4
#   "hello".bytesize       #=> 5
def bytesize; 0; end
##
# Returns <code>true</code> if <i>str</i> has a length of zero.
# 
#    "hello".empty?   #=> false
#    " ".empty?       #=> false
#    "".empty?        #=> true
def empty?; true || false; end
##
# Match---If <i>obj</i> is a <code>Regexp</code>, use it as a pattern to match
# against <i>str</i>,and returns the position the match starts, or
# <code>nil</code> if there is no match. Otherwise, invokes
# <i>obj.=~</i>, passing <i>str</i> as an argument. The default
# <code>=~</code> in <code>Object</code> returns <code>nil</code>.
# 
# Note: <code>str =~ regexp</code> is not the same as
# <code>regexp =~ str</code>. Strings captured from named capture groups
# are assigned to local variables only in the second case.
# 
#    "cat o' 9 tails" =~ /\d/   #=> 7
#    "cat o' 9 tails" =~ 9      #=> nil
def =~; 1 || nil; end
##
# Converts <i>pattern</i> to a <code>Regexp</code> (if it isn't already one),
# then invokes its <code>match</code> method on <i>str</i>.  If the second
# parameter is present, it specifies the position in the string to begin the
# search.
# 
#    'hello'.match('(.)\1')      #=> #<MatchData "ll" 1:"l">
#    'hello'.match('(.)\1')[0]   #=> "ll"
#    'hello'.match(/(.)\1/)[0]   #=> "ll"
#    'hello'.match('xx')         #=> nil
# 
# If a block is given, invoke the block with MatchData if match succeed, so
# that you can write
# 
#    str.match(pat) {|m| ...}
# 
# instead of
# 
#    if m = str.match(pat)
#      ...
#    end
# 
# The return value is a value from block execution in this case.
def match(pattern); MatchData.new || nil; end
##
# Returns the successor to <i>str</i>. The successor is calculated by
# incrementing characters starting from the rightmost alphanumeric (or
# the rightmost character if there are no alphanumerics) in the
# string. Incrementing a digit always results in another digit, and
# incrementing a letter results in another letter of the same case.
# Incrementing nonalphanumerics uses the underlying character set's
# collating sequence.
# 
# If the increment generates a ``carry,'' the character to the left of
# it is incremented. This process repeats until there is no carry,
# adding an additional character if necessary.
# 
#    "abcd".succ        #=> "abce"
#    "THX1138".succ     #=> "THX1139"
#    "<<koala>>".succ   #=> "<<koalb>>"
#    "1999zzz".succ     #=> "2000aaa"
#    "ZZZ9999".succ     #=> "AAAA0000"
#    "***".succ         #=> "**+"
def succ; ''; end
##
# Returns the successor to <i>str</i>. The successor is calculated by
# incrementing characters starting from the rightmost alphanumeric (or
# the rightmost character if there are no alphanumerics) in the
# string. Incrementing a digit always results in another digit, and
# incrementing a letter results in another letter of the same case.
# Incrementing nonalphanumerics uses the underlying character set's
# collating sequence.
# 
# If the increment generates a ``carry,'' the character to the left of
# it is incremented. This process repeats until there is no carry,
# adding an additional character if necessary.
# 
#    "abcd".succ        #=> "abce"
#    "THX1138".succ     #=> "THX1139"
#    "<<koala>>".succ   #=> "<<koalb>>"
#    "1999zzz".succ     #=> "2000aaa"
#    "ZZZ9999".succ     #=> "AAAA0000"
#    "***".succ         #=> "**+"
def next; ''; end
##
# Equivalent to <code>String#succ</code>, but modifies the receiver in
# place.
def succ!; ''; end
##
# Equivalent to <code>String#succ</code>, but modifies the receiver in
# place.
def next!; ''; end
##
# Iterates through successive values, starting at <i>str</i> and
# ending at <i>other_str</i> inclusive, passing each value in turn to
# the block. The <code>String#succ</code> method is used to generate
# each value.  If optional second argument exclusive is omitted or is false,
# the last value will be included; otherwise it will be excluded.
# 
# If no block is given, an enumerator is returned instead.
# 
#    "a8".upto("b6") {|s| print s, ' ' }
#    for s in "a8".."b6"
#      print s, ' '
#    end
# 
# <em>produces:</em>
# 
#    a8 a9 b0 b1 b2 b3 b4 b5 b6
#    a8 a9 b0 b1 b2 b3 b4 b5 b6
# 
# If <i>str</i> and <i>other_str</i> contains only ascii numeric characters,
# both are recognized as decimal numbers. In addition, the width of
# string (e.g. leading zeros) is handled appropriately.
# 
#    "9".upto("11").to_a   #=> ["9", "10", "11"]
#    "25".upto("5").to_a   #=> []
#    "07".upto("11").to_a  #=> ["07", "08", "09", "10", "11"]
def upto(other_str, exclusive=false, &block); Enumerator.new; end
##
# Returns the index of the first occurrence of the given <i>substring</i> or
# pattern (<i>regexp</i>) in <i>str</i>. Returns <code>nil</code> if not
# found. If the second parameter is present, it specifies the position in the
# string to begin the search.
# 
#    "hello".index('e')             #=> 1
#    "hello".index('lo')            #=> 3
#    "hello".index('a')             #=> nil
#    "hello".index(?e)              #=> 1
#    "hello".index(/[aeiou]/, -3)   #=> 4
def index(substring , offset=0); 1 || nil; end
##
# Returns the index of the last occurrence of the given <i>substring</i> or
# pattern (<i>regexp</i>) in <i>str</i>. Returns <code>nil</code> if not
# found. If the second parameter is present, it specifies the position in the
# string to end the search---characters beyond this point will not be
# considered.
# 
#    "hello".rindex('e')             #=> 1
#    "hello".rindex('l')             #=> 3
#    "hello".rindex('a')             #=> nil
#    "hello".rindex(?e)              #=> 1
#    "hello".rindex(/[aeiou]/, -2)   #=> 1
def rindex(substring , fixnum=0); 1 || nil; end
##
# Makes string empty.
# 
#    a = "abcde"
#    a.clear    #=> ""
def clear; ''; end
##
# Returns a one-character string at the beginning of the string.
# 
#    a = "abcde"
#    a.chr    #=> "a"
def chr; ''; end
##
# returns the <i>index</i>th byte as an integer.
def getbyte(index); 0..255; end
##
# modifies the <i>index</i>th byte as <i>int</i>.
def setbyte(index, int); 0; end
##
# Byte Reference---If passed a single <code>Fixnum</code>, returns a
# substring of one byte at that position. If passed two <code>Fixnum</code>
# objects, returns a substring starting at the offset given by the first, and
# a length given by the second. If given a <code>Range</code>, a substring containing
# bytes at offsets given by the range is returned. In all three cases, if
# an offset is negative, it is counted from the end of <i>str</i>. Returns
# <code>nil</code> if the initial offset falls outside the string, the length
# is negative, or the beginning of the range is greater than the end.
# The encoding of the resulted string keeps original encoding.
# 
#    "hello".byteslice(1)     #=> "e"
#    "hello".byteslice(-1)    #=> "o"
#    "hello".byteslice(1, 2)  #=> "el"
#    "\x80\u3042".byteslice(1, 3) #=> "\u3042"
#    "\x03\u3042\xff".byteslice(1..3) #=> "\u3042"
def byteslice(fixnum); '' || nil; end
##
# Returns the result of interpreting leading characters in <i>str</i> as an
# integer base <i>base</i> (between 2 and 36). Extraneous characters past the
# end of a valid number are ignored. If there is not a valid number at the
# start of <i>str</i>, <code>0</code> is returned. This method never raises an
# exception when <i>base</i> is valid.
# 
#    "12345".to_i             #=> 12345
#    "99 red balloons".to_i   #=> 99
#    "0a".to_i                #=> 0
#    "0a".to_i(16)            #=> 10
#    "hello".to_i             #=> 0
#    "1100101".to_i(2)        #=> 101
#    "1100101".to_i(8)        #=> 294977
#    "1100101".to_i(10)       #=> 1100101
#    "1100101".to_i(16)       #=> 17826049
def to_i(base=10); 0; end
##
# Returns the result of interpreting leading characters in <i>str</i> as a
# floating point number. Extraneous characters past the end of a valid number
# are ignored. If there is not a valid number at the start of <i>str</i>,
# <code>0.0</code> is returned. This method never raises an exception.
# 
#    "123.45e1".to_f        #=> 1234.5
#    "45.67 degrees".to_f   #=> 45.67
#    "thx1138".to_f         #=> 0.0
def to_f; 0.0; end
##
# Returns the receiver.
def to_s; ''; end
##
# Returns the receiver.
def to_str; ''; end
##
# Returns a printable version of _str_, surrounded by quote marks,
# with special characters escaped.
# 
#    str = "hello"
#    str[3] = "\b"
#    str.inspect       #=> "\"hel\\bo\""
def inspect; ''; end
##
# Produces a version of +str+ with all non-printing characters replaced by
# <code>\nnn</code> notation and all special characters escaped.
# 
#   "hello \n ''".dump  #=> "\"hello \\n ''\"
def dump; ''; end
##
# Returns a copy of <i>str</i> with all lowercase letters replaced with their
# uppercase counterparts. The operation is locale insensitive---only
# characters ``a'' to ``z'' are affected.
# Note: case replacement is effective only in ASCII region.
# 
#    "hEllO".upcase   #=> "HELLO"
def upcase; ''; end
##
# Returns a copy of <i>str</i> with all uppercase letters replaced with their
# lowercase counterparts. The operation is locale insensitive---only
# characters ``A'' to ``Z'' are affected.
# Note: case replacement is effective only in ASCII region.
# 
#    "hEllO".downcase   #=> "hello"
def downcase; ''; end
##
# Returns a copy of <i>str</i> with the first character converted to uppercase
# and the remainder to lowercase.
# Note: case conversion is effective only in ASCII region.
# 
#    "hello".capitalize    #=> "Hello"
#    "HELLO".capitalize    #=> "Hello"
#    "123ABC".capitalize   #=> "123abc"
def capitalize; ''; end
##
# Returns a copy of <i>str</i> with uppercase alphabetic characters converted
# to lowercase and lowercase characters converted to uppercase.
# Note: case conversion is effective only in ASCII region.
# 
#    "Hello".swapcase          #=> "hELLO"
#    "cYbEr_PuNk11".swapcase   #=> "CyBeR_pUnK11"
def swapcase; ''; end
##
# Upcases the contents of <i>str</i>, returning <code>nil</code> if no changes
# were made.
# Note: case replacement is effective only in ASCII region.
def upcase!; '' || nil; end
##
# Downcases the contents of <i>str</i>, returning <code>nil</code> if no
# changes were made.
# Note: case replacement is effective only in ASCII region.
def downcase!; '' || nil; end
##
# Modifies <i>str</i> by converting the first character to uppercase and the
# remainder to lowercase. Returns <code>nil</code> if no changes are made.
# Note: case conversion is effective only in ASCII region.
# 
#    a = "hello"
#    a.capitalize!   #=> "Hello"
#    a               #=> "Hello"
#    a.capitalize!   #=> nil
def capitalize!; '' || nil; end
##
# Equivalent to <code>String#swapcase</code>, but modifies the receiver in
# place, returning <i>str</i>, or <code>nil</code> if no changes were made.
# Note: case conversion is effective only in ASCII region.
def swapcase!; '' || nil; end
##
# Treats leading characters from <i>str</i> as a string of hexadecimal digits
# (with an optional sign and an optional <code>0x</code>) and returns the
# corresponding number. Zero is returned on error.
# 
#    "0x0a".hex     #=> 10
#    "-1234".hex    #=> -4660
#    "0".hex        #=> 0
#    "wombat".hex   #=> 0
def hex; 0; end
##
# Treats leading characters of <i>str</i> as a string of octal digits (with an
# optional sign) and returns the corresponding number.  Returns 0 if the
# conversion fails.
# 
#    "123".oct       #=> 83
#    "-377".oct      #=> -255
#    "bad".oct       #=> 0
#    "0377bad".oct   #=> 255
def oct; 0; end
##
# Divides <i>str</i> into substrings based on a delimiter, returning an array
# of these substrings.
# 
# If <i>pattern</i> is a <code>String</code>, then its contents are used as
# the delimiter when splitting <i>str</i>. If <i>pattern</i> is a single
# space, <i>str</i> is split on whitespace, with leading whitespace and runs
# of contiguous whitespace characters ignored.
# 
# If <i>pattern</i> is a <code>Regexp</code>, <i>str</i> is divided where the
# pattern matches. Whenever the pattern matches a zero-length string,
# <i>str</i> is split into individual characters. If <i>pattern</i> contains
# groups, the respective matches will be returned in the array as well.
# 
# If <i>pattern</i> is omitted, the value of <code>$;</code> is used.  If
# <code>$;</code> is <code>nil</code> (which is the default), <i>str</i> is
# split on whitespace as if ` ' were specified.
# 
# If the <i>limit</i> parameter is omitted, trailing null fields are
# suppressed. If <i>limit</i> is a positive number, at most that number of
# fields will be returned (if <i>limit</i> is <code>1</code>, the entire
# string is returned as the only entry in an array). If negative, there is no
# limit to the number of fields returned, and trailing null fields are not
# suppressed.
# 
# When the input +str+ is empty an empty Array is returned as the string is
# considered to have no fields to split.
# 
#    " now's  the time".split        #=> ["now's", "the", "time"]
#    " now's  the time".split(' ')   #=> ["now's", "the", "time"]
#    " now's  the time".split(/ /)   #=> ["", "now's", "", "the", "time"]
#    "1, 2.34,56, 7".split(%r{,\s*}) #=> ["1", "2.34", "56", "7"]
#    "hello".split(//)               #=> ["h", "e", "l", "l", "o"]
#    "hello".split(//, 3)            #=> ["h", "e", "llo"]
#    "hi mom".split(%r{\s*})         #=> ["h", "i", "m", "o", "m"]
# 
#    "mellow yellow".split("ello")   #=> ["m", "w y", "w"]
#    "1,2,,3,4,,".split(',')         #=> ["1", "2", "", "3", "4"]
#    "1,2,,3,4,,".split(',', 4)      #=> ["1", "2", "", "3,4,,"]
#    "1,2,,3,4,,".split(',', -4)     #=> ["1", "2", "", "3", "4", "", ""]
# 
#    "".split(',', -1)               #=> []
def split(pattern=$;, limit=0); []; end
##
# Returns an array of lines in <i>str</i> split using the supplied
# record separator (<code>$/</code> by default).  This is a
# shorthand for <code>str.each_line(separator).to_a</code>.
# 
# If a block is given, which is a deprecated form, works the same as
# <code>each_line</code>.
def lines(separator=$/); []; end
##
# Returns an array of bytes in <i>str</i>.  This is a shorthand for
# <code>str.each_byte.to_a</code>.
# 
# If a block is given, which is a deprecated form, works the same as
# <code>each_byte</code>.
def bytes; []; end
##
# Returns an array of characters in <i>str</i>.  This is a shorthand
# for <code>str.each_char.to_a</code>.
# 
# If a block is given, which is a deprecated form, works the same as
# <code>each_char</code>.
def chars; []; end
##
# Returns an array of the <code>Integer</code> ordinals of the
# characters in <i>str</i>.  This is a shorthand for
# <code>str.each_codepoint.to_a</code>.
# 
# If a block is given, which is a deprecated form, works the same as
# <code>each_codepoint</code>.
def codepoints; []; end
##
# Returns a new string with the characters from <i>str</i> in reverse order.
# 
#    "stressed".reverse   #=> "desserts"
def reverse; ''; end
##
# Reverses <i>str</i> in place.
def reverse!; ''; end
##
# Append---Concatenates the given object to <i>str</i>. If the object is a
# <code>Integer</code>, it is considered as a codepoint, and is converted
# to a character before concatenation.
# 
#    a = "hello "
#    a << "world"   #=> "hello world"
#    a.concat(33)   #=> "hello world!"
def concat; ''; end
##
# Append---Concatenates the given object to <i>str</i>. If the object is a
# <code>Integer</code>, it is considered as a codepoint, and is converted
# to a character before concatenation.
# 
#    a = "hello "
#    a << "world"   #=> "hello world"
#    a.concat(33)   #=> "hello world!"
def <<; ''; end
##
# Prepend---Prepend the given string to <i>str</i>.
# 
#    a = "world"
#    a.prepend("hello ") #=> "hello world"
#    a                   #=> "hello world"
def prepend(other_str); ''; end
##
# Applies a one-way cryptographic hash to <i>str</i> by invoking the
# standard library function <code>crypt(3)</code> with the given
# salt string.  While the format and the result are system and
# implementation dependent, using a salt matching the regular
# expression <code>\A[a-zA-Z0-9./]{2}</code> should be valid and
# safe on any platform, in which only the first two characters are
# significant.
# 
# This method is for use in system specific scripts, so if you want
# a cross-platform hash function consider using Digest or OpenSSL
# instead.
def crypt(salt_str); ''; end
##
# Returns the <code>Symbol</code> corresponding to <i>str</i>, creating the
# symbol if it did not previously exist. See <code>Symbol#id2name</code>.
# 
#    "Koala".intern         #=> :Koala
#    s = 'cat'.to_sym       #=> :cat
#    s == :cat              #=> true
#    s = '@cat'.to_sym      #=> :@cat
#    s == :@cat             #=> true
# 
# This can also be used to create symbols that cannot be represented using the
# <code>:xxx</code> notation.
# 
#    'cat and dog'.to_sym   #=> :"cat and dog"
def intern; :a; end
##
# Returns the <code>Symbol</code> corresponding to <i>str</i>, creating the
# symbol if it did not previously exist. See <code>Symbol#id2name</code>.
# 
#    "Koala".intern         #=> :Koala
#    s = 'cat'.to_sym       #=> :cat
#    s == :cat              #=> true
#    s = '@cat'.to_sym      #=> :@cat
#    s == :@cat             #=> true
# 
# This can also be used to create symbols that cannot be represented using the
# <code>:xxx</code> notation.
# 
#    'cat and dog'.to_sym   #=> :"cat and dog"
def to_sym; :a; end
##
# Return the <code>Integer</code> ordinal of a one-character string.
# 
#    "a".ord         #=> 97
def ord; 0; end
##
# Returns <code>true</code> if <i>str</i> contains the given string or
# character.
# 
#    "hello".include? "lo"   #=> true
#    "hello".include? "ol"   #=> false
#    "hello".include? ?h     #=> true
def include? other_str; true || false; end
##
# Returns true if +str+ starts with one of the +prefixes+ given.
# 
#   "hello".start_with?("hell")               #=> true
# 
#   # returns true if one of the prefixes matches.
#   "hello".start_with?("heaven", "hell")     #=> true
#   "hello".start_with?("heaven", "paradise") #=> false
def start_with?(); true || false; end
##
# Returns true if +str+ ends with one of the +suffixes+ given.
def end_with?(); true || false; end
##
# Both forms iterate through <i>str</i>, matching the pattern (which may be a
# <code>Regexp</code> or a <code>String</code>). For each match, a result is
# generated and either added to the result array or passed to the block. If
# the pattern contains no groups, each individual result consists of the
# matched string, <code>$&</code>.  If the pattern contains groups, each
# individual result is itself an array containing one entry per group.
# 
#    a = "cruel world"
#    a.scan(/\w+/)        #=> ["cruel", "world"]
#    a.scan(/.../)        #=> ["cru", "el ", "wor"]
#    a.scan(/(...)/)      #=> [["cru"], ["el "], ["wor"]]
#    a.scan(/(..)(..)/)   #=> [["cr", "ue"], ["l ", "wo"]]
# 
# And the block form:
# 
#    a.scan(/\w+/) {|w| print "<<#{w}>> " }
#    print "\n"
#    a.scan(/(.)(.)/) {|x,y| print y, x }
#    print "\n"
# 
# <em>produces:</em>
# 
#    <<cruel>> <<world>>
#    rceu lowlr
def scan(pattern); ''; end
##
# If <i>integer</i> is greater than the length of <i>str</i>, returns a new
# <code>String</code> of length <i>integer</i> with <i>str</i> left justified
# and padded with <i>padstr</i>; otherwise, returns <i>str</i>.
# 
#    "hello".ljust(4)            #=> "hello"
#    "hello".ljust(20)           #=> "hello               "
#    "hello".ljust(20, '1234')   #=> "hello123412341234123"
def ljust(integer, padstr=' '); ''; end
##
# If <i>integer</i> is greater than the length of <i>str</i>, returns a new
# <code>String</code> of length <i>integer</i> with <i>str</i> right justified
# and padded with <i>padstr</i>; otherwise, returns <i>str</i>.
# 
#    "hello".rjust(4)            #=> "hello"
#    "hello".rjust(20)           #=> "               hello"
#    "hello".rjust(20, '1234')   #=> "123412341234123hello"
def rjust(integer, padstr=' '); ''; end
##
# Centers +str+ in +width+.  If +width+ is greater than the length of +str+,
# returns a new String of length +width+ with +str+ centered and padded with
# +padstr+; otherwise, returns +str+.
# 
#    "hello".center(4)         #=> "hello"
#    "hello".center(20)        #=> "       hello        "
#    "hello".center(20, '123') #=> "1231231hello12312312"
def center(width, padstr=' '); ''; end
##
# Returns a copy of +str+ with the _first_ occurrence of +pattern+
# replaced by the second argument. The +pattern+ is typically a Regexp; if
# given as a String, any regular expression metacharacters it contains will
# be interpreted literally, e.g. <code>'\\\d'</code> will match a backlash
# followed by 'd', instead of a digit.
# 
# If +replacement+ is a String it will be substituted for the matched text.
# It may contain back-references to the pattern's capture groups of the form
# <code>"\\d"</code>, where <i>d</i> is a group number, or
# <code>"\\k<n>"</code>, where <i>n</i> is a group name. If it is a
# double-quoted string, both back-references must be preceded by an
# additional backslash. However, within +replacement+ the special match
# variables, such as <code>&$</code>, will not refer to the current match.
# 
# If the second argument is a Hash, and the matched text is one of its keys,
# the corresponding value is the replacement string.
# 
# In the block form, the current match string is passed in as a parameter,
# and variables such as <code>$1</code>, <code>$2</code>, <code>$`</code>,
# <code>$&</code>, and <code>$'</code> will be set appropriately. The value
# returned by the block will be substituted for the match on each call.
# 
# The result inherits any tainting in the original string or any supplied
# replacement string.
# 
#    "hello".sub(/[aeiou]/, '*')                  #=> "h*llo"
#    "hello".sub(/([aeiou])/, '<\1>')             #=> "h<e>llo"
#    "hello".sub(/./) {|s| s.ord.to_s + ' ' }     #=> "104 ello"
#    "hello".sub(/(?<foo>[aeiou])/, '*\k<foo>*')  #=> "h*e*llo"
#    'Is SHELL your preferred shell?'.sub(/[[:upper:]]{2,}/, ENV)
#     #=> "Is /bin/bash your preferred shell?"
def sub(pattern, replacement); ''; end
##
# Returns a copy of <i>str</i> with the <em>all</em> occurrences of
# <i>pattern</i> substituted for the second argument. The <i>pattern</i> is
# typically a <code>Regexp</code>; if given as a <code>String</code>, any
# regular expression metacharacters it contains will be interpreted
# literally, e.g. <code>'\\\d'</code> will match a backlash followed by 'd',
# instead of a digit.
# 
# If <i>replacement</i> is a <code>String</code> it will be substituted for
# the matched text. It may contain back-references to the pattern's capture
# groups of the form <code>\\\d</code>, where <i>d</i> is a group number, or
# <code>\\\k<n></code>, where <i>n</i> is a group name. If it is a
# double-quoted string, both back-references must be preceded by an
# additional backslash. However, within <i>replacement</i> the special match
# variables, such as <code>&$</code>, will not refer to the current match.
# 
# If the second argument is a <code>Hash</code>, and the matched text is one
# of its keys, the corresponding value is the replacement string.
# 
# In the block form, the current match string is passed in as a parameter,
# and variables such as <code>$1</code>, <code>$2</code>, <code>$`</code>,
# <code>$&</code>, and <code>$'</code> will be set appropriately. The value
# returned by the block will be substituted for the match on each call.
# 
# The result inherits any tainting in the original string or any supplied
# replacement string.
# 
# When neither a block nor a second argument is supplied, an
# <code>Enumerator</code> is returned.
# 
#    "hello".gsub(/[aeiou]/, '*')                  #=> "h*ll*"
#    "hello".gsub(/([aeiou])/, '<\1>')             #=> "h<e>ll<o>"
#    "hello".gsub(/./) {|s| s.ord.to_s + ' '}      #=> "104 101 108 108 111 "
#    "hello".gsub(/(?<foo>[aeiou])/, '{\k<foo>}')  #=> "h{e}ll{o}"
#    'hello'.gsub(/[eo]/, 'e' => 3, 'o' => '*')    #=> "h3ll*"
def gsub(pattern, replacement); Enumerator.new; end
##
# Returns a new <code>String</code> with the last character removed.  If the
# string ends with <code>\r\n</code>, both characters are removed. Applying
# <code>chop</code> to an empty string returns an empty
# string. <code>String#chomp</code> is often a safer alternative, as it leaves
# the string unchanged if it doesn't end in a record separator.
# 
#    "string\r\n".chop   #=> "string"
#    "string\n\r".chop   #=> "string\n"
#    "string\n".chop     #=> "string"
#    "string".chop       #=> "strin"
#    "x".chop.chop       #=> ""
def chop; ''; end
##
# Returns a new <code>String</code> with the given record separator removed
# from the end of <i>str</i> (if present). If <code>$/</code> has not been
# changed from the default Ruby record separator, then <code>chomp</code> also
# removes carriage return characters (that is it will remove <code>\n</code>,
# <code>\r</code>, and <code>\r\n</code>).
# 
#    "hello".chomp            #=> "hello"
#    "hello\n".chomp          #=> "hello"
#    "hello\r\n".chomp        #=> "hello"
#    "hello\n\r".chomp        #=> "hello\n"
#    "hello\r".chomp          #=> "hello"
#    "hello \n there".chomp   #=> "hello \n there"
#    "hello".chomp("llo")     #=> "he"
def chomp(separator=$/); ''; end
##
# Returns a copy of <i>str</i> with leading and trailing whitespace removed.
# 
#    "    hello    ".strip   #=> "hello"
#    "\tgoodbye\r\n".strip   #=> "goodbye"
def strip; ''; end
##
# Returns a copy of <i>str</i> with leading whitespace removed. See also
# <code>String#rstrip</code> and <code>String#strip</code>.
# 
#    "  hello  ".lstrip   #=> "hello  "
#    "hello".lstrip       #=> "hello"
def lstrip; ''; end
##
# Returns a copy of <i>str</i> with trailing whitespace removed. See also
# <code>String#lstrip</code> and <code>String#strip</code>.
# 
#    "  hello  ".rstrip   #=> "  hello"
#    "hello".rstrip       #=> "hello"
def rstrip; ''; end
##
# Performs the same substitution as String#sub in-place.
# 
# Returns +str+ if a substitution was performed or +nil+ if no substitution
# was performed.
def sub!(pattern, replacement); '' || nil; end
##
# Performs the substitutions of <code>String#gsub</code> in place, returning
# <i>str</i>, or <code>nil</code> if no substitutions were performed.
# If no block and no <i>replacement</i> is given, an enumerator is returned instead.
def gsub!(pattern, replacement); Enumerator.new; end
##
# Processes <i>str</i> as for <code>String#chop</code>, returning <i>str</i>,
# or <code>nil</code> if <i>str</i> is the empty string.  See also
# <code>String#chomp!</code>.
def chop!; '' || nil; end
##
# Modifies <i>str</i> in place as described for <code>String#chomp</code>,
# returning <i>str</i>, or <code>nil</code> if no modifications were made.
def chomp!(separator=$/); '' || nil; end
##
# Removes leading and trailing whitespace from <i>str</i>. Returns
# <code>nil</code> if <i>str</i> was not altered.
def strip!; '' || nil; end
##
# Removes leading whitespace from <i>str</i>, returning <code>nil</code> if no
# change was made. See also <code>String#rstrip!</code> and
# <code>String#strip!</code>.
# 
#    "  hello  ".lstrip   #=> "hello  "
#    "hello".lstrip!      #=> nil
def lstrip!; self || nil; end
##
# Removes trailing whitespace from <i>str</i>, returning <code>nil</code> if
# no change was made. See also <code>String#lstrip!</code> and
# <code>String#strip!</code>.
# 
#    "  hello  ".rstrip   #=> "  hello"
#    "hello".rstrip!      #=> nil
def rstrip!; self || nil; end
##
# Returns a copy of +str+ with the characters in +from_str+ replaced by the
# corresponding characters in +to_str+.  If +to_str+ is shorter than
# +from_str+, it is padded with its last character in order to maintain the
# correspondence.
# 
#    "hello".tr('el', 'ip')      #=> "hippo"
#    "hello".tr('aeiou', '*')    #=> "h*ll*"
#    "hello".tr('aeiou', 'AA*')  #=> "hAll*"
# 
# Both strings may use the <code>c1-c2</code> notation to denote ranges of
# characters, and +from_str+ may start with a <code>^</code>, which denotes
# all characters except those listed.
# 
#    "hello".tr('a-y', 'b-z')    #=> "ifmmp"
#    "hello".tr('^aeiou', '*')   #=> "*e**o"
# 
# The backslash character <code>\</code> can be used to escape
# <code>^</code> or <code>-</code> and is otherwise ignored unless it
# appears at the end of a range or the end of the +from_str+ or +to_str+:
# 
#    "hello^world".tr("\\^aeiou", "*") #=> "h*ll**w*rld"
#    "hello-world".tr("a\\-eo", "*")   #=> "h*ll**w*rld"
# 
#    "hello\r\nworld".tr("\r", "")   #=> "hello\nworld"
#    "hello\r\nworld".tr("\\r", "")  #=> "hello\r\nwold"
#    "hello\r\nworld".tr("\\\r", "") #=> "hello\nworld"
# 
#    "X['\\b']".tr("X\\", "")   #=> "['b']"
#    "X['\\b']".tr("X-\\]", "") #=> "'b'"
def tr(from_str, to_str); ''; end
##
# Processes a copy of <i>str</i> as described under <code>String#tr</code>,
# then removes duplicate characters in regions that were affected by the
# translation.
# 
#    "hello".tr_s('l', 'r')     #=> "hero"
#    "hello".tr_s('el', '*')    #=> "h*o"
#    "hello".tr_s('el', 'hx')   #=> "hhxo"
def tr_s(from_str, to_str); ''; end
##
# Returns a copy of <i>str</i> with all characters in the intersection of its
# arguments deleted. Uses the same rules for building the set of characters as
# <code>String#count</code>.
# 
#    "hello".delete "l","lo"        #=> "heo"
#    "hello".delete "lo"            #=> "he"
#    "hello".delete "aeiou", "^e"   #=> "hell"
#    "hello".delete "ej-m"          #=> "ho"
def delete(); ''; end
##
# Builds a set of characters from the <i>other_str</i> parameter(s) using the
# procedure described for <code>String#count</code>. Returns a new string
# where runs of the same character that occur in this set are replaced by a
# single character. If no arguments are given, all runs of identical
# characters are replaced by a single character.
# 
#    "yellow moon".squeeze                  #=> "yelow mon"
#    "  now   is  the".squeeze(" ")         #=> " now is the"
#    "putters shoot balls".squeeze("m-z")   #=> "puters shot balls"
def squeeze(); ''; end
##
# Each +other_str+ parameter defines a set of characters to count.  The
# intersection of these sets defines the characters to count in +str+.  Any
# +other_str+ that starts with a caret <code>^</code> is negated.  The
# sequence <code>c1-c2</code> means all characters between c1 and c2.  The
# backslash character <code>\</code> can be used to escape <code>^</code> or
# <code>-</code> and is otherwise ignored unless it appears at the end of a
# sequence or the end of a +other_str+.
# 
#    a = "hello world"
#    a.count "lo"                   #=> 5
#    a.count "lo", "o"              #=> 2
#    a.count "hello", "^l"          #=> 4
#    a.count "ej-m"                 #=> 4
# 
#    "hello^world".count "\\^aeiou" #=> 4
#    "hello-world".count "a\\-eo"   #=> 4
# 
#    c = "hello world\\r\\n"
#    c.count "\\"                   #=> 2
#    c.count "\\A"                  #=> 0
#    c.count "X-\\w"                #=> 3
def count(); 0; end
##
# Translates <i>str</i> in place, using the same rules as
# <code>String#tr</code>. Returns <i>str</i>, or <code>nil</code> if no
# changes were made.
def tr!(from_str, to_str); '' || nil; end
##
# Performs <code>String#tr_s</code> processing on <i>str</i> in place,
# returning <i>str</i>, or <code>nil</code> if no changes were made.
def tr_s!(from_str, to_str); '' || nil; end
##
# Performs a <code>delete</code> operation in place, returning <i>str</i>, or
# <code>nil</code> if <i>str</i> was not modified.
def delete!(); '' || nil; end
##
# Squeezes <i>str</i> in place, returning either <i>str</i>, or
# <code>nil</code> if no changes were made.
def squeeze!(); '' || nil; end
##
# Splits <i>str</i> using the supplied parameter as the record
# separator (<code>$/</code> by default), passing each substring in
# turn to the supplied block.  If a zero-length record separator is
# supplied, the string is split into paragraphs delimited by
# multiple successive newlines.
# 
# If no block is given, an enumerator is returned instead.
# 
#    print "Example one\n"
#    "hello\nworld".each_line {|s| p s}
#    print "Example two\n"
#    "hello\nworld".each_line('l') {|s| p s}
#    print "Example three\n"
#    "hello\n\n\nworld".each_line('') {|s| p s}
# 
# <em>produces:</em>
# 
#    Example one
#    "hello\n"
#    "world"
#    Example two
#    "hel"
#    "l"
#    "o\nworl"
#    "d"
#    Example three
#    "hello\n\n\n"
#    "world"
def each_line(separator=$/, &block); Enumerator.new; end
##
# Passes each byte in <i>str</i> to the given block, or returns an
# enumerator if no block is given.
# 
#    "hello".each_byte {|c| print c, ' ' }
# 
# <em>produces:</em>
# 
#    104 101 108 108 111
def each_byte(&block); Enumerator.new; end
##
# Passes each character in <i>str</i> to the given block, or returns
# an enumerator if no block is given.
# 
#    "hello".each_char {|c| print c, ' ' }
# 
# <em>produces:</em>
# 
#    h e l l o
def each_char(&block); Enumerator.new; end
##
# Passes the <code>Integer</code> ordinal of each character in <i>str</i>,
# also known as a <i>codepoint</i> when applied to Unicode strings to the
# given block.
# 
# If no block is given, an enumerator is returned instead.
# 
#    "hello\u0639".each_codepoint {|c| print c, ' ' }
# 
# <em>produces:</em>
# 
#    104 101 108 108 111 1593
def each_codepoint(&block); Enumerator.new; end
##
# Returns a basic <em>n</em>-bit checksum of the characters in <i>str</i>,
# where <em>n</em> is the optional <code>Fixnum</code> parameter, defaulting
# to 16. The result is simply the sum of the binary value of each character in
# <i>str</i> modulo <code>2**n - 1</code>. This is not a particularly good
# checksum.
def sum(n=16); 0; end
##
# Deletes the specified portion from <i>str</i>, and returns the portion
# deleted.
# 
#    string = "this is a string"
#    string.slice!(2)        #=> "i"
#    string.slice!(3..6)     #=> " is "
#    string.slice!(/s.*t/)   #=> "sa st"
#    string.slice!("r")      #=> "r"
#    string                  #=> "thing"
def slice!(fixnum); '' || nil; end
##
# Searches <i>sep</i> or pattern (<i>regexp</i>) in the string
# and returns the part before it, the match, and the part
# after it.
# If it is not found, returns two empty strings and <i>str</i>.
# 
#    "hello".partition("l")         #=> ["he", "l", "lo"]
#    "hello".partition("x")         #=> ["hello", "", ""]
#    "hello".partition(/.l/)        #=> ["h", "el", "lo"]
def partition(sep); []; end
##
# Searches <i>sep</i> or pattern (<i>regexp</i>) in the string from the end
# of the string, and returns the part before it, the match, and the part
# after it.
# If it is not found, returns two empty strings and <i>str</i>.
# 
#    "hello".rpartition("l")         #=> ["hel", "l", "o"]
#    "hello".rpartition("x")         #=> ["", "", "hello"]
#    "hello".rpartition(/.l/)        #=> ["he", "ll", "o"]
def rpartition(sep); []; end
##
# Returns the Encoding object that represents the encoding of obj.
def encoding; Encoding.new; end
##
# Changes the encoding to +encoding+ and returns self.
def force_encoding(encoding); ''; end
##
# Returns a copied string whose encoding is ASCII-8BIT.
def b; ''; end
##
# Returns true for a string which encoded correctly.
# 
#   "\xc2\xa1".force_encoding("UTF-8").valid_encoding?  #=> true
#   "\xc2".force_encoding("UTF-8").valid_encoding?      #=> false
#   "\x80".force_encoding("UTF-8").valid_encoding?      #=> false
def valid_encoding?; true || false; end
##
# Returns true for a string which has only ASCII characters.
# 
#   "abc".force_encoding("UTF-8").ascii_only?          #=> true
#   "abc\u{6666}".force_encoding("UTF-8").ascii_only?  #=> false
def ascii_only?; true || false; end
##
# Returns a rational which denotes the string form.  The parser
# ignores leading whitespaces and trailing garbage.  Any digit
# sequences can be separated by an underscore.  Returns zero for null
# or garbage string.
# 
# NOTE: '0.3'.to_r isn't the same as 0.3.to_r.  The former is
# equivalent to '3/10'.to_r, but the latter isn't so.
# 
#    '  2  '.to_r       #=> (2/1)
#    '300/2'.to_r       #=> (150/1)
#    '-9.2'.to_r        #=> (-46/5)
#    '-9.2e2'.to_r      #=> (-920/1)
#    '1_234_567'.to_r   #=> (1234567/1)
#    '21 june 09'.to_r  #=> (21/1)
#    '21/06/09'.to_r    #=> (7/2)
#    'bwv 1079'.to_r    #=> (0/1)
# 
# See Kernel.Rational.
def to_r; Rational.new; end
##
# The first form returns a copy of +str+ transcoded
# to encoding +encoding+.
# The second form returns a copy of +str+ transcoded
# from src_encoding to dst_encoding.
# The last form returns a copy of +str+ transcoded to
# <tt>Encoding.default_internal</tt>.
# 
# By default, the first and second form raise
# Encoding::UndefinedConversionError for characters that are
# undefined in the destination encoding, and
# Encoding::InvalidByteSequenceError for invalid byte sequences
# in the source encoding. The last form by default does not raise
# exceptions but uses replacement strings.
# 
# Please note that conversion from an encoding +enc+ to the
# same encoding +enc+ is a no-op, i.e. the receiver is returned without
# any changes, and no exceptions are raised, even if there are invalid bytes.
# 
# The +options+ Hash gives details for conversion and can have the following
# keys:
# 
# :invalid ::
#   If the value is +:replace+, #encode replaces invalid byte sequences in
#   +str+ with the replacement character.  The default is to raise the
#   Encoding::InvalidByteSequenceError exception
# :undef ::
#   If the value is +:replace+, #encode replaces characters which are
#   undefined in the destination encoding with the replacement character.
#   The default is to raise the Encoding::UndefinedConversionError.
# :replace ::
#   Sets the replacement string to the given value. The default replacement
#   string is "\uFFFD" for Unicode encoding forms, and "?" otherwise.
# :fallback ::
#   Sets the replacement string by the given object for undefined
#   character.  The object should be a Hash, a Proc, a Method, or an
#   object which has [] method.
#   Its key is an undefined character encoded in the source encoding
#   of current transcoder. Its value can be any encoding until it
#   can be converted into the destination encoding of the transcoder.
# :xml ::
#   The value must be +:text+ or +:attr+.
#   If the value is +:text+ #encode replaces undefined characters with their
#   (upper-case hexadecimal) numeric character references. '&', '<', and '>'
#   are converted to "&amp;", "&lt;", and "&gt;", respectively.
#   If the value is +:attr+, #encode also quotes the replacement result
#   (using '"'), and replaces '"' with "&quot;".
# :cr_newline ::
#   Replaces LF ("\n") with CR ("\r") if value is true.
# :crlf_newline ::
#   Replaces LF ("\n") with CRLF ("\r\n") if value is true.
# :universal_newline ::
#   Replaces CRLF ("\r\n") and CR ("\r") with LF ("\n") if value is true.
def encode(encoding  , options=0); ''; end
##
# The first form transcodes the contents of <i>str</i> from
# str.encoding to +encoding+.
# The second form transcodes the contents of <i>str</i> from
# src_encoding to dst_encoding.
# The options Hash gives details for conversion. See String#encode
# for details.
# Returns the string even if no changes were made.
def encode!(encoding  , options=0); ''; end
##
# Decodes <i>str</i> (which may contain binary data) according to the
# format string, returning an array of each value extracted. The
# format string consists of a sequence of single-character directives,
# summarized in the table at the end of this entry.
# Each directive may be followed
# by a number, indicating the number of times to repeat with this
# directive. An asterisk (``<code>*</code>'') will use up all
# remaining elements. The directives <code>sSiIlL</code> may each be
# followed by an underscore (``<code>_</code>'') or
# exclamation mark (``<code>!</code>'') to use the underlying
# platform's native size for the specified type; otherwise, it uses a
# platform-independent consistent size. Spaces are ignored in the
# format string. See also <code>Array#pack</code>.
# 
#    "abc \0\0abc \0\0".unpack('A6Z6')   #=> ["abc", "abc "]
#    "abc \0\0".unpack('a3a3')           #=> ["abc", " \000\000"]
#    "abc \0abc \0".unpack('Z*Z*')       #=> ["abc ", "abc "]
#    "aa".unpack('b8B8')                 #=> ["10000110", "01100001"]
#    "aaa".unpack('h2H2c')               #=> ["16", "61", 97]
#    "\xfe\xff\xfe\xff".unpack('sS')     #=> [-2, 65534]
#    "now=20is".unpack('M*')             #=> ["now is"]
#    "whole".unpack('xax2aX2aX1aX2a')    #=> ["h", "e", "l", "l", "o"]
# 
# This table summarizes the various formats and the Ruby classes
# returned by each.
# 
#  Integer      |         |
#  Directive    | Returns | Meaning
#  -----------------------------------------------------------------
#     C         | Integer | 8-bit unsigned (unsigned char)
#     S         | Integer | 16-bit unsigned, native endian (uint16_t)
#     L         | Integer | 32-bit unsigned, native endian (uint32_t)
#     Q         | Integer | 64-bit unsigned, native endian (uint64_t)
#               |         |
#     c         | Integer | 8-bit signed (signed char)
#     s         | Integer | 16-bit signed, native endian (int16_t)
#     l         | Integer | 32-bit signed, native endian (int32_t)
#     q         | Integer | 64-bit signed, native endian (int64_t)
#               |         |
#     S_, S!    | Integer | unsigned short, native endian
#     I, I_, I! | Integer | unsigned int, native endian
#     L_, L!    | Integer | unsigned long, native endian
#               |         |
#     s_, s!    | Integer | signed short, native endian
#     i, i_, i! | Integer | signed int, native endian
#     l_, l!    | Integer | signed long, native endian
#               |         |
#     S> L> Q>  | Integer | same as the directives without ">" except
#     s> l> q>  |         | big endian
#     S!> I!>   |         | (available since Ruby 1.9.3)
#     L!> Q!>   |         | "S>" is same as "n"
#     s!> i!>   |         | "L>" is same as "N"
#     l!> q!>   |         |
#               |         |
#     S< L< Q<  | Integer | same as the directives without "<" except
#     s< l< q<  |         | little endian
#     S!< I!<   |         | (available since Ruby 1.9.3)
#     L!< Q!<   |         | "S<" is same as "v"
#     s!< i!<   |         | "L<" is same as "V"
#     l!< q!<   |         |
#               |         |
#     n         | Integer | 16-bit unsigned, network (big-endian) byte order
#     N         | Integer | 32-bit unsigned, network (big-endian) byte order
#     v         | Integer | 16-bit unsigned, VAX (little-endian) byte order
#     V         | Integer | 32-bit unsigned, VAX (little-endian) byte order
#               |         |
#     U         | Integer | UTF-8 character
#     w         | Integer | BER-compressed integer (see Array.pack)
# 
#  Float        |         |
#  Directive    | Returns | Meaning
#  -----------------------------------------------------------------
#     D, d      | Float   | double-precision, native format
#     F, f      | Float   | single-precision, native format
#     E         | Float   | double-precision, little-endian byte order
#     e         | Float   | single-precision, little-endian byte order
#     G         | Float   | double-precision, network (big-endian) byte order
#     g         | Float   | single-precision, network (big-endian) byte order
# 
#  String       |         |
#  Directive    | Returns | Meaning
#  -----------------------------------------------------------------
#     A         | String  | arbitrary binary string (remove trailing nulls and ASCII spaces)
#     a         | String  | arbitrary binary string
#     Z         | String  | null-terminated string
#     B         | String  | bit string (MSB first)
#     b         | String  | bit string (LSB first)
#     H         | String  | hex string (high nibble first)
#     h         | String  | hex string (low nibble first)
#     u         | String  | UU-encoded string
#     M         | String  | quoted-printable, MIME encoding (see RFC2045)
#     m         | String  | base64 encoded string (RFC 2045) (default)
#               |         | base64 encoded string (RFC 4648) if followed by 0
#     P         | String  | pointer to a structure (fixed-length string)
#     p         | String  | pointer to a null-terminated string
# 
#  Misc.        |         |
#  Directive    | Returns | Meaning
#  -----------------------------------------------------------------
#     @         | ---     | skip to the offset given by the length argument
#     X         | ---     | skip backward one byte
#     x         | ---     | skip forward one byte
def unpack(format); []; end
##
# Returns a complex which denotes the string form.  The parser
# ignores leading whitespaces and trailing garbage.  Any digit
# sequences can be separated by an underscore.  Returns zero for null
# or garbage string.
# 
#    '9'.to_c           #=> (9+0i)
#    '2.5'.to_c         #=> (2.5+0i)
#    '2.5/1'.to_c       #=> ((5/2)+0i)
#    '-3/2'.to_c        #=> ((-3/2)+0i)
#    '-i'.to_c          #=> (0-1i)
#    '45i'.to_c         #=> (0+45i)
#    '3-4i'.to_c        #=> (3-4i)
#    '-4e2-4e-2i'.to_c  #=> (-400.0-0.04i)
#    '-0.0-0.0i'.to_c   #=> (-0.0-0.0i)
#    '1/2+3/4i'.to_c    #=> ((1/2)+(3/4)*i)
#    'ruby'.to_c        #=> (0+0i)
# 
# See Kernel.Complex.
def to_c; Complex.new; end
end

##
# <code>Symbol</code> objects represent names and some strings
# inside the Ruby
# interpreter. They are generated using the <code>:name</code> and
# <code>:"string"</code> literals
# syntax, and by the various <code>to_sym</code> methods. The same
# <code>Symbol</code> object will be created for a given name or string
# for the duration of a program's execution, regardless of the context
# or meaning of that name. Thus if <code>Fred</code> is a constant in
# one context, a method in another, and a class in a third, the
# <code>Symbol</code> <code>:Fred</code> will be the same object in
# all three contexts.
# 
#    module One
#      class Fred
#      end
#      $f1 = :Fred
#    end
#    module Two
#      Fred = 1
#      $f2 = :Fred
#    end
#    def Fred()
#    end
#    $f3 = :Fred
#    $f1.object_id   #=> 2514190
#    $f2.object_id   #=> 2514190
#    $f3.object_id   #=> 2514190
class Symbol < Object
include Comparable
##
# Returns an array of all the symbols currently in Ruby's symbol
# table.
# 
#    Symbol.all_symbols.size    #=> 903
#    Symbol.all_symbols[1,20]   #=> [:floor, :ARGV, :Binding, :symlink,
#                                    :chown, :EOFError, :$;, :String,
#                                    :LOCK_SH, :"setuid?", :$<,
#                                    :default_proc, :compact, :extend,
#                                    :Tms, :getwd, :$=, :ThreadGroup,
#                                    :wait2, :$>]
def self.all_symbols; []; end
##
# Equality---If <i>sym</i> and <i>obj</i> are exactly the same
# symbol, returns <code>true</code>.
def ==; true || false; end
##
# Equality---If <i>sym</i> and <i>obj</i> are exactly the same
# symbol, returns <code>true</code>.
def ===; true || false; end
##
# Returns the representation of <i>sym</i> as a symbol literal.
# 
#    :fred.inspect   #=> ":fred"
def inspect; ''; end
##
# Returns the name or string corresponding to <i>sym</i>.
# 
#    :fred.id2name   #=> "fred"
def id2name; ''; end
##
# Returns the name or string corresponding to <i>sym</i>.
# 
#    :fred.id2name   #=> "fred"
def to_s; ''; end
##
# In general, <code>to_sym</code> returns the <code>Symbol</code> corresponding
# to an object. As <i>sym</i> is already a symbol, <code>self</code> is returned
# in this case.
def to_sym; :a; end
##
# In general, <code>to_sym</code> returns the <code>Symbol</code> corresponding
# to an object. As <i>sym</i> is already a symbol, <code>self</code> is returned
# in this case.
def intern; :a; end
##
# Returns a _Proc_ object which respond to the given method by _sym_.
# 
#   (1..3).collect(&:to_s)  #=> ["1", "2", "3"]
def to_proc; end
##
# Same as <code>sym.to_s.succ.intern</code>.
def succ; end
##
# Compares +symbol+ with +other_symbol+ after calling #to_s on each of the
# symbols. Returns -1, 0, +1 or nil depending on whether +symbol+ is less
# than, equal to, or greater than +other_symbol+.
# 
#  +nil+ is returned if the two values are incomparable.
# 
# See String#<=> for more information.
def <=>; 1 || nil; end
##
# Case-insensitive version of <code>Symbol#<=></code>.
def casecmp(other); 1 || nil; end
##
# Returns <code>sym.to_s =~ obj</code>.
def =~; 1 || nil; end
##
# Returns <code>sym.to_s[]</code>.
def []; ''; end
##
# Returns <code>sym.to_s[]</code>.
def slice; ''; end
##
# Same as <code>sym.to_s.length</code>.
def length; 0; end
##
# Returns that _sym_ is :"" or not.
def empty?; true || false; end
##
# Returns <code>sym.to_s =~ obj</code>.
def match; 1 || nil; end
##
# Same as <code>sym.to_s.upcase.intern</code>.
def upcase; :a; end
##
# Same as <code>sym.to_s.downcase.intern</code>.
def downcase; :a; end
##
# Same as <code>sym.to_s.capitalize.intern</code>.
def capitalize; :a; end
##
# Same as <code>sym.to_s.swapcase.intern</code>.
def swapcase; :a; end
##
# Returns the Encoding object that represents the encoding of _sym_.
def encoding; Encoding.new; end
end

##
# <code>Proc</code> objects are blocks of code that have been bound to
# a set of local variables. Once bound, the code may be called in
# different contexts and still access those variables.
# 
#    def gen_times(factor)
#      return Proc.new {|n| n*factor }
#    end
# 
#    times3 = gen_times(3)
#    times5 = gen_times(5)
# 
#    times3.call(12)               #=> 36
#    times5.call(5)                #=> 25
#    times3.call(times5.call(4))   #=> 60
class Proc < Object
##
# Creates a new <code>Proc</code> object, bound to the current
# context. <code>Proc::new</code> may be called without a block only
# within a method with an attached block, in which case that block is
# converted to the <code>Proc</code> object.
# 
#    def proc_from
#      Proc.new
#    end
#    proc = proc_from { "hello" }
#    proc.call   #=> "hello"
def self.new(&block); end
##
# Invokes the block, setting the block's parameters to the values in
# <i>params</i> using something close to method calling semantics.
# Generates a warning if multiple values are passed to a proc that
# expects just one (previously this silently converted the parameters
# to an array).  Note that prc.() invokes prc.call() with the parameters
# given.  It's a syntax sugar to hide "call".
# 
# For procs created using <code>lambda</code> or <code>->()</code> an error
# is generated if the wrong number of parameters are passed to a Proc with
# multiple parameters.  For procs created using <code>Proc.new</code> or
# <code>Kernel.proc</code>, extra parameters are silently discarded.
# 
# Returns the value of the last expression evaluated in the block. See
# also <code>Proc#yield</code>.
# 
#    a_proc = Proc.new {|a, *b| b.collect {|i| i*a }}
#    a_proc.call(9, 1, 2, 3)   #=> [9, 18, 27]
#    a_proc[9, 1, 2, 3]        #=> [9, 18, 27]
#    a_proc = lambda {|a,b| a}
#    a_proc.call(1,2,3)
# 
# <em>produces:</em>
# 
#    prog.rb:4:in `block in <main>': wrong number of arguments (3 for 2) (ArgumentError)
#     from prog.rb:5:in `call'
#     from prog.rb:5:in `<main>'
def call(); Object.new; end
##
# Invokes the block, setting the block's parameters to the values in
# <i>params</i> using something close to method calling semantics.
# Generates a warning if multiple values are passed to a proc that
# expects just one (previously this silently converted the parameters
# to an array).  Note that prc.() invokes prc.call() with the parameters
# given.  It's a syntax sugar to hide "call".
# 
# For procs created using <code>lambda</code> or <code>->()</code> an error
# is generated if the wrong number of parameters are passed to a Proc with
# multiple parameters.  For procs created using <code>Proc.new</code> or
# <code>Kernel.proc</code>, extra parameters are silently discarded.
# 
# Returns the value of the last expression evaluated in the block. See
# also <code>Proc#yield</code>.
# 
#    a_proc = Proc.new {|a, *b| b.collect {|i| i*a }}
#    a_proc.call(9, 1, 2, 3)   #=> [9, 18, 27]
#    a_proc[9, 1, 2, 3]        #=> [9, 18, 27]
#    a_proc = lambda {|a,b| a}
#    a_proc.call(1,2,3)
# 
# <em>produces:</em>
# 
#    prog.rb:4:in `block in <main>': wrong number of arguments (3 for 2) (ArgumentError)
#     from prog.rb:5:in `call'
#     from prog.rb:5:in `<main>'
def []; Object.new; end
##
# Invokes the block with +obj+ as the proc's parameter like Proc#call.  It
# is to allow a proc object to be a target of +when+ clause in a case
# statement.
def ===; Proc.new; end
##
# Invokes the block, setting the block's parameters to the values in
# <i>params</i> using something close to method calling semantics.
# Generates a warning if multiple values are passed to a proc that
# expects just one (previously this silently converted the parameters
# to an array).  Note that prc.() invokes prc.call() with the parameters
# given.  It's a syntax sugar to hide "call".
# 
# For procs created using <code>lambda</code> or <code>->()</code> an error
# is generated if the wrong number of parameters are passed to a Proc with
# multiple parameters.  For procs created using <code>Proc.new</code> or
# <code>Kernel.proc</code>, extra parameters are silently discarded.
# 
# Returns the value of the last expression evaluated in the block. See
# also <code>Proc#yield</code>.
# 
#    a_proc = Proc.new {|a, *b| b.collect {|i| i*a }}
#    a_proc.call(9, 1, 2, 3)   #=> [9, 18, 27]
#    a_proc[9, 1, 2, 3]        #=> [9, 18, 27]
#    a_proc = lambda {|a,b| a}
#    a_proc.call(1,2,3)
# 
# <em>produces:</em>
# 
#    prog.rb:4:in `block in <main>': wrong number of arguments (3 for 2) (ArgumentError)
#     from prog.rb:5:in `call'
#     from prog.rb:5:in `<main>'
def yield(); Object.new; end
##
# Part of the protocol for converting objects to <code>Proc</code>
# objects. Instances of class <code>Proc</code> simply return
# themselves.
def to_proc; Proc.new; end
##
# Returns the number of arguments that would not be ignored. If the block
# is declared to take no arguments, returns 0. If the block is known
# to take exactly n arguments, returns n. If the block has optional
# arguments, return -n-1, where n is the number of mandatory
# arguments. A <code>proc</code> with no argument declarations
# is the same a block declaring <code>||</code> as its arguments.
# 
#    proc {}.arity          #=>  0
#    proc {||}.arity        #=>  0
#    proc {|a|}.arity       #=>  1
#    proc {|a,b|}.arity     #=>  2
#    proc {|a,b,c|}.arity   #=>  3
#    proc {|*a|}.arity      #=> -1
#    proc {|a,*b|}.arity    #=> -2
#    proc {|a,*b, c|}.arity #=> -3
# 
#    proc   { |x = 0| }.arity       #=> 0
#    lambda { |a = 0| }.arity       #=> -1
#    proc   { |x=0, y| }.arity      #=> 0
#    lambda { |x=0, y| }.arity      #=> -2
#    proc   { |x=0, y=0| }.arity    #=> 0
#    lambda { |x=0, y=0| }.arity    #=> -1
#    proc   { |x, y=0| }.arity      #=> 1
#    lambda { |x, y=0| }.arity      #=> -2
#    proc   { |(x, y), z=0| }.arity #=> 1
#    lambda { |(x, y), z=0| }.arity #=> -2
def arity; 0; end
##
# Returns a hash value corresponding to proc body.
def hash; 0; end
##
# Returns the unique identifier for this proc, along with
# an indication of where the proc was defined.
def to_s; ''; end
##
# Returns +true+ for a Proc object for which argument handling is rigid.
# Such procs are typically generated by +lambda+.
# 
# A Proc object generated by +proc+ ignores extra arguments.
# 
#   proc {|a,b| [a,b] }.call(1,2,3)    #=> [1,2]
# 
# It provides +nil+ for missing arguments.
# 
#   proc {|a,b| [a,b] }.call(1)        #=> [1,nil]
# 
# It expands a single array argument.
# 
#   proc {|a,b| [a,b] }.call([1,2])    #=> [1,2]
# 
# A Proc object generated by +lambda+ doesn't have such tricks.
# 
#   lambda {|a,b| [a,b] }.call(1,2,3)  #=> ArgumentError
#   lambda {|a,b| [a,b] }.call(1)      #=> ArgumentError
#   lambda {|a,b| [a,b] }.call([1,2])  #=> ArgumentError
# 
# Proc#lambda? is a predicate for the tricks.
# It returns +true+ if no tricks apply.
# 
#   lambda {}.lambda?            #=> true
#   proc {}.lambda?              #=> false
# 
# Proc.new is the same as +proc+.
# 
#   Proc.new {}.lambda?          #=> false
# 
# +lambda+, +proc+ and Proc.new preserve the tricks of
# a Proc object given by <code>&</code> argument.
# 
#   lambda(&lambda {}).lambda?   #=> true
#   proc(&lambda {}).lambda?     #=> true
#   Proc.new(&lambda {}).lambda? #=> true
# 
#   lambda(&proc {}).lambda?     #=> false
#   proc(&proc {}).lambda?       #=> false
#   Proc.new(&proc {}).lambda?   #=> false
# 
# A Proc object generated by <code>&</code> argument has the tricks
# 
#   def n(&b) b.lambda? end
#   n {}                         #=> false
# 
# The <code>&</code> argument preserves the tricks if a Proc object
# is given by <code>&</code> argument.
# 
#   n(&lambda {})                #=> true
#   n(&proc {})                  #=> false
#   n(&Proc.new {})              #=> false
# 
# A Proc object converted from a method has no tricks.
# 
#   def m() end
#   method(:m).to_proc.lambda?   #=> true
# 
#   n(&method(:m))               #=> true
#   n(&method(:m).to_proc)       #=> true
# 
# +define_method+ is treated the same as method definition.
# The defined method has no tricks.
# 
#   class C
#     define_method(:d) {}
#   end
#   C.new.d(1,2)       #=> ArgumentError
#   C.new.method(:d).to_proc.lambda?   #=> true
# 
# +define_method+ always defines a method without the tricks,
# even if a non-lambda Proc object is given.
# This is the only exception for which the tricks are not preserved.
# 
#   class C
#     define_method(:e, &proc {})
#   end
#   C.new.e(1,2)       #=> ArgumentError
#   C.new.method(:e).to_proc.lambda?   #=> true
# 
# This exception insures that methods never have tricks
# and makes it easy to have wrappers to define methods that behave as usual.
# 
#   class C
#     def self.def2(name, &body)
#       define_method(name, &body)
#     end
# 
#     def2(:f) {}
#   end
#   C.new.f(1,2)       #=> ArgumentError
# 
# The wrapper <i>def2</i> defines a method which has no tricks.
def lambda?; true || false; end
##
# Returns the binding associated with <i>prc</i>. Note that
# <code>Kernel#eval</code> accepts either a <code>Proc</code> or a
# <code>Binding</code> object as its second parameter.
# 
#    def fred(param)
#      proc {}
#    end
# 
#    b = fred(99)
#    eval("param", b.binding)   #=> 99
def binding; Binding.new; end
##
# Returns a curried proc. If the optional <i>arity</i> argument is given,
# it determines the number of arguments.
# A curried proc receives some arguments. If a sufficient number of
# arguments are supplied, it passes the supplied arguments to the original
# proc and returns the result. Otherwise, returns another curried proc that
# takes the rest of arguments.
# 
#    b = proc {|x, y, z| (x||0) + (y||0) + (z||0) }
#    p b.curry[1][2][3]           #=> 6
#    p b.curry[1, 2][3, 4]        #=> 6
#    p b.curry(5)[1][2][3][4][5]  #=> 6
#    p b.curry(5)[1, 2][3, 4][5]  #=> 6
#    p b.curry(1)[1]              #=> 1
# 
#    b = proc {|x, y, z, *w| (x||0) + (y||0) + (z||0) + w.inject(0, &:+) }
#    p b.curry[1][2][3]           #=> 6
#    p b.curry[1, 2][3, 4]        #=> 10
#    p b.curry(5)[1][2][3][4][5]  #=> 15
#    p b.curry(5)[1, 2][3, 4][5]  #=> 15
#    p b.curry(1)[1]              #=> 1
# 
#    b = lambda {|x, y, z| (x||0) + (y||0) + (z||0) }
#    p b.curry[1][2][3]           #=> 6
#    p b.curry[1, 2][3, 4]        #=> wrong number of arguments (4 for 3)
#    p b.curry(5)                 #=> wrong number of arguments (5 for 3)
#    p b.curry(1)                 #=> wrong number of arguments (1 for 3)
# 
#    b = lambda {|x, y, z, *w| (x||0) + (y||0) + (z||0) + w.inject(0, &:+) }
#    p b.curry[1][2][3]           #=> 6
#    p b.curry[1, 2][3, 4]        #=> 10
#    p b.curry(5)[1][2][3][4][5]  #=> 15
#    p b.curry(5)[1, 2][3, 4][5]  #=> 15
#    p b.curry(1)                 #=> wrong number of arguments (1 for 3)
# 
#    b = proc { :foo }
#    p b.curry[]                  #=> :foo
def curry; Proc.new; end
##
# Returns the Ruby source filename and line number containing this proc
# or +nil+ if this proc was not defined in Ruby (i.e. native)
def source_location; ['', 0]; end
##
# Returns the parameter information of this proc.
# 
#    prc = lambda{|x, y=42, *other|}
#    prc.parameters  #=> [[:req, :x], [:opt, :y], [:rest, :other]]
def parameters; []; end
end

##
# Raised when Ruby can't yield as requested.
# 
# A typical scenario is attempting to yield when no block is given:
# 
#    def call_block
#      yield 42
#    end
#    call_block
# 
# <em>raises the exception:</em>
# 
#    LocalJumpError: no block given (yield)
# 
# A more subtle example:
# 
#    def get_me_a_return
#      Proc.new { return 42 }
#    end
#    get_me_a_return.call
# 
# <em>raises the exception:</em>
# 
#    LocalJumpError: unexpected return
class LocalJumpError < StandardError
##
# The reason this block was terminated:
# :break, :redo, :retry, :next, :return, or :noreason.
def reason; :a; end
end

##
# Raised in case of a stack overflow.
# 
#    def me_myself_and_i
#      me_myself_and_i
#    end
#    me_myself_and_i
# 
# <em>raises the exception:</em>
# 
#   SystemStackError: stack level too deep
class SystemStackError < Exception
end

##
# Proc   
class Method < Object
##
# Two method objects are equal if they are bound to the same
# object and refer to the same method definition and their owners are the
# same class or module.
def ==; true || false; end
##
# Two method objects are equal if they are bound to the same
# object and refer to the same method definition and their owners are the
# same class or module.
def eql?; true || false; end
##
# Returns a hash value corresponding to the method object.
def hash; 0; end
##
# Returns a clone of this method.
# 
#   class A
#     def foo
#       return "bar"
#     end
#   end
# 
#   m = A.new.method(:foo)
#   m.call # => "bar"
#   n = m.clone.call # => "bar"
def clone; Method.new; end
##
# Invokes the <i>meth</i> with the specified arguments, returning the
# method's return value.
# 
#    m = 12.method("+")
#    m.call(3)    #=> 15
#    m.call(20)   #=> 32
def call(); Object.new; end
##
# Invokes the <i>meth</i> with the specified arguments, returning the
# method's return value.
# 
#    m = 12.method("+")
#    m.call(3)    #=> 15
#    m.call(20)   #=> 32
def []; Object.new; end
##
# Returns an indication of the number of arguments accepted by a
# method. Returns a nonnegative integer for methods that take a fixed
# number of arguments. For Ruby methods that take a variable number of
# arguments, returns -n-1, where n is the number of required
# arguments. For methods written in C, returns -1 if the call takes a
# variable number of arguments.
# 
#    class C
#      def one;    end
#      def two(a); end
#      def three(*a);  end
#      def four(a, b); end
#      def five(a, b, *c);    end
#      def six(a, b, *c, &d); end
#    end
#    c = C.new
#    c.method(:one).arity     #=> 0
#    c.method(:two).arity     #=> 1
#    c.method(:three).arity   #=> -1
#    c.method(:four).arity    #=> 2
#    c.method(:five).arity    #=> -3
#    c.method(:six).arity     #=> -3
# 
#    "cat".method(:size).arity      #=> 0
#    "cat".method(:replace).arity   #=> 1
#    "cat".method(:squeeze).arity   #=> -1
#    "cat".method(:count).arity     #=> -1
def arity; 0; end
##
# Returns the name of the underlying method.
# 
#   "cat".method(:count).inspect   #=> "#<Method: String#count>"
def to_s; ''; end
##
# Returns the name of the underlying method.
# 
#   "cat".method(:count).inspect   #=> "#<Method: String#count>"
def inspect; ''; end
##
# Returns a <code>Proc</code> object corresponding to this method.
def to_proc; Proc.new; end
##
# Returns the bound receiver of the method object.
def receiver; Object.new; end
##
# Returns the name of the method.
def name; :a; end
##
# Returns the original name of the method.
def original_name; :a; end
##
# Returns the class or module that defines the method.
def owner; Class.new || Module.new; end
##
# Dissociates <i>meth</i> from its current receiver. The resulting
# <code>UnboundMethod</code> can subsequently be bound to a new object
# of the same class (see <code>UnboundMethod</code>).
def unbind; Method.new; end
##
# Returns the Ruby source filename and line number containing this method
# or nil if this method was not defined in Ruby (i.e. native)
def source_location; ['', 0]; end
##
# Returns the parameter information of this method.
def parameters; []; end
end

##
# Ruby supports two forms of objectified methods. Class
# <code>Method</code> is used to represent methods that are associated
# with a particular object: these method objects are bound to that
# object. Bound method objects for an object can be created using
# <code>Object#method</code>.
# 
# Ruby also supports unbound methods; methods objects that are not
# associated with a particular object. These can be created either by
# calling <code>Module#instance_method</code> or by calling
# <code>unbind</code> on a bound method object. The result of both of
# these is an <code>UnboundMethod</code> object.
# 
# Unbound methods can only be called after they are bound to an
# object. That object must be be a kind_of? the method's original
# class.
# 
#    class Square
#      def area
#        @side * @side
#      end
#      def initialize(side)
#        @side = side
#      end
#    end
# 
#    area_un = Square.instance_method(:area)
# 
#    s = Square.new(12)
#    area = area_un.bind(s)
#    area.call   #=> 144
# 
# Unbound methods are a reference to the method at the time it was
# objectified: subsequent changes to the underlying class will not
# affect the unbound method.
# 
#    class Test
#      def test
#        :original
#      end
#    end
#    um = Test.instance_method(:test)
#    class Test
#      def test
#        :modified
#      end
#    end
#    t = Test.new
#    t.test            #=> :modified
#    um.bind(t).call   #=> :original
class UnboundMethod < Object
##
# Two method objects are equal if they are bound to the same
# object and refer to the same method definition and their owners are the
# same class or module.
def ==; true || false; end
##
# Two method objects are equal if they are bound to the same
# object and refer to the same method definition and their owners are the
# same class or module.
def eql?; true || false; end
##
# Returns a hash value corresponding to the method object.
def hash; 0; end
##
# Returns a clone of this method.
# 
#   class A
#     def foo
#       return "bar"
#     end
#   end
# 
#   m = A.new.method(:foo)
#   m.call # => "bar"
#   n = m.clone.call # => "bar"
def clone; Method.new; end
##
# Returns an indication of the number of arguments accepted by a
# method. Returns a nonnegative integer for methods that take a fixed
# number of arguments. For Ruby methods that take a variable number of
# arguments, returns -n-1, where n is the number of required
# arguments. For methods written in C, returns -1 if the call takes a
# variable number of arguments.
# 
#    class C
#      def one;    end
#      def two(a); end
#      def three(*a);  end
#      def four(a, b); end
#      def five(a, b, *c);    end
#      def six(a, b, *c, &d); end
#    end
#    c = C.new
#    c.method(:one).arity     #=> 0
#    c.method(:two).arity     #=> 1
#    c.method(:three).arity   #=> -1
#    c.method(:four).arity    #=> 2
#    c.method(:five).arity    #=> -3
#    c.method(:six).arity     #=> -3
# 
#    "cat".method(:size).arity      #=> 0
#    "cat".method(:replace).arity   #=> 1
#    "cat".method(:squeeze).arity   #=> -1
#    "cat".method(:count).arity     #=> -1
def arity; 0; end
##
# Returns the name of the underlying method.
# 
#   "cat".method(:count).inspect   #=> "#<Method: String#count>"
def to_s; ''; end
##
# Returns the name of the underlying method.
# 
#   "cat".method(:count).inspect   #=> "#<Method: String#count>"
def inspect; ''; end
##
# Returns the name of the method.
def name; :a; end
##
# Returns the original name of the method.
def original_name; :a; end
##
# Returns the class or module that defines the method.
def owner; Class.new || Module.new; end
##
# Bind <i>umeth</i> to <i>obj</i>. If <code>Klass</code> was the class
# from which <i>umeth</i> was obtained,
# <code>obj.kind_of?(Klass)</code> must be true.
# 
#    class A
#      def test
#        puts "In test, class = #{self.class}"
#      end
#    end
#    class B < A
#    end
#    class C < B
#    end
# 
#    um = B.instance_method(:test)
#    bm = um.bind(C.new)
#    bm.call
#    bm = um.bind(B.new)
#    bm.call
#    bm = um.bind(A.new)
#    bm.call
# 
# <em>produces:</em>
# 
#    In test, class = C
#    In test, class = B
#    prog.rb:16:in `bind': bind argument must be an instance of B (TypeError)
#     from prog.rb:16
def bind(obj); Method.new; end
##
# Returns the Ruby source filename and line number containing this method
# or nil if this method was not defined in Ruby (i.e. native)
def source_location; ['', 0]; end
##
# Returns the parameter information of this method.
def parameters; []; end
end

##
# Objects of class <code>Binding</code> encapsulate the execution
# context at some particular place in the code and retain this context
# for future use. The variables, methods, value of <code>self</code>,
# and possibly an iterator block that can be accessed in this context
# are all retained. Binding objects can be created using
# <code>Kernel#binding</code>, and are made available to the callback
# of <code>Kernel#set_trace_func</code>.
# 
# These binding objects can be passed as the second argument of the
# <code>Kernel#eval</code> method, establishing an environment for the
# evaluation.
# 
#    class Demo
#      def initialize(n)
#        @secret = n
#      end
#      def get_binding
#        return binding()
#      end
#    end
# 
#    k1 = Demo.new(99)
#    b1 = k1.get_binding
#    k2 = Demo.new(-3)
#    b2 = k2.get_binding
# 
#    eval("@secret", b1)   #=> 99
#    eval("@secret", b2)   #=> -3
#    eval("@secret")       #=> nil
# 
# Binding objects have no class-specific methods.
class Binding < Object
##
# Evaluates the Ruby expression(s) in <em>string</em>, in the
# <em>binding</em>'s context.  If the optional <em>filename</em> and
# <em>lineno</em> parameters are present, they will be used when
# reporting syntax errors.
# 
#    def get_binding(param)
#      return binding
#    end
#    b = get_binding("hello")
#    b.eval("param")   #=> "hello"
def eval(string , filename=0, lineno=0); Object.new; end
end

class Module < Object
##
# Returns an +UnboundMethod+ representing the given
# instance method in _mod_.
# 
#    class Interpreter
#      def do_a() print "there, "; end
#      def do_d() print "Hello ";  end
#      def do_e() print "!\n";     end
#      def do_v() print "Dave";    end
#      Dispatcher = {
#        "a" => instance_method(:do_a),
#        "d" => instance_method(:do_d),
#        "e" => instance_method(:do_e),
#        "v" => instance_method(:do_v)
#      }
#      def interpret(string)
#        string.each_char {|b| Dispatcher[b].bind(self).call }
#      end
#    end
# 
#    interpreter = Interpreter.new
#    interpreter.interpret('dave')
# 
# <em>produces:</em>
# 
#    Hello there, Dave!
def instance_method(symbol); Method.new; end
##
# Similar to _instance_method_, searches public method only.
def public_instance_method(symbol); Method.new; end
##
# Defines an instance method in the receiver. The _method_
# parameter can be a +Proc+, a +Method+ or an +UnboundMethod+ object.
# If a block is specified, it is used as the method body. This block
# is evaluated using <code>instance_eval</code>, a point that is
# tricky to demonstrate because <code>define_method</code> is private.
# (This is why we resort to the +send+ hack in this example.)
# 
#    class A
#      def fred
#        puts "In Fred"
#      end
#      def create_method(name, &block)
#        self.class.send(:define_method, name, &block)
#      end
#      define_method(:wilma) { puts "Charge it!" }
#    end
#    class B < A
#      define_method(:barney, instance_method(:fred))
#    end
#    a = B.new
#    a.barney
#    a.wilma
#    a.create_method(:betty) { p self }
#    a.betty
# 
# <em>produces:</em>
# 
#    In Fred
#    Charge it!
#    #<B:0x401b39e8>
def define_method(symbol, method); Proc.new; end
##
# Evaluates the given block in the context of the class/module.
# The method defined in the block will belong to the receiver.
# 
#    class Thing
#    end
#    Thing.class_exec{
#      def hello() "Hello there!" end
#    }
#    puts Thing.new.hello()
# 
# <em>produces:</em>
# 
#    Hello there!
def module_exec(&block); Object.new; end
##
# Evaluates the given block in the context of the class/module.
# The method defined in the block will belong to the receiver.
# 
#    class Thing
#    end
#    Thing.class_exec{
#      def hello() "Hello there!" end
#    }
#    puts Thing.new.hello()
# 
# <em>produces:</em>
# 
#    Hello there!
def class_exec(&block); Object.new; end
##
# Evaluates the string or block in the context of _mod_, except that when
# a block is given, constant/class variable lookup is not affected. This
# can be used to add methods to a class. <code>module_eval</code> returns
# the result of evaluating its argument. The optional _filename_ and
# _lineno_ parameters set the text for error messages.
# 
#    class Thing
#    end
#    a = %q{def hello() "Hello there!" end}
#    Thing.module_eval(a)
#    puts Thing.new.hello()
#    Thing.module_eval("invalid code", "dummy", 123)
# 
# <em>produces:</em>
# 
#    Hello there!
#    dummy:123:in `module_eval': undefined local variable
#        or method `code' for Thing:Class
def class_eval(string , filename=0, lineno=0); Object.new; end
##
# Evaluates the string or block in the context of _mod_, except that when
# a block is given, constant/class variable lookup is not affected. This
# can be used to add methods to a class. <code>module_eval</code> returns
# the result of evaluating its argument. The optional _filename_ and
# _lineno_ parameters set the text for error messages.
# 
#    class Thing
#    end
#    a = %q{def hello() "Hello there!" end}
#    Thing.module_eval(a)
#    puts Thing.new.hello()
#    Thing.module_eval("invalid code", "dummy", 123)
# 
# <em>produces:</em>
# 
#    Hello there!
#    dummy:123:in `module_eval': undefined local variable
#        or method `code' for Thing:Class
def module_eval(&block); Object.new; end
##
# When this module is included in another, Ruby calls
# <code>append_features</code> in this module, passing it the
# receiving module in _mod_. Ruby's default implementation is
# to add the constants, methods, and module variables of this module
# to _mod_ if this module has not already been added to
# _mod_ or one of its ancestors. See also <code>Module#include</code>.
def append_features(mod); Module.new; end
##
# Extends the specified object by adding this module's constants and
# methods (which are added as singleton methods). This is the callback
# method used by <code>Object#extend</code>.
# 
#    module Picky
#      def Picky.extend_object(o)
#        if String === o
#          puts "Can't add Picky to a String"
#        else
#          puts "Picky added to #{o.class}"
#          super
#        end
#      end
#    end
#    (s = Array.new).extend Picky  # Call Object.extend
#    (s = "quick brown fox").extend Picky
# 
# <em>produces:</em>
# 
#    Picky added to Array
#    Can't add Picky to a String
def extend_object(obj); Object.new; end
##
# Invokes <code>Module.append_features</code> on each parameter in reverse order.
def include(); self; end
##
# When this module is prepended in another, Ruby calls
# <code>prepend_features</code> in this module, passing it the
# receiving module in _mod_. Ruby's default implementation is
# to overlay the constants, methods, and module variables of this module
# to _mod_ if this module has not already been added to
# _mod_ or one of its ancestors. See also <code>Module#prepend</code>.
def prepend_features(mod); Module.new; end
##
# Invokes <code>Module.prepend_features</code> on each parameter in reverse order.
def prepend(); self; end
##
# Refine <i>klass</i> in the receiver.
# 
# Returns an overlaid module.
def refine(klass, &block); Module.new; end
##
# Returns the list of +Modules+ nested at the point of call.
# 
#    module M1
#      module M2
#        $a = Module.nesting
#      end
#    end
#    $a           #=> [M1::M2, M1]
#    $a[0].name   #=> "M1::M2"
def self.nesting; []; end
##
# In the first form, returns an array of the names of all
# constants accessible from the point of call.
# This list includes the names of all modules and classes
# defined in the global scope.
# 
#    Module.constants.first(4)
#       # => [:ARGF, :ARGV, :ArgumentError, :Array]
# 
#    Module.constants.include?(:SEEK_SET)   # => false
# 
#    class IO
#      Module.constants.include?(:SEEK_SET) # => true
#    end
# 
# The second form calls the instance method +constants+.
def self.constants(inherit=true); []; end
##
# Removes the method identified by _symbol_ from the current
# class. For an example, see <code>Module.undef_method</code>.
# String arguments are converted to symbols.
def remove_method(symbol); self; end
##
# Prevents the current class from responding to calls to the named
# method. Contrast this with <code>remove_method</code>, which deletes
# the method from the particular class; Ruby will still search
# superclasses and mixed-in modules for a possible receiver.
# String arguments are converted to symbols.
# 
#    class Parent
#      def hello
#        puts "In parent"
#      end
#    end
#    class Child < Parent
#      def hello
#        puts "In child"
#      end
#    end
# 
#    c = Child.new
#    c.hello
# 
#    class Child
#      remove_method :hello  # remove from child, still in parent
#    end
#    c.hello
# 
#    class Child
#      undef_method :hello   # prevent any calls to 'hello'
#    end
#    c.hello
# 
# <em>produces:</em>
# 
#    In child
#    In parent
#    prog.rb:23: undefined method `hello' for #<Child:0x401b3bb4> (NoMethodError)
def undef_method(symbol); self; end
##
# Makes <i>new_name</i> a new copy of the method <i>old_name</i>. This can
# be used to retain access to methods that are overridden.
# 
#    module Mod
#      alias_method :orig_exit, :exit
#      def exit(code=0)
#        puts "Exiting with code #{code}"
#        orig_exit(code)
#      end
#    end
#    include Mod
#    exit(99)
# 
# <em>produces:</em>
# 
#    Exiting with code 99
def alias_method(new_name, old_name); self; end
##
# With no arguments, sets the default visibility for subsequently
# defined methods to public. With arguments, sets the named methods to
# have public visibility.
# String arguments are converted to symbols.
def public; self; end
##
# With no arguments, sets the default visibility for subsequently
# defined methods to protected. With arguments, sets the named methods
# to have protected visibility.
# String arguments are converted to symbols.
def protected; self; end
##
# With no arguments, sets the default visibility for subsequently
# defined methods to private. With arguments, sets the named methods
# to have private visibility.
# String arguments are converted to symbols.
# 
#    module Mod
#      def a()  end
#      def b()  end
#      private
#      def c()  end
#      private :a
#    end
#    Mod.private_instance_methods   #=> [:a, :c]
def private; self; end
##
# Creates module functions for the named methods. These functions may
# be called with the module as a receiver, and also become available
# as instance methods to classes that mix in the module. Module
# functions are copies of the original, and so may be changed
# independently. The instance-method versions are made private. If
# used with no arguments, subsequently defined methods become module
# functions.
# String arguments are converted to symbols.
# 
#    module Mod
#      def one
#        "This is one"
#      end
#      module_function :one
#    end
#    class Cls
#      include Mod
#      def call_one
#        one
#      end
#    end
#    Mod.one     #=> "This is one"
#    c = Cls.new
#    c.call_one  #=> "This is one"
#    module Mod
#      def one
#        "This is the new one"
#      end
#    end
#    Mod.one     #=> "This is one"
#    c.call_one  #=> "This is the new one"
def module_function(); self; end
##
# Returns +true+ if the named method is defined by
# _mod_ (or its included modules and, if _mod_ is a class,
# its ancestors). Public and protected methods are matched.
# String arguments are converted to symbols.
# 
#    module A
#      def method1()  end
#    end
#    class B
#      def method2()  end
#    end
#    class C < B
#      include A
#      def method3()  end
#    end
# 
#    A.method_defined? :method1    #=> true
#    C.method_defined? "method1"   #=> true
#    C.method_defined? "method2"   #=> true
#    C.method_defined? "method3"   #=> true
#    C.method_defined? "method4"   #=> false
def method_defined?(symbol); true || false; end
##
# Returns +true+ if the named public method is defined by
# _mod_ (or its included modules and, if _mod_ is a class,
# its ancestors).
# String arguments are converted to symbols.
# 
#    module A
#      def method1()  end
#    end
#    class B
#      protected
#      def method2()  end
#    end
#    class C < B
#      include A
#      def method3()  end
#    end
# 
#    A.method_defined? :method1           #=> true
#    C.public_method_defined? "method1"   #=> true
#    C.public_method_defined? "method2"   #=> false
#    C.method_defined? "method2"          #=> true
def public_method_defined?(symbol); true || false; end
##
# Returns +true+ if the named private method is defined by
# _ mod_ (or its included modules and, if _mod_ is a class,
# its ancestors).
# String arguments are converted to symbols.
# 
#    module A
#      def method1()  end
#    end
#    class B
#      private
#      def method2()  end
#    end
#    class C < B
#      include A
#      def method3()  end
#    end
# 
#    A.method_defined? :method1            #=> true
#    C.private_method_defined? "method1"   #=> false
#    C.private_method_defined? "method2"   #=> true
#    C.method_defined? "method2"           #=> false
def private_method_defined?(symbol); true || false; end
##
# Returns +true+ if the named protected method is defined
# by _mod_ (or its included modules and, if _mod_ is a
# class, its ancestors).
# String arguments are converted to symbols.
# 
#    module A
#      def method1()  end
#    end
#    class B
#      protected
#      def method2()  end
#    end
#    class C < B
#      include A
#      def method3()  end
#    end
# 
#    A.method_defined? :method1              #=> true
#    C.protected_method_defined? "method1"   #=> false
#    C.protected_method_defined? "method2"   #=> true
#    C.method_defined? "method2"             #=> true
def protected_method_defined?(symbol); true || false; end
##
# Makes a list of existing class methods public.
# 
# String arguments are converted to symbols.
def public_class_method(); Module.new; end
##
# Makes existing class methods private. Often used to hide the default
# constructor <code>new</code>.
# 
# String arguments are converted to symbols.
# 
#    class SimpleSingleton  # Not thread safe
#      private_class_method :new
#      def SimpleSingleton.create(*args, &block)
#        @me = new(*args, &block) if ! @me
#        @me
#      end
#    end
def private_class_method(); Module.new; end
##
# Registers _filename_ to be loaded (using <code>Kernel::require</code>)
# the first time that _module_ (which may be a <code>String</code> or
# a symbol) is accessed in the namespace of _mod_.
# 
#    module A
#    end
#    A.autoload(:B, "b")
#    A::B.doit            # autoloads "b"
def autoload(modul, filename); end
##
# Returns _filename_ to be loaded if _name_ is registered as
# +autoload+ in the namespace of _mod_.
# 
#    module A
#    end
#    A.autoload(:B, "b")
#    A.autoload?(:B)            #=> "b"
def autoload?(name); '' || nil; end
##
# Callback invoked whenever the receiver is included in another
# module or class. This should be used in preference to
# <tt>Module.append_features</tt> if your code wants to perform some
# action when a module is included in another.
# 
#        module A
#          def A.included(mod)
#            puts "#{self} included in #{mod}"
#          end
#        end
#        module Enumerable
#          include A
#        end
#         # => prints "A included in Enumerable"
def included( othermod ); end
##
# The equivalent of <tt>included</tt>, but for prepended modules.
# 
#        module A
#          def self.prepended(mod)
#            puts "#{self} prepended to #{mod}"
#          end
#        end
#        module Enumerable
#          prepend A
#        end
#         # => prints "A prepended to Enumerable"
def prepended( othermod ); end
##
# Invoked as a callback whenever an instance method is added to the
# receiver.
# 
#   module Chatty
#     def self.method_added(method_name)
#       puts "Adding #{method_name.inspect}"
#     end
#     def self.some_class_method() end
#     def some_instance_method() end
#   end
# 
# produces:
# 
#   Adding :some_instance_method
def method_added(method_name); end
##
# Invoked as a callback whenever an instance method is removed from the
# receiver.
# 
#   module Chatty
#     def self.method_removed(method_name)
#       puts "Removing #{method_name.inspect}"
#     end
#     def self.some_class_method() end
#     def some_instance_method() end
#     class << self
#       remove_method :some_class_method
#     end
#     remove_method :some_instance_method
#   end
# 
# produces:
# 
#   Removing :some_instance_method
def method_removed(method_name); end
##
# Prevents further modifications to <i>mod</i>.
# 
# This method returns self.
def freeze; Module.new; end
##
# Case Equality---Returns <code>true</code> if <i>anObject</i> is an
# instance of <i>mod</i> or one of <i>mod</i>'s descendants. Of
# limited use for modules, but can be used in <code>case</code>
# statements to classify objects by class.
def ===; true || false; end
##
# Equality --- At the <code>Object</code> level, <code>==</code> returns
# <code>true</code> only if +obj+ and +other+ are the same object.
# Typically, this method is overridden in descendant classes to provide
# class-specific meaning.
# 
# Unlike <code>==</code>, the <code>equal?</code> method should never be
# overridden by subclasses as it is used to determine object identity
# (that is, <code>a.equal?(b)</code> if and only if <code>a</code> is the
# same object as <code>b</code>):
# 
#   obj = "a"
#   other = obj.dup
# 
#   a == other      #=> true
#   a.equal? other  #=> false
#   a.equal? a      #=> true
# 
# The <code>eql?</code> method returns <code>true</code> if +obj+ and
# +other+ refer to the same hash key.  This is used by Hash to test members
# for equality.  For objects of class <code>Object</code>, <code>eql?</code>
# is synonymous with <code>==</code>.  Subclasses normally continue this
# tradition by aliasing <code>eql?</code> to their overridden <code>==</code>
# method, but there are exceptions.  <code>Numeric</code> types, for
# example, perform type conversion across <code>==</code>, but not across
# <code>eql?</code>, so:
# 
#    1 == 1.0     #=> true
#    1.eql? 1.0   #=> false
def ==; true || false; end
##
# Equality --- At the <code>Object</code> level, <code>==</code> returns
# <code>true</code> only if +obj+ and +other+ are the same object.
# Typically, this method is overridden in descendant classes to provide
# class-specific meaning.
# 
# Unlike <code>==</code>, the <code>equal?</code> method should never be
# overridden by subclasses as it is used to determine object identity
# (that is, <code>a.equal?(b)</code> if and only if <code>a</code> is the
# same object as <code>b</code>):
# 
#   obj = "a"
#   other = obj.dup
# 
#   a == other      #=> true
#   a.equal? other  #=> false
#   a.equal? a      #=> true
# 
# The <code>eql?</code> method returns <code>true</code> if +obj+ and
# +other+ refer to the same hash key.  This is used by Hash to test members
# for equality.  For objects of class <code>Object</code>, <code>eql?</code>
# is synonymous with <code>==</code>.  Subclasses normally continue this
# tradition by aliasing <code>eql?</code> to their overridden <code>==</code>
# method, but there are exceptions.  <code>Numeric</code> types, for
# example, perform type conversion across <code>==</code>, but not across
# <code>eql?</code>, so:
# 
#    1 == 1.0     #=> true
#    1.eql? 1.0   #=> false
def equal?(other); true || false; end
##
# Equality --- At the <code>Object</code> level, <code>==</code> returns
# <code>true</code> only if +obj+ and +other+ are the same object.
# Typically, this method is overridden in descendant classes to provide
# class-specific meaning.
# 
# Unlike <code>==</code>, the <code>equal?</code> method should never be
# overridden by subclasses as it is used to determine object identity
# (that is, <code>a.equal?(b)</code> if and only if <code>a</code> is the
# same object as <code>b</code>):
# 
#   obj = "a"
#   other = obj.dup
# 
#   a == other      #=> true
#   a.equal? other  #=> false
#   a.equal? a      #=> true
# 
# The <code>eql?</code> method returns <code>true</code> if +obj+ and
# +other+ refer to the same hash key.  This is used by Hash to test members
# for equality.  For objects of class <code>Object</code>, <code>eql?</code>
# is synonymous with <code>==</code>.  Subclasses normally continue this
# tradition by aliasing <code>eql?</code> to their overridden <code>==</code>
# method, but there are exceptions.  <code>Numeric</code> types, for
# example, perform type conversion across <code>==</code>, but not across
# <code>eql?</code>, so:
# 
#    1 == 1.0     #=> true
#    1.eql? 1.0   #=> false
def eql?(other); true || false; end
##
# Comparison---Returns -1, 0, +1 or nil depending on whether +module+
# includes +other_module+, they are the same, or if +module+ is included by
# +other_module+. This is the basis for the tests in Comparable.
# 
# Returns +nil+ if +module+ has no relationship with +other_module+, if
# +other_module+ is not a module, or if the two values are incomparable.
def <=>; 1 || nil; end
##
# Returns true if <i>mod</i> is a subclass of <i>other</i>. Returns
# <code>nil</code> if there's no relationship between the two.
# (Think of the relationship in terms of the class definition:
# "class A<B" implies "A<B").
def <; true || false || nil; end
##
# Returns true if <i>mod</i> is a subclass of <i>other</i> or
# is the same as <i>other</i>. Returns
# <code>nil</code> if there's no relationship between the two.
# (Think of the relationship in terms of the class definition:
# "class A<B" implies "A<B").
def <=; true || false || nil; end
##
# Returns true if <i>mod</i> is an ancestor of <i>other</i>. Returns
# <code>nil</code> if there's no relationship between the two.
# (Think of the relationship in terms of the class definition:
# "class A<B" implies "B>A").
def >; true || false || nil; end
##
# Returns true if <i>mod</i> is an ancestor of <i>other</i>, or the
# two modules are the same. Returns
# <code>nil</code> if there's no relationship between the two.
# (Think of the relationship in terms of the class definition:
# "class A<B" implies "B>A").
def >=; true || false || nil; end
##
# Return a string representing this module or class. For basic
# classes and modules, this is the name. For singletons, we
# show information on the thing we're attached to as well.
def to_s; ''; end
##
# Returns the list of modules included in <i>mod</i>.
# 
#    module Mixin
#    end
# 
#    module Outer
#      include Mixin
#    end
# 
#    Mixin.included_modules   #=> []
#    Outer.included_modules   #=> [Mixin]
def included_modules; []; end
##
# Returns <code>true</code> if <i>module</i> is included in
# <i>mod</i> or one of <i>mod</i>'s ancestors.
# 
#    module A
#    end
#    class B
#      include A
#    end
#    class C < B
#    end
#    B.include?(A)   #=> true
#    C.include?(A)   #=> true
#    A.include?(A)   #=> false
def include?(modul); true || false; end
##
# Returns the name of the module <i>mod</i>.  Returns nil for anonymous modules.
def name; ''; end
##
# Returns a list of modules included in <i>mod</i> (including
# <i>mod</i> itself).
# 
#    module Mod
#      include Math
#      include Comparable
#    end
# 
#    Mod.ancestors    #=> [Mod, Comparable, Math]
#    Math.ancestors   #=> [Math]
def ancestors; []; end
##
# Creates instance variables and corresponding methods that return the
# value of each instance variable. Equivalent to calling
# ``<code>attr</code><i>:name</i>'' on each name in turn.
# String arguments are converted to symbols.
def attr_reader(); end
##
# Creates an accessor method to allow assignment to the attribute
# <i>symbol</i><code>.id2name</code>.
# String arguments are converted to symbols.
def attr_writer(); end
##
# Defines a named attribute for this module, where the name is
# <i>symbol.</i><code>id2name</code>, creating an instance variable
# (<code>@name</code>) and a corresponding access method to read it.
# Also creates a method called <code>name=</code> to set the attribute.
# String arguments are converted to symbols.
# 
#    module Mod
#      attr_accessor(:one, :two)
#    end
#    Mod.instance_methods.sort   #=> [:one, :one=, :two, :two=]
def attr_accessor(); end
##
# Creates a new anonymous module. If a block is given, it is passed
# the module object, and the block is evaluated in the context of this
# module using <code>module_eval</code>.
# 
#    fred = Module.new do
#      def meth1
#        "hello"
#      end
#      def meth2
#        "bye"
#      end
#    end
#    a = "my string"
#    a.extend(fred)   #=> "my string"
#    a.meth1          #=> "hello"
#    a.meth2          #=> "bye"
# 
# Assign the module to a constant (name starting uppercase) if you
# want to treat it like a regular module.
def self.new; end
##
# Returns an array containing the names of the public and protected instance
# methods in the receiver. For a module, these are the public and protected methods;
# for a class, they are the instance (not singleton) methods. With no
# argument, or with an argument that is <code>false</code>, the
# instance methods in <i>mod</i> are returned, otherwise the methods
# in <i>mod</i> and <i>mod</i>'s superclasses are returned.
# 
#    module A
#      def method1()  end
#    end
#    class B
#      def method2()  end
#    end
#    class C < B
#      def method3()  end
#    end
# 
#    A.instance_methods                #=> [:method1]
#    B.instance_methods(false)         #=> [:method2]
#    C.instance_methods(false)         #=> [:method3]
#    C.instance_methods(true).length   #=> 43
def instance_methods(include_super=true); []; end
##
# Returns a list of the public instance methods defined in <i>mod</i>.
# If the optional parameter is not <code>false</code>, the methods of
# any ancestors are included.
def public_instance_methods(include_super=true); []; end
##
# Returns a list of the protected instance methods defined in
# <i>mod</i>. If the optional parameter is not <code>false</code>, the
# methods of any ancestors are included.
def protected_instance_methods(include_super=true); []; end
##
# Returns a list of the private instance methods defined in
# <i>mod</i>. If the optional parameter is not <code>false</code>, the
# methods of any ancestors are included.
# 
#    module Mod
#      def method1()  end
#      private :method1
#      def method2()  end
#    end
#    Mod.instance_methods           #=> [:method2]
#    Mod.private_instance_methods   #=> [:method1]
def private_instance_methods(include_super=true); []; end
##
# Checks for a constant with the given name in <i>mod</i>
# If +inherit+ is set, the lookup will also search
# the ancestors (and +Object+ if <i>mod</i> is a +Module+.)
# 
# The value of the constant is returned if a definition is found,
# otherwise a +NameError+ is raised.
# 
#    Math.const_get(:PI)   #=> 3.14159265358979
# 
# This method will recursively look up constant names if a namespaced
# class name is provided.  For example:
# 
#    module Foo; class Bar; end end
#    Object.const_get 'Foo::Bar'
# 
# The +inherit+ flag is respected on each lookup.  For example:
# 
#    module Foo
#      class Bar
#        VAL = 10
#      end
# 
#      class Baz < Bar; end
#    end
# 
#    Object.const_get 'Foo::Baz::VAL'         # => 10
#    Object.const_get 'Foo::Baz::VAL', false  # => NameError
def const_get(sym, inherit=true); Object.new; end
##
# Sets the named constant to the given object, returning that object.
# Creates a new constant if no constant with the given name previously
# existed.
# 
#    Math.const_set("HIGH_SCHOOL_PI", 22.0/7.0)   #=> 3.14285714285714
#    Math::HIGH_SCHOOL_PI - Math::PI              #=> 0.00126448926734968
def const_set(sym, obj); Object.new; end
##
# Checks for a constant with the given name in <i>mod</i>
# If +inherit+ is set, the lookup will also search
# the ancestors (and +Object+ if <i>mod</i> is a +Module+.)
# 
# Returns whether or not a definition is found:
# 
#    Math.const_defined? "PI"   #=> true
#    IO.const_defined? :SYNC   #=> true
#    IO.const_defined? :SYNC, false   #=> false
def const_defined?(sym, inherit=true); true || false; end
##
# Removes the definition of the given constant, returning that
# constant's previous value.  If that constant referred to
# a module, this will not change that module's name and can lead
# to confusion.
def remove_const(sym); Object.new; end
##
# Invoked when a reference is made to an undefined constant in
# <i>mod</i>. It is passed a symbol for the undefined constant, and
# returns a value to be used for that constant. The
# following code is an example of the same:
# 
#   def Foo.const_missing(name)
#     name # return the constant name as Symbol
#   end
# 
#   Foo::UNDEFINED_CONST    #=> :UNDEFINED_CONST: symbol returned
# 
# In the next example when a reference is made to an undefined constant,
# it attempts to load a file whose name is the lowercase version of the
# constant (thus class <code>Fred</code> is assumed to be in file
# <code>fred.rb</code>).  If found, it returns the loaded class. It
# therefore implements an autoload feature similar to Kernel#autoload and
# Module#autoload.
# 
#   def Object.const_missing(name)
#     @looked_for ||= {}
#     str_name = name.to_s
#     raise "Class not found: #{name}" if @looked_for[str_name]
#     @looked_for[str_name] = 1
#     file = str_name.downcase
#     require file
#     klass = const_get(name)
#     return klass if klass
#     raise "Class not found: #{name}"
#   end
def const_missing(sym); Object.new; end
##
# Returns an array of the names of class variables in <i>mod</i>.
# This includes the names of class variables in any included
# modules, unless the <i>inherit</i> parameter is set to
# <code>false</code>.
# 
#    class One
#      @@var1 = 1
#    end
#    class Two < One
#      @@var2 = 2
#    end
#    One.class_variables   #=> [:@@var1]
#    Two.class_variables   #=> [:@@var2, :@@var1]
def class_variables(inherit=true); []; end
##
# Removes the definition of the <i>sym</i>, returning that
# constant's value.
# 
#    class Dummy
#      @@var = 99
#      puts @@var
#      remove_class_variable(:@@var)
#      p(defined? @@var)
#    end
# 
# <em>produces:</em>
# 
#    99
#    nil
def remove_class_variable(sym); Object.new; end
##
# Returns the value of the given class variable (or throws a
# <code>NameError</code> exception). The <code>@@</code> part of the
# variable name should be included for regular class variables
# String arguments are converted to symbols.
# 
#    class Fred
#      @@foo = 99
#    end
#    Fred.class_variable_get(:@@foo)     #=> 99
def class_variable_get(symbol); Object.new; end
##
# Sets the class variable names by <i>symbol</i> to
# <i>object</i>.
# If the class variable name is passed as a string, that string
# is converted to a symbol.
# 
#    class Fred
#      @@foo = 99
#      def foo
#        @@foo
#      end
#    end
#    Fred.class_variable_set(:@@foo, 101)     #=> 101
#    Fred.new.foo                             #=> 101
def class_variable_set(symbol, obj); Object.new; end
##
# Returns <code>true</code> if the given class variable is defined
# in <i>obj</i>.
# String arguments are converted to symbols.
# 
#    class Fred
#      @@foo = 99
#    end
#    Fred.class_variable_defined?(:@@foo)    #=> true
#    Fred.class_variable_defined?(:@@bar)    #=> false
def class_variable_defined?(symbol); true || false; end
##
# Makes a list of existing constants public.
def public_constant(); Module.new; end
##
# Makes a list of existing constants private.
def private_constant(); Module.new; end
end

##
# A rational number can be represented as a paired integer number;
# a/b (b>0).  Where a is numerator and b is denominator.  Integer a
# equals rational a/1 mathematically.
# 
# In ruby, you can create rational object with Rational, to_r or
# rationalize method.  The return values will be irreducible.
# 
#    Rational(1)      #=> (1/1)
#    Rational(2, 3)   #=> (2/3)
#    Rational(4, -6)  #=> (-2/3)
#    3.to_r           #=> (3/1)
# 
# You can also create rational object from floating-point numbers or
# strings.
# 
#    Rational(0.3)    #=> (5404319552844595/18014398509481984)
#    Rational('0.3')  #=> (3/10)
#    Rational('2/3')  #=> (2/3)
# 
#    0.3.to_r         #=> (5404319552844595/18014398509481984)
#    '0.3'.to_r       #=> (3/10)
#    '2/3'.to_r       #=> (2/3)
#    0.3.rationalize  #=> (3/10)
# 
# A rational object is an exact number, which helps you to write
# program without any rounding errors.
# 
#    10.times.inject(0){|t,| t + 0.1}              #=> 0.9999999999999999
#    10.times.inject(0){|t,| t + Rational('0.1')}  #=> (1/1)
# 
# However, when an expression has inexact factor (numerical value or
# operation), will produce an inexact result.
# 
#    Rational(10) / 3   #=> (10/3)
#    Rational(10) / 3.0 #=> 3.3333333333333335
# 
#    Rational(-8) ** Rational(1, 3)
#                       #=> (1.0000000000000002+1.7320508075688772i)
class Rational < Numeric
class Compatible < Object
end

##
# Returns the numerator.
# 
#    Rational(7).numerator        #=> 7
#    Rational(7, 1).numerator     #=> 7
#    Rational(9, -4).numerator    #=> -9
#    Rational(-2, -10).numerator  #=> 1
def numerator; 0; end
##
# Returns the denominator (always positive).
# 
#    Rational(7).denominator             #=> 1
#    Rational(7, 1).denominator          #=> 1
#    Rational(9, -4).denominator         #=> 4
#    Rational(-2, -10).denominator       #=> 5
#    rat.numerator.gcd(rat.denominator)  #=> 1
def denominator; 0; end
##
# Performs addition.
# 
#    Rational(2, 3)  + Rational(2, 3)   #=> (4/3)
#    Rational(900)   + Rational(1)      #=> (900/1)
#    Rational(-2, 9) + Rational(-9, 2)  #=> (-85/18)
#    Rational(9, 8)  + 4                #=> (41/8)
#    Rational(20, 9) + 9.8              #=> 12.022222222222222
def +; 0; end
##
# Performs subtraction.
# 
#    Rational(2, 3)  - Rational(2, 3)   #=> (0/1)
#    Rational(900)   - Rational(1)      #=> (899/1)
#    Rational(-2, 9) - Rational(-9, 2)  #=> (77/18)
#    Rational(9, 8)  - 4                #=> (23/8)
#    Rational(20, 9) - 9.8              #=> -7.577777777777778
def -; 0; end
##
# Performs multiplication.
# 
#    Rational(2, 3)  * Rational(2, 3)   #=> (4/9)
#    Rational(900)   * Rational(1)      #=> (900/1)
#    Rational(-2, 9) * Rational(-9, 2)  #=> (1/1)
#    Rational(9, 8)  * 4                #=> (9/2)
#    Rational(20, 9) * 9.8              #=> 21.77777777777778
def *; 0; end
##
# Performs division.
# 
#    Rational(2, 3)  / Rational(2, 3)   #=> (1/1)
#    Rational(900)   / Rational(1)      #=> (900/1)
#    Rational(-2, 9) / Rational(-9, 2)  #=> (4/81)
#    Rational(9, 8)  / 4                #=> (9/32)
#    Rational(20, 9) / 9.8              #=> 0.22675736961451246
def /; 0; end
##
# Performs division.
# 
#    Rational(2, 3)  / Rational(2, 3)   #=> (1/1)
#    Rational(900)   / Rational(1)      #=> (900/1)
#    Rational(-2, 9) / Rational(-9, 2)  #=> (4/81)
#    Rational(9, 8)  / 4                #=> (9/32)
#    Rational(20, 9) / 9.8              #=> 0.22675736961451246
def quo(numeric); 0; end
##
# Performs division and returns the value as a float.
# 
#    Rational(2, 3).fdiv(1)       #=> 0.6666666666666666
#    Rational(2, 3).fdiv(0.5)     #=> 1.3333333333333333
#    Rational(2).fdiv(3)          #=> 0.6666666666666666
def fdiv(numeric); 0.0; end
##
# Performs exponentiation.
# 
#    Rational(2)    ** Rational(3)    #=> (8/1)
#    Rational(10)   ** -2             #=> (1/100)
#    Rational(10)   ** -2.0           #=> 0.01
#    Rational(-4)   ** Rational(1,2)  #=> (1.2246063538223773e-16+2.0i)
#    Rational(1, 2) ** 0              #=> (1/1)
#    Rational(1, 2) ** 0.0            #=> 1.0
def **; 0; end
##
# Performs comparison and returns -1, 0, or +1.
# 
# +nil+ is returned if the two values are incomparable.
# 
#    Rational(2, 3)  <=> Rational(2, 3)  #=> 0
#    Rational(5)     <=> 5               #=> 0
#    Rational(2,3)   <=> Rational(1,3)   #=> 1
#    Rational(1,3)   <=> 1               #=> -1
#    Rational(1,3)   <=> 0.3             #=> 1
def <=>; 1 || nil; end
##
# Returns true if rat equals object numerically.
# 
#    Rational(2, 3)  == Rational(2, 3)   #=> true
#    Rational(5)     == 5                #=> true
#    Rational(0)     == 0.0              #=> true
#    Rational('1/3') == 0.33             #=> false
#    Rational('1/2') == '1/2'            #=> false
def ==; true || false; end
##
# Returns the truncated value (toward negative infinity).
# 
#    Rational(3).floor      #=> 3
#    Rational(2, 3).floor   #=> 0
#    Rational(-3, 2).floor  #=> -1
# 
#           decimal      -  1  2  3 . 4  5  6
#                          ^  ^  ^  ^   ^  ^
#          precision      -3 -2 -1  0  +1 +2
# 
#    '%f' % Rational('-123.456').floor(+1)  #=> "-123.500000"
#    '%f' % Rational('-123.456').floor(-1)  #=> "-130.000000"
def floor; Rational.new; end
##
# Returns the truncated value (toward positive infinity).
# 
#    Rational(3).ceil      #=> 3
#    Rational(2, 3).ceil   #=> 1
#    Rational(-3, 2).ceil  #=> -1
# 
#           decimal      -  1  2  3 . 4  5  6
#                          ^  ^  ^  ^   ^  ^
#          precision      -3 -2 -1  0  +1 +2
# 
#    '%f' % Rational('-123.456').ceil(+1)  #=> "-123.400000"
#    '%f' % Rational('-123.456').ceil(-1)  #=> "-120.000000"
def ceil; Rational.new; end
##
# Returns the truncated value (toward zero).
# 
#    Rational(3).truncate      #=> 3
#    Rational(2, 3).truncate   #=> 0
#    Rational(-3, 2).truncate  #=> -1
# 
#           decimal      -  1  2  3 . 4  5  6
#                          ^  ^  ^  ^   ^  ^
#          precision      -3 -2 -1  0  +1 +2
# 
#    '%f' % Rational('-123.456').truncate(+1)  #=>  "-123.400000"
#    '%f' % Rational('-123.456').truncate(-1)  #=>  "-120.000000"
def truncate; Rational.new; end
##
# Returns the truncated value (toward the nearest integer;
# 0.5 => 1; -0.5 => -1).
# 
#    Rational(3).round      #=> 3
#    Rational(2, 3).round   #=> 1
#    Rational(-3, 2).round  #=> -2
# 
#           decimal      -  1  2  3 . 4  5  6
#                          ^  ^  ^  ^   ^  ^
#          precision      -3 -2 -1  0  +1 +2
# 
#    '%f' % Rational('-123.456').round(+1)  #=> "-123.500000"
#    '%f' % Rational('-123.456').round(-1)  #=> "-120.000000"
def round; Rational.new; end
##
# Returns the truncated value as an integer.
# 
# Equivalent to
#    rat.truncate.
# 
#    Rational(2, 3).to_i   #=> 0
#    Rational(3).to_i      #=> 3
#    Rational(300.6).to_i  #=> 300
#    Rational(98,71).to_i  #=> 1
#    Rational(-30,2).to_i  #=> -15
def to_i; 0; end
##
# Return the value as a float.
# 
#    Rational(2).to_f      #=> 2.0
#    Rational(9, 4).to_f   #=> 2.25
#    Rational(-3, 4).to_f  #=> -0.75
#    Rational(20, 3).to_f  #=> 6.666666666666667
def to_f; 0.0; end
##
# Returns self.
# 
#    Rational(2).to_r      #=> (2/1)
#    Rational(-8, 6).to_r  #=> (-4/3)
def to_r; self; end
##
# Returns a simpler approximation of the value if the optional
# argument eps is given (rat-|eps| <= result <= rat+|eps|), self
# otherwise.
# 
#    r = Rational(5033165, 16777216)
#    r.rationalize                    #=> (5033165/16777216)
#    r.rationalize(Rational('0.01'))  #=> (3/10)
#    r.rationalize(Rational('0.1'))   #=> (1/3)
def rationalize; Rational.new; end
##
# Returns the value as a string.
# 
#    Rational(2).to_s      #=> "2/1"
#    Rational(-8, 6).to_s  #=> "-4/3"
#    Rational('1/2').to_s  #=> "1/2"
def to_s; ''; end
##
# Returns the value as a string for inspection.
# 
#    Rational(2).inspect      #=> "(2/1)"
#    Rational(-8, 6).inspect  #=> "(-4/3)"
#    Rational('1/2').inspect  #=> "(1/2)"
def inspect; ''; end
end

class Integer < Object
##
# Returns the greatest common divisor (always positive).  0.gcd(x)
# and x.gcd(0) return abs(x).
# 
#    2.gcd(2)                    #=> 2
#    3.gcd(-7)                   #=> 1
#    ((1<<31)-1).gcd((1<<61)-1)  #=> 1
def gcd(int2); 0; end
##
# Returns the least common multiple (always positive).  0.lcm(x) and
# x.lcm(0) return zero.
# 
#    2.lcm(2)                    #=> 2
#    3.lcm(-7)                   #=> 21
#    ((1<<31)-1).lcm((1<<61)-1)  #=> 4951760154835678088235319297
def lcm(int2); 0; end
##
# Returns an array; [int.gcd(int2), int.lcm(int2)].
# 
#    2.gcdlcm(2)                    #=> [2, 2]
#    3.gcdlcm(-7)                   #=> [1, 21]
#    ((1<<31)-1).gcdlcm((1<<61)-1)  #=> [1, 4951760154835678088235319297]
def gcdlcm(int2); []; end
##
# Returns self.
def numerator; self; end
##
# Returns 1.
def denominator; 1; end
##
# Returns the value as a rational.
# 
#    1.to_r        #=> (1/1)
#    (1<<64).to_r  #=> (18446744073709551616/1)
def to_r; Rational.new; end
##
# Returns the value as a rational.  The optional argument eps is
# always ignored.
def rationalize(eps=0); Rational.new; end
##
# Always returns <code>true</code>.
def integer?; true; end
##
# Returns <code>true</code> if <i>int</i> is an odd number.
def odd?; true || false; end
##
# Returns <code>true</code> if <i>int</i> is an even number.
def even?; true || false; end
##
# Iterates <em>block</em>, passing in integer values from <i>int</i>
# up to and including <i>limit</i>.
# 
# If no block is given, an enumerator is returned instead.
# 
#    5.upto(10) { |i| print i, " " }
# 
# <em>produces:</em>
# 
#    5 6 7 8 9 10
def upto(limit, &block); Enumerator.new; end
##
# Iterates <em>block</em>, passing decreasing values from <i>int</i>
# down to and including <i>limit</i>.
# 
# If no block is given, an enumerator is returned instead.
# 
#    5.downto(1) { |n| print n, ".. " }
#    print "  Liftoff!\n"
# 
# <em>produces:</em>
# 
#    5.. 4.. 3.. 2.. 1..   Liftoff!
def downto(limit, &block); Enumerator.new; end
##
# Iterates block <i>int</i> times, passing in values from zero to
# <i>int</i> - 1.
# 
# If no block is given, an enumerator is returned instead.
# 
#    5.times do |i|
#      print i, " "
#    end
# 
# <em>produces:</em>
# 
#    0 1 2 3 4
def times(&block); Enumerator.new; end
##
# Returns the <code>Integer</code> equal to <i>int</i> + 1.
# 
#    1.next      #=> 2
#    (-1).next   #=> 0
def next; 0; end
##
# Returns the <code>Integer</code> equal to <i>int</i> + 1.
# 
#    1.next      #=> 2
#    (-1).next   #=> 0
def succ; 0; end
##
# Returns the <code>Integer</code> equal to <i>int</i> - 1.
# 
#    1.pred      #=> 0
#    (-1).pred   #=> -2
def pred; 0; end
##
# Returns a string containing the character represented by the
# receiver's value according to +encoding+.
# 
#    65.chr    #=> "A"
#    230.chr   #=> "\346"
#    255.chr(Encoding::UTF_8)   #=> "\303\277"
def chr(encoding=0); ''; end
##
# Returns the int itself.
# 
#    ?a.ord    #=> 97
# 
# This method is intended for compatibility to
# character constant in Ruby 1.9.
# For example, ?a.ord returns 97 both in 1.8 and 1.9.
def ord; self; end
##
# As <i>int</i> is already an <code>Integer</code>, all these
# methods simply return the receiver.
def to_i; 0; end
##
# As <i>int</i> is already an <code>Integer</code>, all these
# methods simply return the receiver.
def to_int; 0; end
##
# As <i>int</i> is already an <code>Integer</code>, all these
# methods simply return the receiver.
def floor; 0; end
##
# As <i>int</i> is already an <code>Integer</code>, all these
# methods simply return the receiver.
def ceil; 0; end
##
# As <i>int</i> is already an <code>Integer</code>, all these
# methods simply return the receiver.
def truncate; 0; end
##
# Rounds <i>flt</i> to a given precision in decimal digits (default 0 digits).
# Precision may be negative.  Returns a floating point number when +ndigits+
# is positive, +self+ for zero, and round down for negative.
# 
#    1.round        #=> 1
#    1.round(2)     #=> 1.0
#    15.round(-1)   #=> 20
def round(ndigits=0); 0 || 0.0; end
end

class Numeric < Object
include Comparable
##
# Returns the numerator.
def numerator; 0; end
##
# Returns the denominator (always positive).
def denominator; 0; end
##
# If <i>aNumeric</i> is the same type as <i>num</i>, returns an array
# containing <i>aNumeric</i> and <i>num</i>. Otherwise, returns an
# array with both <i>aNumeric</i> and <i>num</i> represented as
# <code>Float</code> objects. This coercion mechanism is used by
# Ruby to handle mixed-type numeric operations: it is intended to
# find a compatible common type between the two operands of the operator.
# 
#    1.coerce(2.5)   #=> [2.5, 1.0]
#    1.2.coerce(3)   #=> [3.0, 1.2]
#    1.coerce(2)     #=> [2, 1]
def coerce(numeric); []; end
##
# Returns the corresponding imaginary number.
# Not available for complex numbers.
def i; Complex.new; end
##
# Unary Plus---Returns the receiver's value.
def +@; 0; end
##
# Unary Minus---Returns the receiver's value, negated.
def -@; 0; end
##
# Returns zero if +number+ equals +other+, otherwise +nil+ is returned if the
# two values are incomparable.
def <=>; 0 || nil; end
##
# Returns <code>true</code> if <i>num</i> and <i>numeric</i> are the
# same type and have equal values.
# 
#    1 == 1.0          #=> true
#    1.eql?(1.0)       #=> false
#    (1.0).eql?(1.0)   #=> true
def eql?(numeric); true || false; end
##
# Returns most exact division (rational for integers, float for floats).
def quo(numeric); 0; end
##
# Returns float division.
def fdiv(numeric); 0.0; end
##
# Uses <code>/</code> to perform division, then converts the result to
# an integer. <code>numeric</code> does not define the <code>/</code>
# operator; this is left to subclasses.
# 
# Equivalent to
# <i>num</i>.<code>divmod(</code><i>aNumeric</i><code>)[0]</code>.
# 
# See <code>Numeric#divmod</code>.
def div(numeric); 0; end
##
# Returns an array containing the quotient and modulus obtained by
# dividing <i>num</i> by <i>numeric</i>. If <code>q, r =
# x.divmod(y)</code>, then
# 
#     q = floor(x/y)
#     x = q*y+r
# 
# The quotient is rounded toward -infinity, as shown in the following table:
# 
#    a    |  b  |  a.divmod(b)  |   a/b   | a.modulo(b) | a.remainder(b)
#   ------+-----+---------------+---------+-------------+---------------
#    13   |  4  |   3,    1     |   3     |    1        |     1
#   ------+-----+---------------+---------+-------------+---------------
#    13   | -4  |  -4,   -3     |  -4     |   -3        |     1
#   ------+-----+---------------+---------+-------------+---------------
#   -13   |  4  |  -4,    3     |  -4     |    3        |    -1
#   ------+-----+---------------+---------+-------------+---------------
#   -13   | -4  |   3,   -1     |   3     |   -1        |    -1
#   ------+-----+---------------+---------+-------------+---------------
#    11.5 |  4  |   2,    3.5   |   2.875 |    3.5      |     3.5
#   ------+-----+---------------+---------+-------------+---------------
#    11.5 | -4  |  -3,   -0.5   |  -2.875 |   -0.5      |     3.5
#   ------+-----+---------------+---------+-------------+---------------
#   -11.5 |  4  |  -3,    0.5   |  -2.875 |    0.5      |    -3.5
#   ------+-----+---------------+---------+-------------+---------------
#   -11.5 | -4  |   2,   -3.5   |   2.875 |   -3.5      |    -3.5
# 
# Examples
# 
#    11.divmod(3)         #=> [3, 2]
#    11.divmod(-3)        #=> [-4, -1]
#    11.divmod(3.5)       #=> [3, 0.5]
#    (-11).divmod(3.5)    #=> [-4, 3.0]
#    (11.5).divmod(3.5)   #=> [3, 1.0]
def divmod(numeric); []; end
##
#    x.modulo(y) means x-y*(x/y).floor
# 
# Equivalent to
# <i>num</i>.<code>divmod(</code><i>aNumeric</i><code>)[1]</code>.
# 
# See <code>Numeric#divmod</code>.
def modulo(numeric); 0; end
##
#    x.remainder(y) means x-y*(x/y).truncate
# 
# See <code>Numeric#divmod</code>.
def remainder(numeric); 0; end
##
# Returns the absolute value of <i>num</i>.
# 
#    12.abs         #=> 12
#    (-34.56).abs   #=> 34.56
#    -34.56.abs     #=> 34.56
def abs; 0; end
##
# Returns the absolute value of <i>num</i>.
# 
#    12.abs         #=> 12
#    (-34.56).abs   #=> 34.56
#    -34.56.abs     #=> 34.56
def magnitude; 0; end
##
# Invokes the child class's +to_i+ method to convert +num+ to an integer.
# 
#     1.0.class => Float
#     1.0.to_int.class => Fixnum
#     1.0.to_i.class => Fixnum
def to_int; 0; end
##
# Returns <code>true</code> if <i>num</i> is a <code>Real</code>
# (i.e. non <code>Complex</code>).
def real?; true || false; end
##
# Returns +true+ if +num+ is an Integer (including Fixnum and Bignum).
# 
#     (1.0).integer? #=> false
#     (1).integer?   #=> true
def integer?; true || false; end
##
# Returns <code>true</code> if <i>num</i> has a zero value.
def zero?; true || false; end
##
# Returns +self+ if <i>num</i> is not zero, <code>nil</code>
# otherwise. This behavior is useful when chaining comparisons:
# 
#    a = %w( z Bb bB bb BB a aA Aa AA A )
#    b = a.sort {|a,b| (a.downcase <=> b.downcase).nonzero? || a <=> b }
#    b   #=> ["A", "a", "AA", "Aa", "aA", "BB", "Bb", "bB", "bb", "z"]
def nonzero?; self || nil; end
##
# Returns the largest integer less than or equal to <i>num</i>.
# <code>Numeric</code> implements this by converting <i>anInteger</i>
# to a <code>Float</code> and invoking <code>Float#floor</code>.
# 
#    1.floor      #=> 1
#    (-1).floor   #=> -1
def floor; 0; end
##
# Returns the smallest <code>Integer</code> greater than or equal to
# <i>num</i>. Class <code>Numeric</code> achieves this by converting
# itself to a <code>Float</code> then invoking
# <code>Float#ceil</code>.
# 
#    1.ceil        #=> 1
#    1.2.ceil      #=> 2
#    (-1.2).ceil   #=> -1
#    (-1.0).ceil   #=> -1
def ceil; 0; end
##
# Rounds <i>num</i> to a given precision in decimal digits (default 0 digits).
# Precision may be negative.  Returns a floating point number when <i>ndigits</i>
# is more than zero.  <code>Numeric</code> implements this by converting itself
# to a <code>Float</code> and invoking <code>Float#round</code>.
def round(ndigits=0); 0 || 0.0; end
##
# Returns <i>num</i> truncated to an integer. <code>Numeric</code>
# implements this by converting its value to a float and invoking
# <code>Float#truncate</code>.
def truncate; 0; end
##
# Invokes <em>block</em> with the sequence of numbers starting at
# <i>num</i>, incremented by <i>step</i> (default 1) on each
# call. The loop finishes when the value to be passed to the block
# is greater than <i>limit</i> (if <i>step</i> is positive) or less
# than <i>limit</i> (if <i>step</i> is negative). If all the
# arguments are integers, the loop operates using an integer
# counter. If any of the arguments are floating point numbers, all
# are converted to floats, and the loop is executed <i>floor(n +
# n*epsilon)+ 1</i> times, where <i>n = (limit -
# num)/step</i>. Otherwise, the loop starts at <i>num</i>, uses
# either the <code><</code> or <code>></code> operator to compare
# the counter against <i>limit</i>, and increments itself using the
# <code>+</code> operator.
# 
# If no block is given, an enumerator is returned instead.
# 
#    1.step(10, 2) { |i| print i, " " }
#    Math::E.step(Math::PI, 0.2) { |f| print f, " " }
# 
# <em>produces:</em>
# 
#    1 3 5 7 9
#    2.71828182845905 2.91828182845905 3.11828182845905
def step(limit, step=0, &block); Enumerator.new; end
##
# Returns the value as a complex.
def to_c; Complex.new; end
##
# Returns self.
def real; self; end
##
# Returns zero.
def imag; 0; end
##
# Returns zero.
def imaginary; 0; end
##
# Returns square of self.
def abs2; 0; end
##
# Returns 0 if the value is positive, pi otherwise.
def arg; 0 || 0.0; end
##
# Returns 0 if the value is positive, pi otherwise.
def angle; 0 || 0.0; end
##
# Returns 0 if the value is positive, pi otherwise.
def phase; 0 || 0.0; end
##
# Returns an array; [num, 0].
def rect; []; end
##
# Returns an array; [num.abs, num.arg].
def polar; []; end
##
# Returns self.
def conj; self; end
##
# Returns self.
def conjugate; self; end
end

class Float < Object
##
# Returns the numerator.  The result is machine dependent.
# 
#    n = 0.3.numerator    #=> 5404319552844595
#    d = 0.3.denominator  #=> 18014398509481984
#    n.fdiv(d)            #=> 0.3
def numerator; 0; end
##
# Returns the denominator (always positive).  The result is machine
# dependent.
# 
# See numerator.
def denominator; 0; end
##
# Returns the value as a rational.
# 
# NOTE: 0.3.to_r isn't the same as '0.3'.to_r.  The latter is
# equivalent to '3/10'.to_r, but the former isn't so.
# 
#    2.0.to_r    #=> (2/1)
#    2.5.to_r    #=> (5/2)
#    -0.75.to_r  #=> (-3/4)
#    0.0.to_r    #=> (0/1)
# 
# See rationalize.
def to_r; Rational.new; end
##
# Returns a simpler approximation of the value (flt-|eps| <= result
# <= flt+|eps|).  if the optional eps is not given, it will be chosen
# automatically.
# 
#    0.3.rationalize          #=> (3/10)
#    1.333.rationalize        #=> (1333/1000)
#    1.333.rationalize(0.01)  #=> (4/3)
# 
# See to_r.
def rationalize(eps=0); Rational.new; end
##
# Returns a string containing a representation of self. As well as a
# fixed or exponential form of the number, the call may return
# ``<code>NaN</code>'', ``<code>Infinity</code>'', and
# ``<code>-Infinity</code>''.
def to_s; ''; end
##
# Returns an array with both <i>aNumeric</i> and <i>flt</i> represented
# as <code>Float</code> objects.
# This is achieved by converting <i>aNumeric</i> to a <code>Float</code>.
# 
#    1.2.coerce(3)       #=> [3.0, 1.2]
#    2.5.coerce(1.1)     #=> [1.1, 2.5]
def coerce(numeric); []; end
##
# Returns float, negated.
def -@; 0.0; end
##
# Returns a new float which is the sum of <code>float</code>
# and <code>other</code>.
def +; 0.0; end
##
# Returns a new float which is the difference of <code>float</code>
# and <code>other</code>.
def -; 0.0; end
##
# Returns a new float which is the product of <code>float</code>
# and <code>other</code>.
def *; 0.0; end
##
# Returns a new float which is the result of dividing
# <code>float</code> by <code>other</code>.
def /; 0.0; end
##
# Returns float / numeric.
def quo(numeric); 0.0; end
##
# Return the modulo after division of +float+ by +other+.
# 
#    6543.21.modulo(137)      #=> 104.21
#    6543.21.modulo(137.24)   #=> 92.9299999999996
def %; 0.0; end
##
# Return the modulo after division of +float+ by +other+.
# 
#    6543.21.modulo(137)      #=> 104.21
#    6543.21.modulo(137.24)   #=> 92.9299999999996
def modulo(other); 0.0; end
##
# See Numeric#divmod.
# 
#     42.0.divmod 6 #=> [7, 0.0]
#     42.0.divmod 5 #=> [8, 2.0]
def divmod(numeric); []; end
##
# Raises <code>float</code> the <code>other</code> power.
# 
#    2.0**3      #=> 8.0
def **; 0.0; end
##
# Returns <code>true</code> only if <i>obj</i> has the same value
# as <i>flt</i>. Contrast this with <code>Float#eql?</code>, which
# requires <i>obj</i> to be a <code>Float</code>.
# The result of <code>NaN == NaN</code> is undefined, so the
# implementation-dependent value is returned.
# 
#    1.0 == 1   #=> true
def ==; true || false; end
##
# Returns <code>true</code> only if <i>obj</i> has the same value
# as <i>flt</i>. Contrast this with <code>Float#eql?</code>, which
# requires <i>obj</i> to be a <code>Float</code>.
# The result of <code>NaN == NaN</code> is undefined, so the
# implementation-dependent value is returned.
# 
#    1.0 == 1   #=> true
def ===; true || false; end
##
# Returns -1, 0, +1 or nil depending on whether +float+ is less than, equal
# to, or greater than +real+. This is the basis for the tests in Comparable.
# 
# The result of <code>NaN <=> NaN</code> is undefined, so the
# implementation-dependent value is returned.
# 
# +nil+ is returned if the two values are incomparable.
def <=>; 1 || nil; end
##
# <code>true</code> if <code>flt</code> is greater than <code>real</code>.
# The result of <code>NaN > NaN</code> is undefined, so the
# implementation-dependent value is returned.
def >; true || false; end
##
# <code>true</code> if <code>flt</code> is greater than
# or equal to <code>real</code>.
# The result of <code>NaN >= NaN</code> is undefined, so the
# implementation-dependent value is returned.
def >=; true || false; end
##
# <code>true</code> if <code>flt</code> is less than <code>real</code>.
# The result of <code>NaN < NaN</code> is undefined, so the
# implementation-dependent value is returned.
def <; true || false; end
##
# <code>true</code> if <code>flt</code> is less than
# or equal to <code>real</code>.
# The result of <code>NaN <= NaN</code> is undefined, so the
# implementation-dependent value is returned.
def <=; true || false; end
##
# Returns <code>true</code> only if <i>obj</i> is a
# <code>Float</code> with the same value as <i>flt</i>. Contrast this
# with <code>Float#==</code>, which performs type conversions.
# The result of <code>NaN.eql?(NaN)</code> is undefined, so the
# implementation-dependent value is returned.
# 
#    1.0.eql?(1)   #=> false
def eql?(obj); true || false; end
##
# Returns a hash code for this float.
def hash; 0; end
##
# As <code>flt</code> is already a float, returns +self+.
def to_f; self; end
##
# Returns the absolute value of <i>flt</i>.
# 
#    (-34.56).abs   #=> 34.56
#    -34.56.abs     #=> 34.56
def abs; 0.0; end
##
# Returns the absolute value of <i>flt</i>.
# 
#    (-34.56).abs   #=> 34.56
#    -34.56.abs     #=> 34.56
def magnitude; 0.0; end
##
# Returns <code>true</code> if <i>flt</i> is 0.0.
def zero?; true || false; end
##
# Returns <i>flt</i> truncated to an <code>Integer</code>.
def to_i; 0; end
##
# Returns <i>flt</i> truncated to an <code>Integer</code>.
def to_int; 0; end
##
# Returns <i>flt</i> truncated to an <code>Integer</code>.
def truncate; 0; end
##
# Returns the largest integer less than or equal to <i>flt</i>.
# 
#    1.2.floor      #=> 1
#    2.0.floor      #=> 2
#    (-1.2).floor   #=> -2
#    (-2.0).floor   #=> -2
def floor; 0; end
##
# Returns the smallest <code>Integer</code> greater than or equal to
# <i>flt</i>.
# 
#    1.2.ceil      #=> 2
#    2.0.ceil      #=> 2
#    (-1.2).ceil   #=> -1
#    (-2.0).ceil   #=> -2
def ceil; 0; end
##
# Rounds <i>flt</i> to a given precision in decimal digits (default 0 digits).
# Precision may be negative.  Returns a floating point number when ndigits
# is more than zero.
# 
#    1.4.round      #=> 1
#    1.5.round      #=> 2
#    1.6.round      #=> 2
#    (-1.5).round   #=> -2
# 
#    1.234567.round(2)  #=> 1.23
#    1.234567.round(3)  #=> 1.235
#    1.234567.round(4)  #=> 1.2346
#    1.234567.round(5)  #=> 1.23457
# 
#    34567.89.round(-5) #=> 0
#    34567.89.round(-4) #=> 30000
#    34567.89.round(-3) #=> 35000
#    34567.89.round(-2) #=> 34600
#    34567.89.round(-1) #=> 34570
#    34567.89.round(0)  #=> 34568
#    34567.89.round(1)  #=> 34567.9
#    34567.89.round(2)  #=> 34567.89
#    34567.89.round(3)  #=> 34567.89
def round(ndigits=0); 0 || 0.0; end
##
# Returns <code>true</code> if <i>flt</i> is an invalid IEEE floating
# point number.
# 
#    a = -1.0      #=> -1.0
#    a.nan?        #=> false
#    a = 0.0/0.0   #=> NaN
#    a.nan?        #=> true
def nan?; true || false; end
##
# Returns <code>nil</code>, -1, or +1 depending on whether <i>flt</i>
# is finite, -infinity, or +infinity.
# 
#    (0.0).infinite?        #=> nil
#    (-1.0/0.0).infinite?   #=> -1
#    (+1.0/0.0).infinite?   #=> 1
def infinite?; 1 || nil; end
##
# Returns <code>true</code> if <i>flt</i> is a valid IEEE floating
# point number (it is not infinite, and <code>nan?</code> is
# <code>false</code>).
def finite?; true || false; end
##
# Returns 0 if the value is positive, pi otherwise.
def arg; 0 || 0.0; end
##
# Returns 0 if the value is positive, pi otherwise.
def angle; 0 || 0.0; end
##
# Returns 0 if the value is positive, pi otherwise.
def phase; 0 || 0.0; end
end

class NilClass < Object
##
# Returns zero as a rational.
def to_r; (0/1); end
##
# Returns zero as a rational.  The optional argument eps is always
# ignored.
def rationalize(eps=0); (0/1); end
##
# Always returns zero.
# 
#    nil.to_i   #=> 0
def to_i; 0; end
##
# Always returns zero.
# 
#    nil.to_f   #=> 0.0
def to_f; 0.0; end
##
# Always returns the empty string.
def to_s; ''; end
##
# Always returns an empty array.
# 
#    nil.to_a   #=> []
def to_a; end
##
# Always returns an empty hash.
# 
#    nil.to_h   #=> {}
def to_h; {}; end
##
# Always returns the string "nil".
def inspect; end
##
# And---Returns <code>false</code>. <i>obj</i> is always
# evaluated as it is the argument to a method call---there is no
# short-circuit evaluation in this case.
def &; false; end
##
# Or---Returns <code>false</code> if <i>obj</i> is
# <code>nil</code> or <code>false</code>; <code>true</code> otherwise.
def |; true || false; end
##
# Exclusive Or---If <i>obj</i> is <code>nil</code> or
# <code>false</code>, returns <code>false</code>; otherwise, returns
# <code>true</code>.
def ^; true || false; end
##
# Returns zero as a complex.
def to_c; Complex.new; end
end

##
# Random provides an interface to Ruby's pseudo-random number generator, or
# PRNG.  The PRNG produces a deterministic sequence of bits which approximate
# true randomness. The sequence may be represented by integers, floats, or
# binary strings.
# 
# The generator may be initialized with either a system-generated or
# user-supplied seed value by using Random.srand.
# 
# The class method Random.rand provides the base functionality of Kernel.rand
# along with better handling of floating point values. These are both
# interfaces to Random::DEFAULT, the Ruby system PRNG.
# 
# Random.new will create a new PRNG with a state independent of
# Random::DEFAULT, allowing multiple generators with different seed values or
# sequence positions to exist simultaneously. Random objects can be
# marshaled, allowing sequences to be saved and resumed.
# 
# PRNGs are currently implemented as a modified Mersenne Twister with a period
# of 2**19937-1.
class Random < Object
##
# Creates a new PRNG using +seed+ to set the initial state. If +seed+ is
# omitted, the generator is initialized with Random.new_seed.
# 
# See Random.srand for more information on the use of seed values.
def self.new(seed = Random.new_seed); end
##
# When +max+ is an Integer, +rand+ returns a random integer greater than
# or equal to zero and less than +max+. Unlike Kernel.rand, when +max+
# is a negative integer or zero, +rand+ raises an ArgumentError.
# 
#   prng = Random.new
#   prng.rand(100)       # => 42
# 
# When +max+ is a Float, +rand+ returns a random floating point number
# between 0.0 and +max+, including 0.0 and excluding +max+.
# 
#   prng.rand(1.5)       # => 1.4600282860034115
# 
# When +max+ is a Range, +rand+ returns a random number where
# range.member?(number) == true.
# 
#   prng.rand(5..9)      # => one of [5, 6, 7, 8, 9]
#   prng.rand(5...9)     # => one of [5, 6, 7, 8]
#   prng.rand(5.0..9.0)  # => between 5.0 and 9.0, including 9.0
#   prng.rand(5.0...9.0) # => between 5.0 and 9.0, excluding 9.0
# 
# Both the beginning and ending values of the range must respond to subtract
# (<tt>-</tt>) and add (<tt>+</tt>)methods, or rand will raise an
# ArgumentError.
def rand(max); 0; end
##
# Returns a random binary string containing +size+ bytes.
# 
#   random_string = Random.new.bytes(10) # => "\xD7:R\xAB?\x83\xCE\xFAkO"
#   random_string.size                   # => 10
def bytes(size); ''; end
##
# Returns the seed value used to initialize the generator. This may be used to
# initialize another generator with the same state at a later time, causing it
# to produce the same sequence of numbers.
# 
#   prng1 = Random.new(1234)
#   prng1.seed       #=> 1234
#   prng1.rand(100)  #=> 47
# 
#   prng2 = Random.new(prng1.seed)
#   prng2.rand(100)  #=> 47
def seed; 0; end
##
# Returns true if the two generators have the same internal state, otherwise
# false.  Equivalent generators will return the same sequence of
# pseudo-random numbers.  Two generators will generally have the same state
# only if they were initialized with the same seed
# 
#   Random.new == Random.new             # => false
#   Random.new(1234) == Random.new(1234) # => true
# 
# and have the same invocation history.
# 
#   prng1 = Random.new(1234)
#   prng2 = Random.new(1234)
#   prng1 == prng2 # => true
# 
#   prng1.rand     # => 0.1915194503788923
#   prng1 == prng2 # => false
# 
#   prng2.rand     # => 0.1915194503788923
#   prng1 == prng2 # => true
def ==; true || false; end
##
# Seeds the system pseudo-random number generator, Random::DEFAULT, with
# +number+.  The previous seed value is returned.
# 
# If +number+ is omitted, seeds the generator using a source of entropy
# provided by the operating system, if available (/dev/urandom on Unix systems
# or the RSA cryptographic provider on Windows), which is then combined with
# the time, the process id, and a sequence number.
# 
# srand may be used to ensure repeatable sequences of pseudo-random numbers
# between different runs of the program. By setting the seed to a known value,
# programs can be made deterministic during testing.
# 
#   srand 1234               # => 268519324636777531569100071560086917274
#   [ rand, rand ]           # => [0.1915194503788923, 0.6221087710398319]
#   [ rand(10), rand(1000) ] # => [4, 664]
#   srand 1234               # => 1234
#   [ rand, rand ]           # => [0.1915194503788923, 0.6221087710398319]
def self.srand(number = Random.new_seed); 1; end
##
# Returns an arbitrary seed value. This is used by Random.new
# when no seed value is specified as an argument.
# 
#   Random.new_seed  #=> 115032730400174366788466674494640623225
def self.new_seed; 0; end
end

class BasicObject
##
# Evaluates a string containing Ruby source code, or the given block,
# within the context of the receiver (_obj_). In order to set the
# context, the variable +self+ is set to _obj_ while
# the code is executing, giving the code access to _obj_'s
# instance variables. In the version of <code>instance_eval</code>
# that takes a +String+, the optional second and third
# parameters supply a filename and starting line number that are used
# when reporting compilation errors.
# 
#    class KlassWithSecret
#      def initialize
#        @secret = 99
#      end
#    end
#    k = KlassWithSecret.new
#    k.instance_eval { @secret }   #=> 99
def instance_eval(string  , filename=0, lineno=0); Object.new; end
##
# Executes the given block within the context of the receiver
# (_obj_). In order to set the context, the variable +self+ is set
# to _obj_ while the code is executing, giving the code access to
# _obj_'s instance variables.  Arguments are passed as block parameters.
# 
#    class KlassWithSecret
#      def initialize
#        @secret = 99
#      end
#    end
#    k = KlassWithSecret.new
#    k.instance_exec(5) {|x| @secret+x }   #=> 104
def instance_exec(&block); Object.new; end
##
# Invoked by Ruby when <i>obj</i> is sent a message it cannot handle.
# <i>symbol</i> is the symbol for the method called, and <i>args</i>
# are any arguments that were passed to it. By default, the interpreter
# raises an error when this method is called. However, it is possible
# to override the method to provide more dynamic behavior.
# If it is decided that a particular method should not be handled, then
# <i>super</i> should be called, so that ancestors can pick up the
# missing method.
# The example below creates
# a class <code>Roman</code>, which responds to methods with names
# consisting of roman numerals, returning the corresponding integer
# values.
# 
#    class Roman
#      def roman_to_int(str)
#        # ...
#      end
#      def method_missing(methId)
#        str = methId.id2name
#        roman_to_int(str)
#      end
#    end
# 
#    r = Roman.new
#    r.iv      #=> 4
#    r.xxiii   #=> 23
#    r.mm      #=> 2000
def method_missing(symbol  , args=0); Object.new; end
##
# Invokes the method identified by _symbol_, passing it any
# arguments specified. You can use <code>__send__</code> if the name
# +send+ clashes with an existing method in _obj_.
# When the method is identified by a string, the string is converted
# to a symbol.
# 
#    class Klass
#      def hello(*args)
#        "Hello " + args.join(' ')
#      end
#    end
#    k = Klass.new
#    k.send :hello, "gentle", "readers"   #=> "Hello gentle readers"
def send(symbol , args=0); Object.new; end
##
# Invokes the method identified by _symbol_, passing it any
# arguments specified. You can use <code>__send__</code> if the name
# +send+ clashes with an existing method in _obj_.
# When the method is identified by a string, the string is converted
# to a symbol.
# 
#    class Klass
#      def hello(*args)
#        "Hello " + args.join(' ')
#      end
#    end
#    k = Klass.new
#    k.send :hello, "gentle", "readers"   #=> "Hello gentle readers"
def __send__(symbol , args=0); Object.new; end
##
# Returns an integer identifier for +obj+.
# 
# The same number will be returned on all calls to +id+ for a given object,
# and no two active objects will share an id.
# 
# Object#object_id is a different concept from the +:name+ notation, which
# returns the symbol id of +name+.
# 
# Replaces the deprecated Object#id.
def __id__; 0; end
##
# Returns an integer identifier for +obj+.
# 
# The same number will be returned on all calls to +id+ for a given object,
# and no two active objects will share an id.
# 
# Object#object_id is a different concept from the +:name+ notation, which
# returns the symbol id of +name+.
# 
# Replaces the deprecated Object#id.
def object_id; 0; end
##
# Equality --- At the <code>Object</code> level, <code>==</code> returns
# <code>true</code> only if +obj+ and +other+ are the same object.
# Typically, this method is overridden in descendant classes to provide
# class-specific meaning.
# 
# Unlike <code>==</code>, the <code>equal?</code> method should never be
# overridden by subclasses as it is used to determine object identity
# (that is, <code>a.equal?(b)</code> if and only if <code>a</code> is the
# same object as <code>b</code>):
# 
#   obj = "a"
#   other = obj.dup
# 
#   a == other      #=> true
#   a.equal? other  #=> false
#   a.equal? a      #=> true
# 
# The <code>eql?</code> method returns <code>true</code> if +obj+ and
# +other+ refer to the same hash key.  This is used by Hash to test members
# for equality.  For objects of class <code>Object</code>, <code>eql?</code>
# is synonymous with <code>==</code>.  Subclasses normally continue this
# tradition by aliasing <code>eql?</code> to their overridden <code>==</code>
# method, but there are exceptions.  <code>Numeric</code> types, for
# example, perform type conversion across <code>==</code>, but not across
# <code>eql?</code>, so:
# 
#    1 == 1.0     #=> true
#    1.eql? 1.0   #=> false
def ==; true || false; end
##
# Equality --- At the <code>Object</code> level, <code>==</code> returns
# <code>true</code> only if +obj+ and +other+ are the same object.
# Typically, this method is overridden in descendant classes to provide
# class-specific meaning.
# 
# Unlike <code>==</code>, the <code>equal?</code> method should never be
# overridden by subclasses as it is used to determine object identity
# (that is, <code>a.equal?(b)</code> if and only if <code>a</code> is the
# same object as <code>b</code>):
# 
#   obj = "a"
#   other = obj.dup
# 
#   a == other      #=> true
#   a.equal? other  #=> false
#   a.equal? a      #=> true
# 
# The <code>eql?</code> method returns <code>true</code> if +obj+ and
# +other+ refer to the same hash key.  This is used by Hash to test members
# for equality.  For objects of class <code>Object</code>, <code>eql?</code>
# is synonymous with <code>==</code>.  Subclasses normally continue this
# tradition by aliasing <code>eql?</code> to their overridden <code>==</code>
# method, but there are exceptions.  <code>Numeric</code> types, for
# example, perform type conversion across <code>==</code>, but not across
# <code>eql?</code>, so:
# 
#    1 == 1.0     #=> true
#    1.eql? 1.0   #=> false
def equal?(other); true || false; end
##
# Equality --- At the <code>Object</code> level, <code>==</code> returns
# <code>true</code> only if +obj+ and +other+ are the same object.
# Typically, this method is overridden in descendant classes to provide
# class-specific meaning.
# 
# Unlike <code>==</code>, the <code>equal?</code> method should never be
# overridden by subclasses as it is used to determine object identity
# (that is, <code>a.equal?(b)</code> if and only if <code>a</code> is the
# same object as <code>b</code>):
# 
#   obj = "a"
#   other = obj.dup
# 
#   a == other      #=> true
#   a.equal? other  #=> false
#   a.equal? a      #=> true
# 
# The <code>eql?</code> method returns <code>true</code> if +obj+ and
# +other+ refer to the same hash key.  This is used by Hash to test members
# for equality.  For objects of class <code>Object</code>, <code>eql?</code>
# is synonymous with <code>==</code>.  Subclasses normally continue this
# tradition by aliasing <code>eql?</code> to their overridden <code>==</code>
# method, but there are exceptions.  <code>Numeric</code> types, for
# example, perform type conversion across <code>==</code>, but not across
# <code>eql?</code>, so:
# 
#    1 == 1.0     #=> true
#    1.eql? 1.0   #=> false
def eql?(other); true || false; end
##
# Boolean negate.
def !; true || false; end
##
# Returns true if two objects are not-equal, otherwise false.
def !=; true || false; end
##
# Invoked as a callback whenever a singleton method is added to the
# receiver.
# 
#    module Chatty
#      def Chatty.singleton_method_added(id)
#        puts "Adding #{id.id2name}"
#      end
#      def self.one()     end
#      def two()          end
#      def Chatty.three() end
#    end
# 
# <em>produces:</em>
# 
#    Adding singleton_method_added
#    Adding one
#    Adding three
def singleton_method_added(symbol); end
##
# Invoked as a callback whenever a singleton method is removed from
# the receiver.
# 
#    module Chatty
#      def Chatty.singleton_method_removed(id)
#        puts "Removing #{id.id2name}"
#      end
#      def self.one()     end
#      def two()          end
#      def Chatty.three() end
#      class << self
#        remove_method :three
#        remove_method :one
#      end
#    end
# 
# <em>produces:</em>
# 
#    Removing three
#    Removing one
def singleton_method_removed(symbol); end
##
# Invoked as a callback whenever a singleton method is undefined in
# the receiver.
# 
#    module Chatty
#      def Chatty.singleton_method_undefined(id)
#        puts "Undefining #{id.id2name}"
#      end
#      def Chatty.one()   end
#      class << self
#         undef_method(:one)
#      end
#    end
# 
# <em>produces:</em>
# 
#    Undefining one
def singleton_method_undefined(symbol); end
end

##
# An Encoding instance represents a character encoding usable in Ruby. It is
# defined as a constant under the Encoding namespace. It has a name and
# optionally, aliases:
# 
#   Encoding::ISO_8859_1.name
#   #=> #<Encoding:ISO-8859-1>
# 
#   Encoding::ISO_8859_1.names
#   #=> ["ISO-8859-1", "ISO8859-1"]
# 
# Ruby methods dealing with encodings return or accept Encoding instances as
# arguments (when a method accepts an Encoding instance as an argument, it
# can be passed an Encoding name or alias instead).
# 
#   "some string".encoding
#   #=> #<Encoding:UTF-8>
# 
#   string = "some string".encode(Encoding::ISO_8859_1)
#   #=> "some string"
#   string.encoding
#   #=> #<Encoding:ISO-8859-1>
# 
#   "some string".encode "ISO-8859-1"
#   #=> "some string"
# 
# <code>Encoding::ASCII_8BIT</code> is a special encoding that is usually
# used for a byte string, not a character string. But as the name insists,
# its characters in the range of ASCII are considered as ASCII characters.
# This is useful when you use ASCII-8BIT characters with other ASCII
# compatible characters.
# 
# == Changing an encoding
# 
# The associated Encoding of a String can be changed in two different ways.
# 
# First, it is possible to set the Encoding of a string to a new Encoding
# without changing the internal byte representation of the string, with
# String#force_encoding. This is how you can tell Ruby the correct encoding
# of a string.
# 
#   string
#   #=> "R\xC3\xA9sum\xC3\xA9"
#   string.encoding
#   #=> #<Encoding:ISO-8859-1>
#   string.force_encoding(Encoding::UTF_8)
#   #=> "R\u00E9sum\u00E9"
# 
# Second, it is possible to transcode a string, i.e. translate its internal
# byte representation to another encoding. Its associated encoding is also
# set to the other encoding. See String#encode for the various forms of
# transcoding, and the Encoding::Converter class for additional control over
# the transcoding process.
# 
#   string
#   #=> "R\u00E9sum\u00E9"
#   string.encoding
#   #=> #<Encoding:UTF-8>
#   string = string.encode!(Encoding::ISO_8859_1)
#   #=> "R\xE9sum\xE9"
#   string.encoding
#   #=> #<Encoding::ISO-8859-1>
# 
# == Script encoding
# 
# All Ruby script code has an associated Encoding which any String literal
# created in the source code will be associated to.
# 
# The default script encoding is <code>Encoding::US-ASCII</code>, but it can
# be changed by a magic comment on the first line of the source code file (or
# second line, if there is a shebang line on the first). The comment must
# contain the word <code>coding</code> or <code>encoding</code>, followed
# by a colon, space and the Encoding name or alias:
# 
#   # encoding: UTF-8
# 
#   "some string".encoding
#   #=> #<Encoding:UTF-8>
# 
# The <code>__ENCODING__</code> keyword returns the script encoding of the file
# which the keyword is written:
# 
#   # encoding: ISO-8859-1
# 
#   __ENCODING__
#   #=> #<Encoding:ISO-8859-1>
# 
# <code>ruby -K</code> will change the default locale encoding, but this is
# not recommended. Ruby source files should declare its script encoding by a
# magic comment even when they only depend on US-ASCII strings or regular
# expressions.
# 
# == Locale encoding
# 
# The default encoding of the environment. Usually derived from locale.
# 
# see Encoding.locale_charmap, Encoding.find('locale')
# 
# == Filesystem encoding
# 
# The default encoding of strings from the filesystem of the environment.
# This is used for strings of file names or paths.
# 
# see Encoding.find('filesystem')
# 
# == External encoding
# 
# Each IO object has an external encoding which indicates the encoding that
# Ruby will use to read its data. By default Ruby sets the external encoding
# of an IO object to the default external encoding. The default external
# encoding is set by locale encoding or the interpreter <code>-E</code> option.
# Encoding.default_external returns the current value of the external
# encoding.
# 
#   ENV["LANG"]
#   #=> "UTF-8"
#   Encoding.default_external
#   #=> #<Encoding:UTF-8>
# 
#   $ ruby -E ISO-8859-1 -e "p Encoding.default_external"
#   #<Encoding:ISO-8859-1>
# 
#   $ LANG=C ruby -e 'p Encoding.default_external'
#   #<Encoding:US-ASCII>
# 
# The default external encoding may also be set through
# Encoding.default_external=, but you should not do this as strings created
# before and after the change will have inconsistent encodings.  Instead use
# <code>ruby -E</code> to invoke ruby with the correct external encoding.
# 
# When you know that the actual encoding of the data of an IO object is not
# the default external encoding, you can reset its external encoding with
# IO#set_encoding or set it at IO object creation (see IO.new options).
# 
# == Internal encoding
# 
# To process the data of an IO object which has an encoding different
# from its external encoding, you can set its internal encoding. Ruby will use
# this internal encoding to transcode the data when it is read from the IO
# object.
# 
# Conversely, when data is written to the IO object it is transcoded from the
# internal encoding to the external encoding of the IO object.
# 
# The internal encoding of an IO object can be set with
# IO#set_encoding or at IO object creation (see IO.new options).
# 
# The internal encoding is optional and when not set, the Ruby default
# internal encoding is used. If not explicitly set this default internal
# encoding is +nil+ meaning that by default, no transcoding occurs.
# 
# The default internal encoding can be set with the interpreter option
# <code>-E</code>. Encoding.default_internal returns the current internal
# encoding.
# 
#    $ ruby -e 'p Encoding.default_internal'
#    nil
# 
#    $ ruby -E ISO-8859-1:UTF-8 -e "p [Encoding.default_external, \
#      Encoding.default_internal]"
#    [#<Encoding:ISO-8859-1>, #<Encoding:UTF-8>]
# 
# The default internal encoding may also be set through
# Encoding.default_internal=, but you should not do this as strings created
# before and after the change will have inconsistent encodings.  Instead use
# <code>ruby -E</code> to invoke ruby with the correct internal encoding.
# 
# == IO encoding example
# 
# In the following example a UTF-8 encoded string "R\u00E9sum\u00E9" is transcoded for
# output to ISO-8859-1 encoding, then read back in and transcoded to UTF-8:
# 
#   string = "R\u00E9sum\u00E9"
# 
#   open("transcoded.txt", "w:ISO-8859-1") do |io|
#     io.write(string)
#   end
# 
#   puts "raw text:"
#   p File.binread("transcoded.txt")
#   puts
# 
#   open("transcoded.txt", "r:ISO-8859-1:UTF-8") do |io|
#     puts "transcoded text:"
#     p io.read
#   end
# 
# While writing the file, the internal encoding is not specified as it is
# only necessary for reading.  While reading the file both the internal and
# external encoding must be specified to obtain the correct result.
# 
#   $ ruby t.rb
#   raw text:
#   "R\xE9sum\xE9"
# 
#   transcoded text:
#   "R\u00E9sum\u00E9"
class Encoding < Object
##
# Raised by Encoding and String methods when the source encoding is
# incompatible with the target encoding.
class CompatibilityError < EncodingError
end

##
# Raised by Encoding and String methods when a transcoding operation
# fails.
class UndefinedConversionError < rb_eEncodingError
##
# Returns the source encoding name as a string.
def source_encoding_name; ''; end
##
# Returns the destination encoding name as a string.
def destination_encoding_name; ''; end
##
# Returns the source encoding as an encoding object.
# 
# Note that the result may not be equal to the source encoding of
# the encoding converter if the conversion has multiple steps.
# 
#  ec = Encoding::Converter.new("ISO-8859-1", "EUC-JP") # ISO-8859-1 -> UTF-8 -> EUC-JP
#  begin
#    ec.convert("\xa0") # NO-BREAK SPACE, which is available in UTF-8 but not in EUC-JP.
#  rescue Encoding::UndefinedConversionError
#    p $!.source_encoding              #=> #<Encoding:UTF-8>
#    p $!.destination_encoding         #=> #<Encoding:EUC-JP>
#    p $!.source_encoding_name         #=> "UTF-8"
#    p $!.destination_encoding_name    #=> "EUC-JP"
#  end
def source_encoding; Encoding.new; end
##
# Returns the destination encoding as an encoding object.
def destination_encoding; ''; end
##
# Returns the one-character string which cause Encoding::UndefinedConversionError.
# 
#  ec = Encoding::Converter.new("ISO-8859-1", "EUC-JP")
#  begin
#    ec.convert("\xa0")
#  rescue Encoding::UndefinedConversionError
#    puts $!.error_char.dump   #=> "\xC2\xA0"
#    p $!.error_char.encoding  #=> #<Encoding:UTF-8>
#  end
def error_char; ''; end
end

##
# Raised by Encoding and String methods when the string being
# transcoded contains a byte invalid for the either the source or
# target encoding.
class InvalidByteSequenceError < rb_eEncodingError
##
# Returns the source encoding name as a string.
def source_encoding_name; ''; end
##
# Returns the destination encoding name as a string.
def destination_encoding_name; ''; end
##
# Returns the source encoding as an encoding object.
# 
# Note that the result may not be equal to the source encoding of
# the encoding converter if the conversion has multiple steps.
# 
#  ec = Encoding::Converter.new("ISO-8859-1", "EUC-JP") # ISO-8859-1 -> UTF-8 -> EUC-JP
#  begin
#    ec.convert("\xa0") # NO-BREAK SPACE, which is available in UTF-8 but not in EUC-JP.
#  rescue Encoding::UndefinedConversionError
#    p $!.source_encoding              #=> #<Encoding:UTF-8>
#    p $!.destination_encoding         #=> #<Encoding:EUC-JP>
#    p $!.source_encoding_name         #=> "UTF-8"
#    p $!.destination_encoding_name    #=> "EUC-JP"
#  end
def source_encoding; Encoding.new; end
##
# Returns the destination encoding as an encoding object.
def destination_encoding; ''; end
##
# Returns the discarded bytes when Encoding::InvalidByteSequenceError occurs.
# 
#  ec = Encoding::Converter.new("EUC-JP", "ISO-8859-1")
#  begin
#    ec.convert("abc\xA1\xFFdef")
#  rescue Encoding::InvalidByteSequenceError
#    p $!      #=> #<Encoding::InvalidByteSequenceError: "\xA1" followed by "\xFF" on EUC-JP>
#    puts $!.error_bytes.dump          #=> "\xA1"
#    puts $!.readagain_bytes.dump      #=> "\xFF"
#  end
def error_bytes; ''; end
##
# Returns the bytes to be read again when Encoding::InvalidByteSequenceError occurs.
def readagain_bytes; ''; end
##
# Returns true if the invalid byte sequence error is caused by
# premature end of string.
# 
#  ec = Encoding::Converter.new("EUC-JP", "ISO-8859-1")
# 
#  begin
#    ec.convert("abc\xA1z")
#  rescue Encoding::InvalidByteSequenceError
#    p $!      #=> #<Encoding::InvalidByteSequenceError: "\xA1" followed by "z" on EUC-JP>
#    p $!.incomplete_input?    #=> false
#  end
# 
#  begin
#    ec.convert("abc\xA1")
#    ec.finish
#  rescue Encoding::InvalidByteSequenceError
#    p $!      #=> #<Encoding::InvalidByteSequenceError: incomplete "\xA1" on EUC-JP>
#    p $!.incomplete_input?    #=> true
#  end
def incomplete_input?; true || false; end
end

##
# Raised by transcoding methods when a named encoding does not
# correspond with a known converter.
class ConverterNotFoundError < rb_eEncodingError
end

class Converter < Data
##
# Returns the corresponding ASCII compatible encoding.
# 
# Returns nil if the argument is an ASCII compatible encoding.
# 
# "corresponding ASCII compatible encoding" is an ASCII compatible encoding which
# can represents exactly the same characters as the given ASCII incompatible encoding.
# So, no conversion undefined error occurs when converting between the two encodings.
# 
#   Encoding::Converter.asciicompat_encoding("ISO-2022-JP") #=> #<Encoding:stateless-ISO-2022-JP>
#   Encoding::Converter.asciicompat_encoding("UTF-16BE") #=> #<Encoding:UTF-8>
#   Encoding::Converter.asciicompat_encoding("UTF-8") #=> nil
def self.asciicompat_encoding(string); Encoding.new || nil; end
##
# Returns a conversion path.
# 
#  p Encoding::Converter.search_convpath("ISO-8859-1", "EUC-JP")
#  #=> [[#<Encoding:ISO-8859-1>, #<Encoding:UTF-8>],
#  #    [#<Encoding:UTF-8>, #<Encoding:EUC-JP>]]
# 
#  p Encoding::Converter.search_convpath("ISO-8859-1", "EUC-JP", universal_newline: true)
#  or
#  p Encoding::Converter.search_convpath("ISO-8859-1", "EUC-JP", newline: :universal)
#  #=> [[#<Encoding:ISO-8859-1>, #<Encoding:UTF-8>],
#  #    [#<Encoding:UTF-8>, #<Encoding:EUC-JP>],
#  #    "universal_newline"]
# 
#  p Encoding::Converter.search_convpath("ISO-8859-1", "UTF-32BE", universal_newline: true)
#  or
#  p Encoding::Converter.search_convpath("ISO-8859-1", "UTF-32BE", newline: :universal)
#  #=> [[#<Encoding:ISO-8859-1>, #<Encoding:UTF-8>],
#  #    "universal_newline",
#  #    [#<Encoding:UTF-8>, #<Encoding:UTF-32BE>]]
def self.search_convpath(source_encoding, destination_encoding); []; end
##
# possible options elements:
#   hash form:
#     :invalid => nil            # raise error on invalid byte sequence (default)
#     :invalid => :replace       # replace invalid byte sequence
#     :undef => nil              # raise error on undefined conversion (default)
#     :undef => :replace         # replace undefined conversion
#     :replace => string         # replacement string ("?" or "\uFFFD" if not specified)
#     :newline => :universal     # decorator for converting CRLF and CR to LF
#     :newline => :crlf          # decorator for converting LF to CRLF
#     :newline => :cr            # decorator for converting LF to CR
#     :universal_newline => true # decorator for converting CRLF and CR to LF
#     :crlf_newline => true      # decorator for converting LF to CRLF
#     :cr_newline => true        # decorator for converting LF to CR
#     :xml => :text              # escape as XML CharData.
#     :xml => :attr              # escape as XML AttValue
#   integer form:
#     Encoding::Converter::INVALID_REPLACE
#     Encoding::Converter::UNDEF_REPLACE
#     Encoding::Converter::UNDEF_HEX_CHARREF
#     Encoding::Converter::UNIVERSAL_NEWLINE_DECORATOR
#     Encoding::Converter::CRLF_NEWLINE_DECORATOR
#     Encoding::Converter::CR_NEWLINE_DECORATOR
#     Encoding::Converter::XML_TEXT_DECORATOR
#     Encoding::Converter::XML_ATTR_CONTENT_DECORATOR
#     Encoding::Converter::XML_ATTR_QUOTE_DECORATOR
# 
# Encoding::Converter.new creates an instance of Encoding::Converter.
# 
# Source_encoding and destination_encoding should be a string or
# Encoding object.
# 
# opt should be nil, a hash or an integer.
# 
# convpath should be an array.
# convpath may contain
# - two-element arrays which contain encodings or encoding names, or
# - strings representing decorator names.
# 
# Encoding::Converter.new optionally takes an option.
# The option should be a hash or an integer.
# The option hash can contain :invalid => nil, etc.
# The option integer should be logical-or of constants such as
# Encoding::Converter::INVALID_REPLACE, etc.
# 
# [:invalid => nil]
#   Raise error on invalid byte sequence.  This is a default behavior.
# [:invalid => :replace]
#   Replace invalid byte sequence by replacement string.
# [:undef => nil]
#   Raise an error if a character in source_encoding is not defined in destination_encoding.
#   This is a default behavior.
# [:undef => :replace]
#   Replace undefined character in destination_encoding with replacement string.
# [:replace => string]
#   Specify the replacement string.
#   If not specified, "\uFFFD" is used for Unicode encodings and "?" for others.
# [:universal_newline => true]
#   Convert CRLF and CR to LF.
# [:crlf_newline => true]
#   Convert LF to CRLF.
# [:cr_newline => true]
#   Convert LF to CR.
# [:xml => :text]
#   Escape as XML CharData.
#   This form can be used as a HTML 4.0 #PCDATA.
#   - '&' -> '&amp;'
#   - '<' -> '&lt;'
#   - '>' -> '&gt;'
#   - undefined characters in destination_encoding -> hexadecimal CharRef such as &#xHH;
# [:xml => :attr]
#   Escape as XML AttValue.
#   The converted result is quoted as "...".
#   This form can be used as a HTML 4.0 attribute value.
#   - '&' -> '&amp;'
#   - '<' -> '&lt;'
#   - '>' -> '&gt;'
#   - '"' -> '&quot;'
#   - undefined characters in destination_encoding -> hexadecimal CharRef such as &#xHH;
# 
# Examples:
#   # UTF-16BE to UTF-8
#   ec = Encoding::Converter.new("UTF-16BE", "UTF-8")
# 
#   # Usually, decorators such as newline conversion are inserted last.
#   ec = Encoding::Converter.new("UTF-16BE", "UTF-8", :universal_newline => true)
#   p ec.convpath #=> [[#<Encoding:UTF-16BE>, #<Encoding:UTF-8>],
#                 #    "universal_newline"]
# 
#   # But, if the last encoding is ASCII incompatible,
#   # decorators are inserted before the last conversion.
#   ec = Encoding::Converter.new("UTF-8", "UTF-16BE", :crlf_newline => true)
#   p ec.convpath #=> ["crlf_newline",
#                 #    [#<Encoding:UTF-8>, #<Encoding:UTF-16BE>]]
# 
#   # Conversion path can be specified directly.
#   ec = Encoding::Converter.new(["universal_newline", ["EUC-JP", "UTF-8"], ["UTF-8", "UTF-16BE"]])
#   p ec.convpath #=> ["universal_newline",
#                 #    [#<Encoding:EUC-JP>, #<Encoding:UTF-8>],
#                 #    [#<Encoding:UTF-8>, #<Encoding:UTF-16BE>]]
def self.new(source_encoding, destination_encoding); end
##
# Returns a printable version of <i>ec</i>
# 
#   ec = Encoding::Converter.new("iso-8859-1", "utf-8")
#   puts ec.inspect    #=> #<Encoding::Converter: ISO-8859-1 to UTF-8>
def inspect; ''; end
##
# Returns the conversion path of ec.
# 
# The result is an array of conversions.
# 
#   ec = Encoding::Converter.new("ISO-8859-1", "EUC-JP", crlf_newline: true)
#   p ec.convpath
#   #=> [[#<Encoding:ISO-8859-1>, #<Encoding:UTF-8>],
#   #    [#<Encoding:UTF-8>, #<Encoding:EUC-JP>],
#   #    "crlf_newline"]
# 
# Each element of the array is a pair of encodings or a string.
# A pair means an encoding conversion.
# A string means a decorator.
# 
# In the above example, [#<Encoding:ISO-8859-1>, #<Encoding:UTF-8>] means
# a converter from ISO-8859-1 to UTF-8.
# "crlf_newline" means newline converter from LF to CRLF.
def convpath; []; end
##
# Returns the source encoding as an Encoding object.
def source_encoding; Encoding.new; end
##
# Returns the destination encoding as an Encoding object.
def destination_encoding; Encoding.new; end
##
# possible opt elements:
#   hash form:
#     :partial_input => true           # source buffer may be part of larger source
#     :after_output => true            # stop conversion after output before input
#   integer form:
#     Encoding::Converter::PARTIAL_INPUT
#     Encoding::Converter::AFTER_OUTPUT
# 
# possible results:
#    :invalid_byte_sequence
#    :incomplete_input
#    :undefined_conversion
#    :after_output
#    :destination_buffer_full
#    :source_buffer_empty
#    :finished
# 
# primitive_convert converts source_buffer into destination_buffer.
# 
# source_buffer should be a string or nil.
# nil means an empty string.
# 
# destination_buffer should be a string.
# 
# destination_byteoffset should be an integer or nil.
# nil means the end of destination_buffer.
# If it is omitted, nil is assumed.
# 
# destination_bytesize should be an integer or nil.
# nil means unlimited.
# If it is omitted, nil is assumed.
# 
# opt should be nil, a hash or an integer.
# nil means no flags.
# If it is omitted, nil is assumed.
# 
# primitive_convert converts the content of source_buffer from beginning
# and store the result into destination_buffer.
# 
# destination_byteoffset and destination_bytesize specify the region which
# the converted result is stored.
# destination_byteoffset specifies the start position in destination_buffer in bytes.
# If destination_byteoffset is nil,
# destination_buffer.bytesize is used for appending the result.
# destination_bytesize specifies maximum number of bytes.
# If destination_bytesize is nil,
# destination size is unlimited.
# After conversion, destination_buffer is resized to
# destination_byteoffset + actually produced number of bytes.
# Also destination_buffer's encoding is set to destination_encoding.
# 
# primitive_convert drops the converted part of source_buffer.
# the dropped part is converted in destination_buffer or
# buffered in Encoding::Converter object.
# 
# primitive_convert stops conversion when one of following condition met.
# - invalid byte sequence found in source buffer (:invalid_byte_sequence)
#   +primitive_errinfo+ and +last_error+ methods returns the detail of the error.
# - unexpected end of source buffer (:incomplete_input)
#   this occur only when :partial_input is not specified.
#   +primitive_errinfo+ and +last_error+ methods returns the detail of the error.
# - character not representable in output encoding (:undefined_conversion)
#   +primitive_errinfo+ and +last_error+ methods returns the detail of the error.
# - after some output is generated, before input is done (:after_output)
#   this occur only when :after_output is specified.
# - destination buffer is full (:destination_buffer_full)
#   this occur only when destination_bytesize is non-nil.
# - source buffer is empty (:source_buffer_empty)
#   this occur only when :partial_input is specified.
# - conversion is finished (:finished)
# 
# example:
#   ec = Encoding::Converter.new("UTF-8", "UTF-16BE")
#   ret = ec.primitive_convert(src="pi", dst="", nil, 100)
#   p [ret, src, dst] #=> [:finished, "", "\x00p\x00i"]
# 
#   ec = Encoding::Converter.new("UTF-8", "UTF-16BE")
#   ret = ec.primitive_convert(src="pi", dst="", nil, 1)
#   p [ret, src, dst] #=> [:destination_buffer_full, "i", "\x00"]
#   ret = ec.primitive_convert(src, dst="", nil, 1)
#   p [ret, src, dst] #=> [:destination_buffer_full, "", "p"]
#   ret = ec.primitive_convert(src, dst="", nil, 1)
#   p [ret, src, dst] #=> [:destination_buffer_full, "", "\x00"]
#   ret = ec.primitive_convert(src, dst="", nil, 1)
#   p [ret, src, dst] #=> [:finished, "", "i"]
def primitive_convert(source_buffer, destination_buffer); :a; end
##
# Convert source_string and return destination_string.
# 
# source_string is assumed as a part of source.
# i.e.  :partial_input=>true is specified internally.
# finish method should be used last.
# 
#   ec = Encoding::Converter.new("utf-8", "euc-jp")
#   puts ec.convert("\u3042").dump     #=> "\xA4\xA2"
#   puts ec.finish.dump                #=> ""
# 
#   ec = Encoding::Converter.new("euc-jp", "utf-8")
#   puts ec.convert("\xA4").dump       #=> ""
#   puts ec.convert("\xA2").dump       #=> "\xE3\x81\x82"
#   puts ec.finish.dump                #=> ""
# 
#   ec = Encoding::Converter.new("utf-8", "iso-2022-jp")
#   puts ec.convert("\xE3").dump       #=> "".force_encoding("ISO-2022-JP")
#   puts ec.convert("\x81").dump       #=> "".force_encoding("ISO-2022-JP")
#   puts ec.convert("\x82").dump       #=> "\e$B$\"".force_encoding("ISO-2022-JP")
#   puts ec.finish.dump                #=> "\e(B".force_encoding("ISO-2022-JP")
# 
# If a conversion error occur,
# Encoding::UndefinedConversionError or
# Encoding::InvalidByteSequenceError is raised.
# Encoding::Converter#convert doesn't supply methods to recover or restart
# from these exceptions.
# When you want to handle these conversion errors,
# use Encoding::Converter#primitive_convert.
def convert(source_string); ''; end
##
# Finishes the converter.
# It returns the last part of the converted string.
# 
#   ec = Encoding::Converter.new("utf-8", "iso-2022-jp")
#   p ec.convert("\u3042")     #=> "\e$B$\""
#   p ec.finish                #=> "\e(B"
def finish; ''; end
##
# primitive_errinfo returns important information regarding the last error
# as a 5-element array:
# 
#   [result, enc1, enc2, error_bytes, readagain_bytes]
# 
# result is the last result of primitive_convert.
# 
# Other elements are only meaningful when result is
# :invalid_byte_sequence, :incomplete_input or :undefined_conversion.
# 
# enc1 and enc2 indicate a conversion step as a pair of strings.
# For example, a converter from EUC-JP to ISO-8859-1 converts
# a string as follows: EUC-JP -> UTF-8 -> ISO-8859-1.
# So [enc1, enc2] is either ["EUC-JP", "UTF-8"] or ["UTF-8", "ISO-8859-1"].
# 
# error_bytes and readagain_bytes indicate the byte sequences which caused the error.
# error_bytes is discarded portion.
# readagain_bytes is buffered portion which is read again on next conversion.
# 
# Example:
# 
#   # \xff is invalid as EUC-JP.
#   ec = Encoding::Converter.new("EUC-JP", "Shift_JIS")
#   ec.primitive_convert(src="\xff", dst="", nil, 10)
#   p ec.primitive_errinfo
#   #=> [:invalid_byte_sequence, "EUC-JP", "UTF-8", "\xFF", ""]
# 
#   # HIRAGANA LETTER A (\xa4\xa2 in EUC-JP) is not representable in ISO-8859-1.
#   # Since this error is occur in UTF-8 to ISO-8859-1 conversion,
#   # error_bytes is HIRAGANA LETTER A in UTF-8 (\xE3\x81\x82).
#   ec = Encoding::Converter.new("EUC-JP", "ISO-8859-1")
#   ec.primitive_convert(src="\xa4\xa2", dst="", nil, 10)
#   p ec.primitive_errinfo
#   #=> [:undefined_conversion, "UTF-8", "ISO-8859-1", "\xE3\x81\x82", ""]
# 
#   # partial character is invalid
#   ec = Encoding::Converter.new("EUC-JP", "ISO-8859-1")
#   ec.primitive_convert(src="\xa4", dst="", nil, 10)
#   p ec.primitive_errinfo
#   #=> [:incomplete_input, "EUC-JP", "UTF-8", "\xA4", ""]
# 
#   # Encoding::Converter::PARTIAL_INPUT prevents invalid errors by
#   # partial characters.
#   ec = Encoding::Converter.new("EUC-JP", "ISO-8859-1")
#   ec.primitive_convert(src="\xa4", dst="", nil, 10, Encoding::Converter::PARTIAL_INPUT)
#   p ec.primitive_errinfo
#   #=> [:source_buffer_empty, nil, nil, nil, nil]
# 
#   # \xd8\x00\x00@ is invalid as UTF-16BE because
#   # no low surrogate after high surrogate (\xd8\x00).
#   # It is detected by 3rd byte (\00) which is part of next character.
#   # So the high surrogate (\xd8\x00) is discarded and
#   # the 3rd byte is read again later.
#   # Since the byte is buffered in ec, it is dropped from src.
#   ec = Encoding::Converter.new("UTF-16BE", "UTF-8")
#   ec.primitive_convert(src="\xd8\x00\x00@", dst="", nil, 10)
#   p ec.primitive_errinfo
#   #=> [:invalid_byte_sequence, "UTF-16BE", "UTF-8", "\xD8\x00", "\x00"]
#   p src
#   #=> "@"
# 
#   # Similar to UTF-16BE, \x00\xd8@\x00 is invalid as UTF-16LE.
#   # The problem is detected by 4th byte.
#   ec = Encoding::Converter.new("UTF-16LE", "UTF-8")
#   ec.primitive_convert(src="\x00\xd8@\x00", dst="", nil, 10)
#   p ec.primitive_errinfo
#   #=> [:invalid_byte_sequence, "UTF-16LE", "UTF-8", "\x00\xD8", "@\x00"]
#   p src
#   #=> ""
def primitive_errinfo; []; end
##
# Inserts string into the encoding converter.
# The string will be converted to the destination encoding and
# output on later conversions.
# 
# If the destination encoding is stateful,
# string is converted according to the state and the state is updated.
# 
# This method should be used only when a conversion error occurs.
# 
#  ec = Encoding::Converter.new("utf-8", "iso-8859-1")
#  src = "HIRAGANA LETTER A is \u{3042}."
#  dst = ""
#  p ec.primitive_convert(src, dst)    #=> :undefined_conversion
#  puts "[#{dst.dump}, #{src.dump}]"   #=> ["HIRAGANA LETTER A is ", "."]
#  ec.insert_output("<err>")
#  p ec.primitive_convert(src, dst)    #=> :finished
#  puts "[#{dst.dump}, #{src.dump}]"   #=> ["HIRAGANA LETTER A is <err>.", ""]
# 
#  ec = Encoding::Converter.new("utf-8", "iso-2022-jp")
#  src = "\u{306F 3041 3068 2661 3002}" # U+2661 is not representable in iso-2022-jp
#  dst = ""
#  p ec.primitive_convert(src, dst)    #=> :undefined_conversion
#  puts "[#{dst.dump}, #{src.dump}]"   #=> ["\e$B$O$!$H".force_encoding("ISO-2022-JP"), "\xE3\x80\x82"]
#  ec.insert_output "?"                # state change required to output "?".
#  p ec.primitive_convert(src, dst)    #=> :finished
#  puts "[#{dst.dump}, #{src.dump}]"   #=> ["\e$B$O$!$H\e(B?\e$B!#\e(B".force_encoding("ISO-2022-JP"), ""]
def insert_output(string); end
##
# Returns an exception object for the last conversion.
# Returns nil if the last conversion did not produce an error.
# 
# "error" means that
# Encoding::InvalidByteSequenceError and Encoding::UndefinedConversionError for
# Encoding::Converter#convert and
# :invalid_byte_sequence, :incomplete_input and :undefined_conversion for
# Encoding::Converter#primitive_convert.
# 
#  ec = Encoding::Converter.new("utf-8", "iso-8859-1")
#  p ec.primitive_convert(src="\xf1abcd", dst="")       #=> :invalid_byte_sequence
#  p ec.last_error      #=> #<Encoding::InvalidByteSequenceError: "\xF1" followed by "a" on UTF-8>
#  p ec.primitive_convert(src, dst, nil, 1)             #=> :destination_buffer_full
#  p ec.last_error      #=> nil
def last_error; Exception.new || nil; end
##
# Returns the replacement string.
# 
#  ec = Encoding::Converter.new("euc-jp", "us-ascii")
#  p ec.replacement    #=> "?"
# 
#  ec = Encoding::Converter.new("euc-jp", "utf-8")
#  p ec.replacement    #=> "\uFFFD"
def replacement; ''; end
##
# Sets the replacement string.
# 
#  ec = Encoding::Converter.new("utf-8", "us-ascii", :undef => :replace)
#  ec.replacement = "<undef>"
#  p ec.convert("a \u3042 b")      #=> "a <undef> b"
def replacement= string; end
def ==; true || false; end
end

##
# Returns the name of the encoding.
# 
#   Encoding::UTF_8.name      #=> "UTF-8"
def name; ''; end
##
# Returns a string which represents the encoding for programmers.
# 
#   Encoding::UTF_8.inspect       #=> "#<Encoding:UTF-8>"
#   Encoding::ISO_2022_JP.inspect #=> "#<Encoding:ISO-2022-JP (dummy)>"
def inspect; ''; end
##
# Returns the list of name and aliases of the encoding.
# 
#   Encoding::WINDOWS_31J.names  #=> ["Windows-31J", "CP932", "csWindows31J"]
def names; []; end
##
# Returns true for dummy encodings.
# A dummy encoding is an encoding for which character handling is not properly
# implemented.
# It is used for stateful encodings.
# 
#   Encoding::ISO_2022_JP.dummy?       #=> true
#   Encoding::UTF_8.dummy?             #=> false
def dummy?; true || false; end
##
# Returns whether ASCII-compatible or not.
# 
#   Encoding::UTF_8.ascii_compatible?     #=> true
#   Encoding::UTF_16BE.ascii_compatible?  #=> false
def ascii_compatible?; true || false; end
##
# Returns a replicated encoding of _enc_ whose name is _name_.
# The new encoding should have the same byte structure of _enc_.
# If _name_ is used by another encoding, raise ArgumentError.
def replicate(name); Encoding.new; end
##
# Returns the list of loaded encodings.
# 
#   Encoding.list
#   #=> [#<Encoding:ASCII-8BIT>, #<Encoding:UTF-8>,
#         #<Encoding:ISO-2022-JP (dummy)>]
# 
#   Encoding.find("US-ASCII")
#   #=> #<Encoding:US-ASCII>
# 
#   Encoding.list
#   #=> [#<Encoding:ASCII-8BIT>, #<Encoding:UTF-8>,
#         #<Encoding:US-ASCII>, #<Encoding:ISO-2022-JP (dummy)>]
def self.list; [Encoding.new]; end
##
# Returns the list of available encoding names.
# 
#   Encoding.name_list
#   #=> ["US-ASCII", "ASCII-8BIT", "UTF-8",
#         "ISO-8859-1", "Shift_JIS", "EUC-JP",
#         "Windows-31J",
#         "BINARY", "CP932", "eucJP"]
def self.name_list; [Encoding.new]; end
##
# Returns the hash of available encoding alias and original encoding name.
# 
#   Encoding.aliases
#   #=> {"BINARY"=>"ASCII-8BIT", "ASCII"=>"US-ASCII", "ANSI_X3.4-1986"=>"US-ASCII",
#         "SJIS"=>"Shift_JIS", "eucJP"=>"EUC-JP", "CP932"=>"Windows-31J"}
def self.aliases(&block); end
##
# Search the encoding with specified <i>name</i>.
# <i>name</i> should be a string or symbol.
# 
#   Encoding.find("US-ASCII")  #=> #<Encoding:US-ASCII>
#   Encoding.find(:Shift_JIS)  #=> #<Encoding:Shift_JIS>
# 
# Names which this method accept are encoding names and aliases
# including following special aliases
# 
# "external"::   default external encoding
# "internal"::   default internal encoding
# "locale"::     locale encoding
# "filesystem":: filesystem encoding
# 
# An ArgumentError is raised when no encoding with <i>name</i>.
# Only <code>Encoding.find("internal")</code> however returns nil
# when no encoding named "internal", in other words, when Ruby has no
# default internal encoding.
def self.find(string); Encoding.new; end
##
# Checks the compatibility of two objects.
# 
# If the objects are both strings they are compatible when they are
# concatenatable.  The encoding of the concatenated string will be returned
# if they are compatible, nil if they are not.
# 
#   Encoding.compatible?("\xa1".force_encoding("iso-8859-1"), "b")
#   #=> #<Encoding:ISO-8859-1>
# 
#   Encoding.compatible?(
#     "\xa1".force_encoding("iso-8859-1"),
#     "\xa1\xa1".force_encoding("euc-jp"))
#   #=> nil
# 
# If the objects are non-strings their encodings are compatible when they
# have an encoding and:
# * Either encoding is US-ASCII compatible
# * One of the encodings is a 7-bit encoding
def self.compatible?(obj1, obj2); Encoding.new || nil; end
##
# Returns default external encoding.
# 
# The default external encoding is used by default for strings created from
# the following locations:
# 
# * CSV
# * File data read from disk
# * SDBM
# * StringIO
# * Zlib::GzipReader
# * Zlib::GzipWriter
# * String#inspect
# * Regexp#inspect
# 
# While strings created from these locations will have this encoding, the
# encoding may not be valid.  Be sure to check String#valid_encoding?.
# 
# File data written to disk will be transcoded to the default external
# encoding when written.
# 
# The default external encoding is initialized by the locale or -E option.
def self.default_external; Encoding.new; end
##
# Sets default external encoding.  You should not set
# Encoding::default_external in ruby code as strings created before changing
# the value may have a different encoding from strings created after the value
# was changed., instead you should use <tt>ruby -E</tt> to invoke ruby with
# the correct default_external.
# 
# See Encoding::default_external for information on how the default external
# encoding is used.
def self.default_external= enc; end
##
# Returns default internal encoding.  Strings will be transcoded to the
# default internal encoding in the following places if the default internal
# encoding is not nil:
# 
# * CSV
# * Etc.sysconfdir and Etc.systmpdir
# * File data read from disk
# * File names from Dir
# * Integer#chr
# * String#inspect and Regexp#inspect
# * Strings returned from Curses
# * Strings returned from Readline
# * Strings returned from SDBM
# * Time#zone
# * Values from ENV
# * Values in ARGV including $PROGRAM_NAME
# * __FILE__
# 
# Additionally String#encode and String#encode! use the default internal
# encoding if no encoding is given.
# 
# The locale encoding (__ENCODING__), not default_internal, is used as the
# encoding of created strings.
# 
# Encoding::default_internal is initialized by the source file's
# internal_encoding or -E option.
def self.default_internal; Encoding.new; end
##
# Sets default internal encoding or removes default internal encoding when
# passed nil.  You should not set Encoding::default_internal in ruby code as
# strings created before changing the value may have a different encoding
# from strings created after the change.  Instead you should use
# <tt>ruby -E</tt> to invoke ruby with the correct default_internal.
# 
# See Encoding::default_internal for information on how the default internal
# encoding is used.
def self.default_internal= enc_or_nil; end
##
# Returns the locale charmap name.
# It returns nil if no appropriate information.
# 
#   Debian GNU/Linux
#     LANG=C
#       Encoding.locale_charmap  #=> "ANSI_X3.4-1968"
#     LANG=ja_JP.EUC-JP
#       Encoding.locale_charmap  #=> "EUC-JP"
# 
#   SunOS 5
#     LANG=C
#       Encoding.locale_charmap  #=> "646"
#     LANG=ja
#       Encoding.locale_charmap  #=> "eucJP"
# 
# The result is highly platform dependent.
# So Encoding.find(Encoding.locale_charmap) may cause an error.
# If you need some encoding object even for unknown locale,
# Encoding.find("locale") can be used.
def self.locale_charmap; ''; end
end

class Class < Module
##
# Callback invoked whenever a subclass of the current class is created.
# 
# Example:
# 
#    class Foo
#      def self.inherited(subclass)
#        puts "New subclass: #{subclass}"
#      end
#    end
# 
#    class Bar < Foo
#    end
# 
#    class Baz < Bar
#    end
# 
# produces:
# 
#    New subclass: Bar
#    New subclass: Baz
def inherited(subklass); end
##
# Allocates space for a new object of <i>class</i>'s class and does not
# call initialize on the new instance. The returned object must be an
# instance of <i>class</i>.
# 
#     klass = Class.new do
#       def initialize(*args)
#         @initialized = true
#       end
# 
#       def initialized?
#         @initialized || false
#       end
#     end
# 
#     klass.allocate.initialized? #=> false
def allocate(); Object.new; end
##
# Calls <code>allocate</code> to create a new object of
# <i>class</i>'s class, then invokes that object's
# <code>initialize</code> method, passing it <i>args</i>.
# This is the method that ends up getting called whenever
# an object is constructed using .new.
def new(super_klass=Object, &block); Class.new; end
##
# Returns the superclass of <i>class</i>, or <code>nil</code>.
# 
#    File.superclass          #=> IO
#    IO.superclass            #=> Object
#    Object.superclass        #=> BasicObject
#    class Foo; end
#    class Bar < Foo; end
#    Bar.superclass           #=> Foo
# 
# returns nil when the given class hasn't a parent class:
# 
#    BasicObject.superclass   #=> nil
def superclass; Class.new || nil; end
end

##
# Descendants of class Exception are used to communicate between
# Kernel#raise and +rescue+ statements in <code>begin ... end</code> blocks.
# Exception objects carry information about the exception -- its type (the
# exception's class name), an optional descriptive string, and optional
# traceback information.  Exception subclasses may add additional
# information like NameError#name.
# 
# Programs may make subclasses of Exception, typically of StandardError or
# RuntimeError, to provide custom classes and add additional information.
# See the subclass list below for defaults for +raise+ and +rescue+.
# 
# When an exception has been raised but not yet handled (in +rescue+,
# +ensure+, +at_exit+ and +END+ blocks) the global variable <code>$!</code>
# will contain the current exception and <code>$@</code> contains the
# current exception's backtrace.
# 
# It is recommended that a library should have one subclass of StandardError
# or RuntimeError and have specific exception types inherit from it.  This
# allows the user to rescue a generic exception type to catch all exceptions
# the library may raise even if future versions of the library add new
# exception subclasses.
# 
# For example:
# 
#   class MyLibrary
#     class Error < RuntimeError
#     end
# 
#     class WidgetError < Error
#     end
# 
#     class FrobError < Error
#     end
# 
#   end
# 
# To handle both WidgetError and FrobError the library user can rescue
# MyLibrary::Error.
# 
# The built-in subclasses of Exception are:
# 
# * NoMemoryError
# * ScriptError
#   * LoadError
#   * NotImplementedError
#   * SyntaxError
# * SignalException
#   * Interrupt
# * StandardError -- default for +rescue+
#   * ArgumentError
#   * IndexError
#     * StopIteration
#   * IOError
#     * EOFError
#   * LocalJumpError
#   * NameError
#     * NoMethodError
#   * RangeError
#     * FloatDomainError
#   * RegexpError
#   * RuntimeError -- default for +raise+
#   * SecurityError
#   * SystemCallError
#     * Errno::*
#   * SystemStackError
#   * ThreadError
#   * TypeError
#   * ZeroDivisionError
# * SystemExit
# * fatal -- impossible to rescue
class Exception < Object
##
# With no argument, or if the argument is the same as the receiver,
# return the receiver. Otherwise, create a new
# exception object of the same class as the receiver, but with a
# message equal to <code>string.to_str</code>.
def self.exception(string); Exception.new; end
##
# Construct a new Exception object, optionally passing in
# a message.
def self.new(msg = null); end
##
# Equality---If <i>obj</i> is not an <code>Exception</code>, returns
# <code>false</code>. Otherwise, returns <code>true</code> if <i>exc</i> and
# <i>obj</i> share same class, messages, and backtrace.
def ==; true || false; end
##
# Returns exception's message (or the name of the exception if
# no message is set).
def to_s; ''; end
##
# Returns the result of invoking <code>exception.to_s</code>.
# Normally this returns the exception's message or name. By
# supplying a to_str method, exceptions are agreeing to
# be used where Strings are expected.
def message; ''; end
##
# Return this exception's class name and message
def inspect; ''; end
##
# Returns any backtrace associated with the exception. The backtrace
# is an array of strings, each containing either ``filename:lineNo: in
# `method''' or ``filename:lineNo.''
# 
#    def a
#      raise "boom"
#    end
# 
#    def b
#      a()
#    end
# 
#    begin
#      b()
#    rescue => detail
#      print detail.backtrace.join("\n")
#    end
# 
# <em>produces:</em>
# 
#    prog.rb:2:in `a'
#    prog.rb:6:in `b'
#    prog.rb:10
def backtrace; []; end
##
# Sets the backtrace information associated with +exc+. The +backtrace+ must
# be an array of String objects or a single String in the format described
# in Exception#backtrace.
def set_backtrace(backtrace); []; end
end

##
# Raised by +exit+ to initiate the termination of the script.
class SystemExit < Exception
##
# Create a new +SystemExit+ exception with the given status and message.
# Status is true, false, or an integer.
# If status is not given, true is used.
def self.new; end
##
# Return the status value associated with this system exit.
def status; 0; end
##
# Returns +true+ if exiting successful, +false+ if not.
def success?; true || false; end
end

##
# fatal is an Exception that is raised when ruby has encountered a fatal
# error and must exit.  You are not able to rescue fatal.
class Fatal < Exception
end

##
# Raised when a signal is received.
# 
#    begin
#      Process.kill('HUP',Process.pid)
#      sleep # wait for receiver to handle signal sent by Process.kill
#    rescue SignalException => e
#      puts "received Exception #{e}"
#    end
# 
# <em>produces:</em>
# 
#    received Exception SIGHUP
class SignalException < Exception
##
# Construct a new SignalException object.  +sig_name+ should be a known
# signal name.
def self.new(sig_name); end
##
# Returns a signal number.
def signo; 0; end
end

##
# Raised with the interrupt signal is received, typically because the
# user pressed on Control-C (on most posix platforms). As such, it is a
# subclass of +SignalException+.
# 
#    begin
#      puts "Press ctrl-C when you get bored"
#      loop {}
#    rescue Interrupt => e
#      puts "Note: You will typically use Signal.trap instead."
#    end
# 
# <em>produces:</em>
# 
#    Press ctrl-C when you get bored
# 
# <em>then waits until it is interrupted with Control-C and then prints:</em>
# 
#    Note: You will typically use Signal.trap instead.
class Interrupt < SignalException
end

##
# The most standard error types are subclasses of StandardError. A
# rescue clause without an explicit Exception class will rescue all
# StandardErrors (and only those).
# 
#    def foo
#      raise "Oups"
#    end
#    foo rescue "Hello"   #=> "Hello"
# 
# On the other hand:
# 
#    require 'does/not/exist' rescue "Hi"
# 
# <em>raises the exception:</em>
# 
#    LoadError: no such file to load -- does/not/exist
class StandardError < Exception
end

##
# Raised when encountering an object that is not of the expected type.
# 
#    [1, 2, 3].first("two")
# 
# <em>raises the exception:</em>
# 
#    TypeError: no implicit conversion of String into Integer
class TypeError < StandardError
end

##
# Raised when the arguments are wrong and there isn't a more specific
# Exception class.
# 
# Ex: passing the wrong number of arguments
# 
#    [1, 2, 3].first(4, 5)
# 
# <em>raises the exception:</em>
# 
#    ArgumentError: wrong number of arguments (2 for 1)
# 
# Ex: passing an argument that is not acceptable:
# 
#    [1, 2, 3].first(-4)
# 
# <em>raises the exception:</em>
# 
#    ArgumentError: negative array size
class ArgumentError < StandardError
end

##
# Raised when the given index is invalid.
# 
#    a = [:foo, :bar]
#    a.fetch(0)   #=> :foo
#    a[4]         #=> nil
#    a.fetch(4)   #=> IndexError: index 4 outside of array bounds: -2...2
class IndexError < StandardError
end

##
# Raised when the specified key is not found. It is a subclass of
# IndexError.
# 
#    h = {"foo" => :bar}
#    h.fetch("foo") #=> :bar
#    h.fetch("baz") #=> KeyError: key not found: "baz"
class KeyError < IndexError
end

##
# Raised when a given numerical value is out of range.
# 
#    [1, 2, 3].drop(1 << 100)
# 
# <em>raises the exception:</em>
# 
#    RangeError: bignum too big to convert into `long'
class RangeError < StandardError
end

##
# ScriptError is the superclass for errors raised when a script
# can not be executed because of a +LoadError+,
# +NotImplementedError+ or a +SyntaxError+. Note these type of
# +ScriptErrors+ are not +StandardError+ and will not be
# rescued unless it is specified explicitly (or its ancestor
# +Exception+).
class ScriptError < Exception
end

##
# Raised when encountering Ruby code with an invalid syntax.
# 
#    eval("1+1=2")
# 
# <em>raises the exception:</em>
# 
#    SyntaxError: (eval):1: syntax error, unexpected '=', expecting $end
class SyntaxError < ScriptError
end

##
# Raised when a file required (a Ruby script, extension library, ...)
# fails to load.
# 
#    require 'this/file/does/not/exist'
# 
# <em>raises the exception:</em>
# 
#    LoadError: no such file to load -- this/file/does/not/exist
class LoadError < ScriptError
end

##
# Raised when a feature is not implemented on the current platform. For
# example, methods depending on the +fsync+ or +fork+ system calls may
# raise this exception if the underlying operating system or Ruby
# runtime does not support them.
# 
# Note that if +fork+ raises a +NotImplementedError+, then
# <code>respond_to?(:fork)</code> returns +false+.
class NotImplementedError < ScriptError
end

##
# Raised when a given name is invalid or undefined.
# 
#    puts foo
# 
# <em>raises the exception:</em>
# 
#    NameError: undefined local variable or method `foo' for main:Object
# 
# Since constant names must start with a capital:
# 
#    Fixnum.const_set :answer, 42
# 
# <em>raises the exception:</em>
# 
#    NameError: wrong constant name answer
class NameError < StandardError
class Message < Data
end

##
# Construct a new NameError exception. If given the <i>name</i>
# parameter may subsequently be examined using the <code>NameError.name</code>
# method.
def self.new(msg , name=0); end
##
# Return the name associated with this NameError exception.
def name; '' || nil; end
##
# Produce a nicely-formatted string representing the +NameError+.
def to_s; ''; end
end

##
# Raised when a method is called on a receiver which doesn't have it
# defined and also fails to respond with +method_missing+.
# 
#    "hello".to_ary
# 
# <em>raises the exception:</em>
# 
#    NoMethodError: undefined method `to_ary' for "hello":String
class NoMethodError < NameError
##
# Construct a NoMethodError exception for a method of the given name
# called with the given arguments. The name may be accessed using
# the <code>#name</code> method on the resulting object, and the
# arguments using the <code>#args</code> method.
def self.new(msg, name , args=0); end
##
# Return the arguments passed in as the third parameter to
# the constructor.
def args; Object.new; end
end

##
# A generic error class raised when an invalid operation is attempted.
# 
#    [1, 2, 3].freeze << 4
# 
# <em>raises the exception:</em>
# 
#    RuntimeError: can't modify frozen array
# 
# Kernel.raise will raise a RuntimeError if no Exception class is
# specified.
# 
#    raise "ouch"
# 
# <em>raises the exception:</em>
# 
#    RuntimeError: ouch
class RuntimeError < StandardError
end

##
# Raised when attempting a potential unsafe operation, typically when
# the $SAFE level is raised above 0.
# 
#    foo = "bar"
#    proc = Proc.new do
#      $SAFE = 4
#      foo.gsub! "a", "*"
#    end
#    proc.call
# 
# <em>raises the exception:</em>
# 
#    SecurityError: Insecure: can't modify string
class SecurityError < Exception
end

##
# Raised when memory allocation fails.
class NoMemoryError < Exception
end

##
# EncodingError is the base class for encoding errors.
class EncodingError < StandardError
end

##
# SystemCallError is the base class for all low-level
# platform-dependent errors.
# 
# The errors available on the current platform are subclasses of
# SystemCallError and are defined in the Errno module.
# 
#    File.open("does/not/exist")
# 
# <em>raises the exception:</em>
# 
#    Errno::ENOENT: No such file or directory - does/not/exist
class SystemCallError < StandardError
##
# If _errno_ corresponds to a known system error code, constructs
# the appropriate <code>Errno</code> class for that error, otherwise
# constructs a generic <code>SystemCallError</code> object. The
# error number is subsequently available via the <code>errno</code>
# method.
def self.new(msg, errno); end
##
# Return this SystemCallError's error number.
def errno; 0; end
##
# Return +true+ if the receiver is a generic +SystemCallError+, or
# if the error numbers +self+ and _other_ are the same.
def self.===; true || false; end
end

class Range < Object
include Enumerable
##
# Constructs a range using the given +begin+ and +end+. If the +exclude_end+
# parameter is omitted or is <code>false</code>, the +rng+ will include
# the end object; otherwise, it will be excluded.
def self.new(_begin, _end, exclude__end=false); end
##
# Returns <code>true</code> only if +obj+ is a Range, has equivalent
# begin and end items (by comparing them with <code>==</code>), and has
# the same #exclude_end? setting as the range.
# 
#   (0..2) == (0..2)            #=> true
#   (0..2) == Range.new(0,2)    #=> true
#   (0..2) == (0...2)           #=> false
def ==; true || false; end
##
# Returns <code>true</code> if +obj+ is an element of the range,
# <code>false</code> otherwise.  Conveniently, <code>===</code> is the
# comparison operator used by <code>case</code> statements.
# 
#    case 79
#    when 1..50   then   print "low\n"
#    when 51..75  then   print "medium\n"
#    when 76..100 then   print "high\n"
#    end
# 
# <em>produces:</em>
# 
#    high
def ===; true || false; end
##
# Returns <code>true</code> only if +obj+ is a Range, has equivalent
# begin and end items (by comparing them with <code>eql?</code>),
# and has the same #exclude_end? setting as the range.
# 
#   (0..2).eql?(0..2)            #=> true
#   (0..2).eql?(Range.new(0,2))  #=> true
#   (0..2).eql?(0...2)           #=> false
def eql?(obj); true || false; end
##
# Compute a hash-code for this range. Two ranges with equal
# begin and end points (using <code>eql?</code>), and the same
# #exclude_end? value will generate the same hash-code.
def hash; 0; end
##
# Iterates over the elements of range, passing each in turn to the
# block.
# 
# The +each+ method can only be used if the begin object of the range
# supports the +succ+ method.  A TypeError is raised if the object
# does not have +succ+ method defined (like Float).
# 
# If no block is given, an enumerator is returned instead.
# 
#    (10..15).each {|n| print n, ' ' }
#    # prints: 10 11 12 13 14 15
# 
#    (2.5..5).each {|n| print n, ' ' }
#    # raises: TypeError: can't iterate from Float
def each(&block); Enumerator.new; end
##
# Iterates over the range, passing each <code>n</code>th element to the block.
# If begin and end are numeric, +n+ is added for each iteration.
# Otherwise <code>step</code> invokes <code>succ</code> to iterate through
# range elements.
# 
# If no block is given, an enumerator is returned instead.
# 
#   range = Xs.new(1)..Xs.new(10)
#   range.step(2) {|x| puts x}
#   puts
#   range.step(3) {|x| puts x}
# 
# <em>produces:</em>
# 
#    1 x
#    3 xxx
#    5 xxxxx
#    7 xxxxxxx
#    9 xxxxxxxxx
# 
#    1 x
#    4 xxxx
#    7 xxxxxxx
#   10 xxxxxxxxxx
# 
# See Range for the definition of class Xs.
def step(n=1, &block); Enumerator.new; end
##
# By using binary search, finds a value in range which meets the given
# condition in O(log n) where n is the size of the array.
# 
# You can use this method in two use cases: a find-minimum mode and
# a find-any mode.  In either case, the elements of the array must be
# monotone (or sorted) with respect to the block.
# 
# In find-minimum mode (this is a good choice for typical use case),
# the block must return true or false, and there must be a value x
# so that:
# 
# - the block returns false for any value which is less than x, and
# - the block returns true for any value which is greater than or
#   equal to i.
# 
# If x is within the range, this method returns the value x.
# Otherwise, it returns nil.
# 
#    ary = [0, 4, 7, 10, 12]
#    (0...ary.size).bsearch {|i| ary[i] >= 4 } #=> 1
#    (0...ary.size).bsearch {|i| ary[i] >= 6 } #=> 2
#    (0...ary.size).bsearch {|i| ary[i] >= 8 } #=> 3
#    (0...ary.size).bsearch {|i| ary[i] >= 100 } #=> nil
# 
#    (0.0...Float::INFINITY).bsearch {|x| Math.log(x) >= 0 } #=> 1.0
# 
# In find-any mode (this behaves like libc's bsearch(3)), the block
# must return a number, and there must be two values x and y (x <= y)
# so that:
# 
# - the block returns a positive number for v if v < x,
# - the block returns zero for v if x <= v < y, and
# - the block returns a negative number for v if y <= v.
# 
# This method returns any value which is within the intersection of
# the given range and x...y (if any).  If there is no value that
# satisfies the condition, it returns nil.
# 
#    ary = [0, 100, 100, 100, 200]
#    (0..4).bsearch {|i| 100 - ary[i] } #=> 1, 2 or 3
#    (0..4).bsearch {|i| 300 - ary[i] } #=> nil
#    (0..4).bsearch {|i|  50 - ary[i] } #=> nil
# 
# You must not mix the two modes at a time; the block must always
# return either true/false, or always return a number.  It is
# undefined which value is actually picked up at each iteration.
def bsearch(&block); Object.new; end
##
# Returns the object that defines the beginning of the range.
# 
#     (1..10).begin   #=> 1
def begin; Object.new; end
##
# Returns the object that defines the end of the range.
# 
#    (1..10).end    #=> 10
#    (1...10).end   #=> 10
def end; Object.new; end
##
# Returns the first object in the range, or an array of the first +n+
# elements.
# 
#   (10..20).first     #=> 10
#   (10..20).first(3)  #=> [10, 11, 12]
def first; []; end
##
# Returns the last object in the range,
# or an array of the last +n+ elements.
# 
# Note that with no arguments +last+ will return the object that defines
# the end of the range even if #exclude_end? is +true+.
# 
#   (10..20).last      #=> 20
#   (10...20).last     #=> 20
#   (10..20).last(3)   #=> [18, 19, 20]
#   (10...20).last(3)  #=> [17, 18, 19]
def last; []; end
##
# Returns the minimum value in the range. Returns +nil+ if the begin
# value of the range is larger than the end value.
# 
# Can be given an optional block to override the default comparison
# method <code>a <=> b</code>.
# 
#   (10..20).min    #=> 10
def min; Object.new; end
##
# Returns the maximum value in the range. Returns +nil+ if the begin
# value of the range larger than the end value.
# 
# Can be given an optional block to override the default comparison
# method <code>a <=> b</code>.
# 
#   (10..20).max    #=> 20
def max; Object.new; end
##
# Returns the number of elements in the range.
# 
#   (10..20).size    #=> 11
def size; 0; end
##
# Convert this range object to a printable form (using #to_s to convert the
# begin and end objects).
def to_s; ''; end
##
# Convert this range object to a printable form (using
# <code>inspect</code> to convert the begin and end
# objects).
def inspect; ''; end
##
# Returns <code>true</code> if the range excludes its end value.
# 
#    (1..5).exclude_end?     #=> false
#    (1...5).exclude_end?    #=> true
def exclude_end?; true || false; end
##
# Returns <code>true</code> if +obj+ is an element of
# the range, <code>false</code> otherwise.  If begin and end are
# numeric, comparison is done according to the magnitude of the values.
# 
#    ("a".."z").include?("g")   #=> true
#    ("a".."z").include?("A")   #=> false
#    ("a".."z").include?("cc")  #=> false
def member?(obj); true || false; end
##
# Returns <code>true</code> if +obj+ is an element of
# the range, <code>false</code> otherwise.  If begin and end are
# numeric, comparison is done according to the magnitude of the values.
# 
#    ("a".."z").include?("g")   #=> true
#    ("a".."z").include?("A")   #=> false
#    ("a".."z").include?("cc")  #=> false
def include?(obj); true || false; end
##
# Returns <code>true</code> if +obj+ is between the begin and end of
# the range.
# 
# This tests <code>begin <= obj <= end</code> when #exclude_end? is +false+
# and <code>begin <= obj < end</code> when #exclude_end? is +true+.
# 
#    ("a".."z").cover?("c")    #=> true
#    ("a".."z").cover?("5")    #=> false
#    ("a".."z").cover?("cc")   #=> true
def cover?(obj); true || false; end
end

##
# Raised when attempting to divide an integer by 0.
# 
#    42 / 0
# 
# <em>raises the exception:</em>
# 
#    ZeroDivisionError: divided by 0
# 
# Note that only division by an exact 0 will raise that exception:
# 
#    42 /  0.0 #=> Float::INFINITY
#    42 / -0.0 #=> -Float::INFINITY
#    0  /  0.0 #=> NaN
class ZeroDivisionError < StandardError
end

##
# Raised when attempting to convert special float values
# (in particular infinite or NaN)
# to numerical classes which don't support them.
# 
#    Float::INFINITY.to_r
# 
# <em>raises the exception:</em>
# 
#    FloatDomainError: Infinity
class FloatDomainError < RangeError
end

##
# A <code>Fixnum</code> holds <code>Integer</code> values that can be
# represented in a native machine word (minus 1 bit). If any operation
# on a <code>Fixnum</code> exceeds this range, the value is
# automatically converted to a <code>Bignum</code>.
# 
# <code>Fixnum</code> objects have immediate value. This means that
# when they are assigned or passed as parameters, the actual object is
# passed, rather than a reference to that object. Assignment does not
# alias <code>Fixnum</code> objects. There is effectively only one
# <code>Fixnum</code> object instance for any given integer value, so,
# for example, you cannot add a singleton method to a
# <code>Fixnum</code>.
class Fixnum < Integer
##
# Returns a string containing the representation of <i>fix</i> radix
# <i>base</i> (between 2 and 36).
# 
#    12345.to_s       #=> "12345"
#    12345.to_s(2)    #=> "11000000111001"
#    12345.to_s(8)    #=> "30071"
#    12345.to_s(10)   #=> "12345"
#    12345.to_s(16)   #=> "3039"
#    12345.to_s(36)   #=> "9ix"
def to_s(base=10); ''; end
##
# Negates <code>fix</code> (which might return a Bignum).
def -@; 0; end
##
# Performs addition: the class of the resulting object depends on
# the class of <code>numeric</code> and on the magnitude of the
# result.
def +; 0; end
##
# Performs subtraction: the class of the resulting object depends on
# the class of <code>numeric</code> and on the magnitude of the
# result.
def -; 0; end
##
# Performs multiplication: the class of the resulting object depends on
# the class of <code>numeric</code> and on the magnitude of the
# result.
def *; 0; end
##
# Performs division: the class of the resulting object depends on
# the class of <code>numeric</code> and on the magnitude of the
# result.
def /; 0; end
##
# Performs integer division: returns integer value.
def div(numeric); 0; end
##
# Returns <code>fix</code> modulo <code>other</code>.
# See <code>numeric.divmod</code> for more information.
def %; 0; end
##
# Returns <code>fix</code> modulo <code>other</code>.
# See <code>numeric.divmod</code> for more information.
def modulo(other); 0; end
##
# See <code>Numeric#divmod</code>.
def divmod(numeric); []; end
##
# Returns the floating point result of dividing <i>fix</i> by
# <i>numeric</i>.
# 
#    654321.fdiv(13731)      #=> 47.6528293642124
#    654321.fdiv(13731.24)   #=> 47.6519964693647
def fdiv(numeric); 0.0; end
##
# Raises <code>fix</code> to the <code>numeric</code> power, which may
# be negative or fractional.
# 
#   2 ** 3      #=> 8
#   2 ** -1     #=> (1/2)
#   2 ** 0.5    #=> 1.4142135623731
def **; 0; end
##
# Returns the absolute value of <i>fix</i>.
# 
#    -12345.abs   #=> 12345
#    12345.abs    #=> 12345
def abs; 0; end
##
# Returns the absolute value of <i>fix</i>.
# 
#    -12345.abs   #=> 12345
#    12345.abs    #=> 12345
def magnitude; 0; end
##
# Return <code>true</code> if <code>fix</code> equals <code>other</code>
# numerically.
# 
#   1 == 2      #=> false
#   1 == 1.0    #=> true
def ==; true || false; end
##
# Return <code>true</code> if <code>fix</code> equals <code>other</code>
# numerically.
# 
#   1 == 2      #=> false
#   1 == 1.0    #=> true
def ===; true || false; end
##
# Comparison---Returns -1, 0, +1 or nil depending on whether +fix+ is less
# than, equal to, or greater than +numeric+. This is the basis for the tests
# in  Comparable.
# 
# +nil+ is returned if the two values are incomparable.
def <=>; 1 || nil; end
##
# Returns <code>true</code> if the value of <code>fix</code> is
# greater than that of <code>real</code>.
def >; true || false; end
##
# Returns <code>true</code> if the value of <code>fix</code> is
# greater than or equal to that of <code>real</code>.
def >=; true || false; end
##
# Returns <code>true</code> if the value of <code>fix</code> is
# less than that of <code>real</code>.
def <; true || false; end
##
# Returns <code>true</code> if the value of <code>fix</code> is
# less than or equal to that of <code>real</code>.
def <=; true || false; end
##
# One's complement: returns a number where each bit is flipped.
def ~; 0; end
##
# Bitwise AND.
def &; 0; end
##
# Bitwise OR.
def |; 0; end
##
# Bitwise EXCLUSIVE OR.
def ^; 0; end
##
# Bit Reference---Returns the <em>n</em>th bit in the binary
# representation of <i>fix</i>, where <i>fix</i>[0] is the least
# significant bit.
# 
#    a = 0b11001100101010
#    30.downto(0) do |n| print a[n] end
# 
# <em>produces:</em>
# 
#    0000000000000000011001100101010
def []; 0; end
##
# Shifts _fix_ left _count_ positions (right if _count_ is negative).
def <<; 0; end
##
# Shifts _fix_ right _count_ positions (left if _count_ is negative).
def >>; 0; end
##
# Converts <i>fix</i> to a <code>Float</code>.
def to_f; 0.0; end
##
# Returns the number of <em>bytes</em> in the machine representation
# of a <code>Fixnum</code>.
# 
#    1.size            #=> 4
#    -1.size           #=> 4
#    2147483647.size   #=> 4
def size; 0; end
##
# Returns <code>true</code> if <i>fix</i> is zero.
def zero?; true || false; end
##
# Returns <code>true</code> if <i>fix</i> is an odd number.
def odd?; true || false; end
##
# Returns <code>true</code> if <i>fix</i> is an even number.
def even?; true || false; end
##
# Returns the <code>Integer</code> equal to <i>int</i> + 1.
# 
#    1.next      #=> 2
#    (-1).next   #=> 0
def next; 0; end
##
# Returns the <code>Integer</code> equal to <i>int</i> + 1.
# 
#    1.next      #=> 2
#    (-1).next   #=> 0
def succ; 0; end
end

##
# A Hash is a dictionary-like collection of unique keys and their values.
# Also called associative arrays, they are similar to Arrays, but where an
# Array uses integers as its index, a Hash allows you to use any object
# type.
# 
# Hashes enumerate their values in the order that the corresponding keys
# were inserted.
# 
# A Hash can be easily created by using its implicit form:
# 
#   grades = { "Jane Doe" => 10, "Jim Doe" => 6 }
# 
# Hashes allow an alternate syntax form when your keys are always symbols.
# Instead of
# 
#   options = { :font_size => 10, :font_family => "Arial" }
# 
# You could write it as:
# 
#   options = { font_size: 10, font_family: "Arial" }
# 
# Each named key is a symbol you can access in hash:
# 
#   options[:font_size]  # => 10
# 
# A Hash can also be created through its ::new method:
# 
#   grades = Hash.new
#   grades["Dorothy Doe"] = 9
# 
# Hashes have a <em>default value</em> that is returned when accessing
# keys that do not exist in the hash. If no default is set +nil+ is used.
# You can set the default value by sending it as an argument to Hash.new:
# 
#   grades = Hash.new(0)
# 
# Or by using the #default= method:
# 
#   grades = {"Timmy Doe" => 8}
#   grades.default = 0
# 
# Accessing a value in a Hash requires using its key:
# 
#   puts grades["Jane Doe"] # => 10
# 
# === Common Uses
# 
# Hashes are an easy way to represent data structures, such as
# 
#   books         = {}
#   books[:matz]  = "The Ruby Language"
#   books[:black] = "The Well-Grounded Rubyist"
# 
# Hashes are also commonly used as a way to have named parameters in
# functions. Note that no brackets are used below. If a hash is the last
# argument on a method call, no braces are needed, thus creating a really
# clean interface:
# 
#   Person.create(name: "John Doe", age: 27)
# 
#   def self.create(params)
#     @name = params[:name]
#     @age  = params[:age]
#   end
# 
# === Hash Keys
# 
# Two objects refer to the same hash key when their <code>hash</code> value
# is identical and the two objects are <code>eql?</code> to each other.
# 
# A user-defined class may be used as a hash key if the <code>hash</code>
# and <code>eql?</code> methods are overridden to provide meaningful
# behavior.  By default, separate instances refer to separate hash keys.
# 
# A typical implementation of <code>hash</code> is based on the
# object's data while <code>eql?</code> is usually aliased to the overridden
# <code>==</code> method:
# 
#   class Book
#     attr_reader :author, :title
# 
#     def initialize(author, title)
#       @author = author
#       @title = title
#     end
# 
#     def ==(other)
#       self.class === other and
#         other.author == @author and
#         other.title == @title
#     end
# 
#     alias eql? ==
# 
#     def hash
#       @author.hash ^ @title.hash # XOR
#     end
#   end
# 
#   book1 = Book.new 'matz', 'Ruby in a Nutshell'
#   book2 = Book.new 'matz', 'Ruby in a Nutshell'
# 
#   reviews = {}
# 
#   reviews[book1] = 'Great reference!'
#   reviews[book2] = 'Nice and compact!'
# 
#   reviews.length #=> 1
# 
# See also Object#hash and Object#eql?
class Hash < Object
include Enumerable
##
# Creates a new hash populated with the given objects. Equivalent to
# the literal <code>{ <i>key</i> => <i>value</i>, ... }</code>. In the first
# form, keys and values occur in pairs, so there must be an even number of arguments.
# The second and third form take a single argument which is either
# an array of key-value pairs or an object convertible to a hash.
# 
#    Hash["a", 100, "b", 200]             #=> {"a"=>100, "b"=>200}
#    Hash[ [ ["a", 100], ["b", 200] ] ]   #=> {"a"=>100, "b"=>200}
#    Hash["a" => 100, "b" => 200]         #=> {"a"=>100, "b"=>200}
def self.[]; Object.new; end
##
# Try to convert <i>obj</i> into a hash, using to_hash method.
# Returns converted hash or nil if <i>obj</i> cannot be converted
# for any reason.
# 
#    Hash.try_convert({1=>2})   # => {1=>2}
#    Hash.try_convert("1=>2")   # => nil
def self.try_convert(obj); {} || nil; end
##
# Returns a new, empty hash. If this hash is subsequently accessed by
# a key that doesn't correspond to a hash entry, the value returned
# depends on the style of <code>new</code> used to create the hash. In
# the first form, the access returns <code>nil</code>. If
# <i>obj</i> is specified, this single object will be used for
# all <em>default values</em>. If a block is specified, it will be
# called with the hash object and the key, and should return the
# default value. It is the block's responsibility to store the value
# in the hash if required.
# 
#    h = Hash.new("Go Fish")
#    h["a"] = 100
#    h["b"] = 200
#    h["a"]           #=> 100
#    h["c"]           #=> "Go Fish"
#    # The following alters the single default object
#    h["c"].upcase!   #=> "GO FISH"
#    h["d"]           #=> "GO FISH"
#    h.keys           #=> ["a", "b"]
# 
#    # While this creates a new default object each time
#    h = Hash.new { |hash, key| hash[key] = "Go Fish: #{key}" }
#    h["c"]           #=> "Go Fish: c"
#    h["c"].upcase!   #=> "GO FISH: C"
#    h["d"]           #=> "Go Fish: d"
#    h.keys           #=> ["c", "d"]
def self.new; end
##
# Rebuilds the hash based on the current hash values for each key. If
# values of key objects have changed since they were inserted, this
# method will reindex <i>hsh</i>. If <code>Hash#rehash</code> is
# called while an iterator is traversing the hash, an
# <code>RuntimeError</code> will be raised in the iterator.
# 
#    a = [ "a", "b" ]
#    c = [ "c", "d" ]
#    h = { a => 100, c => 300 }
#    h[a]       #=> 100
#    a[0] = "z"
#    h[a]       #=> nil
#    h.rehash   #=> {["z", "b"]=>100, ["c", "d"]=>300}
#    h[a]       #=> 100
def rehash; {}; end
##
# Returns +self+.
def to_hash; {}; end
##
# Returns +self+. If called on a subclass of Hash, converts
# the receiver to a Hash object.
def to_h; {}; end
##
# Converts <i>hsh</i> to a nested array of <code>[</code> <i>key,
# value</i> <code>]</code> arrays.
# 
#    h = { "c" => 300, "a" => 100, "d" => 400, "c" => 300  }
#    h.to_a   #=> [["c", 300], ["a", 100], ["d", 400]]
def to_a; []; end
##
# Return the contents of this hash as a string.
# 
#     h = { "c" => 300, "a" => 100, "d" => 400, "c" => 300  }
#     h.to_s   #=> "{\"c\"=>300, \"a\"=>100, \"d\"=>400}"
def to_s; ''; end
##
# Return the contents of this hash as a string.
# 
#     h = { "c" => 300, "a" => 100, "d" => 400, "c" => 300  }
#     h.to_s   #=> "{\"c\"=>300, \"a\"=>100, \"d\"=>400}"
def inspect; ''; end
##
# Equality---Two hashes are equal if they each contain the same number
# of keys and if each key-value pair is equal to (according to
# <code>Object#==</code>) the corresponding elements in the other
# hash.
# 
#    h1 = { "a" => 1, "c" => 2 }
#    h2 = { 7 => 35, "c" => 2, "a" => 1 }
#    h3 = { "a" => 1, "c" => 2, 7 => 35 }
#    h4 = { "a" => 1, "d" => 2, "f" => 35 }
#    h1 == h2   #=> false
#    h2 == h3   #=> true
#    h3 == h4   #=> false
def ==; true || false; end
##
# Compute a hash-code for this hash. Two hashes with the same content
# will have the same hash code (and will compare using <code>eql?</code>).
def hash; 0; end
##
# Returns <code>true</code> if <i>hash</i> and <i>other</i> are
# both hashes with the same content.
def eql?(other); true || false; end
##
# Returns a value from the hash for the given key. If the key can't be
# found, there are several options: With no other arguments, it will
# raise an <code>KeyError</code> exception; if <i>default</i> is
# given, then that will be returned; if the optional code block is
# specified, then that will be run and its result returned.
# 
#    h = { "a" => 100, "b" => 200 }
#    h.fetch("a")                            #=> 100
#    h.fetch("z", "go fish")                 #=> "go fish"
#    h.fetch("z") { |el| "go fish, #{el}"}   #=> "go fish, z"
# 
# The following example shows that an exception is raised if the key
# is not found and a default value is not supplied.
# 
#    h = { "a" => 100, "b" => 200 }
#    h.fetch("z")
# 
# <em>produces:</em>
# 
#    prog.rb:2:in `fetch': key not found (KeyError)
#     from prog.rb:2
def fetch(key  , default=0); Object.new; end
##
# Element Assignment---Associates the value given by
# <i>value</i> with the key given by <i>key</i>.
# <i>key</i> should not have its value changed while it is in
# use as a key (a <code>String</code> passed as a key will be
# duplicated and frozen).
# 
#    h = { "a" => 100, "b" => 200 }
#    h["a"] = 9
#    h["c"] = 4
#    h   #=> {"a"=>9, "b"=>200, "c"=>4}
def []=; Object.new; end
##
# Element Assignment---Associates the value given by
# <i>value</i> with the key given by <i>key</i>.
# <i>key</i> should not have its value changed while it is in
# use as a key (a <code>String</code> passed as a key will be
# duplicated and frozen).
# 
#    h = { "a" => 100, "b" => 200 }
#    h["a"] = 9
#    h["c"] = 4
#    h   #=> {"a"=>9, "b"=>200, "c"=>4}
def store(key, value); Object.new; end
##
# Returns the default value, the value that would be returned by
# <i>hsh</i>[<i>key</i>] if <i>key</i> did not exist in <i>hsh</i>.
# See also <code>Hash::new</code> and <code>Hash#default=</code>.
# 
#    h = Hash.new                            #=> {}
#    h.default                               #=> nil
#    h.default(2)                            #=> nil
# 
#    h = Hash.new("cat")                     #=> {}
#    h.default                               #=> "cat"
#    h.default(2)                            #=> "cat"
# 
#    h = Hash.new {|h,k| h[k] = k.to_i*10}   #=> {}
#    h.default                               #=> nil
#    h.default(2)                            #=> 20
def default(key=null); Object.new; end
##
# Sets the default value, the value returned for a key that does not
# exist in the hash. It is not possible to set the default to a
# <code>Proc</code> that will be executed on each key lookup.
# 
#    h = { "a" => 100, "b" => 200 }
#    h.default = "Go fish"
#    h["a"]     #=> 100
#    h["z"]     #=> "Go fish"
#    # This doesn't do what you might hope...
#    h.default = proc do |hash, key|
#      hash[key] = key + key
#    end
#    h[2]       #=> #<Proc:0x401b3948@-:6>
#    h["cat"]   #=> #<Proc:0x401b3948@-:6>
def default= obj; Object.new; end
##
# If <code>Hash::new</code> was invoked with a block, return that
# block, otherwise return <code>nil</code>.
# 
#    h = Hash.new {|h,k| h[k] = k*k }   #=> {}
#    p = h.default_proc                 #=> #<Proc:0x401b3d08@-:1>
#    a = []                             #=> []
#    p.call(a, 2)
#    a                                  #=> [nil, nil, 4]
def default_proc; Object.new; end
##
# Sets the default proc to be executed on each failed key lookup.
# 
#    h.default_proc = proc do |hash, key|
#      hash[key] = key + key
#    end
#    h[2]       #=> 4
#    h["cat"]   #=> "catcat"
def default_proc= proc_or_nil; end
##
# Returns the key of an occurrence of a given value. If the value is
# not found, returns <code>nil</code>.
# 
#    h = { "a" => 100, "b" => 200, "c" => 300, "d" => 300 }
#    h.key(200)   #=> "b"
#    h.key(300)   #=> "c"
#    h.key(999)   #=> nil
def key(value); Object.new; end
##
# Returns the number of key-value pairs in the hash.
# 
#    h = { "d" => 100, "a" => 200, "v" => 300, "e" => 400 }
#    h.length        #=> 4
#    h.delete("a")   #=> 200
#    h.length        #=> 3
def length; 0; end
##
# Returns the number of key-value pairs in the hash.
# 
#    h = { "d" => 100, "a" => 200, "v" => 300, "e" => 400 }
#    h.length        #=> 4
#    h.delete("a")   #=> 200
#    h.length        #=> 3
def size; 0; end
##
# Returns <code>true</code> if <i>hsh</i> contains no key-value pairs.
# 
#    {}.empty?   #=> true
def empty?; true || false; end
##
# Calls <i>block</i> once for each key in <i>hsh</i>, passing the
# value as a parameter.
# 
# If no block is given, an enumerator is returned instead.
# 
#    h = { "a" => 100, "b" => 200 }
#    h.each_value {|value| puts value }
# 
# <em>produces:</em>
# 
#    100
#    200
def each_value(&block); Enumerator.new; end
##
# Calls <i>block</i> once for each key in <i>hsh</i>, passing the key
# as a parameter.
# 
# If no block is given, an enumerator is returned instead.
# 
#    h = { "a" => 100, "b" => 200 }
#    h.each_key {|key| puts key }
# 
# <em>produces:</em>
# 
#    a
#    b
def each_key(&block); Enumerator.new; end
##
# Calls <i>block</i> once for each key in <i>hsh</i>, passing the key-value
# pair as parameters.
# 
# If no block is given, an enumerator is returned instead.
# 
#    h = { "a" => 100, "b" => 200 }
#    h.each {|key, value| puts "#{key} is #{value}" }
# 
# <em>produces:</em>
# 
#    a is 100
#    b is 200
def each(&block); Enumerator.new; end
##
# Calls <i>block</i> once for each key in <i>hsh</i>, passing the key-value
# pair as parameters.
# 
# If no block is given, an enumerator is returned instead.
# 
#    h = { "a" => 100, "b" => 200 }
#    h.each {|key, value| puts "#{key} is #{value}" }
# 
# <em>produces:</em>
# 
#    a is 100
#    b is 200
def each_pair(&block); Enumerator.new; end
##
# Returns a new array populated with the keys from this hash. See also
# <code>Hash#values</code>.
# 
#    h = { "a" => 100, "b" => 200, "c" => 300, "d" => 400 }
#    h.keys   #=> ["a", "b", "c", "d"]
def keys; []; end
##
# Returns a new array populated with the values from <i>hsh</i>. See
# also <code>Hash#keys</code>.
# 
#    h = { "a" => 100, "b" => 200, "c" => 300 }
#    h.values   #=> [100, 200, 300]
def values; []; end
##
# Return an array containing the values associated with the given keys.
# Also see <code>Hash.select</code>.
# 
#   h = { "cat" => "feline", "dog" => "canine", "cow" => "bovine" }
#   h.values_at("cow", "cat")  #=> ["bovine", "feline"]
def values_at(); []; end
##
# Removes a key-value pair from <i>hsh</i> and returns it as the
# two-item array <code>[</code> <i>key, value</i> <code>]</code>, or
# the hash's default value if the hash is empty.
# 
#    h = { 1 => "a", 2 => "b", 3 => "c" }
#    h.shift   #=> [1, "a"]
#    h         #=> {2=>"b", 3=>"c"}
def shift; [] || Object.new; end
##
# Deletes the key-value pair and returns the value from <i>hsh</i> whose
# key is equal to <i>key</i>. If the key is not found, returns the
# <em>default value</em>. If the optional code block is given and the
# key is not found, pass in the key and return the result of
# <i>block</i>.
# 
#    h = { "a" => 100, "b" => 200 }
#    h.delete("a")                              #=> 100
#    h.delete("z")                              #=> nil
#    h.delete("z") { |el| "#{el} not found" }   #=> "z not found"
def delete(key); Object.new; end
##
# Deletes every key-value pair from <i>hsh</i> for which <i>block</i>
# evaluates to <code>true</code>.
# 
# If no block is given, an enumerator is returned instead.
# 
#    h = { "a" => 100, "b" => 200, "c" => 300 }
#    h.delete_if {|key, value| key >= "b" }   #=> {"a"=>100}
def delete_if(&block); Enumerator.new; end
##
# Deletes every key-value pair from <i>hsh</i> for which <i>block</i>
# evaluates to false.
# 
# If no block is given, an enumerator is returned instead.
def keep_if(&block); Enumerator.new; end
##
# Returns a new hash consisting of entries for which the block returns true.
# 
# If no block is given, an enumerator is returned instead.
# 
#    h = { "a" => 100, "b" => 200, "c" => 300 }
#    h.select {|k,v| k > "a"}  #=> {"b" => 200, "c" => 300}
#    h.select {|k,v| v < 200}  #=> {"a" => 100}
def select(&block); Enumerator.new; end
##
# Equivalent to <code>Hash#keep_if</code>, but returns
# <code>nil</code> if no changes were made.
def select!(&block); Enumerator.new; end
##
# Same as <code>Hash#delete_if</code>, but works on (and returns) a
# copy of the <i>hsh</i>. Equivalent to
# <code><i>hsh</i>.dup.delete_if</code>.
def reject(&block); Enumerator.new; end
##
# Equivalent to <code>Hash#delete_if</code>, but returns
# <code>nil</code> if no changes were made.
def reject!(&block); Enumerator.new; end
##
# Removes all key-value pairs from <i>hsh</i>.
# 
#    h = { "a" => 100, "b" => 200 }   #=> {"a"=>100, "b"=>200}
#    h.clear                          #=> {}
def clear; {}; end
##
# Returns a new hash created by using <i>hsh</i>'s values as keys, and
# the keys as values.
# 
#    h = { "n" => 100, "m" => 100, "y" => 300, "d" => 200, "a" => 0 }
#    h.invert   #=> {0=>"a", 100=>"m", 200=>"d", 300=>"y"}
def invert; {}; end
##
# Adds the contents of _other_hash_ to _hsh_.  If no block is specified,
# entries with duplicate keys are overwritten with the values from
# _other_hash_, otherwise the value of each duplicate key is determined by
# calling the block with the key, its value in _hsh_ and its value in
# _other_hash_.
# 
#    h1 = { "a" => 100, "b" => 200 }
#    h2 = { "b" => 254, "c" => 300 }
#    h1.merge!(h2)   #=> {"a"=>100, "b"=>254, "c"=>300}
# 
#    h1 = { "a" => 100, "b" => 200 }
#    h2 = { "b" => 254, "c" => 300 }
#    h1.merge!(h2) { |key, v1, v2| v1 }
#                    #=> {"a"=>100, "b"=>200, "c"=>300}
def merge!(other_hash); {}; end
##
# Adds the contents of _other_hash_ to _hsh_.  If no block is specified,
# entries with duplicate keys are overwritten with the values from
# _other_hash_, otherwise the value of each duplicate key is determined by
# calling the block with the key, its value in _hsh_ and its value in
# _other_hash_.
# 
#    h1 = { "a" => 100, "b" => 200 }
#    h2 = { "b" => 254, "c" => 300 }
#    h1.merge!(h2)   #=> {"a"=>100, "b"=>254, "c"=>300}
# 
#    h1 = { "a" => 100, "b" => 200 }
#    h2 = { "b" => 254, "c" => 300 }
#    h1.merge!(h2) { |key, v1, v2| v1 }
#                    #=> {"a"=>100, "b"=>200, "c"=>300}
def update(other_hash); {}; end
##
# Replaces the contents of <i>hsh</i> with the contents of
# <i>other_hash</i>.
# 
#    h = { "a" => 100, "b" => 200 }
#    h.replace({ "c" => 300, "d" => 400 })   #=> {"c"=>300, "d"=>400}
def replace(other_hash); {}; end
##
# Returns a new hash containing the contents of <i>other_hash</i> and
# the contents of <i>hsh</i>. If no block is specified, the value for
# entries with duplicate keys will be that of <i>other_hash</i>. Otherwise
# the value for each duplicate key is determined by calling the block
# with the key, its value in <i>hsh</i> and its value in <i>other_hash</i>.
# 
#    h1 = { "a" => 100, "b" => 200 }
#    h2 = { "b" => 254, "c" => 300 }
#    h1.merge(h2)   #=> {"a"=>100, "b"=>254, "c"=>300}
#    h1.merge(h2){|key, oldval, newval| newval - oldval}
#                   #=> {"a"=>100, "b"=>54,  "c"=>300}
#    h1             #=> {"a"=>100, "b"=>200}
def merge(other_hash); {}; end
##
# Searches through the hash comparing _obj_ with the key using <code>==</code>.
# Returns the key-value pair (two elements array) or +nil+
# if no match is found.  See <code>Array#assoc</code>.
# 
#    h = {"colors"  => ["red", "blue", "green"],
#         "letters" => ["a", "b", "c" ]}
#    h.assoc("letters")  #=> ["letters", ["a", "b", "c"]]
#    h.assoc("foo")      #=> nil
def assoc(obj); [] || nil; end
##
# Searches through the hash comparing _obj_ with the value using <code>==</code>.
# Returns the first key-value pair (two-element array) that matches. See
# also <code>Array#rassoc</code>.
# 
#    a = {1=> "one", 2 => "two", 3 => "three", "ii" => "two"}
#    a.rassoc("two")    #=> [2, "two"]
#    a.rassoc("four")   #=> nil
def rassoc(obj); [] || nil; end
##
# Returns a new array that is a one-dimensional flattening of this
# hash. That is, for every key or value that is an array, extract
# its elements into the new array.  Unlike Array#flatten, this
# method does not flatten recursively by default.  The optional
# <i>level</i> argument determines the level of recursion to flatten.
# 
#    a =  {1=> "one", 2 => [2,"two"], 3 => "three"}
#    a.flatten    # => [1, "one", 2, [2, "two"], 3, "three"]
#    a.flatten(2) # => [1, "one", 2, 2, "two", 3, "three"]
def flatten; []; end
##
# Returns <code>true</code> if the given key is present in <i>hsh</i>.
# 
#    h = { "a" => 100, "b" => 200 }
#    h.has_key?("a")   #=> true
#    h.has_key?("z")   #=> false
def has_key?(key); true || false; end
##
# Returns <code>true</code> if the given key is present in <i>hsh</i>.
# 
#    h = { "a" => 100, "b" => 200 }
#    h.has_key?("a")   #=> true
#    h.has_key?("z")   #=> false
def include?(key); true || false; end
##
# Returns <code>true</code> if the given key is present in <i>hsh</i>.
# 
#    h = { "a" => 100, "b" => 200 }
#    h.has_key?("a")   #=> true
#    h.has_key?("z")   #=> false
def key?(key); true || false; end
##
# Returns <code>true</code> if the given key is present in <i>hsh</i>.
# 
#    h = { "a" => 100, "b" => 200 }
#    h.has_key?("a")   #=> true
#    h.has_key?("z")   #=> false
def member?(key); true || false; end
##
# Returns <code>true</code> if the given value is present for some key
# in <i>hsh</i>.
# 
#    h = { "a" => 100, "b" => 200 }
#    h.has_value?(100)   #=> true
#    h.has_value?(999)   #=> false
def has_value?(value); true || false; end
##
# Returns <code>true</code> if the given value is present for some key
# in <i>hsh</i>.
# 
#    h = { "a" => 100, "b" => 200 }
#    h.has_value?(100)   #=> true
#    h.has_value?(999)   #=> false
def value?(value); true || false; end
##
# Makes <i>hsh</i> compare its keys by their identity, i.e. it
# will consider exact same objects as same keys.
# 
#    h1 = { "a" => 100, "b" => 200, :c => "c" }
#    h1["a"]        #=> 100
#    h1.compare_by_identity
#    h1.compare_by_identity? #=> true
#    h1["a"]        #=> nil  # different objects.
#    h1[:c]         #=> "c"  # same symbols are all same.
def compare_by_identity; {}; end
##
# Returns <code>true</code> if <i>hsh</i> will compare its keys by
# their identity.  Also see <code>Hash#compare_by_identity</code>.
def compare_by_identity?; true || false; end
end

##
# ENV is a hash-like accessor for environment variables.
class ENV < Object
##
# Retrieves the +value+ for environment variable +name+ as a String.  Returns
# +nil+ if the named variable does not exist.
def self.[]; Object.new; end
##
# Retrieves the environment variable +name+.
# 
# If the given name does not exist and neither +default+ nor a block a
# provided an IndexError is raised.  If a block is given it is called with
# the missing name to provide a value.  If a default value is given it will
# be returned when no block is given.
def self.fetch(name); Object.new; end
##
# Sets the environment variable +name+ to +value+.  If the value given is
# +nil+ the environment variable is deleted.
def self.[]=; end
##
# Sets the environment variable +name+ to +value+.  If the value given is
# +nil+ the environment variable is deleted.
def self.store(name, value); Object.new; end
##
# Yields each environment variable +name+ and +value+.
# 
# If no block is given an Enumerator is returned.
def self.each(&block); Enumerator.new; end
##
# Yields each environment variable +name+ and +value+.
# 
# If no block is given an Enumerator is returned.
def self.each_pair(&block); Enumerator.new; end
##
# Yields each environment variable name.
# 
# An Enumerator is returned if no block is given.
def self.each_key(&block); Enumerator.new; end
##
# Yields each environment variable +value+.
# 
# An Enumerator is returned if no block was given.
def self.each_value(&block); Enumerator.new; end
##
# Deletes the environment variable with +name+ and returns the value of the
# variable.  If a block is given it will be called when the named environment
# does not exist.
def self.delete(name); Object.new; end
##
# Deletes every environment variable for which the block evaluates to +true+.
# 
# If no block is given an enumerator is returned instead.
def self.delete_if(&block); Enumerator.new; end
##
# Deletes every environment variable where the block evaluates to +false+.
# 
# Returns an enumerator if no block was given.
def self.keep_if(&block); Enumerator.new; end
##
# Removes every environment variable.
def self.clear; end
##
# Same as ENV#delete_if, but works on (and returns) a copy of the
# environment.
def self.reject(&block); Enumerator.new; end
##
# Equivalent to ENV#delete_if but returns +nil+ if no changes were made.
# 
# Returns an Enumerator if no block was given.
def self.reject!(&block); Enumerator.new; end
##
# Returns a copy of the environment for entries where the block returns true.
# 
# Returns an Enumerator if no block was given.
def self.select(&block); Enumerator.new; end
##
# Equivalent to ENV#keep_if but returns +nil+ if no changes were made.
def self.select!(&block); Enumerator.new; end
##
# Removes an environment variable name-value pair from ENV and returns it as
# an Array.  Returns +nil+ if when the environment is empty.
def self.shift; [] || nil; end
##
# Returns a new hash created by using environment variable names as values
# and values as names.
def self.invert; {}; end
##
# Replaces the contents of the environment variables with the contents of
# +hash+.
def self.replace(hash); ENV; end
##
# Adds the contents of +hash+ to the environment variables.  If no block is
# specified entries with duplicate keys are overwritten, otherwise the value
# of each duplicate name is determined by calling the block with the key, its
# value from the environment and its value from the hash.
def self.update(hash); {}; end
##
# Returns the contents of the environment as a String.
def self.inspect; ''; end
##
# Re-hashing the environment variables does nothing.  It is provided for
# compatibility with Hash.
def self.rehash; end
##
# Converts the environment variables into an array of names and value arrays.
# 
#   ENV.to_a # => [["TERM" => "xterm-color"], ["SHELL" => "/bin/bash"], ...]
def self.to_a; []; end
##
# Returns "ENV"
def self.to_s; ENV; end
##
# Returns the name of the environment variable with +value+.  If the value is
# not found +nil+ is returned.
def self.key(value); ''; end
##
# Deprecated method that is equivalent to ENV.key
def self.index(value); Object.new; end
##
# Returns the number of environment variables.
def self.length; end
##
# Returns the number of environment variables.
def self.size; end
##
# Returns true when there are no environment variables
def self.empty?; true || false; end
##
# Returns every environment variable name in an Array
def self.keys; []; end
##
# Returns every environment variable value as an Array
def self.values; []; end
##
# Returns an array containing the environment variable values associated with
# the given names.  See also ENV.select.
def self.values_at(); []; end
##
# Returns +true+ if there is an environment variable with the given +name+.
def self.key?(name); true || false; end
##
# Returns +true+ if there is an environment variable with the given +name+.
def self.include?(name); true || false; end
##
# Returns +true+ if there is an environment variable with the given +name+.
def self.has_key?(name); true || false; end
##
# Returns +true+ if there is an environment variable with the given +name+.
def self.member?(name); true || false; end
##
# Returns +true+ if there is an environment variable with the given +value+.
def self.value?(value); true || false; end
##
# Returns +true+ if there is an environment variable with the given +value+.
def self.has_value?(value); true || false; end
##
# Creates a hash with a copy of the environment variables.
def self.to_hash; {}; end
##
# Creates a hash with a copy of the environment variables.
def self.to_h; {}; end
##
# Returns an Array of the name and value of the environment variable with
# +name+ or +nil+ if the name cannot be found.
def self.assoc(name); [] || nil; end
##
# Returns an Array of the name and value of the environment variable with
# +value+ or +nil+ if the value cannot be found.
def self.rassoc(value); end
end

##
# Objects of class <code>Dir</code> are directory streams representing
# directories in the underlying file system. They provide a variety of
# ways to list directories and their contents. See also
# <code>File</code>.
# 
# The directory used in these examples contains the two regular files
# (<code>config.h</code> and <code>main.rb</code>), the parent
# directory (<code>..</code>), and the directory itself
# (<code>.</code>).
class Dir < Object
include Enumerable
##
# With no block, <code>open</code> is a synonym for
# <code>Dir::new</code>. If a block is present, it is passed
# <i>aDir</i> as a parameter. The directory is closed at the end of
# the block, and <code>Dir::open</code> returns the value of the
# block.
def self.open( string ); Object.new; end
##
# Calls the block once for each entry in the named directory, passing
# the filename of each entry as a parameter to the block.
# 
# If no block is given, an enumerator is returned instead.
# 
#    Dir.foreach("testdir") {|x| puts "Got #{x}" }
# 
# <em>produces:</em>
# 
#    Got .
#    Got ..
#    Got config.h
#    Got main.rb
def self.foreach( dirname , &block); Enumerator.new; end
##
# Returns an array containing all of the filenames in the given
# directory. Will raise a <code>SystemCallError</code> if the named
# directory doesn't exist.
# 
#    Dir.entries("testdir")   #=> [".", "..", "config.h", "main.rb"]
def self.entries( dirname ); []; end
##
# Returns a new directory object for the named directory.
def self.new( string ); end
##
# Returns the path parameter passed to <em>dir</em>'s constructor.
# 
#    d = Dir.new("..")
#    d.path   #=> ".."
def path; '' || nil; end
##
# Return a string describing this Dir object.
def inspect; ''; end
##
# Reads the next entry from <em>dir</em> and returns it as a string.
# Returns <code>nil</code> at the end of the stream.
# 
#    d = Dir.new("testdir")
#    d.read   #=> "."
#    d.read   #=> ".."
#    d.read   #=> "config.h"
def read; '' || nil; end
##
# Calls the block once for each entry in this directory, passing the
# filename of each entry as a parameter to the block.
# 
# If no block is given, an enumerator is returned instead.
# 
#    d = Dir.new("testdir")
#    d.each  {|x| puts "Got #{x}" }
# 
# <em>produces:</em>
# 
#    Got .
#    Got ..
#    Got config.h
#    Got main.rb
def each(&block); Enumerator.new; end
##
# Repositions <em>dir</em> to the first entry.
# 
#    d = Dir.new("testdir")
#    d.read     #=> "."
#    d.rewind   #=> #<Dir:0x401b3fb0>
#    d.read     #=> "."
def rewind; Dir.new; end
##
# Returns the current position in <em>dir</em>. See also
# <code>Dir#seek</code>.
# 
#    d = Dir.new("testdir")
#    d.tell   #=> 0
#    d.read   #=> "."
#    d.tell   #=> 12
def pos; 0; end
##
# Returns the current position in <em>dir</em>. See also
# <code>Dir#seek</code>.
# 
#    d = Dir.new("testdir")
#    d.tell   #=> 0
#    d.read   #=> "."
#    d.tell   #=> 12
def tell; 0; end
##
# Seeks to a particular location in <em>dir</em>. <i>integer</i>
# must be a value returned by <code>Dir#tell</code>.
# 
#    d = Dir.new("testdir")   #=> #<Dir:0x401b3c40>
#    d.read                   #=> "."
#    i = d.tell               #=> 12
#    d.read                   #=> ".."
#    d.seek(i)                #=> #<Dir:0x401b3c40>
#    d.read                   #=> ".."
def seek( integer ); Dir.new; end
##
# Closes the directory stream. Any further attempts to access
# <em>dir</em> will raise an <code>IOError</code>.
# 
#    d = Dir.new("testdir")
#    d.close   #=> nil
def close; end
##
# Changes the current working directory of the process to the given
# string. When called without an argument, changes the directory to
# the value of the environment variable <code>HOME</code>, or
# <code>LOGDIR</code>. <code>SystemCallError</code> (probably
# <code>Errno::ENOENT</code>) if the target directory does not exist.
# 
# If a block is given, it is passed the name of the new current
# directory, and the block is executed with that as the current
# directory. The original working directory is restored when the block
# exits. The return value of <code>chdir</code> is the value of the
# block. <code>chdir</code> blocks can be nested, but in a
# multi-threaded program an error will be raised if a thread attempts
# to open a <code>chdir</code> block while another thread has one
# open.
# 
#    Dir.chdir("/var/spool/mail")
#    puts Dir.pwd
#    Dir.chdir("/tmp") do
#      puts Dir.pwd
#      Dir.chdir("/usr") do
#        puts Dir.pwd
#      end
#      puts Dir.pwd
#    end
#    puts Dir.pwd
# 
# <em>produces:</em>
# 
#    /var/spool/mail
#    /tmp
#    /usr
#    /tmp
#    /var/spool/mail
def self.chdir(string=0); Object.new; end
##
# Returns the path to the current working directory of this process as
# a string.
# 
#    Dir.chdir("/tmp")   #=> 0
#    Dir.getwd           #=> "/tmp"
def self.getwd; ''; end
##
# Returns the path to the current working directory of this process as
# a string.
# 
#    Dir.chdir("/tmp")   #=> 0
#    Dir.getwd           #=> "/tmp"
def self.pwd; ''; end
##
# Changes this process's idea of the file system root. Only a
# privileged process may make this call. Not available on all
# platforms. On Unix systems, see <code>chroot(2)</code> for more
# information.
def self.chroot( string ); 0; end
##
# Makes a new directory named by <i>string</i>, with permissions
# specified by the optional parameter <i>anInteger</i>. The
# permissions may be modified by the value of
# <code>File::umask</code>, and are ignored on NT. Raises a
# <code>SystemCallError</code> if the directory cannot be created. See
# also the discussion of permissions in the class documentation for
# <code>File</code>.
# 
#   Dir.mkdir(File.join(Dir.home, ".foo"), 0700) #=> 0
def self.mkdir( string  , integer=0); 0; end
##
# Deletes the named directory. Raises a subclass of
# <code>SystemCallError</code> if the directory isn't empty.
def self.delete( string ); 0; end
##
# Deletes the named directory. Raises a subclass of
# <code>SystemCallError</code> if the directory isn't empty.
def self.rmdir( string ); 0; end
##
# Deletes the named directory. Raises a subclass of
# <code>SystemCallError</code> if the directory isn't empty.
def self.unlink( string ); 0; end
##
# Returns the home directory of the current user or the named user
# if given.
def self.home(); ''; end
##
# Returns the filenames found by expanding <i>pattern</i> which is
# an +Array+ of the patterns or the pattern +String+, either as an
# <i>array</i> or as parameters to the block. Note that this pattern
# is not a regexp (it's closer to a shell glob). See
# <code>File::fnmatch</code> for the meaning of the <i>flags</i>
# parameter. Note that case sensitivity depends on your system (so
# <code>File::FNM_CASEFOLD</code> is ignored), as does the order
# in which the results are returned.
# 
# <code>*</code>::        Matches any file. Can be restricted by
#                         other values in the glob. <code>*</code>
#                         will match all files; <code>c*</code> will
#                         match all files beginning with
#                         <code>c</code>; <code>*c</code> will match
#                         all files ending with <code>c</code>; and
#                         <code>\*c\*</code> will match all files that
#                         have <code>c</code> in them (including at
#                         the beginning or end). Equivalent to
#                         <code>/ .* /x</code> in regexp. Note, this
#                         will not match Unix-like hidden files (dotfiles).
#                         In order to include those in the match results,
#                         you must use something like <code>"{*,.*}"</code>.
# <code>**</code>::       Matches directories recursively.
# <code>?</code>::        Matches any one character. Equivalent to
#                         <code>/.{1}/</code> in regexp.
# <code>[set]</code>::    Matches any one character in +set+.
#                         Behaves exactly like character sets in
#                         Regexp, including set negation
#                         (<code>[^a-z]</code>).
# <code>{p,q}</code>::    Matches either literal <code>p</code> or
#                         literal <code>q</code>. Matching literals
#                         may be more than one character in length.
#                         More than two literals may be specified.
#                         Equivalent to pattern alternation in
#                         regexp.
# <code> \\ </code>::     Escapes the next metacharacter.
#                         Note that this means you cannot use backslash
#                         in windows as part of a glob,
#                         i.e. <code>Dir["c:\\foo*"]</code> will not work,
#                         use <code>Dir["c:/foo*"]</code> instead.
# 
#    Dir["config.?"]                     #=> ["config.h"]
#    Dir.glob("config.?")                #=> ["config.h"]
#    Dir.glob("*.[a-z][a-z]")            #=> ["main.rb"]
#    Dir.glob("*.[^r]*")                 #=> ["config.h"]
#    Dir.glob("*.{rb,h}")                #=> ["main.rb", "config.h"]
#    Dir.glob("*")                       #=> ["config.h", "main.rb"]
#    Dir.glob("*", File::FNM_DOTMATCH)   #=> [".", "..", "config.h", "main.rb"]
# 
#    rbfiles = File.join("**", "*.rb")
#    Dir.glob(rbfiles)                   #=> ["main.rb",
#                                        #    "lib/song.rb",
#                                        #    "lib/song/karaoke.rb"]
#    libdirs = File.join("**", "lib")
#    Dir.glob(libdirs)                   #=> ["lib"]
# 
#    librbfiles = File.join("**", "lib", "**", "*.rb")
#    Dir.glob(librbfiles)                #=> ["lib/song.rb",
#                                        #    "lib/song/karaoke.rb"]
# 
#    librbfiles = File.join("**", "lib", "*.rb")
#    Dir.glob(librbfiles)                #=> ["lib/song.rb"]
def self.glob( pattern, flags=0); end
##
# Equivalent to calling
# <code>Dir.glob(</code><i>array,</i><code>0)</code> and
# <code>Dir.glob([</code><i>string,...</i><code>],0)</code>.
def self.[]; []; end
##
# Returns <code>true</code> if the named file is a directory,
# <code>false</code> otherwise.
def self.exist?(file_name); true || false; end
##
# Returns <code>true</code> if the named file is a directory,
# <code>false</code> otherwise.
def self.exists?(file_name); true || false; end
end

class File < Object
##
# Objects of class <code>File::Stat</code> encapsulate common status
# information for <code>File</code> objects. The information is
# recorded at the moment the <code>File::Stat</code> object is
# created; changes made to the file after that point will not be
# reflected. <code>File::Stat</code> objects are returned by
# <code>IO#stat</code>, <code>File::stat</code>,
# <code>File#lstat</code>, and <code>File::lstat</code>. Many of these
# methods return platform-specific values, and not all values are
# meaningful on all systems. See also <code>Kernel#test</code>.
class Stat < Object
include Comparable
##
# Create a File::Stat object for the given file name (raising an
# exception if the file doesn't exist).
def self.new(file_name); end
##
# Compares File::Stat objects by comparing their respective modification
# times.
# 
# +nil+ is returned if the two values are incomparable.
# 
#    f1 = File.new("f1", "w")
#    sleep 1
#    f2 = File.new("f2", "w")
#    f1.stat <=> f2.stat   #=> -1
def <=>; 1 || nil; end
##
# Returns an integer representing the device on which <i>stat</i>
# resides.
# 
#    File.stat("testfile").dev   #=> 774
def dev; 0; end
##
# Returns the major part of <code>File_Stat#dev</code> or
# <code>nil</code>.
# 
#    File.stat("/dev/fd1").dev_major   #=> 2
#    File.stat("/dev/tty").dev_major   #=> 5
def dev_major; 0; end
##
# Returns the minor part of <code>File_Stat#dev</code> or
# <code>nil</code>.
# 
#    File.stat("/dev/fd1").dev_minor   #=> 1
#    File.stat("/dev/tty").dev_minor   #=> 0
def dev_minor; 0; end
##
# Returns the inode number for <i>stat</i>.
# 
#    File.stat("testfile").ino   #=> 1083669
def ino; 0; end
##
# Returns an integer representing the permission bits of
# <i>stat</i>. The meaning of the bits is platform dependent; on
# Unix systems, see <code>stat(2)</code>.
# 
#    File.chmod(0644, "testfile")   #=> 1
#    s = File.stat("testfile")
#    sprintf("%o", s.mode)          #=> "100644"
def mode; 0; end
##
# Returns the number of hard links to <i>stat</i>.
# 
#    File.stat("testfile").nlink             #=> 1
#    File.link("testfile", "testfile.bak")   #=> 0
#    File.stat("testfile").nlink             #=> 2
def nlink; 0; end
##
# Returns the numeric user id of the owner of <i>stat</i>.
# 
#    File.stat("testfile").uid   #=> 501
def uid; 0; end
##
# Returns the numeric group id of the owner of <i>stat</i>.
# 
#    File.stat("testfile").gid   #=> 500
def gid; 0; end
##
# Returns an integer representing the device type on which
# <i>stat</i> resides. Returns <code>nil</code> if the operating
# system doesn't support this feature.
# 
#    File.stat("/dev/fd1").rdev   #=> 513
#    File.stat("/dev/tty").rdev   #=> 1280
def rdev; 1 || nil; end
##
# Returns the major part of <code>File_Stat#rdev</code> or
# <code>nil</code>.
# 
#    File.stat("/dev/fd1").rdev_major   #=> 2
#    File.stat("/dev/tty").rdev_major   #=> 5
def rdev_major; 0; end
##
# Returns the minor part of <code>File_Stat#rdev</code> or
# <code>nil</code>.
# 
#    File.stat("/dev/fd1").rdev_minor   #=> 1
#    File.stat("/dev/tty").rdev_minor   #=> 0
def rdev_minor; 0; end
##
# Returns the size of <i>stat</i> in bytes.
# 
#    File.stat("testfile").size   #=> 66
def size; 0; end
##
# Returns the native file system's block size. Will return <code>nil</code>
# on platforms that don't support this information.
# 
#    File.stat("testfile").blksize   #=> 4096
def blksize; 1 || nil; end
##
# Returns the number of native file system blocks allocated for this
# file, or <code>nil</code> if the operating system doesn't
# support this feature.
# 
#    File.stat("testfile").blocks   #=> 2
def blocks; 1 || nil; end
##
# Returns the last access time for this file as an object of class
# <code>Time</code>.
# 
#    File.stat("testfile").atime   #=> Wed Dec 31 18:00:00 CST 1969
def atime; Time.new; end
##
# Returns the modification time of <i>stat</i>.
# 
#    File.stat("testfile").mtime   #=> Wed Apr 09 08:53:14 CDT 2003
def mtime; Time.new; end
##
# Returns the change time for <i>stat</i> (that is, the time
# directory information about the file was changed, not the file
# itself).
# 
# Note that on Windows (NTFS), returns creation time (birth time).
# 
#    File.stat("testfile").ctime   #=> Wed Apr 09 08:53:14 CDT 2003
def ctime; Time.new; end
##
# Produce a nicely formatted description of <i>stat</i>.
# 
#   File.stat("/etc/passwd").inspect
#      #=> "#<File::Stat dev=0xe000005, ino=1078078, mode=0100644,
#      #    nlink=1, uid=0, gid=0, rdev=0x0, size=1374, blksize=4096,
#      #    blocks=8, atime=Wed Dec 10 10:16:12 CST 2003,
#      #    mtime=Fri Sep 12 15:41:41 CDT 2003,
#      #    ctime=Mon Oct 27 11:20:27 CST 2003>"
def inspect; ''; end
##
# Identifies the type of <i>stat</i>. The return string is one of:
# ``<code>file</code>'', ``<code>directory</code>'',
# ``<code>characterSpecial</code>'', ``<code>blockSpecial</code>'',
# ``<code>fifo</code>'', ``<code>link</code>'',
# ``<code>socket</code>'', or ``<code>unknown</code>''.
# 
#    File.stat("/dev/tty").ftype   #=> "characterSpecial"
def ftype; ''; end
##
# Returns <code>true</code> if the named file is a directory,
# or a symlink that points at a directory, and <code>false</code>
# otherwise.
# 
#    File.directory?(".")
def directory?(file_name); true || false; end
##
# Returns <code>true</code> if <i>stat</i> is readable by the
# effective user id of this process.
# 
#    File.stat("testfile").readable?   #=> true
def readable?; true || false; end
##
# Returns <code>true</code> if <i>stat</i> is readable by the real
# user id of this process.
# 
#    File.stat("testfile").readable_real?   #=> true
def readable_real?; true || false; end
##
# If <i>stat</i> is readable by others, returns an integer
# representing the file permission bits of <i>stat</i>. Returns
# <code>nil</code> otherwise. The meaning of the bits is platform
# dependent; on Unix systems, see <code>stat(2)</code>.
# 
#    m = File.stat("/etc/passwd").world_readable?  #=> 420
#    sprintf("%o", m)                              #=> "644"
def world_readable?; 1 || nil; end
##
# Returns <code>true</code> if <i>stat</i> is writable by the
# effective user id of this process.
# 
#    File.stat("testfile").writable?   #=> true
def writable?; true || false; end
##
# Returns <code>true</code> if <i>stat</i> is writable by the real
# user id of this process.
# 
#    File.stat("testfile").writable_real?   #=> true
def writable_real?; true || false; end
##
# If <i>stat</i> is writable by others, returns an integer
# representing the file permission bits of <i>stat</i>. Returns
# <code>nil</code> otherwise. The meaning of the bits is platform
# dependent; on Unix systems, see <code>stat(2)</code>.
# 
#    m = File.stat("/tmp").world_writable?         #=> 511
#    sprintf("%o", m)                              #=> "777"
def world_writable?; 1 || nil; end
##
# Returns <code>true</code> if <i>stat</i> is executable or if the
# operating system doesn't distinguish executable files from
# nonexecutable files. The tests are made using the effective owner of
# the process.
# 
#    File.stat("testfile").executable?   #=> false
def executable?; true || false; end
##
# Same as <code>executable?</code>, but tests using the real owner of
# the process.
def executable_real?; true || false; end
##
# Returns <code>true</code> if <i>stat</i> is a regular file (not
# a device file, pipe, socket, etc.).
# 
#    File.stat("testfile").file?   #=> true
def file?; true || false; end
##
# Returns <code>true</code> if <i>stat</i> is a zero-length file;
# <code>false</code> otherwise.
# 
#    File.stat("testfile").zero?   #=> false
def zero?; true || false; end
##
# Returns <code>true</code> if the effective user id of the process is
# the same as the owner of <i>stat</i>.
# 
#    File.stat("testfile").owned?      #=> true
#    File.stat("/etc/passwd").owned?   #=> false
def owned?; true || false; end
##
# Returns true if the effective group id of the process is the same as
# the group id of <i>stat</i>. On Windows NT, returns <code>false</code>.
# 
#    File.stat("testfile").grpowned?      #=> true
#    File.stat("/etc/passwd").grpowned?   #=> false
def grpowned?; true || false; end
##
# Returns <code>true</code> if the operating system supports pipes and
# <i>stat</i> is a pipe; <code>false</code> otherwise.
def pipe?; true || false; end
##
# Returns <code>true</code> if <i>stat</i> is a symbolic link,
# <code>false</code> if it isn't or if the operating system doesn't
# support this feature. As <code>File::stat</code> automatically
# follows symbolic links, <code>symlink?</code> will always be
# <code>false</code> for an object returned by
# <code>File::stat</code>.
# 
#    File.symlink("testfile", "alink")   #=> 0
#    File.stat("alink").symlink?         #=> false
#    File.lstat("alink").symlink?        #=> true
def symlink?; true || false; end
##
# Returns <code>true</code> if <i>stat</i> is a socket,
# <code>false</code> if it isn't or if the operating system doesn't
# support this feature.
# 
#    File.stat("testfile").socket?   #=> false
def socket?; true || false; end
##
# Returns <code>true</code> if the file is a block device,
# <code>false</code> if it isn't or if the operating system doesn't
# support this feature.
# 
#    File.stat("testfile").blockdev?    #=> false
#    File.stat("/dev/hda1").blockdev?   #=> true
def blockdev?; true || false; end
##
# Returns <code>true</code> if the file is a character device,
# <code>false</code> if it isn't or if the operating system doesn't
# support this feature.
# 
#    File.stat("/dev/tty").chardev?   #=> true
def chardev?; true || false; end
##
# Returns <code>true</code> if <i>stat</i> has the set-user-id
# permission bit set, <code>false</code> if it doesn't or if the
# operating system doesn't support this feature.
# 
#    File.stat("/bin/su").setuid?   #=> true
def setuid?; true || false; end
##
# Returns <code>true</code> if <i>stat</i> has the set-group-id
# permission bit set, <code>false</code> if it doesn't or if the
# operating system doesn't support this feature.
# 
#    File.stat("/usr/sbin/lpc").setgid?   #=> true
def setgid?; true || false; end
##
# Returns <code>true</code> if <i>stat</i> has its sticky bit set,
# <code>false</code> if it doesn't or if the operating system doesn't
# support this feature.
# 
#    File.stat("testfile").sticky?   #=> false
def sticky?; true || false; end
end

##
# Returns true if <i>path</i> matches against <i>pattern</i> The
# pattern is not a regular expression; instead it follows rules
# similar to shell filename globbing. It may contain the following
# metacharacters:
# 
# <code>*</code>::        Matches any file. Can be restricted by
#                         other values in the glob. <code>*</code>
#                         will match all files; <code>c*</code> will
#                         match all files beginning with
#                         <code>c</code>; <code>*c</code> will match
#                         all files ending with <code>c</code>; and
#                         <code>\*c*</code> will match all files that
#                         have <code>c</code> in them (including at
#                         the beginning or end). Equivalent to
#                         <code>/ .* /x</code> in regexp.
# <code>**</code>::       Matches directories recursively or files
#                         expansively.
# <code>?</code>::        Matches any one character. Equivalent to
#                         <code>/.{1}/</code> in regexp.
# <code>[set]</code>::    Matches any one character in +set+.
#                         Behaves exactly like character sets in
#                         Regexp, including set negation
#                         (<code>[^a-z]</code>).
# <code> \ </code>::      Escapes the next metacharacter.
# 
# <i>flags</i> is a bitwise OR of the <code>FNM_xxx</code>
# parameters. The same glob pattern and flags are used by
# <code>Dir::glob</code>.
# 
#    File.fnmatch('cat',       'cat')        #=> true  # match entire string
#    File.fnmatch('cat',       'category')   #=> false # only match partial string
#    File.fnmatch('c{at,ub}s', 'cats')       #=> false # { } isn't supported
# 
#    File.fnmatch('c?t',     'cat')          #=> true  # '?' match only 1 character
#    File.fnmatch('c??t',    'cat')          #=> false # ditto
#    File.fnmatch('c*',      'cats')         #=> true  # '*' match 0 or more characters
#    File.fnmatch('c*t',     'c/a/b/t')      #=> true  # ditto
#    File.fnmatch('ca[a-z]', 'cat')          #=> true  # inclusive bracket expression
#    File.fnmatch('ca[^t]',  'cat')          #=> false # exclusive bracket expression ('^' or '!')
# 
#    File.fnmatch('cat', 'CAT')                     #=> false # case sensitive
#    File.fnmatch('cat', 'CAT', File::FNM_CASEFOLD) #=> true  # case insensitive
# 
#    File.fnmatch('?',   '/', File::FNM_PATHNAME)  #=> false # wildcard doesn't match '/' on FNM_PATHNAME
#    File.fnmatch('*',   '/', File::FNM_PATHNAME)  #=> false # ditto
#    File.fnmatch('[/]', '/', File::FNM_PATHNAME)  #=> false # ditto
# 
#    File.fnmatch('\?',   '?')                       #=> true  # escaped wildcard becomes ordinary
#    File.fnmatch('\a',   'a')                       #=> true  # escaped ordinary remains ordinary
#    File.fnmatch('\a',   '\a', File::FNM_NOESCAPE)  #=> true  # FNM_NOESACPE makes '\' ordinary
#    File.fnmatch('[\?]', '?')                       #=> true  # can escape inside bracket expression
# 
#    File.fnmatch('*',   '.profile')                      #=> false # wildcard doesn't match leading
#    File.fnmatch('*',   '.profile', File::FNM_DOTMATCH)  #=> true  # period by default.
#    File.fnmatch('.*',  '.profile')                      #=> true
# 
#    rbfiles = '**' '/' '*.rb' # you don't have to do like this. just write in single string.
#    File.fnmatch(rbfiles, 'main.rb')                    #=> false
#    File.fnmatch(rbfiles, './main.rb')                  #=> false
#    File.fnmatch(rbfiles, 'lib/song.rb')                #=> true
#    File.fnmatch('**.rb', 'main.rb')                    #=> true
#    File.fnmatch('**.rb', './main.rb')                  #=> false
#    File.fnmatch('**.rb', 'lib/song.rb')                #=> true
#    File.fnmatch('*',           'dave/.profile')                      #=> true
# 
#    pattern = '*' '/' '*'
#    File.fnmatch(pattern, 'dave/.profile', File::FNM_PATHNAME)  #=> false
#    File.fnmatch(pattern, 'dave/.profile', File::FNM_PATHNAME | File::FNM_DOTMATCH) #=> true
# 
#    pattern = '**' '/' 'foo'
#    File.fnmatch(pattern, 'a/b/c/foo', File::FNM_PATHNAME)     #=> true
#    File.fnmatch(pattern, '/a/b/c/foo', File::FNM_PATHNAME)    #=> true
#    File.fnmatch(pattern, 'c:/a/b/c/foo', File::FNM_PATHNAME)  #=> true
#    File.fnmatch(pattern, 'a/.b/c/foo', File::FNM_PATHNAME)    #=> false
#    File.fnmatch(pattern, 'a/.b/c/foo', File::FNM_PATHNAME | File::FNM_DOTMATCH) #=> true
def self.fnmatch( pattern, path, flags=0); true || false; end
##
# Returns true if <i>path</i> matches against <i>pattern</i> The
# pattern is not a regular expression; instead it follows rules
# similar to shell filename globbing. It may contain the following
# metacharacters:
# 
# <code>*</code>::        Matches any file. Can be restricted by
#                         other values in the glob. <code>*</code>
#                         will match all files; <code>c*</code> will
#                         match all files beginning with
#                         <code>c</code>; <code>*c</code> will match
#                         all files ending with <code>c</code>; and
#                         <code>\*c*</code> will match all files that
#                         have <code>c</code> in them (including at
#                         the beginning or end). Equivalent to
#                         <code>/ .* /x</code> in regexp.
# <code>**</code>::       Matches directories recursively or files
#                         expansively.
# <code>?</code>::        Matches any one character. Equivalent to
#                         <code>/.{1}/</code> in regexp.
# <code>[set]</code>::    Matches any one character in +set+.
#                         Behaves exactly like character sets in
#                         Regexp, including set negation
#                         (<code>[^a-z]</code>).
# <code> \ </code>::      Escapes the next metacharacter.
# 
# <i>flags</i> is a bitwise OR of the <code>FNM_xxx</code>
# parameters. The same glob pattern and flags are used by
# <code>Dir::glob</code>.
# 
#    File.fnmatch('cat',       'cat')        #=> true  # match entire string
#    File.fnmatch('cat',       'category')   #=> false # only match partial string
#    File.fnmatch('c{at,ub}s', 'cats')       #=> false # { } isn't supported
# 
#    File.fnmatch('c?t',     'cat')          #=> true  # '?' match only 1 character
#    File.fnmatch('c??t',    'cat')          #=> false # ditto
#    File.fnmatch('c*',      'cats')         #=> true  # '*' match 0 or more characters
#    File.fnmatch('c*t',     'c/a/b/t')      #=> true  # ditto
#    File.fnmatch('ca[a-z]', 'cat')          #=> true  # inclusive bracket expression
#    File.fnmatch('ca[^t]',  'cat')          #=> false # exclusive bracket expression ('^' or '!')
# 
#    File.fnmatch('cat', 'CAT')                     #=> false # case sensitive
#    File.fnmatch('cat', 'CAT', File::FNM_CASEFOLD) #=> true  # case insensitive
# 
#    File.fnmatch('?',   '/', File::FNM_PATHNAME)  #=> false # wildcard doesn't match '/' on FNM_PATHNAME
#    File.fnmatch('*',   '/', File::FNM_PATHNAME)  #=> false # ditto
#    File.fnmatch('[/]', '/', File::FNM_PATHNAME)  #=> false # ditto
# 
#    File.fnmatch('\?',   '?')                       #=> true  # escaped wildcard becomes ordinary
#    File.fnmatch('\a',   'a')                       #=> true  # escaped ordinary remains ordinary
#    File.fnmatch('\a',   '\a', File::FNM_NOESCAPE)  #=> true  # FNM_NOESACPE makes '\' ordinary
#    File.fnmatch('[\?]', '?')                       #=> true  # can escape inside bracket expression
# 
#    File.fnmatch('*',   '.profile')                      #=> false # wildcard doesn't match leading
#    File.fnmatch('*',   '.profile', File::FNM_DOTMATCH)  #=> true  # period by default.
#    File.fnmatch('.*',  '.profile')                      #=> true
# 
#    rbfiles = '**' '/' '*.rb' # you don't have to do like this. just write in single string.
#    File.fnmatch(rbfiles, 'main.rb')                    #=> false
#    File.fnmatch(rbfiles, './main.rb')                  #=> false
#    File.fnmatch(rbfiles, 'lib/song.rb')                #=> true
#    File.fnmatch('**.rb', 'main.rb')                    #=> true
#    File.fnmatch('**.rb', './main.rb')                  #=> false
#    File.fnmatch('**.rb', 'lib/song.rb')                #=> true
#    File.fnmatch('*',           'dave/.profile')                      #=> true
# 
#    pattern = '*' '/' '*'
#    File.fnmatch(pattern, 'dave/.profile', File::FNM_PATHNAME)  #=> false
#    File.fnmatch(pattern, 'dave/.profile', File::FNM_PATHNAME | File::FNM_DOTMATCH) #=> true
# 
#    pattern = '**' '/' 'foo'
#    File.fnmatch(pattern, 'a/b/c/foo', File::FNM_PATHNAME)     #=> true
#    File.fnmatch(pattern, '/a/b/c/foo', File::FNM_PATHNAME)    #=> true
#    File.fnmatch(pattern, 'c:/a/b/c/foo', File::FNM_PATHNAME)  #=> true
#    File.fnmatch(pattern, 'a/.b/c/foo', File::FNM_PATHNAME)    #=> false
#    File.fnmatch(pattern, 'a/.b/c/foo', File::FNM_PATHNAME | File::FNM_DOTMATCH) #=> true
def self.fnmatch?( pattern, path, flags=0); true || false; end
##
# Returns a <code>File::Stat</code> object for the named file (see
# <code>File::Stat</code>).
# 
#    File.stat("testfile").mtime   #=> Tue Apr 08 12:58:04 CDT 2003
def self.stat(file_name); ''; end
##
# Same as <code>File::stat</code>, but does not follow the last symbolic
# link. Instead, reports on the link itself.
# 
#    File.symlink("testfile", "link2test")   #=> 0
#    File.stat("testfile").size              #=> 66
#    File.lstat("link2test").size            #=> 8
#    File.stat("link2test").size             #=> 66
def self.lstat(file_name); ''; end
##
# Identifies the type of the named file; the return string is one of
# ``<code>file</code>'', ``<code>directory</code>'',
# ``<code>characterSpecial</code>'', ``<code>blockSpecial</code>'',
# ``<code>fifo</code>'', ``<code>link</code>'',
# ``<code>socket</code>'', or ``<code>unknown</code>''.
# 
#    File.ftype("testfile")            #=> "file"
#    File.ftype("/dev/tty")            #=> "characterSpecial"
#    File.ftype("/tmp/.X11-unix/X0")   #=> "socket"
def self.ftype(file_name); ''; end
##
# Returns the last access time for the named file as a Time object).
# 
#    File.atime("testfile")   #=> Wed Apr 09 08:51:48 CDT 2003
def self.atime(file_name); Time.new; end
##
# Returns the modification time for the named file as a Time object.
# 
#    File.mtime("testfile")   #=> Tue Apr 08 12:58:04 CDT 2003
def self.mtime(file_name); Time.new; end
##
# Returns the change time for the named file (the time at which
# directory information about the file was changed, not the file
# itself).
# 
# Note that on Windows (NTFS), returns creation time (birth time).
# 
#    File.ctime("testfile")   #=> Wed Apr 09 08:53:13 CDT 2003
def self.ctime(file_name); Time.new; end
##
# Sets the access and modification times of each
# named file to the first two arguments. Returns
# the number of file names in the argument list.
def self.utime(); 0; end
##
# Changes permission bits on the named file(s) to the bit pattern
# represented by <i>mode_int</i>. Actual effects are operating system
# dependent (see the beginning of this section). On Unix systems, see
# <code>chmod(2)</code> for details. Returns the number of files
# processed.
# 
#    File.chmod(0644, "testfile", "out")   #=> 2
def self.chmod(); 0; end
##
# Changes the owner and group of the named file(s) to the given
# numeric owner and group id's. Only a process with superuser
# privileges may change the owner of a file. The current owner of a
# file may change the file's group to any group to which the owner
# belongs. A <code>nil</code> or -1 owner or group id is ignored.
# Returns the number of files processed.
# 
#    File.chown(nil, 100, "testfile")
def self.chown(owner_int, group_int ); 0; end
##
# Equivalent to <code>File::chmod</code>, but does not follow symbolic
# links (so it will change the permissions associated with the link,
# not the file referenced by the link). Often not available.
def self.lchmod(); 0; end
##
# Equivalent to <code>File::chown</code>, but does not follow symbolic
# links (so it will change the owner associated with the link, not the
# file referenced by the link). Often not available. Returns number
# of files in the argument list.
def self.lchown(); 0; end
##
# Creates a new name for an existing file using a hard link. Will not
# overwrite <i>new_name</i> if it already exists (raising a subclass
# of <code>SystemCallError</code>). Not available on all platforms.
# 
#    File.link("testfile", ".testfile")   #=> 0
#    IO.readlines(".testfile")[0]         #=> "This is line one\n"
def self.link(old_name, new_name); 0; end
##
# Creates a symbolic link called <i>new_name</i> for the existing file
# <i>old_name</i>. Raises a <code>NotImplemented</code> exception on
# platforms that do not support symbolic links.
# 
#    File.symlink("testfile", "link2test")   #=> 0
def self.symlink(old_name, new_name); 0; end
##
# Returns the name of the file referenced by the given link.
# Not available on all platforms.
# 
#    File.symlink("testfile", "link2test")   #=> 0
#    File.readlink("link2test")              #=> "testfile"
def self.readlink(link_name); ''; end
##
# Deletes the named files, returning the number of names
# passed as arguments. Raises an exception on any error.
# See also <code>Dir::rmdir</code>.
def self.delete(); 0; end
##
# Deletes the named files, returning the number of names
# passed as arguments. Raises an exception on any error.
# See also <code>Dir::rmdir</code>.
def self.unlink(); 0; end
##
# Renames the given file to the new name. Raises a
# <code>SystemCallError</code> if the file cannot be renamed.
# 
#    File.rename("afile", "afile.bak")   #=> 0
def self.rename(old_name, new_name); 0; end
##
# Returns the current umask value for this process. If the optional
# argument is given, set the umask to that value and return the
# previous value. Umask values are <em>subtracted</em> from the
# default permissions, so a umask of <code>0222</code> would make a
# file read-only for everyone.
# 
#    File.umask(0006)   #=> 18
#    File.umask         #=> 6
def self.umask(); 0; end
##
# Truncates the file <i>file_name</i> to be at most <i>integer</i>
# bytes long. Not available on all platforms.
# 
#    f = File.new("out", "w")
#    f.write("1234567890")     #=> 10
#    f.close                   #=> nil
#    File.truncate("out", 5)   #=> 0
#    File.size("out")          #=> 5
def self.truncate(file_name, integer); 0; end
##
# Converts a pathname to an absolute pathname. Relative paths are
# referenced from the current working directory of the process unless
# <i>dir_string</i> is given, in which case it will be used as the
# starting point. The given pathname may start with a
# ``<code>~</code>'', which expands to the process owner's home
# directory (the environment variable <code>HOME</code> must be set
# correctly). ``<code>~</code><i>user</i>'' expands to the named
# user's home directory.
# 
#    File.expand_path("~oracle/bin")           #=> "/home/oracle/bin"
#    File.expand_path("../../bin", "/tmp/x")   #=> "/bin"
def self.expand_path(file_name  , dir_string=0); ''; end
##
# Converts a pathname to an absolute pathname. Relative paths are
# referenced from the current working directory of the process unless
# <i>dir_string</i> is given, in which case it will be used as the
# starting point. If the given pathname starts with a ``<code>~</code>''
# it is NOT expanded, it is treated as a normal directory name.
# 
#    File.absolute_path("~oracle/bin")       #=> "<relative_path>/~oracle/bin"
def self.absolute_path(file_name  , dir_string=0); ''; end
##
# Returns the real (absolute) pathname of _pathname_ in the actual
# filesystem not containing symlinks or useless dots.
# 
# If _dir_string_ is given, it is used as a base directory
# for interpreting relative pathname instead of the current directory.
# 
# All components of the pathname must exist when this method is
# called.
def self.realpath(pathname , dir_string=0); ''; end
##
# Returns the real (absolute) pathname of _pathname_ in the actual filesystem.
# The real pathname doesn't contain symlinks or useless dots.
# 
# If _dir_string_ is given, it is used as a base directory
# for interpreting relative pathname instead of the current directory.
# 
# The last component of the real pathname can be nonexistent.
def self.realdirpath(pathname , dir_string=0); ''; end
##
# Returns the last component of the filename given in <i>file_name</i>,
# which can be formed using both <code>File::SEPARATOR</code> and
# <code>File::ALT_SEPARETOR</code> as the separator when
# <code>File::ALT_SEPARATOR</code> is not <code>nil</code>. If
# <i>suffix</i> is given and present at the end of <i>file_name</i>,
# it is removed.
# 
#    File.basename("/home/gumby/work/ruby.rb")          #=> "ruby.rb"
#    File.basename("/home/gumby/work/ruby.rb", ".rb")   #=> "ruby"
def self.basename(file_name  , suffix=0); ''; end
##
# Returns all components of the filename given in <i>file_name</i>
# except the last one. The filename can be formed using both
# <code>File::SEPARATOR</code> and <code>File::ALT_SEPARETOR</code> as the
# separator when <code>File::ALT_SEPARATOR</code> is not <code>nil</code>.
# 
#    File.dirname("/home/gumby/work/ruby.rb")   #=> "/home/gumby/work"
def self.dirname(file_name ); ''; end
##
# Returns the extension (the portion of file name in +path+
# starting from the last period).
# 
# If +path+ is a dotfile, or starts with a period, then the starting
# dot is not dealt with the start of the extension.
# 
# An empty string will also be returned when the period is the last character
# in +path+.
# 
#    File.extname("test.rb")         #=> ".rb"
#    File.extname("a/b/d/test.rb")   #=> ".rb"
#    File.extname("foo.")            #=> ""
#    File.extname("test")            #=> ""
#    File.extname(".profile")        #=> ""
#    File.extname(".profile.sh")     #=> ".sh"
def self.extname(path); ''; end
##
# Returns the string representation of the path
# 
#    File.path("/dev/null")          #=> "/dev/null"
#    File.path(Pathname.new("/tmp")) #=> "/tmp"
def self.path(path); ''; end
##
# Splits the given string into a directory and a file component and
# returns them in a two-element array. See also
# <code>File::dirname</code> and <code>File::basename</code>.
# 
#    File.split("/home/gumby/.profile")   #=> ["/home/gumby", ".profile"]
def self.split(file_name); []; end
##
# Returns a new string formed by joining the strings using
# <code>File::SEPARATOR</code>.
# 
#    File.join("usr", "mail", "gumby")   #=> "usr/mail/gumby"
def self.join(); ''; end
##
# Returns the size of <i>file</i> in bytes.
# 
#    File.new("testfile").size   #=> 66
def size(file_name); 0; end
##
# Locks or unlocks a file according to <i>locking_constant</i> (a
# logical <em>or</em> of the values in the table below).
# Returns <code>false</code> if <code>File::LOCK_NB</code> is
# specified and the operation would otherwise have blocked. Not
# available on all platforms.
# 
# Locking constants (in class File):
# 
#    LOCK_EX   | Exclusive lock. Only one process may hold an
#              | exclusive lock for a given file at a time.
#    ----------+------------------------------------------------
#    LOCK_NB   | Don't block when locking. May be combined
#              | with other lock options using logical or.
#    ----------+------------------------------------------------
#    LOCK_SH   | Shared lock. Multiple processes may each hold a
#              | shared lock for a given file at the same time.
#    ----------+------------------------------------------------
#    LOCK_UN   | Unlock.
# 
# Example:
# 
#    # update a counter using write lock
#    # don't use "w" because it truncates the file before lock.
#    File.open("counter", File::RDWR|File::CREAT, 0644) {|f|
#      f.flock(File::LOCK_EX)
#      value = f.read.to_i + 1
#      f.rewind
#      f.write("#{value}\n")
#      f.flush
#      f.truncate(f.pos)
#    }
# 
#    # read the counter using read lock
#    File.open("counter", "r") {|f|
#      f.flock(File::LOCK_SH)
#      p f.read
#    }
def flock (locking_constant ); 0 || false; end
##
# Returns <code>true</code> if the named file is a directory,
# or a symlink that points at a directory, and <code>false</code>
# otherwise.
# 
#    File.directory?(".")
def self.directory?(file_name); true || false; end
##
# Return <code>true</code> if the named file exists.
def self.exist?(file_name); true || false; end
##
# Return <code>true</code> if the named file exists.
def self.exists?(file_name); true || false; end
##
# Returns <code>true</code> if the named file is readable by the effective
# user id of this process.
def self.readable?(file_name); true || false; end
##
# Returns <code>true</code> if the named file is readable by the real
# user id of this process.
def self.readable_real?(file_name); true || false; end
##
# If <i>file_name</i> is readable by others, returns an integer
# representing the file permission bits of <i>file_name</i>. Returns
# <code>nil</code> otherwise. The meaning of the bits is platform
# dependent; on Unix systems, see <code>stat(2)</code>.
# 
#    File.world_readable?("/etc/passwd")           #=> 420
#    m = File.world_readable?("/etc/passwd")
#    sprintf("%o", m)                              #=> "644"
def self.world_readable?(file_name); 1 || nil; end
##
# Returns <code>true</code> if the named file is writable by the effective
# user id of this process.
def self.writable?(file_name); true || false; end
##
# Returns <code>true</code> if the named file is writable by the real
# user id of this process.
def self.writable_real?(file_name); true || false; end
##
# If <i>file_name</i> is writable by others, returns an integer
# representing the file permission bits of <i>file_name</i>. Returns
# <code>nil</code> otherwise. The meaning of the bits is platform
# dependent; on Unix systems, see <code>stat(2)</code>.
# 
#    File.world_writable?("/tmp")                  #=> 511
#    m = File.world_writable?("/tmp")
#    sprintf("%o", m)                              #=> "777"
def self.world_writable?(file_name); 1 || nil; end
##
# Returns <code>true</code> if the named file is executable by the effective
# user id of this process.
def self.executable?(file_name); true || false; end
##
# Returns <code>true</code> if the named file is executable by the real
# user id of this process.
def self.executable_real?(file_name); true || false; end
##
# Returns <code>true</code> if the named file exists and is a
# regular file.
def self.file?(file_name); true || false; end
##
# Returns <code>true</code> if the named file exists and has
# a zero size.
def self.zero?(file_name); true || false; end
##
# Returns +nil+ if +file_name+ doesn't exist or has zero size, the size of the
# file otherwise.
def self.size?(file_name); 0 || nil; end
##
# Returns <code>true</code> if the named file exists and the
# effective used id of the calling process is the owner of
# the file.
def self.owned?(file_name); true || false; end
##
# Returns <code>true</code> if the named file exists and the
# effective group id of the calling process is the owner of
# the file. Returns <code>false</code> on Windows.
def self.grpowned?(file_name); true || false; end
##
# Returns <code>true</code> if the named file is a pipe.
def self.pipe?(file_name); true || false; end
##
# Returns <code>true</code> if the named file is a symbolic link.
def self.symlink?(file_name); true || false; end
##
# Returns <code>true</code> if the named file is a socket.
def self.socket?(file_name); true || false; end
##
# Returns <code>true</code> if the named file is a block device.
def self.blockdev?(file_name); true || false; end
##
# Returns <code>true</code> if the named file is a character device.
def self.chardev?(file_name); true || false; end
##
# Returns <code>true</code> if the named file has the setuid bit set.
def self.setuid?(file_name); true || false; end
##
# Returns <code>true</code> if the named file has the setgid bit set.
def self.setgid?(file_name); true || false; end
##
# Returns <code>true</code> if the named file has the sticky bit set.
def self.sticky?(file_name); true || false; end
##
# Returns <code>true</code> if the named files are identical.
# 
#     open("a", "w") {}
#     p File.identical?("a", "a")      #=> true
#     p File.identical?("a", "./a")    #=> true
#     File.link("a", "b")
#     p File.identical?("a", "b")      #=> true
#     File.symlink("a", "c")
#     p File.identical?("a", "c")      #=> true
#     open("d", "w") {}
#     p File.identical?("a", "d")      #=> false
def self.identical?(file_1, file_2); true || false; end
##
# With no associated block, <code>File.open</code> is a synonym for
# File.new. If the optional code block is given, it will
# be passed the opened +file+ as an argument and the File object will
# automatically be closed when the block terminates.  The value of the block
# will be returned from <code>File.open</code>.
# 
# If a file is being created, its initial permissions may be set using the
# +perm+ parameter.  See File.new for further discussion.
# 
# See IO.new for a description of the +mode+ and +opt+ parameters.
def self.open(filename, mode="r" , opt=0); Object.new; end
##
# Opens the file named by +filename+ according to the given +mode+ and
# returns a new File object.
# 
# See IO.new for a description of +mode+ and +opt+.
# 
# If a file is being created, permission bits may be given in +perm+.  These
# mode and permission bits are platform dependent; on Unix systems, see
# open(2) and chmod(2) man pages for details.
# 
# === Examples
# 
#   f = File.new("testfile", "r")
#   f = File.new("newfile",  "w+")
#   f = File.new("newfile", File::CREAT|File::TRUNC|File::RDWR, 0644)
def self.new(filename, mode="r" , opt=0); end
end

class IO < Object
include Constants
include Enumerable
##
# Returns status information for <em>ios</em> as an object of type
# <code>File::Stat</code>.
# 
#    f = File.new("testfile")
#    s = f.stat
#    "%o" % s.mode   #=> "100644"
#    s.blksize       #=> 4096
#    s.atime         #=> Wed Apr 09 08:53:54 CDT 2003
def stat; ''; end
##
# With no associated block, <code>IO.open</code> is a synonym for IO.new.  If
# the optional code block is given, it will be passed +io+ as an argument,
# and the IO object will automatically be closed when the block terminates.
# In this instance, IO.open returns the value of the block.
# 
# See IO.new for a description of the +fd+, +mode+ and +opt+ parameters.
def self.open(fd, mode="r" , opt=0); Object.new; end
##
# Opens the given path, returning the underlying file descriptor as a
# <code>Fixnum</code>.
# 
#    IO.sysopen("testfile")   #=> 3
def self.sysopen(path, mode=0, perm=0); 0; end
##
# Synonym for <code>IO.new</code>.
def self.for_fd(fd, mode , opt=0); IO.new; end
##
# Runs the specified command as a subprocess; the subprocess's
# standard input and output will be connected to the returned
# <code>IO</code> object.
# 
# The PID of the started process can be obtained by IO#pid method.
# 
# _cmd_ is a string or an array as follows.
# 
#   cmd:
#     "-"                                      : fork
#     commandline                              : command line string which is passed to a shell
#     [env, cmdname, arg1, ..., opts]          : command name and zero or more arguments (no shell)
#     [env, [cmdname, argv0], arg1, ..., opts] : command name, argv[0] and zero or more arguments (no shell)
#   (env and opts are optional.)
# 
# If _cmd_ is a +String+ ``<code>-</code>'',
# then a new instance of Ruby is started as the subprocess.
# 
# If <i>cmd</i> is an +Array+ of +String+,
# then it will be used as the subprocess's +argv+ bypassing a shell.
# The array can contains a hash at first for environments and
# a hash at last for options similar to <code>spawn</code>.
# 
# The default mode for the new file object is ``r'',
# but <i>mode</i> may be set to any of the modes listed in the description for class IO.
# The last argument <i>opt</i> qualifies <i>mode</i>.
# 
#   # set IO encoding
#   IO.popen("nkf -e filename", :external_encoding=>"EUC-JP") {|nkf_io|
#     euc_jp_string = nkf_io.read
#   }
# 
#   # merge standard output and standard error using
#   # spawn option.  See the document of Kernel.spawn.
#   IO.popen(["ls", "/", :err=>[:child, :out]]) {|ls_io|
#     ls_result_with_error = ls_io.read
#   }
# 
#   # spawn options can be mixed with IO options
#   IO.popen(["ls", "/"], :err=>[:child, :out]) {|ls_io|
#     ls_result_with_error = ls_io.read
#   }
# 
# Raises exceptions which <code>IO.pipe</code> and
# <code>Kernel.spawn</code> raise.
# 
# If a block is given, Ruby will run the command as a child connected
# to Ruby with a pipe. Ruby's end of the pipe will be passed as a
# parameter to the block.
# At the end of block, Ruby close the pipe and sets <code>$?</code>.
# In this case <code>IO.popen</code> returns
# the value of the block.
# 
# If a block is given with a _cmd_ of ``<code>-</code>'',
# the block will be run in two separate processes: once in the parent,
# and once in a child. The parent process will be passed the pipe
# object as a parameter to the block, the child version of the block
# will be passed <code>nil</code>, and the child's standard in and
# standard out will be connected to the parent through the pipe. Not
# available on all platforms.
# 
#    f = IO.popen("uname")
#    p f.readlines
#    f.close
#    puts "Parent is #{Process.pid}"
#    IO.popen("date") { |f| puts f.gets }
#    IO.popen("-") {|f| $stderr.puts "#{Process.pid} is here, f is #{f.inspect}"}
#    p $?
#    IO.popen(%w"sed -e s|^|<foo>| -e s&$&;zot;&", "r+") {|f|
#      f.puts "bar"; f.close_write; puts f.gets
#    }
# 
# <em>produces:</em>
# 
#    ["Linux\n"]
#    Parent is 21346
#    Thu Jan 15 22:41:19 JST 2009
#    21346 is here, f is #<IO:fd 3>
#    21352 is here, f is nil
#    #<Process::Status: pid 21352 exit 0>
#    <foo>bar;zot;
def self.popen(env=0, cmd=0, mode=0, r=0, opt=0); Object.new; end
##
# Executes the block for every line in the named I/O port, where lines
# are separated by <em>sep</em>.
# 
# If no block is given, an enumerator is returned instead.
# 
#    IO.foreach("testfile") {|x| print "GOT ", x }
# 
# <em>produces:</em>
# 
#    GOT This is line one
#    GOT This is line two
#    GOT This is line three
#    GOT And so on...
# 
# If the last argument is a hash, it's the keyword argument to open.
# See <code>IO.read</code> for detail.
def self.foreach(name, sep=$/ , open_args=0, &block); Enumerator.new; end
##
# Reads the entire file specified by <i>name</i> as individual
# lines, and returns those lines in an array. Lines are separated by
# <i>sep</i>.
# 
#    a = IO.readlines("testfile")
#    a[0]   #=> "This is line one\n"
# 
# If the last argument is a hash, it's the keyword argument to open.
# See <code>IO.read</code> for detail.
def self.readlines(name, sep=$/ , open_args=0); []; end
##
# Opens the file, optionally seeks to the given +offset+, then returns
# +length+ bytes (defaulting to the rest of the file).  <code>read</code>
# ensures the file is closed before returning.
# 
# If the last argument is a hash, it specifies option for internal
# open().  The key would be the following.  open_args: is exclusive
# to others.
# 
# encoding::
#   string or encoding
# 
#   specifies encoding of the read string.  +encoding+ will be ignored
#   if length is specified.
# 
# mode::
#   string
# 
#   specifies mode argument for open().  It should start with "r"
#   otherwise it will cause an error.
# 
# open_args:: array of strings
# 
#   specifies arguments for open() as an array.
# 
# Examples:
# 
#   IO.read("testfile")           #=> "This is line one\nThis is line two\nThis is line three\nAnd so on...\n"
#   IO.read("testfile", 20)       #=> "This is line one\nThi"
#   IO.read("testfile", 20, 10)   #=> "ne one\nThis is line "
def self.read(name, length=0, offset=0); '' || nil; end
##
# Opens the file, optionally seeks to the given <i>offset</i>, then returns
# <i>length</i> bytes (defaulting to the rest of the file).
# <code>binread</code> ensures the file is closed before returning.
# The open mode would be "rb:ASCII-8BIT".
# 
#    IO.binread("testfile")           #=> "This is line one\nThis is line two\nThis is line three\nAnd so on...\n"
#    IO.binread("testfile", 20)       #=> "This is line one\nThi"
#    IO.binread("testfile", 20, 10)   #=> "ne one\nThis is line "
def self.binread(name, length=0, offset=0); ''; end
##
# Opens the file, optionally seeks to the given <i>offset</i>, writes
# <i>string</i>, then returns the length written.
# <code>write</code> ensures the file is closed before returning.
# If <i>offset</i> is not given, the file is truncated.  Otherwise,
# it is not truncated.
# 
# If the last argument is a hash, it specifies option for internal
# open().  The key would be the following.  open_args: is exclusive
# to others.
# 
#  encoding: string or encoding
# 
#   specifies encoding of the read string.  encoding will be ignored
#   if length is specified.
# 
#  mode: string
# 
#   specifies mode argument for open().  it should start with "w" or "a" or "r+"
#   otherwise it would cause error.
# 
#  perm: fixnum
# 
#   specifies perm argument for open().
# 
#  open_args: array
# 
#   specifies arguments for open() as an array.
# 
#    IO.write("testfile", "0123456789", 20) # => 10
#    # File could contain:  "This is line one\nThi0123456789two\nThis is line three\nAnd so on...\n"
#    IO.write("testfile", "0123456789")      #=> 10
#    # File would now read: "0123456789"
def self.write(name, string, offset=0); 0; end
##
# Same as <code>IO.write</code> except opening the file in binary mode
# and ASCII-8BIT encoding ("wb:ASCII-8BIT").
def self.binwrite(name, string, offset=0); 0; end
##
# Calls select(2) system call.
# It monitors given arrays of <code>IO</code> objects, waits one or more
# of <code>IO</code> objects ready for reading, are ready for writing,
# and have pending exceptions respectively, and returns an array that
# contains arrays of those IO objects.  It will return <code>nil</code>
# if optional <i>timeout</i> value is given and no <code>IO</code> object
# is ready in <i>timeout</i> seconds.
# 
# === Parameters
# read_array:: an array of <code>IO</code> objects that wait until ready for read
# write_array:: an array of <code>IO</code> objects that wait until ready for write
# error_array:: an array of <code>IO</code> objects that wait for exceptions
# timeout:: a numeric value in second
# 
# === Example
# 
#     rp, wp = IO.pipe
#     mesg = "ping "
#     100.times {
#       rs, ws, = IO.select([rp], [wp])
#       if r = rs[0]
#         ret = r.read(5)
#         print ret
#         case ret
#         when /ping/
#           mesg = "pong\n"
#         when /pong/
#           mesg = "ping "
#         end
#       end
#       if w = ws[0]
#         w.write(mesg)
#       end
#     }
# 
# <em>produces:</em>
# 
#     ping pong
#     ping pong
#     ping pong
#     (snipped)
#     ping
def self.select(read_arra); [] || nil; end
##
# Creates a pair of pipe endpoints (connected to each other) and
# returns them as a two-element array of <code>IO</code> objects:
# <code>[</code> <i>read_io</i>, <i>write_io</i> <code>]</code>.
# 
# If a block is given, the block is called and
# returns the value of the block.
# <i>read_io</i> and <i>write_io</i> are sent to the block as arguments.
# If read_io and write_io are not closed when the block exits, they are closed.
# i.e. closing read_io and/or write_io doesn't cause an error.
# 
# Not available on all platforms.
# 
# If an encoding (encoding name or encoding object) is specified as an optional argument,
# read string from pipe is tagged with the encoding specified.
# If the argument is a colon separated two encoding names "A:B",
# the read string is converted from encoding A (external encoding)
# to encoding B (internal encoding), then tagged with B.
# If two optional arguments are specified, those must be
# encoding objects or encoding names,
# and the first one is the external encoding,
# and the second one is the internal encoding.
# If the external encoding and the internal encoding is specified,
# optional hash argument specify the conversion option.
# 
# In the example below, the two processes close the ends of the pipe
# that they are not using. This is not just a cosmetic nicety. The
# read end of a pipe will not generate an end of file condition if
# there are any writers with the pipe still open. In the case of the
# parent process, the <code>rd.read</code> will never return if it
# does not first issue a <code>wr.close</code>.
# 
#    rd, wr = IO.pipe
# 
#    if fork
#      wr.close
#      puts "Parent got: <#{rd.read}>"
#      rd.close
#      Process.wait
#    else
#      rd.close
#      puts "Sending message to parent"
#      wr.write "Hi Dad"
#      wr.close
#    end
# 
# <em>produces:</em>
# 
#    Sending message to parent
#    Parent got: <Hi Dad>
def self.pipe; end
##
# Try to convert <i>obj</i> into an IO, using to_io method.
# Returns converted IO or nil if <i>obj</i> cannot be converted
# for any reason.
# 
#    IO.try_convert(STDOUT)     #=> STDOUT
#    IO.try_convert("STDOUT")   #=> nil
# 
#    require 'zlib'
#    f = open("/tmp/zz.gz")       #=> #<File:/tmp/zz.gz>
#    z = Zlib::GzipReader.open(f) #=> #<Zlib::GzipReader:0x81d8744>
#    IO.try_convert(z)            #=> #<File:/tmp/zz.gz>
def self.try_convert(obj); IO.new || nil; end
##
# IO.copy_stream copies <i>src</i> to <i>dst</i>.
# <i>src</i> and <i>dst</i> is either a filename or an IO.
# 
# This method returns the number of bytes copied.
# 
# If optional arguments are not given,
# the start position of the copy is
# the beginning of the filename or
# the current file offset of the IO.
# The end position of the copy is the end of file.
# 
# If <i>copy_length</i> is given,
# No more than <i>copy_length</i> bytes are copied.
# 
# If <i>src_offset</i> is given,
# it specifies the start position of the copy.
# 
# When <i>src_offset</i> is specified and
# <i>src</i> is an IO,
# IO.copy_stream doesn't move the current file offset.
def self.copy_stream(src, dst); end
##
# Returns a new IO object (a stream) for the given integer file descriptor
# +fd+ and +mode+ string.  +opt+ may be used to specify parts of +mode+ in a
# more readable fashion.  See also IO.sysopen and IO.for_fd.
# 
# IO.new is called by various File and IO opening methods such as IO::open,
# Kernel#open, and File::open.
# 
# === Open Mode
# 
# When +mode+ is an integer it must be combination of the modes defined in
# File::Constants (+File::RDONLY+, +File::WRONLY | File::CREAT+).  See the
# open(2) man page for more information.
# 
# When +mode+ is a string it must be in one of the following forms:
# 
#   fmode
#   fmode ":" ext_enc
#   fmode ":" ext_enc ":" int_enc
#   fmode ":" "BOM|UTF-*"
# 
# +fmode+ is an IO open mode string, +ext_enc+ is the external encoding for
# the IO and +int_enc+ is the internal encoding.
# 
# ==== IO Open Mode
# 
# Ruby allows the following open modes:
# 
#     "r"  Read-only, starts at beginning of file  (default mode).
# 
#     "r+" Read-write, starts at beginning of file.
# 
#     "w"  Write-only, truncates existing file
#          to zero length or creates a new file for writing.
# 
#     "w+" Read-write, truncates existing file to zero length
#          or creates a new file for reading and writing.
# 
#     "a"  Write-only, starts at end of file if file exists,
#          otherwise creates a new file for writing.
# 
#     "a+" Read-write, starts at end of file if file exists,
#          otherwise creates a new file for reading and
#          writing.
# 
# The following modes must be used separately, and along with one or more of
# the modes seen above.
# 
#     "b"  Binary file mode
#          Suppresses EOL <-> CRLF conversion on Windows. And
#          sets external encoding to ASCII-8BIT unless explicitly
#          specified.
# 
#     "t"  Text file mode
# 
# When the open mode of original IO is read only, the mode cannot be
# changed to be writable.  Similarly, the open mode cannot be changed from
# write only to readable.
# 
# When such a change is attempted the error is raised in different locations
# according to the platform.
# 
# === IO Encoding
# 
# When +ext_enc+ is specified, strings read will be tagged by the encoding
# when reading, and strings output will be converted to the specified
# encoding when writing.
# 
# When +ext_enc+ and +int_enc+ are specified read strings will be converted
# from +ext_enc+ to +int_enc+ upon input, and written strings will be
# converted from +int_enc+ to +ext_enc+ upon output.  See Encoding for
# further details of transcoding on input and output.
# 
# If "BOM|UTF-8", "BOM|UTF-16LE" or "BOM|UTF16-BE" are used, ruby checks for
# a Unicode BOM in the input document to help determine the encoding.  For
# UTF-16 encodings the file open mode must be binary.  When present, the BOM
# is stripped and the external encoding from the BOM is used.  When the BOM
# is missing the given Unicode encoding is used as +ext_enc+.  (The BOM-set
# encoding option is case insensitive, so "bom|utf-8" is also valid.)
# 
# === Options
# 
# +opt+ can be used instead of +mode+ for improved readability.  The
# following keys are supported:
# 
# :mode ::
#   Same as +mode+ parameter
# 
# :\external_encoding ::
#   External encoding for the IO.  "-" is a synonym for the default external
#   encoding.
# 
# :\internal_encoding ::
#   Internal encoding for the IO.  "-" is a synonym for the default internal
#   encoding.
# 
#   If the value is nil no conversion occurs.
# 
# :encoding ::
#   Specifies external and internal encodings as "extern:intern".
# 
# :textmode ::
#   If the value is truth value, same as "t" in argument +mode+.
# 
# :binmode ::
#   If the value is truth value, same as "b" in argument +mode+.
# 
# :autoclose ::
#   If the value is +false+, the +fd+ will be kept open after this IO
#   instance gets finalized.
# 
# Also, +opt+ can have same keys in String#encode for controlling conversion
# between the external encoding and the internal encoding.
# 
# === Example 1
# 
#   fd = IO.sysopen("/dev/tty", "w")
#   a = IO.new(fd,"w")
#   $stderr.puts "Hello"
#   a.puts "World"
# 
# Produces:
# 
#   Hello
#   World
# 
# === Example 2
# 
#   require 'fcntl'
# 
#   fd = STDERR.fcntl(Fcntl::F_DUPFD)
#   io = IO.new(fd, mode: 'w:UTF-16LE', cr_newline: true)
#   io.puts "Hello, World!"
# 
#   fd = STDERR.fcntl(Fcntl::F_DUPFD)
#   io = IO.new(fd, mode: 'w', cr_newline: true,
#               external_encoding: Encoding::UTF_16LE)
#   io.puts "Hello, World!"
# 
# Both of above print "Hello, World!" in UTF-16LE to standard error output
# with converting EOL generated by <code>puts</code> to CR.
def self.new(fd , mode=0, opt=0); end
##
# Reassociates <em>ios</em> with the I/O stream given in
# <i>other_IO</i> or to a new stream opened on <i>path</i>. This may
# dynamically change the actual class of this stream.
# 
#    f1 = File.new("testfile")
#    f2 = File.new("testfile")
#    f2.readlines[0]   #=> "This is line one\n"
#    f2.reopen(f1)     #=> #<File:testfile>
#    f2.readlines[0]   #=> "This is line one\n"
def reopen(other_IO); IO.new; end
##
# Writes the given object(s) to <em>ios</em>. The stream must be
# opened for writing. If the output field separator (<code>$,</code>)
# is not <code>nil</code>, it will be inserted between each object.
# If the output record separator (<code>$\\</code>)
# is not <code>nil</code>, it will be appended to the output. If no
# arguments are given, prints <code>$_</code>. Objects that aren't
# strings will be converted by calling their <code>to_s</code> method.
# With no argument, prints the contents of the variable <code>$_</code>.
# Returns <code>nil</code>.
# 
#    $stdout.print("This is ", 100, " percent.\n")
# 
# <em>produces:</em>
# 
#    This is 100 percent.
def print(); end
##
# If <i>obj</i> is <code>Numeric</code>, write the character whose code is
# the least-significant byte of <i>obj</i>, otherwise write the first byte
# of the string representation of <i>obj</i> to <em>ios</em>. Note: This
# method is not safe for use with multi-byte characters as it will truncate
# them.
# 
#    $stdout.putc "A"
#    $stdout.putc 65
# 
# <em>produces:</em>
# 
#    AA
def putc(obj); Object.new; end
##
# Writes the given objects to <em>ios</em> as with
# <code>IO#print</code>. Writes a record separator (typically a
# newline) after any that do not already end with a newline sequence.
# If called with an array argument, writes each element on a new line.
# If called without arguments, outputs a single record separator.
# 
#    $stdout.puts("this", "is", "a", "test")
# 
# <em>produces:</em>
# 
#    this
#    is
#    a
#    test
def puts(); end
##
# Formats and writes to <em>ios</em>, converting parameters under
# control of the format string. See <code>Kernel#sprintf</code>
# for details.
def printf(format_string , obj=0); end
##
# Executes the block for every line in <em>ios</em>, where lines are
# separated by <i>sep</i>. <em>ios</em> must be opened for
# reading or an <code>IOError</code> will be raised.
# 
# If no block is given, an enumerator is returned instead.
# 
#    f = File.new("testfile")
#    f.each {|line| puts "#{f.lineno}: #{line}" }
# 
# <em>produces:</em>
# 
#    1: This is line one
#    2: This is line two
#    3: This is line three
#    4: And so on...
def each(sep=$/, &block); Enumerator.new; end
##
# Executes the block for every line in <em>ios</em>, where lines are
# separated by <i>sep</i>. <em>ios</em> must be opened for
# reading or an <code>IOError</code> will be raised.
# 
# If no block is given, an enumerator is returned instead.
# 
#    f = File.new("testfile")
#    f.each {|line| puts "#{f.lineno}: #{line}" }
# 
# <em>produces:</em>
# 
#    1: This is line one
#    2: This is line two
#    3: This is line three
#    4: And so on...
def each_line(sep=$/, &block); Enumerator.new; end
##
# Calls the given block once for each byte (0..255) in <em>ios</em>,
# passing the byte as an argument. The stream must be opened for
# reading or an <code>IOError</code> will be raised.
# 
# If no block is given, an enumerator is returned instead.
# 
#    f = File.new("testfile")
#    checksum = 0
#    f.each_byte {|x| checksum ^= x }   #=> #<File:testfile>
#    checksum                           #=> 12
def each_byte(&block); Enumerator.new; end
##
# Calls the given block once for each character in <em>ios</em>,
# passing the character as an argument. The stream must be opened for
# reading or an <code>IOError</code> will be raised.
# 
# If no block is given, an enumerator is returned instead.
# 
#    f = File.new("testfile")
#    f.each_char {|c| print c, ' ' }   #=> #<File:testfile>
def each_char(&block); Enumerator.new; end
##
# Passes the <code>Integer</code> ordinal of each character in <i>ios</i>,
# passing the codepoint as an argument. The stream must be opened for
# reading or an <code>IOError</code> will be raised.
# 
# If no block is given, an enumerator is returned instead.
def each_codepoint(&block); Enumerator.new; end
##
# Passes the <code>Integer</code> ordinal of each character in <i>ios</i>,
# passing the codepoint as an argument. The stream must be opened for
# reading or an <code>IOError</code> will be raised.
# 
# If no block is given, an enumerator is returned instead.
def codepoints(&block); Enumerator.new; end
##
# Writes the given string to <em>ios</em> using a low-level write.
# Returns the number of bytes written. Do not mix with other methods
# that write to <em>ios</em> or you may get unpredictable results.
# Raises <code>SystemCallError</code> on error.
# 
#    f = File.new("out", "w")
#    f.syswrite("ABCDEF")   #=> 6
def syswrite(string); 0; end
##
# Reads <i>maxlen</i> bytes from <em>ios</em> using a low-level
# read and returns them as a string.  Do not mix with other methods
# that read from <em>ios</em> or you may get unpredictable results.
# If the optional <i>outbuf</i> argument is present, it must reference
# a String, which will receive the data.
# The <i>outbuf</i> will contain only the received data after the method call
# even if it is not empty at the beginning.
# Raises <code>SystemCallError</code> on error and
# <code>EOFError</code> at end of file.
# 
#    f = File.new("testfile")
#    f.sysread(16)   #=> "This is line one"
def sysread(maxlen, outbuf=0); ''; end
##
# Returns an integer representing the numeric file descriptor for
# <em>ios</em>.
# 
#    $stdin.fileno    #=> 0
#    $stdout.fileno   #=> 1
def fileno; 0; end
##
# Returns an integer representing the numeric file descriptor for
# <em>ios</em>.
# 
#    $stdin.fileno    #=> 0
#    $stdout.fileno   #=> 1
def to_i; 0; end
##
# Returns <em>ios</em>.
def to_io; IO.new; end
##
# Immediately writes all buffered data in <em>ios</em> to disk.
# Note that <code>fsync</code> differs from
# using <code>IO#sync=</code>. The latter ensures that data is flushed
# from Ruby's buffers, but does not guarantee that the underlying
# operating system actually writes it to disk.
# 
# <code>NotImplementedError</code> is raised
# if the underlying operating system does not support <em>fsync(2)</em>.
def fsync; 0 || nil; end
##
# Immediately writes all buffered data in <em>ios</em> to disk.
# 
# If the underlying operating system does not support <em>fdatasync(2)</em>,
# <code>IO#fsync</code> is called instead (which might raise a
# <code>NotImplementedError</code>).
def fdatasync; 0 || nil; end
##
# Returns the current ``sync mode'' of <em>ios</em>. When sync mode is
# true, all output is immediately flushed to the underlying operating
# system and is not buffered by Ruby internally. See also
# <code>IO#fsync</code>.
# 
#    f = File.new("testfile")
#    f.sync   #=> false
def sync; true || false; end
##
# Sets the ``sync mode'' to <code>true</code> or <code>false</code>.
# When sync mode is true, all output is immediately flushed to the
# underlying operating system and is not buffered internally. Returns
# the new state. See also <code>IO#fsync</code>.
# 
#    f = File.new("testfile")
#    f.sync = true
# 
# <em>(produces no output)</em>
def sync= boolean; true || false; end
##
# Returns the current line number in <em>ios</em>.  The stream must be
# opened for reading. <code>lineno</code> counts the number of times
# #gets is called rather than the number of newlines encountered.  The two
# values will differ if #gets is called with a separator other than newline.
# 
# Methods that use <code>$/</code> like #each, #lines and #readline will
# also increment <code>lineno</code>.
# 
# See also the <code>$.</code> variable.
# 
#    f = File.new("testfile")
#    f.lineno   #=> 0
#    f.gets     #=> "This is line one\n"
#    f.lineno   #=> 1
#    f.gets     #=> "This is line two\n"
#    f.lineno   #=> 2
def lineno; 0; end
##
# Manually sets the current line number to the given value.
# <code>$.</code> is updated only on the next read.
# 
#    f = File.new("testfile")
#    f.gets                     #=> "This is line one\n"
#    $.                         #=> 1
#    f.lineno = 1000
#    f.lineno                   #=> 1000
#    $.                         #=> 1         # lineno of last read
#    f.gets                     #=> "This is line two\n"
#    $.                         #=> 1001      # lineno of last read
def lineno= integer; 0; end
##
# Reads at most <i>maxlen</i> bytes from <em>ios</em> using
# the read(2) system call after O_NONBLOCK is set for
# the underlying file descriptor.
# 
# If the optional <i>outbuf</i> argument is present,
# it must reference a String, which will receive the data.
# The <i>outbuf</i> will contain only the received data after the method call
# even if it is not empty at the beginning.
# 
# read_nonblock just calls the read(2) system call.
# It causes all errors the read(2) system call causes: Errno::EWOULDBLOCK, Errno::EINTR, etc.
# The caller should care such errors.
# 
# If the exception is Errno::EWOULDBLOCK or Errno::AGAIN,
# it is extended by IO::WaitReadable.
# So IO::WaitReadable can be used to rescue the exceptions for retrying read_nonblock.
# 
# read_nonblock causes EOFError on EOF.
# 
# If the read byte buffer is not empty,
# read_nonblock reads from the buffer like readpartial.
# In this case, the read(2) system call is not called.
# 
# When read_nonblock raises an exception kind of IO::WaitReadable,
# read_nonblock should not be called
# until io is readable for avoiding busy loop.
# This can be done as follows.
# 
#   # emulates blocking read (readpartial).
#   begin
#     result = io.read_nonblock(maxlen)
#   rescue IO::WaitReadable
#     IO.select([io])
#     retry
#   end
# 
# Although IO#read_nonblock doesn't raise IO::WaitWritable.
# OpenSSL::Buffering#read_nonblock can raise IO::WaitWritable.
# If IO and SSL should be used polymorphically,
# IO::WaitWritable should be rescued too.
# See the document of OpenSSL::Buffering#read_nonblock for sample code.
# 
# Note that this method is identical to readpartial
# except the non-blocking flag is set.
def read_nonblock(maxlen); ''; end
##
# Writes the given string to <em>ios</em> using
# the write(2) system call after O_NONBLOCK is set for
# the underlying file descriptor.
# 
# It returns the number of bytes written.
# 
# write_nonblock just calls the write(2) system call.
# It causes all errors the write(2) system call causes: Errno::EWOULDBLOCK, Errno::EINTR, etc.
# The result may also be smaller than string.length (partial write).
# The caller should care such errors and partial write.
# 
# If the exception is Errno::EWOULDBLOCK or Errno::AGAIN,
# it is extended by IO::WaitWritable.
# So IO::WaitWritable can be used to rescue the exceptions for retrying write_nonblock.
# 
#   # Creates a pipe.
#   r, w = IO.pipe
# 
#   # write_nonblock writes only 65536 bytes and return 65536.
#   # (The pipe size is 65536 bytes on this environment.)
#   s = "a" * 100000
#   p w.write_nonblock(s)     #=> 65536
# 
#   # write_nonblock cannot write a byte and raise EWOULDBLOCK (EAGAIN).
#   p w.write_nonblock("b")   # Resource temporarily unavailable (Errno::EAGAIN)
# 
# If the write buffer is not empty, it is flushed at first.
# 
# When write_nonblock raises an exception kind of IO::WaitWritable,
# write_nonblock should not be called
# until io is writable for avoiding busy loop.
# This can be done as follows.
# 
#   begin
#     result = io.write_nonblock(string)
#   rescue IO::WaitWritable, Errno::EINTR
#     IO.select(nil, [io])
#     retry
#   end
# 
# Note that this doesn't guarantee to write all data in string.
# The length written is reported as result and it should be checked later.
# 
# On some platforms such as Windows, write_nonblock is not supported
# according to the kind of the IO object.
# In such cases, write_nonblock raises <code>Errno::EBADF</code>.
def write_nonblock(string); 0; end
##
# Reads at most <i>maxlen</i> bytes from the I/O stream.
# It blocks only if <em>ios</em> has no data immediately available.
# It doesn't block if some data available.
# If the optional <i>outbuf</i> argument is present,
# it must reference a String, which will receive the data.
# The <i>outbuf</i> will contain only the received data after the method call
# even if it is not empty at the beginning.
# It raises <code>EOFError</code> on end of file.
# 
# readpartial is designed for streams such as pipe, socket, tty, etc.
# It blocks only when no data immediately available.
# This means that it blocks only when following all conditions hold.
# * the byte buffer in the IO object is empty.
# * the content of the stream is empty.
# * the stream is not reached to EOF.
# 
# When readpartial blocks, it waits data or EOF on the stream.
# If some data is reached, readpartial returns with the data.
# If EOF is reached, readpartial raises EOFError.
# 
# When readpartial doesn't blocks, it returns or raises immediately.
# If the byte buffer is not empty, it returns the data in the buffer.
# Otherwise if the stream has some content,
# it returns the data in the stream.
# Otherwise if the stream is reached to EOF, it raises EOFError.
# 
#    r, w = IO.pipe           #               buffer          pipe content
#    w << "abc"               #               ""              "abc".
#    r.readpartial(4096)      #=> "abc"       ""              ""
#    r.readpartial(4096)      # blocks because buffer and pipe is empty.
# 
#    r, w = IO.pipe           #               buffer          pipe content
#    w << "abc"               #               ""              "abc"
#    w.close                  #               ""              "abc" EOF
#    r.readpartial(4096)      #=> "abc"       ""              EOF
#    r.readpartial(4096)      # raises EOFError
# 
#    r, w = IO.pipe           #               buffer          pipe content
#    w << "abc\ndef\n"        #               ""              "abc\ndef\n"
#    r.gets                   #=> "abc\n"     "def\n"         ""
#    w << "ghi\n"             #               "def\n"         "ghi\n"
#    r.readpartial(4096)      #=> "def\n"     ""              "ghi\n"
#    r.readpartial(4096)      #=> "ghi\n"     ""              ""
# 
# Note that readpartial behaves similar to sysread.
# The differences are:
# * If the byte buffer is not empty, read from the byte buffer instead of "sysread for buffered IO (IOError)".
# * It doesn't cause Errno::EWOULDBLOCK and Errno::EINTR.  When readpartial meets EWOULDBLOCK and EINTR by read system call, readpartial retry the system call.
# 
# The later means that readpartial is nonblocking-flag insensitive.
# It blocks on the situation IO#sysread causes Errno::EWOULDBLOCK as if the fd is blocking mode.
def readpartial(maxlen); ''; end
##
# Reads the next ``line'' from the I/O stream; lines are separated by
# <i>sep</i>. A separator of <code>nil</code> reads the entire
# contents, and a zero-length separator reads the input a paragraph at
# a time (two successive newlines in the input separate paragraphs).
# The stream must be opened for reading or an <code>IOError</code>
# will be raised. The line read in will be returned and also assigned
# to <code>$_</code>. Returns <code>nil</code> if called at end of
# file.  If the first argument is an integer, or optional second
# argument is given, the returning string would not be longer than the
# given value in bytes.
# 
#    File.new("testfile").gets   #=> "This is line one\n"
#    $_                          #=> "This is line one\n"
def gets(sep=$/); '' || nil; end
##
# Reads a line as with <code>IO#gets</code>, but raises an
# <code>EOFError</code> on end of file.
def readline(sep=$/); ''; end
##
# Reads a one-character string from <em>ios</em>. Returns
# <code>nil</code> if called at end of file.
# 
#    f = File.new("testfile")
#    f.getc   #=> "h"
#    f.getc   #=> "e"
def getc; '' || nil; end
##
# Gets the next 8-bit byte (0..255) from <em>ios</em>. Returns
# <code>nil</code> if called at end of file.
# 
#    f = File.new("testfile")
#    f.getbyte   #=> 84
#    f.getbyte   #=> 104
def getbyte; 1 || nil; end
##
# Reads a one-character string from <em>ios</em>. Raises an
# <code>EOFError</code> on end of file.
# 
#    f = File.new("testfile")
#    f.readchar   #=> "h"
#    f.readchar   #=> "e"
def readchar; ''; end
##
# Reads a byte as with <code>IO#getbyte</code>, but raises an
# <code>EOFError</code> on end of file.
def readbyte; 0; end
##
# Pushes back bytes (passed as a parameter) onto <em>ios</em>,
# such that a subsequent buffered read will return it. Only one byte
# may be pushed back before a subsequent read operation (that is,
# you will be able to read only the last of several bytes that have been pushed
# back). Has no effect with unbuffered reads (such as <code>IO#sysread</code>).
# 
#    f = File.new("testfile")   #=> #<File:testfile>
#    b = f.getbyte              #=> 0x38
#    f.ungetbyte(b)             #=> nil
#    f.getbyte                  #=> 0x38
def ungetbyte(string); end
##
# Pushes back one character (passed as a parameter) onto <em>ios</em>,
# such that a subsequent buffered character read will return it. Only one character
# may be pushed back before a subsequent read operation (that is,
# you will be able to read only the last of several characters that have been pushed
# back). Has no effect with unbuffered reads (such as <code>IO#sysread</code>).
# 
#    f = File.new("testfile")   #=> #<File:testfile>
#    c = f.getc                 #=> "8"
#    f.ungetc(c)                #=> nil
#    f.getc                     #=> "8"
def ungetc(string); end
##
# String Output---Writes <i>obj</i> to <em>ios</em>.
# <i>obj</i> will be converted to a string using
# <code>to_s</code>.
# 
#    $stdout << "Hello " << "world!\n"
# 
# <em>produces:</em>
# 
#    Hello world!
def <<; IO.new; end
##
# Flushes any buffered data within <em>ios</em> to the underlying
# operating system (note that this is Ruby internal buffering only;
# the OS may buffer the data as well).
# 
#    $stdout.print "no newline"
#    $stdout.flush
# 
# <em>produces:</em>
# 
#    no newline
def flush; IO.new; end
##
# Returns the current offset (in bytes) of <em>ios</em>.
# 
#    f = File.new("testfile")
#    f.pos    #=> 0
#    f.gets   #=> "This is line one\n"
#    f.pos    #=> 17
def pos; 0; end
##
# Returns the current offset (in bytes) of <em>ios</em>.
# 
#    f = File.new("testfile")
#    f.pos    #=> 0
#    f.gets   #=> "This is line one\n"
#    f.pos    #=> 17
def tell; 0; end
##
# Seeks to a given offset <i>anInteger</i> in the stream according to
# the value of <i>whence</i>:
# 
#   IO::SEEK_CUR  | Seeks to _amount_ plus current position
#   --------------+----------------------------------------------------
#   IO::SEEK_END  | Seeks to _amount_ plus end of stream (you probably
#                 | want a negative value for _amount_)
#   --------------+----------------------------------------------------
#   IO::SEEK_SET  | Seeks to the absolute location given by _amount_
# 
# Example:
# 
#    f = File.new("testfile")
#    f.seek(-13, IO::SEEK_END)   #=> 0
#    f.readline                  #=> "And so on...\n"
def seek(amount, whence=IO::SEEK_SET); 0; end
##
# Positions <em>ios</em> to the beginning of input, resetting
# <code>lineno</code> to zero.
# 
#    f = File.new("testfile")
#    f.readline   #=> "This is line one\n"
#    f.rewind     #=> 0
#    f.lineno     #=> 0
#    f.readline   #=> "This is line one\n"
# 
# Note that it cannot be used with streams such as pipes, ttys, and sockets.
def rewind; 0; end
##
# Seeks to the given position (in bytes) in <em>ios</em>.
# It is not guranteed that seeking to the right position when <em>ios</em>
# is textmode.
# 
#    f = File.new("testfile")
#    f.pos = 17
#    f.gets   #=> "This is line two\n"
def pos= integer; 0; end
##
# Returns true if <em>ios</em> is at end of file that means
# there are no more data to read.
# The stream must be opened for reading or an <code>IOError</code> will be
# raised.
# 
#    f = File.new("testfile")
#    dummy = f.readlines
#    f.eof   #=> true
# 
# If <em>ios</em> is a stream such as pipe or socket, <code>IO#eof?</code>
# blocks until the other end sends some data or closes it.
# 
#    r, w = IO.pipe
#    Thread.new { sleep 1; w.close }
#    r.eof?  #=> true after 1 second blocking
# 
#    r, w = IO.pipe
#    Thread.new { sleep 1; w.puts "a" }
#    r.eof?  #=> false after 1 second blocking
# 
#    r, w = IO.pipe
#    r.eof?  # blocks forever
# 
# Note that <code>IO#eof?</code> reads data to the input byte buffer.
# So <code>IO#sysread</code> may not behave as you intend with
# <code>IO#eof?</code>, unless you call <code>IO#rewind</code>
# first (which is not available for some streams).
def eof; true || false; end
##
# Returns true if <em>ios</em> is at end of file that means
# there are no more data to read.
# The stream must be opened for reading or an <code>IOError</code> will be
# raised.
# 
#    f = File.new("testfile")
#    dummy = f.readlines
#    f.eof   #=> true
# 
# If <em>ios</em> is a stream such as pipe or socket, <code>IO#eof?</code>
# blocks until the other end sends some data or closes it.
# 
#    r, w = IO.pipe
#    Thread.new { sleep 1; w.close }
#    r.eof?  #=> true after 1 second blocking
# 
#    r, w = IO.pipe
#    Thread.new { sleep 1; w.puts "a" }
#    r.eof?  #=> false after 1 second blocking
# 
#    r, w = IO.pipe
#    r.eof?  # blocks forever
# 
# Note that <code>IO#eof?</code> reads data to the input byte buffer.
# So <code>IO#sysread</code> may not behave as you intend with
# <code>IO#eof?</code>, unless you call <code>IO#rewind</code>
# first (which is not available for some streams).
def eof?; true || false; end
##
# Returns <code>true</code> if <em>ios</em> will be closed on exec.
# 
#    f = open("/dev/null")
#    f.close_on_exec?                 #=> false
#    f.close_on_exec = true
#    f.close_on_exec?                 #=> true
#    f.close_on_exec = false
#    f.close_on_exec?                 #=> false
def close_on_exec?; true || false; end
##
# Sets a close-on-exec flag.
# 
#    f = open("/dev/null")
#    f.close_on_exec = true
#    system("cat", "/proc/self/fd/#{f.fileno}") # cat: /proc/self/fd/3: No such file or directory
#    f.closed?                #=> false
# 
# Ruby sets close-on-exec flags of all file descriptors by default
# since Ruby 2.0.0.
# So you don't need to set by yourself.
# Also, unsetting a close-on-exec flag can cause file descriptor leak
# if another thread use fork() and exec() (via system() method for example).
# If you really needs file descriptor inheritance to child process,
# use spawn()'s argument such as fd=>fd.
def close_on_exec= bool; true || false; end
##
# Closes <em>ios</em> and flushes any pending writes to the operating
# system. The stream is unavailable for any further data operations;
# an <code>IOError</code> is raised if such an attempt is made. I/O
# streams are automatically closed when they are claimed by the
# garbage collector.
# 
# If <em>ios</em> is opened by <code>IO.popen</code>,
# <code>close</code> sets <code>$?</code>.
def close; end
##
# Returns <code>true</code> if <em>ios</em> is completely closed (for
# duplex streams, both reader and writer), <code>false</code>
# otherwise.
# 
#    f = File.new("testfile")
#    f.close         #=> nil
#    f.closed?       #=> true
#    f = IO.popen("/bin/sh","r+")
#    f.close_write   #=> nil
#    f.closed?       #=> false
#    f.close_read    #=> nil
#    f.closed?       #=> true
def closed?; true || false; end
##
# Closes the read end of a duplex I/O stream (i.e., one that contains
# both a read and a write stream, such as a pipe). Will raise an
# <code>IOError</code> if the stream is not duplexed.
# 
#    f = IO.popen("/bin/sh","r+")
#    f.close_read
#    f.readlines
# 
# <em>produces:</em>
# 
#    prog.rb:3:in `readlines': not opened for reading (IOError)
#     from prog.rb:3
def close_read; end
##
# Closes the write end of a duplex I/O stream (i.e., one that contains
# both a read and a write stream, such as a pipe). Will raise an
# <code>IOError</code> if the stream is not duplexed.
# 
#    f = IO.popen("/bin/sh","r+")
#    f.close_write
#    f.print "nowhere"
# 
# <em>produces:</em>
# 
#    prog.rb:3:in `write': not opened for writing (IOError)
#     from prog.rb:3:in `print'
#     from prog.rb:3
def close_write; end
##
# Returns <code>true</code> if <em>ios</em> is associated with a
# terminal device (tty), <code>false</code> otherwise.
# 
#    File.new("testfile").isatty   #=> false
#    File.new("/dev/tty").isatty   #=> true
def isatty; true || false; end
##
# Returns <code>true</code> if <em>ios</em> is associated with a
# terminal device (tty), <code>false</code> otherwise.
# 
#    File.new("testfile").isatty   #=> false
#    File.new("/dev/tty").isatty   #=> true
def tty?; true || false; end
##
# Puts <em>ios</em> into binary mode.
# Once a stream is in binary mode, it cannot be reset to nonbinary mode.
# 
# - newline conversion disabled
# - encoding conversion disabled
# - content is treated as ASCII-8BIT
def binmode; IO.new; end
##
# Returns <code>true</code> if <em>ios</em> is binmode.
def binmode?; true || false; end
##
# Seeks to a given <i>offset</i> in the stream according to the value
# of <i>whence</i> (see <code>IO#seek</code> for values of
# <i>whence</i>). Returns the new offset into the file.
# 
#    f = File.new("testfile")
#    f.sysseek(-13, IO::SEEK_END)   #=> 53
#    f.sysread(10)                  #=> "And so on."
def sysseek(offset, whence=IO::SEEK_SET); 0; end
##
#  Announce an intention to access data from the current file in a
#  specific pattern. On platforms that do not support the
#  <em>posix_fadvise(2)</em> system call, this method is a no-op.
# 
# _advice_ is one of the following symbols:
# 
#  * :normal - No advice to give; the default assumption for an open file.
#  * :sequential - The data will be accessed sequentially:
#     with lower offsets read before higher ones.
#  * :random - The data will be accessed in random order.
#  * :willneed - The data will be accessed in the near future.
#  * :dontneed - The data will not be accessed in the near future.
#  * :noreuse - The data will only be accessed once.
# 
# The semantics of a piece of advice are platform-dependent. See
# <em>man 2 posix_fadvise</em> for details.
# 
#  "data" means the region of the current file that begins at
#  _offset_ and extends for _len_ bytes. If _len_ is 0, the region
#  ends at the last byte of the file. By default, both _offset_ and
#  _len_ are 0, meaning that the advice applies to the entire file.
# 
#  If an error occurs, one of the following exceptions will be raised:
# 
#  * <code>IOError</code> - The <code>IO</code> stream is closed.
#  * <code>Errno::EBADF</code> - The file descriptor of the current file is
#    invalid.
#  * <code>Errno::EINVAL</code> - An invalid value for _advice_ was given.
#  * <code>Errno::ESPIPE</code> - The file descriptor of the current
#  * file refers to a FIFO or pipe. (Linux raises <code>Errno::EINVAL</code>
#  * in this case).
#  * <code>TypeError</code> - Either _advice_ was not a Symbol, or one of the
#    other arguments was not an <code>Integer</code>.
#  * <code>RangeError</code> - One of the arguments given was too big/small.
# 
# This list is not exhaustive; other Errno:: exceptions are also possible.
def advise(advice, offset=0, len=0); end
##
# Provides a mechanism for issuing low-level commands to control or
# query I/O devices. Arguments and results are platform dependent. If
# <i>arg</i> is a number, its value is passed directly. If it is a
# string, it is interpreted as a binary sequence of bytes. On Unix
# platforms, see <code>ioctl(2)</code> for details. Not implemented on
# all platforms.
def ioctl(integer_cmd, arg); 0; end
##
# Provides a mechanism for issuing low-level commands to control or
# query file-oriented I/O streams. Arguments and results are platform
# dependent. If <i>arg</i> is a number, its value is passed
# directly. If it is a string, it is interpreted as a binary sequence
# of bytes (<code>Array#pack</code> might be a useful way to build this
# string). On Unix platforms, see <code>fcntl(2)</code> for details.
# Not implemented on all platforms.
def fcntl(integer_cmd, arg); 0; end
##
# Returns the process ID of a child process associated with
# <em>ios</em>. This will be set by <code>IO.popen</code>.
# 
#    pipe = IO.popen("-")
#    if pipe
#      $stderr.puts "In parent, child pid is #{pipe.pid}"
#    else
#      $stderr.puts "In child, pid is #{$$}"
#    end
# 
# <em>produces:</em>
# 
#    In child, pid is 26209
#    In parent, child pid is 26209
def pid; 0; end
##
# Return a string describing this IO object.
def inspect; ''; end
##
# Returns the Encoding object that represents the encoding of the file.
# If io is write mode and no encoding is specified, returns <code>nil</code>.
def external_encoding; Encoding.new; end
##
# Returns the Encoding of the internal string if conversion is
# specified.  Otherwise returns nil.
def internal_encoding; Encoding.new; end
##
# If single argument is specified, read string from io is tagged
# with the encoding specified.  If encoding is a colon separated two
# encoding names "A:B", the read string is converted from encoding A
# (external encoding) to encoding B (internal encoding), then tagged
# with B.  If two arguments are specified, those must be encoding
# objects or encoding names, and the first one is the external encoding, and the
# second one is the internal encoding.
# If the external encoding and the internal encoding is specified,
# optional hash argument specify the conversion option.
def set_encoding(ext_enc); IO.new; end
##
# Returns +true+ if the underlying file descriptor of _ios_ will be
# closed automatically at its finalization, otherwise +false+.
def autoclose?; true || false; end
##
# Sets auto-close flag.
# 
#    f = open("/dev/null")
#    IO.for_fd(f.fileno)
#    # ...
#    f.gets # may cause IOError
# 
#    f = open("/dev/null")
#    IO.for_fd(f.fileno).autoclose = true
#    # ...
#    f.gets # won't cause IOError
def autoclose= bool; true || false; end
end

##
# A class that provides the functionality of Kernel#set_trace_func in a
# nice Object-Oriented API.
# 
# == Example
# 
# We can use TracePoint to gather information specifically for exceptions:
# 
#      trace = TracePoint.new(:raise) do |tp|
#          p [tp.lineno, tp.event, tp.raised_exception]
#      end
#      #=> #<TracePoint:0x007f786a452448>
# 
#      trace.enable
#      #=> #<TracePoint:0x007f786a452448>
# 
#      0 / 0
#      #=> [5, :raise, #<ZeroDivisionError: divided by 0>]
# 
# == Events
# 
# If you don't specify the type of events you want to listen for,
# TracePoint will include all available events.
# 
# *Note* do not depend on current event set, as this list is subject to
# change. Instead, it is recommended you specify the type of events you
# want to use.
# 
# To filter what is traced, you can pass any of the following as +events+:
# 
# +:line+:: execute code on a new line
# +:class+:: start a class or module definition
# +:end+:: finish a class or module definition
# +:call+:: call a Ruby method
# +:return+:: return from a Ruby method
# +:c_call+:: call a C-language routine
# +:c_return+:: return from a C-language routine
# +:raise+:: raise an exception
# +:b_call+:: event hook at block entry
# +:b_return+:: event hook at block ending
# +:thread_begin+:: event hook at thread beginning
# +:thread_end+:: event hook at thread ending
class TracePoint < Object
##
# Returns a new TracePoint object, not enabled by default.
# 
# Next, in order to activate the trace, you must use TracePoint.enable
# 
#      trace = TracePoint.new(:call) do |tp|
#          p [tp.lineno, tp.defined_class, tp.method_id, tp.event]
#      end
#      #=> #<TracePoint:0x007f17372cdb20>
# 
#      trace.enable
#      #=> #<TracePoint:0x007f17372cdb20>
# 
#      puts "Hello, TracePoint!"
#      # ...
#      # [48, IRB::Notifier::AbstractNotifier, :printf, :call]
#      # ...
# 
# When you want to deactivate the trace, you must use TracePoint.disable
# 
#      trace.disable
# 
# See TracePoint@Events for possible events and more information.
# 
# A block must be given, otherwise a ThreadError is raised.
# 
# If the trace method isn't included in the given events filter, a
# RuntimeError is raised.
# 
#      TracePoint.trace(:line) do |tp|
#          p tp.raised_exception
#      end
#      #=> RuntimeError: 'raised_exception' not supported by this event
# 
# If the trace method is called outside block, a RuntimeError is raised.
# 
#      TracePoint.trace(:line) do |tp|
#        $tp = tp
#      end
#      $tp.line #=> access from outside (RuntimeError)
# 
# Access from other threads is also forbidden.
def self.new(); end
##
# A convenience method for TracePoint.new, that activates the trace
# automatically.
# 
#     trace = TracePoint.trace(:call) { |tp| [tp.lineno, tp.event] }
#     #=> #<TracePoint:0x007f786a452448>
# 
#     trace.enabled? #=> true
def self.trace(); Object.new; end
##
# Activates the trace
# 
# Return true if trace was enabled.
# Return false if trace was disabled.
# 
#      trace.enabled?  #=> false
#      trace.enable    #=> false (previous state)
#                      #   trace is enabled
#      trace.enabled?  #=> true
#      trace.enable    #=> true (previous state)
#                      #   trace is still enabled
# 
# If a block is given, the trace will only be enabled within the scope of the
# block.
# 
#      trace.enabled?
#      #=> false
# 
#      trace.enable do
#          trace.enabled?
#          # only enabled for this block
#      end
# 
#      trace.enabled?
#      #=> false
# 
# Note: You cannot access event hooks within the block.
# 
#      trace.enable { p tp.lineno }
#      #=> RuntimeError: access from outside
def enable; Object.new; end
##
# Deactivates the trace
# 
# Return true if trace was enabled.
# Return false if trace was disabled.
# 
#      trace.enabled?       #=> true
#      trace.disable        #=> false (previous status)
#      trace.enabled?       #=> false
#      trace.disable        #=> false
# 
# If a block is given, the trace will only be disable within the scope of the
# block.
# 
#      trace.enabled?
#      #=> true
# 
#      trace.disable do
#          trace.enabled?
#          # only disabled for this block
#      end
# 
#      trace.enabled?
#      #=> true
# 
# Note: You cannot access event hooks within the block.
# 
#      trace.disable { p tp.lineno }
#      #=> RuntimeError: access from outside
def disable; Object.new; end
##
# The current status of the trace
def enabled?; true || false; end
##
# Return a string containing a human-readable TracePoint
# status.
def inspect; ''; end
end

##
# Arrays are ordered, integer-indexed collections of any object.
# 
# Array indexing starts at 0, as in C or Java.  A negative index is assumed
# to be relative to the end of the array---that is, an index of -1 indicates
# the last element of the array, -2 is the next to last element in the
# array, and so on.
# 
# == Creating Arrays
# 
# A new array can be created by using the literal constructor
# <code>[]</code>.  Arrays can contain different types of objects.  For
# example, the array below contains an Integer, a String and a Float:
# 
#    ary = [1, "two", 3.0] #=> [1, "two", 3.0]
# 
# An array can also be created by explicitly calling Array.new with zero, one
# (the initial size of the Array) or two arguments (the initial size and a
# default object).
# 
#    ary = Array.new    #=> []
#    Array.new(3)       #=> [nil, nil, nil]
#    Array.new(3, true) #=> [0, 0, 0]
# 
# Note that the second argument populates the array with references to the
# same object.  Therefore, it is only recommended in cases when you need to
# instantiate arrays with natively immutable objects such as Symbols,
# numbers, true or false.
# 
# To create an array with separate objects a block can be passed instead.
# This method is safe to use with mutable objects such as hashes, strings or
# other arrays:
# 
#    Array.new(4) { Hash.new } #=> [{}, {}, {}, {}]
# 
# This is also a quick way to build up multi-dimensional arrays:
# 
#    empty_table = Array.new(3) { Array.new(3) }
#    #=> [[nil, nil, nil], [nil, nil, nil], [nil, nil, nil]]
# 
# An array can also be created by using the Array() method, provided by
# Kernel, which tries to call #to_ary, then #to_a on its argument.
# 
#     Array({:a => "a", :b => "b"}) #=> [[:a, "a"], [:b, "b"]]
# 
# == Example Usage
# 
# In addition to the methods it mixes in through the Enumerable module, the
# Array class has proprietary methods for accessing, searching and otherwise
# manipulating arrays.
# 
# Some of the more common ones are illustrated below.
# 
# == Accessing Elements
# 
# Elements in an array can be retrieved using the Array#[] method.  It can
# take a single integer argument (a numeric index), a pair of arguments
# (start and length) or a range.
# 
#    arr = [1, 2, 3, 4, 5, 6]
#    arr[2]    #=> 3
#    arr[100]  #=> nil
#    arr[-3]   #=> 4
#    arr[2, 3] #=> [3, 4, 5]
#    arr[1..4] #=> [2, 3, 4, 5]
# 
# Another way to access a particular array element is by using the #at method
# 
#    arr.at(0) #=> 1
# 
# The #slice method works in an identical manner to Array#[].
# 
# To raise an error for indices outside of the array bounds or else to
# provide a default value when that happens, you can use #fetch.
# 
#    arr = ['a', 'b', 'c', 'd', 'e', 'f']
#    arr.fetch(100) #=> IndexError: index 100 outside of array bounds: -6...6
#    arr.fetch(100, "oops") #=> "oops"
# 
# The special methods #first and #last will return the first and last
# elements of an array, respectively.
# 
#    arr.first #=> 1
#    arr.last  #=> 6
# 
# To return the first +n+ elements of an array, use #take
# 
#    arr.take(3) #=> [1, 2, 3]
# 
# #drop does the opposite of #take, by returning the elements after +n+
# elements have been dropped:
# 
#    arr.drop(3) #=> [4, 5, 6]
# 
# == Obtaining Information about an Array
# 
# Arrays keep track of their own length at all times.  To query an array
# about the number of elements it contains, use #length, #count or #size.
# 
#   browsers = ['Chrome', 'Firefox', 'Safari', 'Opera', 'IE']
#   browsers.length #=> 5
#   browsers.count #=> 5
# 
# To check whether an array contains any elements at all
# 
#   browsers.empty? #=> false
# 
# To check whether a particular item is included in the array
# 
#   browsers.include?('Konqueror') #=> false
# 
# == Adding Items to Arrays
# 
# Items can be added to the end of an array by using either #push or #<<
# 
#   arr = [1, 2, 3, 4]
#   arr.push(5) #=> [1, 2, 3, 4, 5]
#   arr << 6    #=> [1, 2, 3, 4, 5, 6]
# 
# #unshift will add a new item to the beginning of an array.
# 
#    arr.unshift(0) #=> [0, 1, 2, 3, 4, 5, 6]
# 
# With #insert you can add a new element to an array at any position.
# 
#    arr.insert(3, 'apple')  #=> [0, 1, 2, 'apple', 3, 4, 5, 6]
# 
# Using the #insert method, you can also insert multiple values at once:
# 
#    arr.insert(3, 'orange', 'pear', 'grapefruit')
#    #=> [0, 1, 2, "orange", "pear", "grapefruit", "apple", 3, 4, 5, 6]
# 
# == Removing Items from an Array
# 
# The method #pop removes the last element in an array and returns it:
# 
#    arr =  [1, 2, 3, 4, 5, 6]
#    arr.pop #=> 6
#    arr #=> [1, 2, 3, 4, 5]
# 
# To retrieve and at the same time remove the first item, use #shift:
# 
#    arr.shift #=> 1
#    arr #=> [2, 3, 4, 5]
# 
# To delete an element at a particular index:
# 
#    arr.delete_at(2) #=> 4
#    arr #=> [2, 3, 5]
# 
# To delete a particular element anywhere in an array, use #delete:
# 
#    arr = [1, 2, 2, 3]
#    arr.delete(2) #=> [1, 3]
# 
# A useful method if you need to remove +nil+ values from an array is
# #compact:
# 
#    arr = ['foo', 0, nil, 'bar', 7, 'baz', nil]
#    arr.compact  #=> ['foo', 0, 'bar', 7, 'baz']
#    arr          #=> ['foo', 0, nil, 'bar', 7, 'baz', nil]
#    arr.compact! #=> ['foo', 0, 'bar', 7, 'baz']
#    arr          #=> ['foo', 0, 'bar', 7, 'baz']
# 
# Another common need is to remove duplicate elements from an array.
# 
# It has the non-destructive #uniq, and destructive method #uniq!
# 
#    arr = [2, 5, 6, 556, 6, 6, 8, 9, 0, 123, 556]
#    arr.uniq #=> [2, 5, 6, 556, 8, 9, 0, 123]
# 
# == Iterating over Arrays
# 
# Like all classes that include the Enumerable module, Array has an each
# method, which defines what elements should be iterated over and how.  In
# case of Array's #each, all elements in the Array instance are yielded to
# the supplied block in sequence.
# 
# Note that this operation leaves the array unchanged.
# 
#    arr = [1, 2, 3, 4, 5]
#    arr.each { |a| print a -= 10, " " }
#    # prints: -9 -8 -7 -6 -5
#    #=> [1, 2, 3, 4, 5]
# 
# Another sometimes useful iterator is #reverse_each which will iterate over
# the elements in the array in reverse order.
# 
#    words = %w[rats live on no evil star]
#    str = ""
#    words.reverse_each { |word| str += "#{word.reverse} " }
#    str #=> "rats live on no evil star "
# 
# The #map method can be used to create a new array based on the original
# array, but with the values modified by the supplied block:
# 
#    arr.map { |a| 2*a }   #=> [2, 4, 6, 8, 10]
#    arr                   #=> [1, 2, 3, 4, 5]
#    arr.map! { |a| a**2 } #=> [1, 4, 9, 16, 25]
#    arr                   #=> [1, 4, 9, 16, 25]
# 
# == Selecting Items from an Array
# 
# Elements can be selected from an array according to criteria defined in a
# block.  The selection can happen in a destructive or a non-destructive
# manner.  While the destructive operations will modify the array they were
# called on, the non-destructive methods usually return a new array with the
# selected elements, but leave the original array unchanged.
# 
# === Non-destructive Selection
# 
#    arr = [1, 2, 3, 4, 5, 6]
#    arr.select { |a| a > 3 }     #=> [4, 5, 6]
#    arr.reject { |a| a < 3 }     #=> [4, 5, 6]
#    arr.drop_while { |a| a < 4 } #=> [4, 5, 6]
#    arr                          #=> [1, 2, 3, 4, 5, 6]
# 
# === Destructive Selection
# 
# #select! and #reject! are the corresponding destructive methods to #select
# and #reject
# 
# Similar to #select vs. #reject, #delete_if and #keep_if have the exact
# opposite result when supplied with the same block:
# 
#    arr.delete_if { |a| a < 4 } #=> [4, 5, 6]
#    arr                         #=> [4, 5, 6]
# 
#    arr = [1, 2, 3, 4, 5, 6]
#    arr.keep_if { |a| a < 4 } #=> [1, 2, 3]
#    arr                       #=> [1, 2, 3]
class Array < Object
include Enumerable
##
# Tries to convert +obj+ into an array, using +to_ary+ method.  Returns the
# converted array or +nil+ if +obj+ cannot be converted for any reason.
# This method can be used to check if an argument is an array.
# 
#    Array.try_convert([1])   #=> [1]
#    Array.try_convert("1")   #=> nil
# 
#    if tmp = Array.try_convert(arg)
#      # the argument is an array
#    elsif tmp = String.try_convert(arg)
#      # the argument is a string
#    end
def self.try_convert(obj); [] || nil; end
##
# Returns a new array.
# 
# In the first form, if no arguments are sent, the new array will be empty.
# When a +size+ and an optional +obj+ are sent, an array is created with
# +size+ copies of +obj+.  Take notice that all elements will reference the
# same object +obj+.
# 
# The second form creates a copy of the array passed as a parameter (the
# array is generated by calling to_ary on the parameter).
# 
#   first_array = ["Matz", "Guido"]
# 
#   second_array = Array.new(first_array) #=> ["Matz", "Guido"]
# 
#   first_array.equal? second_array       #=> false
# 
# In the last form, an array of the given size is created.  Each element in
# this array is created by passing the element's index to the given block
# and storing the return value.
# 
#   Array.new(3){ |index| index ** 2 }
#   # => [0, 1, 4]
# 
# == Common gotchas
# 
# When sending the second parameter, the same object will be used as the
# value for all the array elements:
# 
#    a = Array.new(2, Hash.new)
#    # => [{}, {}]
# 
#    a[0]['cat'] = 'feline'
#    a # => [{"cat"=>"feline"}, {"cat"=>"feline"}]
# 
#    a[1]['cat'] = 'Felix'
#    a # => [{"cat"=>"Felix"}, {"cat"=>"Felix"}]
# 
# Since all the Array elements store the same hash, changes to one of them
# will affect them all.
# 
# If multiple copies are what you want, you should use the block
# version which uses the result of that block each time an element
# of the array needs to be initialized:
# 
#    a = Array.new(2) { Hash.new }
#    a[0]['cat'] = 'feline'
#    a # => [{"cat"=>"feline"}, {}]
def self.new(size=0, obj=null); end
##
# Replaces the contents of +self+ with the contents of +other_ary+,
# truncating or expanding if necessary.
# 
#    a = [ "a", "b", "c", "d", "e" ]
#    a.replace([ "x", "y", "z" ])   #=> ["x", "y", "z"]
#    a                              #=> ["x", "y", "z"]
def replace(other_ary); []; end
##
# Creates a string representation of +self+.
# 
#    [ "a", "b", "c" ].to_s     #=> "[\"a\", \"b\", \"c\"]"
def inspect; ''; end
##
# Creates a string representation of +self+.
# 
#    [ "a", "b", "c" ].to_s     #=> "[\"a\", \"b\", \"c\"]"
def to_s; ''; end
##
# Returns +self+.
# 
# If called on a subclass of Array, converts the receiver to an Array object.
def to_a; []; end
##
# Returns +self+.
def to_ary; []; end
##
# Return +true+ if this array is frozen (or temporarily frozen
# while being sorted). See also Object#frozen?
def frozen?; true || false; end
##
# Equality --- Two arrays are equal if they contain the same number of
# elements and if each element is equal to (according to Object#==) the
# corresponding element in +other_ary+.
# 
#    [ "a", "c" ]    == [ "a", "c", 7 ]     #=> false
#    [ "a", "c", 7 ] == [ "a", "c", 7 ]     #=> true
#    [ "a", "c", 7 ] == [ "a", "d", "f" ]   #=> false
def ==; true || false; end
##
# Returns +true+ if +self+ and +other+ are the same object,
# or are both arrays with the same content.
def eql?(other); true || false; end
##
# Compute a hash-code for this array.
# 
# Two arrays with the same content will have the same hash code (and will
# compare using #eql?).
def hash; 0; end
##
# Element Reference --- Returns the element at +index+, or returns a
# subarray starting at the +start+ index and continuing for +length+
# elements, or returns a subarray specified by +range+ of indices.
# 
# Negative indices count backward from the end of the array (-1 is the last
# element).  For +start+ and +range+ cases the starting index is just before
# an element.  Additionally, an empty array is returned when the starting
# index for an element range is at the end of the array.
# 
# Returns +nil+ if the index (or starting index) are out of range.
# 
#    a = [ "a", "b", "c", "d", "e" ]
#    a[2] +  a[0] + a[1]    #=> "cab"
#    a[6]                   #=> nil
#    a[1, 2]                #=> [ "b", "c" ]
#    a[1..3]                #=> [ "b", "c", "d" ]
#    a[4..7]                #=> [ "e" ]
#    a[6..10]               #=> nil
#    a[-3, 3]               #=> [ "c", "d", "e" ]
#    # special cases
#    a[5]                   #=> nil
#    a[6, 1]                #=> nil
#    a[5, 1]                #=> []
#    a[5..10]               #=> []
def []; [] || nil; end
##
# Element Reference --- Returns the element at +index+, or returns a
# subarray starting at the +start+ index and continuing for +length+
# elements, or returns a subarray specified by +range+ of indices.
# 
# Negative indices count backward from the end of the array (-1 is the last
# element).  For +start+ and +range+ cases the starting index is just before
# an element.  Additionally, an empty array is returned when the starting
# index for an element range is at the end of the array.
# 
# Returns +nil+ if the index (or starting index) are out of range.
# 
#    a = [ "a", "b", "c", "d", "e" ]
#    a[2] +  a[0] + a[1]    #=> "cab"
#    a[6]                   #=> nil
#    a[1, 2]                #=> [ "b", "c" ]
#    a[1..3]                #=> [ "b", "c", "d" ]
#    a[4..7]                #=> [ "e" ]
#    a[6..10]               #=> nil
#    a[-3, 3]               #=> [ "c", "d", "e" ]
#    # special cases
#    a[5]                   #=> nil
#    a[6, 1]                #=> nil
#    a[5, 1]                #=> []
#    a[5..10]               #=> []
def slice(index); [] || nil; end
##
# Element Assignment --- Sets the element at +index+, or replaces a subarray
# from the +start+ index for +length+ elements, or replaces a subarray
# specified by the +range+ of indices.
# 
# If indices are greater than the current capacity of the array, the array
# grows automatically.  Elements are inserted into the array at +start+ if
# +length+ is zero.
# 
# Negative indices will count backward from the end of the array.  For
# +start+ and +range+ cases the starting index is just before an element.
# 
# An IndexError is raised if a negative index points past the beginning of
# the array.
# 
# See also Array#push, and Array#unshift.
# 
#    a = Array.new
#    a[4] = "4";                 #=> [nil, nil, nil, nil, "4"]
#    a[0, 3] = [ 'a', 'b', 'c' ] #=> ["a", "b", "c", nil, "4"]
#    a[1..2] = [ 1, 2 ]          #=> ["a", 1, 2, nil, "4"]
#    a[0, 2] = "?"               #=> ["?", 2, nil, "4"]
#    a[0..2] = "A"               #=> ["A", "4"]
#    a[-1]   = "Z"               #=> ["A", "Z"]
#    a[1..-1] = nil              #=> ["A", nil]
#    a[1..-1] = []               #=> ["A"]
#    a[0, 0] = [ 1, 2 ]          #=> [1, 2, "A"]
#    a[3, 0] = "B"               #=> [1, 2, "A", "B"]
def []=; [] || nil; end
##
# Returns the element at +index+. A negative index counts from the end of
# +self+. Returns +nil+ if the index is out of range. See also
# Array#[].
# 
#    a = [ "a", "b", "c", "d", "e" ]
#    a.at(0)     #=> "a"
#    a.at(-1)    #=> "e"
def at(index); Object.new || nil; end
##
# Tries to return the element at position +index+, but throws an IndexError
# exception if the referenced +index+ lies outside of the array bounds.  This
# error can be prevented by supplying a second argument, which will act as a
# +default+ value.
# 
# Alternatively, if a block is given it will only be executed when an
# invalid +index+ is referenced.  Negative values of +index+ count from the
# end of the array.
# 
#    a = [ 11, 22, 33, 44 ]
#    a.fetch(1)               #=> 22
#    a.fetch(-1)              #=> 44
#    a.fetch(4, 'cat')        #=> "cat"
#    a.fetch(100) { |i| puts "#{i} is out of bounds" }
#                             #=> "100 is out of bounds"
def fetch(index); Object.new; end
##
# Returns the first element, or the first +n+ elements, of the array.
# If the array is empty, the first form returns +nil+, and the
# second form returns an empty array. See also Array#last for
# the opposite effect.
# 
#    a = [ "q", "r", "s", "t" ]
#    a.first     #=> "q"
#    a.first(2)  #=> ["q", "r"]
def first; []; end
##
# Returns the last element(s) of +self+. If the array is empty,
# the first form returns +nil+.
# 
# See also Array#first for the opposite effect.
# 
#    a = [ "w", "x", "y", "z" ]
#    a.last     #=> "z"
#    a.last(2)  #=> ["y", "z"]
def last; []; end
##
# Appends the elements of +other_ary+ to +self+.
# 
#    [ "a", "b" ].concat( ["c", "d"] ) #=> [ "a", "b", "c", "d" ]
#    a = [ 1, 2, 3 ]
#    a.concat( [ 4, 5 ] )
#    a                                 #=> [ 1, 2, 3, 4, 5 ]
# 
# See also Array#+.
def concat(other_ary); []; end
##
# Append---Pushes the given object on to the end of this array. This
# expression returns the array itself, so several appends
# may be chained together.
# 
#    [ 1, 2 ] << "c" << "d" << [ 3, 4 ]
#            #=>  [ 1, 2, "c", "d", [ 3, 4 ] ]
def <<; []; end
##
# Append --- Pushes the given object(s) on to the end of this array. This
# expression returns the array itself, so several appends
# may be chained together. See also Array#pop for the opposite
# effect.
# 
#    a = [ "a", "b", "c" ]
#    a.push("d", "e", "f")
#            #=> ["a", "b", "c", "d", "e", "f"]
#    [1, 2, 3,].push(4).push(5)
#            #=> [1, 2, 3, 4, 5]
def push(); []; end
##
# Removes the last element from +self+ and returns it, or
# +nil+ if the array is empty.
# 
# If a number +n+ is given, returns an array of the last +n+ elements
# (or less) just like <code>array.slice!(-n, n)</code> does. See also
# Array#push for the opposite effect.
# 
#    a = [ "a", "b", "c", "d" ]
#    a.pop     #=> "d"
#    a.pop(2)  #=> ["b", "c"]
#    a         #=> ["a"]
def pop; []; end
##
# Removes the first element of +self+ and returns it (shifting all
# other elements down by one). Returns +nil+ if the array
# is empty.
# 
# If a number +n+ is given, returns an array of the first +n+ elements
# (or less) just like <code>array.slice!(0, n)</code> does. With +ary+
# containing only the remainder elements, not including what was shifted to
# +new_ary+. See also Array#unshift for the opposite effect.
# 
#    args = [ "-m", "-q", "filename" ]
#    args.shift     #=> "-m"
#    args           #=> ["-q", "filename"]
# 
#    args = [ "-m", "-q", "filename" ]
#    args.shift(2)  #=> ["-m", "-q"]
#    args           #=> ["filename"]
def shift; []; end
##
# Prepends objects to the front of +self+, moving other elements upwards.
# See also Array#shift for the opposite effect.
# 
#    a = [ "b", "c", "d" ]
#    a.unshift("a")   #=> ["a", "b", "c", "d"]
#    a.unshift(1, 2)  #=> [ 1, 2, "a", "b", "c", "d"]
def unshift(); []; end
##
# Inserts the given values before the element with the given +index+.
# 
# Negative indices count backwards from the end of the array, where +-1+ is
# the last element.
# 
#    a = %w{ a b c d }
#    a.insert(2, 99)         #=> ["a", "b", 99, "c", "d"]
#    a.insert(-2, 1, 2, 3)   #=> ["a", "b", 99, "c", 1, 2, 3, "d"]
def insert(); []; end
##
# Calls the given block once for each element in +self+, passing that element
# as a parameter.
# 
# An Enumerator is returned if no block is given.
# 
#    a = [ "a", "b", "c" ]
#    a.each {|x| print x, " -- " }
# 
# produces:
# 
#    a -- b -- c --
def each(&block); Enumerator.new; end
##
# Same as Array#each, but passes the +index+ of the element instead of the
# element itself.
# 
# An Enumerator is returned if no block is given.
# 
#    a = [ "a", "b", "c" ]
#    a.each_index {|x| print x, " -- " }
# 
# produces:
# 
#    0 -- 1 -- 2 --
def each_index(&block); Enumerator.new; end
##
# Same as Array#each, but traverses +self+ in reverse order.
# 
#    a = [ "a", "b", "c" ]
#    a.reverse_each {|x| print x, " " }
# 
# produces:
# 
#    c b a
def reverse_each(&block); Enumerator.new; end
##
# Returns the number of elements in +self+. May be zero.
# 
#    [ 1, 2, 3, 4, 5 ].length   #=> 5
#    [].length                  #=> 0
def length; 0; end
##
# Returns +true+ if +self+ contains no elements.
# 
#    [].empty?   #=> true
def empty?; true || false; end
##
# Returns the _index_ of the first object in +ary+ such that the object is
# <code>==</code> to +obj+.
# 
# If a block is given instead of an argument, returns the _index_ of the
# first object for which the block returns +true+.  Returns +nil+ if no
# match is found.
# 
# See also Array#rindex.
# 
# An Enumerator is returned if neither a block nor argument is given.
# 
#    a = [ "a", "b", "c" ]
#    a.index("b")              #=> 1
#    a.index("z")              #=> nil
#    a.index { |x| x == "b" }  #=> 1
# 
# This is an alias of Array#find_index.
def index(obj); Enumerator.new; end
##
# Returns the _index_ of the last object in +self+ <code>==</code> to +obj+.
# 
# If a block is given instead of an argument, returns the _index_ of the
# first object for which the block returns +true+, starting from the last
# object.
# 
# Returns +nil+ if no match is found.
# 
# See also Array#index.
# 
# If neither block nor argument is given, an Enumerator is returned instead.
# 
#    a = [ "a", "b", "b", "b", "c" ]
#    a.rindex("b")             #=> 3
#    a.rindex("z")             #=> nil
#    a.rindex { |x| x == "b" } #=> 3
def rindex(obj); Enumerator.new; end
##
# Returns a string created by converting each element of the array to
# a string, separated by the given +separator+.
# If the +separator+ is +nil+, it uses current $,.
# If both the +separator+ and $, are nil, it uses empty string.
# 
#    [ "a", "b", "c" ].join        #=> "abc"
#    [ "a", "b", "c" ].join("-")   #=> "a-b-c"
def join(separator=$,); ''; end
##
# Returns a new array containing +self+'s elements in reverse order.
# 
#    [ "a", "b", "c" ].reverse   #=> ["c", "b", "a"]
#    [ 1 ].reverse               #=> [1]
def reverse; []; end
##
# Reverses +self+ in place.
# 
#    a = [ "a", "b", "c" ]
#    a.reverse!       #=> ["c", "b", "a"]
#    a                #=> ["c", "b", "a"]
def reverse!; []; end
##
# Returns a new array by rotating +self+ so that the element at +count+ is
# the first element of the new array.
# 
# If +count+ is negative then it rotates in the opposite direction, starting
# from the end of +self+ where +-1+ is the last element.
# 
#    a = [ "a", "b", "c", "d" ]
#    a.rotate         #=> ["b", "c", "d", "a"]
#    a                #=> ["a", "b", "c", "d"]
#    a.rotate(2)      #=> ["c", "d", "a", "b"]
#    a.rotate(-3)     #=> ["b", "c", "d", "a"]
def rotate(count=1); []; end
##
# Rotates +self+ in place so that the element at +count+ comes first, and
# returns +self+.
# 
# If +count+ is negative then it rotates in the opposite direction, starting
# from the end of the array where +-1+ is the last element.
# 
#    a = [ "a", "b", "c", "d" ]
#    a.rotate!        #=> ["b", "c", "d", "a"]
#    a                #=> ["b", "c", "d", "a"]
#    a.rotate!(2)     #=> ["d", "a", "b", "c"]
#    a.rotate!(-3)    #=> ["a", "b", "c", "d"]
def rotate!(count=1); []; end
##
# Returns a new array created by sorting +self+.
# 
# Comparisons for the sort will be done using the <code><=></code> operator
# or using an optional code block.
# 
# The block must implement a comparison between +a+ and +b+, and return
# +-1+, when +a+ follows +b+, +0+ when +a+ and +b+ are equivalent, or ++1+
# if +b+ follows +a+.
# 
# See also Enumerable#sort_by.
# 
#    a = [ "d", "a", "e", "c", "b" ]
#    a.sort                    #=> ["a", "b", "c", "d", "e"]
#    a.sort { |x,y| y <=> x }  #=> ["e", "d", "c", "b", "a"]
def sort; []; end
##
# Sorts +self+ in place.
# 
# Comparisons for the sort will be done using the <code><=></code> operator
# or using an optional code block.
# 
# The block must implement a comparison between +a+ and +b+, and return
# +-1+, when +a+ follows +b+, +0+ when +a+ and +b+ are equivalent, or ++1+
# if +b+ follows +a+.
# 
# See also Enumerable#sort_by.
# 
#    a = [ "d", "a", "e", "c", "b" ]
#    a.sort!                    #=> ["a", "b", "c", "d", "e"]
#    a.sort! { |x,y| y <=> x }  #=> ["e", "d", "c", "b", "a"]
def sort!; []; end
##
# Sorts +self+ in place using a set of keys generated by mapping the
# values in +self+ through the given block.
# 
# If no block is given, an Enumerator is returned instead.
def sort_by!(&block); Enumerator.new; end
##
# Invokes the given block once for each element of +self+.
# 
# Creates a new array containing the values returned by the block.
# 
# See also Enumerable#collect.
# 
# If no block is given, an Enumerator is returned instead.
# 
#    a = [ "a", "b", "c", "d" ]
#    a.map { |x| x + "!" }   #=> ["a!", "b!", "c!", "d!"]
#    a                       #=> ["a", "b", "c", "d"]
def collect(&block); Enumerator.new; end
##
# Invokes the given block once for each element of +self+.
# 
# Creates a new array containing the values returned by the block.
# 
# See also Enumerable#collect.
# 
# If no block is given, an Enumerator is returned instead.
# 
#    a = [ "a", "b", "c", "d" ]
#    a.map { |x| x + "!" }   #=> ["a!", "b!", "c!", "d!"]
#    a                       #=> ["a", "b", "c", "d"]
def map(&block); Enumerator.new; end
##
# Invokes the given block once for each element of +self+, replacing the
# element with the value returned by the block.
# 
# See also Enumerable#collect.
# 
# If no block is given, an Enumerator is returned instead.
# 
#    a = [ "a", "b", "c", "d" ]
#    a.map! {|x| x + "!" }
#    a #=>  [ "a!", "b!", "c!", "d!" ]
def collect!(&block); Enumerator.new; end
##
# Invokes the given block once for each element of +self+, replacing the
# element with the value returned by the block.
# 
# See also Enumerable#collect.
# 
# If no block is given, an Enumerator is returned instead.
# 
#    a = [ "a", "b", "c", "d" ]
#    a.map! {|x| x + "!" }
#    a #=>  [ "a!", "b!", "c!", "d!" ]
def map!(&block); Enumerator.new; end
##
# Returns a new array containing all elements of +ary+
# for which the given +block+ returns a true value.
# 
# If no block is given, an Enumerator is returned instead.
# 
#    [1,2,3,4,5].select { |num|  num.even?  }   #=> [2, 4]
# 
#    a = %w{ a b c d e f }
#    a.select { |v| v =~ /[aeiou]/ }  #=> ["a", "e"]
# 
# See also Enumerable#select.
def select(&block); Enumerator.new; end
##
# Invokes the given block passing in successive elements from +self+,
# deleting elements for which the block returns a +false+ value.
# 
# If changes were made, it will return +self+, otherwise it returns +nil+.
# 
# See also Array#keep_if
# 
# If no block is given, an Enumerator is returned instead.
def select!(&block); Enumerator.new; end
##
# Deletes every element of +self+ for which the given block evaluates to
# +false+.
# 
# See also Array#select!
# 
# If no block is given, an Enumerator is returned instead.
# 
#    a = %w{ a b c d e f }
#    a.keep_if { |v| v =~ /[aeiou]/ }  #=> ["a", "e"]
def keep_if(&block); Enumerator.new; end
##
# Returns an array containing the elements in +self+ corresponding to the
# given +selector+(s).
# 
# The selectors may be either integer indices or ranges.
# 
# See also Array#select.
# 
#    a = %w{ a b c d e f }
#    a.values_at(1, 3, 5)          # => ["b", "d", "f"]
#    a.values_at(1, 3, 5, 7)       # => ["b", "d", "f", nil]
#    a.values_at(-1, -2, -2, -7)   # => ["f", "e", "e", nil]
#    a.values_at(4..6, 3...6)      # => ["e", "f", nil, "d", "e", "f"]
def values_at(); []; end
##
# Deletes all items from +self+ that are equal to +obj+.
# 
# Returns the last deleted item, or +nil+ if no matching item is found.
# 
# If the optional code block is given, the result of the block is returned if
# the item is not found.  (To remove +nil+ elements and get an informative
# return value, use Array#compact!)
# 
#    a = [ "a", "b", "b", "b", "c" ]
#    a.delete("b")                   #=> "b"
#    a                               #=> ["a", "c"]
#    a.delete("z")                   #=> nil
#    a.delete("z") { "not found" }   #=> "not found"
def delete(obj); Object.new || nil; end
##
# Deletes the element at the specified +index+, returning that element, or
# +nil+ if the +index+ is out of range.
# 
# See also Array#slice!
# 
#    a = ["ant", "bat", "cat", "dog"]
#    a.delete_at(2)    #=> "cat"
#    a                 #=> ["ant", "bat", "dog"]
#    a.delete_at(99)   #=> nil
def delete_at(index); Object.new || nil; end
##
# Deletes every element of +self+ for which block evaluates to +true+.
# 
# The array is changed instantly every time the block is called, not after
# the iteration is over.
# 
# See also Array#reject!
# 
# If no block is given, an Enumerator is returned instead.
# 
#    a = [ "a", "b", "c" ]
#    a.delete_if {|x| x >= "b" }   #=> ["a"]
def delete_if(&block); Enumerator.new; end
##
# Returns a new array containing the items in +self+ for which the given
# block is not +true+.
# 
# See also Array#delete_if
# 
# If no block is given, an Enumerator is returned instead.
def reject(&block); Enumerator.new; end
##
# Equivalent to Array#delete_if, deleting elements from +self+ for which the
# block evaluates to +true+, but returns +nil+ if no changes were made.
# 
# The array is changed instantly every time the block is called, not after
# the iteration is over.
# 
# See also Enumerable#reject and Array#delete_if.
# 
# If no block is given, an Enumerator is returned instead.
def reject!(&block); Enumerator.new; end
##
# Converts any arguments to arrays, then merges elements of +self+ with
# corresponding elements from each argument.
# 
# This generates a sequence of <code>ary.size</code> _n_-element arrays,
# where _n_ is one more that the count of arguments.
# 
# If the size of any argument is less than the size of the initial array,
# +nil+ values are supplied.
# 
# If a block is given, it is invoked for each output +array+, otherwise an
# array of arrays is returned.
# 
#    a = [ 4, 5, 6 ]
#    b = [ 7, 8, 9 ]
#    [1, 2, 3].zip(a, b)   #=> [[1, 4, 7], [2, 5, 8], [3, 6, 9]]
#    [1, 2].zip(a, b)      #=> [[1, 4, 7], [2, 5, 8]]
#    a.zip([1, 2], [8])    #=> [[4, 1, 8], [5, 2, nil], [6, nil, nil]]
def zip(); end
##
# Assumes that +self+ is an array of arrays and transposes the rows and
# columns.
# 
#    a = [[1,2], [3,4], [5,6]]
#    a.transpose   #=> [[1, 3, 5], [2, 4, 6]]
# 
# If the length of the subarrays don't match, an IndexError is raised.
def transpose; []; end
##
# Removes all elements from +self+.
# 
#    a = [ "a", "b", "c", "d", "e" ]
#    a.clear    #=> [ ]
def clear; []; end
##
# The first three forms set the selected elements of +self+ (which
# may be the entire array) to +obj+.
# 
# A +start+ of +nil+ is equivalent to zero.
# 
# A +length+ of +nil+ is equivalent to the length of the array.
# 
# The last three forms fill the array with the value of the given block,
# which is passed the absolute index of each element to be filled.
# 
# Negative values of +start+ count from the end of the array, where +-1+ is
# the last element.
# 
#    a = [ "a", "b", "c", "d" ]
#    a.fill("x")              #=> ["x", "x", "x", "x"]
#    a.fill("z", 2, 2)        #=> ["x", "x", "z", "z"]
#    a.fill("y", 0..1)        #=> ["y", "y", "z", "z"]
#    a.fill { |i| i*i }       #=> [0, 1, 4, 9]
#    a.fill(-2) { |i| i*i*i } #=> [0, 1, 8, 27]
def fill(obj); []; end
##
# Returns +true+ if the given +object+ is present in +self+ (that is, if any
# object <code>==</code> +object+), otherwise returns +false+.
# 
#    a = [ "a", "b", "c" ]
#    a.include?("b")   #=> true
#    a.include?("z")   #=> false
def include?(object); true || false; end
##
# Comparison --- Returns an integer (+-1+, +0+, or <code>+1</code>) if this
# array is less than, equal to, or greater than +other_ary+.
# 
# +nil+ is returned if the two values are incomparable.
# 
# Each object in each array is compared (using the <=> operator).
# 
# Arrays are compared in an "element-wise" manner; the first two elements
# that are not equal will determine the return value for the whole
# comparison.
# 
# If all the values are equal, then the return is based on a comparison of
# the array lengths. Thus, two arrays are "equal" according to Array#<=> if,
# and only if, they have the same length and the value of each element is
# equal to the value of the corresponding element in the other array.
# 
#    [ "a", "a", "c" ]    <=> [ "a", "b", "c" ]   #=> -1
#    [ 1, 2, 3, 4, 5, 6 ] <=> [ 1, 2 ]            #=> +1
def <=>; 1 || nil; end
##
# Deletes the element(s) given by an +index+ (optionally up to +length+
# elements) or by a +range+.
# 
# Returns the deleted object (or objects), or +nil+ if the +index+ is out of
# range.
# 
#    a = [ "a", "b", "c" ]
#    a.slice!(1)     #=> "b"
#    a               #=> ["a", "c"]
#    a.slice!(-1)    #=> "c"
#    a               #=> ["a"]
#    a.slice!(100)   #=> nil
#    a               #=> ["a"]
def slice!(index); [] || nil; end
##
# Searches through an array whose elements are also arrays comparing +obj+
# with the first element of each contained array using <code>obj.==</code>.
# 
# Returns the first contained array that matches (that is, the first
# associated array), or +nil+ if no match is found.
# 
# See also Array#rassoc
# 
#    s1 = [ "colors", "red", "blue", "green" ]
#    s2 = [ "letters", "a", "b", "c" ]
#    s3 = "foo"
#    a  = [ s1, s2, s3 ]
#    a.assoc("letters")  #=> [ "letters", "a", "b", "c" ]
#    a.assoc("foo")      #=> nil
def assoc(obj); []; end
##
# Searches through the array whose elements are also arrays.
# 
# Compares +obj+ with the second element of each contained array using
# <code>obj.==</code>.
# 
# Returns the first contained array that matches +obj+.
# 
# See also Array#assoc.
# 
#    a = [ [ 1, "one"], [2, "two"], [3, "three"], ["ii", "two"] ]
#    a.rassoc("two")    #=> [2, "two"]
#    a.rassoc("four")   #=> nil
def rassoc(obj); [] || nil; end
##
# Concatenation --- Returns a new array built by concatenating the
# two arrays together to produce a third array.
# 
#    [ 1, 2, 3 ] + [ 4, 5 ]    #=> [ 1, 2, 3, 4, 5 ]
#    a = [ "a", "b", "c" ]
#    a + [ "d", "e", "f" ]
#    a                         #=> [ "a", "b", "c", "d", "e", "f" ]
# 
# See also Array#concat.
def +; []; end
##
# Repetition --- With a String argument, equivalent to
# <code>ary.join(str)</code>.
# 
# Otherwise, returns a new array built by concatenating the +int+ copies of
# +self+.
# 
#    [ 1, 2, 3 ] * 3    #=> [ 1, 2, 3, 1, 2, 3, 1, 2, 3 ]
#    [ 1, 2, 3 ] * ","  #=> "1,2,3"
def *; ''; end
##
# Array Difference
# 
# Returns a new array that is a copy of the original array, removing any
# items that also appear in +other_ary+. The order is preserved from the
# original array.
# 
# It compares elements using their #hash and #eql? methods for efficiency.
# 
#    [ 1, 1, 2, 2, 3, 3, 4, 5 ] - [ 1, 2, 4 ]  #=>  [ 3, 3, 5 ]
# 
# If you need set-like behavior, see the library class Set.
def -; []; end
##
# Set Intersection --- Returns a new array containing elements common to the
# two arrays, excluding any duplicates. The order is preserved from the
# original array.
# 
# It compares elements using their #hash and #eql? methods for efficiency.
# 
#    [ 1, 1, 3, 5 ] & [ 1, 2, 3 ]                 #=> [ 1, 3 ]
#    [ 'a', 'b', 'b', 'z' ] & [ 'a', 'b', 'c' ]   #=> [ 'a', 'b' ]
# 
# See also Array#uniq.
def &; []; end
##
# Set Union --- Returns a new array by joining +ary+ with +other_ary+,
# excluding any duplicates and preserving the order from the original array.
# 
# It compares elements using their #hash and #eql? methods for efficiency.
# 
#    [ "a", "b", "c" ] | [ "c", "d", "a" ]    #=> [ "a", "b", "c", "d" ]
# 
# See also Array#uniq.
def |; []; end
##
# Returns a new array by removing duplicate values in +self+.
# 
# If a block is given, it will use the return value of the block for comparison.
# 
# It compares values using their #hash and #eql? methods for efficiency.
# 
#    a = [ "a", "a", "b", "b", "c" ]
#    a.uniq   # => ["a", "b", "c"]
# 
#    b = [["student","sam"], ["student","george"], ["teacher","matz"]]
#    b.uniq { |s| s.first } # => [["student", "sam"], ["teacher", "matz"]]
def uniq; []; end
##
# Removes duplicate elements from +self+.
# 
# If a block is given, it will use the return value of the block for
# comparison.
# 
# It compares values using their #hash and #eql? methods for efficiency.
# 
# Returns +nil+ if no changes are made (that is, no duplicates are found).
# 
#    a = [ "a", "a", "b", "b", "c" ]
#    a.uniq!   # => ["a", "b", "c"]
# 
#    b = [ "a", "b", "c" ]
#    b.uniq!   # => nil
# 
#    c = [["student","sam"], ["student","george"], ["teacher","matz"]]
#    c.uniq! { |s| s.first } # => [["student", "sam"], ["teacher", "matz"]]
def uniq!; [] || nil; end
##
# Returns a copy of +self+ with all +nil+ elements removed.
# 
#    [ "a", nil, "b", nil, "c", nil ].compact
#                      #=> [ "a", "b", "c" ]
def compact; []; end
##
# Removes +nil+ elements from the array.
# 
# Returns +nil+ if no changes were made, otherwise returns the array.
# 
#    [ "a", nil, "b", nil, "c" ].compact! #=> [ "a", "b", "c" ]
#    [ "a", "b", "c" ].compact!           #=> nil
def compact!; [] || nil; end
##
# Returns a new array that is a one-dimensional flattening of +self+
# (recursively).
# 
# That is, for every element that is an array, extract its elements into
# the new array.
# 
# The optional +level+ argument determines the level of recursion to
# flatten.
# 
#    s = [ 1, 2, 3 ]           #=> [1, 2, 3]
#    t = [ 4, 5, 6, [7, 8] ]   #=> [4, 5, 6, [7, 8]]
#    a = [ s, t, 9, 10 ]       #=> [[1, 2, 3], [4, 5, 6, [7, 8]], 9, 10]
#    a.flatten                 #=> [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
#    a = [ 1, 2, [3, [4, 5] ] ]
#    a.flatten(1)              #=> [1, 2, 3, [4, 5]]
def flatten; []; end
##
# Flattens +self+ in place.
# 
# Returns +nil+ if no modifications were made (i.e., the array contains no
# subarrays.)
# 
# The optional +level+ argument determines the level of recursion to flatten.
# 
#    a = [ 1, 2, [3, [4, 5] ] ]
#    a.flatten!   #=> [1, 2, 3, 4, 5]
#    a.flatten!   #=> nil
#    a            #=> [1, 2, 3, 4, 5]
#    a = [ 1, 2, [3, [4, 5] ] ]
#    a.flatten!(1) #=> [1, 2, 3, [4, 5]]
def flatten!; [] || nil; end
##
# Returns the number of elements.
# 
# If an argument is given, counts the number of elements which equal +obj+
# using <code>===</code>.
# 
# If a block is given, counts the number of elements for which the block
# returns a true value.
# 
#    ary = [1, 2, 4, 2]
#    ary.count                  #=> 4
#    ary.count(2)               #=> 2
#    ary.count { |x| x%2 == 0 } #=> 3
def count; 0; end
##
# Shuffles elements in +self+ in place.
# 
# The optional +rng+ argument will be used as the random number generator.
def shuffle!; []; end
##
# Returns a new array with elements of +self+ shuffled.
# 
#    a = [ 1, 2, 3 ]           #=> [1, 2, 3]
#    a.shuffle                 #=> [2, 3, 1]
# 
# The optional +rng+ argument will be used as the random number generator.
# 
#    a.shuffle(random: Random.new(1))  #=> [1, 3, 2]
def shuffle; []; end
##
# Choose a random element or +n+ random elements from the array.
# 
# The elements are chosen by using random and unique indices into the array
# in order to ensure that an element doesn't repeat itself unless the array
# already contained duplicate elements.
# 
# If the array is empty the first form returns +nil+ and the second form
# returns an empty array.
# 
# The optional +rng+ argument will be used as the random number generator.
# 
#    a = [ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ]
#    a.sample         #=> 7
#    a.sample(4)      #=> [6, 4, 2, 5]
def sample; []; end
##
# Calls the given block for each element +n+ times or forever if +nil+ is
# given.
# 
# Does nothing if a non-positive number is given or the array is empty.
# 
# Returns +nil+ if the loop has finished without getting interrupted.
# 
# If no block is given, an Enumerator is returned instead.
# 
#    a = ["a", "b", "c"]
#    a.cycle { |x| puts x }     # print, a, b, c, a, b, c,.. forever.
#    a.cycle(2) { |x| puts x }  # print, a, b, c, a, b, c.
def cycle(n=null, &block); Enumerator.new; end
##
# When invoked with a block, yield all permutations of length +n+ of the
# elements of the array, then return the array itself.
# 
# If +n+ is not specified, yield all permutations of all elements.
# 
# The implementation makes no guarantees about the order in which the
# permutations are yielded.
# 
# If no block is given, an Enumerator is returned instead.
# 
# Examples:
# 
#   a = [1, 2, 3]
#   a.permutation.to_a    #=> [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
#   a.permutation(1).to_a #=> [[1],[2],[3]]
#   a.permutation(2).to_a #=> [[1,2],[1,3],[2,1],[2,3],[3,1],[3,2]]
#   a.permutation(3).to_a #=> [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
#   a.permutation(0).to_a #=> [[]] # one permutation of length 0
#   a.permutation(4).to_a #=> []   # no permutations of length 4
def permutation(&block); Enumerator.new; end
##
# When invoked with a block, yields all combinations of length +n+ of elements
# from the array and then returns the array itself.
# 
# The implementation makes no guarantees about the order in which the
# combinations are yielded.
# 
# If no block is given, an Enumerator is returned instead.
# 
# Examples:
# 
#     a = [1, 2, 3, 4]
#     a.combination(1).to_a  #=> [[1],[2],[3],[4]]
#     a.combination(2).to_a  #=> [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
#     a.combination(3).to_a  #=> [[1,2,3],[1,2,4],[1,3,4],[2,3,4]]
#     a.combination(4).to_a  #=> [[1,2,3,4]]
#     a.combination(0).to_a  #=> [[]] # one combination of length 0
#     a.combination(5).to_a  #=> []   # no combinations of length 5
def combination(n, &block); Enumerator.new; end
##
# When invoked with a block, yield all repeated permutations of length +n+ of
# the elements of the array, then return the array itself.
# 
# The implementation makes no guarantees about the order in which the repeated
# permutations are yielded.
# 
# If no block is given, an Enumerator is returned instead.
# 
# Examples:
# 
#     a = [1, 2]
#     a.repeated_permutation(1).to_a  #=> [[1], [2]]
#     a.repeated_permutation(2).to_a  #=> [[1,1],[1,2],[2,1],[2,2]]
#     a.repeated_permutation(3).to_a  #=> [[1,1,1],[1,1,2],[1,2,1],[1,2,2],
#                                     #    [2,1,1],[2,1,2],[2,2,1],[2,2,2]]
#     a.repeated_permutation(0).to_a  #=> [[]] # one permutation of length 0
def repeated_permutation(n, &block); Enumerator.new; end
##
# When invoked with a block, yields all repeated combinations of length +n+ of
# elements from the array and then returns the array itself.
# 
# The implementation makes no guarantees about the order in which the repeated
# combinations are yielded.
# 
# If no block is given, an Enumerator is returned instead.
# 
# Examples:
# 
#   a = [1, 2, 3]
#   a.repeated_combination(1).to_a  #=> [[1], [2], [3]]
#   a.repeated_combination(2).to_a  #=> [[1,1],[1,2],[1,3],[2,2],[2,3],[3,3]]
#   a.repeated_combination(3).to_a  #=> [[1,1,1],[1,1,2],[1,1,3],[1,2,2],[1,2,3],
#                                   #    [1,3,3],[2,2,2],[2,2,3],[2,3,3],[3,3,3]]
#   a.repeated_combination(4).to_a  #=> [[1,1,1,1],[1,1,1,2],[1,1,1,3],[1,1,2,2],[1,1,2,3],
#                                   #    [1,1,3,3],[1,2,2,2],[1,2,2,3],[1,2,3,3],[1,3,3,3],
#                                   #    [2,2,2,2],[2,2,2,3],[2,2,3,3],[2,3,3,3],[3,3,3,3]]
#   a.repeated_combination(0).to_a  #=> [[]] # one combination of length 0
def repeated_combination(n, &block); Enumerator.new; end
##
# Returns an array of all combinations of elements from all arrays.
# 
# The length of the returned array is the product of the length of +self+ and
# the argument arrays.
# 
# If given a block, #product will yield all combinations and return +self+
# instead.
# 
#    [1,2,3].product([4,5])     #=> [[1,4],[1,5],[2,4],[2,5],[3,4],[3,5]]
#    [1,2].product([1,2])       #=> [[1,1],[1,2],[2,1],[2,2]]
#    [1,2].product([3,4],[5,6]) #=> [[1,3,5],[1,3,6],[1,4,5],[1,4,6],
#                               #     [2,3,5],[2,3,6],[2,4,5],[2,4,6]]
#    [1,2].product()            #=> [[1],[2]]
#    [1,2].product([])          #=> []
def product(); []; end
##
# Returns first +n+ elements from the array.
# 
# If a negative number is given, raises an ArgumentError.
# 
# See also Array#drop
# 
#    a = [1, 2, 3, 4, 5, 0]
#    a.take(3)             #=> [1, 2, 3]
def take(n); []; end
##
# Passes elements to the block until the block returns +nil+ or +false+, then
# stops iterating and returns an array of all prior elements.
# 
# If no block is given, an Enumerator is returned instead.
# 
# See also Array#drop_while
# 
#    a = [1, 2, 3, 4, 5, 0]
#    a.take_while { |i| i < 3 }  #=> [1, 2]
def take_while(&block); Enumerator.new; end
##
# Drops first +n+ elements from +ary+ and returns the rest of the elements in
# an array.
# 
# If a negative number is given, raises an ArgumentError.
# 
# See also Array#take
# 
#    a = [1, 2, 3, 4, 5, 0]
#    a.drop(3)             #=> [4, 5, 0]
def drop(n); []; end
##
# Drops elements up to, but not including, the first element for which the
# block returns +nil+ or +false+ and returns an array containing the
# remaining elements.
# 
# If no block is given, an Enumerator is returned instead.
# 
# See also Array#take_while
# 
#    a = [1, 2, 3, 4, 5, 0]
#    a.drop_while {|i| i < 3 }   #=> [3, 4, 5, 0]
def drop_while(&block); Enumerator.new; end
##
# By using binary search, finds a value from this array which meets
# the given condition in O(log n) where n is the size of the array.
# 
# You can use this method in two use cases: a find-minimum mode and
# a find-any mode.  In either case, the elements of the array must be
# monotone (or sorted) with respect to the block.
# 
# In find-minimum mode (this is a good choice for typical use case),
# the block must return true or false, and there must be an index i
# (0 <= i <= ary.size) so that:
# 
# - the block returns false for any element whose index is less than
#   i, and
# - the block returns true for any element whose index is greater
#   than or equal to i.
# 
# This method returns the i-th element.  If i is equal to ary.size,
# it returns nil.
# 
#    ary = [0, 4, 7, 10, 12]
#    ary.bsearch {|x| x >=   4 } #=> 4
#    ary.bsearch {|x| x >=   6 } #=> 7
#    ary.bsearch {|x| x >=  -1 } #=> 0
#    ary.bsearch {|x| x >= 100 } #=> nil
# 
# In find-any mode (this behaves like libc's bsearch(3)), the block
# must return a number, and there must be two indices i and j
# (0 <= i <= j <= ary.size) so that:
# 
# - the block returns a positive number for ary[k] if 0 <= k < i,
# - the block returns zero for ary[k] if i <= k < j, and
# - the block returns a negative number for ary[k] if
#   j <= k < ary.size.
# 
# Under this condition, this method returns any element whose index
# is within i...j.  If i is equal to j (i.e., there is no element
# that satisfies the block), this method returns nil.
# 
#    ary = [0, 4, 7, 10, 12]
#    # try to find v such that 4 <= v < 8
#    ary.bsearch {|x| 1 - x / 4 } #=> 4 or 7
#    # try to find v such that 8 <= v < 10
#    ary.bsearch {|x| 4 - x / 2 } #=> nil
# 
# You must not mix the two modes at a time; the block must always
# return either true/false, or always return a number.  It is
# undefined which value is actually picked up at each iteration.
def bsearch(&block); Object.new; end
##
# Packs the contents of <i>arr</i> into a binary sequence according to
# the directives in <i>aTemplateString</i> (see the table below)
# Directives ``A,'' ``a,'' and ``Z'' may be followed by a count,
# which gives the width of the resulting field. The remaining
# directives also may take a count, indicating the number of array
# elements to convert. If the count is an asterisk
# (``<code>*</code>''), all remaining array elements will be
# converted. Any of the directives ``<code>sSiIlL</code>'' may be
# followed by an underscore (``<code>_</code>'') or
# exclamation mark (``<code>!</code>'') to use the underlying
# platform's native size for the specified type; otherwise, they use a
# platform-independent size. Spaces are ignored in the template
# string. See also <code>String#unpack</code>.
# 
#    a = [ "a", "b", "c" ]
#    n = [ 65, 66, 67 ]
#    a.pack("A3A3A3")   #=> "a  b  c  "
#    a.pack("a3a3a3")   #=> "a\000\000b\000\000c\000\000"
#    n.pack("ccc")      #=> "ABC"
# 
# Directives for +pack+.
# 
#  Integer      | Array   |
#  Directive    | Element | Meaning
#  ---------------------------------------------------------------------------
#     C         | Integer | 8-bit unsigned (unsigned char)
#     S         | Integer | 16-bit unsigned, native endian (uint16_t)
#     L         | Integer | 32-bit unsigned, native endian (uint32_t)
#     Q         | Integer | 64-bit unsigned, native endian (uint64_t)
#               |         |
#     c         | Integer | 8-bit signed (signed char)
#     s         | Integer | 16-bit signed, native endian (int16_t)
#     l         | Integer | 32-bit signed, native endian (int32_t)
#     q         | Integer | 64-bit signed, native endian (int64_t)
#               |         |
#     S_, S!    | Integer | unsigned short, native endian
#     I, I_, I! | Integer | unsigned int, native endian
#     L_, L!    | Integer | unsigned long, native endian
#               |         |
#     s_, s!    | Integer | signed short, native endian
#     i, i_, i! | Integer | signed int, native endian
#     l_, l!    | Integer | signed long, native endian
#               |         |
#     S> L> Q>  | Integer | same as the directives without ">" except
#     s> l> q>  |         | big endian
#     S!> I!>   |         | (available since Ruby 1.9.3)
#     L!>       |         | "S>" is same as "n"
#     s!> i!>   |         | "L>" is same as "N"
#     l!>       |         |
#               |         |
#     S< L< Q<  | Integer | same as the directives without "<" except
#     s< l< q<  |         | little endian
#     S!< I!<   |         | (available since Ruby 1.9.3)
#     L!<       |         | "S<" is same as "v"
#     s!< i!<   |         | "L<" is same as "V"
#     l!<       |         |
#               |         |
#     n         | Integer | 16-bit unsigned, network (big-endian) byte order
#     N         | Integer | 32-bit unsigned, network (big-endian) byte order
#     v         | Integer | 16-bit unsigned, VAX (little-endian) byte order
#     V         | Integer | 32-bit unsigned, VAX (little-endian) byte order
#               |         |
#     U         | Integer | UTF-8 character
#     w         | Integer | BER-compressed integer
# 
#  Float        |         |
#  Directive    |         | Meaning
#  ---------------------------------------------------------------------------
#     D, d      | Float   | double-precision, native format
#     F, f      | Float   | single-precision, native format
#     E         | Float   | double-precision, little-endian byte order
#     e         | Float   | single-precision, little-endian byte order
#     G         | Float   | double-precision, network (big-endian) byte order
#     g         | Float   | single-precision, network (big-endian) byte order
# 
#  String       |         |
#  Directive    |         | Meaning
#  ---------------------------------------------------------------------------
#     A         | String  | arbitrary binary string (space padded, count is width)
#     a         | String  | arbitrary binary string (null padded, count is width)
#     Z         | String  | same as ``a'', except that null is added with *
#     B         | String  | bit string (MSB first)
#     b         | String  | bit string (LSB first)
#     H         | String  | hex string (high nibble first)
#     h         | String  | hex string (low nibble first)
#     u         | String  | UU-encoded string
#     M         | String  | quoted printable, MIME encoding (see RFC2045)
#     m         | String  | base64 encoded string (see RFC 2045, count is width)
#               |         | (if count is 0, no line feed are added, see RFC 4648)
#     P         | String  | pointer to a structure (fixed-length string)
#     p         | String  | pointer to a null-terminated string
# 
#  Misc.        |         |
#  Directive    |         | Meaning
#  ---------------------------------------------------------------------------
#     @         | ---     | moves to absolute position
#     X         | ---     | back up a byte
#     x         | ---     | null byte
def pack ( aTemplateString ); ''; end
end

##
# A <code>Struct</code> is a convenient way to bundle a number of
# attributes together, using accessor methods, without having to write
# an explicit class.
# 
# The <code>Struct</code> class is a generator of specific classes,
# each one of which is defined to hold a set of variables and their
# accessors. In these examples, we'll call the generated class
# ``<i>Customer</i>Class,'' and we'll show an example instance of that
# class as ``<i>Customer</i>Inst.''
# 
# In the descriptions that follow, the parameter <i>symbol</i> refers
# to a symbol, which is either a quoted string or a
# <code>Symbol</code> (such as <code>:name</code>).
class Struct < Object
include Enumerable
##
# Creates a new class, named by <i>aString</i>, containing accessor
# methods for the given symbols. If the name <i>aString</i> is
# omitted, an anonymous structure class will be created. Otherwise,
# the name of this struct will appear as a constant in class
# <code>Struct</code>, so it must be unique for all
# <code>Struct</code>s in the system and should start with a capital
# letter. Assigning a structure class to a constant effectively gives
# the class the name of the constant.
# 
# If a block is given, it will be evaluated in the context of
# <i>StructClass</i>, passing <i>StructClass</i> as a parameter.
# 
#    Customer = Struct.new(:name, :address) do
#      def greeting
#        "Hello #{name}!"
#      end
#    end
#    Customer.new("Dave", "123 Main").greeting  # => "Hello Dave!"
# 
# <code>Struct::new</code> returns a new <code>Class</code> object,
# which can then be used to create specific instances of the new
# structure. The number of actual parameters must be
# less than or equal to the number of attributes defined for this
# class; unset parameters default to <code>nil</code>.  Passing too many
# parameters will raise an <code>ArgumentError</code>.
# 
# The remaining methods listed in this section (class and instance)
# are defined for this generated class.
# 
#    # Create a structure with a name in Struct
#    Struct.new("Customer", :name, :address)    #=> Struct::Customer
#    Struct::Customer.new("Dave", "123 Main")   #=> #<struct Struct::Customer name="Dave", address="123 Main">
# 
#    # Create a structure named by its constant
#    Customer = Struct.new(:name, :address)     #=> Customer
#    Customer.new("Dave", "123 Main")           #=> #<struct Customer name="Dave", address="123 Main">
def self.new(); end
##
# Creates a new class, named by <i>aString</i>, containing accessor
# methods for the given symbols. If the name <i>aString</i> is
# omitted, an anonymous structure class will be created. Otherwise,
# the name of this struct will appear as a constant in class
# <code>Struct</code>, so it must be unique for all
# <code>Struct</code>s in the system and should start with a capital
# letter. Assigning a structure class to a constant effectively gives
# the class the name of the constant.
# 
# If a block is given, it will be evaluated in the context of
# <i>StructClass</i>, passing <i>StructClass</i> as a parameter.
# 
#    Customer = Struct.new(:name, :address) do
#      def greeting
#        "Hello #{name}!"
#      end
#    end
#    Customer.new("Dave", "123 Main").greeting  # => "Hello Dave!"
# 
# <code>Struct::new</code> returns a new <code>Class</code> object,
# which can then be used to create specific instances of the new
# structure. The number of actual parameters must be
# less than or equal to the number of attributes defined for this
# class; unset parameters default to <code>nil</code>.  Passing too many
# parameters will raise an <code>ArgumentError</code>.
# 
# The remaining methods listed in this section (class and instance)
# are defined for this generated class.
# 
#    # Create a structure with a name in Struct
#    Struct.new("Customer", :name, :address)    #=> Struct::Customer
#    Struct::Customer.new("Dave", "123 Main")   #=> #<struct Struct::Customer name="Dave", address="123 Main">
# 
#    # Create a structure named by its constant
#    Customer = Struct.new(:name, :address)     #=> Customer
#    Customer.new("Dave", "123 Main")           #=> #<struct Customer name="Dave", address="123 Main">
def self.[]; Object.new; end
##
# Equality---Returns <code>true</code> if <i>other_struct</i> is
# equal to this one: they must be of the same class as generated by
# <code>Struct::new</code>, and the values of all instance variables
# must be equal (according to <code>Object#==</code>).
# 
#    Customer = Struct.new(:name, :address, :zip)
#    joe   = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
#    joejr = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
#    jane  = Customer.new("Jane Doe", "456 Elm, Anytown NC", 12345)
#    joe == joejr   #=> true
#    joe == jane    #=> false
def ==; true || false; end
##
# Two structures are equal if they are the same object, or if all their
# fields are equal (using <code>eql?</code>).
def eql?(other); true || false; end
##
# Return a hash value based on this struct's contents.
def hash; 0; end
##
# Describe the contents of this struct in a string.
def to_s; ''; end
##
# Describe the contents of this struct in a string.
def inspect; ''; end
##
# Returns the values for this instance as an array.
# 
#    Customer = Struct.new(:name, :address, :zip)
#    joe = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
#    joe.to_a[1]   #=> "123 Maple, Anytown NC"
def to_a; []; end
##
# Returns the values for this instance as an array.
# 
#    Customer = Struct.new(:name, :address, :zip)
#    joe = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
#    joe.to_a[1]   #=> "123 Maple, Anytown NC"
def values; []; end
##
# Returns the values for this instance as a hash with keys
# corresponding to the instance variable name.
# 
#    Customer = Struct.new(:name, :address, :zip)
#    joe = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
#    joe.to_h[:address]   #=> "123 Maple, Anytown NC"
def to_h; {}; end
##
# Returns the number of instance variables.
# 
#    Customer = Struct.new(:name, :address, :zip)
#    joe = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
#    joe.length   #=> 3
def length; 0; end
##
# Returns the number of instance variables.
# 
#    Customer = Struct.new(:name, :address, :zip)
#    joe = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
#    joe.length   #=> 3
def size; 0; end
##
# Calls <i>block</i> once for each instance variable, passing the
# value as a parameter.
# 
# If no block is given, an enumerator is returned instead.
# 
#    Customer = Struct.new(:name, :address, :zip)
#    joe = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
#    joe.each {|x| puts(x) }
# 
# <em>produces:</em>
# 
#    Joe Smith
#    123 Maple, Anytown NC
#    12345
def each(&block); Enumerator.new; end
##
# Calls <i>block</i> once for each instance variable, passing the name
# (as a symbol) and the value as parameters.
# 
# If no block is given, an enumerator is returned instead.
# 
#    Customer = Struct.new(:name, :address, :zip)
#    joe = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
#    joe.each_pair {|name, value| puts("#{name} => #{value}") }
# 
# <em>produces:</em>
# 
#    name => Joe Smith
#    address => 123 Maple, Anytown NC
#    zip => 12345
def each_pair(&block); Enumerator.new; end
##
# Attribute Assignment---Assigns to the instance variable named by
# <i>symbol</i> or <i>fixnum</i> the value <i>obj</i> and
# returns it. Will raise a <code>NameError</code> if the named
# variable does not exist, or an <code>IndexError</code> if the index
# is out of range.
# 
#    Customer = Struct.new(:name, :address, :zip)
#    joe = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
# 
#    joe["name"] = "Luke"
#    joe[:zip]   = "90210"
# 
#    joe.name   #=> "Luke"
#    joe.zip    #=> "90210"
def []=; Object.new; end
##
# Invokes the block passing in successive elements from
# <i>struct</i>, returning an array containing those elements
# for which the block returns a true value (equivalent to
# <code>Enumerable#select</code>).
# 
#    Lots = Struct.new(:a, :b, :c, :d, :e, :f)
#    l = Lots.new(11, 22, 33, 44, 55, 66)
#    l.select {|v| (v % 2).zero? }   #=> [22, 44, 66]
def select(&block); Enumerator.new; end
##
# Returns an array containing the elements in
# +self+ corresponding to the given selector(s). The selectors
# may be either integer indices or ranges.
# See also </code>.select<code>.
# 
#    a = %w{ a b c d e f }
#    a.values_at(1, 3, 5)
#    a.values_at(1, 3, 5, 7)
#    a.values_at(-1, -3, -5, -7)
#    a.values_at(1..3, 2...5)
def values_at(); []; end
##
# Returns an array of symbols representing the names of the instance
# variables.
# 
#    Customer = Struct.new(:name, :address, :zip)
#    joe = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
#    joe.members   #=> [:name, :address, :zip]
def members; []; end
end

##
# Raised when given an invalid regexp expression.
# 
#    Regexp.new("?")
# 
# <em>raises the exception:</em>
# 
#    RegexpError: target of repeat operator is not specified: /?/
class RegexpError < StandardError
end

##
# A <code>Regexp</code> holds a regular expression, used to match a pattern
# against strings. Regexps are created using the <code>/.../</code> and
# <code>%r{...}</code> literals, and by the <code>Regexp::new</code>
# constructor.
# 
# Regular expressions (<i>regexp</i>s) are patterns which describe the
# contents of a string. They're used for testing whether a string contains a
# given pattern, or extracting the portions that match. They are created
# with the <tt>/</tt><i>pat</i><tt>/</tt> and
# <tt>%r{</tt><i>pat</i><tt>}</tt> literals or the <tt>Regexp.new</tt>
# constructor.
# 
# A regexp is usually delimited with forward slashes (<tt>/</tt>). For
# example:
# 
#     /hay/ =~ 'haystack'   #=> 0
#     /y/.match('haystack') #=> #<MatchData "y">
# 
# If a string contains the pattern it is said to <i>match</i>. A literal
# string matches itself.
# 
#     # 'haystack' does not contain the pattern 'needle', so doesn't match.
#     /needle/.match('haystack') #=> nil
#     # 'haystack' does contain the pattern 'hay', so it matches
#     /hay/.match('haystack')    #=> #<MatchData "hay">
# 
# Specifically, <tt>/st/</tt> requires that the string contains the letter
# _s_ followed by the letter _t_, so it matches _haystack_, also.
# 
# == <tt>=~</tt> and Regexp#match
# 
# Pattern matching may be achieved by using <tt>=~</tt> operator or Regexp#match
# method.
# 
# === <tt>=~</tt> operator
# 
# <tt>=~</tt> is Ruby's basic pattern-matching operator.  When one operand is a
# regular expression and the other is a string then the regular expression is
# used as a pattern to match against the string.  (This operator is equivalently
# defined by Regexp and String so the order of String and Regexp do not matter.
# Other classes may have different implementations of <tt>=~</tt>.)  If a match
# is found, the operator returns index of first match in string, otherwise it
# returns +nil+.
# 
#     /hay/ =~ 'haystack'   #=> 0
#     'haystack' =~ /hay/   #=> 0
#     /a/   =~ 'haystack'   #=> 1
#     /u/   =~ 'haystack'   #=> nil
# 
# Using <tt>=~</tt> operator with a String and Regexp the <tt>$~</tt> global
# variable is set after a successful match.  <tt>$~</tt> holds a MatchData
# object. Regexp.last_match is equivalent to <tt>$~</tt>.
# 
# === Regexp#match method
# 
# #match method return a MatchData object :
# 
#     /st/.match('haystack')   #=> #<MatchData "st">
# 
# == Metacharacters and Escapes
# 
# The following are <i>metacharacters</i> <tt>(</tt>, <tt>)</tt>,
# <tt>[</tt>, <tt>]</tt>, <tt>{</tt>, <tt>}</tt>, <tt>.</tt>, <tt>?</tt>,
# <tt>+</tt>, <tt>*</tt>. They have a specific meaning when appearing in a
# pattern. To match them literally they must be backslash-escaped. To match
# a backslash literally backslash-escape that: <tt>\\\\\\</tt>.
# 
#     /1 \+ 2 = 3\?/.match('Does 1 + 2 = 3?') #=> #<MatchData "1 + 2 = 3?">
# 
# Patterns behave like double-quoted strings so can contain the same
# backslash escapes.
# 
#     /\s\u{6771 4eac 90fd}/.match("Go to 東京都")
#         #=> #<MatchData " 東京都">
# 
# Arbitrary Ruby expressions can be embedded into patterns with the
# <tt>#{...}</tt> construct.
# 
#     place = "東京都"
#     /#{place}/.match("Go to 東京都")
#         #=> #<MatchData "東京都">
# 
# == Character Classes
# 
# A <i>character class</i> is delimited with square brackets (<tt>[</tt>,
# <tt>]</tt>) and lists characters that may appear at that point in the
# match. <tt>/[ab]/</tt> means _a_ or _b_, as opposed to <tt>/ab/</tt> which
# means _a_ followed by _b_.
# 
#     /W[aeiou]rd/.match("Word") #=> #<MatchData "Word">
# 
# Within a character class the hyphen (<tt>-</tt>) is a metacharacter
# denoting an inclusive range of characters. <tt>[abcd]</tt> is equivalent
# to <tt>[a-d]</tt>. A range can be followed by another range, so
# <tt>[abcdwxyz]</tt> is equivalent to <tt>[a-dw-z]</tt>. The order in which
# ranges or individual characters appear inside a character class is
# irrelevant.
# 
#     /[0-9a-f]/.match('9f') #=> #<MatchData "9">
#     /[9f]/.match('9f')     #=> #<MatchData "9">
# 
# If the first character of a character class is a caret (<tt>^</tt>) the
# class is inverted: it matches any character _except_ those named.
# 
#     /[^a-eg-z]/.match('f') #=> #<MatchData "f">
# 
# A character class may contain another character class. By itself this
# isn't useful because <tt>[a-z[0-9]]</tt> describes the same set as
# <tt>[a-z0-9]</tt>. However, character classes also support the <tt>&&</tt>
# operator which performs set intersection on its arguments. The two can be
# combined as follows:
# 
#     /[a-w&&[^c-g]z]/ # ([a-w] AND ([^c-g] OR z))
#     # This is equivalent to:
#     /[abh-w]/
# 
# The following metacharacters also behave like character classes:
# 
# * <tt>/./</tt> - Any character except a newline.
# * <tt>/./m</tt> - Any character (the +m+ modifier enables multiline mode)
# * <tt>/\w/</tt> - A word character (<tt>[a-zA-Z0-9_]</tt>)
# * <tt>/\W/</tt> - A non-word character (<tt>[^a-zA-Z0-9_]</tt>)
# * <tt>/\d/</tt> - A digit character (<tt>[0-9]</tt>)
# * <tt>/\D/</tt> - A non-digit character (<tt>[^0-9]</tt>)
# * <tt>/\h/</tt> - A hexdigit character (<tt>[0-9a-fA-F]</tt>)
# * <tt>/\H/</tt> - A non-hexdigit character (<tt>[^0-9a-fA-F]</tt>)
# * <tt>/\s/</tt> - A whitespace character: <tt>/[ \t\r\n\f]/</tt>
# * <tt>/\S/</tt> - A non-whitespace character: <tt>/[^ \t\r\n\f]/</tt>
# 
# POSIX <i>bracket expressions</i> are also similar to character classes.
# They provide a portable alternative to the above, with the added benefit
# that they encompass non-ASCII characters. For instance, <tt>/\d/</tt>
# matches only the ASCII decimal digits (0-9); whereas <tt>/[[:digit:]]/</tt>
# matches any character in the Unicode _Nd_ category.
# 
# * <tt>/[[:alnum:]]/</tt> - Alphabetic and numeric character
# * <tt>/[[:alpha:]]/</tt> - Alphabetic character
# * <tt>/[[:blank:]]/</tt> - Space or tab
# * <tt>/[[:cntrl:]]/</tt> - Control character
# * <tt>/[[:digit:]]/</tt> - Digit
# * <tt>/[[:graph:]]/</tt> - Non-blank character (excludes spaces, control
#   characters, and similar)
# * <tt>/[[:lower:]]/</tt> - Lowercase alphabetical character
# * <tt>/[[:print:]]/</tt> - Like [:graph:], but includes the space character
# * <tt>/[[:punct:]]/</tt> - Punctuation character
# * <tt>/[[:space:]]/</tt> - Whitespace character (<tt>[:blank:]</tt>, newline,
#   carriage return, etc.)
# * <tt>/[[:upper:]]/</tt> - Uppercase alphabetical
# * <tt>/[[:xdigit:]]/</tt> - Digit allowed in a hexadecimal number (i.e.,
#   0-9a-fA-F)
# 
# Ruby also supports the following non-POSIX character classes:
# 
# * <tt>/[[:word:]]/</tt> - A character in one of the following Unicode
#   general categories _Letter_, _Mark_, _Number_,
#   <i>Connector_Punctuation</i>
# * <tt>/[[:ascii:]]/</tt> - A character in the ASCII character set
# 
#     # U+06F2 is "EXTENDED ARABIC-INDIC DIGIT TWO"
#     /[[:digit:]]/.match("\u06F2")    #=> #<MatchData "\u{06F2}">
#     /[[:upper:]][[:lower:]]/.match("Hello") #=> #<MatchData "He">
#     /[[:xdigit:]][[:xdigit:]]/.match("A6")  #=> #<MatchData "A6">
# 
# == Repetition
# 
# The constructs described so far match a single character. They can be
# followed by a repetition metacharacter to specify how many times they need
# to occur. Such metacharacters are called <i>quantifiers</i>.
# 
# * <tt>*</tt> - Zero or more times
# * <tt>+</tt> - One or more times
# * <tt>?</tt> - Zero or one times (optional)
# * <tt>{</tt><i>n</i><tt>}</tt> - Exactly <i>n</i> times
# * <tt>{</tt><i>n</i><tt>,}</tt> - <i>n</i> or more times
# * <tt>{,</tt><i>m</i><tt>}</tt> - <i>m</i> or less times
# * <tt>{</tt><i>n</i><tt>,</tt><i>m</i><tt>}</tt> - At least <i>n</i> and
#   at most <i>m</i> times
# 
#     # At least one uppercase character ('H'), at least one lowercase
#     # character ('e'), two 'l' characters, then one 'o'
#     "Hello".match(/[[:upper:]]+[[:lower:]]+l{2}o/) #=> #<MatchData "Hello">
# 
# Repetition is <i>greedy</i> by default: as many occurrences as possible
# are matched while still allowing the overall match to succeed. By
# contrast, <i>lazy</i> matching makes the minimal amount of matches
# necessary for overall success. A greedy metacharacter can be made lazy by
# following it with <tt>?</tt>.
# 
#     # Both patterns below match the string. The first uses a greedy
#     # quantifier so '.+' matches '<a><b>'; the second uses a lazy
#     # quantifier so '.+?' matches '<a>'.
#     /<.+>/.match("<a><b>")  #=> #<MatchData "<a><b>">
#     /<.+?>/.match("<a><b>") #=> #<MatchData "<a>">
# 
# A quantifier followed by <tt>+</tt> matches <i>possessively</i>: once it
# has matched it does not backtrack. They behave like greedy quantifiers,
# but having matched they refuse to "give up" their match even if this
# jeopardises the overall match.
# 
# == Capturing
# 
# Parentheses can be used for <i>capturing</i>. The text enclosed by the
# <i>n</i><sup>th</sup> group of parentheses can be subsequently referred to
# with <i>n</i>. Within a pattern use the <i>backreference</i>
# <tt>\n</tt>; outside of the pattern use
# <tt>MatchData[</tt><i>n</i><tt>]</tt>.
# 
#     # 'at' is captured by the first group of parentheses, then referred to
#     # later with \1
#     /[csh](..) [csh]\1 in/.match("The cat sat in the hat")
#         #=> #<MatchData "cat sat in" 1:"at">
#     # Regexp#match returns a MatchData object which makes the captured
#     # text available with its #[] method.
#     /[csh](..) [csh]\1 in/.match("The cat sat in the hat")[1] #=> 'at'
# 
# Capture groups can be referred to by name when defined with the
# <tt>(?<</tt><i>name</i><tt>>)</tt> or <tt>(?'</tt><i>name</i><tt>')</tt>
# constructs.
# 
#     /\$(?<dollars>\d+)\.(?<cents>\d+)/.match("$3.67")
#         => #<MatchData "$3.67" dollars:"3" cents:"67">
#     /\$(?<dollars>\d+)\.(?<cents>\d+)/.match("$3.67")[:dollars] #=> "3"
# 
# Named groups can be backreferenced with <tt>\k<</tt><i>name</i><tt>></tt>,
# where _name_ is the group name.
# 
#     /(?<vowel>[aeiou]).\k<vowel>.\k<vowel>/.match('ototomy')
#         #=> #<MatchData "ototo" vowel:"o">
# 
# *Note*: A regexp can't use named backreferences and numbered
# backreferences simultaneously.
# 
# When named capture groups are used with a literal regexp on the left-hand
# side of an expression and the <tt>=~</tt> operator, the captured text is
# also assigned to local variables with corresponding names.
# 
#     /\$(?<dollars>\d+)\.(?<cents>\d+)/ =~ "$3.67" #=> 0
#     dollars #=> "3"
# 
# == Grouping
# 
# Parentheses also <i>group</i> the terms they enclose, allowing them to be
# quantified as one <i>atomic</i> whole.
# 
#     # The pattern below matches a vowel followed by 2 word characters:
#     # 'aen'
#     /[aeiou]\w{2}/.match("Caenorhabditis elegans") #=> #<MatchData "aen">
#     # Whereas the following pattern matches a vowel followed by a word
#     # character, twice, i.e. <tt>[aeiou]\w[aeiou]\w</tt>: 'enor'.
#     /([aeiou]\w){2}/.match("Caenorhabditis elegans")
#         #=> #<MatchData "enor" 1:"or">
# 
# The <tt>(?:</tt>...<tt>)</tt> construct provides grouping without
# capturing. That is, it combines the terms it contains into an atomic whole
# without creating a backreference. This benefits performance at the slight
# expense of readability.
# 
#     # The group of parentheses captures 'n' and the second 'ti'. The
#     # second group is referred to later with the backreference \2
#     /I(n)ves(ti)ga\2ons/.match("Investigations")
#         #=> #<MatchData "Investigations" 1:"n" 2:"ti">
#     # The first group of parentheses is now made non-capturing with '?:',
#     # so it still matches 'n', but doesn't create the backreference. Thus,
#     # the backreference \1 now refers to 'ti'.
#     /I(?:n)ves(ti)ga\1ons/.match("Investigations")
#         #=> #<MatchData "Investigations" 1:"ti">
# 
# === Atomic Grouping
# 
# Grouping can be made <i>atomic</i> with
# <tt>(?></tt><i>pat</i><tt>)</tt>. This causes the subexpression <i>pat</i>
# to be matched independently of the rest of the expression such that what
# it matches becomes fixed for the remainder of the match, unless the entire
# subexpression must be abandoned and subsequently revisited. In this
# way <i>pat</i> is treated as a non-divisible whole. Atomic grouping is
# typically used to optimise patterns so as to prevent the regular
# expression engine from backtracking needlessly.
# 
#     # The <tt>"</tt> in the pattern below matches the first character of
#     # the string, then <tt>.*</tt> matches <i>Quote"</i>. This causes the
#     # overall match to fail, so the text matched by <tt>.*</tt> is
#     # backtracked by one position, which leaves the final character of the
#     # string available to match <tt>"</tt>
#           /".*"/.match('"Quote"')     #=> #<MatchData "\"Quote\"">
#     # If <tt>.*</tt> is grouped atomically, it refuses to backtrack
#     # <i>Quote"</i>, even though this means that the overall match fails
#     /"(?>.*)"/.match('"Quote"') #=> nil
# 
# == Subexpression Calls
# 
# The <tt>\g<</tt><i>name</i><tt>></tt> syntax matches the previous
# subexpression named _name_, which can be a group name or number, again.
# This differs from backreferences in that it re-executes the group rather
# than simply trying to re-match the same text.
# 
#     # Matches a <i>(</i> character and assigns it to the <tt>paren</tt>
#     # group, tries to call that the <tt>paren</tt> sub-expression again
#     # but fails, then matches a literal <i>)</i>.
#     /\A(?<paren>\(\g<paren>*\))*\z/ =~ '()'
# 
# 
#     /\A(?<paren>\(\g<paren>*\))*\z/ =~ '(())' #=> 0
#     # ^1
#     #      ^2
#     #           ^3
#     #                 ^4
#     #      ^5
#     #           ^6
#     #                      ^7
#     #                       ^8
#     #                       ^9
#     #                           ^10
# 
# 1.  Matches at the beginning of the string, i.e. before the first
#     character.
# 2.  Enters a named capture group called <tt>paren</tt>
# 3.  Matches a literal <i>(</i>, the first character in the string
# 4.  Calls the <tt>paren</tt> group again, i.e. recurses back to the
#     second step
# 5.  Re-enters the <tt>paren</tt> group
# 6.  Matches a literal <i>(</i>, the second character in the
#     string
# 7.  Try to call <tt>paren</tt> a third time, but fail because
#     doing so would prevent an overall successful match
# 8.  Match a literal <i>)</i>, the third character in the string.
#     Marks the end of the second recursive call
# 9.  Match a literal <i>)</i>, the fourth character in the string
# 10. Match the end of the string
# 
# == Alternation
# 
# The vertical bar metacharacter (<tt>|</tt>) combines two expressions into
# a single one that matches either of the expressions. Each expression is an
# <i>alternative</i>.
# 
#     /\w(and|or)\w/.match("Feliformia") #=> #<MatchData "form" 1:"or">
#     /\w(and|or)\w/.match("furandi")    #=> #<MatchData "randi" 1:"and">
#     /\w(and|or)\w/.match("dissemblance") #=> nil
# 
# == Character Properties
# 
# The <tt>\p{}</tt> construct matches characters with the named property,
# much like POSIX bracket classes.
# 
# * <tt>/\p{Alnum}/</tt> - Alphabetic and numeric character
# * <tt>/\p{Alpha}/</tt> - Alphabetic character
# * <tt>/\p{Blank}/</tt> - Space or tab
# * <tt>/\p{Cntrl}/</tt> - Control character
# * <tt>/\p{Digit}/</tt> - Digit
# * <tt>/\p{Graph}/</tt> - Non-blank character (excludes spaces, control
#   characters, and similar)
# * <tt>/\p{Lower}/</tt> - Lowercase alphabetical character
# * <tt>/\p{Print}/</tt> - Like <tt>\p{Graph}</tt>, but includes the space character
# * <tt>/\p{Punct}/</tt> - Punctuation character
# * <tt>/\p{Space}/</tt> - Whitespace character (<tt>[:blank:]</tt>, newline,
#   carriage return, etc.)
# * <tt>/\p{Upper}/</tt> - Uppercase alphabetical
# * <tt>/\p{XDigit}/</tt> - Digit allowed in a hexadecimal number (i.e., 0-9a-fA-F)
# * <tt>/\p{Word}/</tt> - A member of one of the following Unicode general
#   category <i>Letter</i>, <i>Mark</i>, <i>Number</i>,
#   <i>Connector\_Punctuation</i>
# * <tt>/\p{ASCII}/</tt> - A character in the ASCII character set
# * <tt>/\p{Any}/</tt> - Any Unicode character (including unassigned
#   characters)
# * <tt>/\p{Assigned}/</tt> - An assigned character
# 
# A Unicode character's <i>General Category</i> value can also be matched
# with <tt>\p{</tt><i>Ab</i><tt>}</tt> where <i>Ab</i> is the category's
# abbreviation as described below:
# 
# * <tt>/\p{L}/</tt> - 'Letter'
# * <tt>/\p{Ll}/</tt> - 'Letter: Lowercase'
# * <tt>/\p{Lm}/</tt> - 'Letter: Mark'
# * <tt>/\p{Lo}/</tt> - 'Letter: Other'
# * <tt>/\p{Lt}/</tt> - 'Letter: Titlecase'
# * <tt>/\p{Lu}/</tt> - 'Letter: Uppercase
# * <tt>/\p{Lo}/</tt> - 'Letter: Other'
# * <tt>/\p{M}/</tt> - 'Mark'
# * <tt>/\p{Mn}/</tt> - 'Mark: Nonspacing'
# * <tt>/\p{Mc}/</tt> - 'Mark: Spacing Combining'
# * <tt>/\p{Me}/</tt> - 'Mark: Enclosing'
# * <tt>/\p{N}/</tt> - 'Number'
# * <tt>/\p{Nd}/</tt> - 'Number: Decimal Digit'
# * <tt>/\p{Nl}/</tt> - 'Number: Letter'
# * <tt>/\p{No}/</tt> - 'Number: Other'
# * <tt>/\p{P}/</tt> - 'Punctuation'
# * <tt>/\p{Pc}/</tt> - 'Punctuation: Connector'
# * <tt>/\p{Pd}/</tt> - 'Punctuation: Dash'
# * <tt>/\p{Ps}/</tt> - 'Punctuation: Open'
# * <tt>/\p{Pe}/</tt> - 'Punctuation: Close'
# * <tt>/\p{Pi}/</tt> - 'Punctuation: Initial Quote'
# * <tt>/\p{Pf}/</tt> - 'Punctuation: Final Quote'
# * <tt>/\p{Po}/</tt> - 'Punctuation: Other'
# * <tt>/\p{S}/</tt> - 'Symbol'
# * <tt>/\p{Sm}/</tt> - 'Symbol: Math'
# * <tt>/\p{Sc}/</tt> - 'Symbol: Currency'
# * <tt>/\p{Sc}/</tt> - 'Symbol: Currency'
# * <tt>/\p{Sk}/</tt> - 'Symbol: Modifier'
# * <tt>/\p{So}/</tt> - 'Symbol: Other'
# * <tt>/\p{Z}/</tt> - 'Separator'
# * <tt>/\p{Zs}/</tt> - 'Separator: Space'
# * <tt>/\p{Zl}/</tt> - 'Separator: Line'
# * <tt>/\p{Zp}/</tt> - 'Separator: Paragraph'
# * <tt>/\p{C}/</tt> - 'Other'
# * <tt>/\p{Cc}/</tt> - 'Other: Control'
# * <tt>/\p{Cf}/</tt> - 'Other: Format'
# * <tt>/\p{Cn}/</tt> - 'Other: Not Assigned'
# * <tt>/\p{Co}/</tt> - 'Other: Private Use'
# * <tt>/\p{Cs}/</tt> - 'Other: Surrogate'
# 
# Lastly, <tt>\p{}</tt> matches a character's Unicode <i>script</i>. The
# following scripts are supported: <i>Arabic</i>, <i>Armenian</i>,
# <i>Balinese</i>, <i>Bengali</i>, <i>Bopomofo</i>, <i>Braille</i>,
# <i>Buginese</i>, <i>Buhid</i>, <i>Canadian_Aboriginal</i>, <i>Carian</i>,
# <i>Cham</i>, <i>Cherokee</i>, <i>Common</i>, <i>Coptic</i>,
# <i>Cuneiform</i>, <i>Cypriot</i>, <i>Cyrillic</i>, <i>Deseret</i>,
# <i>Devanagari</i>, <i>Ethiopic</i>, <i>Georgian</i>, <i>Glagolitic</i>,
# <i>Gothic</i>, <i>Greek</i>, <i>Gujarati</i>, <i>Gurmukhi</i>, <i>Han</i>,
# <i>Hangul</i>, <i>Hanunoo</i>, <i>Hebrew</i>, <i>Hiragana</i>,
# <i>Inherited</i>, <i>Kannada</i>, <i>Katakana</i>, <i>Kayah_Li</i>,
# <i>Kharoshthi</i>, <i>Khmer</i>, <i>Lao</i>, <i>Latin</i>, <i>Lepcha</i>,
# <i>Limbu</i>, <i>Linear_B</i>, <i>Lycian</i>, <i>Lydian</i>,
# <i>Malayalam</i>, <i>Mongolian</i>, <i>Myanmar</i>, <i>New_Tai_Lue</i>,
# <i>Nko</i>, <i>Ogham</i>, <i>Ol_Chiki</i>, <i>Old_Italic</i>,
# <i>Old_Persian</i>, <i>Oriya</i>, <i>Osmanya</i>, <i>Phags_Pa</i>,
# <i>Phoenician</i>, <i>Rejang</i>, <i>Runic</i>, <i>Saurashtra</i>,
# <i>Shavian</i>, <i>Sinhala</i>, <i>Sundanese</i>, <i>Syloti_Nagri</i>,
# <i>Syriac</i>, <i>Tagalog</i>, <i>Tagbanwa</i>, <i>Tai_Le</i>,
# <i>Tamil</i>, <i>Telugu</i>, <i>Thaana</i>, <i>Thai</i>, <i>Tibetan</i>,
# <i>Tifinagh</i>, <i>Ugaritic</i>, <i>Vai</i>, and <i>Yi</i>.
# 
#     # Unicode codepoint U+06E9 is named "ARABIC PLACE OF SAJDAH" and
#     # belongs to the Arabic script.
#     /\p{Arabic}/.match("\u06E9") #=> #<MatchData "\u06E9">
# 
# All character properties can be inverted by prefixing their name with a
# caret (<tt>^</tt>).
# 
#     # Letter 'A' is not in the Unicode Ll (Letter; Lowercase) category, so
#     # this match succeeds
#     /\p{^Ll}/.match("A") #=> #<MatchData "A">
# 
# == Anchors
# 
# Anchors are metacharacter that match the zero-width positions between
# characters, <i>anchoring</i> the match to a specific position.
# 
# * <tt>^</tt> - Matches beginning of line
# * <tt>$</tt> - Matches end of line
# * <tt>\A</tt> - Matches beginning of string.
# * <tt>\Z</tt> - Matches end of string. If string ends with a newline,
#   it matches just before newline
# * <tt>\z</tt> - Matches end of string
# * <tt>\G</tt> - Matches point where last match finished
# * <tt>\b</tt> - Matches word boundaries when outside brackets;
#   backspace (0x08) when inside brackets
# * <tt>\B</tt> - Matches non-word boundaries
# * <tt>(?=</tt><i>pat</i><tt>)</tt> - <i>Positive lookahead</i> assertion:
#   ensures that the following characters match <i>pat</i>, but doesn't
#   include those characters in the matched text
# * <tt>(?!</tt><i>pat</i><tt>)</tt> - <i>Negative lookahead</i> assertion:
#   ensures that the following characters do not match <i>pat</i>, but
#   doesn't include those characters in the matched text
# * <tt>(?<=</tt><i>pat</i><tt>)</tt> - <i>Positive lookbehind</i>
#   assertion: ensures that the preceding characters match <i>pat</i>, but
#   doesn't include those characters in the matched text
# * <tt>(?<!</tt><i>pat</i><tt>)</tt> - <i>Negative lookbehind</i>
#   assertion: ensures that the preceding characters do not match
#   <i>pat</i>, but doesn't include those characters in the matched text
# 
#     # If a pattern isn't anchored it can begin at any point in the string
#     /real/.match("surrealist") #=> #<MatchData "real">
#     # Anchoring the pattern to the beginning of the string forces the
#     # match to start there. 'real' doesn't occur at the beginning of the
#     # string, so now the match fails
#     /\Areal/.match("surrealist") #=> nil
#     # The match below fails because although 'Demand' contains 'and', the
#     pattern does not occur at a word boundary.
#     /\band/.match("Demand")
#     # Whereas in the following example 'and' has been anchored to a
#     # non-word boundary so instead of matching the first 'and' it matches
#     # from the fourth letter of 'demand' instead
#     /\Band.+/.match("Supply and demand curve") #=> #<MatchData "and curve">
#     # The pattern below uses positive lookahead and positive lookbehind to
#     # match text appearing in <b></b> tags without including the tags in the
#     # match
#     /(?<=<b>)\w+(?=<\/b>)/.match("Fortune favours the <b>bold</b>")
#         #=> #<MatchData "bold">
# 
# == Options
# 
# The end delimiter for a regexp can be followed by one or more single-letter
# options which control how the pattern can match.
# 
# * <tt>/pat/i</tt> - Ignore case
# * <tt>/pat/m</tt> - Treat a newline as a character matched by <tt>.</tt>
# * <tt>/pat/x</tt> - Ignore whitespace and comments in the pattern
# * <tt>/pat/o</tt> - Perform <tt>#{}</tt> interpolation only once
# 
# <tt>i</tt>, <tt>m</tt>, and <tt>x</tt> can also be applied on the
# subexpression level with the
# <tt>(?</tt><i>on</i><tt>-</tt><i>off</i><tt>)</tt> construct, which
# enables options <i>on</i>, and disables options <i>off</i> for the
# expression enclosed by the parentheses.
# 
#     /a(?i:b)c/.match('aBc') #=> #<MatchData "aBc">
#     /a(?i:b)c/.match('abc') #=> #<MatchData "abc">
# 
# Options may also be used with <tt>Regexp.new</tt>:
# 
#     Regexp.new("abc", Regexp::IGNORECASE)                     #=> /abc/i
#     Regexp.new("abc", Regexp::MULTILINE)                      #=> /abc/m
#     Regexp.new("abc # Comment", Regexp::EXTENDED)             #=> /abc # Comment/x
#     Regexp.new("abc", Regexp::IGNORECASE | Regexp::MULTILINE) #=> /abc/mi
# 
# == Free-Spacing Mode and Comments
# 
# As mentioned above, the <tt>x</tt> option enables <i>free-spacing</i>
# mode. Literal white space inside the pattern is ignored, and the
# octothorpe (<tt>#</tt>) character introduces a comment until the end of
# the line. This allows the components of the pattern to be organised in a
# potentially more readable fashion.
# 
#     # A contrived pattern to match a number with optional decimal places
#     float_pat = /\A
#         [[:digit:]]+ # 1 or more digits before the decimal point
#         (\.          # Decimal point
#             [[:digit:]]+ # 1 or more digits after the decimal point
#         )? # The decimal point and following digits are optional
#     \Z/x
#     float_pat.match('3.14') #=> #<MatchData "3.14" 1:".14">
# 
# *Note*: To match whitespace in an <tt>x</tt> pattern use an escape such as
# <tt>\s</tt> or <tt>\p{Space}</tt>.
# 
# Comments can be included in a non-<tt>x</tt> pattern with the
# <tt>(?#</tt><i>comment</i><tt>)</tt> construct, where <i>comment</i> is
# arbitrary text ignored by the regexp engine.
# 
# == Encoding
# 
# Regular expressions are assumed to use the source encoding. This can be
# overridden with one of the following modifiers.
# 
# * <tt>/</tt><i>pat</i><tt>/u</tt> - UTF-8
# * <tt>/</tt><i>pat</i><tt>/e</tt> - EUC-JP
# * <tt>/</tt><i>pat</i><tt>/s</tt> - Windows-31J
# * <tt>/</tt><i>pat</i><tt>/n</tt> - ASCII-8BIT
# 
# A regexp can be matched against a string when they either share an
# encoding, or the regexp's encoding is _US-ASCII_ and the string's encoding
# is ASCII-compatible.
# 
# If a match between incompatible encodings is attempted an
# <tt>Encoding::CompatibilityError</tt> exception is raised.
# 
# The <tt>Regexp#fixed_encoding?</tt> predicate indicates whether the regexp
# has a <i>fixed</i> encoding, that is one incompatible with ASCII. A
# regexp's encoding can be explicitly fixed by supplying
# <tt>Regexp::FIXEDENCODING</tt> as the second argument of
# <tt>Regexp.new</tt>:
# 
#     r = Regexp.new("a".force_encoding("iso-8859-1"),Regexp::FIXEDENCODING)
#     r =~"a\u3042"
#        #=> Encoding::CompatibilityError: incompatible encoding regexp match
#             (ISO-8859-1 regexp with UTF-8 string)
# 
# == Special global variables
# 
# Pattern matching sets some global variables :
# * <tt>$~</tt> is equivalent to Regexp.last_match;
# * <tt>$&</tt> contains the complete matched text;
# * <tt>$`</tt> contains string before match;
# * <tt>$'</tt> contains string after match;
# * <tt>$1</tt>, <tt>$2</tt> and so on contain text matching first, second, etc
#   capture group;
# * <tt>$+</tt> contains last capture group.
# 
# Example:
# 
#     m = /s(\w{2}).*(c)/.match('haystack') #=> #<MatchData "stac" 1:"ta" 2:"c">
#     $~                                    #=> #<MatchData "stac" 1:"ta" 2:"c">
#     Regexp.latch_match                    #=> #<MatchData "stac" 1:"ta" 2:"c">
# 
#     $&      #=> "stac"
#             # same as m[0]
#     $`      #=> "hay"
#             # same as m.pre_match
#     $'      #=> "k"
#             # same as m.post_match
#     $1      #=> "ta"
#             # same as m[1]
#     $2      #=> "c"
#             # same as m[2]
#     $3      #=> nil
#             # no third group in pattern
#     $+      #=> "c"
#             # same as m[-1]
# 
# These global variables are thread-local and method-local variables.
# 
# == Performance
# 
# Certain pathological combinations of constructs can lead to abysmally bad
# performance.
# 
# Consider a string of 25 <i>a</i>s, a <i>d</i>, 4 <i>a</i>s, and a
# <i>c</i>.
# 
#     s = 'a' * 25 + 'd' + 'a' * 4 + 'c'
#     #=> "aaaaaaaaaaaaaaaaaaaaaaaaadaaaac"
# 
# The following patterns match instantly as you would expect:
# 
#     /(b|a)/ =~ s #=> 0
#     /(b|a+)/ =~ s #=> 0
#     /(b|a+)*\/ =~ s #=> 0
# 
# However, the following pattern takes appreciably longer:
# 
#     /(b|a+)*c/ =~ s #=> 26
# 
# This happens because an atom in the regexp is quantified by both an
# immediate <tt>+</tt> and an enclosing <tt>*</tt> with nothing to
# differentiate which is in control of any particular character. The
# nondeterminism that results produces super-linear performance. (Consult
# <i>Mastering Regular Expressions</i> (3rd ed.), pp 222, by
# <i>Jeffery Friedl</i>, for an in-depth analysis). This particular case
# can be fixed by use of atomic grouping, which prevents the unnecessary
# backtracking:
# 
#     (start = Time.now) && /(b|a+)*c/ =~ s && (Time.now - start)
#        #=> 24.702736882
#     (start = Time.now) && /(?>b|a+)*c/ =~ s && (Time.now - start)
#        #=> 0.000166571
# 
# A similar case is typified by the following example, which takes
# approximately 60 seconds to execute for me:
# 
#     # Match a string of 29 <i>a</i>s against a pattern of 29 optional
#     # <i>a</i>s followed by 29 mandatory <i>a</i>s.
#     Regexp.new('a?' * 29 + 'a' * 29) =~ 'a' * 29
# 
# The 29 optional <i>a</i>s match the string, but this prevents the 29
# mandatory <i>a</i>s that follow from matching. Ruby must then backtrack
# repeatedly so as to satisfy as many of the optional matches as it can
# while still matching the mandatory 29. It is plain to us that none of the
# optional matches can succeed, but this fact unfortunately eludes Ruby.
# 
# The best way to improve performance is to significantly reduce the amount of
# backtracking needed.  For this case, instead of individually matching 29
# optional <i>a</i>s, a range of optional <i>a</i>s can be matched all at once
# with <i>a{0,29}</i>:
# 
#     Regexp.new('a{0,29}' + 'a' * 29) =~ 'a' * 29
class Regexp < Object
##
# Escapes any characters that would have special meaning in a regular
# expression. Returns a new escaped string, or self if no characters are
# escaped.  For any string,
# <code>Regexp.new(Regexp.escape(<i>str</i>))=~<i>str</i></code> will be true.
# 
#    Regexp.escape('\*?{}.')   #=> \\\*\?\{\}\.
def self.escape(str); ''; end
##
# Escapes any characters that would have special meaning in a regular
# expression. Returns a new escaped string, or self if no characters are
# escaped.  For any string,
# <code>Regexp.new(Regexp.escape(<i>str</i>))=~<i>str</i></code> will be true.
# 
#    Regexp.escape('\*?{}.')   #=> \\\*\?\{\}\.
def self.quote(str); ''; end
##
# Return a <code>Regexp</code> object that is the union of the given
# <em>pattern</em>s, i.e., will match any of its parts. The <em>pattern</em>s
# can be Regexp objects, in which case their options will be preserved, or
# Strings. If no patterns are given, returns <code>/(?!)/</code>.
# The behavior is unspecified if any given <em>pattern</em> contains capture.
# 
#    Regexp.union                         #=> /(?!)/
#    Regexp.union("penzance")             #=> /penzance/
#    Regexp.union("a+b*c")                #=> /a\+b\*c/
#    Regexp.union("skiing", "sledding")   #=> /skiing|sledding/
#    Regexp.union(["skiing", "sledding"]) #=> /skiing|sledding/
#    Regexp.union(/dogs/, /cats/i)        #=> /(?-mix:dogs)|(?i-mx:cats)/
def self.union(); //; end
##
# The first form returns the MatchData object generated by the
# last successful pattern match.  Equivalent to reading the special global
# variable <code>$~</code> (see Special global variables in Regexp for
# details).
# 
# The second form returns the <i>n</i>th field in this MatchData object.
# _n_ can be a string or symbol to reference a named capture.
# 
# Note that the last_match is local to the thread and method scope of the
# method that did the pattern match.
# 
#    /c(.)t/ =~ 'cat'        #=> 0
#    Regexp.last_match       #=> #<MatchData "cat" 1:"a">
#    Regexp.last_match(0)    #=> "cat"
#    Regexp.last_match(1)    #=> "a"
#    Regexp.last_match(2)    #=> nil
# 
#    /(?<lhs>\w+)\s*=\s*(?<rhs>\w+)/ =~ "var = val"
#    Regexp.last_match       #=> #<MatchData "var = val" lhs:"var" rhs:"val">
#    Regexp.last_match(:lhs) #=> "var"
#    Regexp.last_match(:rhs) #=> "val"
def self.last_match; ''; end
##
# Try to convert <i>obj</i> into a Regexp, using to_regexp method.
# Returns converted regexp or nil if <i>obj</i> cannot be converted
# for any reason.
# 
#    Regexp.try_convert(/re/)         #=> /re/
#    Regexp.try_convert("re")         #=> nil
# 
#    o = Object.new
#    Regexp.try_convert(o)            #=> nil
#    def o.to_regexp() /foo/ end
#    Regexp.try_convert(o)            #=> /foo/
def self.try_convert(obj); // || nil; end
##
# Constructs a new regular expression from +pattern+, which can be either a
# String or a Regexp (in which case that regexp's options are propagated),
# and new options may not be specified (a change as of Ruby 1.8).
# 
# If +options+ is a Fixnum, it should be one or more of the constants
# Regexp::EXTENDED, Regexp::IGNORECASE, and Regexp::MULTILINE,
# <em>or</em>-ed together.  Otherwise, if +options+ is not
# +nil+ or +false+, the regexp will be case insensitive.
# 
# When the +kcode+ parameter is `n' or `N' sets the regexp no encoding.
# It means that the regexp is for binary strings.
# 
#   r1 = Regexp.new('^a-z+:\\s+\w+') #=> /^a-z+:\s+\w+/
#   r2 = Regexp.new('cat', true)     #=> /cat/i
#   r3 = Regexp.new(r2)              #=> /cat/i
#   r4 = Regexp.new('dog', Regexp::EXTENDED | Regexp::IGNORECASE) #=> /dog/ix
def self.new(string, options=0, kcode=0); end
##
# Constructs a new regular expression from +pattern+, which can be either a
# String or a Regexp (in which case that regexp's options are propagated),
# and new options may not be specified (a change as of Ruby 1.8).
# 
# If +options+ is a Fixnum, it should be one or more of the constants
# Regexp::EXTENDED, Regexp::IGNORECASE, and Regexp::MULTILINE,
# <em>or</em>-ed together.  Otherwise, if +options+ is not
# +nil+ or +false+, the regexp will be case insensitive.
# 
# When the +kcode+ parameter is `n' or `N' sets the regexp no encoding.
# It means that the regexp is for binary strings.
# 
#   r1 = Regexp.new('^a-z+:\\s+\w+') #=> /^a-z+:\s+\w+/
#   r2 = Regexp.new('cat', true)     #=> /cat/i
#   r3 = Regexp.new(r2)              #=> /cat/i
#   r4 = Regexp.new('dog', Regexp::EXTENDED | Regexp::IGNORECASE) #=> /dog/ix
def self.compile(string, options=0, kcode=0); //; end
##
# Produce a hash based on the text and options of this regular expression.
def hash; 0; end
##
# Equality---Two regexps are equal if their patterns are identical, they have
# the same character set code, and their <code>casefold?</code> values are the
# same.
# 
#    /abc/  == /abc/x   #=> false
#    /abc/  == /abc/i   #=> false
#    /abc/  == /abc/u   #=> false
#    /abc/u == /abc/n   #=> false
def eql?; true || false; end
##
# Equality---Two regexps are equal if their patterns are identical, they have
# the same character set code, and their <code>casefold?</code> values are the
# same.
# 
#    /abc/  == /abc/x   #=> false
#    /abc/  == /abc/i   #=> false
#    /abc/  == /abc/u   #=> false
#    /abc/u == /abc/n   #=> false
def ==; true || false; end
##
# Match---Matches <i>rxp</i> against <i>str</i>.
# 
#    /at/ =~ "input data"   #=> 7
#    /ax/ =~ "input data"   #=> nil
# 
# If <code>=~</code> is used with a regexp literal with named captures,
# captured strings (or nil) is assigned to local variables named by
# the capture names.
# 
#    /(?<lhs>\w+)\s*=\s*(?<rhs>\w+)/ =~ "  x = y  "
#    p lhs    #=> "x"
#    p rhs    #=> "y"
# 
# If it is not matched, nil is assigned for the variables.
# 
#    /(?<lhs>\w+)\s*=\s*(?<rhs>\w+)/ =~ "  x = "
#    p lhs    #=> nil
#    p rhs    #=> nil
# 
# This assignment is implemented in the Ruby parser.
# The parser detects 'regexp-literal =~ expression' for the assignment.
# The regexp must be a literal without interpolation and placed at left hand side.
# 
# The assignment does not occur if the regexp is not a literal.
# 
#    re = /(?<lhs>\w+)\s*=\s*(?<rhs>\w+)/
#    re =~ "  x = y  "
#    p lhs    # undefined local variable
#    p rhs    # undefined local variable
# 
# A regexp interpolation, <code>#{}</code>, also disables
# the assignment.
# 
#    rhs_pat = /(?<rhs>\w+)/
#    /(?<lhs>\w+)\s*=\s*#{rhs_pat}/ =~ "x = y"
#    p lhs    # undefined local variable
# 
# The assignment does not occur if the regexp is placed at the right hand side.
# 
#   "  x = y  " =~ /(?<lhs>\w+)\s*=\s*(?<rhs>\w+)/
#   p lhs, rhs # undefined local variable
def =~; 1 || nil; end
##
# Case Equality---Used in case statements.
# 
#    a = "HELLO"
#    case a
#    when /^[a-z]*$/; print "Lower case\n"
#    when /^[A-Z]*$/; print "Upper case\n"
#    else;            print "Mixed case\n"
#    end
#    #=> "Upper case"
# 
# Following a regular expression literal with the #=== operator allows you to
# compare against a String.
# 
#     /^[a-z]*$/ === "HELLO" #=> false
#     /^[A-Z]*$/ === "HELLO" #=> true
def ===; true || false; end
##
# Match---Matches <i>rxp</i> against the contents of <code>$_</code>.
# Equivalent to <code><i>rxp</i> =~ $_</code>.
# 
#    $_ = "input data"
#    ~ /at/   #=> 7
def ~; 1 || nil; end
##
# Returns a <code>MatchData</code> object describing the match, or
# <code>nil</code> if there was no match. This is equivalent to retrieving the
# value of the special variable <code>$~</code> following a normal match.
# If the second parameter is present, it specifies the position in the string
# to begin the search.
# 
#    /(.)(.)(.)/.match("abc")[2]   #=> "b"
#    /(.)(.)/.match("abc", 1)[2]   #=> "c"
# 
# If a block is given, invoke the block with MatchData if match succeed, so
# that you can write
# 
#    pat.match(str) {|m| ...}
# 
# instead of
# 
#    if m = pat.match(str)
#      ...
#    end
# 
# The return value is a value from block execution in this case.
def match(str); MatchData.new || nil; end
##
# Returns a string containing the regular expression and its options (using the
# <code>(?opts:source)</code> notation. This string can be fed back in to
# <code>Regexp::new</code> to a regular expression with the same semantics as
# the original. (However, <code>Regexp#==</code> may not return true when
# comparing the two, as the source of the regular expression itself may
# differ, as the example shows).  <code>Regexp#inspect</code> produces a
# generally more readable version of <i>rxp</i>.
# 
#     r1 = /ab+c/ix           #=> /ab+c/ix
#     s1 = r1.to_s            #=> "(?ix-m:ab+c)"
#     r2 = Regexp.new(s1)     #=> /(?ix-m:ab+c)/
#     r1 == r2                #=> false
#     r1.source               #=> "ab+c"
#     r2.source               #=> "(?ix-m:ab+c)"
def to_s; ''; end
##
# Produce a nicely formatted string-version of _rxp_. Perhaps surprisingly,
# <code>#inspect</code> actually produces the more natural version of
# the string than <code>#to_s</code>.
# 
#      /ab+c/ix.inspect        #=> "/ab+c/ix"
def inspect; ''; end
##
# Returns the original string of the pattern.
# 
#     /ab+c/ix.source #=> "ab+c"
# 
# Note that escape sequences are retained as is.
# 
#    /\x20\+/.source  #=> "\\x20\\+"
def source; ''; end
##
# Returns the value of the case-insensitive flag.
# 
#     /a/.casefold?           #=> false
#     /a/i.casefold?          #=> true
#     /(?i:a)/.casefold?      #=> false
def casefold?; true || false; end
##
# Returns the set of bits corresponding to the options used when creating this
# Regexp (see <code>Regexp::new</code> for details. Note that additional bits
# may be set in the returned options: these are used internally by the regular
# expression code. These extra bits are ignored if the options are passed to
# <code>Regexp::new</code>.
# 
#    Regexp::IGNORECASE                  #=> 1
#    Regexp::EXTENDED                    #=> 2
#    Regexp::MULTILINE                   #=> 4
# 
#    /cat/.options                       #=> 0
#    /cat/ix.options                     #=> 3
#    Regexp.new('cat', true).options     #=> 1
#    /\xa1\xa2/e.options                 #=> 16
# 
#    r = /cat/ix
#    Regexp.new(r.source, r.options)     #=> /cat/ix
def options; 0; end
##
# Returns the Encoding object that represents the encoding of obj.
def encoding; Encoding.new; end
##
# Returns false if rxp is applicable to
# a string with any ASCII compatible encoding.
# Returns true otherwise.
# 
#     r = /a/
#     r.fixed_encoding?                               #=> false
#     r =~ "\u{6666} a"                               #=> 2
#     r =~ "\xa1\xa2 a".force_encoding("euc-jp")      #=> 2
#     r =~ "abc".force_encoding("euc-jp")             #=> 0
# 
#     r = /a/u
#     r.fixed_encoding?                               #=> true
#     r.encoding                                      #=> #<Encoding:UTF-8>
#     r =~ "\u{6666} a"                               #=> 2
#     r =~ "\xa1\xa2".force_encoding("euc-jp")        #=> ArgumentError
#     r =~ "abc".force_encoding("euc-jp")             #=> 0
# 
#     r = /\u{6666}/
#     r.fixed_encoding?                               #=> true
#     r.encoding                                      #=> #<Encoding:UTF-8>
#     r =~ "\u{6666} a"                               #=> 0
#     r =~ "\xa1\xa2".force_encoding("euc-jp")        #=> ArgumentError
#     r =~ "abc".force_encoding("euc-jp")             #=> nil
def fixed_encoding?; true || false; end
##
# Returns a list of names of captures as an array of strings.
# 
#     /(?<foo>.)(?<bar>.)(?<baz>.)/.names
#     #=> ["foo", "bar", "baz"]
# 
#     /(?<foo>.)(?<foo>.)/.names
#     #=> ["foo"]
# 
#     /(.)(.)/.names
#     #=> []
def names; []; end
##
# Returns a hash representing information about named captures of <i>rxp</i>.
# 
# A key of the hash is a name of the named captures.
# A value of the hash is an array which is list of indexes of corresponding
# named captures.
# 
#    /(?<foo>.)(?<bar>.)/.named_captures
#    #=> {"foo"=>[1], "bar"=>[2]}
# 
#    /(?<foo>.)(?<foo>.)/.named_captures
#    #=> {"foo"=>[1, 2]}
# 
# If there are no named captures, an empty hash is returned.
# 
#    /(.)(.)/.named_captures
#    #=> {}
def named_captures; {}; end
end

##
# <code>MatchData</code> is the type of the special variable <code>$~</code>,
# and is the type of the object returned by <code>Regexp#match</code> and
# <code>Regexp.last_match</code>. It encapsulates all the results of a pattern
# match, results normally accessed through the special variables
# <code>$&</code>, <code>$'</code>, <code>$`</code>, <code>$1</code>,
# <code>$2</code>, and so on.
class MatchData < Object
##
# Returns the regexp.
# 
#     m = /a.*b/.match("abc")
#     m.regexp #=> /a.*b/
def regexp; //; end
##
# Returns a list of names of captures as an array of strings.
# It is same as mtch.regexp.names.
# 
#     /(?<foo>.)(?<bar>.)(?<baz>.)/.match("hoge").names
#     #=> ["foo", "bar", "baz"]
# 
#     m = /(?<x>.)(?<y>.)?/.match("a") #=> #<MatchData "a" x:"a" y:nil>
#     m.names                          #=> ["x", "y"]
def names; []; end
##
# Returns the number of elements in the match array.
# 
#    m = /(.)(.)(\d+)(\d)/.match("THX1138.")
#    m.length   #=> 5
#    m.size     #=> 5
def length; 0; end
##
# Returns the number of elements in the match array.
# 
#    m = /(.)(.)(\d+)(\d)/.match("THX1138.")
#    m.length   #=> 5
#    m.size     #=> 5
def size; 0; end
##
# Returns a two-element array containing the beginning and ending offsets of
# the <em>n</em>th match.
# <em>n</em> can be a string or symbol to reference a named capture.
# 
#    m = /(.)(.)(\d+)(\d)/.match("THX1138.")
#    m.offset(0)      #=> [1, 7]
#    m.offset(4)      #=> [6, 7]
# 
#    m = /(?<foo>.)(.)(?<bar>.)/.match("hoge")
#    p m.offset(:foo) #=> [0, 1]
#    p m.offset(:bar) #=> [2, 3]
def offset(n); []; end
##
# Returns the offset of the start of the <em>n</em>th element of the match
# array in the string.
# <em>n</em> can be a string or symbol to reference a named capture.
# 
#    m = /(.)(.)(\d+)(\d)/.match("THX1138.")
#    m.begin(0)       #=> 1
#    m.begin(2)       #=> 2
# 
#    m = /(?<foo>.)(.)(?<bar>.)/.match("hoge")
#    p m.begin(:foo)  #=> 0
#    p m.begin(:bar)  #=> 2
def begin(n); 0; end
##
# Returns the offset of the character immediately following the end of the
# <em>n</em>th element of the match array in the string.
# <em>n</em> can be a string or symbol to reference a named capture.
# 
#    m = /(.)(.)(\d+)(\d)/.match("THX1138.")
#    m.end(0)         #=> 7
#    m.end(2)         #=> 3
# 
#    m = /(?<foo>.)(.)(?<bar>.)/.match("hoge")
#    p m.end(:foo)    #=> 1
#    p m.end(:bar)    #=> 3
def end(n); 0; end
##
# Returns the array of matches.
# 
#    m = /(.)(.)(\d+)(\d)/.match("THX1138.")
#    m.to_a   #=> ["HX1138", "H", "X", "113", "8"]
# 
# Because <code>to_a</code> is called when expanding
# <code>*</code><em>variable</em>, there's a useful assignment
# shortcut for extracting matched fields. This is slightly slower than
# accessing the fields directly (as an intermediate array is
# generated).
# 
#    all,f1,f2,f3 = *(/(.)(.)(\d+)(\d)/.match("THX1138."))
#    all   #=> "HX1138"
#    f1    #=> "H"
#    f2    #=> "X"
#    f3    #=> "113"
def to_a; []; end
##
# Match Reference -- <code>MatchData</code> acts as an array, and may be
# accessed using the normal array indexing techniques.  <code>mtch[0]</code>
# is equivalent to the special variable <code>$&</code>, and returns the
# entire matched string.  <code>mtch[1]</code>, <code>mtch[2]</code>, and so
# on return the values of the matched backreferences (portions of the
# pattern between parentheses).
# 
#    m = /(.)(.)(\d+)(\d)/.match("THX1138.")
#    m          #=> #<MatchData "HX1138" 1:"H" 2:"X" 3:"113" 4:"8">
#    m[0]       #=> "HX1138"
#    m[1, 2]    #=> ["H", "X"]
#    m[1..3]    #=> ["H", "X", "113"]
#    m[-3, 2]   #=> ["X", "113"]
# 
#    m = /(?<foo>a+)b/.match("ccaaab")
#    m          #=> #<MatchData "aaab" foo:"aaa">
#    m["foo"]   #=> "aaa"
#    m[:foo]    #=> "aaa"
def []; '' || nil; end
##
# Returns the array of captures; equivalent to <code>mtch.to_a[1..-1]</code>.
# 
#    f1,f2,f3,f4 = /(.)(.)(\d+)(\d)/.match("THX1138.").captures
#    f1    #=> "H"
#    f2    #=> "X"
#    f3    #=> "113"
#    f4    #=> "8"
def captures; []; end
##
# Uses each <i>index</i> to access the matching values, returning an array of
# the corresponding matches.
# 
#    m = /(.)(.)(\d+)(\d)/.match("THX1138: The Movie")
#    m.to_a               #=> ["HX1138", "H", "X", "113", "8"]
#    m.values_at(0, 2, -2)   #=> ["HX1138", "X", "113"]
def values_at(); []; end
##
# Returns the portion of the original string before the current match.
# Equivalent to the special variable <code>$`</code>.
# 
#    m = /(.)(.)(\d+)(\d)/.match("THX1138.")
#    m.pre_match   #=> "T"
def pre_match; ''; end
##
# Returns the portion of the original string after the current match.
# Equivalent to the special variable <code>$'</code>.
# 
#    m = /(.)(.)(\d+)(\d)/.match("THX1138: The Movie")
#    m.post_match   #=> ": The Movie"
def post_match; ''; end
##
# Returns the entire matched string.
# 
#    m = /(.)(.)(\d+)(\d)/.match("THX1138.")
#    m.to_s   #=> "HX1138"
def to_s; ''; end
##
# Returns a printable version of <i>mtch</i>.
# 
#     puts /.$/.match("foo").inspect
#     #=> #<MatchData "o">
# 
#     puts /(.)(.)(.)/.match("foo").inspect
#     #=> #<MatchData "foo" 1:"f" 2:"o" 3:"o">
# 
#     puts /(.)(.)?(.)/.match("fo").inspect
#     #=> #<MatchData "fo" 1:"f" 2:nil 3:"o">
# 
#     puts /(?<foo>.)(?<bar>.)(?<baz>.)/.match("hoge").inspect
#     #=> #<MatchData "hog" foo:"h" bar:"o" baz:"g">
def inspect; ''; end
##
# Returns a frozen copy of the string passed in to <code>match</code>.
# 
#    m = /(.)(.)(\d+)(\d)/.match("THX1138.")
#    m.string   #=> "THX1138."
def string; ''; end
##
# Produce a hash based on the target string, regexp and matched
# positions of this matchdata.
def hash; 0; end
##
# Equality---Two matchdata are equal if their target strings,
# patterns, and matched positions are identical.
def eql?; true || false; end
##
# Equality---Two matchdata are equal if their target strings,
# patterns, and matched positions are identical.
def ==; true || false; end
end

##
# This is a recommended base class for C extensions using Data_Make_Struct
# or Data_Wrap_Struct, see README.EXT for details.
class Data < Object
end

##
# The global value <code>true</code> is the only instance of class
# <code>TrueClass</code> and represents a logically true value in
# boolean expressions. The class provides operators allowing
# <code>true</code> to be used in logical expressions.
class TrueClass < Object
##
# The string representation of <code>true</code> is "true".
def to_s; true; end
##
# And---Returns <code>false</code> if <i>obj</i> is
# <code>nil</code> or <code>false</code>, <code>true</code> otherwise.
def &; true || false; end
##
# Or---Returns <code>true</code>. As <i>anObject</i> is an argument to
# a method call, it is always evaluated; there is no short-circuit
# evaluation in this case.
# 
#    true |  puts("or")
#    true || puts("logical or")
# 
# <em>produces:</em>
# 
#    or
def |; true; end
##
# Exclusive Or---Returns <code>true</code> if <i>obj</i> is
# <code>nil</code> or <code>false</code>, <code>false</code>
# otherwise.
def ^; Object.new; end
end

##
# The global value <code>false</code> is the only instance of class
# <code>FalseClass</code> and represents a logically false value in
# boolean expressions. The class provides operators allowing
# <code>false</code> to participate correctly in logical expressions.
class FalseClass < Object
##
# 'nuf said...
def to_s; false; end
##
# And---Returns <code>false</code>. <i>obj</i> is always
# evaluated as it is the argument to a method call---there is no
# short-circuit evaluation in this case.
def &; false; end
##
# Or---Returns <code>false</code> if <i>obj</i> is
# <code>nil</code> or <code>false</code>; <code>true</code> otherwise.
def |; true || false; end
##
# Exclusive Or---If <i>obj</i> is <code>nil</code> or
# <code>false</code>, returns <code>false</code>; otherwise, returns
# <code>true</code>.
def ^; true || false; end
end

##
# ThreadGroup provides a means of keeping track of a number of threads as a
# group.
# 
# A given Thread object can only belong to one ThreadGroup at a time; adding
# a thread to a new group will remove it from any previous group.
# 
# Newly created threads belong to the same group as the thread from which they
# were created.
class ThreadGroup < Object
##
# Returns an array of all existing Thread objects that belong to this group.
# 
#    ThreadGroup::Default.list   #=> [#<Thread:0x401bdf4c run>]
def list; []; end
##
# Prevents threads from being added to or removed from the receiving
# ThreadGroup.
# 
# New threads can still be started in an enclosed ThreadGroup.
# 
#    ThreadGroup::Default.enclose        #=> #<ThreadGroup:0x4029d914>
#    thr = Thread::new { Thread.stop }   #=> #<Thread:0x402a7210 sleep>
#    tg = ThreadGroup::new               #=> #<ThreadGroup:0x402752d4>
#    tg.add thr
#    #=> ThreadError: can't move from the enclosed thread group
def enclose; ThreadGroup.new; end
##
# Returns +true+ if the +thgrp+ is enclosed. See also ThreadGroup#enclose.
def enclosed?; true || false; end
##
# Adds the given +thread+ to this group, removing it from any other
# group to which it may have previously been a member.
# 
#    puts "Initial group is #{ThreadGroup::Default.list}"
#    tg = ThreadGroup.new
#    t1 = Thread.new { sleep }
#    t2 = Thread.new { sleep }
#    puts "t1 is #{t1}"
#    puts "t2 is #{t2}"
#    tg.add(t1)
#    puts "Initial group now #{ThreadGroup::Default.list}"
#    puts "tg group now #{tg.list}"
# 
# This will produce:
# 
#    Initial group is #<Thread:0x401bdf4c>
#    t1 is #<Thread:0x401b3c90>
#    t2 is #<Thread:0x401b3c18>
#    Initial group now #<Thread:0x401b3c18>#<Thread:0x401bdf4c>
#    tg group now #<Thread:0x401b3c90>
def add(thread); ThreadGroup.new; end
end

##
# Mutex implements a simple semaphore that can be used to coordinate access to
# shared data from multiple concurrent threads.
# 
# Example:
# 
#   require 'thread'
#   semaphore = Mutex.new
# 
#   a = Thread.new {
#     semaphore.synchronize {
#       # access shared resource
#     }
#   }
# 
#   b = Thread.new {
#     semaphore.synchronize {
#       # access shared resource
#     }
#   }
class Mutex < Object
##
# Creates a new Mutex
def self.new; end
##
# Returns +true+ if this lock is currently held by some thread.
def locked?; true || false; end
##
# Attempts to obtain the lock and returns immediately. Returns +true+ if the
# lock was granted.
def try_lock; true || false; end
##
# Attempts to grab the lock and waits if it isn't available.
# Raises +ThreadError+ if +mutex+ was locked by the current thread.
def lock; self; end
##
# Releases the lock.
# Raises +ThreadError+ if +mutex+ wasn't locked by the current thread.
def unlock; self; end
##
# Releases the lock and sleeps +timeout+ seconds if it is given and
# non-nil or forever.  Raises +ThreadError+ if +mutex+ wasn't locked by
# the current thread.
# 
# Note that this method can wakeup without explicit Thread#wakeup call.
# For example, receiving signal and so on.
def sleep(timeout = null); 0; end
##
# Obtains a lock, runs the block, and releases the lock when the block
# completes.  See the example under +Mutex+.
def synchronize(&block); Object.new; end
##
# Returns +true+ if this lock is currently held by current thread.
# <em>This API is experimental, and subject to change.</em>
def owned?; true || false; end
end

##
# Raised when an invalid operation is attempted on a thread.
# 
# For example, when no other thread has been started:
# 
#    Thread.stop
# 
# This will raises the following exception:
# 
#    ThreadError: stopping only thread
#    note: use sleep to stop forever
class ThreadError < StandardError
end

##
# A class which allows both internal and external iteration.
# 
# An Enumerator can be created by the following methods.
# - Kernel#to_enum
# - Kernel#enum_for
# - Enumerator.new
# 
# Most methods have two forms: a block form where the contents
# are evaluated for each item in the enumeration, and a non-block form
# which returns a new Enumerator wrapping the iteration.
# 
#   enumerator = %w(one two three).each
#   puts enumerator.class # => Enumerator
# 
#   enumerator.each_with_object("foo") do |item, obj|
#     puts "#{obj}: #{item}"
#   end
# 
#   # foo: one
#   # foo: two
#   # foo: three
# 
#   enum_with_obj = enumerator.each_with_object("foo")
#   puts enum_with_obj.class # => Enumerator
# 
#   enum_with_obj.each do |item, obj|
#     puts "#{obj}: #{item}"
#   end
# 
#   # foo: one
#   # foo: two
#   # foo: three
# 
# This allows you to chain Enumerators together.  For example, you
# can map a list's elements to strings containing the index
# and the element as a string via:
# 
#   puts %w[foo bar baz].map.with_index { |w, i| "#{i}:#{w}" }
#   # => ["0:foo", "1:bar", "2:baz"]
# 
# An Enumerator can also be used as an external iterator.
# For example, Enumerator#next returns the next value of the iterator
# or raises StopIteration if the Enumerator is at the end.
# 
#   e = [1,2,3].each   # returns an enumerator object.
#   puts e.next   # => 1
#   puts e.next   # => 2
#   puts e.next   # => 3
#   puts e.next   # raises StopIteration
# 
# You can use this to implement an internal iterator as follows:
# 
#   def ext_each(e)
#     while true
#       begin
#         vs = e.next_values
#       rescue StopIteration
#         return $!.result
#       end
#       y = yield(*vs)
#       e.feed y
#     end
#   end
# 
#   o = Object.new
# 
#   def o.each
#     puts yield
#     puts yield(1)
#     puts yield(1, 2)
#     3
#   end
# 
#   # use o.each as an internal iterator directly.
#   puts o.each {|*x| puts x; [:b, *x] }
#   # => [], [:b], [1], [:b, 1], [1, 2], [:b, 1, 2], 3
# 
#   # convert o.each to an external iterator for
#   # implementing an internal iterator.
#   puts ext_each(o.to_enum) {|*x| puts x; [:b, *x] }
#   # => [], [:b], [1], [:b, 1], [1, 2], [:b, 1, 2], 3
class Enumerator < Object
include Enumerable
class Lazy < Enumerator
##
# Creates a new Lazy enumerator. When the enumerator is actually enumerated
# (e.g. by calling #force), +obj+ will be enumerated and each value passed
# to the given block. The block can yield values back using +yielder+.
# For example, to create a method +filter_map+ in both lazy and
# non-lazy fashions:
# 
#   module Enumerable
#     def filter_map(&block)
#       map(&block).compact
#     end
#   end
# 
#   class Enumerator::Lazy
#     def filter_map
#       Lazy.new(self) do |yielder, *values|
#         result = yield *values
#         yielder << result if result
#       end
#     end
#   end
# 
#   (1..Float::INFINITY).lazy.filter_map{|i| i*i if i.even?}.first(5)
#       # => [4, 16, 36, 64, 100]
def self.new(obj, size=null, &block); end
##
# Similar to Kernel#to_enum, except it returns a lazy enumerator.
# This makes it easy to define Enumerable methods that will
# naturally remain lazy if called from a lazy enumerator.
# 
# For example, continuing from the example in Kernel#to_enum:
# 
#   # See Kernel#to_enum for the definition of repeat
#   r = 1..Float::INFINITY
#   r.repeat(2).first(5) # => [1, 1, 2, 2, 3]
#   r.repeat(2).class # => Enumerator
#   r.repeat(2).map{|n| n ** 2}.first(5) # => endless loop!
#   # works naturally on lazy enumerator:
#   r.lazy.repeat(2).class # => Enumerator::Lazy
#   r.lazy.repeat(2).map{|n| n ** 2}.first(5) # => [1, 1, 4, 4, 9]
def to_enum(); Enumerator::Lazy.new; end
##
# Similar to Kernel#to_enum, except it returns a lazy enumerator.
# This makes it easy to define Enumerable methods that will
# naturally remain lazy if called from a lazy enumerator.
# 
# For example, continuing from the example in Kernel#to_enum:
# 
#   # See Kernel#to_enum for the definition of repeat
#   r = 1..Float::INFINITY
#   r.repeat(2).first(5) # => [1, 1, 2, 2, 3]
#   r.repeat(2).class # => Enumerator
#   r.repeat(2).map{|n| n ** 2}.first(5) # => endless loop!
#   # works naturally on lazy enumerator:
#   r.lazy.repeat(2).class # => Enumerator::Lazy
#   r.lazy.repeat(2).map{|n| n ** 2}.first(5) # => [1, 1, 4, 4, 9]
def enum_for(); Enumerator::Lazy.new; end
##
# Returns a new lazy enumerator with the concatenated results of running
# <i>block</i> once for every element in <i>lazy</i>.
# 
#   ["foo", "bar"].lazy.flat_map {|i| i.each_char.lazy}.force
#   #=> ["f", "o", "o", "b", "a", "r"]
# 
# A value <i>x</i> returned by <i>block</i> is decomposed if either of
# the following conditions is true:
# 
#   a) <i>x</i> responds to both each and force, which means that
#      <i>x</i> is a lazy enumerator.
#   b) <i>x</i> is an array or responds to to_ary.
# 
# Otherwise, <i>x</i> is contained as-is in the return value.
# 
#   [{a:1}, {b:2}].lazy.flat_map {|i| i}.force
#   #=> [{:a=>1}, {:b=>2}]
def flat_map(&block); Enumerator::Lazy.new; end
end

class Generator < Object
include Enumerable
end

class Yielder < Object
end

##
# Creates a new Enumerator object, which can be used as an
# Enumerable.
# 
# In the first form, iteration is defined by the given block, in
# which a "yielder" object, given as block parameter, can be used to
# yield a value by calling the +yield+ method (aliased as +<<+):
# 
#   fib = Enumerator.new do |y|
#     a = b = 1
#     loop do
#       y << a
#       a, b = b, a + b
#     end
#   end
# 
#   p fib.take(10) # => [1, 1, 2, 3, 5, 8, 13, 21, 34, 55]
# 
# The optional parameter can be used to specify how to calculate the size
# in a lazy fashion (see Enumerator#size). It can either be a value or
# a callable object.
# 
# In the second, deprecated, form, a generated Enumerator iterates over the
# given object using the given method with the given arguments passed.
# 
# Use of this form is discouraged.  Use Kernel#enum_for or Kernel#to_enum
# instead.
# 
#   e = Enumerator.new(ObjectSpace, :each_object)
#       #-> ObjectSpace.enum_for(:each_object)
# 
#   e.select { |obj| obj.is_a?(Class) }  #=> array of all classes
def self.new(size = null, &block); end
##
# Iterates over the block according to how this Enumerable was constructed.
# If no block is given, returns self.
def each(&block); end
##
# Same as Enumerator#with_index(0), i.e. there is no starting offset.
# 
# If no block is given, a new Enumerator is returned that includes the index.
def each_with_index(&block); end
##
# Iterates the given block for each element with an arbitrary object, +obj+,
# and returns +obj+
# 
# If no block is given, returns a new Enumerator.
# 
# === Example
# 
#   to_three = Enumerator.new do |y|
#     3.times do |x|
#       y << x
#     end
#   end
# 
#   to_three_with_string = to_three.with_object("foo")
#   to_three_with_string.each do |x,string|
#     puts "#{string}: #{x}"
#   end
# 
#   # => foo:0
#   # => foo:1
#   # => foo:2
def with_object(obj, &block); end
##
# Iterates the given block for each element with an index, which
# starts from +offset+.  If no block is given, returns a new Enumerator
# that includes the index, starting from +offset+
# 
# +offset+:: the starting index to use
def with_index(offset = 0, &block); end
##
# Returns the next object as an array in the enumerator, and move the
# internal position forward.  When the position reached at the end,
# StopIteration is raised.
# 
# This method can be used to distinguish <code>yield</code> and <code>yield
# nil</code>.
# 
# === Example
# 
#   o = Object.new
#   def o.each
#     yield
#     yield 1
#     yield 1, 2
#     yield nil
#     yield [1, 2]
#   end
#   e = o.to_enum
#   p e.next_values
#   p e.next_values
#   p e.next_values
#   p e.next_values
#   p e.next_values
#   e = o.to_enum
#   p e.next
#   p e.next
#   p e.next
#   p e.next
#   p e.next
# 
#   ## yield args       next_values      next
#   #  yield            []               nil
#   #  yield 1          [1]              1
#   #  yield 1, 2       [1, 2]           [1, 2]
#   #  yield nil        [nil]            nil
#   #  yield [1, 2]     [[1, 2]]         [1, 2]
# 
# Note that +next_values+ does not affect other non-external enumeration
# methods unless underlying iteration method itself has side-effect, e.g.
# IO#each_line.
def next_values; []; end
##
# Returns the next object as an array, similar to Enumerator#next_values, but
# doesn't move the internal position forward.  If the position is already at
# the end, StopIteration is raised.
# 
# === Example
# 
#   o = Object.new
#   def o.each
#     yield
#     yield 1
#     yield 1, 2
#   end
#   e = o.to_enum
#   p e.peek_values    #=> []
#   e.next
#   p e.peek_values    #=> [1]
#   p e.peek_values    #=> [1]
#   e.next
#   p e.peek_values    #=> [1, 2]
#   e.next
#   p e.peek_values    # raises StopIteration
def peek_values; []; end
##
# Returns the next object in the enumerator, and move the internal position
# forward.  When the position reached at the end, StopIteration is raised.
# 
# === Example
# 
#   a = [1,2,3]
#   e = a.to_enum
#   p e.next   #=> 1
#   p e.next   #=> 2
#   p e.next   #=> 3
#   p e.next   #raises StopIteration
# 
# Note that enumeration sequence by +next+ does not affect other non-external
# enumeration methods, unless the underlying iteration methods itself has
# side-effect, e.g. IO#each_line.
def next; Object.new; end
##
# Returns the next object in the enumerator, but doesn't move the internal
# position forward.  If the position is already at the end, StopIteration
# is raised.
# 
# === Example
# 
#   a = [1,2,3]
#   e = a.to_enum
#   p e.next   #=> 1
#   p e.peek   #=> 2
#   p e.peek   #=> 2
#   p e.peek   #=> 2
#   p e.next   #=> 2
#   p e.next   #=> 3
#   p e.next   #raises StopIteration
def peek; Object.new; end
##
# Sets the value to be returned by the next yield inside +e+.
# 
# If the value is not set, the yield returns nil.
# 
# This value is cleared after being yielded.
# 
#   o = Object.new
#   def o.each
#     x = yield         # (2) blocks
#     p x               # (5) => "foo"
#     x = yield         # (6) blocks
#     p x               # (8) => nil
#     x = yield         # (9) blocks
#     p x               # not reached w/o another e.next
#   end
# 
#   e = o.to_enum
#   e.next              # (1)
#   e.feed "foo"        # (3)
#   e.next              # (4)
#   e.next              # (7)
#                       # (10)
def feed obj; end
##
# Rewinds the enumeration sequence to the beginning.
# 
# If the enclosed object responds to a "rewind" method, it is called.
def rewind; Exception.new; end
##
# Creates a printable version of <i>e</i>.
def inspect; ''; end
##
# Returns the size of the enumerator, or +nil+ if it can't be calculated lazily.
# 
#   (1..100).to_a.permutation(4).size # => 94109400
#   loop.size # => Float::INFINITY
#   (1..100).drop_while.size # => nil
def size; 1 || 0.0 || nil; end
end

##
# Raised to stop the iteration, in particular by Enumerator#next. It is
# rescued by Kernel#loop.
# 
#   loop do
#     puts "Hello"
#     raise StopIteration
#     puts "World"
#   end
#   puts "Done!"
# 
# <em>produces:</em>
# 
#   Hello
#   Done!
class StopIteration < IndexError
##
# Returns the return value of the iterator.
# 
#   o = Object.new
#   def o.each
#     yield 1
#     yield 2
#     yield 3
#     100
#   end
# 
#   e = o.to_enum
# 
#   puts e.next                   #=> 1
#   puts e.next                   #=> 2
#   puts e.next                   #=> 3
# 
#   begin
#     e.next
#   rescue StopIteration => ex
#     puts ex.result              #=> 100
#   end
def result; Object.new; end
end

##
# Fibers are primitives for implementing light weight cooperative
# concurrency in Ruby. Basically they are a means of creating code blocks
# that can be paused and resumed, much like threads. The main difference
# is that they are never preempted and that the scheduling must be done by
# the programmer and not the VM.
# 
# As opposed to other stackless light weight concurrency models, each fiber
# comes with a small 4KB stack. This enables the fiber to be paused from deeply
# nested function calls within the fiber block.
# 
# When a fiber is created it will not run automatically. Rather it must be
# be explicitly asked to run using the <code>Fiber#resume</code> method.
# The code running inside the fiber can give up control by calling
# <code>Fiber.yield</code> in which case it yields control back to caller
# (the caller of the <code>Fiber#resume</code>).
# 
# Upon yielding or termination the Fiber returns the value of the last
# executed expression
# 
# For instance:
# 
#   fiber = Fiber.new do
#     Fiber.yield 1
#     2
#   end
# 
#   puts fiber.resume
#   puts fiber.resume
#   puts fiber.resume
# 
# <em>produces</em>
# 
#   1
#   2
#   FiberError: dead fiber called
# 
# The <code>Fiber#resume</code> method accepts an arbitrary number of
# parameters, if it is the first call to <code>resume</code> then they
# will be passed as block arguments. Otherwise they will be the return
# value of the call to <code>Fiber.yield</code>
# 
# Example:
# 
#   fiber = Fiber.new do |first|
#     second = Fiber.yield first + 2
#   end
# 
#   puts fiber.resume 10
#   puts fiber.resume 14
#   puts fiber.resume 18
# 
# <em>produces</em>
# 
#   12
#   14
#   FiberError: dead fiber called
class Fiber < Object
##
# Yields control back to the context that resumed the fiber, passing
# along any arguments that were passed to it. The fiber will resume
# processing at this point when <code>resume</code> is called next.
# Any arguments passed to the next <code>resume</code> will be the
# value that this <code>Fiber.yield</code> expression evaluates to.
def self.yield(); Object.new; end
##
# Resumes the fiber from the point at which the last <code>Fiber.yield</code>
# was called, or starts running it if it is the first call to
# <code>resume</code>. Arguments passed to resume will be the value of
# the <code>Fiber.yield</code> expression or will be passed as block
# parameters to the fiber's block if this is the first <code>resume</code>.
# 
# Alternatively, when resume is called it evaluates to the arguments passed
# to the next <code>Fiber.yield</code> statement inside the fiber's block
# or to the block value if it runs to completion without any
# <code>Fiber.yield</code>
def resume(); Object.new; end
##
# Transfer control to another fiber, resuming it from where it last
# stopped or starting it if it was not resumed before. The calling
# fiber will be suspended much like in a call to
# <code>Fiber.yield</code>. You need to <code>require 'fiber'</code>
# before using this method.
# 
# The fiber which receives the transfer call is treats it much like
# a resume call. Arguments passed to transfer are treated like those
# passed to resume.
# 
# You cannot resume a fiber that transferred control to another one.
# This will cause a double resume error. You need to transfer control
# back to this fiber before it can yield and resume.
# 
# Example:
# 
#   fiber1 = Fiber.new do
#     puts "In Fiber 1"
#     Fiber.yield
#   end
# 
#   fiber2 = Fiber.new do
#     puts "In Fiber 2"
#     fiber1.transfer
#     puts "Never see this message"
#   end
# 
#   fiber3 = Fiber.new do
#     puts "In Fiber 3"
#   end
# 
#   fiber2.resume
#   fiber3.resume
# 
#   <em>produces</em>
# 
#   In fiber 2
#   In fiber 1
#   In fiber 3
def transfer(); Object.new; end
##
# Returns true if the fiber can still be resumed (or transferred
# to). After finishing execution of the fiber block this method will
# always return false. You need to <code>require 'fiber'</code>
# before using this method.
def alive?; true || false; end
##
# Returns the current fiber. You need to <code>require 'fiber'</code>
# before using this method. If you are not running in the context of
# a fiber this method will return the root fiber.
def self.current(); Fiber.new; end
end

##
# Raised when an invalid operation is attempted on a Fiber, in
# particular when attempting to call/resume a dead fiber,
# attempting to yield from the root fiber, or calling a fiber across
# threads.
# 
#    fiber = Fiber.new{}
#    fiber.resume #=> nil
#    fiber.resume #=> FiberError: dead fiber called
class FiberError < StandardError
end

##
# Continuation objects are generated by Kernel#callcc,
# after having +require+d <i>continuation</i>. They hold
# a return address and execution context, allowing a nonlocal return
# to the end of the <code>callcc</code> block from anywhere within a
# program. Continuations are somewhat analogous to a structured
# version of C's <code>setjmp/longjmp</code> (although they contain
# more state, so you might consider them closer to threads).
# 
# For instance:
# 
#    require "continuation"
#    arr = [ "Freddie", "Herbie", "Ron", "Max", "Ringo" ]
#    callcc{|cc| $cc = cc}
#    puts(message = arr.shift)
#    $cc.call unless message =~ /Max/
# 
# <em>produces:</em>
# 
#    Freddie
#    Herbie
#    Ron
#    Max
# 
# This (somewhat contrived) example allows the inner loop to abandon
# processing early:
# 
#    require "continuation"
#    callcc {|cont|
#      for i in 0..4
#        print "\n#{i}: "
#        for j in i*5...(i+1)*5
#          cont.call() if j == 17
#          printf "%3d", j
#        end
#      end
#    }
#    puts
# 
# <em>produces:</em>
# 
#    0:   0  1  2  3  4
#    1:   5  6  7  8  9
#    2:  10 11 12 13 14
#    3:  15 16
class Continuation < Object
##
# Invokes the continuation. The program continues from the end of the
# <code>callcc</code> block. If no arguments are given, the original
# <code>callcc</code> returns <code>nil</code>. If one argument is
# given, <code>callcc</code> returns it. Otherwise, an array
# containing <i>args</i> is returned.
# 
#    callcc {|cont|  cont.call }           #=> nil
#    callcc {|cont|  cont.call 1 }         #=> 1
#    callcc {|cont|  cont.call 1, 2, 3 }   #=> [1, 2, 3]
def call(); end
##
# Invokes the continuation. The program continues from the end of the
# <code>callcc</code> block. If no arguments are given, the original
# <code>callcc</code> returns <code>nil</code>. If one argument is
# given, <code>callcc</code> returns it. Otherwise, an array
# containing <i>args</i> is returned.
# 
#    callcc {|cont|  cont.call }           #=> nil
#    callcc {|cont|  cont.call 1 }         #=> 1
#    callcc {|cont|  cont.call 1, 2, 3 }   #=> [1, 2, 3]
def []; end
end

##
# A complex number can be represented as a paired real number with
# imaginary unit; a+bi.  Where a is real part, b is imaginary part
# and i is imaginary unit.  Real a equals complex a+0i
# mathematically.
# 
# In ruby, you can create complex object with Complex, Complex::rect,
# Complex::polar or to_c method.
# 
#    Complex(1)           #=> (1+0i)
#    Complex(2, 3)        #=> (2+3i)
#    Complex.polar(2, 3)  #=> (-1.9799849932008908+0.2822400161197344i)
#    3.to_c               #=> (3+0i)
# 
# You can also create complex object from floating-point numbers or
# strings.
# 
#    Complex(0.3)         #=> (0.3+0i)
#    Complex('0.3-0.5i')  #=> (0.3-0.5i)
#    Complex('2/3+3/4i')  #=> ((2/3)+(3/4)*i)
#    Complex('1@2')       #=> (-0.4161468365471424+0.9092974268256817i)
# 
#    0.3.to_c             #=> (0.3+0i)
#    '0.3-0.5i'.to_c      #=> (0.3-0.5i)
#    '2/3+3/4i'.to_c      #=> ((2/3)+(3/4)*i)
#    '1@2'.to_c           #=> (-0.4161468365471424+0.9092974268256817i)
# 
# A complex object is either an exact or an inexact number.
# 
#    Complex(1, 1) / 2    #=> ((1/2)+(1/2)*i)
#    Complex(1, 1) / 2.0  #=> (0.5+0.5i)
class Complex < Numeric
class Compatible < Object
end

##
# Returns a complex object which denotes the given rectangular form.
# 
#    Complex.rectangular(1, 2)  #=> (1+2i)
def self.rect(real, imag=0); []; end
##
# Returns a complex object which denotes the given rectangular form.
# 
#    Complex.rectangular(1, 2)  #=> (1+2i)
def self.rectangular(real, imag=0); []; end
##
# Returns a complex object which denotes the given polar form.
# 
#    Complex.polar(3, 0)            #=> (3.0+0.0i)
#    Complex.polar(3, Math::PI/2)   #=> (1.836909530733566e-16+3.0i)
#    Complex.polar(3, Math::PI)     #=> (-3.0+3.673819061467132e-16i)
#    Complex.polar(3, -Math::PI/2)  #=> (1.836909530733566e-16-3.0i)
def self.polar(abs, arg=0); []; end
##
# Returns the real part.
# 
#    Complex(7).real      #=> 7
#    Complex(9, -4).real  #=> 9
def real; 0; end
##
# Returns the imaginary part.
# 
#    Complex(7).imaginary      #=> 0
#    Complex(9, -4).imaginary  #=> -4
def imag; 0; end
##
# Returns the imaginary part.
# 
#    Complex(7).imaginary      #=> 0
#    Complex(9, -4).imaginary  #=> -4
def imaginary; 0; end
##
# Returns negation of the value.
# 
#    -Complex(1, 2)  #=> (-1-2i)
def -@; Complex.new; end
##
# Performs addition.
# 
#    Complex(2, 3)  + Complex(2, 3)   #=> (4+6i)
#    Complex(900)   + Complex(1)      #=> (901+0i)
#    Complex(-2, 9) + Complex(-9, 2)  #=> (-11+11i)
#    Complex(9, 8)  + 4               #=> (13+8i)
#    Complex(20, 9) + 9.8             #=> (29.8+9i)
def +; Complex.new; end
##
# Performs subtraction.
# 
#    Complex(2, 3)  - Complex(2, 3)   #=> (0+0i)
#    Complex(900)   - Complex(1)      #=> (899+0i)
#    Complex(-2, 9) - Complex(-9, 2)  #=> (7+7i)
#    Complex(9, 8)  - 4               #=> (5+8i)
#    Complex(20, 9) - 9.8             #=> (10.2+9i)
def -; Complex.new; end
##
# Performs multiplication.
# 
#    Complex(2, 3)  * Complex(2, 3)   #=> (-5+12i)
#    Complex(900)   * Complex(1)      #=> (900+0i)
#    Complex(-2, 9) * Complex(-9, 2)  #=> (0-85i)
#    Complex(9, 8)  * 4               #=> (36+32i)
#    Complex(20, 9) * 9.8             #=> (196.0+88.2i)
def *; Complex.new; end
##
# Performs division.
# 
#    Complex(2, 3)  / Complex(2, 3)   #=> ((1/1)+(0/1)*i)
#    Complex(900)   / Complex(1)      #=> ((900/1)+(0/1)*i)
#    Complex(-2, 9) / Complex(-9, 2)  #=> ((36/85)-(77/85)*i)
#    Complex(9, 8)  / 4               #=> ((9/4)+(2/1)*i)
#    Complex(20, 9) / 9.8             #=> (2.0408163265306123+0.9183673469387754i)
def /; Complex.new; end
##
# Performs division.
# 
#    Complex(2, 3)  / Complex(2, 3)   #=> ((1/1)+(0/1)*i)
#    Complex(900)   / Complex(1)      #=> ((900/1)+(0/1)*i)
#    Complex(-2, 9) / Complex(-9, 2)  #=> ((36/85)-(77/85)*i)
#    Complex(9, 8)  / 4               #=> ((9/4)+(2/1)*i)
#    Complex(20, 9) / 9.8             #=> (2.0408163265306123+0.9183673469387754i)
def quo(numeric); Complex.new; end
##
# Performs division as each part is a float, never returns a float.
# 
#    Complex(11, 22).fdiv(3)  #=> (3.6666666666666665+7.333333333333333i)
def fdiv(numeric); Complex.new; end
##
# Performs exponentiation.
# 
#    Complex('i') ** 2              #=> (-1+0i)
#    Complex(-8) ** Rational(1, 3)  #=> (1.0000000000000002+1.7320508075688772i)
def **; Complex.new; end
##
# Returns true if cmp equals object numerically.
# 
#    Complex(2, 3)  == Complex(2, 3)   #=> true
#    Complex(5)     == 5               #=> true
#    Complex(0)     == 0.0             #=> true
#    Complex('1/3') == 0.33            #=> false
#    Complex('1/2') == '1/2'           #=> false
def ==; true || false; end
##
# Returns the absolute part of its polar form.
# 
#    Complex(-1).abs         #=> 1
#    Complex(3.0, -4.0).abs  #=> 5.0
def abs; 0; end
##
# Returns the absolute part of its polar form.
# 
#    Complex(-1).abs         #=> 1
#    Complex(3.0, -4.0).abs  #=> 5.0
def magnitude; 0; end
##
# Returns square of the absolute value.
# 
#    Complex(-1).abs2         #=> 1
#    Complex(3.0, -4.0).abs2  #=> 25.0
def abs2; 0; end
##
# Returns the angle part of its polar form.
# 
#    Complex.polar(3, Math::PI/2).arg  #=> 1.5707963267948966
def arg; 0.0; end
##
# Returns the angle part of its polar form.
# 
#    Complex.polar(3, Math::PI/2).arg  #=> 1.5707963267948966
def angle; 0.0; end
##
# Returns the angle part of its polar form.
# 
#    Complex.polar(3, Math::PI/2).arg  #=> 1.5707963267948966
def phase; 0.0; end
##
# Returns the complex conjugate.
# 
#    Complex(1, 2).conjugate  #=> (1-2i)
def conj; Complex.new; end
##
# Returns the complex conjugate.
# 
#    Complex(1, 2).conjugate  #=> (1-2i)
def conjugate; Complex.new; end
##
# Returns false.
def real?; false; end
##
# Returns the numerator.
# 
#        1   2       3+4i  <-  numerator
#        - + -i  ->  ----
#        2   3        6    <-  denominator
# 
#    c = Complex('1/2+2/3i')  #=> ((1/2)+(2/3)*i)
#    n = c.numerator          #=> (3+4i)
#    d = c.denominator        #=> 6
#    n / d                    #=> ((1/2)+(2/3)*i)
#    Complex(Rational(n.real, d), Rational(n.imag, d))
#                             #=> ((1/2)+(2/3)*i)
# See denominator.
def numerator; 0; end
##
# Returns the denominator (lcm of both denominator - real and imag).
# 
# See numerator.
def denominator; 0; end
##
# Returns the value as a string.
# 
#    Complex(2).to_s                       #=> "2+0i"
#    Complex('-8/6').to_s                  #=> "-4/3+0i"
#    Complex('1/2i').to_s                  #=> "0+1/2i"
#    Complex(0, Float::INFINITY).to_s      #=> "0+Infinity*i"
#    Complex(Float::NAN, Float::NAN).to_s  #=> "NaN+NaN*i"
def to_s; ''; end
##
# Returns the value as a string for inspection.
# 
#    Complex(2).inspect                       #=> "(2+0i)"
#    Complex('-8/6').inspect                  #=> "((-4/3)+0i)"
#    Complex('1/2i').inspect                  #=> "(0+(1/2)*i)"
#    Complex(0, Float::INFINITY).inspect      #=> "(0+Infinity*i)"
#    Complex(Float::NAN, Float::NAN).inspect  #=> "(NaN+NaN*i)"
def inspect; ''; end
##
# Returns the value as an integer if possible (the imaginary part
# should be exactly zero).
# 
#    Complex(1, 0).to_i    #=> 1
#    Complex(1, 0.0).to_i  # RangeError
#    Complex(1, 2).to_i    # RangeError
def to_i; 0; end
##
# Returns the value as a float if possible (the imaginary part should
# be exactly zero).
# 
#    Complex(1, 0).to_f    #=> 1.0
#    Complex(1, 0.0).to_f  # RangeError
#    Complex(1, 2).to_f    # RangeError
def to_f; 0.0; end
##
# Returns the value as a rational if possible (the imaginary part
# should be exactly zero).
# 
#    Complex(1, 0).to_r    #=> (1/1)
#    Complex(1, 0.0).to_r  # RangeError
#    Complex(1, 2).to_r    # RangeError
# 
# See rationalize.
def to_r; Rational.new; end
##
# Returns the value as a rational if possible (the imaginary part
# should be exactly zero).
# 
#    Complex(1.0/3, 0).rationalize  #=> (1/3)
#    Complex(1, 0.0).rationalize    # RangeError
#    Complex(1, 2).rationalize      # RangeError
# 
# See to_r.
def rationalize(eps=0); Rational.new; end
##
# Returns self.
# 
#    Complex(2).to_c      #=> (2+0i)
#    Complex(-8, 6).to_c  #=> (-8+6i)
def to_c; self; end
end

##
# Raised when an IO operation fails.
# 
#    File.open("/etc/hosts") {|f| f << "example"}
#      #=> IOError: not opened for writing
# 
#    File.open("/etc/hosts") {|f| f.close; f.read }
#      #=> IOError: closed stream
# 
# Note that some IO failures raise +SystemCallError+s and these are not
# subclasses of IOError:
# 
#    File.open("does/not/exist")
#      #=> Errno::ENOENT: No such file or directory - does/not/exist
class IOError < StandardError
end

##
# Raised by some IO operations when reaching the end of file. Many IO
# methods exist in two forms,
# 
# one that returns +nil+ when the end of file is reached, the other
# raises EOFError +EOFError+.
# 
# +EOFError+ is a subclass of +IOError+.
# 
#    file = File.open("/etc/hosts")
#    file.read
#    file.gets     #=> nil
#    file.readline #=> EOFError: end of file reached
class EOFError < IOError
end

##
# +ARGF+ is a stream designed for use in scripts that process files given as
# command-line arguments or passed in via STDIN.
# 
# The arguments passed to your script are stored in the +ARGV+ Array, one
# argument per element. +ARGF+ assumes that any arguments that aren't
# filenames have been removed from +ARGV+. For example:
# 
#     $ ruby argf.rb --verbose file1 file2
# 
#     ARGV  #=> ["--verbose", "file1", "file2"]
#     option = ARGV.shift #=> "--verbose"
#     ARGV  #=> ["file1", "file2"]
# 
# You can now use +ARGF+ to work with a concatenation of each of these named
# files. For instance, +ARGF.read+ will return the contents of _file1_
# followed by the contents of _file2_.
# 
# After a file in +ARGV+ has been read +ARGF+ removes it from the Array.
# Thus, after all files have been read +ARGV+ will be empty.
# 
# You can manipulate +ARGV+ yourself to control what +ARGF+ operates on. If
# you remove a file from +ARGV+, it is ignored by +ARGF+; if you add files to
# +ARGV+, they are treated as if they were named on the command line. For
# example:
# 
#     ARGV.replace ["file1"]
#     ARGF.readlines # Returns the contents of file1 as an Array
#     ARGV           #=> []
#     ARGV.replace ["file2", "file3"]
#     ARGF.read      # Returns the contents of file2 and file3
# 
# If +ARGV+ is empty, +ARGF+ acts as if it contained STDIN, i.e. the data
# piped to your script. For example:
# 
#     $ echo "glark" | ruby -e 'p ARGF.read'
#     "glark\n"
class ARGF < Object
include Enumerable
##
# Returns "ARGF".
def to_s; ''; end
##
# Returns the +ARGV+ array, which contains the arguments passed to your
# script, one per element.
# 
# For example:
# 
#     $ ruby argf.rb -v glark.txt
# 
#     ARGF.argv   #=> ["-v", "glark.txt"]
def argv; ARGV; end
##
# Returns an integer representing the numeric file descriptor for
# the current file. Raises an +ArgumentError+ if there isn't a current file.
# 
#    ARGF.fileno    #=> 3
def fileno; 0; end
##
# Returns an integer representing the numeric file descriptor for
# the current file. Raises an +ArgumentError+ if there isn't a current file.
# 
#    ARGF.fileno    #=> 3
def to_i; 0; end
##
# Returns an +IO+ object representing the current file. This will be a
# +File+ object unless the current file is a stream such as STDIN.
# 
# For example:
# 
#    ARGF.to_io    #=> #<File:glark.txt>
#    ARGF.to_io    #=> #<IO:<STDIN>>
def to_io; IO; end
##
# Returns IO instance tied to _ARGF_ for writing if inplace mode is
# enabled.
def to_write_io; IO.new; end
##
# Returns an enumerator which iterates over each line (separated by _sep_,
# which defaults to your platform's newline character) of each file in
# +ARGV+. If a block is supplied, each line in turn will be yielded to the
# block, otherwise an enumerator is returned.
# The optional _limit_ argument is a +Fixnum+ specifying the maximum
# length of each line; longer lines will be split according to this limit.
# 
# This method allows you to treat the files supplied on the command line as
# a single file consisting of the concatenation of each named file. After
# the last line of the first file has been returned, the first line of the
# second file is returned. The +ARGF.filename+ and +ARGF.lineno+ methods can
# be used to determine the filename and line number, respectively, of the
# current line.
# 
# For example, the following code prints out each line of each named file
# prefixed with its line number, displaying the filename once per file:
# 
#    ARGF.lines do |line|
#      puts ARGF.filename if ARGF.lineno == 1
#      puts "#{ARGF.lineno}: #{line}"
#    end
def each(sep=$/, &block); Enumerator.new; end
##
# Returns an enumerator which iterates over each line (separated by _sep_,
# which defaults to your platform's newline character) of each file in
# +ARGV+. If a block is supplied, each line in turn will be yielded to the
# block, otherwise an enumerator is returned.
# The optional _limit_ argument is a +Fixnum+ specifying the maximum
# length of each line; longer lines will be split according to this limit.
# 
# This method allows you to treat the files supplied on the command line as
# a single file consisting of the concatenation of each named file. After
# the last line of the first file has been returned, the first line of the
# second file is returned. The +ARGF.filename+ and +ARGF.lineno+ methods can
# be used to determine the filename and line number, respectively, of the
# current line.
# 
# For example, the following code prints out each line of each named file
# prefixed with its line number, displaying the filename once per file:
# 
#    ARGF.lines do |line|
#      puts ARGF.filename if ARGF.lineno == 1
#      puts "#{ARGF.lineno}: #{line}"
#    end
def each_line(sep=$/, &block); Enumerator.new; end
##
#  Iterates over each byte of each file in +ARGV+.
#  A byte is returned as a +Fixnum+ in the range 0..255.
# 
#  This method allows you to treat the files supplied on the command line as
#  a single file consisting of the concatenation of each named file. After
#  the last byte of the first file has been returned, the first byte of the
#  second file is returned. The +ARGF.filename+ method can be used to
#  determine the filename of the current byte.
# 
#  If no block is given, an enumerator is returned instead.
# 
# For example:
# 
#     ARGF.bytes.to_a  #=> [35, 32, ... 95, 10]
def bytes(&block); Enumerator.new; end
##
#  Iterates over each byte of each file in +ARGV+.
#  A byte is returned as a +Fixnum+ in the range 0..255.
# 
#  This method allows you to treat the files supplied on the command line as
#  a single file consisting of the concatenation of each named file. After
#  the last byte of the first file has been returned, the first byte of the
#  second file is returned. The +ARGF.filename+ method can be used to
#  determine the filename of the current byte.
# 
#  If no block is given, an enumerator is returned instead.
# 
# For example:
# 
#     ARGF.bytes.to_a  #=> [35, 32, ... 95, 10]
def each_byte(&block); Enumerator.new; end
##
# Iterates over each character of each file in +ARGF+.
# 
# This method allows you to treat the files supplied on the command line as
# a single file consisting of the concatenation of each named file. After
# the last character of the first file has been returned, the first
# character of the second file is returned. The +ARGF.filename+ method can
# be used to determine the name of the file in which the current character
# appears.
# 
# If no block is given, an enumerator is returned instead.
def each_char(&block); Enumerator.new; end
##
# Iterates over each codepoint of each file in +ARGF+.
# 
# This method allows you to treat the files supplied on the command line as
# a single file consisting of the concatenation of each named file. After
# the last codepoint of the first file has been returned, the first
# codepoint of the second file is returned. The +ARGF.filename+ method can
# be used to determine the name of the file in which the current codepoint
# appears.
# 
# If no block is given, an enumerator is returned instead.
def each_codepoint(&block); Enumerator.new; end
##
#  Reads _length_ bytes from ARGF. The files named on the command line
#  are concatenated and treated as a single file by this method, so when
#  called without arguments the contents of this pseudo file are returned in
#  their entirety.
# 
#  _length_ must be a non-negative integer or nil. If it is a positive
#  integer, +read+ tries to read at most _length_ bytes. It returns nil
#  if an EOF was encountered before anything could be read. Fewer than
#  _length_ bytes may be returned if an EOF is encountered during the read.
# 
#  If _length_ is omitted or is _nil_, it reads until EOF. A String is
#  returned even if EOF is encountered before any data is read.
# 
#  If _length_ is zero, it returns _""_.
# 
#  If the optional _outbuf_ argument is present, it must reference a String,
#  which will receive the data.
#  The <i>outbuf</i> will contain only the received data after the method call
#  even if it is not empty at the beginning.
# 
# For example:
# 
#     $ echo "small" > small.txt
#     $ echo "large" > large.txt
#     $ ./glark.rb small.txt large.txt
# 
#     ARGF.read      #=> "small\nlarge"
#     ARGF.read(200) #=> "small\nlarge"
#     ARGF.read(2)   #=> "sm"
#     ARGF.read(0)   #=> ""
# 
#  Note that this method behaves like fread() function in C.  If you need the
#  behavior like read(2) system call, consider +ARGF.readpartial+.
def read(length=0, outbuf=0); '' || nil; end
##
# Reads at most _maxlen_ bytes from the ARGF stream. It blocks only if
# +ARGF+ has no data immediately available. If the optional _outbuf_
# argument is present, it must reference a String, which will receive the
# data.
# The <i>outbuf</i> will contain only the received data after the method call
# even if it is not empty at the beginning.
# It raises <code>EOFError</code> on end of file.
# 
# +readpartial+ is designed for streams such as pipes, sockets, and ttys. It
# blocks only when no data is immediately available. This means that it
# blocks only when following all conditions hold:
# 
# * The byte buffer in the +IO+ object is empty.
# * The content of the stream is empty.
# * The stream has not reached EOF.
# 
# When +readpartial+ blocks, it waits for data or EOF. If some data is read,
# +readpartial+ returns with the data. If EOF is reached, readpartial raises
# an +EOFError+.
# 
# When +readpartial+ doesn't block, it returns or raises immediately.  If
# the byte buffer is not empty, it returns the data in the buffer. Otherwise, if
# the stream has some content, it returns the data in the stream. If the
# stream reaches EOF an +EOFError+ is raised.
def readpartial(maxlen); ''; end
##
# Reads at most _maxlen_ bytes from the ARGF stream in non-blocking mode.
def read_nonblock(maxlen); ''; end
##
# Reads +ARGF+'s current file in its entirety, returning an +Array+ of its
# lines, one line per element. Lines are assumed to be separated by _sep_.
# 
#    lines = ARGF.readlines
#    lines[0]                #=> "This is line one\n"
def readlines(sep=$/); []; end
##
# Reads +ARGF+'s current file in its entirety, returning an +Array+ of its
# lines, one line per element. Lines are assumed to be separated by _sep_.
# 
#    lines = ARGF.readlines
#    lines[0]                #=> "This is line one\n"
def to_a(sep=$/); []; end
##
# Returns the next line from the current file in +ARGF+.
# 
# By default lines are assumed to be separated by +$/+; to use a different
# character as a separator, supply it as a +String+ for the _sep_ argument.
# 
# The optional  _limit_ argument specifies how many characters of each line
# to return. By default all characters are returned.
def gets(sep=$/); ''; end
##
# Returns the next line from the current file in +ARGF+.
# 
# By default lines are assumed to be separated by +$/+; to use a different
# character as a separator, supply it as a +String+ for the _sep_ argument.
# 
# The optional  _limit_ argument specifies how many characters of each line
# to return. By default all characters are returned.
# 
# An +EOFError+ is raised at the end of the file.
def readline(sep=$/); ''; end
##
# Reads the next character from +ARGF+ and returns it as a +String+. Returns
# +nil+ at the end of the stream.
# 
# +ARGF+ treats the files named on the command line as a single file created
# by concatenating their contents. After returning the last character of the
# first file, it returns the first character of the second file, and so on.
# 
# For example:
# 
#    $ echo "foo" > file
#    $ ruby argf.rb file
# 
#    ARGF.getc  #=> "f"
#    ARGF.getc  #=> "o"
#    ARGF.getc  #=> "o"
#    ARGF.getc  #=> "\n"
#    ARGF.getc  #=> nil
#    ARGF.getc  #=> nil
def getc; '' || nil; end
##
# Gets the next 8-bit byte (0..255) from +ARGF+. Returns +nil+ if called at
# the end of the stream.
# 
# For example:
# 
#    $ echo "foo" > file
#    $ ruby argf.rb file
# 
#    ARGF.getbyte #=> 102
#    ARGF.getbyte #=> 111
#    ARGF.getbyte #=> 111
#    ARGF.getbyte #=> 10
#    ARGF.getbyte #=> nil
def getbyte; 0 || nil; end
##
# Reads the next character from +ARGF+ and returns it as a +String+. Raises
# an +EOFError+ after the last character of the last file has been read.
# 
# For example:
# 
#    $ echo "foo" > file
#    $ ruby argf.rb file
# 
#    ARGF.readchar  #=> "f"
#    ARGF.readchar  #=> "o"
#    ARGF.readchar  #=> "o"
#    ARGF.readchar  #=> "\n"
#    ARGF.readchar  #=> end of file reached (EOFError)
def readchar; '' || nil; end
##
# Reads the next 8-bit byte from ARGF and returns it as a +Fixnum+. Raises
# an +EOFError+ after the last byte of the last file has been read.
# 
# For example:
# 
#    $ echo "foo" > file
#    $ ruby argf.rb file
# 
#    ARGF.readbyte  #=> 102
#    ARGF.readbyte  #=> 111
#    ARGF.readbyte  #=> 111
#    ARGF.readbyte  #=> 10
#    ARGF.readbyte  #=> end of file reached (EOFError)
def readbyte; 0; end
##
# Returns the current offset (in bytes) of the current file in +ARGF+.
# 
#    ARGF.pos    #=> 0
#    ARGF.gets   #=> "This is line one\n"
#    ARGF.pos    #=> 17
def tell; 0; end
##
# Returns the current offset (in bytes) of the current file in +ARGF+.
# 
#    ARGF.pos    #=> 0
#    ARGF.gets   #=> "This is line one\n"
#    ARGF.pos    #=> 17
def pos; 0; end
##
# Seeks to offset _amount_ (an +Integer+) in the +ARGF+ stream according to
# the value of _whence_. See +IO#seek+ for further details.
def seek(amount, whence=IO::SEEK_SET); 0; end
##
# Positions the current file to the beginning of input, resetting
# +ARGF.lineno+ to zero.
# 
#    ARGF.readline   #=> "This is line one\n"
#    ARGF.rewind     #=> 0
#    ARGF.lineno     #=> 0
#    ARGF.readline   #=> "This is line one\n"
def rewind; 0; end
##
# Seeks to the position given by _position_ (in bytes) in +ARGF+.
# 
# For example:
# 
#     ARGF.pos = 17
#     ARGF.gets   #=> "This is line two\n"
def pos= position; 0; end
##
# Returns true if the current file in +ARGF+ is at end of file, i.e. it has
# no data to read. The stream must be opened for reading or an +IOError+
# will be raised.
# 
#    $ echo "eof" | ruby argf.rb
# 
#    ARGF.eof?                 #=> false
#    3.times { ARGF.readchar }
#    ARGF.eof?                 #=> false
#    ARGF.readchar             #=> "\n"
#    ARGF.eof?                 #=> true
def eof?; true || false; end
##
# Returns true if the current file in +ARGF+ is at end of file, i.e. it has
# no data to read. The stream must be opened for reading or an +IOError+
# will be raised.
# 
#    $ echo "eof" | ruby argf.rb
# 
#    ARGF.eof?                 #=> false
#    3.times { ARGF.readchar }
#    ARGF.eof?                 #=> false
#    ARGF.readchar             #=> "\n"
#    ARGF.eof?                 #=> true
def eof; true || false; end
##
# Puts +ARGF+ into binary mode. Once a stream is in binary mode, it cannot
# be reset to non-binary mode. This option has the following effects:
# 
# *  Newline conversion is disabled.
# *  Encoding conversion is disabled.
# *  Content is treated as ASCII-8BIT.
def binmode; ARGF; end
##
#  Returns true if +ARGF+ is being read in binary mode; false otherwise. (To
#  enable binary mode use +ARGF.binmode+.
# 
# For example:
# 
#     ARGF.binmode?  #=> false
#     ARGF.binmode
#     ARGF.binmode?  #=> true
def binmode?; true || false; end
##
# Writes _string_ if inplace mode.
def write(string); 0; end
##
# Writes the given object(s) to <em>ios</em>. The stream must be
# opened for writing. If the output field separator (<code>$,</code>)
# is not <code>nil</code>, it will be inserted between each object.
# If the output record separator (<code>$\\</code>)
# is not <code>nil</code>, it will be appended to the output. If no
# arguments are given, prints <code>$_</code>. Objects that aren't
# strings will be converted by calling their <code>to_s</code> method.
# With no argument, prints the contents of the variable <code>$_</code>.
# Returns <code>nil</code>.
# 
#    $stdout.print("This is ", 100, " percent.\n")
# 
# <em>produces:</em>
# 
#    This is 100 percent.
def print(); end
##
# If <i>obj</i> is <code>Numeric</code>, write the character whose code is
# the least-significant byte of <i>obj</i>, otherwise write the first byte
# of the string representation of <i>obj</i> to <em>ios</em>. Note: This
# method is not safe for use with multi-byte characters as it will truncate
# them.
# 
#    $stdout.putc "A"
#    $stdout.putc 65
# 
# <em>produces:</em>
# 
#    AA
def putc(obj); Object.new; end
##
# Writes the given objects to <em>ios</em> as with
# <code>IO#print</code>. Writes a record separator (typically a
# newline) after any that do not already end with a newline sequence.
# If called with an array argument, writes each element on a new line.
# If called without arguments, outputs a single record separator.
# 
#    $stdout.puts("this", "is", "a", "test")
# 
# <em>produces:</em>
# 
#    this
#    is
#    a
#    test
def puts(); end
##
# Formats and writes to <em>ios</em>, converting parameters under
# control of the format string. See <code>Kernel#sprintf</code>
# for details.
def printf(format_string , obj=0); end
##
# Returns the current filename. "-" is returned when the current file is
# STDIN.
# 
# For example:
# 
#    $ echo "foo" > foo
#    $ echo "bar" > bar
#    $ echo "glark" > glark
# 
#    $ ruby argf.rb foo bar glark
# 
#    ARGF.filename  #=> "foo"
#    ARGF.read(5)   #=> "foo\nb"
#    ARGF.filename  #=> "bar"
#    ARGF.skip
#    ARGF.filename  #=> "glark"
def filename; ''; end
##
# Returns the current filename. "-" is returned when the current file is
# STDIN.
# 
# For example:
# 
#    $ echo "foo" > foo
#    $ echo "bar" > bar
#    $ echo "glark" > glark
# 
#    $ ruby argf.rb foo bar glark
# 
#    ARGF.filename  #=> "foo"
#    ARGF.read(5)   #=> "foo\nb"
#    ARGF.filename  #=> "bar"
#    ARGF.skip
#    ARGF.filename  #=> "glark"
def path; ''; end
##
# Returns the current file as an +IO+ or +File+ object. #<IO:<STDIN>> is
# returned when the current file is STDIN.
# 
# For example:
# 
#    $ echo "foo" > foo
#    $ echo "bar" > bar
# 
#    $ ruby argf.rb foo bar
# 
#    ARGF.file      #=> #<File:foo>
#    ARGF.read(5)   #=> "foo\nb"
#    ARGF.file      #=> #<File:bar>
def file; IO.new || File.new; end
##
#  Sets the current file to the next file in ARGV. If there aren't any more
#  files it has no effect.
# 
# For example:
# 
#     $ ruby argf.rb foo bar
#     ARGF.filename  #=> "foo"
#     ARGF.skip
#     ARGF.filename  #=> "bar"
def skip; ARGF; end
##
#  Closes the current file and skips to the next in the stream. Trying to
#  close a file that has already been closed causes an +IOError+ to be
#  raised.
# 
# For example:
# 
#     $ ruby argf.rb foo bar
# 
#     ARGF.filename  #=> "foo"
#     ARGF.close
#     ARGF.filename  #=> "bar"
#     ARGF.close
#     ARGF.close     #=> closed stream (IOError)
def close; ARGF; end
##
# Returns _true_ if the current file has been closed; _false_ otherwise. Use
# +ARGF.close+ to actually close the current file.
def closed?; true || false; end
##
# Returns the current line number of ARGF as a whole. This value
# can be set manually with +ARGF.lineno=+.
# 
# For example:
# 
#     ARGF.lineno   #=> 0
#     ARGF.readline #=> "This is line 1\n"
#     ARGF.lineno   #=> 1
def lineno; 0; end
##
# Sets the line number of +ARGF+ as a whole to the given +Integer+.
# 
# +ARGF+ sets the line number automatically as you read data, so normally
# you will not need to set it explicitly. To access the current line number
# use +ARGF.lineno+.
# 
# For example:
# 
#     ARGF.lineno      #=> 0
#     ARGF.readline    #=> "This is line 1\n"
#     ARGF.lineno      #=> 1
#     ARGF.lineno = 0  #=> 0
#     ARGF.lineno      #=> 0
def lineno= integer; 0; end
##
# Returns the file extension appended to the names of modified files under
# inplace-edit mode. This value can be set using +ARGF.inplace_mode=+ or
# passing the +-i+ switch to the Ruby binary.
def inplace_mode; ''; end
##
#  Sets the filename extension for inplace editing mode to the given String.
#  Each file being edited has this value appended to its filename. The
#  modified file is saved under this new name.
# 
#  For example:
# 
#      $ ruby argf.rb file.txt
# 
#      ARGF.inplace_mode = '.bak'
#      ARGF.lines do |line|
#        print line.sub("foo","bar")
#      end
# 
# Each line of _file.txt_ has the first occurrence of "foo" replaced with
# "bar", then the new line is written out to _file.txt.bak_.
def inplace_mode= ext; ARGF; end
##
#  Returns the external encoding for files read from +ARGF+ as an +Encoding+
#  object. The external encoding is the encoding of the text as stored in a
#  file. Contrast with +ARGF.internal_encoding+, which is the encoding used
#  to represent this text within Ruby.
# 
#  To set the external encoding use +ARGF.set_encoding+.
# 
# For example:
# 
#     ARGF.external_encoding  #=>  #<Encoding:UTF-8>
def external_encoding; Encoding.new; end
##
# Returns the internal encoding for strings read from +ARGF+ as an
# +Encoding+ object.
# 
# If +ARGF.set_encoding+ has been called with two encoding names, the second
# is returned. Otherwise, if +Encoding.default_external+ has been set, that
# value is returned. Failing that, if a default external encoding was
# specified on the command-line, that value is used. If the encoding is
# unknown, nil is returned.
def internal_encoding; Encoding.new; end
##
# If single argument is specified, strings read from ARGF are tagged with
# the encoding specified.
# 
# If two encoding names separated by a colon are given, e.g. "ascii:utf-8",
# the read string is converted from the first encoding (external encoding)
# to the second encoding (internal encoding), then tagged with the second
# encoding.
# 
# If two arguments are specified, they must be encoding objects or encoding
# names. Again, the first specifies the external encoding; the second
# specifies the internal encoding.
# 
# If the external encoding and the internal encoding are specified, the
# optional +Hash+ argument can be used to adjust the conversion process. The
# structure of this hash is explained in the +String#encode+ documentation.
# 
# For example:
# 
#     ARGF.set_encoding('ascii')         # Tag the input as US-ASCII text
#     ARGF.set_encoding(Encoding::UTF_8) # Tag the input as UTF-8 text
#     ARGF.set_encoding('utf-8','ascii') # Transcode the input from US-ASCII
#                                        # to UTF-8.
def set_encoding(ext_enc); ARGF; end
end

# The exception information message set by 'raise'. 
$! = Exception.new

# Array of backtrace of the last exception thrown.
$@ = ['']

# The string matched by the last successful match.
$& = ''

# The string to the left  of the last successful match.
$` = ''

# The string to the right of the last successful match.
$' = ''

# The highest group matched by the last successful match.
$+ = ''

# The information about the last match in the current scope.
$~ = MatchData.new

# The flag for case insensitive, nil by default.
$= = true || false

# The input record separator, newline by default.
$/ = ''

# The output record separator for the print and IO#write. Default is nil.
$\ = ''

# The output field separator for the print and Array#join.
$, = ''

# The default separator for String#split.
$; = ''

# The current input line number of the last file that was read.
$. = 0

# The virtual concatenation file of the files given on command line (or from $stdin if no files were given).
$< = IO.new

# The default output for print, printf. $stdout by default.
$> = IO.new

# The last input line of string by gets or readline.
$_ = ''

# Contains the name of the script being executed. May be assignable.
$0 = ''

# Command line arguments given for the script sans args.
$* = ['']

# The process number of the Ruby running this script.
$$ = 0

# The status of the last executed child process.
$? = 0

# Load path for scripts and binary modules by load or require.
$: = ['']

# The array contains the module names loaded by require.
$" = ['']

# The status of the -d switch.
$DEBUG = true || false

# Current input file from $<. Same as $<.filename.
$FILENAME = ''

# The alias to the $:.
$LOAD_PATH = $:

# The current standard error output.
$stderr = IO.new

# The current standard input.
$stdin = IO.new

# The current standard output.
$stdout = IO.new

# The verbose flag, which is set by the -v switch.
$VERBOSE = true || false

# The alias to $/.
$-0 = $/

# True if option -a is set. Read-only variable.
$-a = true || false

# The alias to $DEBUG.
$-d = $DEBUG

# The alias to $;.
$-F = $;

# In in-place-edit mode, this variable holds the extension, otherwise nil.
$-i = nil

# The alias to $:.
$-I = $:

# True if option -l is set. Read-only variable.
$-l = true || false

# True if option -p is set. Read-only variable.
$-p = true || false

# The alias to $VERBOSE.
$-v = $VERBOSE

# True if option -w is set.
$-w = true || false

# The typical true value.
TRUE = true

# The false itself.
FALSE = false

# The nil itself.
NIL = nil

# The standard input. The default value for $stdin.
STDIN = $stdin

# The standard output. The default value for $stdout.
STDOUT = $stdout

# The standard error output. The default value for $stderr.
STDERR = $stderr

# The hash contains current environment variables.
ENV = {''=>''}

# The alias to the $<.
ARGF = $<

# The alias to the $*.
ARGV = $*

# The file object of the script, pointing just after __END__.
DATA = File.new

# The ruby version string (VERSION was deprecated).
RUBY_VERSION = ''

# The release date string.
RUBY_RELEASE_DATE = ''

# The platform identifier.
RUBY_PLATFORM = ''

