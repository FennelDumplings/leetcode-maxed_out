// prob85: Maximal Rectangle

/*
 * Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.
 */

/*
 * Example:
 * Input:
 * [
 *   ["1","0","1","0","0"],
 *   ["1","0","1","1","1"],
 *   ["1","1","1","1","1"],
 *   ["1","0","0","1","0"]
 * ]
 * Output: 6
 */

#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.empty()) return 0;
        int n = matrix.size(), m = matrix[0].size();
        vector<int> heights(m, 0);
        int result = 0;
        for(int i = 0; i < n; ++i)
        {
            _get_geights(matrix, heights, i);
            int result_i = _max_rec_hist(heights);
            result = max(result, result_i);
        }
        return result;
    }

private:
    void _get_geights(vector<vector<char> >& matrix, vector<int>& heights, int i)
    {
        int m = matrix[0].size();
        for(int j = 0; j < m; ++j)
        {
            int cnt = 0;
            int h = i;
            while(h >= 0 && matrix[h][j] == '1')
            {
                ++cnt;
                --h;
            }
            heights[j] = cnt;
        }
    }

    int _max_rec_hist(vector<int>& heights)
    {
        int m = heights.size();
        stack<int> st;
        st.push(-1);
        int result = 0;
        for(int j = 0; j < m; ++j)
        {
            while(st.top() != -1 && heights[st.top()] > heights[j])
            {
                int h = heights[st.top()];
                st.pop();
                int l = st.top();
                int w = j - l - 1;
                result = max(result, h * w);
            }
            st.push(j);
        }
        while(st.top() != -1)
        {
            int h = heights[st.top()];
            st.pop();
            int l = st.top();
            int w = m - l - 1;
            result = max(result, w * h);
        }
        return result;
    }
};
