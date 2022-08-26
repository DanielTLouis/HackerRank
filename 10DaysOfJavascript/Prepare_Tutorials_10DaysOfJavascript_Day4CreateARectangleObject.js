/*
Objective
    In this challenge, we practice creating objects. Check out the attached
    tutorial for more details.
Task
    Complete the function in the editor. It has two parameters: a and b. It must 
    return an object modeling a rectangle that has the following properties:
        length: This value is equal to a.
        width: This value is equal to b.
        perimeter: This value is equal to 2*(a+b)
        area: This value is equal to a*b
    Note: The names of the object's properties must be spelled correctly to pass 
    this challenge.
Input Format
    The first line contains an integer denoting a.
    The second line contains an integer denoting b.
Constraints
    1<=a,b<=100
Output Format
    Return a object that has the properties specified above. Locked code in the 
    editor prints the returned object's length, width, perimeter, and area to 
    STDOUT.
Sample Input 0
    4
    5
Sample Output 0
    4
    5
    18
    20
Explanation 0
    Given a length of a=4 and a width of b=5, the Rectangle object's perimeter is 
    4+4+5+5=18 and its area is 4*5=20.
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

class Rectagle
{
    constructor(l,w)
    {
        this.length = l;
        this.width = w;
        this.area = l*w;
        this.perimeter = 2*(l+w);
    }
    /*
    area()
    {
        return this.length * this.width;
    }
    perimeter()
    {
        return 2 * (this.length + this.width);
    }
    */
}
/*
 * Complete the Rectangle function
 */
function Rectangle(a, b) 
{
    return new Rectagle(a,b);
}


function main() {
    const a = +(readLine());
    const b = +(readLine());
    
    const rec = new Rectangle(a, b);
    
    console.log(rec.length);
    console.log(rec.width);
    console.log(rec.perimeter);
    console.log(rec.area);
}