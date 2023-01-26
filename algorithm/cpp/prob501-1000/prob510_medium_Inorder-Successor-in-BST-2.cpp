// prob510: Inorder Successor in BST II

/*
 * Given a node in a binary search tree, find the in-order successor of that node in the BST.
 * If that node has no in-order successor, return null.
 * The successor of a node is the node with the smallest key greater than node.val.
 * You will have direct access to the node but not to the root of the tree.
 * Each node will have a reference to its parent node. Below is the definition for Node:
 */

class Node {
public:
    int val;
    Node *left;
    Node *right;
    Node *parent;
};

class Solution {
public:
    Node* inorderSuccessor(Node* node) {
        if(!node) return nullptr;
        if(node -> right)
        {
            Node *iter = node -> right;
            while(iter -> left)
                iter = iter -> left;
            return iter;
        }
        Node *iter = node;
        while(iter -> parent && iter -> parent -> left != iter)
            iter = iter -> parent;
        return iter -> parent;
    }
};

