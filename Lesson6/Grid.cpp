#include <iostream>
#include <string>


template<typename T>
class Grid{
private:
    T* memory;
    size_t x_size, y_size;

public:
    Grid(size_t x_size, size_t y_size): memory{ new T[x_size * y_size]}, x_size{x_size}, y_size{y_size} { }

    ~Grid()
    {
        x_size = y_size = 0;
        delete [] memory;
    }

    T operator()(size_t x_idx, size_t y_idx) const
    {
        return memory[y_idx*x_size + x_idx];
    }

    T& operator()(size_t x_idx, size_t y_idx)
    {
        return memory[y_idx*x_size + x_idx];
    }

    size_t get_xsize() const {return x_size;}
    size_t get_ysize() const {return y_size;}

    Grid& operator=(T value)
    {
        for(int i=0; i<x_size*y_size; ++i)
            memory[i] = value;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, Grid const& g)
    {
        for(int i=0; i < g.x_size*g.y_size-1; ++i)
            out << g.memory[i] <<' ';
        out << g.memory[g.x_size*g.y_size-1];
        return out;
    }

    friend std::istream& operator>>(std::istream& out, Grid& g)
    {
        for(int i=0; i < g.x_size * g.y_size; ++i)
            out >> g.memory[i];
        return out;
    }
};


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

void test_grid()
{
    Grid<int> gr1(2, 3);
    Test::test(gr1.get_xsize(), 2, "x_size = 2");
    Test::test(gr1.get_ysize(), 3, "y_size = 3");
    gr1 = 1;
    Test::test(gr1(0,0), 1, "gr1(0,0) = 1");
    Test::test(gr1(0,1), 1, "gr1(0,1) = 1");
    Test::test(gr1(1,1), 1, "gr1(1,1) = 1");
    Grid<double> gr2(3, 3);
    gr2(0, 0) = -1.0;
    gr2(1, 0) = 3.345;
    gr2(0, 1) = gr2(1, 1) = gr2(1, 2) = -45.654;
    gr2(0, 2) = 20.20;
    Test::test(gr2(0,0), -1.0, "gr2(0,0) = 11.0");
    Test::test(gr2(1,1), -45.654, "gr2(1,1) = -45.654");
    Test::test(gr2(1,2), -45.654, "gr2(1,1) = -45.654");
    Test::test(gr2(0,2), 20.20, "gr2(0,2) = 20.20");
}

int main()
{
    test_grid();
//    Grid<int> gr1(2, 2);
//    std::cin >> gr1;
//    std::cout << gr1 << '\n';
//    //gr1(1, 1) = 1000;
//    Grid<int> gr2(1,2);
//    std::cin >> gr2;
//    //gr1(1, 1) = gr2;
//    std::cout << gr1 << '\n';

    return 0;
}
