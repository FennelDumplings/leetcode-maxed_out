// interview34: 二叉树中和为某一值的路径

/*
 * https://leetcode-cn.com/problems/er-cha-shu-zhong-he-wei-mou-yi-zhi-de-lu-jing-lcof/
 */

#include <vector>
#include "../../include/Node.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int target) {
        if(!root) return {};
        vector<vector<int>> result;
        vector<int> path;
        int sum = 0;
        path.push_back(root -> val);
        sum += root -> val;
        _preOrder(root, target, sum, path, result);
        return result;
    }

private:
    void _preOrder(TreeNode* node, int target, int& sum, vector<int>& path, vector<vector<int>>& result)
    {
        if(!node -> left && !node -> right)
        {
            if(sum == target)
            {
                result.push_back(path);
                return;
            }
        }

        if(node -> left)
        {
            sum += node -> left -> val;
            path.push_back(node -> left -> val);
            _preOrder(node -> left, target, sum, path, result);
            path.pop_back();
            sum -= node -> left -> val;
        }
        if(node -> right)
        {
            sum += node -> right -> val;
            path.push_back(node -> right -> val);
            _preOrder(node -> right, target, sum, path, result);
            path.pop_back();
            sum -= node -> right -> val;
        }
    }
};
