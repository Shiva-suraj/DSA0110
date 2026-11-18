#include <iostream>
class OrderDemo {
    int first;
    int second;
public:
    // Intentional warning demonstration: actual order is declaration order.
    OrderDemo():second(20),first(second+1){std::cout<<"first="<<first<<", second="<<second<<'\n';}
};
int main(){OrderDemo x;}
