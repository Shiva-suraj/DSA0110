#include <chrono>
#include <cstring>
#include <iostream>
#include <string>
class TinyText{
    char* p;
public:
    TinyText(const char* s=""){p=new char[std::strlen(s)+1];std::strcpy(p,s);}
    TinyText(const TinyText& x){p=new char[std::strlen(x.p)+1];std::strcpy(p,x.p);}
    TinyText& operator=(const TinyText& x){if(this!=&x){char* q=new char[std::strlen(x.p)+1];std::strcpy(q,x.p);delete[] p;p=q;}return *this;}
    ~TinyText(){delete[] p;}
    TinyText operator+(const TinyText& x)const{std::size_t n=std::strlen(p)+std::strlen(x.p);char* q=new char[n+1];std::strcpy(q,p);std::strcat(q,x.p);TinyText r(q);delete[] q;return r;}
    std::size_t size()const{return std::strlen(p);}
};
int main(){constexpr int N=100000;TinyText left("short "),right("text");std::size_t customTotal=0;auto a=std::chrono::steady_clock::now();for(int i=0;i<N;++i){TinyText combined=left+right;customTotal+=combined.size();}auto b=std::chrono::steady_clock::now();std::string sl="short ",sr="text";std::size_t standardTotal=0;auto c=std::chrono::steady_clock::now();for(int i=0;i<N;++i){std::string combined=sl+sr;standardTotal+=combined.size();}auto d=std::chrono::steady_clock::now();std::cout<<"Custom Text +: "<<std::chrono::duration<double,std::milli>(b-a).count()<<" ms, characters="<<customTotal<<'\n';std::cout<<"std::string +: "<<std::chrono::duration<double,std::milli>(d-c).count()<<" ms, characters="<<standardTotal<<'\n';}
