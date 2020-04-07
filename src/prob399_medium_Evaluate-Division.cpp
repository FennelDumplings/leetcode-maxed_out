// prob399: Evaluate Division

/*
 * Equations are given in the format A / B = k, where A and B are variables represented as strings,
 * and k is a real number (floating point number). Given some queries, return the answers. If the answer does not exist, return -1.0.
 */

/*
 * Example:
 * Given a / b = 2.0, b / c = 3.0.
 * queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? .
 * return [6.0, 0.5, -1.0, 1.0, -1.0 ].
 */

/*
 * The input is always valid. You may assume that evaluating the queries will result in no division by zero and there is no contradiction.
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class WeightUnionFindSet
{
public:
    WeightUnionFindSet(int N)
    {
        _father = vector<int>(N, -1);
        _rank = vector<int>(N, 1);
        _weight = vector<double>(N, 1.0); // a / a = 1.0
        for(int i = 0; i < N; ++i)
            _father[i] = i;
    }

    bool same(int x, int y)
    {
        return _find(x) == _find(y);
    }

    double get_weight(int x)
    {
        _find(x);
        return _weight[x];
    }

    void merge(int x, int y, double w)
    {
        int rootx = _find(x);
        int rooty = _find(y);
        if(rootx == rooty) return;
        if(_rank[rootx] < _rank[rooty])
        {
            _father[rootx] = rooty;
            _weight[rootx] = _weight[y] * w / _weight[x];
        }
        else
        {
            _father[rooty] = rootx;
            _weight[rooty] = _weight[x] * (1 / w) / _weight[y];
        }
        if(_rank[rootx] == _rank[rooty])
            ++_rank[rootx];
    }



private:
    vector<int> _father;
    vector<int> _rank;
    vector<double> _weight;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        int new_fa = _find(_father[x]);; // 路径压缩前的父节点
        _weight[x] *= _weight[_father[x]];
        _father[x] = new_fa;
        return _father[x];
    }
};

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        if(equations.empty()) return vector<double>((int)queries.size(), -1.0);
        int n = equations.size();
        unordered_map<string, int> item_id;
        int N = 0;
        for(const vector<string> &equation: equations)
        {
            for(const string &item: equation)
            {
                auto it = item_id.find(item);
                if(it == item_id.end())
                    item_id[item] = N++;
            }
        }
        WeightUnionFindSet weightunionfindset(N);
        for(int i = 0; i < n; ++i)
        {
            int x = item_id[equations[i][0]];
            int y = item_id[equations[i][1]];
            double w = values[i];
            if(!weightunionfindset.same(x, y))
                weightunionfindset.merge(x, y, w);
        }
        vector<double> result;
        for(const vector<string> &query: queries)
        {
            if(item_id.find(query[0]) == item_id.end() || item_id.find(query[1]) == item_id.end())
            {
                result.push_back(-1.0);
                continue;
            }
            int x = item_id[query[0]], y = item_id[query[1]];
            if(!weightunionfindset.same(x, y))
            {
                result.push_back(-1.0);
                continue;
            }
            double tmp = weightunionfindset.get_weight(x) / weightunionfindset.get_weight(y);
            result.push_back(tmp);
        }
        return result;
    }
};
