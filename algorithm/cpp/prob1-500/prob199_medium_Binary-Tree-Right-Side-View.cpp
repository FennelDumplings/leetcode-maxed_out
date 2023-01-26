// prob199: Binary Tree Right Side View

/*
 * Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.
 */

/*
 * Example:
 * Input: [1,2,3,null,5,null,4]
 * Output: [1, 3, 4]
 * Explanation:
 *    1            <---
 *  /   \
 * 2     3         <---
 *  \     \
 *   5     4       <---
 */

#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if(!root) return vector<int>();
        vector<int> result;
        dfs(root, result, 0);
        return result;
    }

private:
    void dfs(TreeNode* root, vector<int>& result, int level)
    {
        if(level == (int)result.size())
            result.push_back(root -> val);
        if(root -> right)
            dfs(root -> right, result, level + 1);
        if(root -> left)
            dfs(root -> left, result, level + 1);
    }
};
