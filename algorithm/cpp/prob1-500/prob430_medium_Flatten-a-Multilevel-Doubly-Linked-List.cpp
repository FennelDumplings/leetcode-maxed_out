// prob430: Flatten a Multilevel Doubly Linked List

/*
 * https://leetcode-cn.com/problems/flatten-a-multilevel-doubly-linked-list/
 */

/*
// Definition for a Node.
*/

#include <stack>

using namespace std;

class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
    Node(int v):val(v){}
};

class Solution {
public:
    Node* flatten(Node* head) {
        if(!head) return nullptr;
        Node dummy_node(0);
        Node *dummy = &dummy_node;
        dummy -> next = head;
        stack<Node*> st;
        Node *iter = dummy;
        while(iter -> next || !st.empty())
        {
            if(!iter -> next)
            {
                Node *nxt = st.top();
                st.pop();
                iter -> next = nxt;
                nxt -> prev = iter;
            }
            iter = iter -> next;
            while(iter -> child)
            {
                if(iter -> next)
                    st.push(iter -> next);
                iter -> next = iter -> child;
                iter -> child = nullptr;
                iter -> next -> prev = iter;
                iter = iter -> next;
            }
        }
        return dummy -> next;
    }
};
