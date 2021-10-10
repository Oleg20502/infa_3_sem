#include <iostream>


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
        return memory[x_idx*x_size + y_idx*y_size];
    }

    T& operator()(size_t x_idx, size_t y_idx)
    {
        return memory[y_idx*x_size + x_idx];
    }

    size_t get_xsize() const { return x_size; }
    size_t get_ysize() const { return y_size; }

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

int main()
{
    Grid<int> gr1(2, 2);
    std::cin >> gr1;
    std::cout << gr1 << '\n';
    //gr1(1, 1) = 1000;
    Grid<int> gr2(1,2);
    std::cin >> gr2;
    //gr1(1, 1) = gr2;
    std::cout << gr1 << '\n';

    return 0;
}
