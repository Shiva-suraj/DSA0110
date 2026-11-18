#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
class Time {
    int seconds;
public:
    explicit Time(int s=0):seconds(s<0?0:s){}
    Time& operator++(){++seconds;return *this;}
    Time operator++(int){Time old=*this;++seconds;return old;}
    bool operator==(const Time& x)const{return seconds==x.seconds;}
    bool operator<(const Time& x)const{return seconds<x.seconds;}
    friend std::ostream& operator<<(std::ostream& o,const Time& t){
        int h=t.seconds/3600,m=(t.seconds/60)%60,s=t.seconds%60;
        return o<<h<<':'<<(m<10?"0":"")<<m<<':'<<(s<10?"0":"")<<s;
    }
};
class Playlist {
    std::vector<std::string> tracks;
public:
    Playlist(std::initializer_list<std::string> x):tracks(x){}
    std::string& operator[](int i){if(i<0||i>=static_cast<int>(tracks.size()))throw std::out_of_range("playlist index out of range");return tracks[i];}
    const std::string& operator[](int i)const{if(i<0||i>=static_cast<int>(tracks.size()))throw std::out_of_range("playlist index out of range");return tracks[i];}
    int size()const{return static_cast<int>(tracks.size());}
};
int main(){
    Time t(3599);Time a=t++;Time b=++t;
    std::cout<<"a="<<a<<", b="<<b<<", t="<<t<<'\n';
    Time x(10),y(11);std::cout<<std::boolalpha<<"x<y: "<<(x<y)<<'\n';
    Time rollover(3599);++rollover;std::cout<<"Rollover: "<<rollover<<'\n';
    Playlist p{"Intro","Song A","Song B"};std::cout<<"Now playing: "<<p[1]<<'\n';
    p[1]="Remixed Song A";std::cout<<"Updated: "<<p[1]<<'\n';
    try{std::cout<<p[-1]<<'\n';}catch(const std::out_of_range& e){std::cout<<"Checked access: "<<e.what()<<'\n';}
    try{std::cout<<p[p.size()]<<'\n';}catch(const std::out_of_range& e){std::cout<<"End access: "<<e.what()<<'\n';}
}