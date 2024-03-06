#include<vector>
#include<string>

template<typename>T
struct QueueNode {
    T val;
    QueueNode<T>* next;
    QueueNode(T d):val(d),next(NULL){}
};
 
template<typename>T
struct Queue {
    QueueNode<T> *front, *back;
    int q_size;
    Queue() { front = back = NULL; q_size=0; }

    int Size(){return q_size;}
    bool isEmpty(){return (q_size==0);}
    void push(T x)
    {
        QueueNode<T>* temp = new QueueNode(x);
        if (back == NULL) {
            front = back = temp;
        }
        else{
            back->next = temp;
            back = temp;
        }
        q_size++;
    }
    void pop()
    {
        if (front == NULL) return;
        QueueNode<T>* temp = front;
        front = front->next;
        if (front == NULL) back = NULL;     //single node
        delete temp;
        q_size--;
    }
    void empty(){
        while(q_size>=0) pop();
    }
};