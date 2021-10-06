#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>

template <typename value_t, size_t N>
size_t stack_array_size(const value_t(&)[N]) { return N; }

template <typename stream_t, typename data_t>
stream_t& operator << (stream_t& out, std::vector<data_t> const& value){
  out << "[";
  for (auto i = 0; i<value.size()-1; ++i)
    out << value[i] << ", ";
  out << value[value.size()-1] << "]";
  return out;
}

//template <typename stream_t, typename T>
//stream_t& operator << (stream_t& out, T value){
//  out << "[";
//  size_t size = stack_array_size(value);
//  for (auto i = 0; i < size-1; ++i)
//    out << value[i] << ", ";
//  out << value[size-1] << "]";
//  return out;
//}

//template<typename value_t, typename stream_t = std::ostream>
//void dump(value_t* v, stream_t& out = std::cout){
//  out << v << std::endl;
//}

template<typename value_t>
void dump(value_t arr, size_t size, std::ostream & out = std::cout){
    out << "[";
    for (auto i = 0; i < size-1; ++i)
        out << arr[i] << ", ";
    out << arr[size-1] << "]\n";
}

template<typename value_t>
std::string get_string(value_t arr, size_t size)
{
    std::string str = "[";
    for (auto i = 0; i < size-1; ++i){
        str.append(std::to_string(arr[i]));
        str.append(", ");
    }
    str.append(std::to_string(arr[size-1]));
    str.append("]");
    return str;
}

template<typename T, typename V>
size_t search(T const beg, T const end, V const value)
{
    size_t iter = 0;
    for(auto i = beg; i < end; ++i){
        if((*i) == value)
            return iter;
        ++iter;
    }
    return iter;
}

template<>
size_t search(double* beg, double* end, double const value)
{
    double eps = 0.0001;
    size_t iter = 0;
    for(auto i = beg; i < end; ++i){
        if((*i) >= value-eps && (*i) <= value+eps)
            return iter;
        ++iter;
    }
    return iter;
}

template<typename iter_t>
void qsort(iter_t beg, iter_t end)
{
    iter_t l = beg, r = end;
    auto piv = *(l);
    while (l <= r){
        while (*l < piv)
            ++l;
        while (*r > piv)
            --r;
        if (l <= r)
            std::swap(*(l++), *(r--));
    }
    if (beg < r)
        qsort(beg, r);
    if (end > l)
        qsort(l, end);
}

template<typename value_t>
void quick_sort(value_t arr, size_t N)
{
    auto p = arr[N/2];
    size_t s = 0;
    size_t f = N-1;
    while (s <= f){
        while (arr[s] < p) ++s;
        while (arr[f] > p) --f;
        if (s <= f){
            std::swap(arr[f], arr[s]);
            ++s;
            --f;
        }
    }
    if (f > 0) quick_sort(arr, f+1);
    if (N - 1 > s) quick_sort(arr+s, N-s);
}

template<typename K, typename V>
struct Node
{
    K key;
    V value;
    bool live;
};

template<typename K, typename V>
class HashMap{
private:
    size_t n_elements, size;
    Node<K, V>** table;
    double k = 0.25;

    void reallocate()
    {
        size_t old_size = size;
        size *= 2;
        Node<K, V>** new_table = new Node<K, V>* [size];
        for (auto i = 0; i < size; ++i)
            new_table[i] = NULL;
        std::swap(table, new_table);
        for (auto i = 0; i < old_size; ++i)
        {
            if (new_table[i] && new_table[i]->live)
                add(new_table[i]->key, new_table[i]->value);
        }
        for (auto i = 0; i < old_size; ++i)
            if (new_table[i])
                delete new_table[i];
        delete[] new_table;
    }

    int hash(K a, int rand){ return (a * rand) % size;}

public:
    HashMap()
    {
        size = 10;
        table = new Node<K, V>* [size];
        for (auto i = 0; i < size; ++i){
            table[i] = NULL;
        }
    }

    ~HashMap()
    {
        for (auto i = 0; i < size; ++i)
            if (table[i])
                delete table[i];
        delete[] table;
    }

    void add(K key, V value)
    {
        if (n_elements > k * size)
            reallocate();

        size_t h1 = hash(key, size-1);
        size_t h2 = hash(key, size+1);
        size_t i = 0;
        while (table[h1] != NULL && i < size){
            if (table[h1]->live == false)
                break;
            h1 = (h1 + h2) % size;
            ++i;
        }
        if (table[h1] == NULL)
            table[h1] = new Node<K, V>;
        table[h1]->key = key;
        table[h1]->value = value;
        table[h1]->live = true;
        ++n_elements;
    }

    //void add(V value){ add(value, value);}

    //void &operator[]=(K key, V val) {add(key, val);}

    //V const &operator[](K key) const {return get(key);}

    V get(K key)
    {
         size_t h1 = hash(key, size-1);
         size_t h2 = hash(key, size+1);
         for (auto i=0; i<n_elements; ++i){
             if (table[h1]->key == key)
                return table[h1]->value;
             h1 = (h1 + h2) % size;
         }
         return -245648298;
    }

    V pop(K key)
    {
         size_t h1 = hash(key, size-1);
         size_t h2 = hash(key, size+1);
         size_t elem = -245648298;
         for (auto i=0; i<n_elements; ++i){
             if (table[h1]->key == key){
                 elem = table[h1]->value;
                 table[h1]->live = false;
                 --n_elements;
                 break;
             }
             h1 = (h1 + h2) % size;
         }
         return elem;
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

void test_search()
{
    std::vector<int> a = {3, 1, 2};
    int b[] = {5, 6, 9, 8};
    double c[] = {2.0, 5.1, 6.0, 11.94};
    std::vector<double> d = {3.0, 1.0, 2.0, 4.0};
    Test::test(search(a.begin(), a.end(), 3), 0, "correct: 0");
    Test::test(search(b, b+4, 3), 4, "correct: 4");
    Test::test(search(b, b+4, 6.00001), 4, "correct: 4");
    Test::test(search(c, c+4, 6.00001), 2, "correct: 2");
    Test::test(search(d.begin(), d.end(), 4.0), 3, "correct: 3");
}

void test_qsort()
{
    std::vector<int> a = {3, 1, 2};
    int b[] = {5, 6, 9, 8};
    double c[] = {6.1, 5.5, 2.0, 11.999};

    qsort(&a[0], &a.back());
    //quick_sort(&a, a.size());
    Test::test(get_string(a, a.size()), "[1, 2, 3]");
    std::cout << get_string(a, a.size()) << '\n';

    qsort(b, b+4);
     Test::test(get_string(b, 4), "[5, 6, 8, 9]");
    std::cout << get_string(b, 4) << '\n';

    qsort(c, c+4);
    Test::test(get_string(c, 4), "[2.000000, 5.500000, 6.100000, 11.999000]");
    std::cout << get_string(c, 4) << '\n';
}

int main()
{

    test_search();
    //test_qsort();

    HashMap<char, int> m;
    m.add('a', 10);
    m.add('b', 11);
    std::cout << m.get('b') << '\n';

    return 0;
}
