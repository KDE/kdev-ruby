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
elsif b > a then c = 1
else b = 5
end
