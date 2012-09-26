#!/usr/bin/python

def fib(n):
  assert n >= 1
  if n == 1: return 1
  if n == 2: return 2
  a = 1
  b = 2
  for i in xrange(3, n + 1):
    r = a + b
    a = b
    b = r
  return r

def generate_fib(n):
  assert n >= 1
  m = [ 1, 2 ]
  a = 1
  b = 2
  for i in xrange(3, n + 1):
    r = a + b
    m.append(r)
    a = b
    b = r
  return m

def fsum(n):
  r = 0
  for i in xrange(1, n + 1):
    r = r + fib(i)
  return r
    
def level(n):
  prev = 0
  i = 1
  while 1:
    curr = fsum(i)
    if prev < n and n <= curr:
      return i
    i = i + 1
    prev = curr

def path(n):
  N = n
  r = []
  while n >= 2:
    l = level(n)
    if n <= fsum(l - 1) + fib(l - 1):
      r.append("l")
      sum = 0
      for i in xrange(1, l - 2):
        sum = sum + fib(i)
      n = n - sum - 2
    else:
      r.append("r")
      if l > 2:
        r.append("u")
      sum = 0
      for i in xrange(1, l):
        sum = sum + fib(i)
      n = n - sum - 2
  return r
    
# print path(15)

def level_start_index(n):
  l = level(n) 
  return fsum(l) + 1

def current_level_offset(n):
  l = level(n)
  return n - (fsum(l - 1) + 1)
  
fibs = generate_fib(40)

def split_by_fib(n):
  i = len(fibs) - 1
  r = []
  while i >= 0:
    f = fibs[i]
    if f <= n:
      n = n - f
      r.append(f)
    else:
      i = i - 1
  return r
  
def next_fib(n):
  for i in xrange(0, len(fibs)):
    if fibs[i] == n:
      return fibs[i + 1]
  assert false

def piping(n):
  p = path(n)
  t = 1
  for i in p:
    jump = 0
    if t > 1:
      jump = sum(map(lambda x: next_fib(x), split_by_fib(current_level_offset(t))))
    if i == 'r':
      jump = jump + 1
    t = level_start_index(t) + jump
    print t
  
piping(433494435)

print fibs
