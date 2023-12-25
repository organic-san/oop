#ifndef _QUEUE_H
#define _QUEUE_H

template<typename T>
struct Node {
    T data;
    Node* next;
    Node(const T& item) : data(item), next(nullptr) {}
};

template<typename T>
class Queue {
private:
    Node<T> *head;
    Node<T> *tail;

    void deepCopy(const Queue& other);
public:
    Queue(/* args */);
    ~Queue();

    Queue(const Queue& other);
    Queue& operator=(const Queue& other);

    void enqueue(const T& data);
    T dequeue();

    bool isEmpty() const;
};

#endif // _QUEUE_H