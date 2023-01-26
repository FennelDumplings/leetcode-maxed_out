// prob1506: Find Root of N-Ary Tree

/*
 * https://leetcode-cn.com/problems/find-root-of-n-ary-tree/
 */

/*
// Definition for a Node.
*/

#include <vector>
#include <unordered_map>

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
    Node* findRoot(vector<Node*> tree) {
        unordered_map<Node*, int> indegrees;
        for(Node *node: tree)
        {
            if(indegrees.count(node) == 0)
                indegrees[node] = 0;
            for(Node *child: node -> children)
            {
                if(child)
                    ++indegrees[child];
            }
        }
        for(auto info: indegrees)
        {
            if(info.second == 0)
                return info.first;
        }
        return nullptr;
    }
};
