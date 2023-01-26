// prob429: n-ary-tree-level-order-traversal

/*
 * Given an n-ary tree, return the level order traversal of its nodes' values.
 * Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).
 */

/*
 * Constraints:
 * The height of the n-ary tree is less than or equal to 1000
 * The total number of nodes is between [0, 10^4]
 */

#include <vector>
#include <queue>

using namespace std;

// Definition for a Node.
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
    vector<vector<int>> levelOrder(Node* root) {
        if(!root) return vector<vector<int> >();
        queue<Node*> q;
        q.push(root);
        vector<Node*> level_nodes;
        vector<int> level_values;
        vector<vector<int> > result;
        while(!q.empty())
        {
            level_nodes.clear();
            level_values.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            for(Node *node: level_nodes)
            {
                level_values.push_back(node -> val);
                if(!(node -> children).empty())
                {
                    for(Node *child: node -> children)
                        q.push(child);
                }
            }
            result.push_back(level_values);
        }
        return result;
    }
};
