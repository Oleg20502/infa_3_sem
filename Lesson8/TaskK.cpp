#include <iostream>
#include <set>
#include <vector>
#include <array>
#include <algorithm>

class Comp{
public:
    bool operator()(std::array<int, 4> const &arr1, std::array<int, 4> const &arr2)
    {
        if(arr1[2] > arr2[2]){
        return true;
    }
    else if(arr1[2] == arr2[2] && arr1[3] > arr2[3]){
        return true;
    }
    else if(arr1[2] == arr2[2] && arr1[3] == arr2[3] &&
            arr1[0]*arr1[0] + arr1[1]*arr1[1] <
            arr2[0]*arr2[0] + arr2[1]*arr2[1]){
            return true;
    }
    else{
        return false;
        }
    }

};


int main()
{
    int N;
    std::cin >> N;
    int X, Y, B;
    std::multiset<std::array<int, 3>> points;
    std::array<int, 3> point;
    std::array<int, 4> line;
    for(int i=0; i<N; ++i){
        std::cin >> X >> Y >> B;
        if(B >= 10 || X*X + Y*Y <= 10000){
            point[0] = X;
            point[1] = Y;
            point[2] = B;
            points.insert(point);
        }
    }
    const int n = points.size();
    std::set<std::array<int, 4>, Comp> points_with_count;
    int i = 0;
    for(auto &p: points){
        line[0] = p[0];
        line[1] = p[1];
        line[2] = p[2];
        line[3] = points.count(p);
        points_with_count.insert(line);
        ++i;
    }
    for(const auto &p: points_with_count){
        std::cout << p[0] << ' '<< p[1] << ' ' <<
                  p[2] << '\n';
    }

    return 0;
}
