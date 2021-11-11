#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <cmath>

class HashMap{
private:
    static const int capacity = 100000;

    std::array<std::list<std::pair<int, unsigned int>>, capacity> H;

    int hash(int a, int rand)
    {
        return std::abs(a * rand + 1) % capacity;
    }

public:
    HashMap() {}

    void add(int key, unsigned int value)
    {
        bool if_add = true;
        int h = hash(key, 1);
        for(auto i=H[h].begin(); i!=H[h].end(); ++i){
            if((*i).first == key){
                (*i).second = value;
                if_add = false;
                break;
            }
        }
        if(if_add){
            std::pair<int, unsigned int> p{key, value};
            H[h].push_back(p);
        }
    }

    unsigned int get(int key, unsigned int value)
    {
        int h = hash(key, 1);
        for(auto i=H[h].begin(); i!=H[h].end(); ++i){
            if((*i).first == key){
                return (*i).second;
            }
        }
        return value;
    }

    void pop(int key)
    {
         int h = hash(key, 1);
         for(auto i=H[h].begin(); i!=H[h].end(); ++i){
             if ((*i).first == key){
                H[h].erase(i);
                break;
             }
         }
    }
};

int main()
{
    int N, M;
    std::cin >> N >> M;
    std::vector<HashMap> Hash(N);
    int I, key;
    unsigned int value;
    char s;
    for(int i=0; i<M; ++i){
        std::cin >> I >> s >> key >> value;
        if (s == '+'){
            Hash[I].add(key, value);
        }
        else if(s == '-'){
            Hash[I].pop(key);
        }
        else if(s == '?'){
            std::cout << Hash[I].get(key, value) << '\n';
        }
    }
    return 0;
}
