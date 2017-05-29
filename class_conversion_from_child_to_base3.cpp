#include <iostream>
#include <string>
using namespace std;

class Quote
{
public:
    Quote() = default;
    ~Quote() = default;
    const string& isbn() const { return this->bookNo; }
    virtual void debug() const { cout << "bookNo=" << this->bookNo << " price=" << this->price << endl; }
    virtual double net_price(std::size_t n) const { return n * this->price; }
    Quote(std::string& book, double sale_price) : price(sale_price), bookNo(book){}

private:
    std::string bookNo;
protected:
    double price = 0.0;
};

class Disc_Quote : public Quote
{
public:
    Disc_Quote() = default;
    ~Disc_Quote() = default;
    Disc_Quote(std::string& book, double sale_price = 0, std::size_t n = 0, double rate = 0.0)
                : Quote(book, sale_price), quantity(n), discount(rate){}
    virtual double net_price(std::size_t) const = 0;
    virtual void debug() const
    {
        Quote::debug();
        cout << "quantity=" << this->quantity << " discount=" << this->discount << endl;
    }

protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

class Bulk_quote : public Disc_Quote
{
public:
    Bulk_quote() = default;
    ~Bulk_quote() = default;
    Bulk_quote(std::string& book, double sale_price = 0, std::size_t n = 0, double discount = 0.0)
        : Disc_Quote(book, sale_price, n, discount){}
    virtual double net_price(std::size_t n) const override
    {
        if (n >= quantity)
            return n * (1 - discount) * price;
        else
            return n * price;
    }
};

double print_total(ostream& os, Quote& obj, std::size_t n)
{
    double ret = obj.net_price(n);
    os << "ISBN=" << obj.isbn() << " # sold=" << n << " total due=" << ret << endl;
    return ret;
}

int main()
{
    string isbn = "IS-66666-9999";
    Quote quote(isbn, 10);
    Bulk_quote bulk_quote(isbn, 10, 11, 0.8);
    print_total(cout, bulk_quote, 20);

    return 0;
}
