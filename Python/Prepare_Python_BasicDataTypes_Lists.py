"""
Consider a list (list = []). You can perform the following commands:

1.insert i e: Insert integer e at position i.
2.print: Print the list.
3.remove e: Delete the first occurrence of integer e.
4.append e: Insert integer e at the end of the list.
5.sort: Sort the list.
6.pop: Pop the last element from the list.
7.reverse: Reverse the list.
Initialize your list and read in the value of n followed by n lines of commands where each command will be of the 7 types listed above. Iterate through each command in order and perform the corresponding operation on your list.
"""

if __name__ == '__main__':
    N = int(raw_input())
    list = []
    for i in range(0, N):
        tempCommand = raw_input()
        tempCommand = tempCommand.split(" ")
        if tempCommand[0] == "insert":
            list.insert(int(tempCommand[1]), int(tempCommand[2]))
        if tempCommand[0] == "print":
            print(list)
        if tempCommand[0] == "append":
            list.append(int(tempCommand[1]))
        if tempCommand[0] == "remove":
            list.remove(int(tempCommand[1]))
        if tempCommand[0] == "sort":
            list.sort()
        if tempCommand[0] == "reverse":
            list.reverse()
        if tempCommand[0] == "pop":
            list.pop()
