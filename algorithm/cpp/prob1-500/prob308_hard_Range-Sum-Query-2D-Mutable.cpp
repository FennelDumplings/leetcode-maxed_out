// prob308: Range Sum Query 2D - Mutable

/*
 * https://leetcode-cn.com/problems/range-sum-query-2d-mutable/
 */

/*
 * Note:
 * The matrix is only modifiable by the update function.
 * You may assume the number of calls to update and sumRegion function is distributed evenly.
 * You may assume that row1 ≤ row2 and col1 ≤ col2.
 */

#include <vector>
#include <iostream>

using namespace std;


// --------------------------------------------------------
// 链式四叉树实现二维线段树
// 368ms
// --------------------------------------------------------

// 节点定义
struct QTNode
{
    int top, bottom, left, right;
    int sum;
    QTNode *topleft, *topright, *bottomleft, *bottomright;
    QTNode(int t, int b, int l, int r, int sum,
            QTNode* tl=nullptr, QTNode* tr=nullptr, QTNode* bl=nullptr, QTNode* br=nullptr)
        :top(t),bottom(b),left(l),right(r),sum(sum),topleft(tl),topright(tr),bottomleft(bl),bottomright(br){}
    ~QTNode()
    {
        for(QTNode* son: vector<QTNode*>{topleft, topright, bottomleft, bottomright})
        {
            if(son)
            {
                delete son;
                son = nullptr;
            }
        }
    }
};

class QT_2D_SegmentTree
{
public:
    QT_2D_SegmentTree()
    {
        root = nullptr;
    }

    ~QT_2D_SegmentTree()
    {
        if(root)
        {
            delete root;
            root = nullptr;
        }
    }

    void build(const vector<vector<int>>& matrix)
    {
        if(matrix.empty()) return;
        int n = matrix.size(), m = matrix[0].size();
        root = _build(0, n - 1, 0, m - 1, matrix);
    }

    void point_update(int i, int j, int val)
    {
        _point_update(root, i, j, val);
    }

    int range_query(int row1, int col1, int row2, int col2)
    {
        // cout << "query" << endl;
        return _range_query(root, row1, row2, col1, col2);
    }

    void traverse()
    {
        cout << "================" << endl;
        _traverse(root);
        cout << "================" << endl;
    }

private:
    QTNode *root;

    void _traverse(QTNode* node)
    {
        cout << node -> top << " " << node -> bottom << " " << node -> left << " " << node -> right << endl;
        cout << "sum: " << node -> sum << endl;
        for(auto *son: vector<QTNode*>{node -> topleft, node -> topright, node -> bottomleft, node -> bottomright})
        {
            if(!son) continue;
            _traverse(son);
        }
    }

