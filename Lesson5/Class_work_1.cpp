#include <iostream>
#include <string>
#include <vector>

template<typename stream_t>
stream_t& operator << (stream_t& out, std::vector<int> const& value){
    for(auto const&e: value){
        out << e << ' ';
    }
    return out;
}

template<typename T, typename stream_t = std::ostream>
void log(T const& value, stream_t& out = std::cout)
{
    out << value << '\n'; // T has operator << (&, T)
}

template<>
void log<std::vector<int>, std::ostream>
      (std::vector<int> const& value, std::ostream& out)
{
    for(auto e: value)
        out << e << ' ';
    out << '\n';
}

//size_t array_size(int arr[])
//{
//    return sizeof(arr)/sizeof(int);
//}

template<typename T, size_t N>
size_t array_size(const T(&)[N]) {return N;}

template<typename T, typename function_t>
void transform(T& arr, size_t N, function_t f)
{
    for(auto i = 0; i<N; ++i){
        arr[i] = f(arr[i]);
    }
}

int sqr(int x) {return x*x;}

/*
class ivalue{
public:
    virtual void log() const = 0;
};

void log(ivalue const& v){
    v->log();
}

void log(int value)
{
    std::cout << value << std::endl;
}

void log(std::string const& value)
{
    std::cout << value << std::endl;
}

void log(double value)
{
    std::cout << value << std::endl;
}
*/

int main()
{
    log(3.14, std::cout);
    log(3, std::cout);
    log('c', std::cerr);
    log(std::string{"Hello, world!"}, std::cout);

    log(std::vector<int> {1,2, 3});

    int value[] = {1,2,3};
    log(array_size(value));
    //transform(value, array_size(value), sqr);
    //log(*value);
    return 0;
}
