#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <iostream>
#include <string>
#include <sstream>


template <class Key, class Value>
class Quadratic {
private:
    struct Node {
        Key key;
        Value value;
        bool filled;

        Node() : filled(false) {}
    };

    Node* table;
    unsigned int size;
    Key initialValue;

    unsigned int (*hashFunction)(const Key);

public:
    Quadratic(unsigned int tableSize, Key initial, unsigned int (*func)(const Key))
        : size(tableSize), initialValue(initial), hashFunction(func) {
        table = new Node[size];
    }

    ~Quadratic() {
        delete[] table;
    }
void put(const Key& key, const Value& value) {
    unsigned int index = hashFunction(key) % size;
    unsigned int originalIndex = index;
    int i = 1;

    while (table[index].filled) {
        index = (originalIndex + i * i) % size; 
        i++;
    }

    table[index].key = key;
    table[index].value = value;
    table[index].filled = true;
}

Value get(const Key& key) {
    unsigned int index = hashFunction(key) % size;
    unsigned int originalIndex = index;
    int i = 1;

    while (table[index].filled) {
        if (table[index].key == key) {
            return table[index].value;
        }
        index = (originalIndex + i * i) % size; 
        i++;
    }

    throw std::runtime_error("Key not found");
}

std::string toString() const {
    std::stringstream aux;
    for (int i = 0; i < size; i++) {
        if (table[i].filled) {
            aux << "(" << i << " " << table[i].key << " : " << table[i].value << ") ";
        }
    }
    return aux.str();
}
};



#endif /* QUADRATIC_H_ */
