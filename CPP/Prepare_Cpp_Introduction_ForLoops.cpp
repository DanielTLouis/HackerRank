/*
A for loop is a programming language statement which allows code to be repeatedly 
executed.
The syntax is
        for ( <expression_1> ; <expression_2> ; <expression_3> )
            <statement>
    -expression_1 is used for intializing variables which are generally used for 
    controlling the terminating flag for the loop.
    -expression_2 is used to check for the terminating condition. If this 
    evaluates to false, then the loop is terminated.
    -expression_3 is generally used to update the flags/variables.
A sample loop is
        for(int i = 0; i < 10; i++) {
            ...
        }
    In this challenge, you will use a for loop to increment a variable through 
    a range.
Input Format
    You will be given two positive integers, a and b (a<=b), separated by 
    a newline.
Output Format
    For each integer  in the inclusive interval [a,b]:
        -If 1<=n<=9, then print the English representation of it in lowercase. 
        That is "one" for 1, "two" for 2, and so on.
        -Else if n>9 and it is an even number, then print "even".
        -Else if n>9 and it is an odd number, then print "odd".
    Note: [a,b]={xis an element of Z | a<=x<=b}={a,a+1,...,b}
Sample Input
    8
    11
Sample Output
    eight
    nine
    even
    odd
*/

#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    // Complete the code.
    int a, b;
    std::cin >> a >> b;
    for(int i = a; i <= b; i++)
    {
        if(i >=1 && i <= 9)
        {
            if(i == 1)
            {
                std::cout << "one\n";
            }
            else if(i == 2)
            {
                std::cout << "two\n";
            }
             else if(i == 3)
            {
                std::cout << "three\n";
            }
             else if(i == 4)
            {
                std::cout << "four\n";
            }
             else if(i == 5)
            {
                std::cout << "five\n";
            }
             else if(i == 6)
            {
                std::cout << "six\n";
            }
             else if(i == 7)
            {
                std::cout << "seven\n";
            }
             else if(i == 8)
            {
                std::cout << "eight\n";
            }
             else if(i == 9)
            {
                std::cout << "nine\n";
            }
        }
        else{
            if(i % 2 == 0)
            {
                std::cout << "even\n";
            }
            else 
            {
                std::cout << "odd\n";
            }
        }
    }
    return 0;
}
