/*Problem*/
/**
  You are given a main function which reads the enumeration values for two different types as input, then prints out the corresponding enumeration names. Write a class template that can provide the names of the enumeration values for both types. If the enumeration value is not valid, then print unknown.
Input Format
  The first line contains t, the number of test cases.
  Each of the t subsequent lines contains two space-separated integers. The first integer is a color value, c, and the second integer is a fruit value, f.
Constraints
  1<=t<=100
  -2X10^9<=c<=2X10^9
  -2X10^9<=f<=2X10^9
Output Format
  The locked stub code in your editor prints t lines containing the color name and the fruit name corresponding to the input enumeration index.
Sample Input
  2
  1 0
  3 3
Sample Output
  green apple
  unknown unknown
Explanation
  Since t= 2, there are two lines of output.
  1.The two input index values, 1 and 0, correspond to green in the color enumeration and apple in the fruit enumeration. Thus, we print green apple.
  2.The two input values, 3 and 3, are outside of the range of our enums. Thus, we print unknown unknown.
**/

#include <iostream>
using namespace std;
enum class Fruit { apple, orange, pear };
enum class Color { red, green, orange };

template <typename T> struct Traits;
template<typename T>
struct Traits
{
    static string name(int n)
    {
         switch(static_cast<T>(n))
        {
            case static_cast<T>(0):
                if (typeid(T) == typeid(Color)) return "red";
                else return "apple";
            case static_cast<T>(1):
                if (typeid(T) == typeid(Color)) return "green";
                else return "orange";
            case static_cast<T>(2):
                if (typeid(T) == typeid(Color)) return "orange";
                else return "pear";
        }
        return "unknown";
    }
};

int main()
{
	int t = 0; std::cin >> t;

    for (int i=0; i!=t; ++i) {
        int index1; std::cin >> index1;
        int index2; std::cin >> index2;
        cout << Traits<Color>::name(index1) << " ";
        cout << Traits<Fruit>::name(index2) << "\n";
    }
}
