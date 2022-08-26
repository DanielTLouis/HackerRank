#!/bin/python
#Task
#   Given an integer, n, perform the following conditional actions:
#       if n is odd, print Wierd
#       if n is even and in the inclusive range of 2 to 5, print Not Weird
#       if n is even and in the inclusive range of 6 to 20, print Weird
#       if n is even and is greater than 20, print Not Weird

import math
import os
import random
import re
import sys



if __name__ == '__main__':
    n = int(raw_input().strip())
    if(n % 2 != 0):
        print("Weird")
    if(n > 20 and n % 2 == 0):
         print("Not Weird")
    if(n >= 2 and n <= 5 and n % 2 == 0):
         print("Not Weird")
    if(n >= 6 and n <= 20 and n % 2 == 0):
        print("Weird")
