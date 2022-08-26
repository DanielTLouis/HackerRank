/*
Objective
  In this challenge, we learn about if-else statements. Check out the attached
  tutorial for more details.
Task
  Complete the getGrade(score) function in the editor. It has one parameter: an
  integer, score, denoting the number of points Julia earned on an exam. It must
  return the letter corresponding to her  according to the following rules:
    If 25<score<=30, then grade=A.
    If 20<score<=25, then grade=B.
    If 15<score<=20, then grade=C.
    If 10<score<=15, then grade=D.
    If 5<score<=10, then grade=E.
    If 0<=score<=5, then grade=F.
Input Format
  Stub code in the editor reads a single integer denoting score from stdin and
  passes it to the function.
Constraints
  0<=score<=30
Output Format
  The function must return the value of grade (i.e., the letter grade) that
  Julia earned on the exam.
Sample Input 0
  11
Sample Output 0
  D
Explanation 0
  Because score=11, it satisfies the condition 10<score<15(which corresponds to
  D). Thus, we return D as our answer.
*/

'use strict';

process.stdin.resume();
process.stdin.setEncoding('utf-8');

let inputString = '';
let currentLine = 0;

process.stdin.on('data', inputStdin => {
    inputString += inputStdin;
});

process.stdin.on('end', _ => {
    inputString = inputString.trim().split('\n').map(string => {
        return string.trim();
    });

    main();
});

function readLine() {
    return inputString[currentLine++];
}

function getGrade(score) {
    let grade;
    // Write your code here
    if(score > 25 && score <= 30)
    {
        grade = "A";
    }
    else if(score > 20 && score <= 25)
    {
        grade = "B";
    }
    else if(score > 15 && score <= 20)
    {
        grade = "C";
    }
    else if(score > 10 && score <= 15)
    {
        grade = "D";
    }
    else if(score > 5 && score <= 10)
    {
        grade = "E";
    }
    else
    {
        grade = "F";
    }
    return grade;
}


function main() {
    const score = +(readLine());

    console.log(getGrade(score));
}
