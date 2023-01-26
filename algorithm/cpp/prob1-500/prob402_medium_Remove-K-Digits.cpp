// prob402: Remove K Digits

/*
 * Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.
 * Note:
 * The length of num is less than 10002 and will be ≥ k.
 * The given num does not contain any leading zero.
 */

/*
 * Example 1:
 * Input: num = "1432219", k = 3
 * Output: "1219"
 * Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
 * Example 2:
 * Input: num = "10200", k = 1
 * Output: "200"
 * Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
 * Example 3:
 * Input: num = "10", k = 2
 * Output: "0"
 * Explanation: Remove all the digits from the number and it is left with nothing which is 0.
 */

#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    string removeKdigits(string num, int k) {
        if(num.empty()) return "0";
        int n = num.size();
        if(k == n) return "0";
        stack<char> st;
        st.push(num[0]);
        for(int i = 1; i < n; ++i)
        {
            while(k > 0 && !st.empty() && st.top() > num[i])
            {
                st.pop();
                --k;
            }
            st.push(num[i]);
        }
        while(k > 0)
        {
            st.pop();
            --k;
        }
        int m = st.size();
        string result(m, ' ');
        for(int i = m - 1; i >= 0; --i)
        {
            result[i] = st.top();
            st.pop();
        }
        int start = 0;
        while(start < m && result[start] == '0')
            ++start;
        if(start == m) return "0";
        return result.substr(start);
    }
};
