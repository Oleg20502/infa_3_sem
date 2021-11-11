#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

template<typename type, typename type_it>
inline
type sum(type_it beg, type_it end)
{
    type sum = 0;
    for(auto i=beg; i!= end; ++i){
        sum += *i;
    }
    return sum;
}

int main()
{
    int N;
    int S;
    std::cin >> N;
    std::vector<int> nums(N, 0);
    for(auto i=0; i<N; ++i){
        std::cin >> nums[i];
    }
    std::cin >> S;
    sort(nums.begin(), nums.end());
    std::vector<int> four(4, 0);
    std::set<std::vector<int>> fours;
    for(int i=0; i<N-3; ++i){
        for(int j=i+1; j<N; ++j){
            for(int k=j+1; k<N; ++k){
                for(int m=k+1; m<N; ++m){
                    four[0] = nums[i];
                    four[1] = nums[j];
                    four[2] = nums[k];
                    four[3] = nums[m];
                    if(sum<int>(four.begin(), four.end()) == S){
                        fours.insert(four);
                    }
                }
            }
        }
    }
    for(auto f:fours){
        std::cout << f[0] <<' '<< f[1] <<' '<<
                                   f[2]<<' '<< f[3] <<'\n';
    }
    return 0;
}
