// prob428: Serialize and Deserialize N-ary Tree

/*
 * Serialization is the process of converting a data structure or object into a sequence of bits so that it
 * can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed
 * later in the same or another computer environment.
 * Design an algorithm to serialize and deserialize an N-ary tree. An N-ary tree is a rooted tree
 * in which each node has no more than N children. There is no restriction on how your serialization/deserialization
 * algorithm should work. You just need to ensure that an N-ary tree can be serialized to a string and this string
 * can be deserialized to the original tree structure.
 */

/*
 * Constraints:
 *
 * The height of the n-ary tree is less than or equal to 1000
 * The total number of nodes is between [0, 10^4]
 * Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.
 */

#include <stack>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(Node* root) {
        if(!root) return "";
        string result = "[";
        _preOrder(root, result);
        result += ']';
        return result;
    }

    // Decodes your encoded data to tree.
    Node* deserialize(string data) {
        if(data.empty()) return nullptr;
        return _build(data);
    }

private:
    Node* _build(const string& data)
    {
        int n = data.size();
        int i = 1;
        stack<Node*> st;
        while(i < n - 1)
        {
            int j = i;
            while(j < n - 1 && data[j] >= '0' && data[j] <= '9')
                ++j;
            int val;
            stringstream ss;
            ss << data.substr(i, j - i);
            ss >> val;
            Node* node = new Node(val);
            if(!st.empty())
                (st.top() -> children).push_back(node);
            else
                st.push(node);
            while(j < n - 1 && data[j] == ']')
            {
                st.pop();
                ++j;
            }
            if(data[j] == '[')
                st.push(node);
            i = j + 1;
        }
        return st.top();
    }

    void _preOrder(Node* root, string& result)
    {
        result += to_string(root -> val);

        int n = (root -> children).size();
        if(n == 0) return;
        // 有子节点
        result += '[';
        for(int i = 0; i < n; ++i)
        {
            Node *child = (root -> children)[i];
            if(child)
            {
                _preOrder(child, result);
                if(i < n - 1)
                    result += ',';
            }
        }
        result += ']';
    }
};
