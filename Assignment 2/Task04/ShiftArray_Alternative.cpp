#include <iostream>
class ShiftHistory{double data[10]{};int count=0;
public:void add(double x){if(count<10)data[count++]=x;else{for(int i=1;i<10;++i)data[i-1]=data[i];data[9]=x;}}
void print()const{for(int i=0;i<count;++i)std::cout<<data[i]<<' ';std::cout<<'\n';}};
int main(){ShiftHistory h;for(int i=1;i<=12;++i)h.add(i*10);h.print();}