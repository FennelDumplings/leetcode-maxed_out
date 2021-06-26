// prob1430: Check If a String Is a Valid Sequence from Root to Leaves Path in a Binary Tree

/*
 * https://leetcode-cn.com/problems/check-if-a-string-is-a-valid-sequence-from-root-to-leaves-path-in-a-binary-tree/
 */

#include "include/Node.h"
#include <vector>

using namespace std;

class Solution {
public:
    bool isValidSequence(TreeNode* root, vector<int>& arr) {
        return _preOrder(root, 0, arr);
    }

private:
    bool _preOrder(TreeNode* node, int level, const vector<int>& arr)
    {
        int n = arr.size();
        if(level == n)
            return false;
        if(node -> val != arr[level])
            return false;
        // node -> val == arr[level];
        if(!node -> left && !node -> right && level == n - 1)
            return true;
        if(node -> left)
            if(_preOrder(node -> left, level + 1, arr))
                return true;
        if(node -> right)
            if(_preOrder(node -> right, level + 1, arr))
                return true;
        return false;
    }
};
