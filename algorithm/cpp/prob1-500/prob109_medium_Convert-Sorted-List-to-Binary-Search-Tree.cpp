// prob109: Convert Sorted List to Binary Search Tree

/*
 * Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
 * For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two
 * subtrees of every node never differ by more than 1.
 */

/*
 * Example:
 * Given the sorted linked list: [-10,-3,0,5,9],
 * One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:
 *       0
 *      / \
 *    -3   9
 *    /   /
 *  -10  5
 */

#include "include/Node.h"
#include <vector>

using namespace std;

class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if(!head) return nullptr;
        vector<ListNode*> nodes;
        ListNode *iter = head;
        while(iter)
        {
            nodes.push_back(iter);
            iter = iter -> next;
        }
        int n = nodes.size();
        return _build(nodes, 0, n - 1);
    }

private:
    TreeNode* _build(const vector<ListNode*>& nodes, int left, int right)
    {
        if(left > right) return nullptr;
        if(left == right) return new TreeNode(nodes[left] -> val);

        int mid = left + (right - left) / 2;
        TreeNode *root = new TreeNode(nodes[mid] -> val);
        if(left <= mid - 1)
        {
            TreeNode *left_root = _build(nodes, left, mid - 1);
            root -> left = left_root;
        }
        if(mid + 1 <= right)
        {
            TreeNode *right_root = _build(nodes, mid + 1, right);
            root -> right = right_root;
        }
        return root;
    }
};
