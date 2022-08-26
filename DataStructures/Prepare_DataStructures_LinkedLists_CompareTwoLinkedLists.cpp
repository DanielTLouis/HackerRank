/*
This challenge is part of a tutorial track by MyCodeSchool
You’re given the pointer to the head nodes of two linked lists. Compare the
data in the nodes of the linked lists to check if they are equal. If all data
attributes are equal and the lists are the same length, return 1. Otherwise,
return 0.
Example
  list1=1->2->3->NULL
  llist2=1->2->3->4->NULL
  The two lists have equal data attributes for the first 3 nodes. llist2 is
  longer, though, so the lists are not equal. Return 0.
Function Description
  Complete the compare_lists function in the editor below.
  compare_lists has the following parameters:
    -SinglyLinkedListNode llist1: a reference to the head of a list
    -SinglyLinkedListNode llist2: a reference to the head of a list
Returns
  int: return 1 if the lists are equal, or 0 otherwise
Input Format
  The first line contains an integer t, the number of test cases.
  Each of the test cases has the following format:
  The first line contains an integer n, the number of nodes in the first linked
  list.
  Each of the next n lines contains an integer, each a value for a data
  attribute.
  The next line contains an integer m, the number of nodes in the second linked
  list.
  Each of the next m lines contains an integer, each a value for a data
  attribute.
Constraints
  1<=t<=10
  1<=n,m<=1000
  1<=llist1[i],llist2[i]<=1000
Output Format
  Compare the two linked lists and return 1 if the lists are equal. Otherwise,
  return 0. Do NOT print anything to stdout/console.
  The output is handled by the code in the editor and it is as follows:
  For each test case, in a new line, print 1 if the two lists are equal, else
  print 0.
Sample Input
  2
  2
  1
  2
  1
  1
  2
  1
  2
  2
  1
  2
Sample Output
  0
  1
Explanation
  There are t=2 test cases, each with a pair of linked lists.
    -In the first case, linked lists are: 1 -> 2 -> NULL and 1 -> NULL
    -In the second case, linked lists are: 1 -> 2 -> NULL and 1 -> 2 -> NULL
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

// Complete the compare_lists function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
bool compare_lists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
    while(head1->next)
    {
        if(!head2->next)
        {
            return 0;
        }
        if(head1->data != head2->data)
        {
            return 0;
        }
        head1 = head1->next;
        head2 = head2->next;
    }
    if(head2->next)
    {
        return 0;
    }
    return 1;

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

        bool result = compare_lists(llist1->head, llist2->head);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
