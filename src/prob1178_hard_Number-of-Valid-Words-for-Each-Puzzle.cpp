// prob1178: Number of Valid Words for Each Puzzle

/*
 * https://leetcode-cn.com/problems/number-of-valid-words-for-each-puzzle/
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        unordered_map<int, int> mapping; // bitmap 模式 -> 单词个数
        for(const string &w: words)
        {
            int pattern = 0;
            for(const char &ch: w)
                pattern |= (1 << (ch - 'a'));
            ++mapping[pattern];
        }
        int m = puzzles.size();
        vector<int> result(m);
        for(int i = 0; i < m; ++i)
        {
            int s = 0;
            for(const char &ch: puzzles[i])
                s |= 1 << (ch - 'a');
            result[i] += mapping[s];
            // 枚举 s 的真子集
            for(int subset = (s - 1) & s; subset != s; subset = (subset - 1) & s)
            {
                if(subset & (1 << (puzzles[i][0] - 'a')))
                    result[i] += mapping[subset];
            }
        }
        return result;
    }
};
