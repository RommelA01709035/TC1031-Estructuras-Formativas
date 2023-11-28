#include <iostream>
#include <sstream>

template <class T>
class Heap
{
private:
    T *data;
    unsigned int tamanio;
    unsigned int count;

    unsigned int parent(unsigned int) const;
    unsigned int left(unsigned int) const;
    unsigned int right(unsigned int) const;
    void heapify(unsigned int);
    void swap(unsigned int, unsigned int);

public:
    Heap(unsigned int sze);
    ~Heap();
    std::string toString() const;
    void push(T);
    bool full() const;
    bool empty() const;
    T pop();
    T top();
    int size();
};

template <class T>
Heap<T>::Heap(unsigned int sze)
{
    tamanio = sze;
    data = new T[tamanio];
    count = 0;
}

template <class T>
Heap<T>::~Heap()
{
    delete[] data;
    data = 0;
    tamanio = 0;
    count = 0;
}

template <class T>
bool Heap<T>::empty() const
{
    return (count == 0);
}

template <class T>
bool Heap<T>::full() const
{
    return (count == tamanio);
}

template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const
{
    return (pos - 1) / 2;
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const
{
    return (2 * pos) + 1;
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const
{
    return (2 * pos) + 2;
}

template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j)
{
    T aux = data[i];
    data[i] = data[j];
    data[j] = aux;
}

template <class T>
void Heap<T>::heapify(unsigned int pos)
{
    unsigned int le = left(pos);
    unsigned int ri = right(pos);
    unsigned int min = pos;
    if (le <= count && data[le] < data[min])
    {
        min = le;
    }
    if (ri <= count && data[ri] < data[min])
    {
        min = ri;
    }
    if (min != pos)
    {
        swap(pos, min);
        heapify(min);
    }
}

template <class T>
std::string Heap<T>::toString() const
{
    std::stringstream aux;
    aux << "[";
    for (unsigned int i = 0; i < count; i++)
    {
        if (i != 0)
        {
            aux << " ";
        }
        aux << data[i];
    }
    aux << "]";
    return aux.str();
}

template <class T>
void Heap<T>::push(T n)
{
    if (full())
    {
        std::cerr << "El montículo está lleno. No se puede agregar un elemento." << std::endl;
        return;
    }

    data[count] = n;
    unsigned int current = count;
    count++;

    while (current > 0 && data[current] < data[parent(current)])
    {
        swap(current, parent(current));
        current = parent(current);
    }
}

template <class T>
T Heap<T>::pop()
{
    if (empty())
    {
        return T(); 
    }

    T root = data[0];
    data[0] = data[count - 1];
    count--;
    heapify(0);

    return root;
}

template <class T>
T Heap<T>::top()
{
    if (empty())
    {
        return T(); 
    }

    return data[0];
}

template <class T>
int Heap<T>::size()
{
    return count;
}