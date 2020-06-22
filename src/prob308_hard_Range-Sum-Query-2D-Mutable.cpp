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

using namespace std;


// --------------------------------------------------------
// 链式四叉树
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

    void build(int top, int bottom, int left, int right, const vector<vector<int>>& matrix)
    {
        // cout << "build" << endl;
        if(top <= bottom && left <= right)
            root = _build(top, bottom, left, right, matrix);
    }

    void point_update(int i, int j, int val)
    {
        // cout << "update" << endl;
        _point_update(root, i, j, val);
        // traverse();
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

    void _traverse(QTNode* root)
    {
        cout << root -> top << " " << root -> bottom << " " << root -> left << " " << root -> right << endl;
        cout << "sum: " << root -> sum << endl;
        for(auto *son: vector<QTNode*>{root -> topleft, root -> topright, root -> bottomleft, root -> bottomright})
        {
            if(!son) continue;
            _traverse(son);
        }
    }

    int _range_query(QTNode* root, int i_top, int i_bottom, int j_left, int j_right)
    {
        // cout << "-----------------------------" << endl;
        // cout << "查询区间： " <<  i_top << " " << i_bottom << " " << j_left << " " << j_right << endl;
        // cout << "节点表示区间 : " << root -> top << " " << root -> bottom << " " << root -> left << " " << root -> right << endl;
        // cout << "-----------------------------" << endl;
        if(root -> top == root -> bottom && root -> left == root -> right
                && root -> top == i_top && root -> left == j_left)
        {
            // cout << "top == bottom && left == right" << endl;
            return root -> sum;
        }

        if(root -> left == root -> right)
        {
            // left == right，看 i_top, i_bottom 与 [top, bottom] 关系
            // cout << "left == right : " ;
            int mid_tb = (root -> top + root -> bottom) / 2;
            if(i_bottom <= mid_tb)
            {
                // cout << "topleft" << endl;
                return _range_query(root -> topleft, i_top, i_bottom, j_left, j_right);
            }
            else if(mid_tb < i_top)
            {
                // cout << "bottomleft" << endl;
                return _range_query(root -> bottomleft, i_top, i_bottom, j_left, j_right);
            }
            else
            {
                // cout << "topleft + bottomleft" << endl;
                int s1 =  _range_query(root -> topleft, i_top, mid_tb, j_left, j_right);
                int s2 = _range_query(root -> bottomleft, mid_tb + 1, i_bottom, j_left, j_right);
                return s1 + s2;
            }
        }
        if(root -> top == root -> bottom)
        {
            // top == bottom，看 j_left, j_right 与 [left, right] 关系
            // cout << "top == bottom : " ;
            int mid_lr = (root -> left + root -> right) / 2;
            // cout << j_left << " " << mid_lr << " " << j_right << endl;
            if(j_right <= mid_lr)
            {
                // cout << "topleft" << endl;
                return _range_query(root -> topleft, i_top, i_bottom, j_left, j_right);
            }
            else if(mid_lr < j_left)
            {
                // cout << "topright" << endl;
                return _range_query(root -> topright, i_top, i_bottom, j_left, j_right);
            }
            else
            {
                // cout << "topleft + topright" << endl;
                int s1 = _range_query(root -> topleft, i_top, i_bottom, j_left, mid_lr);
                int s2 = _range_query(root -> topright, i_top, i_bottom, mid_lr + 1, j_right);
                return s1 + s2;
            }
        }

        int mid_tb = (root -> top + root -> bottom) / 2;
        int mid_lr = (root -> left + root -> right) / 2;
        // 看 i_top, i_bottom 与 [top, bottom] 关系 和 看 j_left, j_right 与 [left, right] 关系
        // 两个维度分别各有 3 中情况，加起来有 9 中情况
        // cout << "left < right && top < bottom" << endl;
        if(i_bottom <= mid_tb)
        {
            // 只在 top
            if(j_right <= mid_lr)
            {
                // cout << "topleft" << endl;
                return _range_query(root -> topleft, i_top, i_bottom, j_left, j_right);
            }
            else if(mid_lr < j_left)
            {
                // cout << "topright" << endl;
                return _range_query(root -> topright, i_top, i_bottom, j_left, j_right);
            }
            else
            {
                // cout << "topleft + topright" << endl;
                int s1 = _range_query(root -> topleft, i_top, i_bottom, j_left, mid_lr);
                int s2 = _range_query(root -> topright, i_top, i_bottom, mid_lr + 1, j_right);
                return s1 + s2;
            }
        }
        else if(mid_tb < i_top)
        {
            // 只在 bottom
            if(j_right <= mid_lr)
            {
                // cout << "bottomleft" << endl;
                return _range_query(root -> bottomleft, i_top, i_bottom, j_left, j_right);
            }
            else if(mid_lr < j_left)
            {
                // cout << "bottomright" << endl;
                return _range_query(root -> bottomright, i_top, i_bottom, j_left, j_right);
            }
            else
            {
                // cout << "bottomleft + bottomright" << endl;
                int s1 = _range_query(root -> bottomleft, i_top, i_bottom, j_left, mid_lr);
                int s2 = _range_query(root -> bottomright, i_top, i_bottom, mid_lr + 1, j_right);
                return s1 + s2;
            }
        }
        else
        {
            // top 和 bottom 都有
            if(j_right <= mid_lr)
            {
                // cout << "topleft + bottomleft" << endl;
                int s1 = _range_query(root -> topleft, i_top, mid_tb, j_left, j_right);
                int s2 = _range_query(root -> bottomleft, mid_tb + 1, i_bottom, j_left, j_right);
                return s1 + s2;
            }
            else if(mid_lr < j_left)
            {
                // cout << "topright + bottomright" << endl;
                int s1 = _range_query(root -> topright, i_top, mid_tb, j_left, j_right);
                int s2 = _range_query(root -> bottomright, mid_tb + 1, i_bottom, j_left, j_right);
                return s1 + s2;
            }
            else
            {
                // cout << "topleft + topright + bottomleft + bottomright" << endl;
                int s1 = _range_query(root -> topleft, i_top, mid_tb, j_left, mid_lr);
                int s2 = _range_query(root -> topright, i_top, mid_tb, mid_lr + 1, j_right);
                int s3 = _range_query(root -> bottomleft, mid_tb + 1, i_bottom, j_left, mid_lr);
                int s4 = _range_query(root -> bottomright, mid_tb + 1, i_bottom, mid_lr + 1, j_right);
                return s1 + s2 + s3 + s4;
            }
        }
    }

    void _point_update(QTNode* root, int i, int j, int val)
    {
        // 根据 i 与 [top, bottom], j 与 [left, right] 确定(i, j)在哪个子树
        // 更新完叶子，回溯阶段更新当前节点sum
        if(root -> top == root -> bottom && root -> left == root -> right
                && root -> top == i && root -> left == j)
        {
            root -> sum = val;
            return;
        }

        if(root -> left == root -> right)
        {
            // left == right，看 i 与 [top, bottom] 关系
            int mid_tb = (root -> top + root -> bottom) / 2;
            if(i <= mid_tb)
                _point_update(root -> topleft, i, j, val);
            else
                _point_update(root -> bottomleft, i, j, val);
            root -> sum = root -> topleft -> sum + root -> bottomleft -> sum;
            return;
        }
        if(root -> top == root -> bottom)
        {
            // top == bottom，看 j 与 [left, right] 关系
            int mid_lr = (root -> left + root -> right) / 2;
            if(j <= mid_lr)
                _point_update(root -> topleft, i, j, val);
            else
                _point_update(root -> topright, i, j, val);
            root -> sum = root -> topleft -> sum + root -> topright -> sum;
            return;
        }

        int mid_tb = (root -> top + root -> bottom) / 2;
        int mid_lr = (root -> left + root -> right) / 2;
        if(i <= mid_tb && j <= mid_lr)
            _point_update(root -> topleft, i, j, val);
        else if(i <= mid_tb)
            _point_update(root -> topright, i, j, val);
        else if(j <= mid_lr)
            _point_update(root -> bottomleft, i, j, val);
        else
            _point_update(root -> bottomright, i, j, val);
        root -> sum = root -> topleft -> sum + root -> topright -> sum
            + root -> bottomleft -> sum + root -> bottomright -> sum;
    }

    // topleft(tl),topright(tr),bottomleft(bl),bottomright(br)
    QTNode* _build(int top, int bottom, int left, int right, const vector<vector<int>>& matrix)
    {
        if(top == bottom && left == right)
            return new QTNode(top, bottom, left, right, matrix[top][left]);

        // top == bottom 和 left == right 恰有一个存在
        if(left == right)
        {
            int mid_tb = (top + bottom) / 2;
            QTNode *topleft = _build(top, mid_tb, left, right, matrix);
            QTNode *bottomleft = _build(mid_tb + 1, bottom, left, right, matrix);
            int sum = topleft -> sum + bottomleft -> sum;
            return new QTNode(top, bottom, left, right, sum, topleft, nullptr, bottomleft, nullptr);
        }
        if(top == bottom)
        {
            int mid_lr = (left + right) / 2;
            QTNode *topleft = _build(top, bottom, left, mid_lr, matrix);
            QTNode *topright = _build(top, bottom, mid_lr + 1, right, matrix);
            int sum = topleft -> sum + topright -> sum;
            return new QTNode(top, bottom, left, right, sum, topleft, topright, nullptr, nullptr);
        }

        // top < bottom 和 left < right 均满足
        int mid_tb = (top + bottom) / 2;
        int mid_lr = (left + right) / 2;
        QTNode *topleft = _build(top, mid_tb, left, mid_lr, matrix);
        QTNode *topright = _build(top, mid_tb, mid_lr + 1, right, matrix);
        QTNode *bottomleft = _build(mid_tb + 1, bottom, left, mid_lr, matrix);
        QTNode *bottomright = _build(mid_tb + 1, bottom, mid_lr + 1, right, matrix);
        int sum = topleft -> sum + topright -> sum + bottomleft -> sum + bottomright -> sum;
        return new QTNode(top, bottom, left, right, sum, topleft, topright, bottomleft, bottomright);
    }
};

class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int n = 0, m = 0;
        if(!matrix.empty())
            n = matrix.size(), m = matrix[0].size();
        sttree_2d = QT_2D_SegmentTree();
        sttree_2d.build(0, n - 1, 0, m - 1, matrix);
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
