def function(a, b: {})
end

def foo(a: '', b: '')
  puts "#{a}, #{b}"
  puts args
end

foo(a: 1, b: 2, 'asd' => 1)

def another(a, *b, c: '')
end

def yet_another(a, b = 1, *c, d: '', **e, &blk)
end

def yay a: 1, **; end
