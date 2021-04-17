// prob449: Serialize and Deserialize BST

/*
 * Serialization is the process of converting a data structure or object into a sequence of bits so that it can be
 * stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed
 * later in the same or another computer environment.
 * Design an algorithm to serialize and deserialize a binary search tree. There is no restriction on how
 * your serialization/deserialization algorithm should work. You just need to ensure that a binary search tree can be
 * serialized to a string and this string can be deserialized to the original tree structure.
 * The encoded string should be as compact as possible.
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

#include <string>
#include <sstream>
#include "include/Node.h"

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


// 4 个 16 进制字符表示一个整数(节点值)
class Codec_2 {
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
        data += char(0x100);
        int i = 0;
        TreeNode *root = _build(data, i);
        return root;
    }

private:
    TreeNode* _build(const string& data, int& pos)
    {
        TreeNode *root = nullptr;
        int j = pos;
        while(data[j] != char(0x100))
            ++j;
        string item = data.substr(pos, j - pos);
        pos = j + 1;
        if(item == string({char(0x101)})) return root;

        root = new TreeNode(hexstr2int(item));

        TreeNode *left = _build(data, pos);
        TreeNode *right = _build(data, pos);
        root -> left = left;
        root -> right = right;

        return root;
    }

    int hexstr2int(const string& hexstr)
    {
        unsigned int x;
        stringstream ss;
        ss << hex << hexstr;
        ss >> x;
        // output it as a signed type
        return static_cast<int>(x);
    }

    //i要转化的十进制整数，width转化后的宽度，位数不足则补0
    std::string int2hexstr(int i, int width)
    {
        stringstream ioss;     //定义字符串流
        string s_temp;         //存放转化后字符
        ioss << hex << i;      //以十六制形式输出
        ioss >> s_temp;

        if(width > (int)s_temp.size())
        {
            std::string s_0(width - s_temp.size(), '0');      //位数不够则补0
            s_temp = s_0 + s_temp;                            //合并
        }

        string s = s_temp.substr(s_temp.length() - width, s_temp.length());    //取右width位
        return s;
    }

    void _preOrder(TreeNode* root, string& result)
    {
        if(!root)
        {
            result += string({char(0x101), char(0x100)});
            return;
        }
        result += int2hexstr(root -> val, 4) + char(0x100);
        _preOrder(root -> left, result);
        _preOrder(root -> right, result);
    }
};

