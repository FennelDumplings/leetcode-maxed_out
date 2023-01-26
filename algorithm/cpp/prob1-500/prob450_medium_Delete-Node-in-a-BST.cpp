// prob450: Delete Node in a BST

/*
 * Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.
 * Basically, the deletion can be divided into two stages:
 * Search for a node to remove.
 * If the node is found, delete the node.
 * Note: Time complexity should be O(height of tree).
 */

#include "include/Node.h"
#include <algorithm>

using namespace std;

class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(!root) return nullptr;
        if(root -> val < key)
        {
            root -> right = deleteNode(root -> right, key);
            return root;
        }
        if(root -> val > key)
        {
            root -> left = deleteNode(root -> left, key);
            return root;
        }
        if(!root -> left)
        {
            TreeNode *right = root -> right;
            delete root;
            root = nullptr;
            return right;
        }
        if(!root -> right)
        {
            TreeNode *left = root -> left;
            delete root;
            root = nullptr;
            return left;
        }
        TreeNode* precursor = root -> left;
        while(precursor -> right)
            precursor = precursor -> right;
        swap(root -> val, precursor -> val);
        root -> left = deleteNode(root -> left, key);
        return root;
    }
};
