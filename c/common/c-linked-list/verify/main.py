#!/usr/bin/python

N = int(input())
a = ""
arr = [[] for _ in range(51)]
for _ in range(N):
    a = str(input())
    arr[len(a)].append(a)

for i in arr:
    if len(i) == 0:
        pass
    else:
        temp = list(set(sorted(i)))
        for j in temp:
            print(j)