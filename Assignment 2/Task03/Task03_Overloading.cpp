#include <iostream>
#include <iomanip>
struct Parcel{double kilograms;bool express;bool insured;};
double charge(double kg,bool express=false,bool insured=false){double total=40+kg*20;if(express)total+=30;if(insured)total+=15;return total;}
double charge(int grams){return charge((double)grams/1000,false,false);}
double charge(float kg){return charge((double)kg,false,false);}
double charge(const Parcel& p){return charge(p.kilograms,p.express,p.insured);}
int main(){std::cout<<std::fixed<<std::setprecision(2);std::cout<<"charge(2) [int grams]: "<<charge(2)<<'\n'<<"charge(2.0) [double kg]: "<<charge(2.0)<<'\n'<<"charge(2.0f) [float kg]: "<<charge(2.0f)<<'\n'<<"charge(1500) [int grams]: "<<charge(1500)<<'\n'<<"charge(2.5, true) [double + express]: "<<charge(2.5,true)<<'\n';Parcel p{3.0,true,true};std::cout<<"charge(Parcel): "<<charge(p)<<'\n';}