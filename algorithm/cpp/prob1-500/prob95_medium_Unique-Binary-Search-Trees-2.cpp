// prob95: Unique Binary Search Trees

/*
 * Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1 ... n.
 */

/*
 * Example:
 * Input: 3
 * Output:
 * [
 *   [1,null,3,2],
 *   [3,2,null,1],
 *   [3,1,null,null,2],
 *   [2,1,3],
 *   [1,null,2,null,3]
 * ]
 * Explanation:
 * The above output corresponds to the 5 unique BST's shown below:
 *
 *    1         3     3      2      1
 *     \       /     /      / \      \
 *      3     2     1      1   3      2
 *     /     /       \                 \
 *    2     1         2                 3
 */

#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if(n < 1) return vector<TreeNode*>();
        return dfs(1, n);
     }

private:
    vector<TreeNode*> dfs(int l, int r)
    {
        vector<TreeNode*> res;
        if(l > r)
        {
            res.push_back(nullptr);
            return res;
        }
        for(int i = l; i <= r; ++i)
        {
            auto left = dfs(l, i - 1);
            auto right = dfs(i + 1, r);
            for(auto &lt: left)
                for(auto &rt: right)
                {
                    auto root = new TreeNode(i);
                    root -> left = lt;
                    root -> right = rt;
                    res.push_back(root);
                }
        }
        return res;
    }
};
