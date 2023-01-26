// interview36: 二叉搜索树与双向链表

/*
 * https://leetcode-cn.com/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof/
 */

class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = nullptr;
        right = nullptr;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if(!root) return nullptr;
        Node *head = nullptr;
        Node *prev = nullptr;
        _inOrder(root, head, prev);
        prev -> right = head;
        head -> left = prev;
        return head;
    }

private:
    void _inOrder(Node* node, Node*& head, Node*& prev)
    {
        if(node -> left)
            _inOrder(node -> left, head, prev);

        if(!head) head = node;
        if(prev)
        {
            prev -> right = node;
            node -> left = prev;
        }
        prev = node;

        if(node -> right)
            _inOrder(node -> right, head, prev);
    }
};
