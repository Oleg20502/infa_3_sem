#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::cout, std::cin, std::map, std::string;

int is_float(string str, int j)
{

}

int main()
{
    map<int, double> koef;
    std::string str;
    std::getline(cin, str);
    //cin >> str;
    char a, b, c, d;
    int i,s;

    while(str.find(' ') != 18446744073709551615){
        str.erase(str.find(' '), 1);
    }
    unsigned int size = str.size();

    a = str[0];
    if(size == 1){
        if(a == 'x')
            koef[1] = 1.0;
        else
            koef[0] = (int)(a);
    }
    else if (size == 2){
        b = str[1];
        if (0 <= a <= 9){
            if (0 <= b <= 9)
                koef[0] = static_cast<double> (10*((int)(a)) + (int)(b));
            else if(b =='.')
                koef[0] = static_cast<double> ((int)(a));
            else if(b == 'x')
                koef[1] = static_cast<double> ((int)(a));
        }
        else if(a == '+' || a == '-'){
            if(0 <= b <= 9)
                koef[0] = static_cast<double> (-(int)(b));
            else if(b == 'x')
                koef[1] = a == '+'? 1: -1;
        }
        else if(a == '.'){
            if(0 <= b <= 9)
                koef[0] = static_cast<double> ((int)(b))/10;
        }
    }
    else if (size == 3){
        b = str[1];
        c = str[2];
        if(a == '+' || a == '-'){
            if (0 <= b <= 9){
                if (0 <= c <= 9)
                    koef[0] = a == '+'? static_cast<double> (10*((int)(b)) + (int)(c))
                                      : -static_cast<double> (10*((int)(b)) + (int)(c));
                else if (c == '.')
                    koef[0] = a == '+'? static_cast<double> ((int)(b))
                                       :-static_cast<double> ((int)(b));
                else if (c == 'x')
                    koef[1] = a == '+'? static_cast<double> ((int)(b))
                                       :-static_cast<double> ((int)(b));
            }
            else if(b == '.' && 0 <= c <= 9)
                koef[0] = a == '+'? static_cast<double> ((int)(c))/10
                                   : -static_cast<double> ((int)(c))/10;
        }
        else if(0 <= a <= 9){
            if (0 <= b <= 9){
                if (0 <= c <= 9)
                    koef[0] = static_cast<double> (100*((int)(a)) + 10*((int)(b)) + (int)(c));
                else if(c == '.')
                    koef[0] = static_cast<double> (10*((int)(a)) + (int)(b));
                else if(c == 'x')
                    koef[1] = static_cast<double> (10*((int)(a)) + (int)(b));
            }
            else if(b == '+' || b == '-'){
                if (0 <= c <= 9)
                    koef[0] = static_cast<double> ((int)(a) + (int)(c));
                else if (c =='x')
                    koef[0] = static_cast<double> ((int)(a));
                    koef[1] = 1.0;
            }
            else if(b == '.'){
                if(0 <= c <= 9)
                    koef[0] = (int)(a) + static_cast<double> ((int)(c))/10;
                else if(c == 'x')
                    koef[1] = static_cast<double> ((int)(a));
            }
        }
        else if (a == '.'){
            if (0 <= b <= 9 && 0 <= c <= 9)
                koef[0] = static_cast<double> (10*((int)(b)) + (int)(c))/100;
            else if(0 <= b && b <= 9 && c == 'x')
                koef[1] = static_cast<double> ((int)(b))/10;
        }
        else if (a == 'x' && b == '^' && 0 <= c <= 9)
            koef[(int)(c)] = 1;
    }

    for(auto i = 2; i < size; ++i){
        c = str[i];
        if (0 <= a <= 9){
            if (b == 'x' || (b == '.' && c == 'x')) {

            }
        }
    }
    cout << str;

    return 0;
}