    int _range_query(QTNode* node, int top, int bottom, int left, int right)
    {
        // cout << "-----------------------------" << endl;
        // cout << "查询区间： " <<  i_top << " " << i_bottom << " " << j_left << " " << j_right << endl;
        // cout << "节点表示区间 : " << node -> top << " " << node -> bottom << " " << node -> left << " " << node -> right << endl;
        // cout << "-----------------------------" << endl;
        int nodeTop = node -> top, nodeBottom = node -> bottom;
        int nodeLeft = node -> left, nodeRight = node -> right;
        if(nodeTop == top && nodeBottom == bottom && nodeLeft == left && nodeRight == right)
        {
            // cout << "top == bottom && left == right" << endl;
            return node -> sum;
        }

        // 通过 bottom, top 与 nodeTopBottomMid 的关系确定上，下半边是否需要查询，left, right 与 nodeLeftRightMid 的关系确定左，右半边是否需要查询。这两个是独立的，因此 if, else 比较多，容易写错。
        int nodeTopBottomMid = (nodeBottom + nodeTop) / 2;
        int nodeLeftRightMid = (nodeLeft + nodeRight) / 2;
        if(bottom <= nodeTopBottomMid)
        {
            if(right <= nodeLeftRightMid)
                return _range_query(node -> topleft, top, bottom, left, right);
            else if(nodeLeftRightMid < left)
                return _range_query(node -> topright, top, bottom, left, right);
            else
            {
                int s1 = _range_query(node -> topleft, top, bottom, left, nodeLeftRightMid);
                int s2 = _range_query(node -> topright, top, bottom, nodeLeftRightMid + 1, right);
                return s1 + s2;
            }
        }
        else if(nodeTopBottomMid < top)
        {
            if(right <= nodeLeftRightMid)
                return _range_query(node -> bottomleft, top, bottom, left, right);
            else if(nodeLeftRightMid < left)
                return _range_query(node -> bottomright, top, bottom, left, right);
            else
            {
                int s1 = _range_query(node -> bottomleft, top, bottom, left, nodeLeftRightMid);
                int s2 = _range_query(node -> bottomright, top, bottom, nodeLeftRightMid + 1, right);
                return s1 + s2;
            }
        }
        else
        {
            if(right <= nodeLeftRightMid)
            {
                int s1 = _range_query(node -> topleft, top, nodeTopBottomMid, left, right);
                int s2 = _range_query(node -> bottomleft, nodeTopBottomMid + 1, bottom, left, right);
                return s1 + s2;
            }
            else if(nodeLeftRightMid < left)
            {

                int s1 = _range_query(node -> topright, top, nodeTopBottomMid, left, right);
                int s2 = _range_query(node -> bottomright, nodeTopBottomMid + 1, bottom, left, right);
                return s1 + s2;
            }
            else
            {
                int s1 = _range_query(node -> topleft, top, nodeTopBottomMid, left, nodeLeftRightMid);
                int s2 = _range_query(node -> bottomleft, nodeTopBottomMid + 1, bottom, left, nodeLeftRightMid);
                int s3 = _range_query(node -> topright, top, nodeTopBottomMid, nodeLeftRightMid + 1, right);
                int s4 = _range_query(node -> bottomright, nodeTopBottomMid + 1, bottom, nodeLeftRightMid + 1, right);
                return s1 + s2 + s3 + s4;
            }
        }
    }

    void _point_update(QTNode* node, int i, int j, int val)
    {
        // 根据 i 与 [top, bottom], j 与 [left, right] 确定(i, j)在哪个子树
        // 更新完叶子，回溯阶段更新当前节点sum
        int nodeTop = node -> top, nodeBottom = node -> bottom;
        int nodeLeft = node -> left, nodeRight = node -> right;
        if(nodeTop == nodeBottom && nodeTop == i && nodeLeft == nodeRight && nodeLeft == j)
        {
            node -> sum = val;
            return;
        }

        int nodeTopBottomMid = (nodeBottom + nodeTop) / 2;
        int nodeLeftRightMid = (nodeLeft + nodeRight) / 2;
        if(i <= nodeTopBottomMid)
        {
            if(j <= nodeLeftRightMid)
                _point_update(node -> topleft, i, j, val);
            else
                _point_update(node -> topright, i, j, val);
        }
        else
        {
            if(j <= nodeLeftRightMid)
                _point_update(node -> bottomleft, i, j, val);
            else
                _point_update(node -> bottomright, i, j, val);
        }
        int sum = 0;
        if(node -> topleft) sum += node -> topleft -> sum;
        if(node -> topright) sum += node -> topright -> sum;
        if(node -> bottomleft) sum += node -> bottomleft -> sum;
        if(node -> bottomright) sum += node -> bottomright -> sum;
        node -> sum = sum;
    }

