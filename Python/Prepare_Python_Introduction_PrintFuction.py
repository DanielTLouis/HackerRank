#The included code stub will read an integer, , from STDIN.
#Without using any string methods, try to print the following:
#123...n
#Note that "" represents the consecutive values in between.

from __future__ import print_function

if __name__ == '__main__':
    n = int(raw_input())
i = 1
for i in range(1,n+1):
    print(i, end = '')
