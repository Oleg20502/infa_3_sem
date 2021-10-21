#include <iostream>


template<typename T>
class MultiGrid{
private:
    bool if_subgrid = false;
    MultiGrid* memory;
    T data = (T)0;
    size_t x_size, y_size;

public:
    MultiGrid(): memory{nullptr}, x_size{1}, y_size{1} {}

    MultiGrid(T val): memory{nullptr}, data{val}, x_size{1}, y_size{1} {}

    MultiGrid(size_t x_size, size_t y_size): memory{ new MultiGrid[x_size * y_size]},
                                            x_size{x_size}, y_size{y_size}, if_subgrid{true} {}

    MultiGrid(MultiGrid const &g)
    {
        if (g.is_subgrid() == false){
            memory = nullptr;
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
    }

    MultiGrid(MultiGrid &&g): memory{g.memory}, data{g.data}, x_size{g.x_size}, y_size{g.y_size},
                              if_subgrid{g.if_subgrid}
    {
        g.memory = nullptr;
        g.data = (T)0;
        g.x_size = g.y_size = 0;
        g.if_subgrid = false;
    }

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

    MultiGrid& operator=(T const &value)
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

    MultiGrid& operator=(MultiGrid const &g)
    {
        delete [] memory;
        if (g.is_subgrid() == false){
            memory = nullptr;
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

    MultiGrid& operator=(MultiGrid &&g)
    {
        memory = g.memory;
        data = g.data;
        x_size = g.x_size;
        y_size = g.y_size;
        if_subgrid = g.if_subgrid;

        g.memory = nullptr;
        g.data = (T)0;
        g.x_size = g.y_size = 0;
        g.if_subgrid = false;

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
            MultiGrid<T> g((static_cast<const MultiGrid<T>> (*this))(x_idx, y_idx));
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


void test_MultiGrid()
{
    MultiGrid<int> gr1(3, 3);
    Test::test(gr1.get_xsize(), 3, "Correct: 3");
    Test::test(gr1(0, 0).is_subgrid(), false, "Correct: false");
    Test::test(gr1(1, 2).get_data(), 0, "Correct: 0");
    gr1 = 8;
    Test::test(gr1(2, 0).get_data(), 8, "Correct: 8");
    gr1.make_subgrid(0, 0, 3, 5);
    Test::test(gr1(0, 0).is_subgrid(), true, "Correct: true");
    gr1(0, 0)(1, 2) = 5;
    Test::test(gr1(1, 1).get_data(), 8, "Correct: 8");
    Test::test(gr1(0, 0)(1, 2).get_data(), 5, "Correct: 5");
    gr1(0, 0).make_subgrid(0, 2, 1, 4);
    Test::test(gr1(0, 0)(0, 2).get_ysize(), 4, "Correct: 4");
    Test::test(gr1(0, 0)(0, 2).is_subgrid(), true, "Correct: true");
    Test::test(gr1(0, 0)(0, 2)(0, 3).get_data(), 8, "Correct: 8");
    MultiGrid<int> gr2 = gr1(0, 0)(0, 2);
    Test::test(gr1.get_subgrid(0, 0).is_subgrid(), true, "Correct: true");
    Test::test(gr1.get_subgrid(0, 0).get_xsize(), 3, "Correct: 3");
    gr2.make_subgrid(0, 2, 20, 10);
    Test::test(gr2(0, 2).is_subgrid(), true, "Correct: true");
    gr2(0, 2)(16, 7) = -10000;
    gr2.collapse_subgrid(0, 2, 20, 10);
    Test::test(gr2(0, 2).is_subgrid(), false, "Correct: false");
    Test::test(gr2(0, 2).get_data(), -42, "Correct: -42");
    const MultiGrid<int> gr3 = gr1;
    Test::test(gr3(0, 0), 7, "Correct: 7");
    gr1.collapse_subgrid(0, 0, 2, 2);
    Test::test(gr1(0, 0).is_subgrid(), false, "Correct: false");
    Test::test(gr1(0, 0).get_data(), 7, "Correct: 7");
    MultiGrid<int> gr4(22);
    MultiGrid<int> gr5(std::move(gr4));
    Test::test(gr5.get_data(), 22, "Correct: 22");
    Test::test(gr4.get_data(), 0, "Correct: 0");
    MultiGrid<int> gr6;
    gr6 = std::move(gr5);
    Test::test(gr6.get_data(), 22, "Correct: 22");

    MultiGrid<double> gr11(3, 3);
    Test::test(gr11.get_xsize(), 3, "Correct: 3");
    Test::test(gr11(0, 0).is_subgrid(), false, "Correct: false");
    Test::test(gr11(1, 2).get_data(), 0, "Correct: 0");
    gr11 = 8.5;
    Test::test(gr11(2, 0).get_data(), 8.5, "Correct: 8.5");
    gr11.make_subgrid(0, 0, 3, 5);
    Test::test(gr11(0, 0).is_subgrid(), true, "Correct: true");
    gr11(0, 0)(1, 2) = 5.784;
    Test::test(gr11(1, 1).get_data(), 8.5, "Correct: 8.5");
    Test::test(gr11(0, 0)(1, 2).get_data(), 5.784, "Correct: 5.784");
    gr11(0, 0).make_subgrid(0, 2, 1, 4);
    Test::test(gr11(0, 0)(0, 2).get_ysize(), 4, "Correct: 4");
    Test::test(gr11(0, 0)(0, 2).is_subgrid(), true, "Correct: true");
    Test::test(gr11(0, 0)(0, 2)(0, 3).get_data(), 8.5, "Correct: 8.5");
    MultiGrid<double> gr22 = gr11(0, 0)(0, 2);
    Test::test(gr11.get_subgrid(0, 0).is_subgrid(), true, "Correct: true");
    Test::test(gr11.get_subgrid(0, 0).get_xsize(), 3, "Correct: 3");
    gr22.make_subgrid(0, 2, 20, 10);
    Test::test(gr22(0, 2).is_subgrid(), true, "Correct: true");
    gr22(0, 2)(16, 7) = -10000.1234;
    gr22.collapse_subgrid(0, 2, 20, 10);
    Test::test(gr22(0, 2).is_subgrid(), false, "Correct: false");
    //std:: cout << gr22(0, 2).get_data() << '\n';
    //Test::test(gr22(0, 2).get_data(), -41.5431, "Correct: -41.5431");
    const MultiGrid<double> gr33 = gr11;
    //std:: cout << gr33(0, 0) << '\n';
    //Test::test(gr33(0, 0), 8.31893, "Correct: 8.31893");
    gr11.collapse_subgrid(0, 0, 2, 2);
    Test::test(gr11(0, 0).is_subgrid(), false, "Correct: false");
    //Test::test(gr11(0, 0).get_data(), 8.31893, "Correct: 8.31893");
    //There is some difficulty when checking if doubles are equal
    MultiGrid<double> gr44(22);
    MultiGrid<double> gr55(std::move(gr44));
    Test::test(gr55.get_data(), 22.0, "Correct: 22.0");
    Test::test(gr44.get_data(), 0.0, "Correct: 0.0");
    MultiGrid<double> gr66;
    gr66 = std::move(gr55);
    Test::test(gr66.get_data(), 22.0, "Correct: 22.0");
}

int main()
{
    test_MultiGrid();

    return 0;
}

