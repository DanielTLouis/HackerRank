/*
You are given pointer to the root of the binary search tree and two values v1
and v2. You need to return the lowest common ancestor (LCA) of v1 and v2 in the
binary search tree.
  image 
In the diagram above, the lowest common ancestor of the nodes 4 and 6 is the
node 3. Node 3 is the lowest node which has nodes 4 and 6 as descendants.
Function Description
  Complete the function lca in the editor below. It should return a pointer to
  the lowest common ancestor node of the two values given.
  lca has the following parameters:
    - root: a pointer to the root node of a binary search tree
    - v1: a node.data value
    - v2: a node.data value
Input Format
  The first line contains an integer, n, the number of nodes in the tree.
  The second line contains n space-separated integers representing node.data
  values.
  The third line contains two space-separated integers, v1 and v2.
  To use the test data, you will have to create the binary search tree yourself.
  Here on the platform, the tree will be created for you.
Constraints
  1<=n,node.data<=25
  1<=v1,v2<=25
  v1!=v2
  The tree will contain nodes with data equal to v1 and v2.
Output Format
  Return the a pointer to the node that is the lowest common ancestor of v1 and
  v2.
Sample Input
  6
  4 2 3 1 7 6
  1 7
  image
  v1=1 and v2=7.
Sample Output
  [reference to node 4]
Explanation
  LCA of 1 and 7 is 4, the root in this case.
  Return a pointer to the node.
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

    Node *lca(Node *root, int v1,int v2) {
		// Write your code here.
        /*
        def lca(root, v1, v2):
            if root is None:
                return None
            if root.info < v1 and root.info < v2:
                return lca(root.right, v1, v2)
            if root.info > v1 and root.info > v2:
                return lca(root.left, v1, v2)
            return root
        */
        if(!root)
        {
            return nullptr;
        }
        if(root->data < v1 && root->data < v2)
        {
            return lca(root->right, v1, v2);
        }
        if(root->data > v1 && root->data > v2)
        {
            return lca(root->left, v1,v2);
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

  	int v1, v2;
  	std::cin >> v1 >> v2;

    Node *ans = myTree.lca(root, v1, v2);

  	std::cout << ans->data;

    return 0;
}
