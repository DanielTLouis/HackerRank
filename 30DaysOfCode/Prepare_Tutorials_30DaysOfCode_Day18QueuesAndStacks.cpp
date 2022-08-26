/*Problem*/
/**
Welcome to Day 18! Today we're learning about Stacks and
Queues. Check out the Tutorial tab for learning materials
and an instructional video!
A palindrome is a word, phrase, number, or other sequence
of characters which reads the same backwards and
forwards. Can you determine if a given string, s, is a
palindrome?
To solve this challenge, we must first take each
character in s, enqueue it in a queue, and also push that
same character onto a stack. Once that's done, we must
dequeue the first character from the queue and pop the
top character off the stack, then compare the two
characters to see if they are the same; as long as the
characters match, we continue dequeueing, popping, and
comparing each character until our containers are empty
(a non-match means s isn't a palindrome).
    Write the following declarations and implementations:
    1.Two instance variables: one for your stack, and one
    for your queue.
    2.A void pushCharacter(char ch) method that pushes a
    character onto a stack.
    3.A void enqueueCharacter(char ch) method that
    enqueues a character in the queue instance variable.
    4.A char popCharacter() method that pops and returns
    the character at the top of the stack instance
    variable.
    5.A char dequeueCharacter() method that dequeues and
    returns the first character in the queue instance
    variable.
Input Format
    You do not need to read anything from stdin. The
    locked stub code in your editor reads a single line
    containing string s. It then calls the methods
    specified above to pass each character to your
    instance variables.
Constraints
s is composed of lowercase English letters.
Output Format
    You are not responsible for printing any output to
    stdout.
    If your code is correctly written and s is a palindrome,
    the locked stub code will print The word s, is a
    palindrome;otherwise, it will print The word s, is not
     a palindrome.
Sample Input
    racecar
Sample Output
    The word, racecar, is a palindrome.
**/
#include <iostream>

using namespace std;
struct node
{
    char c;
    node* next;
    node(char ch)
    {
        c = ch;
        next = NULL;
    }
};
//I made my own list to act as que and stack
class myList
{
    public:
    node* head;
    myList(){
        head = NULL;
    }
    myList(char c){
        head = new node(c);
    }
    void insert(char c)
    {
        node* temp = head;
        if(head == NULL)
        {
            head = new node(c);
            return;
        }
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new node(c);
    }
    char pop_back()
    {
        node* temp = head;
        node* tempBehind = head;
        if(head == NULL)
        {
            return '\n';
        }
        char c = ' ';
        while(temp->next != NULL)
        {
            tempBehind = temp;
            temp = temp->next;
        }
        tempBehind->next = NULL;
        c = temp->c;
        delete(temp);
        return c;
    }
    char pop_front()
    {
        node* temp = head;
        char c = temp->c;
        if(head == NULL)
        {
            return '\n';
        }
        head = head->next;
        delete(temp);
        return c;
    }
    void operator=(myList a)
    {
        node* temp = head;
        node* tempBehind;
        head = a.head;
        while(temp->next != NULL)
        {
            tempBehind = temp;
            temp = temp->next;
            delete(tempBehind);
        }
        return;
    }
};
class Solution {
    //Write your code here
    public:
    myList stack;
    myList que;
    Solution(){}

    void pushCharacter(char c)
    {
        stack.insert(c);
        return;
    }
    void enqueueCharacter(char c)
    {
        que.insert(c);
        return;
    }
    char popCharacter()
    {
        char c;
        c = stack.pop_front();
        return c;
    }
    char dequeueCharacter()
    {
        char c;
        c = que.pop_back();
        return c;
    }
};

int main() {
    // read the string s.
    string s;
    getline(cin, s);

  	// create the Solution class object p.
    Solution obj;

    // push/enqueue all the characters of string s to stack.
    for (int i = 0; i < s.length(); i++) {
        obj.pushCharacter(s[i]);
        obj.enqueueCharacter(s[i]);
    }

    bool isPalindrome = true;

    // pop the top character from stack.
    // dequeue the first character from queue.
    // compare both the characters.
    for (int i = 0; i < s.length() / 2; i++) {
        if (obj.popCharacter() != obj.dequeueCharacter()) {
            isPalindrome = false;

            break;
        }
    }

    // finally print whether string s is palindrome or not.
    if (isPalindrome) {
        cout << "The word, " << s << ", is a palindrome.";
    } else {
        cout << "The word, " << s << ", is not a palindrome.";
    }

    return 0;
}
