#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
#include <fstream>
#include <string>


class TimeMeasure{
public:
    void start()
    {
        start_time_ = std::chrono::high_resolution_clock::now();
    }
    void stop()
    {
        stop_time_ = std::chrono::high_resolution_clock::now();
    }
     double elapsed()
    {
        auto elapsed_time = stop_time_ - start_time_;
        return std::chrono::duration_cast<std::chrono::milliseconds> (elapsed_time).count();
    }

private:
    std::chrono::high_resolution_clock::time_point start_time_, stop_time_;
};


template<typename container, typename T>
double measure_time(bool regime, int N, int iter)
{
    container arr;
    arr.resize(N);
    arr.insert(arr.end(), (T)0);
    typename std::vector<T>::iterator I;
    if (regime){
        I = std::next(arr.begin());
    }
    else{
        I = arr.end();
    }
    TimeMeasure Tm;
    Tm.start();
    for(int i=0; i<iter; ++i){
        arr.insert(I, (T)0);
    }
    Tm.stop();
    return static_cast<double> (Tm.elapsed());
}

template<typename container, typename T>
void measure(bool regime, std::vector<int> num, int iter, std::string path)
{
    std::ofstream out(path);
    if (out.is_open()){
        for(int i=0; i<num.size(); ++i){
            out << num[i] << ' ' << measure_time<container, T>(regime, num[i], iter)/iter << '\n';
        }
    }
    std::cout << path << " updated\n";
}



int main()
{
    std::cout << "Started\n";
    std::vector<int> N_end = {1000000, 1200000, 1400000, 1600000, 1800000, 2000000};
    std::vector<int> N_m = {100000, 200000, 300000, 400000, 500000,
                             600000, 700000, 800000, 900000, 1000000};
    measure<std::vector<int>, int> (false, N_end, 20000, "Vector_end.txt");
    measure<std::vector<int>, int> (false, N_end, 20000, "Deque_end.txt");
    measure<std::vector<int>, int> (true, N_m, 5000, "Vector_middle.txt");
    measure<std::vector<int>, int> (true, N_m, 5000, "Deque_middle.txt");
    std::cout << "Finished\n";
    return 0;
}
