// prob652: Find Duplicate Subtrees

/*
 * Given a binary tree, return all duplicate subtrees. For each kind of duplicate subtrees,
 * you only need to return the root node of any one of them.
 * Two trees are duplicate if they have the same structure with same node values.
 */

/*
 * Example 1:
 *        1
 *       / \
 *      2   3
 *     /   / \
 *    4   2   4
 *       /
 *      4
 *The following are two duplicate subtrees:
 *      2
 *     /
 *    4
 *and
 *    4
 */

#include "include/Node.h"
#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

class Solution {
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        if(!root) return vector<TreeNode*>();
        unordered_set<string> setting;
        unordered_set<string> used_setting;
        vector<TreeNode*> result;
        _postOrder(root, setting, used_setting, result);
        return result;
    }

private:
    string _postOrder(TreeNode* root, unordered_set<string>& setting, unordered_set<string>& used_setting, vector<TreeNode*>& result)
    {
        string str_left(1, '#'), str_right(1, '#');
        if(root -> left)
            str_left = _postOrder(root -> left, setting, used_setting, result);
        if(root -> right)
            str_right = _postOrder(root -> right, setting, used_setting, result);

        string str = str_left + ',' + str_right + ',' + to_string(root -> val);
        if(setting.find(str) != setting.end())
        {
            if(used_setting.find(str) == used_setting.end())
            {
                used_setting.insert(str);
                result.push_back(root);
            }
        }
        else
            setting.insert(str);
        return str;
    }
};
