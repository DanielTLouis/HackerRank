/*
Objective
  In this challenge, we practice using arrow functions. Check the attached
  tutorial for more details.
Task
  Complete the function in the editor. It has one parameter: an array, nums. It
  must iterate through the array performing one of the following actions on each
  element:
    If the element is even, multiply the element by 2.
    If the element is odd, multiply the element by 3.
    The function must then return the modified array.
Input Format
  The first line contains an integer, n, denoting the size of nums.
  The second line contains n space-separated integers describing the respective
  elements of nums.
Constraints
  1<=n<=10
  1<=nums_i<=100, where nums_i is the ith element of nums.
Output Format
  Return the modified array where every even element is doubled and every odd
  element is tripled.
Sample Input 0
  5
  1 2 3 4 5
Sample Output 0
  3 4 9 8 15
Explanation 0
  Given nums=[1,2,3,4,5], we modify each element so that all even elements are
  multiplied by 2 and all odd elements are multipled by 3. In other words,
  [1,2,3,4,5]=>[1*3,2*2,3*3,4*2,5*3]. We then return the modified array as our
  answer.
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
 * Modify and return the array so that all even elements are doubled and all odd elements are tripled.
 *
 * Parameter(s):
 * nums: An array of numbers.
 */
function modifyArray(nums) {
    for(let i = 0; i < nums.length; i++)
    {
        if(nums[i] % 2 == 0)
        {
            nums[i] *= 2;
        }
        else
        {
            nums[i] *= 3;
        }
    }
    return nums;
}


function main() {
    const n = +(readLine());
    const a = readLine().split(' ').map(Number);

    console.log(modifyArray(a).toString().split(',').join(' '));
}
