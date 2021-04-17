/**
 * Definition for a binary tree node.
 */

#include <vector>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int maxValue(TreeNode* root, int k) {
        vector<int> result = _postOrder(root, k);
        return *max_element(result.begin(), result.end());
    }

private:
    vector<int> _postOrder(TreeNode* node, const int k)
    {
        if(!node)
            return vector<int>(k + 1);
        vector<int> result_left = _postOrder(node -> left, k);
        vector<int> result_right = _postOrder(node -> right, k);

        vector<int> result(k + 1);
        for(int j = 1; j <= k; ++j)
        {
            for(int l = 0; l <= j - 1; ++l)
            {
                int r = j - 1 - l;
                result[j] = max(result[j], result_left[l] + result_right[r] + node -> val);
            }
        }
        int max_l = 0, max_r = 0;
        for(int l = 0; l <= k; ++l)
            max_l = max(max_l, result_left[l]);
        for(int r = 0; r <= k; ++r)
            max_r = max(max_r, result_right[r]);
        result[0] = max_l + max_r;
        return result;
    }
};
