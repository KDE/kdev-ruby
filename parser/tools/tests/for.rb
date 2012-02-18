a = 0
for i in (1..10) do
  a += 1
end

for i in (1...10)
  a += 1
end

for i, j in {a: 'hola', b: 'adeu'}
  puts "Primer: #{i}, Segon: #{j}"
end

for i, j in (1..10) do
  puts i
end
