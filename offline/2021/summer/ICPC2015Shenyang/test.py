import sys

sys.stdout = open('in.txt', 'w')
print(6)
for i in range(6):
    n = 100000
    m = 500000
    print(n, m)
    for j in range(m):
        print(1000000000, 2, (j + 1) % n + 1, (j + 2) % n + 1)