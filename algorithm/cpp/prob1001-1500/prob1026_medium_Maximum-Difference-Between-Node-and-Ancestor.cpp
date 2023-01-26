// prob1026: Maximum Difference Between Node and Ancestor

/*
 * Given the root of a binary tree, find the maximum value V for which there exists different nodes A and B
 * where V = |A.val - B.val| and A is an ancestor of B.
 * (A node A is an ancestor of B if either: any child of A is equal to B, or any child of A is an ancestor of B.)
 */

/*
 * Example 1:
 * Input: [8,3,10,1,6,null,14,null,null,4,7,13]
 * Output: 7
 * Explanation:
 * We have various ancestor-node differences, some of which are given below :
 * |8 - 3| = 5
 * |3 - 7| = 4
 * |8 - 1| = 7
 * |10 - 13| = 3
 * Among all possible differences, the maximum value of 7 is obtained by |8 - 1| = 7.
 */

/*
 * Note:
 * The number of nodes in the tree is between 2 and 5000.
 * Each node will have value between 0 and 100000.
 */

#include "include/Node.h"
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

class Solution {
public:
    int maxAncestorDiff(TreeNode* root) {
        int ans = 0;
        _postOrder(root, ans);
        return ans;
    }

private:
    using PII = pair<int, int>;

    PII _postOrder(TreeNode* root, int& ans)
    {
        // 返回 {min, max}
        PII left({INT_MAX, INT_MIN}), right({INT_MAX, INT_MIN});
        if(root -> left)
        {
            left = _postOrder(root -> left, ans);
        }
        if(root -> right)
        {
            right = _postOrder(root -> right, ans);
        }
        PII result({root -> val, root -> val});
        result.first = min(result.first, left.first);
        result.first = min(result.first, right.first);
        result.second = max(result.second, left.second);
        result.second = max(result.second, right.second);
        ans = max(ans, abs(root -> val - result.first));
        ans = max(ans, abs(result.second) - root -> val);
        return result;
    }
};
