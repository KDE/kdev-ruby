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
a.each(1) do |x|
  puts(x)
end

a.each(1) do
  |x|
  puts(x)
end

a.foo 1, 2 do |x|
  puts x
end

a.each(1).c.d do
  |x|
  puts(x)
end

a.each(1).c.d 1, 2 do
  |x|
  puts(x)
end

a.each do |x, y, *z|
end
