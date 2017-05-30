/*
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
*/

//+++++++++++++++++++++++++++++++++++以下是进行重构的版本，添加了抽象基类Disc_Quote++++++++++++++++++++++++++++++++++++++++++++
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

class Disc_Quote : public Quote
{
public:
    Disc_Quote() = default;
    Disc_Quote(const string& book, double sale_price = 0.0, std::size_t n = 0, double dis_rate = 0.0) :
        Quote(book, sale_price), quantity(n), discount(dis_rate) {}
    virtual void debug() const { Quote::debug(); cout << " maxSold=" << quantity << " discount=" << discount << endl; }
    virtual double net_price(std::size_t) const = 0;    //这是一个纯虚函数，因此该类是抽象基类，抽象基类是无法创建对象（实例化）的。
protected:
    double discount = 0.0;
    std::size_t quantity = 0;
};

class Bulk_Quote : public Disc_Quote
{
    friend ostream& operator<<(ostream& os, Bulk_Quote& b) { os << "\tUsing operator<<(ostream&, Bulk_Quote&)" << endl; return os; }
public:
    Bulk_Quote(const string& book = "", double sale_price = 0.0, std::size_t n = 0, double dis_rate = 0.0 ) :
        Disc_Quote(book, sale_price, n, dis_rate) { cout << "Bulk_quote Constructor is running..." << endl; }
    ~Bulk_Quote() { cout << "Bulk_Quote Destructor is running..." << endl; }
    virtual void debug() const override { Disc_Quote::debug();}
    virtual double net_price(std::size_t n) const { if (n >= quantity) return n * (1 - discount) * price; else return n * price; }
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
