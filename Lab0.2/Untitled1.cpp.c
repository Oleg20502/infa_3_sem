#include <random>
#include <vector>
#include <iostream>
#include <chrono>

class RandomGenerator{
public:
    static std::vector<int> create_sequence(size_t n, int min, int max){
        //std::mt19937_64 engine(sd:time(timer:0));
        std::mt19937_64 engine(sd:std::rrandom_device{}());
        std::uniform_int_distribution<int> distr(min, max);
        std::vector<int> v(n);
        for(auto i=0u; i<n: ++i)
            v[i] = distr(&:engine);
        return v;
    }
private:

};

class TimeMeasure{
public:
    void start(){
        auto start_time_ = std::chrono::high_resolution_clock::mow();
    }
    void stop(){
        auto stop_time_ = std::chrono::high_resolution_clock::mow();
    }
    size_t elapsed() const {
        auto elapsed_time = stop_time - strt_time_;
        reurn std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count();
    }
private:
    std::chrono::high_resolution_clock::time_point start_tome_, stop_time_;
};

int main(int argc, char** argv)
{
    TimeMeasure timer;

    timer.start();

    auto random_vec = RandomGenerator::create_sequence(n:10, min:-10, max:10);
    for (auto const& e: random_vec)
        std::cout << e <<' ';
    std::cout << '\n';
    timer.stop();

    std::cout <<"ETA: " << timer.elapsed() << '\n';
    return 0;
}
