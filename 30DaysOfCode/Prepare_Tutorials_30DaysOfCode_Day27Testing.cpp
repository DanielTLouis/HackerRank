/*Problem*/
/**
This problem is about unit testing.
Your company needs a function that meets the following requirements:
  * For a given array of n integers, the function returns the index of the element with the minimum value in
    the array. If there is more than one element with the minimum value, it returns the smallest one.
  * If an empty array is passed to the function, it raises an exception. A colleague has written this method.
    The implementation in Python is listed below. Implementations in other languages can be found in the code
    template.
    def minimum_index(seq):
        if len(seq) == 0:
            raise ValueError("Cannot get the minimum value index from an empty sequence")
        min_idx = 0
        for i in range(1, len(seq)):
            if a[i] < a[min_idx]:
                min_idx = i
        return min_idx
A coworker has prepared functions that will perform the tests and validate return values. Finish the
implementation of 3 classes to provide data and expected results for the tests.
Complete the following methods.
  In the class TestDataEmptyArray:
    * get_array() returns an empty array
  In the class TestDataUniqueValues:
    * get_array() returns an array of size at least 2 with all unique elements
    * get_expected_result() returns the expected minimum value index for this array
  In the class TestDataExactlyTwoDifferentMinimums:
    * get_array() returns an array where the minimum value occurs at exactly 2 indices
    * get_expected_result() returns the expected index
Take a look at the code template to see the exact implementation of functions that your colleague already
implemented.
Note: The arrays are indexed from 0.
**/
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cassert>
#include <set>

using namespace std;

int minimum_index(vector<int> seq) {
    if (seq.empty()) {
        throw invalid_argument("Cannot get the minimum value index from an empty sequence");
    }
    int min_idx = 0;
    for (int i = 1; i < seq.size(); ++i) {
        if (seq[i] < seq[min_idx]) {
            min_idx = i;
        }
    }
    return min_idx;
}

class TestDataEmptyArray
{
    public:
    TestDataEmptyArray(){}
    static vector<int> get_array()
    {
        return {};
    }
};
class TestDataUniqueValues
{
    public:
    TestDataUniqueValues(){}
    static vector<int> get_array()
    {
        return {1,2};
    }
    static int get_expected_result()
    {
        return 0;
    }
};
class TestDataExactlyTwoDifferentMinimums
{
    public:
    TestDataExactlyTwoDifferentMinimums(){}
    static vector<int> get_array()
    {
        return {1,1};
    }
    static int get_expected_result()
    {
        return 0;
    }
};

void TestWithEmptyArray() {
    try {
        auto seq = TestDataEmptyArray::get_array();
        auto result = minimum_index(seq);
    } catch (invalid_argument& e) {
        return;
    }
    assert(false);
}

void TestWithUniqueValues() {
    auto seq = TestDataUniqueValues::get_array();
    assert(seq.size() >= 2);

    assert(set<int>(seq.begin(), seq.end()).size() == seq.size());

    auto expected_result = TestDataUniqueValues::get_expected_result();
    auto result = minimum_index(seq);
    assert(result == expected_result);
}

void TestWithExactlyTwoDifferentMinimums() {
    auto seq = TestDataExactlyTwoDifferentMinimums::get_array();
    assert(seq.size() >= 2);

    auto tmp = seq;
    sort(tmp.begin(), tmp.end());
    assert(tmp[0] == tmp[1] and (tmp.size() == 2 or tmp[1] < tmp[2]));

    auto expected_result = TestDataExactlyTwoDifferentMinimums::get_expected_result();
    auto result = minimum_index(seq);
    assert(result == expected_result);
}

int main() {
    TestWithEmptyArray();
    TestWithUniqueValues();
    TestWithExactlyTwoDifferentMinimums();
    cout << "OK" << endl;
    return 0;
}
