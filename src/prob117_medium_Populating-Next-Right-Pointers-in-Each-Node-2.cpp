// prob117: Populating Next Right Pointers in Each Node II

/*
 * Given a binary tree
 * struct Node {
 *   int val;
 *   Node *left;
 *   Node *right;
 *   Node *next;
 * }
 * Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
 * Initially, all next pointers are set to NULL.
 */

/*
 * Follow up:
 * You may only use constant extra space.
 * Recursive approach is fine, you may assume implicit stack space does not count as extra space for this problem.
 */

/*
 * Constraints:
 * The number of nodes in the given tree is less than 6000.
 * -100 <= node.val <= 100
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
        if(root -> left && root -> right)
            root -> left -> next = root -> right;
        if(root -> next && !_is_leaf(root))
        {
            Node *iter = root;
            while(iter -> next && _is_leaf(iter -> next))
                iter = iter -> next;
            if(iter -> next)
            {
                Node *tmp1, *tmp2;
                if(iter -> next -> left)
                    tmp2 = iter -> next -> left;
                else
                    tmp2 = iter -> next -> right;
                if(root -> right)
                    tmp1 = root -> right;
                else
                    tmp1 = root -> left;
                tmp1 -> next = tmp2;
            }
        }
        if(root -> right)
            dfs(root -> right);
        if(root -> left)
            dfs(root -> left);
    }

    bool _is_leaf(Node* root)
    {
        return !(root -> left) && !(root -> right);
    }
};
