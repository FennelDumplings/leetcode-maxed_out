// prob294: Flip Game 2

/*
 * You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -,
 * you and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer
 * make a move and therefore the other person will be the winner.
 * Write a function to determine if the starting player can guarantee a win.
 */

/*
 * Example:
 * Input: s = "++++"
 * Output: true
 * Explanation: The starting player can guarantee a win by flipping the middle "++" to become "+--+".
 */

#include <string>
#include <unordered_map>

using namespace std;

// 记忆化搜索
// 策梅洛定理
class Solution {
public:
    bool canWin(string s) {
        int n = s.size();
        if(n < 2) return false;
        unordered_map<string, bool> mapping;
        string state = s;
        return _canWin(state, mapping);
    }

private:
    bool _canWin(string& state, unordered_map<string, bool>& mapping)
    {
        int n = state.size();
        if(mapping.find(state) != mapping.end()) // 该状态已经算过
            return mapping[state];
        for(int i = 0; i < n - 1; ++i) // 枚举所有次态
        {
            if(state[i] == '+' && state[i + 1] == '+')
            {
                state[i] = '-';
                state[i + 1] = '-';
                bool f = _canWin(state, mapping);
                state[i] = '+';
                state[i + 1] = '+';
                if(!f)
                {
                    mapping[state] = true;
                    return true;
                }
            }
        }
        mapping[state] = false;
        return false;
    }
};
