#Prompt:
#The provided code stub reads two integers from STDIN, a and b.
#Add code to print three lines where:
#   1. the first line contains the sum of the two numbers.
#   2. the second line contains the differece of the two numbers (first - second).
#   3. the third line contains the product of the two numbers.

if __name__ == '__main__':
    a = int(raw_input())
    b = int(raw_input())
    print(a+b)
    print(a-b)
    print(a*b)
