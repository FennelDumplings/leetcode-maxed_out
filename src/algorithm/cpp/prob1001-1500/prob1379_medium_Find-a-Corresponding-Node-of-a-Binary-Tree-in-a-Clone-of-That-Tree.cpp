// prob1379: Find a Corresponding Node of a Binary Tree in a Clone of That Tree

/*
 * https://leetcode-cn.com/problems/find-a-corresponding-node-of-a-binary-tree-in-a-clone-of-that-tree/
 */

#include "include/Node.h"
#include <string>

using namespace std;

class Solution {
public:
    TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
        string path;
        _preOrder(original, path, target);
        TreeNode *iter = cloned;
        for(char ch: path)
        {
            if(ch == '0')
                iter = iter -> left;
            else
                iter = iter -> right;
        }
        return iter;
    }

private:
    bool _preOrder(TreeNode* node, string& path, TreeNode* target)
    {
        if(node == target)
            return true;
        if(node -> left)
        {
            path += '0';
            if(_preOrder(node -> left, path, target))
                return true;
            path.pop_back();
        }
        if(node -> right)
        {
            path += '1';
            if(_preOrder(node -> right, path, target))
                return true;
            path.pop_back();
        }
        return false;
    }
};
