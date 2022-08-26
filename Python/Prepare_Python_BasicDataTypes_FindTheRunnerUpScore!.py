#Python practice Find the Runner-Up Score!
#prompt:
"""
Given the participants' score sheet for your University Sports Day, you are required to find the runner-up score. You are given  scores. Store them in a list and find the score of the runner-up.

Input Format

The first line contains a. The second line contains an array A[] of n integers each separated by a space.
"""

if __name__ == '__main__':
    n = int(raw_input())
    arr = map(int, raw_input().split())
    
    
    z = max(arr)
    while max(arr) == z:
        arr.remove(max(arr))

    print max(arr)
