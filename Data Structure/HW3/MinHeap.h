
#include<iostream>
#include<climits>
#include"tree.h"

using namespace std;



void swap(Tree** x, Tree** y)
{
    Tree* temp = *x;
    *x = *y;
    *y = temp;
}


class MinHeap
{
    Tree** heap_array;
    int capacity;
    int heap_size;
public:

    void set_capacity(int capacity);


    int parent(int i)
    {
        return (i - 1) / 2;
    }
    int left(int i)
    {
        return (2 * i + 1);
    }
    int right(int i)
    {
        return (2 * i + 2);
    }
    Tree* pop();
    void push(Tree* data);
    void top_down(int index);
};


void MinHeap::set_capacity(int cap)
{
    heap_size = 0;
    capacity = cap;
    heap_array = new Tree*[cap];
}




void MinHeap::push(Tree* data)
{
    if (heap_size == capacity)
    {
        cout << "have full";
        return;
    }

    heap_size++;
    int i = heap_size - 1;
    heap_array[i] = data;

    //bottom up
    while (i != 0 && heap_array[parent(i)]->get_data() > heap_array[i]->get_data())
    {
        swap(&heap_array[i], &heap_array[parent(i)]);
        i = parent(i);
    }
}



Tree* MinHeap::pop()
{

    if (heap_size == 1)
    {
        heap_size--;
        return heap_array[0];
    }

    // Store the minimum value, and remove it from heap
    Tree* root = heap_array[0];

    heap_array[0] = heap_array[heap_size - 1];
    heap_size--;
    top_down(0);

    return root;
}



void MinHeap::top_down(int index)
{
    int l = left(index);
    int r = right(index);
    int min_index = index;

    if (l < heap_size && heap_array[l]->get_data() < heap_array[index]->get_data())
        min_index = l;
    if (r < heap_size && heap_array[r]->get_data() < heap_array[min_index]->get_data())
        min_index = r;
    if (min_index != index)
    {
        swap(&heap_array[index], &heap_array[min_index]);
        top_down(min_index);
    }
}


