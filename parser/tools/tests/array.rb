def foo a, b
  a + b
end

def alone
  3
end

a = [1, (b = foo 1, 2), 3]
b = [foo(1, 2), 2]
c = [alone, foo(1, 2), d = a] # Warning: 'alone' detected as object
a = [1, (puts 1, 2), 2]
e = [(f, g = 1, 2), 3]
h = [(i, = 1, 2, 3), 4]
j = [1 + 3, 'string''another''one']
k = [[1, 2, 3], [[1, 2], [1, 2]], {'asd' => 1 }]

x = [1, 2, 4]
y = [[1, 2], [[1, 2], [3, 4]]]
x[0] = y[0][alone] + y[1][1][0]

a = [
  1, 2 ]
a = [
  1,
  2]
a = [
  1,
  2
]

%w{one two three}
%w(one two three)
%w<one two three>
%w[one two three]

%w[ HTML HEAD BODY P PLAINTEXT DT DD LI OPTION tr
          th td ]
%w[one two three]
%w$Revision: 26193 $
