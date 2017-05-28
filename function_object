#include <iostream>
#include <functional>
#include <string>
#include <map>
using namespace std;

//加法运算 （普通函数）
int add(int i, int j) { return i + j; }

//求余数运算 （lambda表达式）
auto mod = [](int i, int j){ return i % j; };

//除法运算 （重载了调用运算符的类--即函数对象）
struct divide
{
    int operator()(int i, int j){ return i / j; }
};

//function是模版函数，可以表示任意类型的可调用对象。如：函数，函数指针， lambda表达式，
//bind创建的对象，重载了函数调用运算符的类
//在使用该模版函数时，需要提供额外的信息。即 该function类型能够表示的对象的调用形式
map<string, function<int(int, int)>> binops = {
    {"+", add}, //加法
    {"-", std::minus<int>()}, //减法
    {"%", mod}, //求余数
    {"/", divide()}, //除法
    {"*", [](int i, int j){ return i * j; }} //乘法
};


int main()
{
    cout << "1 + 1 = " << binops["+"](1, 1) << endl;
    cout << "1 - 1 = " << binops["-"](1, 1) << endl;
    cout << "1 * 2 = " << binops["*"](1, 2) << endl;
    cout << "4 / 2 = " << binops["/"](4, 2) << endl;
    cout << "1 % 2 = " << binops["%"](1, 2) << endl;
    return 0;
}
