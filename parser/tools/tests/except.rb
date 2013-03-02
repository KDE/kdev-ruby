begin
  a = 0
end

begin
  a = 0
rescue NameError
  c = 0
end

begin
  a = 0
rescue NameError
  c = 0
rescue ZeroDivisionError
  d = 0
end

begin
  a = 0
else
  d = 0
end

begin
  a = 0
ensure
  d = 1
end

begin
  a = 0
else
  c = 0
ensure
  d = 0
end

begin
  a = 0
rescue ZeroDivisionError
  b = 0
else
  a = 0
ensure
  c = 0
end

begin
  a = 1
  c = 0
  a /=  c
rescue ZeroDivisionError => e
  b = 1
rescue NameError then
  c += 1
rescue RuntimeError
  puts 'lalala'
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

begin
rescue => ex
  1
end

begin
  return
rescue FTPPermError => e
end
