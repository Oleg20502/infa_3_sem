#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>

using std::cout, std::cin, std::map, std::string, std::pow, std::abs;

string create_spaces(int val)
{
    string s(val, ' ');
    return s;
}

int count_length(double val)
{
    string s = std::to_string(val);
    if(s.find('.') != string::npos)
        while(s.find('0', s.find('.')) != string::npos){
            s.erase(s.find('0', s.find('.')), 1);
        }
    s.erase(s.find('.'), 1);
    return s.size();
}

class Test {
public:
    template<typename T>
    static void test(T test_val, T correct_val, std::string message = "  ")
    {
        if (test_val == correct_val)
            std::cout << "OK" << '\n';
        else
            std::cout << "Error " << message << '\n';
    }

    static void test(std::string test_val, std::string correct_val, std::string message = "  ")
    {
        if (test_val.compare(correct_val) == 0)
            std::cout << "OK" << '\n';
        else
            std::cout << "Error " << message << '\n';
    }
};

void test_count_length()
{
    Test::test(count_length(0), 1, "length of 0 is 1");
    Test::test(count_length(123), 3, "length of 123 is 3");
    Test::test(count_length(123.), 3, "length of 123. is 3");
    Test::test(count_length(123.0000), 3, "length of 123.0000 is 3");
    Test::test(count_length(123.4), 4, "length of 123.4 is 4");
    Test::test(count_length(-123.), 4, "length of -123. is 4");
    Test::test(count_length(-123.4), 5, "length of -123.4 is 5");
    Test::test(count_length(12300), 5, "length of 12300 is 5");
    Test::test(count_length(12300.4), 6, "length of 12300.4 is 6");
    Test::test(count_length(12300.0), 5, "length of 12300.0 is 5");
}

void test_create_spaces()
{

    Test::test(create_spaces(10), "          ", "length is 10");
    Test::test(create_spaces(3), "   ", "length is 3");
}

int main()
{
    test_count_length();
    test_create_spaces();

    map<int, double> koef;
    std::string str;
    std::getline(cin, str);
    std::vector<std::string> polinom;

    while(str.find(' ') != std::string::npos){
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

    std::vector<double> values;
    std::vector<int> powers;
    for (auto &[key, val]: koef){
        if (val != 0){
            values.push_back(val);
            powers.push_back(key);
        }
    }
    cout << '|';
    int length1, length2;
    string spaces1, spaces2;
    for(auto i=0; i<powers.size(); ++i){
        length1 = count_length(powers[i]);
        length2 = count_length(values[i]);
        if(2 + length1 <= length2){
            spaces1 = create_spaces((length2 - length1-2)/2);
            spaces2 = create_spaces((length2 - length1-2)/2 + (length2-length1)%2);
        }
        else
            spaces1 = spaces2 = "";
        cout << ' ' << spaces1 << "x^" << powers[i] << spaces2 << " |";
    }
    cout << '\n' << '|';
    for(auto i=0; i<powers.size(); ++i){
        length1 = count_length(powers[i]);
        length2 = count_length(values[i]);
        if(2 + length1 > length2){
            spaces1 = create_spaces((2 + length1 - length2)/2);
            spaces2 = create_spaces((2 + length1 - length2)/2 + abs(length1 - length2)%2);
        }
        else
            spaces1 = spaces2 = "";
        cout << ' ' << spaces1 << values[i] << spaces2 << " |";
    }
    cout << '\n';

    //x^2 + 3000x^4 + 2x + 8
    //-x+x^2 -   x^   2 + 10
    //-2x - 5x^4 - 8x^2 - 4567x^1 - 1234x^1234

    return 0;
}

