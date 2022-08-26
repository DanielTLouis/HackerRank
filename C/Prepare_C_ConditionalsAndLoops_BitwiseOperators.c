/*
problem:
In this challenge, you will use logical bitwise operators. All data is stored in its binary representation. The logical operators, and C language, use 1 to represent true and 0 to represent false. The logical operators compare bits in two numbers and return true or false, 0 or 1, for each bit compared.

Bitwise AND operator & The output of bitwise AND is 1 if the corresponding bits of two operands is 1. If either bit of an operand is 0, the result of corresponding bit is evaluated to 0. It is denoted by &.

Bitwise OR operator | The output of bitwise OR is 1 if at least one corresponding bit of two operands is 1. It is denoted by |.

Bitwise XOR (exclusive OR) operator ^ The result of bitwise XOR operator is 1 if the corresponding bits of two operands are opposite. It is denoted by ^.
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
//Complete the following function.


void calculate_the_maximum(int n, int k) {
    int maxAnd = 0;
    int maxOr = 0;
    int maxXor = 0;
    //the numbers int the range 0 - n to see the max bitwise 
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            //if it is larger then the set one then make it that new one and make sure its not as large as k
            if (((i & j) > maxAnd) && ((i & j) < k)) {
                maxAnd = i & j;
            }
            if (((i | j) > maxOr) && ((i | j) < k)) {
                maxOr = i | j;
            }
            if (((i ^ j) > maxXor) && ((i ^ j) < k)) {
                maxXor = i ^ j;
            }
        }
    }

    printf("%d\n%d\n%d\n", maxAnd, maxOr, maxXor);
}

int main() {
    int n, k;

    scanf("%d %d", &n, &k);
    calculate_the_maximum(n, k);

    return 0;
}
