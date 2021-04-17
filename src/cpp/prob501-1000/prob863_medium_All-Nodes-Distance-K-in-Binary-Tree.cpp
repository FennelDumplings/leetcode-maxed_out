// prob863: All Nodes Distance K in Binary Tree

/*
 * We are given a binary tree (with root node root), a target node, and an integer value K.
 * Return a list of the values of all nodes that have a distance K from the target node.  The answer can be returned in any order.
 */

/*
 * Example 1:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2
 * Output: [7,4,1]
 * Explanation:
 * The nodes that are a distance 2 from the target node (with value 5)
 * have values 7, 4, and 1.
 * Note that the inputs "root" and "target" are actually TreeNodes.
 * The descriptions of the inputs above are just serializations of these objects.
 */

/*
 * Note:
 * The given tree is non-empty.
 * Each node in the tree has unique values 0 <= node.val <= 500.
 * The target node is a node in the tree.
 * 0 <= K <= 1000.
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        // 先建邻接表再bfs
        vector<vector<int> > g(1, vector<int>());
        int node_id = 0;
        int start = -1;
        vector<int> nodes_weight;
        _preOrder(root, target, g, node_id, start, nodes_weight);

        int n = g.size();
        vector<bool> visited(n, false);
        visited[start] = true;
        queue<int> q;
        q.push(start);
        vector<int> level_nodes;
        int level = 0;
        vector<int> result;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            if(level == K)
            {
                for(int node: level_nodes)
                    result.push_back(nodes_weight[node]);
                break;
            }
            for(int node: level_nodes)
            {
                for(int son: g[node])
                {
                    if(visited[son]) continue;
                    q.push(son);
                    visited[son] = true;
                }
            }
            ++level;
        }
        return result;
    }

private:
    void _preOrder(TreeNode* root, TreeNode* target, vector<vector<int> >& g, int& node_id, int& start, vector<int>& nodes_weight)
    {
        if(root == target)
            start = node_id;
        nodes_weight.push_back(root -> val);
        int cur_id = node_id;
        if(root -> left)
        {
            g.push_back(vector<int>());
            ++node_id;
            g[cur_id].push_back(node_id);
            g[node_id].push_back(cur_id);
            _preOrder(root -> left, target, g, node_id, start, nodes_weight);
        }
        if(root -> right)
        {
            g.push_back(vector<int>());
            ++node_id;
            g[cur_id].push_back(node_id);
            g[node_id].push_back(cur_id);
            _preOrder(root -> right, target, g, node_id, start, nodes_weight);
        }
    }
};
