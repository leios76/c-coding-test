
n = int(input())
time_list = []
last_idx = 0
cnt = 0
for i in range(n):
    time_list.append(list(map(int, input().split())))

time_list.sort(key=lambda x: (x[1], x[0]))

for i in range(len(time_list)):
    if time_list[i][0] >= last_idx:
        print(time_list[i])
        last_idx = time_list[i][1]
        cnt += 1
        continue
    else:
        continue

print(cnt)