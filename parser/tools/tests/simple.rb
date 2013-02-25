def foo
  return 1+1
end

def foo1
  return 1
end

def a
  puts 'el riu anoia fa pudor'
end

a = 0
b = 0
while a < 10
  if a == 5 && b == 0
    b = 1
    redo
  end
  next
  a += 1
end

alias foo foo1
alias foo1 :a
alias $ERROR_INFO $!
alias mon= month=
alias [] test

undef :a, foo
if defined? anoia
  puts 'a'
end
