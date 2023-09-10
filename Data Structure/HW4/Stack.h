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
    int pop();
    bool isEmpty();
    int isFull();
    int get_size();
    void displayItems();
    int get_top_value();
};
Stack::Stack() {
    top = -1;
}

int Stack::get_top_value() 
{
    return num[top];
}

bool Stack::isEmpty() {
    if (top == -1)
        return true;
    else
        return false;
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

int Stack::pop() {
    //to store and print which number
    //is deleted
    int temp;
    //check for empty
    temp = num[top];
    --top;

    return temp;
}

int Stack::get_size() 
{
    return top + 1;
    
}

void Stack::displayItems() {
    int i; //for loop
    for (i =0; i <=top; i++)
        cout << num[i] ;
}