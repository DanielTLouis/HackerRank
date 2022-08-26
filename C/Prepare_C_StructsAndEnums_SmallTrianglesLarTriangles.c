/*
You are given n triangles, specifically, their sides a, b and c. Print them in
the same style but sorted by their areas from the smallest one to the largest
one. It is guaranteed that all the areas are different.
The best way to calculate a area of a triangle with sides a, b and c is Heron's
formula:
S=squrt(p(p-a)(p-b)(p-c)) where p=(a+b+c)/2.0.
Input Format
  The first line of each test file contains a single integer n. n lines follow
  with three space-separated integers, a-i, b_i and c_i.
Constraints
  1<=n<=100
  1<=a_i,b_i,c_i<=70
  a_i+b_i>c_i,a_i+c_i>b_i, and b_i+c_i>a_i
Output Format
  Print exactly n lines. On each line print 3 space-separated integers, the a_i,
  b_i and c_i of the corresponding triangle.
Sample Input 0
  3
  7 24 25
  5 12 13
  3 4 5
Sample Output 0
  3 4 5
  5 12 13
  7 24 25
Explanation 0
  The square of the first triangle is 84. The square of the second triangle is
  30. The square of the third triangle is 6. So the sorted order is the reverse
  one.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
	int a;
	int b;
	int c;
};

typedef struct triangle triangle;

void sort_by_area(triangle* tr, int n) {
	/**
	* Sort an array a of the length n
	*/

    int i = 0;
    while(i < n-1)
    {
        //need to case to floating point or you will have integer division.
        double p1 = (tr[i].a + tr[i].b + tr[i].c) / 2.0;
        //sqrt didn't work with this but worked without sqrt
        //double area1 = sqrt(p1*(p1-tr[i].a)*(p1-tr[i].b)*(p1-tr[i].c));
        double area1 = p1*(p1-tr[i].a)*(p1-tr[i].b)*(p1-tr[i].c);
        double p2 = (tr[i+1].a + tr[i+1].b + tr[i+1].c) / 2.0;
        //double area2 = sqrt(p2*(p2-tr[i+1].a)*(p2-tr[i+1].b)*(p2-tr[i+1].c));
        double area2 = p2*(p2-tr[i+1].a)*(p2-tr[i+1].b)*(p2-tr[i+1].c);
        if(area1 > area2)
        {
            triangle temp = tr[i];
            tr[i] = tr[i+1];
            tr[i+1] = temp;
            i = 0;
            continue;
        }
        i++;
    }
}

int main()
{
	int n;
	scanf("%d", &n);
	triangle *tr = malloc(n * sizeof(triangle));
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
	}
	sort_by_area(tr, n);
	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
	}
	return 0;
}
