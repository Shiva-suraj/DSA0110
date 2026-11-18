#include <chrono>
#include <iostream>
#include <cstdint>
class ClockTime{int h,m;public:ClockTime(int a,int b):h(a),m(b){}friend int distanceInline(const ClockTime&,const ClockTime&);friend int distanceOutOfLine(const ClockTime&,const ClockTime&);};
inline int distanceInline(const ClockTime&a,const ClockTime&b){int x=a.h*60+a.m,y=b.h*60+b.m;return x>y?x-y:y-x;}
int distanceOutOfLine(const ClockTime&a,const ClockTime&b){int x=a.h*60+a.m,y=b.h*60+b.m;return x>y?x-y:y-x;}
int main(){ClockTime a(9,45),b(13,10);constexpr int N=10000000;volatile std::int64_t x=0,y=0;auto s=std::chrono::steady_clock::now();for(int i=0;i<N;++i)x+=distanceInline(a,b);auto m=std::chrono::steady_clock::now();for(int i=0;i<N;++i)y+=distanceOutOfLine(a,b);auto e=std::chrono::steady_clock::now();std::cout<<"inline calls: "<<std::chrono::duration<double,std::milli>(m-s).count()<<" ms, checksum="<<x<<'\n';std::cout<<"out-of-line calls: "<<std::chrono::duration<double,std::milli>(e-m).count()<<" ms, checksum="<<y<<'\n';}