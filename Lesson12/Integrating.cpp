#include <iostream>
#include <cmath>
#include <chrono>
#include <string>

template<typename F>
double integrate(F func, double a, double b, double dx=0.001)
{
    double sum = 0.0;
    long long int I = 0;
    for(double i=a; i<b; i += dx){
        ++I;
        sum += func(i+dx) + func(i);
    }
    sum *= 0.5*(b-a)/I;
    return sum;
}

class Time_measure{
public:
    template<typename F1, typename F2>
    static double measure(int N, std::string str, F1 func1, F2 func2, double a, double b, double dx=0.001)
    {
        std::cout << str << ' ';
        auto t1 = std::chrono::high_resolution_clock::now();
        for(int i=0; i<N; ++i){
            func1(func2, a, b, dx);
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::milliseconds> (t2-t1);
        std:: cout << (1.0*time.count())/N << '\n';
        return (1.0*time.count())/N;
    }
};

double polinom(double x)
{
    return std::pow(x, 3) + std::pow(x, 2);
}

double sinus(double x)
{
    return std::sin(100000*x);
}

double foo(double x)
{
    int sum = 0;
    for(int i=0; i<(int)x ; ++i){
        sum += i;
    }
    return std::sqrt(sum);
}

int main()
{
    //auto result = std::async()

    std::cout << integrate(foo, 0.0, 100.0, 0.001) << '\n';

    Time_measure::measure(1000, "polinom", integrate<decltype(polinom)>, polinom, 0.0, 1.0);

    Time_measure::measure(10, "sinus", integrate<decltype(sinus)>, sinus, 0.0, 1.0, 0.000001);

    Time_measure::measure(10, "foo", integrate<decltype(foo)>, foo, 0.0, 20.0, 0.001);
    return 0;
}
