a = lambda { |x| return x + 1 }
a = lambda { |;y| return y + 1  }
a = lambda { |x;y| return y + 1  }

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
