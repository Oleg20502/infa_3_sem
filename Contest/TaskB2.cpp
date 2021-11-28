#include <iostream>
#include <functional>
#include <unordered_map>
#include <list>

template <typename K, typename V, typename H = std::hash<K>>
class AssociativeArray {
public:
    using value_type = std::pair<K const, V>;
    using reference = std::pair<K const, V>&;
    using const_reference = std::pair<K const, V> const &;
    using pointer = std::pair<K const, V>*;
    using iterator = typename std::list<value_type>::iterator;
    using const_iterator = typename std::list<value_type>::const_iterator;

    AssociativeArray() {}

    iterator insert(const K key, V && value)
    {
        iterator I;
        if(hashmap.count(key)){
            I = hashmap[key];
            I->second = std::forward<V>(value);
        }
        else{
            value_type p(key, std::forward<V>(value));
            I = data.insert(data.end(), std::forward<value_type>(p));
            hashmap[key] = I;
        }
        return I;
    }

    iterator find(K key)
    {
        if(hashmap.count(key)){
            return hashmap[key];
        }
        else{
            return data.end();
        }
    }

    const_iterator find(K key) const
    {
        if(hashmap.count(key)){
            return hashmap.find(key)->second;
        }
        else{
            return data.cend();
        }
    }

    iterator erase(K key)
    {
        if(hashmap.count(key)){
            iterator I = hashmap[key];
            hashmap.erase(key);
            return data.erase(I);
        }
        else{
            return data.end();
        }
    }

    iterator erase(iterator I)
    {
        hashmap.erase(I->first);
        return data.erase(I);
    }

    iterator begin()
    {
        return data.begin();
    }

    iterator end()
    {
        return data.end();
    }

    const_iterator begin() const
    {
        return data.cbegin();
    }

    const_iterator end() const
    {
        return data.cend();
    }

private:
    std::unordered_map<K, iterator> hashmap;
    std::list<value_type> data;
};

// неработающая версия с сайта
/*
void list_all(AssociativeArray<KeyType, DataType> const &marked_data) {
    std::for_each(marked_data.begin(), marked_data.end(), [] (DataType const &d) { std::cout << d << ' ';});
}
*/

// модифицированная версия
template<typename KeyType, typename DataType>
void list_all(AssociativeArray<KeyType, DataType> const &marked_data) {
    std::for_each(marked_data.begin(), marked_data.end(), [] (std::pair<KeyType const, DataType> const &d) { std::cout << d.second << ' ';});
}


template<typename KeyType, typename DataType>
void list_n_from(AssociativeArray<KeyType,DataType> const &marked_data, size_t size, KeyType const &first_key) {
    auto it = marked_data.find(first_key);
    for (size_t cnt = 0; cnt != size and marked_data.end() != it; ++cnt, ++it)
       std::cout << it->first << ' ' << it->second << std::endl;
}

template<typename KeyType, typename DataType>
typename AssociativeArray<KeyType,DataType>::iterator remove_key(AssociativeArray<KeyType,DataType> &marked_data, KeyType const &key) {
    return marked_data.erase(key);
}

template<typename KeyType, typename DataType>
typename AssociativeArray<KeyType,DataType>::iterator remove_n_from(AssociativeArray<KeyType,DataType> &marked_data, size_t size, KeyType const &first_key) {
    auto it = marked_data.find(first_key);
    for (size_t cnt = 0; cnt != size and marked_data.end() != it; ++cnt)
        it = marked_data.erase(it);
    return it;
}

struct HeavyData{
int a;
    HeavyData() {}

    //HeavyData(int &b) = delete;

    HeavyData(int && b)
    {
        a = b;
    }

    HeavyData(HeavyData const& other) = delete;

    HeavyData(HeavyData && other)
    {
        a = other.a;
    }

    HeavyData& operator=(HeavyData const & b) = delete;

    HeavyData& operator=(HeavyData && other)
    {
        a = other.a;
        return *this;
    }

    void print()
    {
        std::cout << a << '\n';
    }
};

int main()
{
    AssociativeArray<int, int> arr;
    arr.insert(1, 10);
    list_all(arr);
    arr.insert(2, 20);
    std::cout << (arr.find(2))->second << '\n';
    arr.insert(3, -31);
    std::cout << arr.erase(2)->second << '\n';
    const AssociativeArray<int, int> & r_arr = arr;
    std::cout << (r_arr.find(1))->second << '\n';
    arr.insert(2, 21);
    arr.insert(3, 12);
    arr.insert(4, 90);
    arr.insert(5, -542);
    arr.insert(-12, 49000);
    list_n_from(arr, 6, 1);
    std::cout << remove_key(arr, 4)->first << '\n';
    remove_n_from(arr, 4, 5);
    list_n_from(arr, 6, 1);
    std::cout << "start\n";
    AssociativeArray<int, HeavyData> arr2;
    HeavyData a(10);
    HeavyData b(20);
    arr2.insert(1, std::move(a));
    arr2.insert(2, std::move(b));
    (arr2.erase(1)->second).print();
    return 0;
}
