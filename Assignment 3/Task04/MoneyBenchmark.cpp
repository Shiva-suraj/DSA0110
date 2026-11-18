#include <chrono>
#include <iomanip>
#include <iostream>
#include <cstdint>
int main(){
    constexpr int N=1000000;
    volatile std::int64_t paise=123;auto a=std::chrono::steady_clock::now();
    for(int i=0;i<N;++i)paise=paise+17;auto b=std::chrono::steady_clock::now();
    volatile double amount=1.23;auto c=std::chrono::steady_clock::now();
    for(int i=0;i<N;++i)amount=amount+0.17;auto d=std::chrono::steady_clock::now();
    std::cout<<"Integer paise: "<<std::chrono::duration<double,std::milli>(b-a).count()<<" ms; result="<<paise<<'\n';
    std::cout<<std::setprecision(15)<<"double: "<<std::chrono::duration<double,std::milli>(d-c).count()<<" ms; result="<<amount<<'\n';
}
