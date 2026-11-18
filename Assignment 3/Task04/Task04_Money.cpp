#include <iomanip>
#include <iostream>
class Money {
    long long paise;
    struct RawTag {};
    Money(long long totalPaise,RawTag) : paise(totalPaise) {}
public:
    Money(long long rupees=0,int p=0) : paise(rupees*100+p) {}
    Money operator+(const Money& x) const { return Money(paise+x.paise,RawTag{}); }
    Money operator-(const Money& x) const { return Money(paise-x.paise,RawTag{}); }
    Money& operator+=(const Money& x) { paise+=x.paise; return *this; }
    bool operator==(const Money& x) const { return paise==x.paise; }
    bool operator<(const Money& x) const { return paise<x.paise; }
    friend std::ostream& operator<<(std::ostream& o,const Money& m) {
        long long v=m.paise<0?-m.paise:m.paise;
        if(m.paise<0) o<<"-";
        return o<<"Rs "<<v/100<<'.'<<std::setw(2)<<std::setfill('0')<<v%100;
    }
    friend std::istream& operator>>(std::istream& in,Money& m) {
        long long r; int p; if(in>>r>>p) m.paise=r*100+p; return in;
    }
};
int main() {
    Money a(120,75),b(79,25); Money c=a+b;
    std::cout<<c<<'\n'<<std::boolalpha<<(c==Money(200,0))<<'\n';
    Money carry(0,75); carry+=Money(0,50); std::cout<<"Paise carry: "<<carry<<'\n';
    Money negative=Money(1,0)-Money(2,25); std::cout<<"Negative balance: "<<negative<<'\n';
}