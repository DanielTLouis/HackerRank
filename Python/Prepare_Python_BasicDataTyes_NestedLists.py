#Problem:
"""
Given the names and grades for each student in a class of N students, store them in a nested list and print the name(s) of any student(s) having the second lowest grade.

Note: If there are multiple students with the second lowest grade, order their names alphabetically and print each name on a new line.
"""
if __name__ == '__main__':
    d={} #1
    for _ in range(int(raw_input())): #2
        Name=raw_input() #3
        Grade=float(raw_input()) #4
        d[Name]=Grade #5
    v=d.values()#6
    second=sorted(list(set(v)))[1] #7
    second_lowest=[] #8
    for key,value in d.items():  #9
        if value==second: #10
            second_lowest.append(key) #11
    second_lowest.sort() #12
    for name in second_lowest: #13
        print name #14
    
"""
Solution Explained
@1) Empty dictionary.

@2) Range for number of students.

@3) Accepting name of the student.

@4) Accepting the grade of the student.

@5) Assigning name as key and grade as value for the dictionary.

@6) Obtaining the values of dictionary(all grades of students.

@7) Remoing duplicte grades by using set data type , changing it to list, sorting in ascending order and taking the second lowest grade.

@8) Declaring an empty list for storing the name of the students who got the second lowest grade.

@9) Going through the name and grade of each students by using items() method of dictionary.

@10) Checking whether the grade is equal to the second lowest grade.

@11) If yes , append it to the second_lowest list.

@12) bSorting the name of students in asceding order

@13) Going through the name of each students who got the second lowes grade.

@14) Printing each name of students in seperate line.
"""
