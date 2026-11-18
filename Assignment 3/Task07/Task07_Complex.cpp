#include <cmath>
#include <iostream>
#include <stdexcept>
#include <iomanip>
class Complex {
    double re,im;
public:
    Complex():re(0),im(0){}
    Complex(double real):re(real),im(0){}
    Complex(double real,double imag):re(real),im(imag){}
    double magnitude()const{return std::sqrt(re*re+im*im);}
    Complex operator+(const Complex& z)const{return {re+z.re,im+z.im};}
    Complex operator-(const Complex& z)const{return {re-z.re,im-z.im};}
    Complex operator*(const Complex& z)const{return {re*z.re-im*z.im,re*z.im+im*z.re};}
    Complex operator/(const Complex& z)const{
        double d=z.re*z.re+z.im*z.im;
        if(d==0.0)throw std::domain_error("division by zero impedance");
        return {(re*z.re+im*z.im)/d,(im*z.re-re*z.im)/d};
    }
    bool operator==(const Complex& z)const{return std::abs(re-z.re)<1e-9&&std::abs(im-z.im)<1e-9;}
    friend std::ostream& operator<<(std::ostream& o,const Complex& z){
        o<<std::fixed<<std::setprecision(2)<<z.re<<(z.im<0?" - j":" + j")<<std::abs(z.im);return o;
    }
};
int main(){
    const double w=1000.0,L=0.01,C=10e-6;
    Complex R(10,0),ZL(0,w*L),ZC(0,-1.0/(w*C));
    Complex series=R+ZL+ZC,parallel=(R*ZL)/(R+ZL);
    std::cout<<"R = "<<R<<", |R| = "<<R.magnitude()<<'\n';
    std::cout<<"Series RLC impedance = "<<series<<", magnitude = "<<series.magnitude()<<'\n';
    std::cout<<"Parallel R-L impedance = "<<parallel<<", magnitude = "<<parallel.magnitude()<<'\n';
    try{Complex bad=R/Complex();std::cout<<bad<<'\n';}
    catch(const std::domain_error& e){std::cout<<"Safe error: "<<e.what()<<'\n';}
}