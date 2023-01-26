// prob536: Construct Binary Tree from String

/*
 * You need to construct a binary tree from a string consisting of parenthesis and integers.
 * The whole input represents a binary tree. It contains an integer followed by zero, one or two pairs of parenthesis.
 * The integer represents the root's value and a pair of parenthesis contains a child binary tree with the same structure.
 * You always start to construct the left child node of the parent first if it exists.
 */

/*
 * Example:
 * Input: "4(2(3)(1))(6(5))"
 * Output: return the tree root node representing the following tree:
 *        4
 *      /   \
 *     2     6
 *    / \   /
 *   3   1 5
 */

/*
 * Note:
 * There will only be '(', ')', '-' and '0' ~ '9' in the input string.
 * An empty tree is represented by "" instead of "()".
 */

#include <stack>
#include <string>
#include <sstream>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    TreeNode* str2tree(string s) {
        if(s.empty()) return nullptr;
        int n = s.size();
        int iter = 0;
        int right = _get_num_right(s, iter);
        string str = s.substr(iter, right - iter);
        iter = right;
        int num = _str2int(str);
        TreeNode *root = new TreeNode(num);
        if(iter == n) return root;
        stack<TreeNode*> st1;
        st1.push(root);
        while(iter < n)
        {
            char cur = s[iter];
            if(cur == '(')
            {
                ++iter;
                int right = _get_num_right(s, iter);
                string str = s.substr(iter, right - iter);
                int num = _str2int(str);
                TreeNode *node = new TreeNode(num);
                if(s[iter - 2] == ')')
                    st1.top() -> right = node;
                else
                    st1.top() -> left = node;
                st1.push(node);
                iter = right;
            }
            else if(cur == ')')
            {
                st1.pop();
                ++iter;
            }
        }
        return st1.top();
    }

private:
    int _get_num_right(const string& s, int left)
    {
        int n = s.size();
        if(s[left] == '-') ++left;
        while(left < n && s[left] >= '0' && s[left] <= '9')
            ++left;
        return left;
    }

    int _str2int(const string& str)
    {
        int num;
        stringstream ss;
        ss << str;
        ss >> num;
        return num;
    }
};
