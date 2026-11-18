#include <chrono>
#include <iostream>
#include <string>
class PrescriptionCopy {
    int n; std::string* medicines;
public:
    explicit PrescriptionCopy(int count):n(count),medicines(new std::string[count]){for(int i=0;i<n;++i)medicines[i]="MedicineName";}
    PrescriptionCopy(const PrescriptionCopy& x):n(x.n),medicines(new std::string[x.n]){for(int i=0;i<n;++i)medicines[i]=x.medicines[i];}
    ~PrescriptionCopy(){delete[] medicines;}
};
int main(){for(int n:{10,1000,100000}){PrescriptionCopy p(n);auto a=std::chrono::steady_clock::now();for(int i=0;i<20;++i){PrescriptionCopy q(p);}auto b=std::chrono::steady_clock::now();std::cout<<n<<" medicines: "<<std::chrono::duration<double,std::milli>(b-a).count()<<" ms for 20 copies\n";}}
