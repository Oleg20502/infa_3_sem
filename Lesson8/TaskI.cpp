#include <iostream>
#include <string>
#include <bitset>

class Checker{
public:
    Checker()
    {
        H.reset();
    }

    void Add(const std::string& s)
    {
        //int h1 = hash(s, 11);
        int h1 = std::hash<std::string>{}(s)%capacity;
        H[h1] = true;
    }

    bool Exists(const std::string& s)
    {
        //int h1 = hash(s, 11);
        int h1 = std::hash<std::string>{}(s)%capacity;
        if(H.test(h1) == true){
            return true;
        }
        else{
            return false;
        }
    }

private:
    static const long long int capacity = 10000000;
    std::bitset<capacity> H;

    int hash(std::string const& str, int rand)
    {
        int p0 = 3;
        int p = 1;
        int c = 1;
        int h = 0;
        for(char s: str){
            h += (int)s * p;
            p *= p0;
            ++c;
        }
        h *= rand;
        h = h%capacity;
        return h;
    }
};



int main()
{
    Checker ch;
    ch.Add("AAA");
    ch.Add("BBB");
    std::cout << ch.Exists("BBB.") << '\n';
    return 0;
}
