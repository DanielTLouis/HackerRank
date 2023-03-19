/*
There is a given list of strings where each string contains only lowercase letters from
a-j, inclusive. The set of strings is said to be a GOOD SET if no string is a prefix of
another string. In this case, print GOOD SET. Otherwise, print BAD SET on the first line
followed by the string being checked.
Note If two strings are identical, they are prefixes of each other.
Example
    words['abcd','bcd','abcde','bcde']
    Here 'abcd' is a prefix of 'abcde' and 'bcd' is a prefix of 'bcde'. Since 'abcde' is
    tested first, print
        BAD SET
        abcde
    words = ['ab','bc','cd'].
    No string is a prefix of another so print
      GOOD SET
Function Description
    Complete the noPrefix function in the editor below.
    noPrefix has the following parameter(s):
        - string words[n]: an array of strings
Prints
    - string(s): either GOOD SET or BAD SET on one line followed by the word on the next
    line. No return value is expected.
Input Format
    First line contains n, the size of words[].
    Then next n lines each contain a string, words[i].
Constraints
    1<=n<=10^5
    1<= the length of words[i]<=60
    All letters in words[i] are in the range 'a' through 'j', inclusive.
Sample Input00
    STDIN       Function
    -----       --------
    7            words[] size n = 7
    aab          words = ['aab', 'defgab', 'abcde', 'aabcde', 'bbbbbbbbbb', 'jabjjjad']
    defgab
    abcde
    aabcde
    cedaaa
    bbbbbbbbbb
    jabjjjad
Sample Output00
    BAD SET
    aabcde
Explanation
    'aab' is prefix of 'aabcde' so it is a BAD SET and fails at string 'aabcde'.
Sample Input01
    4
    aab
    aac
    aacghgh
    aabghgh
Sample Output01
    BAD SET
    aacghgh
Explanation
    'aab' is a prefix of 'aabghgh', and aac' is prefix of 'aacghgh'. The set is a BAD
    SET. 'aacghgh' is tested before 'aabghgh', so and it fails at 'aacghgh'.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'noPrefix' function below.
 *
 * The function accepts STRING_ARRAY words as parameter.
 */

class Trie{

    public:
    Trie *childNodes[10];
    int wordCount;

    Trie(){
    for(int i=0;i<10;i++){

        childNodes[i]=NULL;
    }
    wordCount = 0;
    }

};

bool insert_key(Trie *root, string key_word){

Trie *currentNode = root;

for(int i=0;i<key_word.size();i++){
    int index = key_word[i]-'a';

    if(currentNode->childNodes[index]==NULL){
        Trie *newNode = new Trie();
        currentNode->childNodes[index]= newNode;
    }
    else{
        if(currentNode->childNodes[index]->wordCount || i==key_word.size()-1){

            return false;
       }
    }
    currentNode = currentNode->childNodes[index];
}
  currentNode->wordCount++;
  return true;
}

void noPrefix(vector<string> words) {
  Trie *root = new Trie();
for(auto word : words){
  if(!insert_key(root, word)){
      cout<< "BAD SET \n"<< word;
      return;
  }
}
cout<<"GOOD SET ";

}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> words(n);

    for (int i = 0; i < n; i++) {
        string words_item;
        getline(cin, words_item);

        words[i] = words_item;
    }

    noPrefix(words);

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
