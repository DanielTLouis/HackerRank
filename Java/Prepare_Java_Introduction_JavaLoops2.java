/*
We use the integers a, b, and n to create the following series:
(a+2^0 *b),(a+2^0 *b+2^1 *b),...,(a+2^0 *b+...+2^n *b)
You are given  queries in the form of a, b, and n. For each query, 
print the series corresponding to the given a, b, and n values as a 
single line of n space-separated integers.
Input Format
    The first line contains an integer, q, denoting the number of 
    queries.
    Each line i of the q subsequent lines contains three 
    space-separated integers describing the respective a_i, b_i, and 
    n_i values for that query.
Constraints
    0<=q<=500
    0<=a,b<50
    1<=n<=15
Output Format
    For each query, print the corresponding series on a new line. Each 
    series must be printed in order as a single line of n 
    space-separated integers.
Sample Input
    2
    0 2 10
    5 3 5
Sample Output
    2 6 14 30 62 126 254 510 1022 2046
    8 14 26 50 98
Explanation
    We have two queries:
    1.We use a=0, b=2, and n=10 to produce some series :
        s_0,s_1,...,s_n-1
            s_0=0+1*2=2
            s_1=0+1*2+2*2=6
            s_2=0+1*2+2*2+4*2=14
        ... and so on.
    Once we hit n=10, we print the first ten terms as a single line of
    space-separated integers.
    We use a=5, b=3, and n=5 to produce some series :
    ...
    We then print each element of our series as a single line of 
    space-separated values.
*/

import java.util.*;
import java.io.*;
import java.lang.Math;

class Solution{
    public static void main(String []argh){
        Scanner in = new Scanner(System.in);
        int t=in.nextInt();
        for(int i=0;i<t;i++){
            int a = in.nextInt();
            int b = in.nextInt();
            int n = in.nextInt();
            
            for(int j = 0; j < n; j++)
            {
                a += Math.pow(2,j) * b;
                System.out.print(a);
                System.out.print(' ');
            }
            System.out.print('\n');
        }
        in.close();
    }
}