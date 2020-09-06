// prob242: Different Ways to Add Parentheses

/*
 * Given a string of numbers and operators, return all possible results from computing all the different
 * possible ways to group numbers and operators. The valid operators are +, - and *.
 */

/*
 * Example 1:
 * Input: "2-1-1"
 * Output: [0, 2]
 * Explanation:
 * ((2-1)-1) = 0
 * (2-(1-1)) = 2
 * Example 2:
 * Input: "2*3-4*5"
 * Output: [-34, -14, -10, -10, 10]
 * Explanation:
 * (2*(3-(4*5))) = -34
 * ((2*3)-(4*5)) = -14
 * ((2*(3-4))*5) = -10
 * (2*((3-4)*5)) = -10
 * (((2*3)-4)*5) = 10
 */

#include <stack>
#include <vector>
#include <string>
#include <unordered_set>
#include <sstream>

using namespace std;

class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> symbol_idxs;
        int n = input.size();
        for(int i = 0; i < n; ++i)
        {
            char ch = input[i];
            if(ch == '+' || ch == '-' || ch == '*')
                symbol_idxs.push_back(i);
        }
        return solve(input, 0, n - 1, symbol_idxs);
    }

private:
    // 分治
    vector<int> solve(const string& input, int left, int right, const vector<int>& symbol_idxs)
    {
        // [left, right]
        auto it_partition_left = lower_bound(symbol_idxs.begin(), symbol_idxs.end(), left);
        if(it_partition_left == symbol_idxs.end() || right < *it_partition_left)
        {
            int num;
            stringstream ss;
            ss << input.substr(left, right - left + 1);
            ss >> num;
            return {num};
        }

        vector<int> result_left, result_right;
        vector<int> result;
        auto it_partition_right = lower_bound(symbol_idxs.begin(), symbol_idxs.end(), right) - 1;
        for(auto it = it_partition_left; it <= it_partition_right; ++it)
        {
            int partition = *it;
            result_left = solve(input, left, partition - 1, symbol_idxs);
            result_right = solve(input, partition + 1, right, symbol_idxs);
            for(int l: result_left)
                for(int r: result_right)
                {
                    if(input[partition] == '+')
                    {
                        result.push_back(l + r);
                    }
                    else if(input[partition] == '-')
                    {
                        result.push_back(l - r);
                    }
                    else if(input[partition] == '*')
                    {
                        result.push_back(l * r);
                    }
                }
        }
        return result;
    }
};

// 记忆化
class Solution_2 {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> symbol_idxs;
        int n = input.size();
        for(int i = 0; i < n; ++i)
        {
            char ch = input[i];
            if(ch == '+' || ch == '-' || ch == '*')
                symbol_idxs.push_back(i);
        }
        dp = vector<vector<vector<int>>>(n, vector<vector<int>>(n));
        return solve(input, 0, n - 1, symbol_idxs);
    }

private:
    vector<vector<vector<int>>> dp;

    // 分治
    vector<int> solve(const string& input, int left, int right, const vector<int>& symbol_idxs)
    {
        if(!dp[left][right].empty())
            return dp[left][right];
        // [left, right]
        auto it_partition_left = lower_bound(symbol_idxs.begin(), symbol_idxs.end(), left);
        if(it_partition_left == symbol_idxs.end() || right < *it_partition_left)
        {
            int num;
            stringstream ss;
            ss << input.substr(left, right - left + 1);
            ss >> num;
            return dp[left][right] = {num};
        }

        vector<int> result_left, result_right;
        vector<int> result;
        auto it_partition_right = lower_bound(symbol_idxs.begin(), symbol_idxs.end(), right) - 1;
        for(auto it = it_partition_left; it <= it_partition_right; ++it)
        {
            int partition = *it;
            result_left = solve(input, left, partition - 1, symbol_idxs);
            result_right = solve(input, partition + 1, right, symbol_idxs);
            for(int l: result_left)
                for(int r: result_right)
                {
                    if(input[partition] == '+')
                    {
                        result.push_back(l + r);
                    }
                    else if(input[partition] == '-')
                    {
                        result.push_back(l - r);
                    }
                    else if(input[partition] == '*')
                    {
                        result.push_back(l * r);
                    }
                }
        }
        return dp[left][right] = result;
    }
};
