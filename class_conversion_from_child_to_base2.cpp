#include <iostream>
#include <string>
using namespace std;

class Quote
{
public:
    Quote() = default;
    ~Quote() = default;
    virtual double net_price(std::size_t n) const { return n * this->price; }
    Quote(const string& book, double sales_price) : bookNo(book), price(sales_price) {}
    std::string& isbn() { return this->bookNo; }
    virtual void debug()
    {
        cout << "bookNo:" << this->bookNo << " price:" << this->price << endl;
    }
private:
    std::string bookNo;
protected:
    double price = 0.0;
};

class Bulk_quote : public Quote
{
public:
    Bulk_quote() = default;
    Bulk_quote(const string& book, double sale_price = 0, double dis_rate = 0, std::size_t n = 0)
            : Quote(book, sale_price), discount(dis_rate), min_qty(n){}
    virtual double net_price(std::size_t n) const override
    {
        if (n <= min_qty)
            return n * price;
        else
            return n * ( 1- discount) * price;
    }
    virtual void debug() override
    {
        Quote::debug(); //bookNo是private成员变量，所以派生类无法直接访问该变量，职能调用基类的虚函数debug来显示
        cout << "discount=" << this->discount << " min_qty=" << this->min_qty << endl;
    }
private:
    double discount;
    std::size_t min_qty;
};

int main()
{
    return 0;
}
