/*
This challenge is part of a MyCodeSchool tutorial track and is accompanied by a
video lesson.
This is an to practice traversing a linked list. Given a pointer to the head node
of a linked list, print each node's data element, one per line. If the head
pointer is null (indicating the list is empty), there is nothing to print.
Function Description
  Complete the printLinkedList function in the editor below.
  printLinkedList has the following parameter(s):
    -SinglyLinkedListNode head: a reference to the head of the list
Print
  For each node, print its data value on a new line (console.log in Javascript).
Input Format
  The first line of input contains n, the number of elements in the linked list.
  The next n lines contain one element each, the data values for each node.
  Note: Do not read any input from stdin/console. Complete the printLinkedList
  function in the editor below.
Constraints
  1<=n<=1000
  1<=list[i]<=1000, where list[i] is the ith element of the linked list.
Sample Input
  2
  16
  13
Sample Output
  16
  13
Explanation
  There are two elements in the linked list. They are represented as
  16 -> 13 -> NULL. So, the printLinkedList function should print 16 and 13 each
  on a new line.
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

void free_singly_linked_list(SinglyLinkedListNode* node) {
    while (node) {
        SinglyLinkedListNode* temp = node;
        node = node->next;

        free(temp);
    }
}

// Complete the printLinkedList function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
void printLinkedList(SinglyLinkedListNode* head) {
    SinglyLinkedListNode* temp = head;
    while(temp)
    {
        cout << temp->data << endl;
        temp = temp->next;
    }
    return;
}

int main()
{
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

    printLinkedList(llist->head);

    return 0;
}
