#include <iostream>

using namespace std;

class Quote
{
public:
    Quote() = default;
    Quote(const std::string& book, double& sales_price)
            : bookNo(book), price(sales_price) {}
    std::string isbn() const { return this->bookNo; }
    virtual double net_price(std::size_t n) const { return n * price; }
    //Quote& operator=(const Quote&) = default;
    virtual ~Quote() = default;
private:
    std::string bookNo;
protected:
    double price = 0.0;
};

class Bulk_quotes : public Quote
{
public:
    Bulk_quotes() = default;
    ~Bulk_quotes() = default;
    Bulk_quotes(const std::string&, double, std::size_t&, double);
    double net_price(std::size_t) const override;
private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};
double Bulk_quotes::net_price(std::size_t cnt) const
{
    if (cnt <= min_qty)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}

class Limited_quote : public Quote
{
public:
    double net_price(std::size_t cnt) const override
    {
        if (cnt <= min_qty)
            return cnt * (1 - discount) * price;
        else
            return min_qty * (1 - discount) *price + (cnt - min_qty) * price;
    }
private:
    std::size_t min_qty;
    double discount;
};

int main()
{
    Bulk_quotes bulk1;
    Quote item = bulk1; //调用Quote(const Quote&){} 基类的拷贝构造函数
    item = bulk1; //调用Quote& operator=(const Quote&){} 拷贝赋值运算符
    return 0;
}
