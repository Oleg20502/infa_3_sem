#include <iostream>
#include <map>
#include <string>

struct Date{
    unsigned int day;
    unsigned int month;
    unsigned int year;

    friend bool operator<(Date d1, Date d2)
    {
        if(d1.year < d2.year){
            return true;
        }
        else if(d1.year == d2.year){
            if(d1.month < d2.month){
                return true;
            }
            else if(d1.month == d2.month){
                if(d1.day < d2.day){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
};

int main()
{
    std::map<Date, unsigned int> data;
    int N;
    std::cin >> N;
    Date d;
    unsigned int a;
    std::string str;
    for(int i=0; i<N; ++i){
        std::cin >> str >> a;
        d.day = std::stoi(str.substr(0, 2));
        d.month = std::stoi(str.substr(3, 2));
        d.year = std::stoi(str.substr(6, 4));
        if(data.count(d)){
            if(data[d] < a){
                data[d] = a;
            }
        }
        else{
            data[d] = a;
        }
    }
    int M;
    std::cin >> M;
    for(int i=0; i<M; ++i){
        unsigned int max = 0;
        std::cin >> str;
        d.day = std::stoi(str.substr(0, 2));
        d.month = std::stoi(str.substr(3, 2));
        d.year = std::stoi(str.substr(6, 4));
        for(auto i=data.begin(); i!= data.upper_bound(d); ++i){
            if(max < (*i).second){
                max = (*i).second;
            }
        }
        std::cout << max << '\n';
    }
    return 0;
}
