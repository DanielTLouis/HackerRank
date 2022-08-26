/*
Given a reference to the head of a doubly-linked list and an integer, data,
create a new DoublyLinkedListNode object having data value value and insert it
at the proper location to maintain the sort.
Example
  head refers to the list 1<->2<->4->NULL
  data=3
  Return a reference to the new list: 1<->2<->3<->4->NULL.
Function Description
  Complete the sortedInsert function in the editor below.
  sortedInsert has two parameters:
    -DoublyLinkedListNode pointer head: a reference to the head of a
    doubly-linked list
    -int data: An integer denoting the value of the data field for the
    DoublyLinkedListNode you must insert into the list.
Returns
  DoublyLinkedListNode pointer: a reference to the head of the list
  Note: Recall that an empty list (i.e., where head=NULL) and a list with one
  element are sorted lists.
Input Format
  The first line contains an integer t, the number of test cases.
    -Each of the test case is in the following format:
    -The first line contains an integer n, the number of elements in the linked
    list.
    -Each of the next n lines contains an integer, the data for each node of the
    linked list.
    -The last line contains an integer, data, which needs to be inserted into
    the sorted doubly-linked list.
Constraints
  1<=t<=10
  1<=n<=1000
  1<=DoublyLinkedListNode.data<=1000
Sample Input
  STDIN   Function
  -----   --------
  1       t = 1
  4       n = 4
  1       node data values = 1, 3, 4, 10
  3
  4
  10
  5       data = 5
Sample Output
  1 3 4 5 10
Explanation
  The initial doubly linked list is:  1<->3<->4<->10->NULL.
  The doubly linked list after insertion is: 1<->3<->4<->5<->10->NULL
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
 * Complete the 'sortedInsert' function below.
 *
 * The function is expected to return an INTEGER_DOUBLY_LINKED_LIST.
 * The function accepts following parameters:
 *  1. INTEGER_DOUBLY_LINKED_LIST llist
 *  2. INTEGER data
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

DoublyLinkedListNode* sortedInsert(DoublyLinkedListNode* llist, int data) {
    DoublyLinkedListNode* head = llist;
    if(data < llist->data)//new head
    {
        DoublyLinkedListNode* newHead = new DoublyLinkedListNode(data);
        newHead->next = head;
        return newHead;
    }
    while(head->next)
    {
        if(head->next->data > data)//found the place
        {
            DoublyLinkedListNode* hold = head->next;
            head->next = new DoublyLinkedListNode(data);
            cout << head->next->data;
            head->next->next = hold;
            return llist;
        }
        head = head->next;
    }
    head->next = new DoublyLinkedListNode(data);//new tail
    return llist;
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

        int data;
        cin >> data;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        DoublyLinkedListNode* llist1 = sortedInsert(llist->head, data);

        print_doubly_linked_list(llist1, " ", fout);
        fout << "\n";

        free_doubly_linked_list(llist1);
    }

    fout.close();

    return 0;
}
