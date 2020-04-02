// prov662: Design Circular Queue

/*
 * Design your implementation of the circular queue. The circular queue is a linear data structure
 * in which the operations are performed based on FIFO (First In First Out) principle
 * and the last position is connected back to the first position to make a circle. It is also called "Ring Buffer".
 * One of the benefits of the circular queue is that we can make use of the spaces in front of the queue.
 * In a normal queue, once the queue becomes full, we cannot insert the next element
 * even if there is a space in front of the queue. But using the circular queue, we can use the space to store new values.
 */

/*
 * Front: Get the front item from the queue. If the queue is empty, return -1.
 * Rear: Get the last item from the queue. If the queue is empty, return -1.
 * enQueue(value): Insert an element into the circular queue. Return true if the operation is successful.
 * deQueue(): Delete an element from the circular queue. Return true if the operation is successful.
 * isEmpty(): Checks whether the circular queue is empty or not.
 * isFull(): Checks whether the circular queue is full or not.
 */

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */

#include "include/Node.h"

class MyCircularQueue {
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) {
        capacity = k;
        head = new ListNode(0);
        head -> next = head;
        tail = head;
        length = 0;
    }

    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if(isFull())
            return false;
        ListNode *cur = new ListNode(value);
        tail -> next = cur;
        cur -> next = head;
        tail = cur;
        ++length;
        return true;
    }

    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if(isEmpty())
            return false;
        ListNode *tmp = head -> next;
        head -> next = tmp -> next;
        delete tmp;
        --length;
        if(head -> next == head)
            tail = head;
        return true;
    }

    /** Get the front item from the queue. */
    int Front() {
        if(isEmpty())
            return -1;
        return head -> next -> val;
    }

    /** Get the last item from the queue. */
    int Rear() {
        if(isEmpty())
            return -1;
        return tail -> val;
    }

    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        return head == tail;
    }

    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        return length == capacity;
    }

private:
    // 有虚拟头结点，队列空的时候 head == tail
    int capacity;
    int length;
    ListNode *head;
    ListNode *tail;
};

