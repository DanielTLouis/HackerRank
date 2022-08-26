/*
This challenge is part of a tutorial track by MyCodeSchool and is accompanied by
a video lesson.
Delete the node at a given position in a linked list and return a reference to
the head node. The head is at position 0. The list may be empty after you delete
the node. In that case, return a null value.
Example
  llist=0->1->2->3
  position=2
  After removing the node at position 2, llist'=0->1->3.
Function Description
  Complete the deleteNode function in the editor below.
  deleteNode has the following parameters:
    - SinglyLinkedListNode pointer llist: a reference to the head node in the
    list
    - int position: the position of the node to remove
Returns
  - SinglyLinkedListNode pointer: a reference to the head of the modified list
Input Format
  The first line of input contains an integer n, the number of elements in the
  linked list.
  Each of the next n lines contains an integer, the node data values in order.
  The last line contains an integer, position, the position of the node to
  delete.
Constraints
  1<=n<=1000
  1<=list[i]<=1000, where list[i] is the ith element of the linked list.
Sample Input
  8
  20
  6
  2
  19
  7
  4
  15
  9
  3
Sample Output
  20 6 2 7 4 15 9
Explanation
  The original list is 20->6->2->19->7->4->15->9. After deleting the node at
  position 3, the list is  20->6->2->7->4->15->9.
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
 * Complete the 'deleteNode' function below.
 *
 * The function is expected to return an INTEGER_SINGLY_LINKED_LIST.
 * The function accepts following parameters:
 *  1. INTEGER_SINGLY_LINKED_LIST llist
 *  2. INTEGER position
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

SinglyLinkedListNode* deleteNode(SinglyLinkedListNode* llist, int position) {
    SinglyLinkedListNode* temp = llist;
    if(position == 0)
    {
        llist = llist->next;
        free(temp);
        return llist;
    }
    for(int i = 0; i < position -1; i++)
    {
        temp = temp->next;
    }
    SinglyLinkedListNode* del = temp->next;
    temp->next = temp->next->next;
    free(del);
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

        llist->insert_node(llist_item);
    }

    int position;
    cin >> position;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    SinglyLinkedListNode* llist1 = deleteNode(llist->head, position);

    print_singly_linked_list(llist1, " ", fout);
    fout << "\n";

    free_singly_linked_list(llist1);

    fout.close();

    return 0;
}
