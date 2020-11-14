// prob1586: Binary Search Tree Iterator II

/*
 * https://leetcode-cn.com/problems/binary-search-tree-iterator-ii/
 */

#include "include/Node.h"
#include <vector>

using namespace std;

class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        dummy = new TreeNode(-1);
        dummy -> right = root;
        iter = dummy;
    }

    bool hasNext() {
        if(iter -> right != nullptr)
            return true;
        int m = fathers.size();
        TreeNode *f2 = iter;
        for(int i = m - 1; i >= 0; --i)
        {
            TreeNode *f1 = fathers[i];
            if(f1 -> left == f2)
                return true;
            f2 = f1;
        }
        return false;
    }

    int next() {
        if(iter -> right != nullptr)
        {
            if(iter != dummy)
                fathers.push_back(iter);
            iter = iter -> right;
            while(iter -> left != nullptr)
            {
                fathers.push_back(iter);
                iter = iter -> left;
            }
            return iter -> val;
        }
        else
        {
            int m = fathers.size();
            TreeNode *f2 = iter;
            for(int i = m - 1; i >= 0; --i)
            {
                TreeNode *f1 = fathers[i];
                fathers.pop_back();
                if(f1 -> left == f2)
                {
                    iter = f1;
                    return iter -> val;
                }
                else
                    f2 = f1;
            }
            return -1;
        }
    }

    bool hasPrev() {
        if(iter -> left != nullptr)
            return true;
        int m = fathers.size();
        TreeNode *f2 = iter;
        for(int i = m - 1; i >= 0; --i)
        {
            TreeNode *f1 = fathers[i];
            if(f1 -> right == f2)
                return true;
            f2 = f1;
        }
        return false;
    }

    int prev() {
        if(iter -> left != nullptr)
        {
            fathers.push_back(iter);
            iter = iter -> left;
            while(iter -> right != nullptr)
            {
                fathers.push_back(iter);
                iter = iter -> right;
            }
            return iter -> val;
        }
        else
        {
            int m = fathers.size();
            TreeNode *f2 = iter;
            for(int i = m - 1; i >= 0; --i)
            {
                TreeNode *f1 = fathers[i];
                fathers.pop_back();
                if(f1 -> right == f2)
                {
                    iter = f1;
                    return iter -> val;
                }
                else
                    f2 = f1;
            }
            return -1;
        }
    }

private:
    TreeNode *iter;
    TreeNode *dummy;
    vector<TreeNode*> fathers; // [dummy -> iter] 的父亲链
};
