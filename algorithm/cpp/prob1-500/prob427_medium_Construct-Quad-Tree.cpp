// prob427: Construct Quad Tree

/*
 * https://leetcode-cn.com/problems/construct-quad-tree/
 */

#include <vector>

using namespace std;

// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }

    ~Node()
    {
        for(Node *son: vector<Node*>{topLeft, topRight, bottomLeft, bottomRight})
        {
            if(son)
            {
                delete son;
                son = nullptr;
            }
        }
    }
};

class Solution {
public:
    // 线段树对区间的处理
    // [start, mid], [mid + 1, end]
    // mid = (end + start) / 2;
    // start == end 为叶节点
    Node* construct(vector<vector<int>>& grid) {
        if(grid.empty()) return nullptr;
        int n = grid.size(), m = grid[0].size();
        // i: 0..n-1
        // j: 0..m-1
        return build(grid, 0, n - 1, 0, m - 1);
    }

private:
    using PBB = pair<bool, bool>; // 当前点是否 isLeaf, 若为 isLeaf, 值为多少

    Node* build(const vector<vector<int>>& grid, int i_start, int i_end, int j_start, int j_end)
    {
        Node *root =  _build(grid, i_start, i_end, j_start, j_end);
        _postOrder(root);
        return root;
    }

    Node* _build(const vector<vector<int>>& grid, int i_start, int i_end, int j_start, int j_end)
    {
        if(i_start == i_end && j_start == j_end)
            return new Node(grid[i_start][j_start], true);
        Node *root = new Node();
        bool i_partition = false, j_partition = false; // 标记 i, j 方向是否要划分下去
        int i_mid = -1, j_mid = -1;
        if(i_start != i_end)
        {
            i_partition = true;
            i_mid = (i_start + i_end) / 2;
        }
        if(j_start != j_end)
        {
            j_partition = true;
            j_mid = (j_start + j_end) / 2;
        }
        if(i_partition && j_partition)
        {
            root -> topLeft = _build(grid, i_start, i_mid, j_start, j_mid);
            root -> topRight = _build(grid, i_start, i_mid, j_mid + 1, j_end);
            root -> bottomLeft = _build(grid, i_mid + 1, i_end, j_start, j_mid);
            root -> bottomRight = _build(grid, i_mid + 1, i_end, j_mid + 1, j_end);
        }
        else if(i_partition)
        {
            root -> topLeft = _build(grid, i_start, i_mid, j_start, j_start);
            root -> bottomLeft = _build(grid, i_mid + 1, i_end, j_start, j_start);
        }
        else
        {
            root -> topLeft = _build(grid, i_start, i_start, j_start, j_mid);
            root -> topRight = _build(grid, i_start, i_start, j_mid + 1, j_end);
        }
        return root;
    }

    void _postOrder(Node* root)
    {
        if(root -> isLeaf)
            return;

        // 至少有 topLeft

        bool val = false;
        bool get_topleft_val = false;
        bool is_leaf = true;
        for(Node *son: vector<Node*>{root -> topLeft, root -> topRight, root -> bottomLeft, root -> bottomRight})
        {
            if(!son) continue;
            _postOrder(son);
            if(!get_topleft_val)
            {
                val = son -> val;
                get_topleft_val = true;
            }
            if(!son -> isLeaf || son -> val != val)
                is_leaf = false;
        }
        if(is_leaf)
        {
            root -> isLeaf = true;
            root -> val = val;
            root -> topLeft = nullptr;
            root -> topRight = nullptr;
            root -> bottomLeft = nullptr;
            root -> bottomRight = nullptr;
        }
    }
};
