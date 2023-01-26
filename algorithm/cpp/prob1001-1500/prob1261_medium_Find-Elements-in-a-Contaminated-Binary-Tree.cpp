// prob1261: Find Elements in a Contaminated Binary Tree

/*
 * https://leetcode-cn.com/problems/find-elements-in-a-contaminated-binary-tree/
 */


#include "include/Node.h"
#include <stack>

using namespace std;

class FindElements {
public:
    FindElements(TreeNode* root):root(root) {
        if(!root) return;
        root -> val = 0;
        _preOrder(root);
    }

    bool find(int target) {
        if(!root) return false;
        if(target == 0) return true;
        stack<bool> st;
        while(target)
        {
            if(target & 1)
                st.push(true);
            else
                st.push(false);
            target = (target - 1) / 2;
        }
        return _find(root, st);
    }

private:
    TreeNode *root;

    bool _find(TreeNode* node, stack<bool>& path)
    {
        if(path.empty())
            return true;
        bool flag = path.top();
        path.pop();
        if(flag)
        {
            if(node -> left)
                return _find(node -> left, path);
            else
                return false;
        }
        else
        {
            if(node -> right)
                return _find(node -> right, path);
            else
                return false;
        }
    }

    void _preOrder(TreeNode* node)
    {
        if(node -> left)
        {
            node -> left -> val = (node -> val) * 2 + 1;
            _preOrder(node -> left);
        }
        if(node -> right)
        {
            node -> right -> val = (node -> val) * 2 + 2;
            _preOrder(node -> right);
        }
    }
};
