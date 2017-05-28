#include <iostream>
#include <map>
#include <algorithm>
#include <functional>
using namespace std;

map<string, function<int(int, int)>> binops = {
    {"+", std::plus<int>()},
    {"-", std::minus<int>()},
    {"*", std::multiplies<int>()},
    {"/", std::divides<int>()},
    {"%", std::modulus<int>()}
};

int main()
{
    int a, b;
    string op;
    cin >> a >> op >> b;
    cout << binops[op](a, b) << endl;
    cout << "++++++++++++++++分割线++++++++++++++" << endl;
    cout << "1 + 1 = " << binops["+"](1, 1) << endl;
    cout << "1 - 1 = " << binops["-"](1, 1) << endl;
    cout << "2 * 3 = " << binops["*"](2, 3) << endl;
    cout << "4 / 2 = " << binops["+"](4, 2) << endl;
    cout << "3 % 2 = " << binops["%"](3, 2) << endl;
    return 0;
}
