// Prob965 Univalued Binary Tree

/*
 * A binary tree is univalued if every node in the tree has the same value.
 * Return true if and only if the given tree is univalued.
 */

/*
 * The number of nodes in the given tree will be in the range [1, 100].
 * Each node's value will be an integer in the range [0, 99].
 */


#include "include/Node.h"
#include <iostream>
using namespace std;


class Solution
{
public:
    bool isUnivalTree(TreeNode* root)
    {
        if(root == nullptr) return false;
        int root_value = root -> val;
        return _isUnivalTree(root, root_value);
    }

    bool _isUnivalTree(TreeNode* root, int root_value)
    {
        if(root -> left == nullptr and root -> right == nullptr)
            return true;
        else if(root -> left == nullptr)
        {
            if(root -> right -> val != root_value)
                return false;
            else
                return _isUnivalTree(root -> right, root_value);
        }
        else if(root -> right == nullptr)
        {
            if(root -> left -> val != root_value)
                return false;
            else
                return _isUnivalTree(root -> left, root_value);
        }
        else
        {
            if(root -> left -> val == root_value && root -> right -> val == root_value)
                return _isUnivalTree(root -> left, root_value) && _isUnivalTree(root -> right, root_value);
            else
                return false;
        }
    }
};


int main()
{
    return 0;
}