    // topleft(tl),topright(tr),bottomleft(bl),bottomright(br)
    QTNode* _build(int top, int bottom, int left, int right, const vector<vector<int>>& matrix)
    {
        if(top == bottom && left == right)
            return new QTNode(top, bottom, left, right, matrix[top][left]);

        int nodeTopBottomMid = (top + bottom) / 2;
        int nodeLeftRightMid = (left + right) / 2;
        // top == bottom 和 left == right 恰有一个存在
        if(left == right)
        {
            QTNode *topleft = _build(top, nodeTopBottomMid, left, right, matrix);
            QTNode *bottomleft = _build(nodeTopBottomMid + 1, bottom, left, right, matrix);
            int sum = topleft -> sum + bottomleft -> sum;
            return new QTNode(top, bottom, left, right, sum, topleft, nullptr, bottomleft, nullptr);
        }
        if(top == bottom)
        {
            QTNode *topleft = _build(top, bottom, left, nodeLeftRightMid, matrix);
            QTNode *topright = _build(top, bottom, nodeLeftRightMid + 1, right, matrix);
            int sum = topleft -> sum + topright -> sum;
            return new QTNode(top, bottom, left, right, sum, topleft, topright, nullptr, nullptr);
        }

        // top < bottom 和 left < right 均满足
        QTNode *topleft = _build(top, nodeTopBottomMid, left, nodeLeftRightMid, matrix);
        QTNode *topright = _build(top, nodeTopBottomMid, nodeLeftRightMid + 1, right, matrix);
        QTNode *bottomleft = _build(nodeTopBottomMid + 1, bottom, left, nodeLeftRightMid, matrix);
        QTNode *bottomright = _build(nodeTopBottomMid + 1, bottom, nodeLeftRightMid + 1, right, matrix);
        int sum = topleft -> sum + topright -> sum + bottomleft -> sum + bottomright -> sum;
        return new QTNode(top, bottom, left, right, sum, topleft, topright, bottomleft, bottomright);
    }
};

class NumMatrix_3 {
public:
    NumMatrix_3(vector<vector<int>>& matrix) {
        int n = 0, m = 0;
        if(!matrix.empty())
            n = matrix.size(), m = matrix[0].size();
        sttree_2d = QT_2D_SegmentTree();
        sttree_2d.build(matrix);
        // sttree_2d.traverse();
    }

    void update(int row, int col, int val) {
        sttree_2d.point_update(row, col, val);
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return sttree_2d.range_query(row1, col1, row2, col2);
    }

private:
    QT_2D_SegmentTree sttree_2d;
};



// --------------------------------------------------------
// 数组四叉树实现二维线段树
// --------------------------------------------------------

class Seq_QT_2D_SegmentTree
{
public:
    Seq_QT_2D_SegmentTree()
    {
        st_vec = vector<int>();
        n = -1;
        m = -1;
    }

    void build(const vector<vector<int>>& arr)
    {
        if(arr.empty()) return;
        n = arr.size(), m = arr[0].size();
        // 32 是试出来的
        st_vec.resize(n * m * 32);
        _build(1, 0, n - 1, 0, m - 1, arr);
    }

    void point_update(int i, int j, int v)
    {
        _point_update(1, 0, n - 1, 0, m - 1, i, j, v);
    }

    int range_query(int row1, int col1, int row2, int col2)
    {
        return _range_query(1, 0, n - 1, 0, m - 1, row1, row2, col1, col2);
    }

private:
    vector<int> st_vec;
    int n, m; // 原始数据的行数列数
    int topleft = 0, topright = 1, bottomleft = 2, bottomright = 3;

