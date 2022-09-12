/*
This challenge works with a custom-designed markup language HRML. In HRML, each element
consists of a starting and ending tag, and there are attributes associated with each tag.
Only starting tags can have attributes. We can call an attribute by referencing the tag,
followed by a tilde, '~' and the name of the attribute. The tags may also be nested.
The opening tags follow the format:
<tag-name attribute1-name = "value1" attribute2-name = "value2" ...>
The closing tags follow the format:
</tag-name>
The attributes are referenced as:
    tag1~value
    tag1.tag2~name
Given the source code in HRML format consisting of N lines, answer Q queries. For each
query, print the value of the attribute specified. Print "Not Found!" if the attribute
does not exist.
Example
        HRML listing
        <tag1 value = "value">
        <tag2 name = "name">
        <tag3 another="another" final="final">
        </tag3>
        </tag2>
        </tag1>

        Queries
        tag1~value
        tag1.tag2.tag3~name
        tag1.tag2~value
    Here, tag2 is nested within tag1, so attributes of tag2 are accessed as
    tag1.tag2~<attribute>. Results of the queries are:
        Query                 Value
        tag1~value            "value"
        tag1.tag2.tag3~name   "Not Found!"
        tag1.tag2.tag3~final  "final"
Input Format
The first line consists of two space separated integers, N and Q. N specifies the number of lines in the HRML source program. Q specifies the number of queries.
The following N lines consist of either an opening tag with zero or more attributes or a closing tag. There is a space after the tag-name, attribute-name, '=' and value.There is no space after the last value. If there are no attributes there is no space after tag name.
Q queries follow. Each query consists of string that references an attribute in the source program.More formally, each query is of the form tag_i1,tag_i2,tag_i3...tag_im ~attr-name where m>=1 and tag_i1,tag_i2,tag_i3...tag_im are valid tags in the input.
Constraints
    1<=N<=20
    1<=Q<=20
    Each line in the source program contains, at most, 200 characters.
    Every reference to the attributes in the Q queries contains at most 200 characters.
    All tag names are unique and the HRML source program is logically correct, i.e. valid
    nesting.
    A tag can may have no attributes.
Output Format
    Print the value of the attribute for each query. Print "Not Found!" without quotes if
    the attribute does not exist.
Sample Input
    4 3
    <tag1 value = "HelloWorld">
    <tag2 name = "Name1">
    </tag2>
    </tag1>
    tag1.tag2~name
    tag1~name
    tag1~value
Sample Output
    Name1
    Not Found!
    HelloWorld
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<string> getQuery(vector<string> query) {
    int l, st;
    string buf;
    query.clear();
    getline(cin, buf);
    l = buf.length();
    st = 0;
    for (int i = 0; i < l; i++) {
        if (buf[i] == '.') {
            query.push_back(buf.substr(st, i - st));
            st = i + 1;
        }
        else if (buf[i] == '~') {
            query.push_back(buf.substr(st, i - st));
            st = i;
            query.push_back(buf.substr(st, l - st));
        }
    }
    return query;
}

void resolveQuery(vector<string> query, vector<string> listing) {
    int lQ = query.size();
    int lL = listing.size();
    int iQ = 0;
    int listS, attL, lineL;
    vector<string> currentTagList;
    for (int j = 0; j < lL; j++) {
        if (listing[j][1] == '/') {
            currentTagList.pop_back(); //we remove last tag from the list, valid listing means, we dont need to check what tag it is
        }
        else {
            int k = 1;
            while (listing[j][k] != ' ' && listing[j][k] != '>') {
                k++;
            }
            string newTag = listing[j].substr(1, k-1);
            currentTagList.push_back(newTag);
            if (newTag == query[iQ]) {
                iQ++;
                if (query[iQ][0] == '~') { //we are on the attribute query, our value is on this line, or nowhere
                    listS = currentTagList.size();
                    for (int i = 0; i < listS; i++) {
                        if (currentTagList[i] != query[i]) {
                            cout << "Not Found!" << endl;
                            return;
                        }
                    }
                    attL = query[iQ].length() - 1; //don't count '~'
                    lineL = listing[j].length();
                    for (int i = 1; i + attL < lineL; i++) {
                        if (listing[j].substr(i, attL + 1) == ' ' + query[iQ].substr(1, attL)) {
                            k = i + attL;
                            while (listing[j][k] != '"') {
                                k++;
                            }
                            k++;
                            while (listing[j][k] != '"') {
                                cout << listing[j][k];
                                k++;
                            }
                            cout << endl;
                            return;
                        }
                    }
                    cout << "Not Found!" << endl; //since we didn't find <attribute> on this line we can safetly return
                    return;
                }
            }
        }
    }
    cout << "Not Found!" << endl; //if we gone through the whole list without finding out tag we do not forget to print the result
    return;
}

int main() {
    vector<string> listing;
    vector<string> query;
    int t, q;
    string buffer;
    cin >> t >> q;
    listing.reserve(t);
    getline(cin, buffer); //clearing cin from last endl
    for (int i = 0; i < t; i++) {
        getline(cin, buffer);
        listing.push_back(buffer);
    }
    for (int i = 0; i < q; i++) {
        query = getQuery(query);
        resolveQuery(query, listing);
    }
    return 0;
}

/*
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    // Enter your code here. Read input from STDIN. Print output to STDOUT
    vector<string> code;
    vector<string> querries;
    int n, q;
    cin >> n >> q;
    cin.ignore();
    for(int i = 0; i < n; i++)
    {
        string line;
        getline(cin, line);
        code.push_back(line);
    }
    for(int i = 0; i < q; i++)
    {
        string tempQ;
        getline(cin, tempQ);
        for(int j = 0; j < code.size(); j++)
        {
            if(tempQ.find(".")!= std::string::npos){
                string level = tempQ.substr(0, tempQ.find("."));
                tempQ = tempQ.substr(tempQ.find(".")+1, tempQ.size());
            }
            else if(code[j][1] == '/')
            {
                break;
            }
            else{
                string val = tempQ.substr(tempQ.find("~"), tempQ.size());
                val = val.substr(1,val.size());
                if(code[j].find(val) != std::string::npos)
                {
                    string ans = code[j].substr(code[j].find('\"')+1, code[j].size());
                    cout << ans.substr(0, ans.find('\"')) << endl;
                    break;
                }
                else{
                    cout << "Not Found!" << endl;
                    break;
                }
            }
        }
    }

    return 0;
}
*/
