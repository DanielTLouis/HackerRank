/*
Given a string, s, and two indices, start and end, print a
substring consisting of all characters in the inclusive range
from start to end-1. You'll find the String class' substring
method helpful in completing this challenge.
Input Format
    The first line contains a single string denoting s.
    The second line contains two space-separated integers
    denoting the respective values of start and end.
Constraints
    1<=|s|<=100
    0<=start<end<=n
    String s consists of English alphabetic letters (i.e.,
    [a-zA-Z]) only.
Output Format
    Print the substring in the inclusive range from start to
    end-1.
Sample Input
    Helloworld
    3 7
Sample Output
    lowo
Explanation
    In the diagram below, the substring is highlighted in green:
    substring.png
*/

import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        Scanner sc = new Scanner(System.in);
        String s = sc.next();
        int start = sc.nextInt();
        int end = sc.nextInt();
        String ns = s.substring(start, end);
        System.out.println(ns);
    }
}
