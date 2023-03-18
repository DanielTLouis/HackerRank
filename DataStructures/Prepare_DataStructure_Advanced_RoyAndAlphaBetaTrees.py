"""
Roy has taken a liking to the Binary Search Trees(BST)*. He is interested in knowing the
number of ways an array A of N integers can be arranged to form a BST. Thus, he tries a few
combinations, and notes down the numbers at the odd levels and the numbers at the even levels.
You're given two values, alpha and beta. Can you calculate the sum of Liking of all possible
BST's that can be formed from an array of N integers? Liking of each BST is defined as follows
    (sum of numbers on even levels * alpha) - (sum of numbers on odd levels * beta)
* https://en.wikipedia.org/wiki/Binary_search_tree *
Note
        * The root element is at level 0 ( Even )
        * The elements smaller or equal to the parent element are present in the left subtree,
        elements greater than or equal to the parent element are present in the right subtree.
        Explained here**
        ** https://www.hackerrank.com/contests/w4/challenges/roy-and-alpha-beta-trees/forum/questions/6070 **
    If the answer is no less than 10^9 + 9, output the answer % 10^9 + 9.
    (If the answer is less than 0, keep adding 10^9 + 9 until the value turns non negative.)
Input Format
    The first line of input file contains an integer, T, denoting the number of test cases to
    follow.
    Each testcase comprises of 3 lines.
    The first line contains N, the number of integers.
    The second line contains two space separated integers, alpha and beta.
    The third line contains space separated N integers_, denoting the ith integer in
    array A[i].
Output Format
    Output T lines. Each line contains the answer to its respective test case.
Constraints
    1<=T<=10
    1<=N<=150
    1<=A[i]<10^9
    1<=alpha,beta<=10^9
Sample Input
    4
    1
    1 1
    1
    2
    1 1
    1 2
    3
    1 1
    1 2 3
    5
    1 1
    1 2 3 4 5
Sample Output
    1
    0
    6
    54
Explanation
    There are 4 test cases in total.
       * For the first test case, only 1 BST can be formed with 1 as the root node. Hence the Liking / sum is 1.
       * For the second test case, we get 2 BSTs of the form, the Liking of the first tree is 1*1-2*1=-1 and 2*1-1*1=1, this sums to 0, hence the answer.
            1                  2
             \                /
              2              1
       * For the third test case, we get 5 BSTs. The Liking of each of the BST from left to right are 2,-2,4,2,0 which sums to 6 and hence the answer.
            1            2                 3          3      1
             \          / \               /          /        \
              2        1   3             1          2          3
               \                          \        /          /
                3                          2      1          2
       * Similarly, for the fourth test case, the answer is 54.
"""

# https://www.hackerrank.com/contests/w4/challenges/roy-and-alpha-beta-trees
import sys

MOD = 10 ** 9 + 9
MAX_N = 150
dp = [[None] * MAX_N for _ in range(MAX_N)]

def read_numbers():
    return [int(d) for d in sys.stdin.readline().split()]

def subtree(numbers, start, end):
    """Calculates result for all trees from start to end, inclusive."""
    if start == end:
        return 1, 0, 0
    if dp[start][end] is not None:
        return dp[start][end]
    tree_count = 0
    even_sum = 0
    odd_sum = 0
    for i in range(start, end):
        left_count, left_even_sum, left_odd_sum = subtree(numbers, start, i)
        right_count, right_even_sum, right_odd_sum = subtree(numbers, i + 1, end)
        tree_count = (tree_count + left_count * right_count) % MOD
        even_sum = (even_sum + numbers[i] * left_count * right_count + left_odd_sum * right_count + right_odd_sum * left_count) % MOD
        odd_sum = (odd_sum + left_even_sum * right_count + right_even_sum * left_count) % MOD
    dp[start][end] = (tree_count, even_sum, odd_sum)
    return tree_count, even_sum, odd_sum

def solve(numbers, alpha, beta):
    global dp
    dp = [[None] * MAX_N for _ in range(MAX_N)]
    numbers.sort()
    tree_count, even_sum, odd_sum = subtree(numbers, 0, len(numbers))
    return (alpha * even_sum - beta * odd_sum) % MOD

if __name__ == '__main__':
    T = int(sys.stdin.readline())
    for t in range(T):
        n = int(sys.stdin.readline())
        alpha, beta = read_numbers()
        numbers = read_numbers()
        print(solve(numbers, alpha, beta))
