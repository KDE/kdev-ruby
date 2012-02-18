
super( @source.eof? ? str : str+@source.readline( @line_break ) )

overflow = "This text should flow gracefully onto the next page, like a stream" +
           " flows elegantly from a mountain lake down into the village below."

b = 1
a = b
    - 1 # assign and unary
a = b -
    1   # just an assign

a = a *
    b

a = a %
    b

a = b ^
    2

a = b &
    2

a = b |
    2

a = b /
    2.0
