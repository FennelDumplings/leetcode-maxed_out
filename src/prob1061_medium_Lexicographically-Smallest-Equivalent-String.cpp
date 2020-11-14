// prob1061: Lexicographically Smallest Equivalent String

/*
 * https://leetcode-cn.com/problems/lexicographically-smallest-equivalent-string/
 */

#include <vector>
#include <string>

using namespace std;

class UnionFindSet
{
public:
    UnionFindSet(int n)
    {
        _father.assign(n, 0);
        _rank.assign(n, 0);
        _weight.assign(n, 0);
        for(int i = 0; i < n; ++i)
        {
            _father[i] = i;
            _weight[i] = i;
        }
    }

    void merge(int x, int y)
    {
        x = _find(x);
        y = _find(y);
        if(x == y) return;

        if(_rank[x] < _rank[y])
        {
            _father[x] = y;
            _weight[y] = min(_weight[x], _weight[y]);
        }
        else
        {
            _father[y] = x;
            _weight[x] = min(_weight[x], _weight[y]);
            if(_rank[x] == _rank[y])
                ++_rank[x];
        }
    }

    int get_weight(int x)
    {
        return _weight[_find(x)];
    }

private:
    vector<int> _father;
    vector<int> _rank;
    vector<int> _weight;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        return _father[x] = _find(_father[x]);
    }
};

class Solution {
public:
    string smallestEquivalentString(string A, string B, string S) {
        UnionFindSet unionfindset(26);
        int n = A.size();
        for(int i = 0; i < n; ++i)
            unionfindset.merge(A[i] - 'a', B[i] - 'a');
        string result = S;
        for(char &ch: result)
            ch = 'a' + unionfindset.get_weight(ch - 'a');
        return result;
    }
};
