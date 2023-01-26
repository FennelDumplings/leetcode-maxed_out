// prob559: Maximum Depth of N-ary Tree

/*
 * Given a n-ary tree, find its maximum depth.
 * The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
 * Nary-Tree input serialization is represented in their level order traversal,
 * each group of children is separated by the null value (See examples).
 */

/*
 * Constraints:
 * The depth of the n-ary tree is less than or equal to 1000.
 * The total number of nodes is between [0, 10^4].
 */

#include <vector>
#include <queue>

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

class Solution {
public:
    int maxDepth(Node* root) {
        if(!root) return 0;
        queue<Node*> q;
        q.push(root);
        int level = 1;
        vector<Node*> level_nodes;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            for(auto node: level_nodes)
                for(auto child: node -> children)
                    if(child) q.push(child);
            ++level;
        }
        return level - 1;
    }
};
