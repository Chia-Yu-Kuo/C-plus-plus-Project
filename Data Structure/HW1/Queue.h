#include <iostream>
using std::cout;

class Queue {
private:
    int capacity, front, back;
    int* queue;
    void DoubleCapacity();
public:
    Queue() :capacity(10), front(-1), back(-1) {
        queue = new int[capacity];
    };
    void Push(int x);
    void Pop();
    bool IsEmpty();
    bool IsFull();
    int getFront();
    int getBack();
    int getSize();
    int getCapacity();    // 驗證用, 可有可無
};

void Queue::DoubleCapacity() {

    capacity *= 2;
    int* newQueue = new int[capacity];

    int j = -1;
    for (int i = front + 1; i <= back; i++) {
        j++;
        newQueue[j] = queue[i];
    }
    front = -1;       // 新的array從0開始, 把舊的array"整段平移", front跟back要更新
    back = j;
    delete[] queue;
    queue = newQueue;
}
void Queue::Push(int x) {

    if (IsFull()) {
        DoubleCapacity();
    }
    queue[++back] = x;
}
void Queue::Pop() {

    if (IsEmpty()) {
       // std::cout << "Queue is empty.\n";
        return;
    }
    front++;
}
bool Queue::IsFull() {

    return (back + 1 == capacity);
}
bool Queue::IsEmpty() {

    return (front == back);
}
int Queue::getFront() {

    if (IsEmpty()) {
        //std::cout << "Queue is empty.\n";
        return -1;
    }

    return queue[front+1];
}
int Queue::getBack() {

    if (IsEmpty()) {
        //std::cout << "Queue is empty.\n";
        return -1;
    }

    return queue[back];
}
int Queue::getSize() {

    return (back - front);
}
int Queue::getCapacity() {

    return capacity;
}

void printSequentialQueue(Queue queue) {
    cout << "front: " << queue.getFront() << "    back: " << queue.getBack() << "\n"
        << "capacity: " << queue.getCapacity() << "  number of elements: " << queue.getSize() << "\n\n";
}