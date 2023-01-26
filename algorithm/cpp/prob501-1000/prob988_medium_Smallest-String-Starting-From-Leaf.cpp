// prob988: Smallest String Starting From Leaf

/*
 * Given the root of a binary tree, each node has a value from 0 to 25 representing the letters 'a' to 'z': a
 * value of 0 represents 'a', a value of 1 represents 'b', and so on.
 * Find the lexicographically smallest string that starts at a leaf of this tree and ends at the root.
 * (As a reminder, any shorter prefix of a string is lexicographically smaller: for example, "ab" is lexicographically
 * smaller than "aba".  A leaf of a node is a node that has no children.)
 */

/*
 * Example 1:
 * Input: [0,1,2,3,4,3,4]
 * Output: "dba"
 * Example 2:
 * Input: [25,1,3,1,3,0,2]
 * Output: "adz"
 * Example 3:
 * Input: [2,2,1,null,1,0,null,0]
 * Output: "abc"
 */

/*
 * Note:
 * The number of nodes in the given tree will be between 1 and 8500.
 * Each node in the tree will have a value between 0 and 25.
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "include/Node.h"

using namespace std;

// 100ms
class Solution {
public:
    string smallestFromLeaf(TreeNode* root) {
        unordered_map<TreeNode*, TreeNode*> father;
        father[root] = nullptr;
        vector<TreeNode*> leaves;
        _preOrder(root, leaves, father);
        Cmp cmp(father);
        sort(leaves.begin(), leaves.end(), cmp);
        string result;
        TreeNode *iter = leaves[0];
        while(iter)
        {
            result += (iter -> val) + 'a';
            iter = father[iter];
        }
        return result;
    }

private:
    void _preOrder(TreeNode* root, vector<TreeNode*>& leaves, unordered_map<TreeNode*, TreeNode*>& father)
    {
        if(!root -> left && !root -> right)
            leaves.push_back(root);

        if(root -> left)
        {
            father[root -> left] = root;
            _preOrder(root -> left, leaves, father);
        }
        if(root -> right)
        {
            father[root -> right] = root;
            _preOrder(root -> right, leaves, father);
        }
    }

    struct Cmp
    {
        unordered_map<TreeNode*, TreeNode*>& father;
        Cmp(unordered_map<TreeNode*, TreeNode*>& father):father(father){}
        bool operator()(TreeNode*& leaf1, TreeNode*& leaf2)
        {
            TreeNode *iter1 = leaf1, *iter2 = leaf2;
            while(iter1 && iter2 && iter1 -> val == iter2 -> val)
            {
                iter1 = father[iter1];
                iter2 = father[iter2];
            }
            if(!iter2) return false;
            if(!iter1) return true;
            return iter1 -> val < iter2 -> val;
        }
    };
};

// dfs 过程中维护最小字符串
// 20ms
class Solution_2 {
public:
    string smallestFromLeaf(TreeNode* root) {
        if(!root) return "";
        string cur_str(1, root -> val + 'a');
        string min_str = "";
        _preOrder(root, cur_str, min_str);
        return min_str;
    }

private:
    void _preOrder(TreeNode* root, string& cur_str, string& min_str)
    {
        if(!root -> left && !root -> right)
        {
            reverse(cur_str.begin(), cur_str.end());
            if(min_str.empty())
                min_str = cur_str;
            else
                min_str = min(min_str, cur_str);
            reverse(cur_str.begin(), cur_str.end());
            return;
        }

        if(root -> left)
        {
            cur_str += root -> left -> val + 'a';
            _preOrder(root -> left, cur_str, min_str);
            cur_str.pop_back();
        }
        if(root -> right)
        {
            cur_str += root -> right -> val + 'a';
            _preOrder(root -> right, cur_str, min_str);
            cur_str.pop_back();
        }
    }
};
