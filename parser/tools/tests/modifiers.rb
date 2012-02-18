a = 0
a = 1 if a == 0
a += 1 unless a != 1
a += 1 while a < 5
a -= 1 until a == 0

begin
  self[column] = SecureRandom.urlsafe_base64
end while User.exists?(column => self[column])

a unless (1..31).include?
