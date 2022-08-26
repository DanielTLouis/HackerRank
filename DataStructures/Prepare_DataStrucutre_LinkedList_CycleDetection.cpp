/*
A linked list is said to contain a cycle if any node is visited more than once
while traversing the list. Given a pointer to the head of a linked list,
determine if it contains a cycle. If it does, return 1. Otherwise, return 0.
Example
  head refers to the list of nodes 1->2->3->NULL
  The numbers shown are the node numbers, not their data values. There is no
  cycle in this list so return 0.
  head refers to the list of nodes 1->2->3->1->NULL
  There is a cycle where node 3 points back to node 1, so return 1.
Function Description
  Complete the has_cycle function in the editor below.
  It has the following parameter:
    -SinglyLinkedListNode pointer head: a reference to the head of the list
Returns
  int:  1 if there is a cycle or 0 if there is not
  Note: If the list is empty, head will be null.
Input Format
  The code stub reads from stdin and passes the appropriate argument to your
  function. The custom test cases format will not be described for this question
  due to its complexity. Expand the section for the main function and review the
  code if you would like to figure out how to create a custom case.
Constraints
  0<=list size<=1000
Sample Input
  References to each of the following linked lists are passed as arguments to
  your function:
  Sample Inputs
Sample Output
  0
  1
Explanation
  The first list has no cycle, so return 0.
  The second list has a cycle, so return 1.
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
/*//comment solution I like

//clacrone 6 years ago(user)
//The old "tortoise and the hare" problem. Essentially, the "fast" pointer moves 2x
//the speed as the "slow" pointer. If there is a cycle, they will meet.
int HasCycle(Node head) {
    if (head == null){
        return 0;
    }

    Node slow = head;
    Node fast = head;

    while (fast != null && fast.next != null){
        slow = slow.next;
        fast = fast.next.next;

        if (slow == fast){
            return 1;
        }
    }

    return 0;
}
*/
// Complete the has_cycle function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
bool has_cycle(SinglyLinkedListNode* head) {
    int i = 0;
    while(head->next)
    {
        head=head->next;
        i +=1;
        if(i == 1001)//0<=listsize<=1000
        {
            return 1;
        }
    }
    return 0;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int tests;
    cin >> tests;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int tests_itr = 0; tests_itr < tests; tests_itr++) {
        int index;
        cin >> index;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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

      	SinglyLinkedListNode* extra = new SinglyLinkedListNode(-1);
      	SinglyLinkedListNode* temp = llist->head;

      	for (int i = 0; i < llist_count; i++) {
            if (i == index) {
          		extra = temp;
            }

          	if (i != llist_count-1) {
          		temp = temp->next;
            }
        }

      	temp->next = extra;

        bool result = has_cycle(llist->head);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
