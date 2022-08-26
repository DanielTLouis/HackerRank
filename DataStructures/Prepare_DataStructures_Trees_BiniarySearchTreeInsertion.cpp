/*
You are given a pointer to the root of a binary search tree and values to be
inserted into the tree. Insert the values into their appropriate position in the
binary search tree and return the root of the updated binary tree. You just have
to complete the function.
Input Format
  You are given a function,
    Node * insert (Node * root ,int data) {

    }
Constraints
  No. of nodes in the tree <= 500
Output Format
  Return the root of the binary search tree after inserting the value into the
  tree.
Sample Input
        4
       / \
      2   7
     / \
    1   3
  The value to be inserted is 6.
Sample Output
         4
       /   \
      2     7
     / \   /
    1   3 6
*/

#include <iostream>
#include <cstddef>

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

    void preOrder(Node *root) {

          if( root == NULL )
              return;

          std::cout << root->data << " ";

          preOrder(root->left);
          preOrder(root->right);
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



    Node * insert(Node * root, int data) {
        Node* temp = root;
        bool inserted = false;
        if(root)
        {
            while(!inserted)
            {
                if(data <= temp->data)
                {
                    if(temp->left)
                    {
                        temp = temp->left;
                    }
                    else {
                        temp->left = new Node(data);
                        inserted = true;
                    }
                }
                else
                {
                    if(temp->right)
                    {
                        temp = temp->right;
                    }
                    else {
                        temp->right = new Node(data);
                        inserted = true;
                    }
                }
            }
            return root;
        }
        else {
            root = new Node(data);
            return root;
        }

        return root;
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
	myTree.preOrder(root);
    return 0;
}
