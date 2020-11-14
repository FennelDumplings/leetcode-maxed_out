// prob1522: Diameter of N-Ary Tree

/*
 * https://leetcode-cn.com/problems/diameter-of-n-ary-tree/
 */

/*
// Definition for a Node.
*/

#include <vector>

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
    int diameter(Node* root) {
        int ans = 0;
        _postOrder(root, ans);
        return ans;
    }

private:
    int _postOrder(Node *node, int& ans)
    {
        int h1 = -1, h2 = -1;
        for(Node *child: node -> children)
        {
            int h = _postOrder(child, ans);
            if(h1 == -1 || h > h1)
            {
                h2 = h1;
                h1 = h;
            }
            else if(h2 == -1 || h > h2)
            {
                h2 = h;
            }
        }
        if(h1 == -1)
            return 0;
        else if(h2 == -1)
        {
            ans = max(ans, h1 + 1);
            return h1 + 1;
        }
        else
        {
            ans = max(ans, h1 + h2 + 2);
            return h1 + 1;
        }
    }
};
