module A a = 0
end

module B
  a = 1
  b = 0
end

module C
  def foo
    a = 0
  end
end

module Foo
  module A
    def b
      2
    end
    module_function :b
  end
  def a
    A::b
  end

  module_function :a
end

a = Foo::a
puts a
