#include <iostream>
#include <vector>
#include <stdexcept>
int& highestMark(int a[],int n){if(n<=0)throw std::invalid_argument("empty");int b=0;for(int i=1;i<n;++i)if(a[i]>a[b])b=i;return a[b];}
const int& highestMarkReadOnly(const int a[],int n){if(n<=0)throw std::invalid_argument("empty");int b=0;for(int i=1;i<n;++i)if(a[i]>a[b])b=i;return a[b];}
int highestMarkCopy(const int a[],int n){if(n<=0)throw std::invalid_argument("empty");int b=0;for(int i=1;i<n;++i)if(a[i]>a[b])b=i;return a[b];}
int highestIndex(const std::vector<int>& a){if(a.empty())throw std::invalid_argument("empty");int b=0;for(int i=1;i<(int)a.size();++i)if(a[i]>a[b])b=i;return b;}
int* highestPointer(std::vector<int>& a){if(a.empty())return nullptr;return &a[highestIndex(a)];}
int main(){int m[]={78,92,85,88,91};int n=sizeof(m)/sizeof(m[0]);std::cout<<"Highest before moderation: "<<highestMark(m,n)<<'\n';highestMark(m,n)+=2;std::cout<<"After +2 moderation: "<<highestMark(m,n)<<'\n';std::cout<<"Read-only highest: "<<highestMarkReadOnly(m,n)<<'\n';std::cout<<"Returned copy: "<<highestMarkCopy(m,n)<<'\n';std::vector<int> v={70,94,81};int ix=highestIndex(v);int* p=highestPointer(v);std::cout<<"Index before growth: "<<ix<<", value: "<<v[ix]<<'\n'<<"Pointer before growth: "<<*p<<'\n';int saved=v[ix];v.reserve(v.capacity()+10);std::cout<<"After reserve, index remains valid: "<<v[ix]<<", saved value: "<<saved<<'\n'<<"Pointer/reference obtained before growth may be invalid; do not dereference it.\n";}