#include <chrono>
#include <iostream>
#include <array>
#include <iomanip>
class ShiftHistory{std::array<int,50> v{};int n=0;public:void add(int x){if(n<50)v[n++]=x;else{for(int i=1;i<50;++i)v[i-1]=v[i];v[49]=x;}}int at(int i)const{return v[i];}};
class CircularHistory{std::array<int,50> v{};int n=0,next=0;public:void add(int x){v[next]=x;next=(next+1)%50;if(n<50)++n;}int atOldestFirst(int i)const{return v[(n==50?next:0+i)%50];}};
int main(){constexpr int N=2000000;ShiftHistory s;CircularHistory c;auto a=std::chrono::steady_clock::now();for(int i=0;i<N;++i)s.add(i);auto b=std::chrono::steady_clock::now();for(int i=0;i<N;++i)c.add(i);auto d=std::chrono::steady_clock::now();bool same=true;for(int i=0;i<50;++i)if(s.at(i)!=c.atOldestFirst(i))same=false;std::cout<<"Shift array time: "<<std::fixed<<std::setprecision(3)<<std::chrono::duration<double,std::milli>(b-a).count()<<" ms\nCircular buffer time: "<<std::chrono::duration<double,std::milli>(d-b).count()<<" ms\nSame final 50 values: "<<std::boolalpha<<same<<"\nFirst retained: "<<c.atOldestFirst(0)<<", last retained: "<<c.atOldestFirst(49)<<'\n';}