#ifndef DLIST_H
#define DLIST_H

#include <iostream>
#include <sstream>

template <class T>
class DList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    DList() : head(nullptr), tail(nullptr) {}

    void insertion(const T& value) {
        Node* newNode = new Node(value);

        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    T search(const T& value) const {
        Node* current = head;
        int index = 0;

        while (current) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            index++;
        }

        return -1;
    }

    void update(int index, const T& value) {
        if (index < 0) {
            return;
        }

        Node* current = head;
        int currentIndex = 0;

        while (current && currentIndex != index) {
            current = current->next;
            currentIndex++;
        }

        if (current) {
            current->data = value;
        }
    }

    void deleteAt(int index) {
        if (index < 0) {
            return;
        }

        Node* current = head;
        int currentIndex = 0;

        while (current && currentIndex != index) {
            current = current->next;
            currentIndex++;
        }

        if (current) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }

            if (current->next) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }

            delete current;
        }
    }

    ~DList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    std::string toStringForward() const {
        std::stringstream ss;
        ss << "[";
        Node* current = head;
        while (current) {
            ss << current->data;
            if (current->next) {
                ss << ", ";
            }
            current = current->next;
        }
        ss << "]";
        return ss.str();
    }

    std::string toStringBackward() const {
        std::stringstream ss;
        ss << "[";
        Node* current = tail;
        while (current) {
            ss << current->data;
            if (current->prev) {
                ss << ", ";
            }
            current = current->prev;
        }
        ss << "]";
        return ss.str();
    }
};
#endif
