/*
This challenge is part of a tutorial track by MyCodeSchool
Given pointers to the heads of two sorted linked lists, merge them into a single, sorted linked list. Either head pointer may be null meaning that the corresponding list is empty.
Example
  headA refers to 1->3->7->NULL 
  headB refers to 1->2->NULL
  The new list is 1->1->2->3->7->NULL
Function Description
  Complete the mergeLists function in the editor below.
  mergeLists has the following parameters:
    -SinglyLinkedListNode pointer headA: a reference to the head of a list
    -SinglyLinkedListNode pointer headB: a reference to the head of a list
Returns
  SinglyLinkedListNode pointer: a reference to the head of the merged list
Input Format
  The first line contains an integer t, the number of test cases.
  The format for each test case is as follows:
  The first line contains an integer n, the length of the first linked list.
  The next n lines contain an integer each, the elements of the linked list.
  The next line contains an integer m, the length of the second linked list.
  The next m lines contain an integer each, the elements of the second linked list.
Constraints
  1<=t<=10
  1<=n,m<=1000
  1<=list[i]<=1000, where list[i] is the ith element of the list.
Sample Input
  1
  3
  1
  2
  3
  2
  3
  4
Sample Output
  1 2 3 3 4
Explanation
  The first linked list is: 1->3->7->NULL
  The second linked list is: 3->4->NULL
  Hence, the merged linked list is: 1->2->3->3->4->NULL
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

// Complete the mergeLists function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
    SinglyLinkedListNode* ans;
    if(head1->data <= head2->data)
    {
        ans = new SinglyLinkedListNode(head1->data);
        head1 = head1->next;
    }
    else {
        ans = new SinglyLinkedListNode(head2->data);
        head2 = head2->next;
    }
    SinglyLinkedListNode* temp = ans;
    while(head1 || head2)
    {
        if(head1 && head2)
        {
            if(head1->data <= head2->data)
            {
                temp->next = new SinglyLinkedListNode(head1->data);
                head1 = head1->next;
            }
            else
            {
                temp->next = new SinglyLinkedListNode(head2->data);
                head2 = head2->next;
            }
        }
        else if(head1)
        {
            temp->next = new SinglyLinkedListNode(head1->data);
            head1 = head1->next;
        }
        else if(head2)
        {
            temp->next = new SinglyLinkedListNode(head2->data);
            head2 = head2->next;
        }
        temp = temp->next;
    }
    return ans;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int tests;
    cin >> tests;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int tests_itr = 0; tests_itr < tests; tests_itr++) {
        SinglyLinkedList* llist1 = new SinglyLinkedList();

        int llist1_count;
        cin >> llist1_count;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < llist1_count; i++) {
            int llist1_item;
            cin >> llist1_item;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            llist1->insert_node(llist1_item);
        }

      	SinglyLinkedList* llist2 = new SinglyLinkedList();

        int llist2_count;
        cin >> llist2_count;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < llist2_count; i++) {
            int llist2_item;
            cin >> llist2_item;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            llist2->insert_node(llist2_item);
        }

        SinglyLinkedListNode* llist3 = mergeLists(llist1->head, llist2->head);

        print_singly_linked_list(llist3, " ", fout);
        fout << "\n";

        free_singly_linked_list(llist3);
    }

    fout.close();

    return 0;
}
