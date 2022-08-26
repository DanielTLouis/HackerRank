/*
This challenge is part of a tutorial track by MyCodeSchool and is accompanied by
a video lesson.
Given a pointer to the head of a linked list, insert a new node before the head.
The next value in the new node should point to head and the data value should be
replaced with a given value. Return a reference to the new head of the list. The
head pointer given may be null meaning that the initial list is empty.
Function Description
  Complete the function insertNodeAtHead in the editor below.
  insertNodeAtHead has the following parameter(s):
    -SinglyLinkedListNode llist: a reference to the head of a list
    -data: the value to insert in the data field of the new node
Input Format
  The first line contains an integer n, the number of elements to be inserted at
  the head of the list.
  The next n lines contain an integer each, the elements to be inserted, one per
  function call.
Constraints
  1<=n<=1000
  1<=list[i]<=1000
Sample Input
  5
  383
  484
  392
  975
  321
Sample Output
  321
  975
  392
  484
  383
Explanation
  Intially the list in NULL. After inserting 383, the list is 383 -> NULL.
  After inserting 484, the list is 484 -> 383 -> NULL.
  After inserting 392, the list is 392 -> 484 -> 383 -> NULL.
  After inserting 975, the list is 975 -> 392 -> 484 -> 383 -> NULL.
  After inserting 321, the list is 321 -> 975 -> 392 -> 484 -> 383 -> NULL.
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

// Complete the insertNodeAtHead function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* insertNodeAtHead(SinglyLinkedListNode* llist, int data) {
	SinglyLinkedListNode* temp = llist;
    llist = new SinglyLinkedListNode(data);
    llist->next = temp;
    return llist;


}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    SinglyLinkedList* llist = new SinglyLinkedList();

    int llist_count;
    cin >> llist_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    for (int i = 0; i < llist_count; i++) {
        int llist_item;
        cin >> llist_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    	SinglyLinkedListNode* llist_head = insertNodeAtHead(llist->head, llist_item);
      	llist->head = llist_head;
    }


    print_singly_linked_list(llist->head, "\n", fout);
    fout << "\n";

    free_singly_linked_list(llist->head);

    fout.close();

    return 0;
}
