#include <iostream>
#include <vector>
#include <string>



template<typename T, size_t N>
size_t array_size(const T(&)[N]) {return N;}

template<typename T>
size_t array_size(const T arr) {return arr.size();}

template<class A, class V>
size_t search(A arr, V value)
{
    size_t size = array_size(arr);
    for(int i = 0; i < size; ++i){
        //if(arr[i] >= value - eps && arr[i] <= value + eps)
        if(arr[i] == value)
            return i;
    }
    return size;
}

//template<>
//size_t search<>()
//{
//
//}


int main()
{
    std::vector<int> a = {1, 2, 3};
    int b[] = {5, 6, 8, 9};
    std::cout << search(&a, 3) << '\n';
    std::cout << search(b, 3) << '\n';
    return 0;
}
