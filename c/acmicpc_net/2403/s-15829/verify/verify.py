#!/usr/bin/python

import sys

h = 0
m = 1

l = (int)(sys.stdin.readline())
ch = sys.stdin.readline()

for i in range(0, l):
    h += (ord(ch[i]) - ord('a') + 1) * m
    print((ord(ch[i]) - ord('a') + 1) * m, h)
    m = m * 31

print(1234567891)
print((h % 1234567891))