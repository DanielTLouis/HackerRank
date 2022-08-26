/*Problem*/
/**
Objective
    Today's challenge puts your understanding of nested conditional statements to
    the test. You already have the knowledge to complete this challenge, but
    check out the Tutorial tab for a video on testing.
    * https://www.hackerrank.com/challenges/30-nested-logic/tutorial *
Task
    Your local library needs your help! Given the expected and actual return
    dates for a library book, create a program that calculates the fine (if any).
    The fee structure is as follows:
        1.If the book is returned on or before the expected return date, no fine
        will be charged (i.e.: fine = 0).
        2.If the book is returned after the expected return day but still within
        the same calendar month and year as the expected return date,
        fine = 15 Hackos * (number of days late).
        3.If the book is returned after the expected return month but still
        within the same calendar year as the expected return date, the
        fine = 500 Hackos * (number of months late).
        4.If the book is returned after the calendar year in which it was
        expected, there is a fixed fine of 10000 Hackos.
Example
    d1,m1,y1 =12312024 returned date
    d2,m2,y2 =112015 due date
    The book is returned on time, so no fine is applied.
    d1,m1,y1 =112015 returned date
    d2,m2,y2 =12312014 due date
    The book is returned in the following year, so the fine is a fixed 10000.
Input Format
    The first line contains 3 space-separated integers denoting the respective
    day, month, and year on which the book was actually returned.
    The second line contains 3 space-separated integers denoting the respective
    day, month, and yea on which the book was expected to be returned (due date).
Constraints
    1<=D<=31
    1<=M<=12
    1<=Y<=3000
    it is guaranteed that the dates will be valid Gregorian calendar dates
Output Format
    Print a single integer denoting the library fine for the book received as
    input.
Sample Input
    STDIN       Function
    -----       --------
    9 6 2015    day = 9, month = 6, year = 2015 (date returned)
    6 6 2015    day = 6, month = 6, year = 2015 (date due)
Sample Output
    45
Explanation
    Given the following return dates:
    Returned: D1 = 9, M1 = 6, Y1 = 2015
    Due: D2 = 6, M2 = 6, Y2 = 2015
    Because Y2 == Y1, it is less than a year late.
    Because M2 == M1, it is less than a month late.
    Because D2<D1, it was returned late (but still within the same month and
    year).
    Per the library's fee structure, we know that our fine will be
    15 Hackos * (number of days late). We then print the result of
    15*(D1-D2)=15*(9-6)=45 as our output.
**/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int reDate[3], exDate[3];
    cin >> reDate[0] >> reDate[1] >> reDate[2];
    cin >> exDate[0] >> exDate[1] >> exDate[2];

    //the year has lapsted but may not be a year late yet
    if(reDate[2] > exDate[2])
    {
        //this breaks my year rounding but also is how the problem determina a
        //*year late is by the year rolling over not being 12 months late
        if(reDate[2] > exDate[2])
        {
            cout << 10000;
        }
        //it is the same month or more
        else if(reDate[1] >= exDate[1])
        {
            //exsactly one year late or more
            if(reDate[0] >= exDate[0] && reDate[1] == exDate[1])
            {
                cout << 1000;
            }
            //it is less than a year late by days
            else if(reDate[1] == exDate[1]){
                cout << 500 * (reDate[0] - exDate[0]);
            }
            //more than one year late by months
            else {
                cout << 10000;
            }
        }
        //year lapsted but less than several month late
        else
        {
            //month returned + 12 will give represenation of how long it was
            cout << 500 * ((reDate[1]+12) - exDate[1]);
        }
    }
    //it is within a year
    else {
        //at least one month late
        if(reDate[2] < exDate[2])
        {
            cout << 0;
        }
        else if(reDate[1] > exDate[1] && reDate[0] > exDate[0])
        {
            cout << 500 * (reDate[1] - exDate[1]);
        }
        //should be within a month late
        else if(reDate[0] > exDate[0])
        {
            cout << 15 * (reDate[0] - exDate[0]);
        }
        else
        {
            cout << 0;
        }
    }
    return 0;
}
