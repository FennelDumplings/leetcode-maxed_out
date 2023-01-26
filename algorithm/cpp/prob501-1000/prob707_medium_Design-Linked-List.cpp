// prob707: Design Linked List

/*
 * Design your implementation of the linked list. You can choose to use the singly linked list or the doubly linked list.
 * A node in a singly linked list should have two attributes: val and next. val is the value of the current node,
 * and next is a pointer/reference to the next node. If you want to use the doubly linked list,
 * you will need one more attribute prev to indicate the previous node in the linked list. Assume all nodes in the linked list are 0-indexed.
 * Implement these functions in your linked list class:
 * get(index) : Get the value of the index-th node in the linked list. If the index is invalid, return -1.
 * addAtHead(val) : Add a node of value val before the first element of the linked list. After the insertion,
 * the new node will be the first node of the linked list.
 * addAtTail(val) : Append a node of value val to the last element of the linked list.
 * addAtIndex(index, val) : Add a node of value val before the index-th node in the linked list.
 * If index equals to the length of linked list, the node will be appended to the end of linked list.
 * If index is greater than the length, the node will not be inserted.
 * deleteAtIndex(index) : Delete the index-th node in the linked list, if the index is valid.
 */

#include "include/Node.h"
#include <unordered_map>
#include <vector>

using namespace std;

// 用 vector 代替 unordered_map 后，时间 200ms -> 40ms(击败 99%)
class MyLinkedList_2 {
public:
    /** Initialize your data structure here. */
    MyLinkedList_2() {
        dummy = new ListNode(0); // dummy_node 存表长
        mapping = vector<ListNode*>();
    }

    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        int n = mapping.size();
        if(index < n && index >= 0)
            return mapping[index] -> val;
        else
            return -1;
    }

    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        addAtIndex(0, val);
    }

    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        addAtIndex(mapping.size(), val);
    }

    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        if(index < 0) index = 0;
        int n = mapping.size();
        if(index > n) index = n;
        ListNode *prev;
        if(index == 0)
            prev = dummy;
        else
            prev = mapping[index - 1];
        ListNode *cur = new ListNode(val);
        cur -> next = prev -> next;
        prev -> next = cur;
        mapping.push_back(nullptr);
        for(int i = n; i > index; --i)
            mapping[i] = mapping[i - 1];
        mapping[index] = cur;
    }

    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        int n = mapping.size();
        if(index < n && index >= 0)
        {
            ListNode *prev;
            if(index == 0)
                prev = dummy;
            else
                prev = mapping[index - 1];
            prev -> next = prev -> next -> next;
            delete mapping[index];
            for(int i = index; i < n - 1; ++i)
                mapping[i] = mapping[i + 1];
            mapping.pop_back();
        }
    }

private:
    vector<ListNode*> mapping;
    ListNode *dummy;
};

// 224ms, 时间比较慢
class MyLinkedList {
public:
    /** Initialize your data structure here. */
    MyLinkedList() {
        dummy = new ListNode(0); // dummy_node 存表长
        mapping = unordered_map<int, ListNode*>();
        mapping[-1] = dummy;
    }

    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        auto it = mapping.find(index);
        if(it != mapping.end())
            return it -> second -> val;
        else
            return -1;
    }

    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        addAtIndex(0, val);
    }

    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        addAtIndex(dummy -> val, val);
    }

    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        if(index < 0) index = 0;
        if(index > dummy -> val) index = dummy -> val;
        ListNode *prev;
        prev = mapping[index - 1];
        ListNode *cur = new ListNode(val);
        cur -> next = prev -> next;
        prev -> next = cur;
        for(int i = dummy -> val; i > index; --i)
            mapping[i] = mapping[i - 1];
        mapping[index] = cur;
        ++(dummy -> val);
    }

    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        auto it = mapping.find(index);
        if(it != mapping.end())
        {
            ListNode *prev = mapping[index - 1];
            prev -> next = prev -> next -> next;
            delete mapping[index];
            for(int i = index; i < dummy -> val - 1; ++i)
                mapping[i] = mapping[i + 1];
            mapping.erase(mapping.find(dummy -> val - 1));
            --(dummy -> val);
        }
    }

private:
    unordered_map<int, ListNode*> mapping;
    ListNode *dummy;
};
