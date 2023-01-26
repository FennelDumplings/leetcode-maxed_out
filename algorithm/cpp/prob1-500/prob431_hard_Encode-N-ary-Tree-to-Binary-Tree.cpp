// prob431: Encode N-ary Tree to Binary Tree

/*
 * Design an algorithm to encode an N-ary tree into a binary tree and decode the binary tree to get the original N-ary tree. An
 * N-ary tree is a rooted tree in which each node has no more than N children. Similarly, a binary tree is a rooted tree
 * in which each node has no more than 2 children. There is no restriction on how your encode/decode algorithm should work.
 * You just need to ensure that an N-ary tree can be encoded to a binary tree and this binary tree can be decoded to the original N-nary tree structure.
 * Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See following example).
 */

/*
 * Constraints:
 * The height of the n-ary tree is less than or equal to 1000
 * The total number of nodes is between [0, 10^4]
 * Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.
 */

#include <vector>
#include <queue>
#include "include/Node.h"

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

class Codec {
public:
    // Encodes an n-ary tree to a binary tree.
    TreeNode* encode(Node* root) {
        if(!root) return nullptr;
        return _levelOrder(root);
    }

    // Decodes your binary tree to an n-ary tree.
    Node* decode(TreeNode* root) {
        if(!root) return nullptr;
        return _build(root);
    }

private:
    Node* _build(TreeNode* root)
    {
        Node *result = new Node(root -> val);
        queue<TreeNode*> q2;
        q2.push(root);
        queue<Node*> q;
        q.push(result);
        while(!q2.empty())
        {
            TreeNode *node2 = q2.front();
            q2.pop();
            Node *node = q.front();
            q.pop();
            if(!(node2 -> left)) continue;
            TreeNode *iter = node2 -> left;
            while(iter)
            {
                Node *tmp = new Node(iter -> val);
                (node -> children).push_back(tmp);
                q.push(tmp);
                q2.push(iter);
                iter = iter -> right;
            }
        }
        return result;
    }

    TreeNode* _levelOrder(Node* root)
    {
        TreeNode *result = new TreeNode(root -> val);
        queue<TreeNode*> q2;
        q2.push(result);

        queue<Node*> q;
        q.push(root);
        while(!q.empty())
        {
            Node *node = q.front();
            q.pop();
            TreeNode *node2 = q2.front();
            q2.pop();
            int n = (node -> children).size();
            if(n == 0) continue;
            TreeNode *iter = node2;
            for(int i = 0; i < n; ++i)
            {
                Node *child = (node -> children)[i];
                q.push(child);
                TreeNode *tmp = new TreeNode(child -> val);
                q2.push(tmp);
                if(i == 0)
                    iter -> left = tmp;
                else
                    iter -> right = tmp;
                iter = tmp;
            }
        }
        return result;
    }
};
