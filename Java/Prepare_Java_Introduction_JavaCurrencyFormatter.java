/*
Given a double-precision number, , denoting an amount of money, use the
NumberFormat class' getCurrencyInstance method to convert  into the US,
Indian, Chinese, and French currency formats. Then print the formatted
values as follows:
    US: formattedPayment
    India: formattedPayment
    China: formattedPayment
    France: formattedPayment
where formanttedPayment is payment formatted according to the appropriate
Locale's currency.
Note: India does not have a built-in Locale, so you must construct one where
the language is en (i.e., English).
Input Format
    A single double-precision number denoting payment.
Constraints
    0<=payemnt<=10^9
Output Format
    On the first line, print US: u where u is payment formatted for US
    currency.
    On the second line, print India: i where i is payment formatted for
    Indian currency.
    On the third line, print China: c where c is payment formatted for
    Chinese currency.
    On the fourth line, print France: f, where f is payment formatted for
    French currency.
Sample Input
    12324.134
Sample Output
    US: $12,324.13
    India: Rs.12,324.13
    China: ￥12,324.13
    France: 12 324,13 €
Explanation
    Each line contains the value of payment formatted according to the four
    countries' respective currencies.
*/

import java.util.*;
import java.text.*;

public class Solution {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        double payment = scanner.nextDouble();
        scanner.close();

        // Write your code here.
        /* Create custom Locale for India.
        I used the "IANA Language Subtag Registry" to find India's country code */
        Locale indiaLocale = new Locale("en", "IN");

        /* Create NumberFormats using Locales */
        NumberFormat us     = NumberFormat.getCurrencyInstance(Locale.US);
        NumberFormat india  = NumberFormat.getCurrencyInstance(indiaLocale);
        NumberFormat china  = NumberFormat.getCurrencyInstance(Locale.CHINA);
        NumberFormat france = NumberFormat.getCurrencyInstance(Locale.FRANCE);

        System.out.println("US: " + us.format(payment));
        System.out.println("India: " + india.format(payment));
        System.out.println("China: " + china.format(payment));
        System.out.println("France: " + france.format(payment));
    }
}
