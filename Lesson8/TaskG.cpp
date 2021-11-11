#include <iostream>
#include <stack>
#include <string>

int main()
{
    std::string a;
    int b, c;
    std::stack<int> numbers;
    while(std::cin >> a){
        if(a == "+"){
            b = numbers.top();
            numbers.pop();
            numbers.top() += b;
        }
        else if(a == "-" && a.size() == 1){
            b = numbers.top();
            numbers.pop();
            numbers.top() -= b;
        }
        else if(a == "*"){
            b = numbers.top();
            numbers.pop();
            numbers.top() *= b;
        }
        else if(a == "/"){
            b = numbers.top();
            numbers.pop();
            numbers.top() /= b;
        }
        else{
            numbers.push(std::stoi(a));
        }
    }
    std::cout << numbers.top();
    return 0;
}
