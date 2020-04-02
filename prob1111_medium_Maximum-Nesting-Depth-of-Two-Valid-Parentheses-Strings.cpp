// prob1111: Maximum Nesting Depth of Two Valid Parentheses Strings

/*
 * 给你一个合法的括号序列，你需要将其拆分成两个合法的子序列（不连续），使得两个子序列的括号嵌套深度较大者尽量的小。
 */

/*
 * Example 1:
 * Input: seq = "(()())"
 * Output: [0,1,1,1,1,0]
 * Example 2:
 * Input: seq = "()(())()"
 * Output: [0,0,0,1,1,0,1,1]
 */

/*
 * Constraints:
 * 1 <= seq.size <= 10000
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        if(seq.empty()) return vector<int>();
        int n = seq.size();
        int cnt = 0;
        vector<int> result(n, -1);
        for(int i = 0; i < n; ++i)
        {
            if(seq[i] == '(')
            {
                ++cnt;
                if(cnt & 1)
                    result[i] = 0;
                else
                    result[i] = 1;
            }
            else
            {
                if(cnt & 1)
                    result[i] = 0;
                else
                    result[i] = 1;
                --cnt;
            }
        }
        return result;
    }
};
