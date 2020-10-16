// prob1057: Campus Bikes

/*
 * https://leetcode-cn.com/problems/campus-bikes/
 */

#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Pair
{
    int x1, y1, x2, y2;
    int d;
    int id1, id2;
    Pair(int x1, int y1, int x2, int y2, int id1, int id2):x1(x1),y1(y1),x2(x2),y2(y2),id1(id1),id2(id2)
    {
        d = abs(x1 - x2) + abs(y1 - y2);
    }
};

struct Cmp
{
    bool operator()(const Pair& p1, const Pair& p2) const
    {
        if(p1.d == p2.d)
        {
            if(p1.id1 == p2.id1)
                return p1.id2 < p2.id2;
            return p1.id1 < p2.id1;
        }
        return p1.d < p2.d;
    }
};

class Solution {
public:
    vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        int n = workers.size(), m = bikes.size();
        vector<bool> used1(n, false), used2(m, false);
        vector<Pair> pairs;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                pairs.emplace_back(workers[i][0], workers[i][1], bikes[j][0], bikes[j][1], i, j);
        sort(pairs.begin(), pairs.end(), Cmp());
        vector<int> result(n, -1);
        for(const Pair& p: pairs)
        {
            if(used1[p.id1] || used2[p.id2])
                continue;
            result[p.id1] = p.id2;
            used1[p.id1] = true;
            used2[p.id2] = true;
        }
        return result;
    }
};
