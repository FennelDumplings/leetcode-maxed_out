// prob894: All Possible Full Binary Trees

/*
 * A full binary tree is a binary tree where each node has exactly 0 or 2 children.
 * Return a list of all possible full binary trees with N nodes.  Each element of the answer is the root node of one possible tree.
 * Each node of each tree in the answer must have node.val = 0.
 * You may return the final list of trees in any order.
 */

/*
 * Example 1:
 * Input: 7
 * Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
 * Explanation:
 */

/*
 * Note:
 * 1 <= N <= 20
 */

#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<TreeNode*> allPossibleFBT(int N) {
        return _build(N);
    }

private:
    vector<TreeNode*> _build(int N)
    {
        // 返回含 N 个节点的满足条件二叉树的根节点列表
        if(N == 1)
        {
            TreeNode *root = new TreeNode(0);
            return vector<TreeNode*>({root});
        }
        if(N == 3)
        {
            TreeNode *root = new TreeNode(0);
            TreeNode* left = _build(1)[0];
            TreeNode* right = _build(1)[0];
            root -> left = left;
            root -> right = right;
            return vector<TreeNode*>({root});
        }
        // N >= 5
        // 左 1 右 N - 2
        // ...
        // 左 N - 2 右 1
        vector<TreeNode*> result;
        for(int i = 1; i <= N - 2; i += 2)
        {
            vector<TreeNode*> lefts = _build(i);
            vector<TreeNode*> rights = _build(N - 1 - i);
            int n_left = lefts.size();
            int n_right = rights.size();
            for(int j = 0; j < n_left; ++j)
                for(int k = 0; k < n_right; ++k)
                {
                    TreeNode *root = new TreeNode(0);
                    TreeNode * left = _clone(lefts[j]);
                    TreeNode * right = _clone(rights[k]);
                    root -> left = left;
                    root -> right = right;
                    result.push_back(root);
                }
        }
        return result;
    }

    TreeNode* _clone(TreeNode* root)
    {
        TreeNode *new_root = new TreeNode(root -> val);
        if(root -> left)
            new_root -> left = _clone(root -> left);
        if(root -> right)
            new_root -> right = _clone(root -> right);
        return new_root;
    }
};


// 不带 clone 也能过
class Solution_2 {
public:
    vector<TreeNode*> allPossibleFBT(int N) {
        return _build(N);
    }

private:
    vector<TreeNode*> _build(int N)
    {
        // 返回含 N 个节点的满足条件二叉树的根节点列表
        if(N == 1)
        {
            TreeNode *root = new TreeNode(0);
            return vector<TreeNode*>({root});
        }
        if(N == 3)
        {
            TreeNode *root = new TreeNode(0);
            TreeNode* left = _build(1)[0];
            TreeNode* right = _build(1)[0];
            root -> left = left;
            root -> right = right;
            return vector<TreeNode*>({root});
        }
        // N >= 5
        // 左 1 右 N - 2
        // ...
        // 左 N - 2 右 1
        vector<TreeNode*> result;
        for(int i = 1; i <= N - 2; i += 2)
        {
            vector<TreeNode*> lefts = _build(i);
            vector<TreeNode*> rights = _build(N - 1 - i);
            int n_left = lefts.size();
            int n_right = rights.size();
            for(int j = 0; j < n_left; ++j)
                for(int k = 0; k < n_right; ++k)
                {
                    TreeNode *root = new TreeNode(0);
                    root -> left = lefts[j];
                    root -> right = rights[k];
                    result.push_back(root);
                }
        }
        return result;
    }
};


// 记忆化
class Solution_3 {
public:
    vector<TreeNode*> allPossibleFBT(int N) {
        vector<vector<TreeNode*> > dp(N + 1, vector<TreeNode*>());
        return _build(N, dp);
    }

private:
    vector<TreeNode*> _build(int N, vector<vector<TreeNode*> >& dp)
    {
        if(!dp[N].empty())
            return dp[N];

        // 返回含 N 个节点的满足条件二叉树的根节点列表
        if(N == 1)
        {
            TreeNode *root = new TreeNode(0);
            dp[N] = vector<TreeNode*>({root});
            return dp[N];
        }
        if(N == 3)
        {
            TreeNode *root = new TreeNode(0);
            TreeNode* left = _build(1, dp)[0];
            TreeNode* right = _build(1, dp)[0];
            root -> left = left;
            root -> right = right;
            dp[N] = vector<TreeNode*>({root});
            return dp[N];
        }
        // N >= 5
        // 左 1 右 N - 2
        // ...
        // 左 N - 2 右 1
        vector<TreeNode*> result;
        for(int i = 1; i <= N - 2; i += 2)
        {
            vector<TreeNode*> lefts = _build(i, dp);
            vector<TreeNode*> rights = _build(N - 1 - i, dp);
            int n_left = lefts.size();
            int n_right = rights.size();
            for(int j = 0; j < n_left; ++j)
                for(int k = 0; k < n_right; ++k)
                {
                    TreeNode *root = new TreeNode(0);
                    root -> left = lefts[j];
                    root -> right = rights[k];
                    result.push_back(root);
                }
        }
        dp[N] = result;
        return dp[N];
    }
};

// 不返回 vector<TreeNode*>
class Solution_4 {
public:
    vector<TreeNode*> allPossibleFBT(int N) {
        vector<vector<TreeNode*> > dp(N + 1, vector<TreeNode*>());
        _build(N, dp);
        return dp[N];
    }

private:
    void _build(int N, vector<vector<TreeNode*> >& dp)
    {
        if(!dp[N].empty()) return;

        // 返回含 N 个节点的满足条件二叉树的根节点列表
        if(N == 1)
        {
            TreeNode *root = new TreeNode(0);
            dp[N] = vector<TreeNode*>({root});
            return;
        }
        if(N == 3)
        {
            TreeNode *root = new TreeNode(0);
            TreeNode *left = new TreeNode(0);
            TreeNode *right = new TreeNode(0);
            root -> left = left;
            root -> right = right;
            dp[N] = vector<TreeNode*>({root});
            return;
        }
        // N >= 5
        // 左 1 右 N - 2
        // ...
        // 左 N - 2 右 1
        for(int i = 1; i <= N - 2; i += 2)
        {
            _build(i, dp);
            _build(N - 1 - i, dp);
            for(int j = 0; j < (int)dp[i].size(); ++j)
                for(int k = 0; k < (int)dp[N - 1 - i].size(); ++k)
                {
                    TreeNode *root = new TreeNode(0);
                    root -> left = dp[i][j];
                    root -> right = dp[N - 1 - i][k];
                    dp[N].push_back(root);
                }
        }
    }
};
