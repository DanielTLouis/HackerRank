/*
The height of a binary tree is the number of edges between the tree's root and
its furthest leaf. For example, the following binary tree is of height 2:
  image
Function Description
  Complete the getHeight or height function in the editor. It must return the
  height of a binary tree as an integer.
  getHeight or height has the following parameter(s):
    -root: a reference to the root of a binary tree.
  Note -The Height of binary tree with single node is taken as zero.
Input Format
  The first line contains an integer n, the number of nodes in the tree.
  Next line contains n space separated integer where ith integer denotes
  node[i].data.
  Note: Node values are inserted into a binary search tree before a reference to
  the tree's root node is passed to your function. In a binary search tree, all
  nodes on the left branch of a node are less than the node value. All values on
  the right branch are greater than the node value.
Constraints
  1<=node.data[i]<=20
  1<=n<=20
Output Format
  Your function should return a single integer denoting the height of the binary
  tree.
Sample Input
  image
Sample Output
  3
Explanation
  The longest root-to-leaf path is shown below:
    image
  There are 4 nodes in this path that are connected by 3 edges, meaning our
  binary tree's height=3.
*/

#include <bits/stdc++.h>

using namespace std;

class Node {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};

class Solution {
    public:
  		Node* insert(Node* root, int data) {
            if(root == NULL) {
                return new Node(data);
            } else {
                Node* cur;
                if(data <= root->data) {
                    cur = insert(root->left, data);
                    root->left = cur;
                } else {
                    cur = insert(root->right, data);
                    root->right = cur;
               }

               return root;
           }
        }
/*The tree node has data, left child and right child
class Node {
    int data;
    Node* left;
    Node* right;
};

*/
    void traverse(Node* root, int cur, int* maxh)
    {
        if(root->left)
        {
            cur += 1;
            if(*maxh < cur)
            {
                *maxh = cur;
            }
            traverse(root->left, cur, maxh);
            cur -= 1;
        }
        if(root->right)
        {
            cur+=1;
            if(*maxh < cur)
            {
                *maxh = cur;
            }
            traverse(root->right, cur, maxh);
            cur -= 1;
        }
        return;
    }
    int height(Node* root) {
        // Write your code here.
        int maxHieght = 0, currentHieght=0;
        traverse(root, currentHieght, &maxHieght);
        return maxHieght;

    }

}; //End of Solution

int main() {

    Solution myTree;
    Node* root = NULL;

    int t;
    int data;

    std::cin >> t;

    while(t-- > 0) {
        std::cin >> data;
        root = myTree.insert(root, data);
    }

    int height = myTree.height(root);

  	std::cout << height;

    return 0;
}
