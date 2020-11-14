// prob1469: Find All The Lonely Nodes

/*
 * https://leetcode-cn.com/problems/find-all-the-lonely-nodes/
 */

#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<int> getLonelyNodes(TreeNode* root) {
        vector<int> result;
        _preOrder(root, result);
        return result;
    }

private:
    void _preOrder(TreeNode* node, vector<int>& result)
    {
        if(!node -> left && !node -> right)
            return;
        else if(!node -> left)
        {
            result.push_back(node -> right -> val);
            _preOrder(node -> right, result);
        }
        else if(!node -> right)
        {
            result.push_back(node -> left -> val);
            _preOrder(node -> left, result);
        }
        else
        {
            _preOrder(node -> left, result);
            _preOrder(node -> right, result);
        }
    }
};
