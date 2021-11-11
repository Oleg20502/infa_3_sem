#include <iostream>
#include <deque>

int main()
{
    int N;
    char symbol;
    int n;
    std::cin >> N;
    std::deque<int> q;
    for(int i=0; i<N; ++i){
        std::cin >> symbol;
        if(symbol == '-'){
            n = q[0];
            q.pop_front();
            std::cout << n << '\n';;
        }
        else if(symbol == '+'){
            std::cin >> n;
            q.push_back(n);
        }
        else if(symbol == '*'){
            std::cin >> n;
            auto I = q.begin();
            std::advance(I, q.size()/2 + q.size()%2);
            q.insert(I, n);
        }
    }
    return 0;
}
