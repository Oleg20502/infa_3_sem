#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>

using std::cout, std::cin, std::map, std::string, std::pow;

int main()
{
    map<int, double> koef;
    std::string str;
    std::getline(cin, str);
    std::vector<std::string> polinom;

    while(str.find(' ') != 18446744073709551615){
        str.erase(str.find(' '), 1);
    }

    if (str.back() != '+' && str.back() != '-')
        str.push_back('+');

    unsigned int size = str.size();
    int j = 0;
    for (int i = 1; i < size; ++i){
        if (str[i] == '+' || str[i] == '-'){
            polinom.push_back(str.substr(j, i-j));
            j = i;
        }
    }

    int point = 0, is_x = 0, power = 0;
    double sum = 0.0, sign = 1.0;
    for (auto &s: polinom){
        if(s[0] == '+'){
            s.erase(0, 1);
            sign = 1.0;
        }
        else if (s[0] != '-'){
            sign = 1.0;
        }
        else{
            s.erase(0, 1);
            sign = -1.0;
        }
        size = s.size();
        for(int i=0; i<size; ++i){
            if (0 <= (int)(s[i]) - 48 && (int)(s[i]) - 48 <= 9){
                if (is_x == 0){
                    if (point == 0){
                        sum *= 10;
                        sum += (int)(s[i])-48;
                    }
                    else{
                        sum+= static_cast<double> ((int)(s[i])-48)/pow(10, point);
                        ++point;
                    }
                }
                else{
                    power *= 10;
                    power += (int)(s[i])-48;
                }
            }
            else if (s[i] == '.'){
                point = 1;
            }
            else if (s[i] == 'x'){
                point = 0;
                is_x = 1;
                if (sum == 0.0){
                    sum = 1.0;
                }
                if(i == size-1){
                    power = 1;
                }
            }
        }
        if (koef.count(power)){
            koef[power] += sign * sum;
        }
        else{
            koef[power] = sign * sum;
        }
        sum = 0;
        power = 0;
        point = 0;
        is_x = 0;
    }

    std::vector<int> powers;
    for (auto &[key, val]: koef){
        if (val != 0)
            cout << key << ' ' << val << '\n';
        powers.push_back(key);
    }

    //-x+x^2 -   x^   2 + 10

    return 0;
}

