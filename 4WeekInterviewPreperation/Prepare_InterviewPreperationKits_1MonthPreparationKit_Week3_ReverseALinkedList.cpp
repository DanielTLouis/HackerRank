/*
This challenge is part of a tutorial track by MyCodeSchool and is accompanied by
a video lesson.
Given the pointer to the head node of a linked list, change the next pointers of
the nodes so that their order is reversed. The head pointer given may be null
meaning that the initial list is empty.
Example
head references the list 1->2->3->NULL
Manipulate the next pointers of each node in place and return head, now
referencing the head of the list 3->2->1->NULL.
Function Description
  Complete the reverse function in the editor below.
  reverse has the following parameter:
    -SinglyLinkedListNode pointer head: a reference to the head of a list
Returns
  SinglyLinkedListNode pointer: a reference to the head of the reversed list
Input Format
  The first line contains an integer t, the number of test cases.
  Each test case has the following format:
  The first line contains an integer n, the number of elements in the linked
  list.
  Each of the next n lines contains an integer, the data values of the elements
  in the linked list.
Constraints
  1<=t<=10
  1<=n<=1000
  1<=list[i]<=1000, where list[i] is the ith element in the list.
Sample Input
  1
  5
  1
  2
  3
  4
  5
Sample Output
  5 4 3 2 1
Explanation
  The initial linked list is: 1->2->3->4->5->NULL.
  The reversed linked list is: 5->4->3->2->1->NULL.
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
 * Complete the 'reverse' function below.
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

SinglyLinkedListNode* reverse(SinglyLinkedListNode* llist) {
    vector<int> container;
    while(true)
    {
        container.push_back(llist->data);
        if(llist->next != nullptr)
        {
            llist = llist->next;
        }
        else
        {
            break;
        }
    }
    SinglyLinkedList* nl = new SinglyLinkedList();
    for(int i = container.size()-1; i >= 0; i--)
    {
        nl->insert_node(container[i]);
    }
    return nl->head;
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

        SinglyLinkedListNode* llist1 = reverse(llist->head);

        print_singly_linked_list(llist1, " ", fout);
        fout << "\n";

        free_singly_linked_list(llist1);
    }

    fout.close();

    return 0;
}
