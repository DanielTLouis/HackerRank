#Task:
#The prodived code stub reads and integer, n, from STDIN. For all non-negative
#integers i<n print i^2

if __name__ == '__main__':
    n = int(raw_input())
i = 0
if(n > 0):
    for i in range(n):
        print(i * i)
