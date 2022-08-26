/*
This challenge is part of a tutorial track by MyCodeSchool
Given a pointer to the head of a linked list and a specific position, determine
the data value at that position. Count backwards from the tail node. The tail is
at postion 0, its parent is at 1 and so on.
Example
  head refers to 3->2->1->0->NULL
  positionFromTail=2
Each of the data values matches its distance from the tail. The value  is at the
desired position.
Function Description
  Complete the getNode function in the editor below.
  getNode has the following parameters:
    SinglyLinkedListNode pointer head: refers to the head of the list
    int positionFromTail: the item to retrieve
Returns
  int: the value at the desired position
Input Format
  The first line contains an integer t, the number of test cases.
  Each test case has the following format:
  The first line contains an integer n, the number of elements in the linked
  list.
  The next n lines contains an integer, the data value for an element of the
  linked list.
  The last line contains an integer positionFromTail, the position from the tail
  to retrieve the value of.
Constraints
  1<=t<=10
  1<=n,m<=1000
  1<=list[i]<=1000, where list[i] is the ith element of the linked list.
  0<=positionFromTail<n
Sample Input
  2
  1
  1
  0
  3
  3
  2
  1
  2
Sample Output
  1
  3
Explanation
  In the first case, there is one element in linked list with a value of 1. The last (only) element contains 1.
  In the second case, the list is 3->2->1->NULL. The element with position of 2 from tail contains 3.
*/

#include <bits/stdc++.h>

using namespace std;

class SinglyLinkedListNode {
    public:
        int data;
        SinglyLinkedListNode *next;

        SinglyLinkedListNode(int node_data) {
            this->data = node_data;
            this->next = nullptr;
        }
};

class SinglyLinkedList {
    public:
        SinglyLinkedListNode *head;
        SinglyLinkedListNode *tail;

        SinglyLinkedList() {
            this->head = nullptr;
            this->tail = nullptr;
        }

        void insert_node(int node_data) {
            SinglyLinkedListNode* node = new SinglyLinkedListNode(node_data);

            if (!this->head) {
                this->head = node;
            } else {
                this->tail->next = node;
            }

            this->tail = node;
        }
};

void print_singly_linked_list(SinglyLinkedListNode* node, string sep, ofstream& fout) {
    while (node) {
        fout << node->data;

        node = node->next;

        if (node) {
            fout << sep;
        }
    }
}

void free_singly_linked_list(SinglyLinkedListNode* node) {
    while (node) {
        SinglyLinkedListNode* temp = node;
        node = node->next;

        free(temp);
    }
}

/*
 * Complete the 'getNode' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_SINGLY_LINKED_LIST llist
 *  2. INTEGER positionFromTail
 */

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */

int getNode(SinglyLinkedListNode* llist, int positionFromTail) {
    vector<int> ar;
    while(llist)
    {
        ar.push_back(llist->data);
        llist = llist->next;
    }
    return ar[ar.size() - positionFromTail-1];
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int tests;
    cin >> tests;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int tests_itr = 0; tests_itr < tests; tests_itr++) {
        SinglyLinkedList* llist = new SinglyLinkedList();

        int llist_count;
        cin >> llist_count;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < llist_count; i++) {
            int llist_item;
            cin >> llist_item;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            llist->insert_node(llist_item);
        }

        int position;
        cin >> position;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int result = getNode(llist->head, position);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
