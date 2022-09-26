"""
There are a number of people who will be attending
ACM-ICPC World Finals*. Each of them may be well versed in a number
of topics. Given a list of topics known by each attendee, presented
as binary strings, determine the maximum number of topics a 2-person
team can know. Each subject has a column in the binary string, and a
'1' means the subject is known while '0' means it is not. Also
determine the number of teams that know the maximum number of
topics. Return an integer array with two elements. The first is the
maximum number of topics known, and the second is the number of
teams that know that number of topics.
* https://en.wikipedia.org/wiki/ACM_International_Collegiate_Programming_Contest *
Example
    n=3
    topics=['10101','11110','00010']
    The attendee data is aligned for clarity below:
        10101
        11110
        00010
    These are all possible teams that can be formed:
        Members Subjects
        (1,2)   [1,2,3,4,5]
        (1,3)   [1,3,4,5]
        (2,3)   [1,2,3,4]
    In this case, the first team will know all 5 subjects. They are
    the only team that can be created that knows that many subjects,
    so [5,1] is returned.
Function Description
    Complete the acmTeam function in the editor below.
    acmTeam has the following parameter(s):
        string topic: a string of binary digits
Returns
    int[2]: the maximum topics and the number of teams that know
    that many topics
Input Format
    The first line contains two space-separated integers n and m,
    where n is the number of attendees and m is the number of topics.
    Each of the next n lines contains a binary string of length m.
Constraints
    2<=n<=500
    1<=m<=500
Sample Input
    4 5
    10101
    11100
    11010
    00101
Sample Output
    5
    2
Explanation
    Calculating topics known for all permutations of 2 attendees we
    get:
        (1,2)->4
        (1,3)->5
        (1,4)->3
        (2,3)->4
        (2,4)->5
        (3,4)->5
    The 2 teams (1, 3) and (3, 4) know all 5 topics which is maximal.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'acmTeam' function below.
#
# The function is expected to return an INTEGER_ARRAY.
# The function accepts STRING_ARRAY topic as parameter.
#
def sortTeams( teams):
    i = 0
    while(i != len(teams) -1):
        if(teams[i][1] < teams[i+1][1] ):
            temp = teams[i]
            teams[i] = teams[i+1]
            teams[i+1] = temp
            i = 0
            continue
        i += 1
def acmTeam(topic):
    # Write your code here
    lista = []
    for i in range(len(topic)):
        for j in range(i, len(topic)):
            x = str(int(topic[i])+int(topic[j]))
            #two elements are added and converted into string and stored in a var
            lista.append(x.count("1")+x.count("2"))
    maxi = max(lista)
    return [maxi,lista.count(maxi)]
    """
    #way to slow
    teams = []
    for i in range(0, len(topic)):
        known = 0
        for j in range(i, len(topic)):
            known = 0
            if(i == j):
                continue
            for k in range(0, len(topic[i])):
                if(topic[i][k] == '1' or topic[j][k] == '1'):
                    known += 1
            team = [i+1,j+1]
            teams.append([team, known])
    sortTeams(teams)
    most = teams[0][1]
    many = 0
    for i in teams:
        if(i[1] == most):
            many+=1
        if(i[1] < most):
            break
    return [most, many]
    """

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    m = int(first_multiple_input[1])

    topic = []

    for _ in range(n):
        topic_item = input()
        topic.append(topic_item)

    result = acmTeam(topic)

    fptr.write('\n'.join(map(str, result)))
    fptr.write('\n')

    fptr.close()
