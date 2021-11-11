#include <iostream>
#include <string>
#include <vector>


struct Node
{
    int key;
    unsigned int value;
    bool live;
};


class HashMap{
private:
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
        for (int i = 0; i < old_size; ++i)
        {
            if (new_table[i] && new_table[i]->live)
                add(new_table[i]->key, new_table[i]->value);
        }
        for (int i = 0; i < old_size; ++i)
            if (new_table[i])
                delete new_table[i];
        delete[] new_table;
    }

    int hash(int a, int rand)
    {
        return (a * rand) % size;
    }

public:
    HashMap()
    {
        n_elements = 0;
        size = 10;
        table = new Node* [size];
        for (int i=0; i<size; ++i){
            table[i] = NULL;
        }
    }

    void add(int key, unsigned int value)
    {
        if (n_elements > k * size)
            reallocate();

        int h1 = hash(key, size-1);
        int h2 = hash(key, size+1);
        int i = 0;
        while (table[h1] != NULL && i < size){
            if (table[h1]->live == false ||
                table[h1]->key == key) break;
            h1 = (h1 + h2) % size;
            ++i;
        }
        if (table[h1] == NULL){
            table[h1] = new Node;
        }
        table[h1]->key = key;
        table[h1]->value = value;
        table[h1]->live = true;
        ++n_elements;
    }

    ~HashMap()
    {
        for (int i = 0; i < size; ++i)
            if (table[i] != NULL)
                delete table[i];
        delete [] table;
    }

    unsigned int get(int key, unsigned int val)
    {
        int h1 = hash(key, size-1);
        int h2 = hash(key, size+1);
        for (int i=0; i<n_elements; ++i){
            if (table[h1] != NULL &&
                table[h1]->key == key &&
                table[h1]->live == true){
                return table[h1]->value;
            }
            h1 = (h1 + h2) % size;
        }
        return val;
    }

    unsigned int pop(int key)
    {
         int h1 = hash(key, size-1);
         int h2 = hash(key, size+1);
         unsigned int elem = 0;
         for (int i=0; i<n_elements; ++i){
             if (table[h1] != NULL &&
                 table[h1]->key == key){
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

int main()
{
    int N, M;
    std::cin >> N >> M;
    std::vector<HashMap> H(N);
    int I, key;
    unsigned int value;
    char s;
    for(int i=0; i<M; ++i){
        std::cin >> I >> s >> key >> value;
        if (s == '+'){
            H[I].add(key, value);
        }
        else if(s == '-'){
            H[I].pop(key);
        }
        else if(s == '?'){
            std::cout << H[I].get(key, value) << '\n';
        }
    }
    return 0;
}
