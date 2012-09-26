a = input()
b = input()

o = ""
for i in xrange(a, b + 1):
  if i % 2 == 0:
    o = o + str(i) + " "
print o.strip()

