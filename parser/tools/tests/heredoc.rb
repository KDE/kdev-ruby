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

@body << <<-_end_of_html_
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN">
<HTML>
  <HEAD><TITLE>#{HTMLUtils::escape(@reason_phrase)}</TITLE></HEAD>
  <BODY>
    <H1>#{HTMLUtils::escape(@reason_phrase)}</H1>
    #{HTMLUtils::escape(ex.message)}
    <HR>
_end_of_html_

msg = <<"MSGEND"
  <html>
    <head>
      <title>#{err}</title>
    </head>
    <body>
      <h1>#{err}</h1>
      <p>Unexpected error occured while processing XML-RPC request!</p>
    </body>
  </html>
MSGEND

  msg = <<-"MSGEND"
    <html>
      <head>
        <title>#{err}</title>
      </head>
      <body>
        <h1>#{err}</h1>
        <p>Unexpected error occured while processing XML-RPC request!</p>
      </body>
    </html>
  MSGEND

a = <<-'erb1',
  sdasda
erb1
