#include <iostream>
#include <vector>
#include <deque>
#include <functional>


template<class InputIt, class UnaryOp, class T, class BinaryOp>
T transform_reduce(InputIt first, InputIt last,
                   UnaryOp unary_op, T init, BinaryOp binary_op)
{
    for(auto it = first; it != last; ++it){
        init = binary_op(init, unary_op(*it));
    }
    return init;
}

int sum(int a, int b)
{
    return a+b;
}

int id(int a)
{
    return a;
}


class Test {
public:
    template<typename T1, typename T2>
    static void test(T1 test_val, T2 correct_val, std::string message = "  ")
    {
        if (test_val == correct_val)
            std::cout << "OK" << '\n';
        else
            std::cout << "Error " << message << '\n';
    }

    static void test(std::string test_val, std::string correct_val, std::string message = "  ")
    {
        if (test_val.compare(correct_val) == 0)
            std::cout << "OK" << '\n';
        else
            std::cout << "Error " << message << '\n';
    }
};


void test_transform_reduce()
{
    std::function<int(int, int)> P_sum = sum;
    std::function<int(int)> P_id = id;
    std::vector<int> vec = {1, 2, 4, 2, 9};
    std::deque<double> deq = {32.53, 65.91, 90.32, 0.0, 5.3, 9.0};
    Test::test(transform_reduce(vec.begin(), vec.end(), P_id, 0, P_sum), 18, "Correct: 18");
    Test::test(transform_reduce(vec.begin(), vec.end(), [](int x) {return x*x;} , 1, P_sum), 107, "Correct: 107");
    Test::test(transform_reduce(deq.begin(), deq.end(), [](double x) {return 2*x;}, 1,
                  [](double x, double y){return x*y;}), 0.0, "Correct: 0.0");
}

int main()
{
    test_transform_reduce();

    return 0;
}

