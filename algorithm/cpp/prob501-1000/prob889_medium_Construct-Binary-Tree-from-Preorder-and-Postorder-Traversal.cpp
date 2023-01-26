// prob889: Construct Binary Tree from Preorder and Postorder Traversal

/*
 * Return any binary tree that matches the given preorder and postorder traversals.
 * Values in the traversals pre and post are distinct positive integers.
 */

/*
 * Example 1:
 * Input: pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]
 * Output: [1,2,3,4,5,6,7]
 */

/*
 * Note:
 * 1 <= pre.length == post.length <= 30
 * pre[] and post[] are both permutations of 1, 2, ..., pre.length.
 * It is guaranteed an answer exists. If there exists multiple answers, you can return any of them.
 */

#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        int n = pre.size();
        vector<int> pre_idxs(n + 1, -1);
        for(int i = 0; i < n; ++i)
            pre_idxs[pre[i]] = i;
        vector<int> post_idxs(n + 1, -1);
        for(int i = 0; i < n; ++i)
            post_idxs[post[i]] = i;
        return _build(pre, 0, n - 1, post, 0, n - 1, pre_idxs, post_idxs);
    }

private:
    TreeNode* _build(const vector<int>& pre, int l_pre, int r_pre, const vector<int>& post, int l_post, int r_post,
            const vector<int>& pre_idxs, const vector<int>& post_idxs)
    {
        TreeNode *root = new TreeNode(pre[l_pre]);
        if(l_pre == r_pre)
            return root;

        int pre_right = pre[l_pre + 1];
        int post_left = post[r_post - 1];
        if(pre_right == post_left)
            root -> left = _build(pre, l_pre + 1, r_pre, post, l_post, r_post - 1, pre_idxs, post_idxs);
        else
        {
            root -> left = _build(pre, l_pre + 1, pre_idxs[post_left] - 1, post, l_post, post_idxs[pre_right], pre_idxs, post_idxs);
            root -> right = _build(pre, pre_idxs[post_left], r_pre, post, post_idxs[pre_right] + 1, r_post - 1, pre_idxs, post_idxs);
        }
        return root;
    }
};
