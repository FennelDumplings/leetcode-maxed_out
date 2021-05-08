
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class UnionFindSet {
public:
    UnionFindSet(int n)
    {
        _father = vector<int>(n, -1);
        _rank = vector<int>(n, 0);
        _elements = vector<vector<int>>(n, vector<int>{});
        for(int i = 0; i < n; ++i)
        {
            _elements[i].push_back(i);
            roots.insert(i);
            _father[i] = i;
        }
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

        if(_rank[x] < _rank[y])
        {
            roots.erase(x);
            _elements[y].insert(_elements[y].end(), _elements[x].begin(), _elements[x].end());
            _father[x] = y;
        }
        else
        {
            roots.erase(y);
            _elements[x].insert(_elements[x].end(), _elements[y].begin(), _elements[y].end());
            _father[y] = x;
            if(_rank[x] == _rank[y])
                ++_rank[x];
        }
    }

    vector<int> get_cc(int x)
    {
        return _elements[_find(x)];
    }

    vector<vector<int>> get_cc_list()
    {
        vector<vector<int>> result;
        for(int x: roots)
        {
            result.push_back(get_cc(x));
        }
        return result;
    }

private:
    vector<int> _father;
    vector<int> _rank;
    vector<vector<int>> _elements; // 连通分量内的元素
    unordered_set<int> roots;

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
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = source.size();
        UnionFindSet unionfindset(n);
        for(const vector<int> &edge: allowedSwaps)
            unionfindset.merge(edge[0], edge[1]);
        vector<vector<int>> cc_list =  unionfindset.get_cc_list(); // 所有的连通分量
        int match = 0;
        for(const vector<int> &cc: cc_list)
        {
            unordered_map<int, int> cnts;
            for(int i: cc)
                ++cnts[source[i]];
            for(int i: cc)
            {
                if(cnts.count(target[i]) > 0)
                {
                    ++match;
                    --cnts[target[i]];
                    if(cnts[target[i]] == 0)
                        cnts.erase(target[i]);
                }
            }
        }
        return n - match;
    }
};
