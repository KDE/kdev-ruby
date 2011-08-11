module Dummy
  module BA
    def inject(n)
      each { |value| n = yield(n, value) }
      n
    end

    def BA.greeting str
      "Hello #{str}!"
    end

    def BA.want_a_block(&mblock)
      yield mblock
    end

    CONST = 0
  end
end

module AA
  include ::Dummy::BA

  def sum(initial = 0)
    inject(initial) { |n, value| n + value }
  end

  ACONST = 1
end

class Range
  include AA
end

puts (1..5).sum
puts Dummy::BA::CONST, ::AA::ACONST
puts(Dummy::BA::CONST, ::AA::ACONST)
puts 'lalala', Dummy::BA.greeting('Miquel')
puts('lalala', Dummy::BA.greeting('Miquel'))
puts "Where is thumbkin?", Dummy::BA.want_a_block { 'Here I am!' }
puts("Where is thumbkin?", Dummy::BA.want_a_block { 'Here I am!' })
puts %Q{ lalala }.length

# Original method_call test :)
__inspect__.sub("Chameleon", method.to_s.sub('to_','').capitalize)
method.to_s.sub('to_','').capitalize
puts CharDet.detect("Привет Волку")["encoding"]
b.a(1).c
a.b.c 1, 2
puts 1+1

a.class
foo 1,
    2

foo a, :a => 'string', b: 'another'
where_is_thumbkin? && here_i_am!
