$: << File.expand_path(File.dirname(__FILE__) + 'lib')

$global = 0
if $-a
  puts '-a option is set'
end

begin
  1/0
rescue
  puts $!
end

# (global) vars starting with $
$!
$@
$;
$,
$/
$\
$.
$_
$>
$<
$$
$?
$~
$= # deprecated
$*
$&
$`
$'
$+
