// prob1237: Find Positive Integer Solution for a Given Equation

/*
 * https://leetcode-cn.com/problems/find-positive-integer-solution-for-a-given-equation/
 */

/*
 * // This is the custom function interface.
 * // You should not implement it, or speculate about its implementation
 */

#include <vector>
#include <unordered_set>

using namespace std;

class CustomFunction {
public:
    // Returns f(x, y) for any given positive integers x and y.
    // Note that f(x, y) is increasing with respect to both x and y.
    // i.e. f(x, y) < f(x + 1, y), f(x, y) < f(x, y + 1)
    int f(int x, int y);
};

class Solution {
public:
    vector<vector<int>> findSolution(CustomFunction& customfunction, int z) {
        vector<vector<int>> result;
        dfs(customfunction, z, 1, 1, result);
        return result;
    }

private:
    unordered_set<int> setting;
    const int maxx = 1001;

    void dfs(CustomFunction& customfunction, int z, int x, int y, vector<vector<int>>& result)
    {
        if(setting.count(x * maxx + y) > 0)
            return;
        setting.insert(x * maxx + y);
        int res = customfunction.f(x, y);
        if(res == z)
        {
            result.push_back({x, y});
            return;
        }
        else if(res < z)
        {
            dfs(customfunction, z, x + 1, y, result);
            dfs(customfunction, z, x, y + 1, result);
        }
    }
};
