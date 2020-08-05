import math

t = int(input())
for i in range(t):
    n = int(input())
    sum = n * (n + 1) * (2 * n + 1) // 6
    sq = int(math.sqrt(sum))
    if sq * sq == sum :
        print("Fake news!")
    else:
        print("Nobody knows it better than me!")
