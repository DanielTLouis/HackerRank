/*
You are a waiter at a party. There is a pile of numbered plates. Create an empty
answers array. At each iteration, i, remove each plate from the top of the stack
in order. Determine if the number on the plate is evenly divisible by the ith
prime number. If it is, stack it in pile Bi. Otherwise, stack it in stack Ai.
Store the values in Bi from top to bottom in answers. In the next iteration, do
the same with the values in stack Ai. Once the required number of iterations is
complete, store the remaining values in Ai in answers, again from top to bottom.
Return the answers array.
Example
  A=[2,3,4,5,6,7]
  q=3
  An abbreviated list of primes is [2,3,5,7,11,13]. Stack the plates in reverse
  order.
  A0=[2,3,4,5,6,7]
  answers=[]
  Begin iterations. On the first iteration, check if items are divisible by 2.
  A1=[7,5,3]
  B1=[6,4,2]
  Move B1 elements to answers.
  answers=[2,4,6]
  On the second iteration, test if A2 elements are divisible by 3.
  A2=[7,5]
  B2=[3]
  Move B2 elmements to answers.
  answer=[2,4,6,3]
  And on the third iteration, test if A2 elements are divisible by 5.
  A3=[7]
  B3=[5]
  Move B2 elmements to answers.
  answers=[2,4,6,3,5]
  All iterations are complete, so move the remaining elements in A3, from top to
  bottom, to answers.
  answers=[2,4,6,3,5,7]. Return this list.
Function Description
  Complete the waiter function in the editor below.
  waiter has the following parameters:
    -int number[n]: the numbers on the plates
    -int q: the number of iterations
Returns
  int[n]: the numbers on the plates after processing
Input Format
  The first line contains two space separated integers, n and q.
  The next line contains n space separated integers representing the initial
  pile of plates, i.e., A.
Constraints
  1<=n<=5*1064
  2<=number[i]<=10^4
  1<=q<=1200
Sample Input 0
  5 1
  3 4 7 6 5
Sample Output 0
  4
  6
  3
  7
  5
Explanation 0
  Initially:
  A= [3, 4, 7, 6, 5]<-TOP
  After 1 iteration (divide by 2, the 1st prime number):
  A1= [5, 7, 3]<-TOP
  B1= [6, 4]<-TOP
  Move B1 elements to answers.
  answers=[4,6]
  All iterations are complete, so move A1 elements to answers.
  answers=[4,6,3,7,5].
Sample Input 1
  5 2
  3 3 4 4 9
Sample Output 1
  4
  4
  9
  3
  3
Explanation 1
  Initially:
  A= [3, 3, 4, 4, 9]<-TOP
  After 1st iteration (divide by 2):
  A1= [9, 3, 3]<-TOP
  B1= [4, 4]<-TOP
  Move B1 to answers.
  answer=[4,4]
  After 2nd iteration (divide by 3):
  A2= []<- TOP
  B2= [3, 3, 9]<-TOP
  Move B2 elements to answers.
  answers=[4,4,9,3,3]
  There are no values remaining in A2.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
*Next Prime Number
*/
int nextPrime(int n)
{
    int nxtPrime = n + 1;
    if(nxtPrime == 2)
    {
        return 2;
    }
    bool found = false;
    while(!found)
    {
        for(int i = 2; i < nxtPrime; i++)
        {
            if(nxtPrime % i == 0)
            {
                break;
            }
            if(i == nxtPrime - 1)
            {
                found = true;
            }
        }
        if(!found)
        {
            nxtPrime += 1;
        }
        else
        {
            break;
        }
    }
    return nxtPrime;
}

/*Append
*append to vector
*/
void append(vector<int>& v1,vector<int> v2)
{
    for(auto index = v2.crbegin();index != v2.crend();++index)
    {
        v1.push_back(*index);
    }
}

/*
 * Complete the 'waiter' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY number
 *  2. INTEGER q
 */

vector<int> waiter(vector<int> number, int q) {
    vector<int> answers;
    int prime = 2;
    vector<int> a , b;
    while(q>0)
    {
        a.clear();b.clear();
        for(auto index = number.crbegin();index != number.crend();++index)
        {
            if(*index%prime == 0)
                b.push_back(*index);
            else
                a.push_back(*index);
        }
        append(answers, b);

        number.clear();
        append(number, a);
        number = a;
        prime = nextPrime(prime);
        q--;
    }
    append(answers, a);
    return answers;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int q = stoi(first_multiple_input[1]);

    string number_temp_temp;
    getline(cin, number_temp_temp);

    vector<string> number_temp = split(rtrim(number_temp_temp));

    vector<int> number(n);

    for (int i = 0; i < n; i++) {
        int number_item = stoi(number_temp[i]);

        number[i] = number_item;
    }

    vector<int> result = waiter(number, q);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
