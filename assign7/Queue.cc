#include "Queue.h"
#include <stdexcept>

template<typename T>
Queue<T>::Queue(/* args */)
: head(nullptr), tail(nullptr) { }

template<typename T>
Queue<T>::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

template<typename T>
Queue<T>::Queue(const Queue& other) {
    deepCopy(other);
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if (this != &other) {
        while (!isEmpty()) {
            dequeue();
        }
        deepCopy(other);
    }
    return *this;

}

template<typename T>
void Queue<T>::deepCopy(const Queue& other) {
    Node<T> *curr = other.head;
    while (curr) {
        enqueue(curr->data);
        curr = curr->next;
    }
}

template<typename T>
void Queue<T>::enqueue(const T& data) {
    Node<T> *newNode = new Node<T>(data);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        throw std::runtime_error("Nomore memory to enqueue a new node");
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

template<typename T>
T Queue<T>::dequeue() {
    if (head == nullptr) {
        throw std::runtime_error("Attempt to dequeue from an empty queue");
    }
    Node<T> *curr = head;
    T data = curr->data;
    head = head->next;
    delete curr;
    return data;
}

template<typename T>
bool Queue<T>::isEmpty() const {
    return head == nullptr;
}