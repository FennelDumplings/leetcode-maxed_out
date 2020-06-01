// prob996: Number of Squareful Arrays

/*
 * Given an array A of non-negative integers, the array is squareful if for every pair of adjacent elements,
 * their sum is a perfect square.
 * Return the number of permutations of A that are squareful.  Two permutations A1 and A2 differ if and
 * only if there is some index i such that A1[i] != A2[i].
 */

/*
 * Example 1:
 * Input: [1,17,8]
 * Output: 2
 * Explanation:
 * [1,8,17] and [17,8,1] are the valid permutations.
 * Example 2:
 * Input: [2,2,2]
 * Output: 1
 */

/*
 * Note:
 *
 * 1 <= A.length <= 12
 * 0 <= A[i] <= 1e9
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numSquarefulPerms(vector<int>& A) {
        int n = A.size();
        sort(A.begin(), A.end());
        vector<bool> visited(n, false);
        int ans = 0;
        int prev = -1;
        for(int i = 0; i < n; ++i)
        {
            if(A[i] == prev) continue;
            prev = A[i];
            visited.assign(n, false);
            visited[i] = true;
            dfs(A, i, visited, ans, 0);
        }
        return ans;
    }

private:
    void dfs(const vector<int>& A, int prev_idx, vector<bool>& visited, int& ans, int pos)
    {
        int n = visited.size();
        if(pos == n - 1)
            ++ans;
        int prev = -1;
        for(int i = 0; i < n; ++i)
        {
            if(visited[i]) continue;
            if(!_check(A[prev_idx], A[i])) continue;
            if(A[i] == prev) continue;
            prev = A[i];
            visited[i] = true;
            dfs(A, i, visited, ans, pos + 1);
            visited[i] = false;
        }
    }

    using ll = long long;;

    bool _check(int a, int b)
    {
        int sum = a + b;
        int left = 0, right = sum;
        while(left <= right)
        {
            int mid = (left + right) / 2;
            if((ll)mid * mid == sum)
                return true;
            if((ll)mid * mid > sum)
                right = mid - 1;
            else
                left = mid + 1;
        }
        return false;
    }
};
