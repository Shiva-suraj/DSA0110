#include <iostream>
#include <iomanip>
class SavingsAccount{
 long long accountNumber;double balance;double transactions[10]{};int count=0,next=0;
 void addTransaction(double x){transactions[next]=x;next=(next+1)%10;if(count<10)++count;}
public:
 SavingsAccount(long long n,double b):accountNumber(n),balance(b){}
 bool deposit(double x){if(x<=0)return false;balance+=x;addTransaction(x);return true;}
 bool withdraw(double x);
 void miniStatement()const;
 double getBalance()const{return balance;}
};
bool SavingsAccount::withdraw(double x){if(x<=0||x>balance)return false;balance-=x;addTransaction(-x);return true;}
void SavingsAccount::miniStatement()const{std::cout<<"Account: "<<accountNumber<<"\nBalance: Rs "<<std::fixed<<std::setprecision(2)<<balance<<"\nRecent transactions (oldest to newest):\n";int start=count==10?next:0;for(int i=0;i<count;++i)std::cout<<i+1<<". "<<(transactions[(start+i)%10]>=0?"+":"")<<transactions[(start+i)%10]<<'\n';}
int main(){SavingsAccount a(100245,1000);a.deposit(200);a.withdraw(50);for(int i=1;i<=10;++i)a.deposit(i*10);a.withdraw(25);a.miniStatement();std::cout<<"Invalid withdrawal accepted: "<<std::boolalpha<<a.withdraw(999999)<<'\n';}