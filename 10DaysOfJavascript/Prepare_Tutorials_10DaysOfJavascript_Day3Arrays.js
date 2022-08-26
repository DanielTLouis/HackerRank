/*
Objective
  In this challenge, we learn about Arrays. Check out the attached tutorial for
  more details.
Function Description
  Complete the getSecondLargest function in the editor below.
  getSecondLargest has the following parameters:
    int nums[n]: an array of integers
Returns
  int: the second largest number in nums
Input Format
  The first line contains an integer, n, the size of the nums array.
  The second line contains n space-separated numbers that describe the elements
  in nums.
Constraints
  1<=n<=10
  0<=nums_i<=100, where nums is the number at index .
  The numbers in nums may not be distinct.
Sample Input 0
  5
  2 3 6 6 5
Sample Output 0
  5
Explanation 0
  Given the array nums=[2,3,66,5], we see that the largest value in the array is
  and the second largest value is 5. Thus, we return 5 as our answer.
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

/**
*   Return the second largest number in the array.
*   @param {Number[]} nums - An array of numbers.
*   @return {Number} The second largest number in the array.
**/
function getSecondLargest(nums) {
    // Complete the function
    var largest = 0;
    var secondL = 0;
    for(let i =0; i < nums.length; i++)
    {
        if(nums[i] > largest && nums[i] > secondL)
        {
            if(secondL < largest)
            {
                secondL = largest;
            }
            largest = nums[i];
        }
        else if(nums[i] < largest && nums[i] > secondL)
        {
            secondL = nums[i];
        }

    }
    return secondL;
}


function main() {
    const n = +(readLine());
    const nums = readLine().split(' ').map(Number);

    console.log(getSecondLargest(nums));
}
