class FooClass
  def foo
  end
end

class FooFooClass < FooClass
  def foofoo
  end
end

f = FooClass.new
puts f.foo

class << (a = 0)
  def foo
    'Modified'
  end
end

puts f.foo

class << { a: 3 }
  def foo
    'Modified2'
  end
end

puts f.foo

class
  << f
  def foo
    'Modified3'
  end
end

puts f.foo

class Lalala << ::FooClass
end
