#include <iostream>

template<typename T>
struct Node{
    Node* prev;
    Node* next;
    Node* up;
    Node* down;
    T value;
};

template<typename V, typename Comp>
class SkipList {
private:
    std::list<V> data;
    std::vector<std::list<std::list<V>::iterator>> iters;
    size_t n_levels;
    size_t size;
public:
    SkipList()
    {
        n_levels= 0;
        size = 0;
    }

    template<typename T>
    SkipList(T beg, T end)
    {

    }


    bool empty() // {return size;}
    {
        if(size){
            return true;
        }
        else
        {
            return false;
        }
    }

    size_t size()
    {
        return size;
    }

};
