// prob1022: Sum of Root To Leaf Binary Numbers

/*
 * Given a binary tree, each node has value 0 or 1.  Each root-to-leaf path represents a binary number
 * starting with the most significant bit.  For example, if the path is 0 -> 1 -> 1 -> 0 -> 1,
 * then this could represent 01101 in binary, which is 13.
 * For all leaves in the tree, consider the numbers represented by the path from the root to that leaf.
 * Return the sum of these numbers.
 */

/*
 * Example 1:
 * Input: [1,0,1,0,1,0,1]
 * Output: 22
 * Explanation: (100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22
 */

/*
 * Note:
 * The number of nodes in the tree is between 1 and 1000.
 * node.val is 0 or 1.
 * The answer will not exceed 2^31 - 1.
 */

#include <string>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    int sumRootToLeaf(TreeNode* root) {
        int result = 0;
        string num_str(1, root -> val + '0');
        _preOrder(root, result, num_str);
        return result;
    }

private:
    const int MOD = 1e9 + 7;
    using ll = long long;

    void _preOrder(TreeNode* root, int& result, string& num_str)
    {
        if(!root -> left && !root -> right)
        {
            result = ((ll)result + _str2int(num_str)) % MOD;
            return;
        }
        if(root -> left)
        {
            num_str += root -> left -> val + '0';
            _preOrder(root -> left, result, num_str);
            num_str.pop_back();
        }
        if(root -> right)
        {
            num_str += root -> right -> val + '0';
            _preOrder(root -> right, result, num_str);
            num_str.pop_back();
        }
    }

    ll _str2int(const string& num_str)
    {
        int n = num_str.size();
        ll result = num_str[0] - '0';
        for(int i = 1; i <= n - 1; ++i)
        {
            result *= 2;
            result += num_str[i] - '0';
        }
        return result;
    }
};
