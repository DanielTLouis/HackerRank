/*
Given a string, , matching the regular expression [A-Za-z !,?._'@]+, split
the string into tokens. We define a token to be one or more consecutive
English alphabetic letters. Then, print the number of tokens, followed by
each token on a new line.
Note: You may find the String.split* method helpful in completing this
challenge.
* https://docs.oracle.com/javase/8/docs/api/java/lang/String.html#split-java.lang.String- *
Input Format
    A single string, s.
Constraints
    1<=length of s <=4*10^5
    s is composed of any of the following: English alphabetic letters, blank
    spaces, exclamation points (!), commas (,), question marks (?), periods
    (.), underscores (_), apostrophes ('), and at symbols (@).
Output Format
    On the first line, print an integer, n, denoting the number of tokens in
    string s(they do not need to be unique). Next, print each of the n
    tokens on a new line in the same order as they appear in input string s.
Sample Input
    He is a very very good boy, isn't he?
Sample Output
    10
    He
    is
    a
    very
    very
    good
    boy
    isn
    t
    he
Explanation
    We consider a token to be a contiguous segment of alphabetic characters.
    There are a total of 10 such tokens in string s, and each token is
    printed in the same order in which it appears in string s.
*/

import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        Scanner scan = new Scanner(System.in);
        scan.useDelimiter("\\Z");
        String s = scan.next().trim();
        if (s.length() > 0) {
            String[] tokens = s.split("[!,?._'@\\s]+");
            System.out.println(tokens.length);
            for(String token : tokens) {
                System.out.println(token);
            }
        } else {
            System.out.println(0);
        }
        scan.close();
    }
}
