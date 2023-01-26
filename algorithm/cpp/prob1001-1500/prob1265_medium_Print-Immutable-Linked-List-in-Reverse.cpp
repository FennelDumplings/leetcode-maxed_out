// prob1265: Print Immutable Linked List in Reverse

/*
 * https://leetcode-cn.com/problems/print-immutable-linked-list-in-reverse/
 */

/**
 * // This is the ImmutableListNode's API interface.
 * // You should not implement it, or speculate about its implementation.
 */

#include <iostream>

using namespace std;

class ImmutableListNode {
public:
   void printValue(); // print the value of the node.
   ImmutableListNode* getNext(); // return the next node.
};

class Solution {
public:
    void printLinkedListInReverse(ImmutableListNode* head) {
        if(head -> getNext())
            printLinkedListInReverse(head -> getNext());
        head -> printValue();
    }
};
