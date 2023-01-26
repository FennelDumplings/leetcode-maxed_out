// prob590: N-ary Tree Postorder Traversal

/*
 * Given an n-ary tree, return the postorder traversal of its nodes' values.
 * Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).
 */

/*
 * Follow up:
 * Recursive solution is trivial, could you do it iteratively?
 */

#include <vector>
#include <stack>

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

// 递归
class Solution {
public:
    vector<int> postorder(Node* root) {
        if(!root) return vector<int>();
        vector<int> result;
        _postOrder(root, result);
        return result;
    }

private:
    void _postOrder(Node* root, vector<int>& result)
    {
        for(Node *child: (root -> children))
        {
            if(child)
                _postOrder(child, result);
        }
        result.push_back(root -> val);
    }
};

// 迭代
class Solution_2 {
public:
    vector<int> postorder(Node* root) {
        if(!root) return vector<int>();
        stack<Node*> st;
        stack<Node*> output;
        st.push(root);
        while(!st.empty())
        {
            Node *cur = st.top();
            st.pop();
            output.push(cur);
            for(Node *child: (cur -> children))
            {
                if(child)
                    st.push(child);
            }
        }
        vector<int> result;
        while(!output.empty())
        {
            result.push_back(output.top() -> val);
            output.pop();
        }
        return result;
    }
};
