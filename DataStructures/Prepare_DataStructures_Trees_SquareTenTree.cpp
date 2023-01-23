/*
The square-ten tree decomposition of an array is defined as
follows:
    -The lowest (0th) level of the square-ten tree consists of
    single array elements in their natural order.
    -The kth level (starting from 1) of the square-ten tree
    consists of subsequent array subsegments of length
    10^(2^(k-1)) in their natural order. Thus, the 1st level
    contains subsegments of length 10^2^1-1 =10, the 2nd level
    contains subsegments of length 10^2^2-1 =100, the 3rd level
    contains subsegments of length 10^2^3-2 = 1000000, etc.
In other words, every kth level (for every k>=1) of square-ten
tree consists of array subsegments indexed as:
[1,10^2^k-1],[10^2^k-1 + 1, 2*10^2^k-1],...,[i*10^2^k-1 + 1,
Level 0 consists of array subsegments indexed as
[1,1],[2,2],...,[i,i],....
The image below depicts the bottom-left corner (i.e., the first
128 array elements) of the table representing a square-ten tree.
The levels are numbered from bottom to top:
4x128 square-ten tree table
Task
    Given the borders of array subsegment [L,R], find its
    decomposition into a minimal number of nodes of a square-ten
    tree. In other words, you must find a subsegment sequence
    [l_1,r_1], [l_2,l_2], ..., [l_m,r_m] such as l_(i+1)=r_i +1
    for every 1<=i<m, l_1 = L, r_m = R, where every [l_i,r_i]
    belongs to any of the square-ten tree levels and  is minimal
    amongst all such variants.
Input Format
    The first line contains a single integer denoting L.
    The second line contains a single integer denoting R.
Constraints
    1<=L<=R<=10^(10^6)
    The numbers in input do not contain leading zeroes.
Output Format
    As soon as array indices are too large, you should find a
    sequence of M square-ten tree level numbers, s_1,s_2,...,s_m,
    meaning that subsegment [l_i,r_i] belongs to the s_ith level
    of the square-ten tree.
    Print this sequence in the following compressed format:
        -On the first line, print the value of n(i.e., the
        compressed sequence block count).
        -For each of the n subsequent lines, print 2
        space-separated integers, t_i and  c_i(t_i>=0, c_i>=1),
        meaning that the number t_i appears consequently c_i
        times in sequence s. Blocks should be listed in the
        order they appear in the sequence. In other words, s_1,
        s_2,...,s_c_1 should be equal to t_1,
        s_c_1 +1,s_c_1 +2,...,s_c_1 + c_2 should be equal to t_2,
        etc.
    Thus (sumation(c_i = m) for all i=1 to n) must be true and
    t_i != t_i+1 must be true for every 1<=i<n. All numbers
    should be printed without leading zeroes.
Sample Input 0
    1
    10
Sample Output 0
    1
    1 1
Explanation 0
    Segment [1,10] belongs to level 1 of the square-ten tree.
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <stdlib.h>
#include <sstream>
using namespace std;

struct Block {
    unsigned int level;
    string count;
};

void pushBlocks(vector<Block> &blocks, unsigned level, const string& s) {
    auto it = s.rbegin();
    while (*it == '0') it++;
    if (it != s.rend()) blocks.push_back({level, string(it, s.rend())});
}

int main() {
    string l, r;
    vector<Block> blocks;
    cin >> l >> r;

    if (l == r) {
        blocks.push_back({ 0, "1" });
    }
    else {
        // skip matching start
        if (l.length() == r.length()) {
            int i = 0;
            while (l[i] == r[i]) i++;
            l = l.substr(i);
            r = r.substr(i);
        }
        // reverse strings for easier indexing from lowest digit
        reverse(l.begin(), l.end());
        reverse(r.begin(), r.end());

        const int llen = l.length();
        const int rlen = r.length();

        int blockEnd = 1;
        unsigned int level = 0;
        int carry = -1;
        stringstream output;

        // blocks needed raise 'l' to next blockEnd
        int i = 0;
        for (; i < rlen; i++) {
            if (i >= blockEnd) {
                pushBlocks(blocks, level, output.str());
                level++;
                blockEnd *= 2;
                output.str("");
            }
            if (blockEnd >= rlen) {
                break;
            }
            int x = i < llen ? l[i] - '0' : 0;
            int diff = (10 - x - carry) % 10;
            carry = x + carry + diff >= 10;
            output << (char)('0' + diff);
        }
        // top block (simply 'r' - 'l')
        for (int j = i; j < rlen; j++) {
            int x = j < llen ? l[j] - '0' : 0;
            int y = r[j] - '0';
            int diff = (10 + y - x - carry) % 10;
            carry = y - x - carry < 0;
            output << (char)('0' + diff);
        }
        pushBlocks(blocks, level, output.str());
        level--;
        blockEnd /= 2;
        output.str("");

        // add remaining 'r' blocks
        while (blockEnd > 1) {
            pushBlocks(blocks, level, r.substr(blockEnd / 2, blockEnd / 2));
            level--;
            blockEnd /= 2;
        }
        pushBlocks(blocks, level, r.substr(0, 1));
    }

    // print result
    cout << blocks.size() << endl;
    for (auto iter = blocks.begin(); iter != blocks.end(); iter++) {
        cout << iter->level << " " << iter->count << endl;
    }

    return 0;
}
