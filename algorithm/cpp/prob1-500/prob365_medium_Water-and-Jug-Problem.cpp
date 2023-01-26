// prob365: Water and Jug Problem

/*
 * You are given two jugs with capacities x and y litres. There is an infinite amount of water supply available.
 * You need to determine whether it is possible to measure exactly z litres using these two jugs.
 * If z liters of water is measurable, you must have z liters of water contained within one or both buckets by the end.
 * Operations allowed:
 * Fill any of the jugs completely with water.
 * Empty any of the jugs.
 * Pour water from one jug into another till the other jug is completely full or the first jug itself is empty.
 */

/*
 * Example 1: (From the famous "Die Hard" example)
 * Input: x = 3, y = 5, z = 4
 * Output: True
 * Example 2:
 * Input: x = 2, y = 6, z = 5
 * Output: False
 */

#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

// BFS
pair<int, int> op(int type, const pair<int, int> &state, int x, int y)
{
    switch(type) {
        case 0 : return make_pair(x, state.second);
        case 1 : return make_pair(state.first, y);
        case 2 : return make_pair(0, state.second);
        case 3 : return make_pair(state.first, 0);
        case 4 :{
            int move = min(state.first, y - state.second);
            return make_pair(state.first - move, state.second + move);
        }
        case 5 :{
            int move = min(x - state.first, state.second);
            return make_pair(state.first + move, state.second - move);
        }
    }
    return make_pair(0, 0);
}

struct HashPair
{
    size_t operator()(const pair<int, int> &key) const noexcept
    {
        return size_t(key.first)*100000007 + key.second;
    }
};

class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        unordered_set<pair<int,int>, HashPair> mark;
        queue<pair<int,int> > q;
        q.push(make_pair(0, 0));
        while(!q.empty())
        {
            auto f = q.front();
            q.pop();
            if(f.first + f.second == z)
                return true;
            for(int i = 0; i < 6; i++) {
                auto next = op(i, f, x, y);
                if(mark.find(next) != mark.end())
                    continue;
                mark.insert(next);
                q.push(next);
            }
        }
        return false;
    }
};

// 裴蜀定理
class Solution_2 {
public:
    bool canMeasureWater(int x, int y, int z) {
        if(z ==0) return true;
        if(x == y && y == 0) return false;
        if(x == 0 && y != z) return false;
        if(y == 0 && x != z) return false;
        if(x + y < z) return false;
        return z % gcd(x, y) == 0;
    }

private:
    // 辗转相除
    int gcd(int x, int y)
    {
        return x == 0 ? y : gcd(y % x, x);
    }
};
