#include<iostream>

#define SIZE 30

using namespace std;

class Stack
{
private:
    int num[SIZE];
    int top;
public:
    Stack();    //defualt constructor
    void push(int);
    void pop();
    int isEmpty();
    int isFull();
    void displayItems();
};
Stack::Stack() {
    top = -1;
}

int Stack::isEmpty() {
    if (top == -1)
        return 1;
    else
        return 0;
}

int Stack::isFull() {
    if (top == (SIZE - 1))
        return 1;
    else
        return 0;
}

void Stack::push(int n) {
    //check stack is full or not

    ++top;
    num[top] = n;

}

void Stack::pop() {
    //to store and print which number
    //is deleted
    int temp;
    //check for empty
    temp = num[top];
    --top;


}

void Stack::displayItems() {
    int i; //for loop
    for (i =0; i <=top; i++)
        cout << num[i] ;
}