a = 'Hello'
b = 'I\'m a string'
c = 'Let\'s' + ' concatenate!'
d = "I'm a double-quoted string"
e = 0
f = "The value of e variable: #{e}"
g = 'Don\'t forget' ' this way to' ' concatenate strings'

this_is = %q( This is )
persian = %Q( #{this_is} blasphemy! #{this_is} madness! )
leonidas = %{ Madness? #{this_is} Sparta! }

k = `ls \`asdas`
l = `ls`
dir = "."
m = `ls #{dir}`

# test cases for general delimited input
# quoted strings
%Q|this is a string|
%Q{this is a string}
%Q(this is a string)
%Q<this is a string>
%Q[this is a string]

%|also a string|
%{also a string}
%(also a string)
%<also a string>
%[also a string]

# apostrophed strings
%q|apostrophed|
%q{apostrophed}
%q(apostrophed)
%q<apostrophed>
%q[apostrophed]

%x[ ls ]

# Weird way to declare a char :D
c = ?a
c = ?\n
c = ?-
a = b ?1 : c
a = (b) ?1 : c

a = 'asdas
asd'

a = 'asd
asdasd
asdasdasdasd'

b = "asd #{c.foo}" "aaa #{a} "
