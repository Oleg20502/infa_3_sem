#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

struct Activity{
    float min;
    float max;
    int cnt;
};

bool compare(std::pair<int, float> const & p1, std::pair<int, float> const & p2)
{
    if(p1.second < p2.second){
        return true;
    }
    else{
        return false;
    }
}

int main()
{
    int N, time, id;
    float tmp1, tmp2, tmp3, tmp4, na;
    std::map<int, Activity> data;
    Activity A;
    std::cin >> N;
    for(int i=0; i<N; ++i){
        std::cin >> time >> id >> tmp1 >> tmp2 >> tmp3 >> na >> tmp4;
        if(data.count(id)){
            ++data[id].cnt;
            if(data[id].min > na){
                data[id].min = na;
            }
            else if(data[id].max < na){
                data[id].max = na;
            }
        }
        else{
            A.min = A.max = na;
            A.cnt = 1;
            data[id] = A;
        }
    }
    std::vector<std::pair<int, float>> new_data;
    std::pair<int, float> p;
    for(auto i=data.begin(); i!=data.end(); ++i){
        if((*i).second.cnt > 1){
            p.first = (*i).first;
            p.second = (*i).second.max - (*i).second.min;
            new_data.push_back(p);
        }
    }
    std::sort(new_data.begin(), new_data.end(), compare);
    std::vector<int> show_data;
    int tmp = 0;
    for(auto i=new_data.begin(); i!=new_data.end(); ++i){
        if(tmp>=3){
            break;
        }
        show_data.push_back((*i).first);
        ++tmp;
    }
    std::sort(show_data.begin(), show_data.end());
    if(tmp == 0){
        std::cout << -1 << '\n';
    }
    else{
        for(int i=0; i<tmp; ++i){
            std::cout << show_data[i] <<' ';
        }
    }
    return 0;
}
