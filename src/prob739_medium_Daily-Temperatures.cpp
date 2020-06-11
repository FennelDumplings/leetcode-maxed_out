// prob739: Daily Temperatures

/*
 * Given a list of daily temperatures T, return a list such that, for each day in the input, tells you how many
 * days you would have to wait until a warmer temperature. If there is no future day for which this is possible, put 0 instead.
 * For example, given the list of temperatures T = [73, 74, 75, 71, 69, 72, 76, 73], your output
 * should be [1, 1, 4, 2, 1, 1, 0, 0].
 * Note: The length of temperatures will be in the range [1, 30000]. Each temperature will be an integer in the range [30, 100].
 */

#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        int n = T.size();
        stack<int> st;
        vector<int> result(n, -1);
        for(int i = 0; i < n; ++i)
        {
            while(!st.empty() && T[st.top()] < T[i])
            {
                result[st.top()] = i - st.top();
                st.pop();
            }
            st.push(i);
        }
        while(!st.empty())
        {
            result[st.top()] = 0;
            st.pop();
        }
        return result;
    }
};
