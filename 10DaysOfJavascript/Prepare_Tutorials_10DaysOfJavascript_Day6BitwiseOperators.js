/*
Objective
    Today, we're practicing bitwise operations. Check the attached tutorial 
    for more details.

Task
    We define S to be a sequence of distinct sequential integers 
    from 1 to n; in other words, S={1,2,3,...,n}. We want to know 
    the maximum bitwise AND value of any two integers, a and b (
    where a<b), in sequence S that is also less than a given 
    integer, k.
    Complete the function in the editor so that given n and k, it 
    returns the maximum a&b<k.
    Note: The & symbol represents the bitwise AND operator.
Input Format
    The first line contains an integer, q, denoting the number of 
    function calls.
    Each of the q subsequent lines defines a dataset for a 
    function call in the form of two space-separated integers 
    describing the respective values of n and k.
Constraints
    1<=q<=10^3
    2<=n<=10^3
    2<=k<=n
Output Format
    Return the maximum possible value of a&b<k for any a<b in 
    sequence S.
Sample Input 0
    3
    5 2
    8 5
    2 2
Sample Output 0
    1
    4
    0
Explanation 0
    We perform the following q=3 function calls:
    1.When n=5 and k=2, we have the following possible a and b 
    values in set S={1,2,3,4,5}:
        a b  a&b
        1 2  001&010=(000)_2=(0)_10
        1 3  001&011=(00)1_2=(1)_10
        .
        .
        .
        4 5  100&101=(100)_2=(4)_10
    The maximum of any a&b that is also <k is 1, so we return 1.
    2.When n=8 and k=5, the maximum of any a&b<k in set 
    S={1,2,3,4,5,6,7,8|} is 4 (see table above), so we return 4.
    3.When n=2 and k=2, the maximum of any a&b<k in set S={1,2} 
    is 0 (see table above), so we return 0.
Sample Input 1
    2
    9 2
    8 3
Sample Output 1
    1
    2
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
function getMaxLessThanK(n,k)
{
    k = Number(k);
    n = Number(n);
    var l = 0; 
    for(let i = 1; i <= n; i++)
    {
        for(let j = 1; j < i; j++)
        {
            var bi = j&i;
            if(bi < k && bi >= l)
            {
                l = j&i;
            }
        }
    }
    return l;
}

function main() {
    const q = +(readLine());
    
    for (let i = 0; i < q; i++) {
        const [n, k] = readLine().split(' ').map(Number);
        
        console.log(getMaxLessThanK(n, k));
    }
}