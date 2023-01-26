// prob1516: Move Sub-Tree of N-Ary Tree

/*
 * https://leetcode-cn.com/problems/move-sub-tree-of-n-ary-tree/
 */

#include <vector>

using namespace std;

class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    Node* moveSubTree(Node* root, Node* p, Node* q) {
        Node *dummy = new Node(0);
        (dummy -> children).push_back(root);
        Node *fa_p = nullptr, *fa_q = nullptr;
        get_fa(dummy, p, q, fa_p, fa_q);
        if(!check(p, q))
        {
            for(Node *child: q -> children)
                if(child == p)
                    return dummy -> children[0];
            (q -> children).push_back(p);
            int m = (fa_p -> children).size();
            for(int i = 0; i < m; ++i)
            {
                if((fa_p -> children)[i] == p)
                {
                    for(int j = i; j < m - 1; ++j)
                        (fa_p -> children)[j] = (fa_p -> children)[j + 1];
                    (fa_p -> children).pop_back();
                    break;
                }
            }
        }
        else
        {
            // q 在 p 的子树中
            (q -> children).push_back(p);
            for(Node *&child: fa_p -> children)
                if(child == p)
                {
                    child = q;
                    break;
                }
            int m = (fa_q -> children).size();
            for(int i = 0; i < m; ++i)
            {
                if((fa_q -> children)[i] == q)
                {
                    for(int j = i; j < m - 1; ++j)
                        (fa_q -> children)[j] = (fa_q -> children)[j + 1];
                    (fa_q -> children).pop_back();
                    break;
                }
            }
        }
        return dummy -> children[0];
    }

private:
    bool check(Node* p, Node* q)
    {
        // q 是否是 p 的子树
        return _preOrder(p, q);
    }

    bool _preOrder(Node* node, const Node* q)
    {
        if(node == q)
            return true;
        for(Node *child: node -> children)
            if(child)
                if(_preOrder(child, q))
                    return true;
        return false;
    }

    void get_fa(Node* node, const Node* p, const Node* q, Node*& fa_p, Node*& fa_q)
    {
        for(Node *child: node -> children)
        {
            if(child == p)
                fa_p = node;
            if(child == q)
                fa_q = node;
            if(fa_p != nullptr && fa_q != nullptr)
                break;
            get_fa(child, p, q, fa_p, fa_q);
        }
    }
};
