// prob641: Design Circular Deque

/*
 * Design your implementation of the circular double-ended queue (deque).
 * Your implementation should support following operations:
 * MyCircularDeque(k): Constructor, set the size of the deque to be k.
 * insertFront(): Adds an item at the front of Deque. Return true if the operation is successful.
 * insertLast(): Adds an item at the rear of Deque. Return true if the operation is successful.
 * deleteFront(): Deletes an item from the front of Deque. Return true if the operation is successful.
 * deleteLast(): Deletes an item from the rear of Deque. Return true if the operation is successful.
 * getFront(): Gets the front item from the Deque. If the deque is empty, return -1.
 * getRear(): Gets the last item from Deque. If the deque is empty, return -1.
 * isEmpty(): Checks whether Deque is empty or not.
 * isFull(): Checks whether Deque is full or not.
 */

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */

#include "include/Node.h"

class MyCircularDeque {
public:
    /** Initialize your data structure here. Set the size of the deque to be k. */
    MyCircularDeque(int k) {
        capacity = k;
        head = new DoubleListNode(0);
        head -> next = head;
        head -> prev = head;
        tail = head;
        length = 0;
    }

    /** Adds an item at the front of Deque. Return true if the operation is successful. */
    bool insertFront(int value) {
        if(isFull())
            return false;
        DoubleListNode *cur = new DoubleListNode(value);
        cur -> next = head -> next;
        cur -> prev = head;
        head -> next -> prev = cur;
        head -> next = cur;
        if(tail == head)
            tail = cur;
        ++length;
        return true;
    }

    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
    bool insertLast(int value) {
        if(isFull())
            return false;
        DoubleListNode *cur = new DoubleListNode(value);
        cur -> next = head;
        cur -> prev = tail;
        tail -> next = cur;
        head -> prev = cur;
        tail = cur;
        ++length;
        return true;
    }

    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
    bool deleteFront() {
        if(isEmpty())
            return false;
        DoubleListNode *tmp = head -> next;
        head -> next = tmp -> next;
        tmp -> next -> prev = head;
        delete tmp;
        --length;
        if(head -> next == head)
            tail = head;
        return true;
    }

    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
    bool deleteLast() {
        if(isEmpty())
            return false;
        tail -> prev -> next = head;
        head -> prev = tail -> prev;
        delete tail;
        tail = head -> prev;
        --length;
        return true;
    }

    /** Get the front item from the deque. */
    int getFront() {
        if(isEmpty())
            return -1;
        return head -> next -> val;
    }

    /** Get the last item from the deque. */
    int getRear() {
        if(isEmpty())
            return -1;
        return tail -> val;
    }

    /** Checks whether the circular deque is empty or not. */
    bool isEmpty() {
        return head == tail;
    }

    /** Checks whether the circular deque is full or not. */
    bool isFull() {
        return length == capacity;
    }

private:
    struct DoubleListNode {
        int val;
        DoubleListNode *next;
        DoubleListNode *prev;
        DoubleListNode(int x) : val(x), next(nullptr), prev(nullptr) {}
    };

    DoubleListNode *head, *tail;
    int capacity;
    int length;
};
