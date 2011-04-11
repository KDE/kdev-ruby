begin
  a = 1
  c = 0
  a /=  c
rescue ZeroDivisionError => e
  b = 1
rescue NameError then
  c += 1
else
  d = 0
ensure
  a = 0
end

begin
  1/0
rescue ZeroDivisionError, NameError => m
  puts e.message
end
