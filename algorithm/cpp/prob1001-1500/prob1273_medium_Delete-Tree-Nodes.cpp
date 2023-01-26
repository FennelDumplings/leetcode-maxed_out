// prob1273: Delete Tree Nodes

/*
 * A tree rooted at node 0 is given as follows:
 * The number of nodes is nodes;
 * The value of the i-th node is value[i];
 * The parent of the i-th node is parent[i].
 * Remove every subtree whose sum of values of nodes is zero.
 * After doing so, return the number of nodes remaining in the tree.
 */

/*
 * Example 1:
 * Input: nodes = 7, parent = [-1,0,0,1,2,2,2], value = [1,-2,4,0,-2,-1,-1]
 * Output: 2
 */

/*
 * Constraints:
 * 1 <= nodes <= 10^4
 * -10^5 <= value[i] <= 10^5
 *  parent.length == nodes
 *  parent[0] == -1 which indicates that 0 is the root.
 */

#include <vector>

using namespace std;

class Solution {
public:
    int deleteTreeNodes(int nodes, vector<int>& parent, vector<int>& value) {
        vector<vector<int> > g(nodes);
        for(int i = 1; i < nodes; ++i)
            g[parent[i]].push_back(i);
        vector<bool> delete_root(nodes, false);
        postOrder(g, 0, value, delete_root);
        return preOrder(g, 0, delete_root);
    }

private:
    int postOrder(const vector<vector<int> >& g, int root, const vector<int>& value, vector<bool>& delete_root)
    {
        int sum = value[root];
        for(int son: g[root])
            sum += postOrder(g, son, value, delete_root);
        if(sum == 0)
            delete_root[root] = true;
        return sum;
    }

    int preOrder(const vector<vector<int> >& g, int root, vector<bool>& delete_root)
    {
        if(delete_root[root])
            return 0;
        int cnt = 1;
        for(int son: g[root])
            cnt += preOrder(g, son, delete_root);
        return cnt;
    }
};
