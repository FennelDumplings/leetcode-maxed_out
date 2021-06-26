// prob297: Serialize and Deserialize Binary Tree

/*
 * erialization is the process of converting a data structure or object into a sequence of bits so that it
 * can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in
 * the same or another computer environment.
 * Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how
 * your serialization/deserialization algorithm should work. You just need to ensure that a binary tree
 * can be serialized to a string and this string can be deserialized to the original tree structure.
 */

/*
 * Example:
 * You may serialize the following tree:
 *
 *     1
 *    / \
 *   2   3
 *      / \
 *     4   5
 *
 * as "[1,2,3,null,null,4,5]"
 */

/*
 * Clarification: The above format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format,
 * so please be creative and come up with different approaches yourself.
 */

/*
 * Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.
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
#include <string>
#include <sstream>

using namespace std;

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string result;
        _preOrder(root, result);
        result.pop_back();
        return result;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        data += ',';
        int i = 0;
        TreeNode *root = _build(data, i);
        return root;
    }

private:
    TreeNode* _build(const string& data, int& pos)
    {
        TreeNode *root = nullptr;
        int j = pos;
        while(data[j] != ',')
            ++j;
        string item = data.substr(pos, j - pos);
        pos = j + 1;
        if(item == "null") return root;

        int value;
        stringstream ss;
        ss << item;
        ss >> value;
        root = new TreeNode(value);

        TreeNode *left = _build(data, pos);
        TreeNode *right = _build(data, pos);
        root -> left = left;
        root -> right = right;

        return root;
    }

    void _preOrder(TreeNode* root, string& result)
    {
        if(!root)
        {
            result += "null,";
            return;
        }
        result += to_string(root -> val) + ',';
        _preOrder(root -> left, result);
        _preOrder(root -> right, result);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
