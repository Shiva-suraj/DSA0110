#include <chrono>
#include <iostream>
struct Counter{
    volatile long long value;
    Counter():value(0){}
    Counter(const Counter& x):value(x.value){}
    Counter& operator++(){value=value+1;return *this;}
    Counter operator++(int){Counter old=*this;value=value+1;return old;}
};
int main(){constexpr int N=10000000;Counter a,b;auto start=std::chrono::steady_clock::now();for(int i=0;i<N;++i)++a;auto mid=std::chrono::steady_clock::now();for(int i=0;i<N;++i)b++;auto end=std::chrono::steady_clock::now();std::cout<<"prefix: "<<std::chrono::duration<double,std::milli>(mid-start).count()<<" ms, value="<<a.value<<'\n';std::cout<<"postfix: "<<std::chrono::duration<double,std::milli>(end-mid).count()<<" ms, value="<<b.value<<'\n';}