    int _range_query(int node, int nodeTop, int nodeBottom, int nodeLeft, int nodeRight, int top, int bottom, int left, int right)
    {
        if(nodeTop == top && nodeBottom == bottom && nodeLeft == left && nodeRight == right)
            return st_vec[node];

        int nodeTopBottomMid = (nodeTop + nodeBottom) / 2;
        int nodeLeftRightMid = (nodeLeft + nodeRight) / 2;
        if(bottom <= nodeTopBottomMid)
        {
            if(right <= nodeLeftRightMid)
                return _range_query(son(node, topleft), nodeTop, nodeTopBottomMid, nodeLeft, nodeLeftRightMid, top, bottom, left, right);
            else if(nodeLeftRightMid < left)
                return _range_query(son(node, topright), nodeTop, nodeTopBottomMid, nodeLeftRightMid + 1, nodeRight, top, bottom, left, right);
            else
            {
                int s1 = _range_query(son(node, topleft), nodeTop, nodeTopBottomMid, nodeLeft, nodeLeftRightMid, top, bottom, left, nodeLeftRightMid);
                int s2 = _range_query(son(node, topright), nodeTop, nodeTopBottomMid, nodeLeftRightMid + 1, nodeRight, top, bottom, nodeLeftRightMid + 1, right);
                return s1 + s2;
            }
        }
        else if(nodeTopBottomMid < top)
        {
            if(right <= nodeLeftRightMid)
                return _range_query(son(node, bottomleft), nodeTopBottomMid + 1, nodeBottom, nodeLeft, nodeLeftRightMid, top, bottom, left, right);
            else if(nodeLeftRightMid < left)
                return _range_query(son(node, bottomright), nodeTopBottomMid + 1, nodeBottom, nodeLeftRightMid + 1, nodeRight, top, bottom, left, right);
            else
            {
                int s1 = _range_query(son(node, bottomleft), nodeTopBottomMid + 1, nodeBottom, nodeLeft, nodeLeftRightMid, top, bottom, left, nodeLeftRightMid);
                int s2 = _range_query(son(node, bottomright), nodeTopBottomMid + 1, nodeBottom, nodeLeftRightMid + 1, nodeRight, top, bottom, nodeLeftRightMid + 1, right);
                return s1 + s2;
            }
        }
        else
        {
            if(right <= nodeLeftRightMid)
            {
                int s1 = _range_query(son(node, topleft), nodeTop, nodeTopBottomMid, nodeLeft, nodeLeftRightMid, top, nodeTopBottomMid, left, right);
                int s2 = _range_query(son(node, bottomleft), nodeTopBottomMid + 1, nodeBottom, nodeLeft, nodeLeftRightMid, nodeTopBottomMid + 1, bottom, left, right);
                return s1 + s2;

            }
            else if(nodeLeftRightMid < left)
            {
                int s1 = _range_query(son(node, topright), nodeTop, nodeTopBottomMid, nodeLeftRightMid + 1, nodeRight, top, nodeTopBottomMid, left, right);
                int s2 = _range_query(son(node, bottomright), nodeTopBottomMid + 1, nodeBottom, nodeLeftRightMid + 1, nodeRight, nodeTopBottomMid + 1, bottom, left, right);
                return s1 + s2;
            }
            else
            {
                int s1 = _range_query(son(node, topleft), nodeTop, nodeTopBottomMid, nodeLeft, nodeLeftRightMid, top, nodeTopBottomMid, left, nodeLeftRightMid);
                int s2 = _range_query(son(node, topright), nodeTop, nodeTopBottomMid, nodeLeftRightMid + 1, nodeRight, top, nodeTopBottomMid, nodeLeftRightMid + 1, right);
                int s3 = _range_query(son(node, bottomleft), nodeTopBottomMid + 1, nodeBottom, nodeLeft, nodeLeftRightMid, nodeTopBottomMid + 1, bottom, left, nodeLeftRightMid);
                int s4 = _range_query(son(node, bottomright), nodeTopBottomMid + 1, nodeBottom, nodeLeftRightMid + 1, nodeRight, nodeTopBottomMid + 1, bottom, nodeLeftRightMid + 1, right);
                return s1 + s2 + s3 + s4;
            }
        }
    }

    void _point_update(int node, int nodeTop, int nodeBottom, int nodeLeft, int nodeRight, int i, int j, int v)
    {
        if(nodeTop > nodeBottom || nodeLeft > nodeRight)
        {
            cout << "nodeTop > nodeBottom || nodeLeft > nodeRight" << endl;
            return;
        }
        if(nodeTop == nodeBottom && nodeTop == i && nodeLeft == nodeRight && nodeLeft == j)
        {
            st_vec[node] = v;
            return;
        }

        int nodeTopBottomMid = (nodeTop + nodeBottom) / 2;
        int nodeLeftRightMid = (nodeLeft + nodeRight) / 2;
        if(i <= nodeTopBottomMid)
        {
            if(j <= nodeLeftRightMid)
                _point_update(son(node, topleft), nodeTop, nodeTopBottomMid, nodeLeft, nodeLeftRightMid, i, j, v);
            else
                _point_update(son(node, topright), nodeTop, nodeTopBottomMid, nodeLeftRightMid + 1, nodeRight, i, j, v);
        }
        else
        {
            if(j <= nodeLeftRightMid)
                _point_update(son(node, bottomleft), nodeTopBottomMid + 1, nodeBottom, nodeLeft, nodeLeftRightMid, i, j, v);
            else
                _point_update(son(node, bottomright), nodeTopBottomMid + 1, nodeBottom, nodeLeftRightMid + 1, nodeRight, i, j, v);
        }
        int sum = st_vec[son(node, topleft)];
        if(nodeTop < nodeBottom) sum += st_vec[son(node, bottomleft)];
        if(nodeLeft < nodeRight) sum += st_vec[son(node, topright)];
        if(nodeTop < nodeBottom && nodeLeft < nodeRight) sum += st_vec[son(node, bottomright)];
        st_vec[node] = sum;
    }

