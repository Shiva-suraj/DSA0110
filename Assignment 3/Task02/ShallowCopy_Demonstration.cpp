#include <iostream>
class Shallow {
    int* data;
public:
    Shallow():data(new int(42)){}
    ~Shallow(){delete data;}
    int value()const{return *data;}
};
int main(){Shallow a;Shallow b=a;std::cout<<a.value()<<' '<<b.value()<<'\n';}
// Intentional unsafe example: both objects delete the same pointer.
