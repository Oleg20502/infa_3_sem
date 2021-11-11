#include <iostream>
#include <set>

int main()
{
    int N, a;
    std::cin >> N;
    std::set<int> numbers;
    for(int i=0; i<N; ++i){
        std::cin >> a;
        numbers.insert(a);
    }
    std::cout << numbers.size();
    return 0;
}
