a = 1
b = a
c = 2

unless a == 4
  b = 5
  c += 1
  if c == 3
    c -= 1
  end
end

if b == c then
  a += 1
elsif b > a
  c = 1
else
  b = 5
end

if b == c
  a += 1
elsif b > a
  then c = 1
else
  b = 5
end

if b == c
  then
  a += 1
elsif b > a then
  c = 1
else
  b = 5
end

if b == c then a += 1
elsif (b > a) then c = 1
else b = 5
end

if name !~ /[a-zA-Z0-9_.:\/]+/
  raise ArgumentError, "Wrong XML-RPC method-name"
end

if param >= -(2**31) and param <= (2**31-1)
end

if a and
    n
end

if /^(\d+)\.(\d+)$/ =~ version
  @major, @minor = $1.to_i, $2.to_i
end

if (ret = @major <=> other.major) == 0
  return @minor <=> other.minor
end
