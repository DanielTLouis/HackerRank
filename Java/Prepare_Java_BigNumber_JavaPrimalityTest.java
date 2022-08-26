/*
A prime number is a natural number greater than 1 whose only positive
divisors are  and itself. For example, the first six prime numbers are 2, 3,
 5, 7, 11, and 13.
Given a large integer, n, use the Java BigInteger class' isProbablePrime*
method to determine and print whether it's prime or not prime.
* https://docs.oracle.com/javase/7/docs/api/java/math/BigInteger.html#isProbablePrime%28int%29 *
Input Format
    A single line containing an integer, n (the number to be checked).
Constraints
    n contains at most 100 digits.
Output Format
    If n is a prime number, print prime; otherwise, print not prime.
Sample Input
    13
Sample Output
    prime
Explanation
    The only positive divisors of 13 are 1 and 13, so we print prime.
*/

import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.regex.*;



public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));

        String n = bufferedReader.readLine();
        BigInteger a = new BigInteger(n);
        if(a.isProbablePrime(1))
        {
            System.out.println("prime");
        }
        else
        {
            System.out.println("not prime");
        }
        bufferedReader.close();
    }
}
