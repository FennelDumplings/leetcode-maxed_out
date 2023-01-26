// prob987: Vertical Order Traversal of a Binary Tree

/*
 * Given a binary tree, return the vertical order traversal of its nodes values.
 * For each node at position (X, Y), its left and right children respectively will be at positions (X-1, Y-1) and (X+1, Y-1).
 * Running a vertical line from X = -infinity to X = +infinity, whenever the vertical line touches some nodes, we
 * report the values of the nodes in order from top to bottom (decreasing Y coordinates).
 * If two nodes have the same position, then the value of the node that is reported first is the value that is smaller.
 * Return an list of non-empty reports in order of X coordinate.  Every report will have a list of values of nodes.
 */

/*
 * Example 1:
 * Input: [3,9,20,null,null,15,7]
 * Output: [[9],[3,15],[20],[7]]
 * Explanation:
 * Without loss of generality, we can assume the root node is at position (0, 0):
 * Then, the node with value 9 occurs at position (-1, -1);
 * The nodes with values 3 and 15 occur at positions (0, 0) and (0, -2);
 * The node with value 20 occurs at position (1, -1);
 * The node with value 7 occurs at position (2, -2).
 * Example 2:
 * Input: [1,2,3,4,5,6,7]
 * Output: [[4],[2],[1,5,6],[3],[7]]
 * Explanation:
 * The node with value 5 and the node with value 6 have the same position according to the given scheme.
 * However, in the report "[1,5,6]", the node value of 5 comes first since 5 is smaller than 6.
 */

/*
 * Note:
 * The tree will have between 1 and 1000 nodes.
 * Each node's value will be between 0 and 1000.
 */

#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include "include/Node.h"

using namespace std;

// bfs + deque
class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        if(!root) return vector<vector<int> >();
        deque<vector<int> > result_deque(1, vector<int>());
        queue<PDT> q;
        q.push(PDT(result_deque.begin(), root));
        vector<PDT> level_nodes;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            int n = level_nodes.size();
            sort(level_nodes.begin(), level_nodes.end(), Cmp());
            for(int i = 0; i < n; ++i)
            {
                auto item = level_nodes[i];
                DQI iter = item.first;
                TreeNode *node = item.second;
                iter -> push_back(node -> val);
                if(node -> left)
                {
                    if(iter == result_deque.begin())
                        result_deque.push_front(vector<int>());
                    --iter;
                    q.push(PDT(iter, node -> left));
                    ++iter;
                }
                if(node -> right)
                {
                    ++iter;
                    if(iter == result_deque.end())
                        result_deque.push_back(vector<int>());
                    q.push(PDT(iter, node -> right));
                    --iter;
                }
            }
        }
        vector<vector<int> > result;
        for(vector<int> item: result_deque)
            result.push_back(item);
        return result;
    }

private:
    using DQI = deque<vector<int> >::iterator;
    using PDT = pair<DQI, TreeNode*>;

    struct Cmp
    {
        bool operator()(const PDT& pdt1, const PDT& pdt2)
        {
            if(pdt1.first == pdt2.first)
                return (pdt1.second -> val < pdt2.second -> val);
            return pdt1.first < pdt2.first;
        }
    };
};
