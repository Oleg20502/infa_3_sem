#include <iostream>
#include <string>
#include <vector>
#include <list>

class HashMap{
private:
    static const int capacity = 1000000;

    std::vector<std::list<std::pair<int, unsigned int>>> H;

    int hash(int a, int rand)
    {
        if(a > 0){
            return (a * rand) % capacity;
        }
        else{
            return (-a * rand) % capacity;
        }
    }

public:
    HashMap():H{std::vector<std::list<std::pair<int, unsigned int>>> (capacity)} {}

    void add(int key, unsigned int value)
    {
        bool if_add = true;
        int h = hash(key, key+1);
        std::pair<int, unsigned int> p{key, value};
        for(auto i=H[h].begin(); i!=H[h].end(); ++i){
            if((*i).first == key){
                (*i).second = value;
                if_add = false;
                break;
            }
        }
        if(if_add){
            H[h].emplace_back(p);
        }
    }

    unsigned int get(int key, unsigned int value)
    {
        int h = hash(key, key+1);
        for(auto i=H[h].begin(); i!=H[h].end(); ++i){
            if((*i).first == key){
                return (*i).second;
            }
        }
        return value;
    }

    unsigned int pop(int key)
    {
         int h = hash(key, key+1);
         unsigned int elem = 0;
         for(auto i=H[h].begin(); i!=H[h].end(); ++i){
             if ((*i).first == key){
                elem = (*i).second;
                H[h].erase(i);
                return elem;
             }
         }
         return elem;
    }
};

int main()
{
    int N, M;
    std::cin >> N >> M;
    std::vector<HashMap> H(N);
    int I, key;
    unsigned int value;
    char s;
    for(int i=0; i<M; ++i){
        std::cin >> I >> s >> key >> value;
        if (s == '+'){
            H[I].add(key, value);
        }
        else if(s == '-'){
            H[I].pop(key);
        }
        else if(s == '?'){
            std::cout << H[I].get(key, value) << '\n';
        }
    }
    return 0;
}
