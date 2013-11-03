# script to check whether a file has balanced glPushMatrix() and glPopMatrix() calls

i, j = 0, 0
File.open(ARGV[0]).each do |line|
  j += 1
  if line =~ /PushMatrix/
    i += 1
  elsif line =~ /PopMatrix/
    i -= 1
  end
  if i < 0 then puts j end
end