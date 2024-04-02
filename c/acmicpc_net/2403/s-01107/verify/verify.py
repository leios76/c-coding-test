#!/usr/bin/python

data = """
1555
8
0 1 3 4 5 6 7 9
670

944
7
2 3 4 5 6 7 9
59
""".split('\n')
def sol(N, M, wrong_btn):
    asnwer = 0
    return answer

i = 0
N, M, wrong_btn = None, None, set()
while i != len(data):
    if data[i] == '':
        N, M, wrong_btn = None, None, set()
        i += 1
        continue
    if N is None:
        N = int(data[i])
        i += 1
        M = int(data[i])
        i += 1
        if M != 0:
            wrong_btn = set(data[i].split())
            i += 1
        ans = int(data[i])
        i += 1
        if sol(N, M, wrong_btn) != ans:
            print(N, M, wrong_btn, ans)
        N, M, wrong_btn = None, None, set()