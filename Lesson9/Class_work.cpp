

template<typename Container>
void print(Container const& arr)
{
    std::copy(std::begin(arr), std::end(arr),
              std::ostream_iterator<decltype(*arr.begin())>(std::cout, " "));
    std::cout << std::endl;
}


int main()
{
    auto gen_func = [&value](){};

    struct generator_function{
        int operator()(){
            return value_ *= 3;
        }
    private:
        int value_ = 1;
    };

    std::vector<int> v;
    v.resize();
    std::generate(std::begin(v), std::end(v), generator_function{});


    std::transform(std::begin(v), std::end(v), std::back_insert())

    return 0;
}
