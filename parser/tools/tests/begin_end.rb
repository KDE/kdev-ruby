BEGIN {
  a = 0
  a += 1
}

END { b = 0 }
END { b = 0
      }

puts DATA.read

__END__
Perl, Perl everywhere... 
