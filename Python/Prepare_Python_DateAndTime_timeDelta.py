#Problem
"""
When users post an update on social media,such as a URL, image, status update
etc., other users in their network are able to view this new post on their news
feed. Users can also see exactly when the post was published, i.e, how many
hours, minutes or seconds ago.
Since sometimes posts are published and viewed in different time zones, this can
be confusing. You are given two timestamps of one such post that a user can see
on his newsfeed in the following format:
Day dd Mon yyyy hh:mm:ss +xxxx
Here +xxxx represents the time zone. Your task is to print the absolute
difference (in seconds) between them.
Input Format
  The first line contains T, the number of testcases.
  Each testcase contains 2 lines, representing time t1 and time t2.
Constraints
  Input contains only valid timestamps
  year<=3000.
Output Format
  Print the absolute difference (t1-t2) in seconds.
Sample Input 0
  2
  Sun 10 May 2015 13:54:36 -0700
  Sun 10 May 2015 13:54:36 -0000
  Sat 02 May 2015 19:54:36 +0530
  Fri 01 May 2015 13:54:36 -0000
Sample Output 0
  25200
  88200
Explanation 0
  In the first query, when we compare the time in UTC for both the time stamps,
  we see a difference of 7 hours. which is 7X3600 seconds or 25200 seconds.
  Similarly, in the second query, time difference is 5 hours and 30 minutes for
  time zone adjusting for that we have a difference of 1 day and 30 minutes. Or
  24X3600+30X60=88200
"""

#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the time_delta function below.
def time_delta(t1, t2):
    """
    one = t1.split(' ')
    time1 = one[4].split(':')
    seconds1 = int(time1[0]) * 3600 + int(time1[1]) * 60 + int(time1[2]) + int(one[5])
    two = t2.split(' ')
    time2 = two[4].split(':')
    seconds2 = int(time2[0]) * 3600 + int(time2[1]) * 60 + int(time2[2]) + int(two[5])
    #need to subract the time and convert everyting to seconds
    return str(abs(seconds1 - seconds2))
    """
    from datetime import datetime as dt
    fmt = '%a %d %b %Y %H:%M:%S %z'
    return str(int(abs((dt.strptime(t1, fmt) -
                dt.strptime(t2, fmt)).total_seconds())))
if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        t1 = input()

        t2 = input()

        delta = time_delta(t1, t2)

        fptr.write(delta + '\n')

    fptr.close()
