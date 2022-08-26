/*
This challenge is part of a tutorial track by MyCodeSchool
You are given the pointer to the head node of a sorted linked list, where the
data in the nodes is in ascending order. Delete nodes and return a sorted list
with each distinct value in the original list. The given head pointer may be
null indicating that the list is empty.
Example
  head refers to the first node in the list 1->2->2->3->3->3->3->4->NULL.
  Remove 1 of the 2 data values and return  pointing to the revised list
  1->2->3->NULL.
Function Description
  Complete the removeDuplicates function in the editor below.
  removeDuplicates has the following parameter:
    -SinglyLinkedListNode pointer head: a reference to the head of the list
Returns
  SinglyLinkedListNode pointer: a reference to the head of the revised list
Input Format
  The first line contains an integer t, the number of test cases.
  The format for each test case is as follows:
  The first line contains an integer , the number of elements in the linked
  list.
  Each of the next n lines contains an integer, the data value for each of the
  zelements of the linked list.
Constraints
  1<=t<=10
  1<=n<=1000
  1<=list[i]<=1000
Sample Input
  STDIN   Function
  -----   --------
  1       t = 1
  5       n = 5
  1       data values = 1, 2, 2, 3, 4
  2
  2
  3
  4
Sample Output
  1 2 3 4
Explanation
  The initial linked list is: 1->2->2->3->4->NULL.
  The final linked list is: 1->2->3->4->NULL.
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
 * Complete the 'removeDuplicates' function below.
 *
 * The function is expected to return an INTEGER_SINGLY_LINKED_LIST.
 * The function accepts INTEGER_SINGLY_LINKED_LIST llist as parameter.
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

SinglyLinkedListNode* removeDuplicates(SinglyLinkedListNode* llist) {
    SinglyLinkedListNode* temp = llist;
    while(temp->next)
    {
        if(temp->data == temp->next->data)
        {
            SinglyLinkedListNode* hold = temp->next;
            temp->next = temp->next->next;
            free(hold);
            continue;
        }
        temp = temp->next;
    }
    return llist;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
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

        SinglyLinkedListNode* llist1 = removeDuplicates(llist->head);

        print_singly_linked_list(llist1, " ", fout);
        fout << "\n";

        free_singly_linked_list(llist1);
    }

    fout.close();

    return 0;
}
