// prob1305: All Elements in Two Binary Search Trees

/*
 * https://leetcode-cn.com/problems/all-elements-in-two-binary-search-trees/
 */

#include "include/Node.h"
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        if(!root1 && !root2) return {};
        vector<int> vec1, vec2;
        if(root1)
            _inOrder(root1, vec1);
        if(root2)
            _inOrder(root2, vec2);
        int n1 = vec1.size();
        int n2 = vec2.size();
        vector<int> vec(n1 + n2);
        merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), vec);
        return vec;
    }

private:
    void _inOrder(TreeNode* node, vector<int>& vec)
    {
        if(node -> left)
            _inOrder(node -> left, vec);
        vec.push_back(node -> val);
        if(node -> right)
            _inOrder(node -> right, vec);
    }
};
