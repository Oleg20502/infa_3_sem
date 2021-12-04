#include <iostream>

template<typename T, typename D>
struct Node{
    //std::list<Node<T>>::iterator up;
    //std::list<Node<T>>::iterator down;
    Node<D>* up;
    Node<D>* down;
    T value;
};

template<typename V, typename Comp>
class SkipList {
private:
    std::list<Node<value_type, reference> data;
    std::vector<std::list<Node<reference, reference>>> iters;
    size_t n_levels;
    size_t size;
    bool p;
public:
    //using value_type = Node<V, std::list<Node<std::list<>>>::iterator>;
    using value_type = V;
    using reference = value_type&;
    using const_reference = value_type const &;
    using pointer = value_type*;
    using iterator = typename std::list<value_type>::iterator;
    using const_iterator = typename std::list<value_type>::const_iterator;

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

    iterator insert(T& val)
    {

    }

};

int main()
{
    return 0;
}
