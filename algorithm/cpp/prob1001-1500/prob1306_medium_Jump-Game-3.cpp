// prob1306: Jump Game III

/*
 * https://leetcode-cn.com/problems/jump-game-iii/
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();
        visited = vector<bool>(n, false);
        return dfs(arr, start);
    }

private:
    vector<bool> visited;

    bool dfs(const vector<int>& arr, int pos)
    {
        if(arr[pos] == 0)
            return true;
        if(visited[pos])
            return false;
        visited[pos] = true;
        int n = arr.size();
        int nxt1 = pos + arr[pos];
        if(nxt1 >= 0 && nxt1 < n && dfs(arr, nxt1))
            return true;
        int nxt2 = pos - arr[pos];
        if(nxt2 >= 0 && nxt2 < n && dfs(arr, nxt2))
            return true;
        return false;
    }
};
