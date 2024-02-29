#!/usr/bin/python

import re
import sys

t = sys.stdin.readline()
for i in range(int(t)):
    line = sys.stdin.readline().strip()
    m = re.match('(100+?1+?|01)+?', line)
    if m == None:
        print("NO")
    elif m.group(0) == line:
        print("YES")
    else:
        print("NO")
