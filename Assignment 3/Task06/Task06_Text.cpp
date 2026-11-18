#include <cstring>
#include <iostream>
class Text {
    char* data;
public:
    Text(const char* s=""){if(!s)s="";data=new char[std::strlen(s)+1];std::strcpy(data,s);}
    Text(const Text& x):data(new char[std::strlen(x.data)+1]){std::strcpy(data,x.data);}
    Text& operator=(const Text& x){
        if(this!=&x){char* fresh=new char[std::strlen(x.data)+1];std::strcpy(fresh,x.data);delete[] data;data=fresh;}
        return *this;
    }
    ~Text(){delete[] data;}
    Text operator+(const Text& x)const{
        std::size_t n=std::strlen(data)+std::strlen(x.data);
        char* joined=new char[n+1];std::strcpy(joined,data);std::strcat(joined,x.data);
        Text result(joined);delete[] joined;return result;
    }
    bool operator==(const Text& x)const{return std::strcmp(data,x.data)==0;}
    bool operator!=(const Text& x)const{return !(*this==x);}
    friend std::ostream& operator<<(std::ostream& o,const Text& x){return o<<x.data;}
};
int main(){
    Text a("Hello "),b("World"),c("!");Text message=a+b+c;std::cout<<message<<'\n';
    Text empty;Text copy=empty;std::cout<<"Empty text: ["<<copy<<"]\n";
    a=a;std::cout<<"Self assignment: "<<a<<'\n';
    Text same("Hello ");std::cout<<std::boolalpha<<"a==same: "<<(a==same)<<", a!=b: "<<(a!=b)<<'\n';
    Text longMessage("This is a longer message used to test dynamic character storage safely.");std::cout<<longMessage<<'\n';
}