num = 5
case
  when num % 2 == 0 then :a
  when num % 3 == 0 then :b
  else :c
end

n = case
  when num % 2 == 0 then :a
  when num % 3 == 0 then :b
  else :c
end

case num
  when 2 then :a
  when 3 then :b
end

case a
when :text
  return 1
=begin

=end
end
