// prob257: Binary Tree Paths

/*
 * Given a binary tree, return all root-to-leaf paths.
 */

/*
 * Example:
 * Input:
 *
 *    1
 *  /   \
 * 2     3
 *  \
 *   5
 *
 * Output: ["1->2->5", "1->3"]
 * Explanation: All root-to-leaf paths are: 1->2->5, 1->3
 */

#include <vector>
#include <string>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        if(!root) return vector<string>();
        vector<string> result;
        string item;
        _preOrder(root, result, item);
        return result;
    }

private:
    void _preOrder(TreeNode* root, vector<string>& result, string& item)
    {
        int len = item.size();
        if(!(root -> left) && !(root -> right))
        {
            item += to_string(root -> val);
            result.push_back(item);
            item.erase(len);
            return;
        }

        item += to_string(root -> val) + "->";
        if(root -> left)
            _preOrder(root -> left, result, item);
        if(root -> right)
            _preOrder(root -> right, result, item);
        item.erase(len);
    }
};