    void _build(int node, int nodeTop, int nodeBottom, int nodeLeft, int nodeRight, const vector<vector<int> >& arr)
    {
        if(nodeLeft == nodeRight && nodeTop == nodeBottom)
        {
            st_vec[node] = arr[nodeTop][nodeLeft];
            return;
        }
        int nodeTopBottomMid = (nodeTop + nodeBottom) / 2;
        int nodeLeftRightMid = (nodeLeft + nodeRight) / 2;
        if(nodeTop == nodeBottom)
        {
            _build(son(node, topleft), nodeTop, nodeBottom, nodeLeft, nodeLeftRightMid, arr);
            _build(son(node, topright), nodeTop, nodeBottom, nodeLeftRightMid + 1, nodeRight, arr);
            st_vec[node] = st_vec[son(node, topleft)] + st_vec[son(node, topright)];
            return;
        }
        if(nodeLeft == nodeRight)
        {
            _build(son(node, topleft), nodeTop, nodeTopBottomMid, nodeLeft, nodeRight, arr);
            _build(son(node, bottomleft), nodeTopBottomMid + 1, nodeBottom, nodeLeft, nodeRight, arr);
            st_vec[node] = st_vec[son(node, topleft)] + st_vec[son(node, bottomleft)];
            return;
        }
        _build(son(node, topleft), nodeTop, nodeTopBottomMid, nodeLeft, nodeLeftRightMid, arr);
        _build(son(node, topright), nodeTop, nodeTopBottomMid, nodeLeftRightMid + 1, nodeRight, arr);
        _build(son(node, bottomleft), nodeTopBottomMid + 1, nodeBottom, nodeLeft, nodeLeftRightMid, arr);
        _build(son(node, bottomright), nodeTopBottomMid + 1, nodeBottom, nodeLeftRightMid + 1, nodeRight, arr);
        st_vec[node] = st_vec[son(node, topleft)] + st_vec[son(node, topright)] + st_vec[son(node, bottomleft)] + st_vec[son(node, bottomright)];
    }

    int son(int node, int son_id)
    {
        // node : 1
        // 0(topleft) -> 2
        // 1(topright) -> 3
        // 2(bottomleft) -> 4
        // 3(bottomright) -> 5
        return node * 4 - 2 + son_id;
    }
};

class NumMatrix_2 {
public:
    NumMatrix_2(vector<vector<int>>& matrix) {
        seqsttree_2d = Seq_QT_2D_SegmentTree();
        seqsttree_2d.build(matrix);
    }

    void update(int row, int col, int val) {
        seqsttree_2d.point_update(row, col, val);
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return seqsttree_2d.range_query(row1, col1, row2, col2);
    }

private:
    Seq_QT_2D_SegmentTree seqsttree_2d;
};

// --------------------------------------------------------
// 数组树套树实现二维线段树
// --------------------------------------------------------

class Seq_TT_2D_SegmentTree
{
public:
    Seq_TT_2D_SegmentTree()
    {
        st_vec = vector<vector<int>>();
        n = -1;
        m = -1;
    }

    void build(const vector<vector<int>>& arr)
    {
        if(arr.empty()) return;
        n = arr.size(), m = arr[0].size();
        // 32 是试出来的
        st_vec.assign(n * 4, vector<int>(m * 4));
        _build(1, 0, n - 1, 0, m - 1, arr);
    }

