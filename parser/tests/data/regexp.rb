a / 1
a = a / 1
/asd/
a = / 1 /
a = / \/ /
a = %r[ Mon "adasdadas" /asdasda/ @a ]
variable = 'variable'
a = /#{variable}/
a = /#{variable}#{a}/

path.gsub(/..\/tests\/?/, '')

if ajax_method =~ /^find_user_(.+)$/
  validate_user_uniqueness $1
else
  raise NoMethodError, "Linx: '#{ajax_method}' is not a valid Ajax method!"
end
