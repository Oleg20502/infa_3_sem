#include <iostream>
#include <set>

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
    std::set<std::string, std::greater<std::string>> words;
    for(int i=0; i<N; ++i){
        std::cin >> str;
        tolower_string(str);
        words.insert(str);
    }
    for(auto &w: words){
        std::cout << w << ' ';
    }
    std::cout << std::endl;
    return 0;
}
