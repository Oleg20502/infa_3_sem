#include <iostream>
#include <stack>
#include <cmath>

int main()
{
    int a;
    std::cin >> a;
    std::stack<int> st;
    while(a != 0){
        if(a > 0){
            st.push(a);
        }
        else if(st.size() > 0){
            if(std::abs(a) < std::abs(st.top())){
                st.top() += a;
            }
            else{
                st.pop();
            }
        }
        std::cin >> a;
    }
    int t = -1;
    if (st.size() > 0){
        t = st.top();
    }
    std::cout << st.size() << ' ' << t;
    return 0;
}
