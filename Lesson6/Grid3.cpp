#include <iostream>
#include <string>


template<typename T>
class MultiGrid{
private:
    bool if_subgrid = false;
    MultiGrid* memory;
    T data;
    size_t x_size, y_size;

public:
    MultiGrid(): memory{nullptr}, x_size{1}, y_size{1} {}

    MultiGrid(T val): memory{nullptr}, data{val}, x_size{1}, y_size{1} {}

    MultiGrid(size_t x_size, size_t y_size): memory{ new MultiGrid[x_size * y_size]},
                                            x_size{x_size}, y_size{y_size}, if_subgrid{true}, data{(T)0} {}

    ~MultiGrid()
    {
        x_size = y_size = 0;
        delete [] memory;
    }

    T operator()(size_t x_idx, size_t y_idx) const
    {
        const MultiGrid g = memory[y_idx*x_size + x_idx];
        if(g.is_subgrid() == false ||
             (g.get_xsize() == 1 && g.get_ysize() == 1)){
            return g.get_data();
        }
        else{
            T sum = (T)0;
            int I = 0;
            for(int i=0; i<g.get_xsize(); ++i){
                for(int j=0; j<g.get_ysize(); ++j){
                    ++I;
                    sum += g(i, j);
                }
            }
            return sum/I;
        }
    }

    MultiGrid& operator()(size_t x_idx, size_t y_idx)
    {
        return memory[y_idx*x_size + x_idx];
    }

    size_t get_xsize() const {return x_size;}
    size_t get_ysize() const {return y_size;}

    MultiGrid& operator=(T value)
    {
        if(if_subgrid == false){
            data = value;
        }
        else{
            for(auto i=0; i<x_size*y_size; ++i){
                memory[i] = value;
            }
        }
        return *this;
    }

    MultiGrid& operator=(MultiGrid &g)
    {
        delete [] memory;
        if (g.is_subgrid() == false){
            //memory = nullptr;
            data = g.get_data();
            if_subgrid = false;
        }
        else{
            x_size = g.get_xsize();
            y_size = g.get_ysize();
            if_subgrid = true;
            memory = new MultiGrid[x_size*y_size];
            for(auto i=0; i<x_size; ++i){
                for(auto j=0; j<y_size; ++j){
                    memory[j*x_size + i] = g(i, j);
                }
            }
        }
        return *this;
    }

    T get_data() const {return data;}

    bool is_subgrid() const {return if_subgrid;}

    MultiGrid& make_subgrid(size_t x_idx, size_t y_idx, size_t x_sub_size, size_t y_sub_size)
    {
        MultiGrid g(x_sub_size, y_sub_size);
        if (memory[y_idx*x_size + x_idx].is_subgrid() == false){
            g = memory[y_idx*x_size + x_idx].get_data();
        }
        memory[y_idx*x_size + x_idx] = g;
        return *this;
    }

    MultiGrid& collapse_subgrid(size_t x_idx, size_t y_idx, size_t x_sub_size, size_t y_sub_size)
    {
        if (memory[y_idx*x_size + x_idx].is_subgrid() == true){
            MultiGrid g((static_cast<const MultiGrid> (*this))(x_idx, y_idx));
            memory[y_idx*x_size + x_idx] = g;
        }
        return *this;
    }

    MultiGrid& get_subgrid(size_t x_idx, size_t y_idx) {return memory[y_idx*x_size + x_idx];}
    MultiGrid const& get_subgrid(size_t x_idx, size_t y_idx) const {return memory[y_idx*x_size + x_idx];}
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


void test_UniGrid()
{
    MultiGrid<int> gr1(3, 3);
    Test::test(gr1(0, 0).is_subgrid(), false, "Correct: false");
    Test::test(gr1(1, 2).get_data(), 0, "Correct: 0");
    const MultiGrid<double> gr2(3, 4);


}

int main()
{
    MultiGrid<int> gr1(3, 3);
    //std::cout << gr1(0, 0).is_subgrid() << '\n';
    //std::cout << gr1(0, 0).get_data() << '\n';
    gr1 = 8;
    //std::cout << gr1(0, 0).get_data() << '\n';
    gr1.make_subgrid(0, 0, 3, 3);
    std::cout << gr1(0, 0).is_subgrid() << '\n';
    gr1(0, 0)(1, 2) = 5;
    std::cout << gr1(0, 0)(1, 1).get_data() << '\n';
    std::cout << gr1(0, 0)(1, 2).get_data() << '\n';
    gr1.collapse_subgrid(0, 0, 3, 3);
    std::cout << gr1(0, 0).get_data() << '\n';

    const MultiGrid<int> gr5(5, 5);
    //gr5 = 13;
    std::cout << gr5(0, 0) << '\n';
    std::cout << "Bye" << '\n';

//    MultiGrid<int> gr3(2, 2);
//    gr3 = 2222;
//    gr1(0, 0) = gr3;
//    std::cout << "start1" << '\n';
//    std::cout << typeid(gr1(1, 1)(0,0)).name() << '\n';
//    std::cout << gr1(0, 0)(1, 1).get_data() << '\n';
//    std::cout << gr1(0, 0)(0,0).is_subgrid() << '\n';
//    std::cout << gr3(0,0).is_subgrid() << '\n';
//    std::cout << "start2" << '\n';
//    MultiGrid<int> gr2 = gr1(0, 0);
//    std::cout << gr2.is_subgrid() << '\n';
//    std::cout << gr2.get_xsize() << '\n';
//    std::cout << gr2(0, 0).get_xsize() << '\n';
//    std::cout << gr2(0, 0).is_subgrid() << '\n';
//    std::cout << (gr1(0, 0)(0,0)).get_data() << '\n';
    return 0;
}

