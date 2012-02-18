a, *, b, c = 0, 1, 3, [1, 2]
a, (b, c), d = 0, 1, 2
a,
    b =
    1,
    2
a, b = 1,
   2
a = 1, 2, 3
a, = 1, 2, 3
a[0] = 1
a[foo 1, 2, 3] = 1
a.b = 1
a::b.c = 2

a = if b < 1
  3
  else
    4
  end

b = class Klass
end

a = begin
  0
end

a.CONST += 1
a::b += 1
a.b += 1
a[1] += 1
a::year, b.month, c.DAY, d::LALA = year, month, day, lala
