/*
A queue is an abstract data type that maintains the order in which elements were added
to it, allowing the oldest elements to be removed from the front and new elements to
be added to the rear. This is called a First-In-First-Out (FIFO) data structure
because the first element added to the queue (i.e., the one that has been waiting the
longest) is always the first one to be removed.
A basic queue has the following operations:
    -Enqueue: add a new element to the end of the queue.
    -Dequeue: remove the element from the front of the queue and return it.
In this challenge, you must first implement a queue using two stacks. Then process q
queries, where each query is one of the following 3 types:
    1 x: Enqueue element x into the end of the queue.
    2: Dequeue the element at the front of the queue.
    3: Print the element at the front of the queue.
Input Format
    The first line contains a single integer, q, denoting the number of queries.
    Each line i of the q subsequent lines contains a single query in the form
    described in the problem statement above. All three queries start with an integer
    denoting the query type, but only query 1 is followed by an additional
    space-separated value, x, denoting the value to be enqueued.
Constraints
    1<=q<=10^5
    1<=type<=3
    1<=|x|<=10^9
    It is guaranteed that a valid answer always exists for each query of type 3.
Output Format
    For each query of type 3, print the value of the element at the front of the queue
    on a new line.
Sample Input
    STDIN   Function
    -----   --------
    10      q = 10 (number of queries)
    1 42    1st query, enqueue 42
    2       dequeue front element
    1 14    enqueue 42
    3       print the front element
    1 28    enqueue 28
    3       print the front element
    1 60    enqueue 60
    1 78    enqueue 78
    2       dequeue front element
    2       dequeue front element
Sample Output
    14
    14
Explanation
    Perform the following sequence of actions:
        1.Enqueue 42; queue={42}.
        2.Dequeue the value at the head of the queue, 42; queue={}.
        3.Enqueue 14; queue={14}.
        4.Print the value at the head of the queue, 14; queue={14}.
        5.Enqueue 28; queue={14,28}.
        6.Print the value at the head of the queue, 14; queue={14,28}.
        7.Enqueue 60; queue={14,28,60}.
        8.Enqueue 78; queue={14,28,60,78}.
        9.Dequeue the value at the head of the queue, 14; queue={28,60,78}.
        10.Dequeue the value at the head of the queue, 28; queue={60,78}.
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <cstddef>
#include <bitset>
using namespace std;

/* to slow but worked
class node
{
  public:
    int data;
    node* next;
    node(int d)
    {
        data = d;
        next = nullptr;
    }
};
class queue
{
  public:
    node* head;
    queue()
    {
        head = nullptr;
    }
    void insert(int data)
    {
        if(head == nullptr)
        {
            head = new node(data);
        }
        else
        {
            node* temp = head;
            while(true)
            {
                if(temp->next != nullptr)
                {
                    temp = temp->next;
                }
                else{
                    break;
                }
            }
            node* n = new node(data);
            temp->next = n;
        }
    }
    int front()
    {
        return head->data;
    }
    void pop()
    {
        node* temp = head;
        head = head->next;
        delete(temp);
    }
};





int main() {
    // Enter your code here. Read input from STDIN. Print output to STDOUT
    int n;
    cin >> n;
    queue  q;
    int one = 0, two = 0;
    for(int i = 0; i < n; i++)
    {
        cin >> one;
        if(one == 1)
        {
            cin >> two;
            q.insert(two);
        }
        if(one == 2)
        {
            q.pop();
        }
        if(one == 3)
        {
            cout << q.front() << endl;
        }
    }
    return 0;
}
*/
int deQueue(vector<int> &queue){
    int element = queue.at(0);
    queue.erase(queue.begin());
    return element;

}
void enQueue(vector<int> &queue, int data){
    queue.push_back(data);
}
int main() {
    vector<int> q;
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    for(string line; getline(cin,line);){
        string query = "";
        string data = "";
        if(line.length() > 1){
            bool flag = false;
            for(auto c: line){
                if(c == ' '){
                    flag = true;
                }else{
                    if(flag){
                        data+=c;
                    }else{
                        query+=c;
                    }
                }
            }
        }else{
            query = line;
        }

        if(query == "1"){
            enQueue(q, stoi(data));
        }
        else if(query == "2"){
            deQueue(q);
        }
        else if (query == "3") {
            cout << q.at(0) << endl;
        }
    }
    return 0;
}
