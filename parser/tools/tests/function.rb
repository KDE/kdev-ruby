
def foo? a
  a = 0
  while a < 5
    a += 1
  end
rescue
  b = 5
else
  c = 3
ensure
  d = 9
end

def foo a,
    b
end

def foo(a, b)
end

def a.append_features(klass)
  super

  klass.install_must_call_validator('', ::RSS::URI)
end

# Singleton

class Single
  def foo a = 2, b
    25
  end
end

s = Single.new
puts s.foo

def s.foo a = 2
  20
end

puts s.foo

# Defining functions with a weird argument list

def aa a, b, c
end

def bb a = 1, b = 2, c = 3
end

def funny *a, c, b, &d
end

def jolly a = 0, b = 1, c, d, &e
end

def fuck! a = 0, b = 1, *c, d, e, &f
end

def nice a = 0, b = 1, *c, &d
end

def yeah! a, b, c = 1, d = 2, e, f, &g
end

def head_shot! a, b, c = 1, d = 2, *e, f, g, &h
end

def final a, b, c = 1, d = 2, *e, &h
end

def == other
end

def another(a=1)
end

def a.b=(val)
end
