//prompt is down below 

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    int n;
    scanf("%d", &n);
    int temp = 0, tempTotal = 0;
    //Complete the code to calculate the sum of the five digits on n.
    for (int i = 10000; i > 0; i /= 10)
    {
        temp = (n / i);
        tempTotal += temp;
        n -= temp * i;
    }

    printf("%d", tempTotal);
    return 0;
}

/*
Objective

The modulo operator, %, returns the remainder of a division. For example,
4 % 3 = 1 and 12 % 10 = 2. The ordinary division operator, /, returns a truncated 
integer value when performed on integers. For example, 5 / 3 = 1. To get the last
digit of a number in base 10, use 10 as the modulo divisor.

Task

Given a five digit integer, print the sum of its digits.

Input Format

The input contains a single five digit number, n.

Constraints
10000 <= n <= 99999

Output Format

Print the sum of the digits of the five digit number.

Sample Input 0

10564
Sample Output 0

16
*/