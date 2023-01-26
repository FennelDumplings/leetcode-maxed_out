// prob872: Leaf-Similar Trees

/*
 * Consider all the leaves of a binary tree.  From left to right order, the values of those leaves form a leaf value sequence.
 * For example, in the given tree above, the leaf value sequence is (6, 7, 4, 9, 8).
 * Two binary trees are considered leaf-similar if their leaf value sequence is the same.
 * Return true if and only if the two given trees with head nodes root1 and root2 are leaf-similar.
 */

/*
 * Constraints:
 * Both of the given trees will have between 1 and 200 nodes.
 * Both of the given trees will have values between 0 and 200
 */

#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> seq1, seq2;
        _preOrder(root1, seq1);
        _preOrder(root2, seq2);
        int n1 = seq1.size(), n2 = seq2.size();
        if(n1 != n2) return false;
        for(int i = 0; i < n1; ++i)
            if(seq1[i] != seq2[i])
                return false;
        return true;
    }

private:
    void _preOrder(TreeNode* root, vector<int>& seq)
    {
        if(!(root -> left) && !(root -> right))
        {
            seq.push_back(root -> val);
            return;
        }

        if(root -> left)
            _preOrder(root -> left, seq);
        if(root -> right)
            _preOrder(root -> right, seq);
    }
};
