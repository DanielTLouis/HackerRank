/*Problem*/
/**
Objective
  Today we will work with a Linked List. Check out the Tutorial* tab for learning materials and an instructional video.
  A Node class is provided for you in the editor. A Node object has an integer data field, data, and a Node instance pointer, next, pointing to another node (i.e.: the next node in the list).
  A Node insert function is also declared in your editor. It has two parameters: a pointer, head, pointing to the first node of a linked list, and an integer, data, that must be added to the end of the list as a new Node object.
  * https://www.hackerrank.com/challenges/30-linked-list/tutorial
Task
  Complete the insert function in your editor so that it creates a new Node (pass data as the Node constructor argument) and inserts it at the tail of the linked list referenced by the head parameter. Once the new node is added, return the reference to the head node.
  Note: The head argument is null for an empty list.
Input Format
  The first line contains T, the number of elements to insert.
  Each of the next T lines contains an integer to insert at the end of the list.
Output Format
  Return a reference to the head node of the linked list.
Sample Input
  STDIN   Function
  -----   --------
  4       T = 4
  2       first data = 2
  3
  4
  1       fourth data = 1
Sample Output
  2 3 4 1
Explanation
  T=4, so your method will insert 4 nodes into an initially empty list.
  First the code returns a new node that contains the data value 2 as the head of the list. Then create and insert nodes 3, 4, and 1 at the tail of the list.
  LinkedListExplanation.png
**/

#include <iostream>
#include <cstddef>
using namespace std;
class Node
{
    public:
        int data;
        Node *next;
        Node(int d){
            data=d;
            next=NULL;
        }
};
class Solution{
    public:

      Node* insert(Node *head,int data)
      {
          //Complete this method
          Node *temp = new Node(data);
          if(head == NULL)
          {
              head = temp;
              return head;
          }
          else
          {
            temp = head;
            while(temp->next != NULL)
            {
                    temp = temp->next;
            }
            temp->next = new Node(data);
            //need to return head or it will not work (idk why you
            //* would wand to return anyhting )
            return head;
          }
      }

      void display(Node *head)
      {
          Node *start=head;
          while(start)
          {
              cout<<start->data<<" ";
              start=start->next;
          }
      }
};
int main()
{
	Node* head=NULL;
  	Solution mylist;
    int T,data;
    cin>>T;
    while(T-->0){
        cin>>data;
        head=mylist.insert(head,data);
    }
	mylist.display(head);

}
