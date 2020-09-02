// prob389: Longest Absolute File Path

/*
 * https://leetcode-cn.com/problems/longest-absolute-file-path/
 */

#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    int lengthLongestPath(string input) {
        stack<int> st;
        int n = input.size();
        int left = 0;
        int level = 0;
        string item = "";
        int ans = 0;
        while(left < n)
        {
            // 多少个 \t 前缀
            int cnt = 0;
            int right = left;
            while(right < n && input[right] == '\t')
            {
                ++cnt;
                ++right;
            }
            left = right;
            bool file = false;
            // 推进 left 直至 '\n'
            while(right < n && input[right] != '\n')
            {
                if(input[right] == '.')
                    file = true;
                ++right;
            }
            string cur = input.substr(left, right - left);
            // 使得 level == cnt - 1
            while(level > cnt)
            {
                int len = st.top();
                st.pop();
                item.erase((int)item.size() - len);
                --level;
            }
            item += '/' + cur;
            ++level;
            st.push(right - left + 1);
            if(file)
                ans = max(ans, (int)item.size() - 1);
            left = right + 1;
        }
        return ans;
    }
};
