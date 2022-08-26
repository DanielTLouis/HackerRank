#Problem
"""
You are given a string, and you have to validate whether it's
a valid Roman numeral. If it is valid, print True. Otherwise,
print False. Try to create a regular expression for a valid
Roman numeral.
Input Format
    A single line of input containing a string of Roman
    characters.
Output Format
    Output a single line containing True or False according to
    the instructions above.
Constraints
    The number will be between 1 and 3999 (both included).
Sample Input
    CDXXI
Sample Output
    True
References
    Regular expressions are a key concept in any programming
    language. A quick explanation with Python examples is
    available here*. You could also go through the link below
    to read more about regular expressions in Python.
https://developers.google.com/edu/python/regular-expressions
* http://www.thelearningpoint.net/computer-science/learning-python-programming-and-data-structures/learning-python-programming-and-data-structures--tutorial-13--regular-expression-matching *
"""

thousand = "(?:(M){0,3})?"
hundred  = "(?:(D?(C){0,3})|(CM)|(CD))?"
ten      = "(?:(L?(X){0,3})|(XC)|(XL))?"
unit     = "(?:(V?(I){0,3})|(IX)|(IV))?"

regex_pattern = r"^" + thousand + hundred + ten + unit + "$"
# Do not delete 'r'.

import re
print(str(bool(re.match(regex_pattern, input()))))
