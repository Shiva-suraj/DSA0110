double charge(double weight);
double charge(double weight,bool express);
double charge(double weight,bool express=false,bool insured=false);
int main(){return static_cast<int>(charge(2.0));}