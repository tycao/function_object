#include <iostream>

using namespace std;

class Quote
{
public:
    Quote() = default;
    Quote(const std::string& book = "", double sales_price = 0.0) :
        bookNo(book), price(sales_price){ cout << "Quote constructor is running..." << endl; }
    const std::string& isbn() const { return this->bookNo; }
    virtual double net_price(std::size_t n) const { return n * price; }
    virtual void debug() const { cout << "bookNo=" << bookNo << " price=" << price << endl; }
    virtual ~Quote() { cout << "Quote Destructor is running..." << endl; }
    friend ostream& operator<<(ostream&, Quote&);

private:
    std::string bookNo;
protected:
    double price = 0.0;
};
ostream& operator<<(ostream& os, Quote& q)
{
    os << "\tUsing operator<<(ostream&, Quote&);" << endl;
    return os;
}

class Bulk_Quote : public Quote
{
    friend ostream& operator<<(ostream& os, Bulk_Quote& b) { os << "\tUsing operator<<(ostream&, Bulk_Quote&)" << endl; return os; }
public:
    Bulk_Quote(const string& book = "", double sale_price = 0.0, std::size_t n = 0, double dis_rate = 0.0 ) :
        Quote(book, sale_price), quantity(n), discount(dis_rate) { cout << "Bulk_quote Constructor is running..." << endl; }
    ~Bulk_Quote() { cout << "Bulk_Quote Destructor is running..." << endl; }
    virtual void debug() { Quote::debug();}
    virtual double net_price(std::size_t n) { if (n >= quantity) return n * (1 - discount) * price; else return n * price; }
private:
    double discount = 0.0;
    std::size_t quantity;
};


int main()
{
    Quote q(string("IS-6666-9999"), 0.8);
    cout << q.isbn() << endl;
    cout << q.net_price(20) << endl;
    cout << q << endl;

    cout << "+++++++++++++++++++++++++" << endl;
    Bulk_Quote b(string("IS-888888-999999"), 10, 9, 0.8);
    cout << b.isbn() << endl;
    b.debug();
    cout << b << endl;
    return 0;
}
