// prob116: Populating Next Right Pointers in Each Node

/*
 * You are given a perfect binary tree where all leaves are on the same level, and every parent has two children.
 * The binary tree has the following definition:
 * struct Node {
 *   int val;
 *   Node *left;
 *   Node *right;
 *   Node *next;
 * }
 */

/*
 * Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
 * Initially, all next pointers are set to NULL.
 */

/*
 * Follow up:
 * You may only use constant extra space.
 * Recursive approach is fine, you may assume implicit stack space does not count as extra space for this problem.
 */

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
};

class Solution {
public:
    Node* connect(Node* root) {
        if(!root) return nullptr;
        dfs(root);
        return root;
    }

private:
    void dfs(Node* root)
    {
        if(root -> left)
        {
            // 满二叉树
            root -> left -> next = root -> right;
            dfs(root -> left);
            dfs(root -> right);
            if(root -> next)
            {
                root -> right -> next = root -> next -> left;
            }
        }
    }
};

