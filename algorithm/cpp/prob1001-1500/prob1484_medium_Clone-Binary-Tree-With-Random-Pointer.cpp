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
        return dfs(root);
    }

private:
    unordered_map<Node*, NodeCopy*> mapping;

    NodeCopy* dfs(Node* node)
    {
        NodeCopy *new_node = new NodeCopy(node -> val);
        mapping[node] = new_node;
        if(node -> left)
        {
            if(mapping.count(node -> left) > 0)
                new_node -> left = mapping[node -> left];
            else
                new_node -> left = dfs(node -> left);
        }
        if(node -> right)
        {
            if(mapping.count(node -> right) > 0)
                new_node -> right = mapping[node -> right];
            else
                new_node -> right = dfs(node -> right);
        }
        if(node -> random)
        {
            if(mapping.count(node -> random) > 0)
                new_node -> random = mapping[node -> random];
            else
                new_node -> random = dfs(node -> random);
        }
        return new_node;
    }
};
