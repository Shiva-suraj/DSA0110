#include <iostream>
#include <stdexcept>
class Time{int h,m;
public:Time(int hh,int mm):h(hh),m(mm){if(hh<0||hh>23||mm<0||mm>59)throw std::invalid_argument("invalid time");}
friend inline int minutesBetween(const Time&,const Time&);
friend inline bool earlier(const Time&,const Time&);
};
inline int minutesBetween(const Time&a,const Time&b){int x=a.h*60+a.m,y=b.h*60+b.m;return x>y?x-y:y-x;}
inline bool earlier(const Time&a,const Time&b){return a.h<b.h||(a.h==b.h&&a.m<b.m);}
int main(){Time d(9,45),a(13,10);std::cout<<minutesBetween(d,a)<<' '<<std::boolalpha<<earlier(a,d)<<'\n';Time x(11,55),y(12,5),z(12,5);std::cout<<minutesBetween(x,y)<<' '<<earlier(x,y)<<'\n'<<minutesBetween(z,z)<<' '<<earlier(z,z)<<'\n';}