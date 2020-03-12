// prob1145: Binary Tree Coloring Game

/*
 * https://leetcode.com/problems/binary-tree-coloring-game/
 */

/*
 * Constraints:
 * root is the root of a binary tree with n nodes and distinct node values from 1 to n.
 * n is odd.
 * 1 <= x <= n <= 100
 */

#include <unordered_set>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        int k = n / 2;
        unordered_set<int> setting; // 胜点
        _postOrder(root, k, setting);
        auto it = setting.find(x);
        return it == setting.end();
    }

private:
    int _postOrder(TreeNode* root, int k, unordered_set<int>& setting)
    {
        if(!root) return 0;

        int cnt_left = _postOrder(root -> left, k, setting);
        int cnt_right = _postOrder(root -> right, k, setting);
        int cnt = 1 + cnt_left + cnt_right;
        if(cnt >= k + 1 && cnt_left <= k && cnt_right <= k)
            setting.insert(root -> val);
        return cnt;
    }
};
