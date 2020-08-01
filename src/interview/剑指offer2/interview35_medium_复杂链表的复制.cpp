// interview35: 复杂链表的复制

/*
 * https://leetcode-cn.com/problems/fu-za-lian-biao-de-fu-zhi-lcof/
 */

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
        if(!head) return nullptr;
        unordered_map<Node*, Node*> mapping1; // 新 node -> 老 node
        unordered_map<Node*, Node*> mapping2; // 老 node -> 新 node
        // 新点 -> mapping1 -> 老点 -> 老点的 random -> 新点的 random
        Node dummy_node(0);
        Node *dummy = &dummy_node;
        Node *iter1 = head;
        Node *iter2 = dummy;
        while(iter1)
        {
            iter2 -> next = new Node(iter1 -> val);
            iter2 = iter2 -> next;
            mapping1[iter2] = iter1;
            mapping2[iter1] = iter2;
            iter1 = iter1 -> next;
        }
        iter2 = dummy -> next;;
        iter1 = head;
        while(iter1)
        {
            iter2 -> random = mapping2[mapping1[iter2] -> random];
            iter1 = iter1 -> next;
            iter2 = iter2 -> next;
        }
        return dummy -> next;
    }
};
