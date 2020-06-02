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
        vector<int> nums;
        vector<char> symbols;
        vector<int> result;
        int n = input.size();
        dfs(input, 0, nums, symbols, result, n);
        return result;
    }

private:
    void dfs(const string& input, int pos, vector<int>& nums, vector<char>& symbols, vector<int>& result, int n)
    {
        if(pos == n)
        {
            int i = nums.size() - 1;
            int j = symbols.size() - 1;
            int tmp = nums[i];
            --i;
            while(j >= 0)
            {
                int x = nums[i];
                --i;
                if(symbols[j] == '*')
                    tmp = tmp * x;
                else if(symbols[j] == '+')
                    tmp = tmp + x;
                else
                    tmp = x - tmp;
                --j;
            }
            result.push_back(tmp);
            return;
        }

        if(input[pos] == '*')
        {
            symbols.push_back('*');
            dfs(input, pos + 1, nums, symbols, result, n);
            return;
        }
        if(input[pos] == '+')
        {
            symbols.push_back('+');
            dfs(input, pos + 1, nums, symbols, result, n);
            return;
        }
        if(input[pos] == '-')
        {
            symbols.push_back('-');
            dfs(input, pos + 1, nums, symbols, result, n);
            return;
        }

        int iter = pos;
        while(iter < n &&  (input[iter] >= '0' && input[iter] <= '9'))
            ++iter;
        int cur;
        stringstream ss;
        ss << input.substr(pos, iter - pos);
        ss >> cur;

        nums.push_back(cur);
        dfs(input, iter, nums, symbols, result, n);
        nums.pop_back();

        if(!symbols.empty())
        {
            int tmp = nums.back();
            if(symbols.back() == '*')
                tmp *= cur;
            else if(symbols.back() == '-')
                tmp -= cur;
            else
                tmp += cur;
            nums[nums.size() - 1] = tmp;
            symbols.pop_back();
            dfs(input, iter, nums, symbols, result, n);
        }

    }
};
