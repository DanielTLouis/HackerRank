/*
A palindrome is a word, phrase, number, or other sequence of characters which reads the same backward or forward.
Given a string A, print Yes if it is a palindrome, print No otherwise.
Constraints
    A will consist at most 50 lower case english letters.
Sample Input
    madam
Sample Output
    Yes
*/
import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        Scanner sc = new Scanner(System.in);
        String s = sc.next();
        String rs = "";
        for(int i = s.length()-1; i >= 0; i--)
        {
            rs += s.charAt(i);
        }
        boolean c = true;
        for(int i = s.length()-1; i >= 0; i--)
        {
            if(rs.charAt(i) != s.charAt(i))
            {
                c = false;
            }
        }
        if(c)
        {
            System.out.println("Yes");
        }
        else
        {
            System.out.println("No");
        }
    }
}
