// prob682: Baseball Game

/*
 * https://leetcode-cn.com/problems/baseball-game/
 */

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Solution {
public:
    int calPoints(vector<string>& ops) {
        vector<int> scores;
        for(const string &op: ops)
        {
            if(op == "+")
            {
                auto it = scores.rbegin();
                int score = *it;
                ++it;
                score += *it;
                scores.push_back(score);
            }
            else if(op == "C")
            {
                scores.pop_back();
            }
            else if(op == "D")
            {
                int score = scores.back() * 2;
                scores.push_back(score);
            }
            else
            {
                int score;
                stringstream ss;
                ss << op;
                ss >> score;
                scores.push_back(score);
            }
        }
        int ans = 0;
        for(int i: scores) ans += i;
        return ans;
    }
};
