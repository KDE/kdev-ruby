a = 0
b = 0

while a < 5
  a += 1
end

until a == 0
  a -= 1
end

while a < 5 do
  a += 2
  if b == 0
    b += 1
  else
    b += 2
  end
  a -= 1
end

until a == 0 do
  a -= 1
end
