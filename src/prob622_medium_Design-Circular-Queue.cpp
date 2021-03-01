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

class MyCircularQueue_2 {
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue_2(int k) {
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



// ---------------------------------------------

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

class MyCircularQueue {
public:
    MyCircularQueue(int k) {
        dclist = DoubleCircleList(k);
    }

    bool enQueue(int value) {
        bool flag = dclist.insertTail(value);
        return flag;
    }

    bool deQueue() {
        bool flag = dclist.removeHead();
        return flag;
    }

    int Front() {
        int ans = dclist.getHead();
        return ans;
    }

    int Rear() {
        int ans = dclist.getTail();
        return ans;
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

