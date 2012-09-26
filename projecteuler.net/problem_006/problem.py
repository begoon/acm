n = 100
r = range(1, n + 1)
a = sum(map(lambda x: x*x, r))
b = sum(r) * sum(r)
print b - a
