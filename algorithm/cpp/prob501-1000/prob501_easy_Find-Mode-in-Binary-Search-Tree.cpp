// prob501: Find Mode in Binary Search Tree

/*
 * Given a binary search tree (BST) with duplicates, find all the mode(s) (the most frequently occurred element) in the given BST.
 */

/*
 * BST [1,null,2,2],
 *    1
 *     \
 *      2
 *     /
 *    2
 * return [2].
 * Note: If a tree has more than one mode, you can return them in any order.
 */

/*
 * Follow up: Could you do that without using any extra space? (Assume that the implicit stack space incurred due to recursion does not count).
 */

#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<int> findMode(TreeNode* root) {
        if(!root) return vector<int>();
        vector<int> result;
        int cnt = 0;
        int max_cnt = 0;
        _inOrder(root, result, cnt, max_cnt);
        if(cnt < max_cnt) result.pop_back();
        return result;
    }

private:
    void _inOrder(TreeNode* root, vector<int>& result, int& cnt, int& max_cnt)
    {
        if(root -> left)
        {
            _inOrder(root -> left, result, cnt, max_cnt);
        }

        int cur = root -> val;
        if(result.empty())
        {
            result.push_back(cur);
            cnt = 1;
        }
        else if(cur != result.back())
        {
            if(cnt < max_cnt)
                result.pop_back();
            else if(cnt > max_cnt)
            {
                int tmp = result.back();
                result.clear();
                result.push_back(tmp);
                max_cnt = cnt;
            }
            result.push_back(cur);
            cnt = 1;
        }
        else
        {
            ++cnt;
            if(cnt > max_cnt)
            {
                result.clear();
                result.push_back(cur);
                max_cnt = cnt;
            }
        }

        if(root -> right)
        {
            _inOrder(root -> right, result, cnt, max_cnt);
        }
    }
};
