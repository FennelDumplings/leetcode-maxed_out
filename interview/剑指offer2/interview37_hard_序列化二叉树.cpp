// interview37: 序列化二叉树

/*
 * https://leetcode-cn.com/problems/xu-lie-hua-er-cha-shu-lcof/
 */

#include <string>
#include <sstream>
#include "../../include/Node.h"

using namespace std;

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root) return "";
        string result = "";
        _preOrder(root, result);
        result.pop_back();
        return result;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data.empty()) return nullptr;
        int pos = 0;
        int n = data.size();
        while(pos < n && data[pos] != ',')
            ++pos;
        string num_str = data.substr(0, pos);
        stringstream ss;
        int num;
        ss << num_str;
        ss >> num;
        TreeNode *root = new TreeNode(num);
        ++pos;
        dfs(root, data, pos);
        return root;
    }

private:
    void _preOrder(TreeNode* node, string& result)
    {
        if(!node)
        {
            result += "#,";
            return;
        }
        result += to_string(node -> val) + ',';
        _preOrder(node -> left, result);
        _preOrder(node -> right, result);
    }

    void dfs(TreeNode* node, string& data, int& pos)
    {
        int n = data.size();
        if(pos >= n) return;
        int left = pos;
        while(pos < n && data[pos] != ',')
            ++pos;
        string num_str = data.substr(left, pos - left);
        ++pos;
        if(num_str != "#")
        {
            stringstream ss;
            int num;
            ss << num_str;
            ss >> num;
            TreeNode *left = new TreeNode(num);
            node -> left = left;
            dfs(node -> left, data, pos);
        }
        int right = pos;
        while(pos < n && data[pos] != ',')
            ++pos;
        num_str = data.substr(right, pos - right);
        ++pos;
        if(num_str != "#")
        {
            stringstream ss;
            int num;
            ss << num_str;
            ss >> num;
            TreeNode *right = new TreeNode(num);
            node -> right = right;
            dfs(node -> right, data, pos);
        }
    }
};
