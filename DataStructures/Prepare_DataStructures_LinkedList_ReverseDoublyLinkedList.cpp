/*
This challenge is part of a tutorial track by MyCodeSchool
Given the pointer to the head node of a doubly linked list, reverse the order of
the nodes in place. That is, change the next and prev pointers of the nodes so
that the direction of the list is reversed. Return a reference to the head node
of the reversed list.
Note: The head node might be NULL to indicate that the list is empty.
Function Description
  Complete the reverse function in the editor below.
  reverse has the following parameter(s):
    -DoublyLinkedListNode head: a reference to the head of a DoublyLinkedList
Returns
  - DoublyLinkedListNode: a reference to the head of the reversed list
Input Format
  The first line contains an integer t, the number of test cases.
  Each test case is of the following format:
    -The first line contains an integer n, the number of elements in the linked
    list.
    -The next n lines contain an integer each denoting an element of the linked
    list.
Constraints
  1<=t<=10
  0<=n<=1000
  0<=DoublyLinkedList.data<=1000
Output Format
  Return a reference to the head of your reversed list. The provided code will
  print the reverse array as a one line of space-separated integers for each
  test case.
Sample Input
  1
  4
  1
  2
  3
  4
Sample Output
  4 3 2 1
Explanation
  The initial doubly linked list is: 1<->2<->3<->4->NULL
  The reveresed doubly linked list: 4<->3<->2<->1->NULL
*/

#include <bits/stdc++.h>

using namespace std;

class DoublyLinkedListNode {
    public:
        int data;
        DoublyLinkedListNode *next;
        DoublyLinkedListNode *prev;

        DoublyLinkedListNode(int node_data) {
            this->data = node_data;
            this->next = nullptr;
            this->prev = nullptr;
        }
};

class DoublyLinkedList {
    public:
        DoublyLinkedListNode *head;
        DoublyLinkedListNode *tail;

        DoublyLinkedList() {
            this->head = nullptr;
            this->tail = nullptr;
        }

        void insert_node(int node_data) {
            DoublyLinkedListNode* node = new DoublyLinkedListNode(node_data);

            if (!this->head) {
                this->head = node;
            } else {
                this->tail->next = node;
                node->prev = this->tail;
            }

            this->tail = node;
        }
};

void print_doubly_linked_list(DoublyLinkedListNode* node, string sep, ofstream& fout) {
    while (node) {
        fout << node->data;

        node = node->next;

        if (node) {
            fout << sep;
        }
    }
}

void free_doubly_linked_list(DoublyLinkedListNode* node) {
    while (node) {
        DoublyLinkedListNode* temp = node;
        node = node->next;

        free(temp);
    }
}

/*
 * Complete the 'reverse' function below.
 *
 * The function is expected to return an INTEGER_DOUBLY_LINKED_LIST.
 * The function accepts INTEGER_DOUBLY_LINKED_LIST llist as parameter.
 */

/*
 * For your reference:
 *
 * DoublyLinkedListNode {
 *     int data;
 *     DoublyLinkedListNode* next;
 *     DoublyLinkedListNode* prev;
 * };
 *
 */

DoublyLinkedListNode* reverse(DoublyLinkedListNode* llist) {
    while(llist->next)
    {
        llist=llist->next;
    }
    DoublyLinkedListNode* newHead = new DoublyLinkedListNode(llist->data);
    DoublyLinkedListNode* temp = newHead;
    llist = llist->prev;
    while(llist)
    {
        newHead->next = new DoublyLinkedListNode(llist->data);
        newHead = newHead->next;
        llist = llist->prev;
    }
    return temp;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        DoublyLinkedList* llist = new DoublyLinkedList();

        int llist_count;
        cin >> llist_count;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < llist_count; i++) {
            int llist_item;
            cin >> llist_item;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            llist->insert_node(llist_item);
        }

        DoublyLinkedListNode* llist1 = reverse(llist->head);

        print_doubly_linked_list(llist1, " ", fout);
        fout << "\n";

        free_doubly_linked_list(llist1);
    }

    fout.close();

    return 0;
}
