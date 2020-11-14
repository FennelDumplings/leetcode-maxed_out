// prob1484: Clone Binary Tree With Random Pointer

/*
 * https://leetcode-cn.com/problems/clone-binary-tree-with-random-pointer/
 */

/**
 * Definition for a binary tree node.
 */

#include <unordered_map>

using namespace std;

struct Node {
    int val;
    Node *left;
    Node *right;
    Node *random;
    Node() : val(0), left(nullptr), right(nullptr), random(nullptr) {}
    Node(int x) : val(x), left(nullptr), right(nullptr), random(nullptr) {}
    Node(int x, Node *left, Node *right, Node *random) : val(x), left(left), right(right), random(random) {}
};

struct NodeCopy {
    int val;
    NodeCopy *left;
    NodeCopy *right;
    NodeCopy *random;
    NodeCopy() : val(0), left(nullptr), right(nullptr), random(nullptr) {}
    NodeCopy(int x) : val(x), left(nullptr), right(nullptr), random(nullptr) {}
    NodeCopy(int x, NodeCopy *left, NodeCopy *right, NodeCopy *random) : val(x), left(left), right(right), random(random) {}
};


class Solution {
public:
    NodeCopy* copyRandomBinaryTree(Node* root) {
        if(!root) return nullptr;
        NodeCopy *clone = dfs1(root);
        dfs2(clone);
        return clone;
    }

private:
    unordered_map<Node*, NodeCopy*> mapping1;
    unordered_map<NodeCopy*, Node*> mapping2;

    void dfs2(NodeCopy* node)
    {
        if(mapping2[node] -> random)
            node -> random = mapping1[mapping2[node] -> random];
        if(node -> left)
            dfs2(node -> left);
        if(node -> right)
            dfs2(node -> right);
    }

    NodeCopy* dfs1(Node* node)
    {
        NodeCopy *left = nullptr, *right = nullptr;
        if(node -> left)
            left = dfs1(node -> left);
        if(node -> right)
            right = dfs1(node -> right);
        NodeCopy *clone = new NodeCopy(node -> val);
        clone -> left = left;
        clone -> right = right;
        mapping1[node] = clone;
        mapping2[clone] = node;
        return clone;
    }
};
