// prob655: Print Binary Tree

/*
 * Print a binary tree in an m*n 2D string array following these rules:
 *
 * The row number m should be equal to the height of the given binary tree.
 * The column number n should always be an odd number.
 * The root node's value (in string format) should be put in the exactly middle of the first row it can be put.
 * The column and the row where the root node belongs will separate the rest space into two parts (left-bottom
 * part and right-bottom part). You should print the left subtree in the left-bottom part and print the right
 * subtree in the right-bottom part. The left-bottom part and the right-bottom part should have the same size.
 * Even if one subtree is none while the other is not, you don't need to print anything for the none subtree but
 * still need to leave the space as large as that for the other subtree. However, if two subtrees are none,
 * then you don't need to leave space for both of them.
 * Each unused space should contain an empty string "".
 * Print the subtrees following the same rules.
 */

/*
 * Example 1:
 * Input:
 *      1
 *     /
 *    2
 * Output:
 * [["", "1", ""],
 *  ["2", "", ""]]
 * Example 2:
 * Input:
 *      1
 *     / \
 *    2   3
 *     \
 *      4
 * Output:
 * [["", "", "", "1", "", "", ""],
 *  ["", "2", "", "", "", "3", ""],
 *  ["", "", "4", "", "", "", ""]]
 * Example 3:
 * Input:
 *       1
 *      / \
 *     2   5
 *    /
 *   3
 *  /
 * 4
 * Output:
 * [["",  "",  "", "",  "", "", "", "1", "",  "",  "",  "",  "", "", ""]
 *  ["",  "",  "", "2", "", "", "", "",  "",  "",  "",  "5", "", "", ""]
 *  ["",  "3", "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]
 *  ["4", "",  "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]]
 */

#include <vector>
#include <string>
#include <cmath>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<vector<string>> printTree(TreeNode* root) {
        if(!root) return vector<vector<string> >();
        int h = _postOrder(root);
        int w = pow(2, h) - 1;
        vector<vector<string> > result(h, vector<string>(w, ""));
        _preOrder(root, result, 0, 0, w - 1);
        return result;
    }

private:
    int _postOrder(TreeNode* root)
    {
        int h_left = 0, h_right = 0;
        if(root -> left)
            h_left = _postOrder(root -> left);
        if(root -> right)
            h_right = _postOrder(root -> right);

        return max(h_left, h_right) + 1;
    }

    void _preOrder(TreeNode* root, vector<vector<string> >& result, int row, int left, int right)
    {
        int mid = left + (right - left) / 2;
        result[row][mid] = to_string(root -> val);

        if(root -> left)
            _preOrder(root -> left, result, row + 1, left, mid - 1);
        if(root -> right)
            _preOrder(root -> right, result, row + 1, mid + 1, right);
    }
};
