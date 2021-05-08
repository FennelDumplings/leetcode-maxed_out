// prob138: Copy List with Random Pointer

/*
 * A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.
 * Return a deep copy of the list.
 * The Linked List is represented in the input/output as a list of n nodes. Each node is represented as a pair of [val, random_index] where:
 * val: an integer representing Node.val
 * random_index: the index of the node (range from 0 to n-1) where random pointer points to, or null if it does not point to any node.
 */

/*
 * Constraints:
 * -10000 <= Node.val <= 10000
 *  Node.random is null or pointing to a node in the linked list.
 *  Number of Nodes will not exceed 1000.
 */

// Definition for a Node.

#include <unordered_map>

using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head == nullptr) return nullptr;
        Node *dummy = new Node(0);
        Node *cur = dummy;
        Node *iter = head;
        unordered_map<Node*, Node*> mapping;
        // 第一趟遍历时，无视 random 建表, 此时 random 是空表
        // 并且：每一轮对应的两个节点，原节点的指针作键，新节点的指针做值存到哈希表里
        while(iter != nullptr)
        {
            Node *tmp = new Node(iter -> val);
            cur -> next = tmp;
            cur = cur -> next;
            mapping[iter] = cur;
            iter = iter -> next;
        }
        mapping[iter] = cur -> next; // 空指针也 map 进来
        // 第二趟遍历，通过哈希表把 random 指向的原节点对应到新节点
        iter = head;
        cur = dummy -> next;
        while(iter != nullptr)
        {
            cur -> random = mapping[iter -> random];
            iter = iter -> next;
            cur = cur -> next;
        }
        return dummy -> next;
    }
};

// 不用哈希表的思路
// 克隆节点插入原节点之后
// 在原表上处理 random 节点
// 分离链表
class Solution_2 {
public:
    Node* copyRandomList(Node* head) {
        if(head == nullptr) return nullptr;
        Node *iter = head;
        // 第一趟遍历时，无视 random 建表, 新节点插入到原节点后面
        while(iter != nullptr)
        {
            Node *tmp = new Node(iter -> val);
            tmp -> next = iter -> next;
            iter -> next = tmp;
            iter = iter -> next -> next;
        }
        // 第二趟遍历，在原链表上处理 random 节点
        iter = head;
        while(iter != nullptr)
        {
            if(iter -> random != nullptr)
                iter -> next -> random = iter -> random -> next;
            else
                iter -> next -> random = nullptr;
            iter = iter -> next -> next;
        }
        // 第三趟遍历，分离链表
        iter = head;
        Node *dummy = new Node(0);
        Node *cur = dummy;
        while(iter != nullptr)
        {
            cur -> next = iter -> next;
            iter -> next = iter -> next -> next;
            cur = cur -> next;
            iter = iter -> next;
        }
        cur -> next = nullptr;
        return dummy -> next;
    }
};
