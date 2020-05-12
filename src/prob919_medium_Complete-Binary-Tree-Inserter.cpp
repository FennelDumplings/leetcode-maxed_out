// prob919: Complete Binary Tree Inserter

/*
 * A complete binary tree is a binary tree in which every level, except possibly the last, is completely filled, and all nodes are as far left as possible.
 * Write a data structure CBTInserter that is initialized with a complete binary tree and supports the following operations:
 * - CBTInserter(TreeNode root) initializes the data structure on a given tree with head node root;
 * - CBTInserter.insert(int v) will insert a TreeNode into the tree with value node.val = v so that the tree remains complete, and
 * returns the value of the parent of the inserted TreeNode;
 * - CBTInserter.get_root() will return the head node of the tree.
 */

/*
 * Example 1:
 * Input: inputs = ["CBTInserter","insert","get_root"], inputs = [[[1]],[2],[]]
 * Output: [null,1,[1,2]]
 * Example 2:
 * Input: inputs = ["CBTInserter","insert","insert","get_root"], inputs = [[[1,2,3,4,5,6]],[7],[8],[]]
 * Output: [null,3,4,[1,2,3,4,5,6,7,8]]
 */

/*
 * Note:
 * The initial given tree is complete and contains between 1 and 1000 nodes.
 * CBTInserter.insert is called at most 10000 times per test case.
 * Every value of a given or inserted node is between 0 and 5000.
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include "include/Node.h"
#include <vector>
#include <queue>

using namespace std;

class CBTInserter {
public:
    CBTInserter(TreeNode* root) {
        // i -> left: i * 2 + 1
        // i -> right: i * 2 + 2
        // i -> father: (i - 1)/2
        tree = vector<TreeNode*>();
        if(root)
            _levelOrder(root);
    }

    void _levelOrder(TreeNode* root)
    {
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            TreeNode *cur = q.front();
            q.pop();
            tree.push_back(cur);
            if(cur -> left)
                q.push(cur -> left);
            if(cur -> right)
                q.push(cur -> right);
        }
    }

    int insert(int v) {
        int idx = tree.size();
        int father_idx = (idx - 1) / 2;
        TreeNode *father = tree[father_idx];
        TreeNode *cur = new TreeNode(v);
        if(!father -> left)
            father -> left = cur;
        else
            father -> right = cur;
        tree.push_back(cur);
        return father -> val;
    }

    TreeNode* get_root() {
        return tree[0];
    }

private:
    vector<TreeNode*> tree;
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(v);
 * TreeNode* param_2 = obj->get_root();
 */
