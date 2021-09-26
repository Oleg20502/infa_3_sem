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
    char a, b, c;
    int i;

    /*while(str.find(' ') != 18446744073709551615){
        str.erase(str.find(' '), 1);
    }*/

    b = '';
    for(auto i=0; i<str.size()-1, ++i){
        if (str[i] !=' '){
            a = str[i];
            if (0 <= a <= 9){

            }
        }
    }

    cout << str;

    return 0;
}
