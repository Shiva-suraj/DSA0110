#include <iostream>
class Event {
    int rows, seats, booked;
    char** map;
public:
    Event(int r,int s) : rows(r<0?0:r), seats(s<0?0:s), booked(0), map(nullptr) {
        if(rows>0 && seats>0) {
            map=new char*[rows]; int made=0;
            try { for(;made<rows;++made) map[made]=new char[seats]{}; }
            catch(...) { while(made>0) delete[] map[--made]; delete[] map; map=nullptr; throw; }
        }
        std::cout<<"Created event "<<rows<<'x'<<seats<<'\n';
    }
    Event(const Event&)=delete;
    Event& operator=(const Event&)=delete;
    bool book(int r,int s) {
        if(!map || r<0 || r>=rows || s<0 || s>=seats || map[r][s]=='B') return false;
        map[r][s]='B'; ++booked; return true;
    }
    bool cancel(int r,int s) {
        if(!map || r<0 || r>=rows || s<0 || s>=seats || map[r][s]!='B') return false;
        map[r][s]=0; --booked; return true;
    }
    void show() const {
        for(int r=0;r<rows;++r) { for(int s=0;s<seats;++s) std::cout<<(map[r][s]=='B'?'B':'.')<<' '; std::cout<<'\n'; }
    }
    ~Event() {
        if(map) { for(int r=0;r<rows;++r) delete[] map[r]; delete[] map; }
        std::cout<<"Closed event; seats currently booked="<<booked<<'\n';
    }
};
int main() {
    Event morning(2,3); morning.book(0,1); morning.book(1,2); morning.cancel(0,1); morning.show();
    { Event workshop(1,2); workshop.book(0,0); }
    Event* evening=new Event(2,2); evening->book(1,1); delete evening;
    Event zero(0,5); zero.show();
}