    void point_update(int i, int j, int v)
    {
        _point_update(1, 0, n - 1, 0, m - 1, i, j, v);
    }

    int range_query(int row1, int col1, int row2, int col2)
    {
        return _range_query(1, 0, n - 1, 0, m - 1, row1, row2, col1, col2);
    }

private:
    vector<vector<int> > st_vec;
    int n, m; // 原始数据的行数列数

    int _range_subquery(int node, int nodeLeft, int nodeRight, int left, int right, int f_node)
    {
        if(left == nodeLeft && nodeRight == right)
            return st_vec[f_node][node];
        int nodeLeftRightMid = (nodeLeft + nodeRight) / 2;
        if(right <= nodeLeftRightMid)
            return _range_subquery(node * 2, nodeLeft, nodeLeftRightMid, left, right, f_node);
        else if(nodeLeftRightMid < left)
            return _range_subquery(node * 2 + 1, nodeLeftRightMid + 1, nodeRight, left, right, f_node);
        else
        {
            int s1 = _range_subquery(node * 2, nodeLeft, nodeLeftRightMid, left, nodeLeftRightMid, f_node);
            int s2 = _range_subquery(node * 2 + 1, nodeLeftRightMid + 1, nodeRight, nodeLeftRightMid + 1, right, f_node);
            return s1 + s2;
        }
    }

    int _range_query(int node, int nodeTop, int nodeBottom, int nodeLeft, int nodeRight, int top, int bottom, int left, int right)
    {
        if(top <= nodeTop && nodeBottom <= bottom)
            return _range_subquery(1, nodeLeft, nodeRight, left, right, node);
        int nodeTopBottomMid = (nodeTop + nodeBottom) / 2;
        if(bottom <= nodeTopBottomMid)
            return _range_query(node * 2, nodeTop, nodeTopBottomMid, nodeLeft, nodeRight, top, bottom, left, right);
        else if(nodeTopBottomMid < top)
            return _range_query(node * 2 + 1, nodeTopBottomMid + 1, nodeBottom, nodeLeft, nodeRight, top, bottom, left, right);
        else
        {
            int s1 = _range_query(node * 2, nodeTop, nodeTopBottomMid, nodeLeft, nodeRight, top, nodeTopBottomMid, left, right);
            int s2 = _range_query(node * 2 + 1, nodeTopBottomMid + 1, nodeBottom, nodeLeft, nodeRight, nodeTopBottomMid + 1, bottom, left, right);
            return s1 + s2;
        }
    }

    void _point_subupdate(int node, int nodeLeft, int nodeRight, int j, int v, int f_node, int f)
    {
        // f_node 表示外层节点索引
        // f 表示外层节点的 nodeTop 和 nodeBottom 关系
        // f = 0: nodeTop < nodeBottom
        // f = 1: nodeTop == nodeBottom
        if(nodeLeft == nodeRight)
        {
            if(f) st_vec[f_node][node] = v;
            else st_vec[f_node][node] = st_vec[f_node * 2][node] + st_vec[f_node * 2 + 1][node];
        }
        else
        {
            int nodeLeftRightMid = (nodeLeft + nodeRight) / 2;
            if(j <= nodeLeftRightMid)
                _point_subupdate(node * 2, nodeLeft, nodeLeftRightMid, j, v, f_node, f);
            else
                _point_subupdate(node * 2 + 1, nodeLeftRightMid + 1, nodeRight, j, v, f_node, f);
            st_vec[f_node][node] = st_vec[f_node][node * 2] + st_vec[f_node][node * 2 + 1];
        }
    }

    void _point_update(int node, int nodeTop, int nodeBottom, int nodeLeft, int nodeRight, int i, int j, int v)
    {
        if(nodeTop == nodeBottom)
        {
            _point_subupdate(1, nodeLeft, nodeRight, j, v, node, 1);
            return;
        }
        int nodeTopBottomMid = (nodeTop + nodeBottom) / 2;
        if(i <= nodeTopBottomMid)
            _point_update(node * 2, nodeTop, nodeTopBottomMid, nodeLeft, nodeRight, i, j, v);
        else
            _point_update(node * 2 + 1, nodeTopBottomMid + 1, nodeBottom, nodeLeft, nodeRight, i, j, v);
        _point_subupdate(1, nodeLeft, nodeRight, j, v, node, 0);
    }

