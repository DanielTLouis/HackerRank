/*
Given a pointer to the root of a binary tree, you need to print the level order
traversal of this tree. In level-order traversal, nodes are visited level by
level from left to right. Complete the function levelOrder and print the values
in a single line separated by a space.
For example:
     1
      \
       2
        \
         5
        /  \
       3    6
        \
         4
  For the above tree, the level order traversal is 1->2->5->3->6->4.
Input Format
  You are given a function,
    void levelOrder(Node * root) {

    }
Constraints
  1<=Nodes in the tree<=500
Output Format
  Print the values in a single line separated by a space.
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
  1 2 5 3 6 4
Explanation
  We need to print the nodes level by level. We process each level from left to
  right. 
  Level Order Traversal: 1->2->5->3->6->4.
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
/*
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

    void levelOrder(Node * root) {
        /*
        queue = []
        queue.append(root)
        while(len(queue)>0):
            node = queue.pop(0)
            print node.data,
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
        */
        queue<Node*> q;
        q.push(root);
        while(q.size() > 0)
        {
            Node* temp = q.front();
            q.pop();
            cout << temp->data << " ";
            if(temp->left)
            {
                q.push(temp->left);
            }
            if(temp->right)
            {
                q.push(temp->right);
            }
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

	myTree.levelOrder(root);
    return 0;
}
