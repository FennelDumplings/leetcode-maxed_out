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

class MyCircularDeque2 {
public:
    /** Initialize your data structure here. Set the size of the deque to be k. */
    MyCircularDeque2(int k) {
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

// -----------------------------

typedef int DLType;
const DLType DLTypeNULL = -1;
const int MAX_LEN = 1e6;

struct DLNode
{
    DLType val;
    DLNode *next;
    DLNode *prev;
    DLNode(DLType x) : val(x), next(nullptr), prev(nullptr) {}
};

class DoubleCircleList
{
private:
    // head 一直指向 dummy
    // tail 在空表时指向 dummy，否则指向 head 的前一个节点
    DLNode *head, *tail;
    int length;
    int capacity;

public:
    DoubleCircleList(int N=MAX_LEN)
    {
        head = new DLNode(0);
        head -> next = head;
        head -> prev = head;
        tail = head;
        length = 0;
        capacity = N;
    }

    bool removeHead()
    {
        if(isEmpty())
            return false;
        remove(get_head());
        return true;
    }

    bool removeTail()
    {
        if(isEmpty())
            return false;
        remove(get_tail());
        return true;
    }

    DLType getHead() const
    {
        if(isEmpty())
            return DLTypeNULL;
        return get_head() -> val;
    }

    DLType getTail() const
    {
        if(isEmpty())
            return DLTypeNULL;
        return get_tail() -> val;
    }

    bool insertHead(DLType val)
    {
        if(isFull())
            return false;
        insert(head, val);
        return true;
    }

    bool insertTail(DLType val)
    {
        if(isFull())
            return false;
        insert(tail, val);
        return true;
    }

    DLNode* insert(DLNode *pos, DLType val)
    {
        if(isFull())
            return nullptr;
        DLNode *cur = new DLNode(val);
        cur -> next = pos -> next;
        cur -> prev = pos;
        pos -> next -> prev = cur;
        pos -> next = cur;
        if(tail == pos)
            tail = cur;
        ++length;
        return cur;
    }

    DLType get(DLNode *pos) const
    {
        if(is_dummy(pos))
            return DLTypeNULL;
        return pos -> val;
    }

    DLNode* remove(DLNode *pos)
    {
        if(isEmpty())
            return nullptr;
        if(is_dummy(pos))
            return nullptr;
        if(tail == pos)
            tail = tail -> prev;
        --length;
        pos -> prev -> next = pos -> next;
        pos -> next -> prev = pos -> prev;
        DLNode *result = pos -> next;
        delete pos;
        pos = nullptr;
        if(isEmpty())
            return nullptr;
        if(is_dummy(result))
            result = result -> next;
        return result;
    }

    bool change(DLNode* pos, DLType val)
    {
        if(is_dummy(pos))
            return false;
        pos -> val = val;
        return true;
    }

    DLNode* get_next(DLNode *pos) const
    {
        if(isEmpty())
            return nullptr;
        if(is_tail(pos))
            return get_head();
        return pos -> next;
    }

    DLNode* get_prev(DLNode *pos) const
    {
        if(isEmpty())
            return nullptr;
        if(is_head(pos))
            return get_tail();
        return pos -> prev;
    }

    bool is_dummy(DLNode *pos) const
    {
        return pos == head;
    }

    bool is_head(DLNode *pos) const
    {
        return (!isEmpty() && pos == head -> next);
    }

    bool is_tail(DLNode *pos) const
    {
        return (!isEmpty() && pos == tail);
    }

    DLNode* get_tail() const
    {
        if(isEmpty())
            return nullptr;
        return tail;
    }

    DLNode* get_head() const
    {
        if(isEmpty())
            return nullptr;
        return head -> next;
    }


    bool isEmpty() const
    {
        return head == tail;
    }

    int size() const
    {
        return length;
    }

    bool isFull() const
    {
        return length >= capacity;
    }

    void traverse() const
    {
        auto iter = head -> next;
        while(iter != head)
        {
            cout << iter -> val << " ";
            iter = iter -> next;
        }
        cout << endl;
    }
};


class MyCircularDeque {
public:
    MyCircularDeque(int k) {
        dclist = DoubleCircleList(k);
    }

    bool insertFront(int value) {
        return dclist.insertHead(value);
    }

    bool insertLast(int value) {
        return dclist.insertTail(value);
    }

    bool deleteFront() {
        return dclist.removeHead();
    }

    bool deleteLast() {
        return dclist.removeTail();
    }

    int getFront() {
        return dclist.getHead();
    }

    int getRear() {
        return dclist.getTail();
    }

    bool isEmpty() {
        return dclist.isEmpty();
    }

    bool isFull() {
        return dclist.isFull();
    }

private:
    DoubleCircleList dclist;
};
