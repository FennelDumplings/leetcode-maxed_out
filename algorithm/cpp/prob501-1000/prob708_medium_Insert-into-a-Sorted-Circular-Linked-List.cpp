// prob708: Insert into a Sorted Circular Linked List

/*
 * https://leetcode-cn.com/problems/insert-into-a-sorted-circular-linked-list/
 */

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = nullptr;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};

class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        if(!head)
        {
            head = new Node(insertVal);
            head -> next = head;
            return head;
        }
        if(head -> next == head)
        {
            head -> next = new Node(insertVal);
            head -> next -> next = head;
            return head;
        }
        // 找到起点 p
        Node *p = head;
        while(p -> val <= p -> next -> val && p -> next != head)
        {
            if(p -> val < insertVal && insertVal <= p -> next -> val)
            {
                Node *tmp = p -> next;
                p -> next = new Node(insertVal);
                p -> next -> next = tmp;
                return head;
            }
            p = p -> next;
        }
        // p -> val > p -> next -> val
        // p -> next 是开头
        if(insertVal > p -> val || insertVal <= p -> next -> val)
        {
            Node *tmp = p -> next;
            p -> next = new Node(insertVal);
            p -> next -> next = tmp;
            return head;
        }
        p = p -> next;
        while(p -> val <= p -> next -> val && p -> next != head)
        {
            if(p -> val < insertVal && insertVal <= p -> next -> val)
            {
                Node *tmp = p -> next;
                p -> next = new Node(insertVal);
                p -> next -> next = tmp;
                return head;
            }
            p = p -> next;
        }
        Node *tmp = p -> next;
        p -> next = new Node(insertVal);
        p -> next -> next = tmp;
        return head;
    }
};
