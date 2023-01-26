// prob547: Friend Circles

/*
 * There are N students in a class. Some of them are friends, while some are not.
 * Their friendship is transitive in nature. For example, if A is a direct friend of B,
 * and B is a direct friend of C, then A is an indirect friend of C.
 * And we defined a friend circle is a group of students who are direct or indirect friends.
 *
 * Given a N*N matrix M representing the friend relationship between students in the class. If M[i][j] = 1,
 * then the ith and jth students are direct friends with each other, otherwise not.
 * And you have to output the total number of friend circles among all the students.
 */

/*
 * Example 1:
 * Input:
 * [[1,1,0],
 *  [1,1,0],
 *  [0,0,1]]
 * Output: 2
 * Example 2:
 * Input:
 * [[1,1,0],
 *  [1,1,1],
 *  [0,1,1]]
 * Output: 1
 */

/*
 * Example 2:
 * Input:
 * [[1,1,0],
 *  [1,1,1],
 *  [0,1,1]]
 * Output: 1
 */

#include <vector>

using namespace std;

class UnionFindSet {
public:
    UnionFindSet(int n)
    {
        _set_size = n;
        _father = vector<int>(_set_size, -1);
        _rank = vector<int>(_set_size, 0);
        for(int i = 0; i < _set_size; ++i)
            _father[i] = i;
    }

    ~UnionFindSet(){}

    bool same(int x, int y)
    {
        return _find(x) == _find(y);
    }

    void merge(int x, int y)
    {
        x = _find(x);
        y = _find(y);
        if(x == y) return;

        // 此时 x, y 是所在树的根
        if(_rank[x] < _rank[y])
            _father[x] = y;
        else
        {
            _father[y] = x;
            if(_rank[x] == _rank[y])
                ++_rank[x];
        }

        --_set_size;
    }

    int set_size()
    {
        return _set_size;
    }

private:
    vector<int> _father;
    vector<int> _rank;
    int _set_size;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        else
            return _father[x] = _find(_father[x]); // 路径压缩
    }
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int m = M.size();
        if(m == 1) return 1;
        UnionFindSet unionfindset(m);
        for(int i = 0; i < m - 1; ++i)
            for(int j = i + 1; j < m; ++j)
                if(M[i][j] == 1)
                    unionfindset.merge(i, j);
        return unionfindset.set_size();
    }
};
