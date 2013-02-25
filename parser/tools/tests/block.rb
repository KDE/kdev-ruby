a = lambda { |x| return x + 1 }
a = lambda { |;y| return y + 1  }
a = lambda { |x;y| return y + 1  }

fun = ->(a, b) do
  puts a + b
end
fun.call(1, 2)

variable = -> { puts 'lalala' }
variable.call

hash = { foo: ->(a, b) { puts a + b } }
hash[:foo].call(1, 2)

a = [1, 2, 3, 4]
a.foo(1) do |x|
  puts(x)
end

a.foo(1) do
  |x|
  puts(x)
end

a.foo 1, 2 do |x|
  puts x
end

a.foo(1).c.d do
  |x|
  puts(x)
end

a.foo(1).c.d 1, 2 do
  |x|
  puts(x)
end

a.foo do |x, y, *z|
end

{ a: 1, b: 2 }.each do |x, y|
end

5.times { puts 'Spartans! What is your profession !?' }

foo do |x = 1|
end

foo do |x = 1, *y|
end

foo do |*| # Expected: the star has pos = -1
end

foo do |x, &y|
end

foo do |x, y = 1; z|
end

a {[]}
