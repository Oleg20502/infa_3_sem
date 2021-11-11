#include <iostream>
#include <set>
#include <string>

void tolower_string(std::string &str)
{
    for(int i=0; i<str.size(); ++i){
        str[i] = std::tolower(str[i]);
    }
}

int main()
{
    int N;
    std::cin >> N;
    std::string str;
    std::multiset<std::string> dict;
    for(int i=0; i<N; ++i){
        std::cin >> str;
        tolower_string(str);
        dict.insert(str);
    }
    std::string s;
    int max = 0;
    int c;
    for(auto const &d: dict){
        c = dict.count(d);
        if(c >= max){
            max = c;
            s = d;
        }
    }
    std::cout << s << ' ' << max;
    return 0;
}
