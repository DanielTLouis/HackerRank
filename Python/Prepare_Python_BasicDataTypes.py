#problem
"""
The provided code stub will read in a dictionary containing key/value pairs of name:[marks] for a list of students. Print the average of the marks array for the student name provided, showing 2 places after the decimal.
"""
if __name__ == '__main__':
    n = int(raw_input())
    student_marks = {}
    for _ in range(n):
        line = raw_input().split()
        name, scores = line[0], line[1:]
        scores = map(float, scores)
        student_marks[name] = scores
    queryname = raw_input()
    #add the three scores and divide by 3 to get average 
    result = (student_marks[queryname][0]+ student_marks[queryname][1]+student_marks[queryname][2])/3
    #print two decimal places with regex formating 
    print("{:.2f}".format(result))