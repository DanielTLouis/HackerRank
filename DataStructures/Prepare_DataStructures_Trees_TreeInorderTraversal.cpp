/*
In this challenge, you are required to implement inorder traversal of a tree.
Complete the inOrder function in your editor below, which has 1 parameter: a
pointer to the root of a binary tree. It must print the values in the tree's
inorder traversal as a single line of space-separated values.
Input Format
  Our hidden tester code passes the root node of a binary tree to your $inOrder*
  function.
Constraints
  1<=NodeInTheTree<=500
Output Format
  Print the tree's inorder traversal as a single line of space-separated values.
Sample Input
     1
      \
       2
        \
         5
        /  \
       3    6
        \
         4
Sample Output
  1 2 3 4 5 6
Explanation
  The tree's inorder traversal results in  1 2 3 4 5 as the required result.
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

/* you only have to complete the function given below.
Node is defined as

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

*/

    void inOrder(Node *root) {
        if(root->left)
        {
            inOrder(root->left);
        }
        std::cout << root->data << " ";
        if(root->right)
        {
            inOrder(root->right);
        }
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

    myTree.inOrder(root);

    return 0;
}
