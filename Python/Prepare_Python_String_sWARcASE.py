##Problem
"""
You are given a string and your task is to swap cases. In other words, convert all lowercase letters to uppercase letters and vice versa.

For Example:

Www.HackerRank.com → wWW.hACKERrANK.COM
Pythonist 2 → pYTHONIST 2  

"""

def swap_case(s):
    temp = ""
    for i in range(0, len(s)):
        if s[i].isupper():
            temp += s[i].lower() 
        else :
            temp += s[i].upper()
        
    return temp

if __name__ == '__main__':
    s = raw_input()
    result = swap_case(s)
    print result
