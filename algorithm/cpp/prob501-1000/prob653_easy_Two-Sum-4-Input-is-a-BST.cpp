// prob653: Two Sum IV - Input is a BST

/*
 * Given a Binary Search Tree and a target number, return true if there exist two elements
 * in the BST such that their sum is equal to the given target.
 */

#include <unordered_set>
#include <vector>
#include <stack>
#include "include/Node.h"

using namespace std;

// 任意遍历 +　哈希表
// 48ms, 27M
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        unordered_set<int> setting;
        // return _inOrderTraversal(root, k, setting);
        return _preOrderTraversal(root, k, setting);
    }

private:
    bool _inOrderTraversal(TreeNode* root, int k, unordered_set<int>& setting)
    {
        if(!root) return false;
        bool flag_left = _inOrderTraversal(root -> left, k, setting);
        int gap = k - root -> val;
        if(setting.find(gap) != setting.end())
            return true;
        else
            setting.insert(root -> val);
        bool flag_right = _inOrderTraversal(root -> right, k, setting);
        return flag_left || flag_right;
    }

    bool _preOrderTraversal(TreeNode* root, int k, unordered_set<int>& setting)
    {
        if(!root) return false;
        int gap = k - root -> val;
        if(setting.find(gap) != setting.end())
            return true;
        else
            setting.insert(root -> val);
        bool flag_left = _inOrderTraversal(root -> left, k, setting);
        bool flag_right = _inOrderTraversal(root -> right, k, setting);
        return flag_left || flag_right;
    }
};

// 中序遍历 + 双指针, 开双栈也需要 O(N) 空间
// 40ms, 24M
class Solution_2 {
public:
    bool findTarget(TreeNode* root, int k) {
        if(!root) return false;
        vector<int> vec;
        _inOrderTraversal(root, vec);
        int n = vec.size();
        if(n == 1) return false;
        int left = 0, right = n - 1;
        while(left < right)
        {
            int sum = vec[left] + vec[right];
            if(sum == k)
                return true;
            else if(sum > k)
                --right;
            else
                ++left;
        }
        return false;
    }

private:
    void _inOrderTraversal(TreeNode* root, vector<int>& vec)
    {
        if(!root) return;
        _inOrderTraversal(root -> left, vec);
        vec.push_back(root -> val);
        _inOrderTraversal(root -> right, vec);
    }
};

// 直接在遍历过程中双指针
// 开双栈
class Solution_3 {
public:
    bool findTarget(TreeNode* root, int k) {
        if(!root) return false;

        stack<TreeNode*> leftStack;
        pullLeft(leftStack, root);
        TreeNode *left = leftStack.top();
        leftStack.pop();
        stack<TreeNode*> rightStack;
        pullRight(rightStack, root);
        TreeNode *right = rightStack.top();
        rightStack.pop();

        while (left != right)
        {
            if((left -> val + right -> val) == k)
                return true;
            else if ((left -> val + right -> val) > k)
            {
                pullRight(rightStack, right -> left);
                right = rightStack.top();
                rightStack.pop();
            }
            else
            {
                pullLeft(leftStack, left -> right);
                left = leftStack.top();
                leftStack.pop();
            }
        }
        return false;
    }

private:
    void pullRight(stack<TreeNode*>& rightStack, TreeNode* node) {
        // node 以及 node -> right 进栈
        while (node != nullptr)
        {
            rightStack.push(node);
            node = node -> right;
        }
    }

    void pullLeft(stack<TreeNode*>& leftStack, TreeNode* node) {
        // node 以及 node -> left 进栈
        while (node != nullptr)
        {
            leftStack.push(node);
            node = node -> left;
        }
    }
};
