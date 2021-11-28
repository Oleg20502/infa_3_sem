#include <functional>

template <typename K, typename V, typename H = std::hash<K>>
class AssociativeArray {
public:
    using value_type = std::pair<K const, V>;
    using reference = std::pair<K const, V>&;
    using const_reference = std::pair<K const, V> const &;
    using pointer = std::pair<K const, V>*;
    using iterator = /* ??? */;
    using const_iterator = /* ??? */;

    AssociativeArray()
    {
        n_elements = 0;
        size = 10;
        table = new Node* [size];
        for (int i=0; i<size; ++i){
            table[i] = NULL;
        }
    }

    iterator insert(/* ??? */)
    {
        if (n_elements > k * size)
            reallocate();
        int h1 = H{}(key);
        int h2 = H{}(key);
        int i = 0;
        while(table[h1] != NULL && i < size){
            if (table[h1]->live == false ||
                table[h1]->key == key){
                break;
            }
            h1 = (h1 + h2) % size;
            ++i;
        }
        if (table[h1] == NULL || i == size){
            table[h1] = new Node;
        }
        table[h1]->key = key;
        table[h1]->value = value;
        table[h1]->live = true;
        ++n_elements;


    }
    iterator find(/* ??? */)
    {
        int h1 = H{}(key);
        int h2 = H{}(key);
        int i = 0;
        while(table[h1] != NULL && i < size){
            if(table[h1]->live == true &&
               table[h1]->key == key){
                return ; //iterator on table[h1]->value;
            }
            h1 = (h1 + h2) % size;
            ++i;
        }
        return ; //past the end iterator
    }
    const_iterator find(/* ??? */) const; //метод поиска в неизменяемом объекте, см. примеры
    iterator erase(/* ??? */)
    {
        int h1 = H{}(key);
        int h2 = H{}(key);
        int i = 0;
        while(table[h1] != NULL && i < size){
            if(table[h1]->live == true &&
               table[h1]->key == key){
                table[h1]->live = false;
                --n_elements;
                return ; //iterator on past table[h1]->value;
            }
            h1 = (h1 + h2) % size;
            ++i;
        }
        return ; //past the end iterator
    }

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
private:
    static struct Node{
        K key;
        V value;
        bool live;
    };

    int n_elements, size;
    Node** table;
    double k = 0.25;

    void reallocate()
    {
        int old_size = size;
        size *= 2;
        Node** new_table = new Node* [size];
        for (int i = 0; i < size; ++i)
            new_table[i] = NULL;
        std::swap(table, new_table);
        for(int i = 0; i < old_size; ++i){
            if (new_table[i] && new_table[i]->live)
                insert(new_table[i]->key, new_table[i]->value);
        }
        for (int i = 0; i < old_size; ++i)
            if (new_table[i])
                delete new_table[i];
        delete[] new_table;
    }
};

int main()
{
    return 0;
}
