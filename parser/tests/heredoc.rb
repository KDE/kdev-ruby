a = <<start
This is a heredoc
start

b = <<-do
  asd
do

<<here
Morehere
here

this_is = a_shift << not_a_heredoc
