// prob12214: Two Sum BSTs

/*
 * https://leetcode-cn.com/problems/two-sum-bsts/
 */

#include "include/Node.h"
#include <vector>

using namespace std;

class Solution {
public:
    bool twoSumBSTs(TreeNode* root1, TreeNode* root2, int target) {
        vector<int> vec1;
        _inOrder(root1, vec1);
        vector<int> vec2;
        _inOrder(root2, vec2);
        int n = vec1.size(), m = vec2.size();
        int i = n - 1, j = 0;
        while(i >= 0 && j < m)
        {
            if(vec1[i] + vec2[j] == target)
                return true;
            else if(vec1[i] + vec2[j] < target)
                ++j;
            else
                --i;
        }
        return false;
    }

private:
    void _inOrder(TreeNode* node, vector<int>& vec)
    {
        if(node -> left)
            _inOrder(node -> left, vec);
        vec.push_back(node -> val);
        if(node -> right)
            _inOrder(node -> right, vec);
    }
};
