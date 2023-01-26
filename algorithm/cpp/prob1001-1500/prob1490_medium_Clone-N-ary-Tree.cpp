// prob1490: Clone N-ary Tree

/*
 * https://leetcode-cn.com/problems/clone-n-ary-tree/
 */

#include <vector>

using namespace std;

/*
// Definition for a Node.
*/
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

class Solution {
public:
    Node* cloneTree(Node* root) {
        if(!root) return nullptr;
        return build(root);
    }

private:
    Node* build(Node* node)
    {
        Node *ans = new Node(node -> val);
        int m = (node -> children).size();
        (ans -> children).assign(m, nullptr);
        for(int i = 0; i < m; ++i)
        {
            Node *child = (node -> children)[i];
            if(child)
                ans -> children[i] = build(child);
        }
        return ans;
    }
};