    void _subbuild(int node, int nodeTop, int nodeBottom, int nodeLeft, int nodeRight, const vector<vector<int>>& arr, int f_node)
    {
        if(nodeLeft == nodeRight)
        {
            if(nodeTop == nodeBottom) st_vec[f_node][node] = arr[nodeTop][nodeLeft];
            else st_vec[f_node][node] = st_vec[f_node * 2][node] + st_vec[f_node * 2 + 1][node];
            return;
        }
        int nodeLeftRightMid = (nodeLeft + nodeRight) / 2;
        _subbuild(node * 2, nodeTop, nodeBottom, nodeLeft, nodeLeftRightMid, arr, f_node);
        _subbuild(node * 2 + 1, nodeTop, nodeBottom, nodeLeftRightMid + 1, nodeRight, arr, f_node);
        st_vec[f_node][node] = st_vec[f_node][node * 2] + st_vec[f_node][node * 2 + 1];
    }

    void _build(int node, int nodeTop, int nodeBottom, int nodeLeft, int nodeRight, const vector<vector<int> >& arr)
    {
        if(nodeTop == nodeBottom)
        {
            _subbuild(1, nodeTop, nodeBottom, nodeLeft, nodeRight, arr, node);
            return;
        }
        int nodeTopBottomMid = (nodeTop + nodeBottom) / 2;
        _build(node * 2, nodeTop, nodeTopBottomMid, nodeLeft, nodeRight, arr);
        _build(node * 2 + 1, nodeTopBottomMid + 1, nodeBottom, nodeLeft, nodeRight, arr);
        _subbuild(1, nodeTop, nodeBottom, nodeLeft, nodeRight, arr, node);
    }
};

class NumMatrix_4 {
public:
    NumMatrix_4(vector<vector<int>>& matrix) {
        seqsttree_2d = Seq_TT_2D_SegmentTree();
        seqsttree_2d.build(matrix);
    }

    void update(int row, int col, int val) {
        seqsttree_2d.point_update(row, col, val);
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return seqsttree_2d.range_query(row1, col1, row2, col2);
    }

private:
    Seq_TT_2D_SegmentTree seqsttree_2d;
};

// --------------------------------------------------------
// 二维树状数组
// --------------------------------------------------------

class BIT2d {
public:
    BIT2d(){}
    BIT2d(int n, int m):sums(n + 1, vector<int>(m + 1)){}

    void update(int i, int j, int delta)
    {
        int n = sums.size(), m = sums[0].size();
        for(int x = i; x < n; x += _lowbit(x))
            for(int y = j; y < m; y += _lowbit(y))
                sums[x][y] += delta;
    }

    int query(int i, int j)
    {
        int sum = 0;
        for(int x = i; x > 0; x -= _lowbit(x))
            for(int y = j; y > 0; y -= _lowbit(y))
                sum += sums[x][y];
        return sum;
    }

private:
    vector<vector<int> > sums;

    int _lowbit(int x)
    {
        return x & (-x);
    }
};


class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix):vec(matrix) {
        if(matrix.empty())
        {
            bit2d = BIT2d();
            return;
        }
        int n = matrix.size(), m = matrix[0].size();
        bit2d = BIT2d(n, m);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                bit2d.update(i + 1, j + 1, vec[i][j]);
    }

    void update(int row, int col, int val) {
        bit2d.update(row + 1, col + 1, val - vec[row][col]);
        vec[row][col] = val;
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return bit2d.query(row2 + 1, col2 + 1) - bit2d.query(row2 + 1, col1) - bit2d.query(row1, col2 + 1) + bit2d.query(row1, col1);
    }

private:
    vector<vector<int>> vec;
    BIT2d bit2d;
};
