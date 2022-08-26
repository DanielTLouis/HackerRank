/*
Objective
  In this challenge, we practice looping over the characters of string. Check
  out the attached tutorial for more details.
Task
  1.First, print each vowel in s on a new line. The English vowels are a, e, i,
  o, and u, and each vowel must be printed in the same order as it appeared in
  s.
  2.Second, print each consonant (i.e., non-vowel) in s on a new line in the
  same order as it appeared in s.
Function Description
  Complete the vowelsAndConsonants function in the editor below.
  vowelsAndConsonants has the following parameters:
    -string s: the string to process
Prints
  -Print each vowel of  in order on a new line, then print each consonant in
  order on a new line. Return nothing.
Input Format
  There is one line of input with the string s.
Output Format
  First, print each vowel in s on a new line (in the same order as they appeared
  in s). Second, print each consonant (i.e., non-vowel) in s on a new line (in
  the same order as they appeared in ).
Sample Input 0
  javascriptloops
Sample Output 0
  a
  a
  i
  o
  o
  j
  v
  s
  c
  r
  p
  t
  l
  p
  s
Explanation 0
  Observe the following:
    -Each letter is printed on a new line.
    -Then the vowels are printed in the same order as they appeared in s.
    -Then the consonants are printed in the same order as they appeared in s.
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

/*
 * Complete the vowelsAndConsonants function.
 * Print your output using 'console.log()'.
 */
function vowelsAndConsonants(s) {
    var bo = true;
    var tempS = s;
    for(let i = 0; i < s.length; i++)
    {
        if(s[i] == "a" || s[i] == "e" || s[i] == "i"
            || s[i]== "o" || s[i] == "u" || s[i] == "A"
            || s[i] == "E" || s[i] == "I" || s[i] == "O"
            || s[i] == "U")
        {
            console.log(s[i]);
        }
    }
      for(let i = 0; i < s.length; i++)
    {
        if(s[i] == "a" || s[i] == "e" || s[i] == "i"
            || s[i]== "o" || s[i] == "u" || s[i] == "A"
            || s[i] == "E" || s[i] == "I" || s[i] == "O"
            || s[i] == "U")
        {
            continue;
        }
        else
        {
            console.log(s[i]);
        }
    }
    /*while(bo)
    {
        bo = false;
        for(let i = 1; i < s.length -1; i++)
        {
            if(tempS[i] > tempS[i+1])
            {
                var temp = tempS[i];
                tempS[i] = tempS[i+1];
                tempS[i+1] = temp;
                bo = true;
                break;
            }
        }
    }*/
    //did not ask for sorted order read instructions!
    /*var sortAlphabets = function(text) {
        return text.split('').sort().join('');
        };
    s = sortAlphabets(s);
    for(let i = 0; i < s.length; i++)
    {
        console.log(s[i]);
    }
    */
}


function main() {
    const s = readLine();

    vowelsAndConsonants(s);
}
