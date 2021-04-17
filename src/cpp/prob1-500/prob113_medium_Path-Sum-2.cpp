// prob113: Path Sum 2

/*
 * Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
 * Note: A leaf is a node with no children.
 */

#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if(!root) return vector<vector<int> >();
        vector<vector<int> > results;
        vector<int> path;
        int cur_sum = root -> val;
        path.push_back(root -> val);
        _preOrder(root, cur_sum, sum, path, results);
        return results;
    }

private:
    void _preOrder(TreeNode* root, int& sum, int target, vector<int>& path, vector<vector<int> >& results)
    {
        // 调用方保证 root 合法

        if(!(root -> left ) && !(root -> right))
        {
            if(sum == target)
                results.push_back(path);
            return;
        }

        if(root -> left)
        {
            sum += root -> left -> val;
            path.push_back(root -> left -> val);
            _preOrder(root -> left, sum, target, path, results);
            path.pop_back();
            sum -= root -> left -> val;
        }
        if(root -> right)
        {
            sum += root -> right -> val;
            path.push_back(root -> right -> val);
            _preOrder(root -> right, sum, target, path, results);
            path.pop_back();
            sum -= root -> right -> val;
        }
    }
};
