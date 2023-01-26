// prob649: Dota2 Senate
/*
 * In the world of Dota2, there are two parties: the Radiant and the Dire.
 *
 * The Dota2 senate consists of senators coming from two parties. Now the senate wants to make a decision about a change in the Dota2 game. The voting for this change is a round-based procedure. In each round, each senator can exercise one of the two rights:
 *
 * Ban one senator's right:
 * A senator can make another senator lose all his rights in this and all the following rounds.
 * Announce the victory:
 * If this senator found the senators who still have rights to vote are all from the same party, he can announce the victory and make the decision about the change in the game.
 *  
 *
 * Given a string representing each senator's party belonging. The character 'R' and 'D' represent the Radiant party and the Dire party respectively. Then if there are n senators, the size of the given string will be n.
 *
 * The round-based procedure starts from the first senator to the last senator in the given order. This procedure will last until the end of voting. All the senators who have lost their rights will be skipped during the procedure.
 *
 * Suppose every senator is smart enough and will play the best strategy for his own party, you need to predict which party will finally announce the victory and make the change in the Dota2 game. The output should be Radiant or Dire.
 */

/*
 * Example 1:
 *
 * Input: "RD"
 * Output: "Radiant"
 * Explanation: The first senator comes from Radiant and he can just ban the next senator's right in the round 1.
 * And the second senator can't exercise any rights any more since his right has been banned.
 * And in the round 2, the first senator can just announce the victory since he is the only guy in the senate who can vote.
 *  
 *
 * Example 2:
 *
 * Input: "RDD"
 * Output: "Dire"
 * Explanation:
 * The first senator comes from Radiant and he can just ban the next senator's right in the round 1.
 * And the second senator can't exercise any rights anymore since his right has been banned.
 * And the third senator comes from Dire and he can ban the first senator's right in the round 1.
 * And in the round 2, the third senator can just announce the victory since he is the only guy in the senate who can vote.
 */

/*
 * Note:
 * The length of the given string will in the range [1, 10,000].
 */

#include <string>
#include <stack>
#include <deque>
#include <set>

using namespace std;

class Solution {
public:
    string predictPartyVictory(string senate) {
        int n = senate.size();
        int nd = 0;
        for(int i: senate)
            if(i == 'D')
                ++nd;
        int nr = n - nd;
        if(nr == 0) return "Dire";
        if(nd == 0) return "Radiant";
        stack<int> st_d, st_r; // 有权利尚未使用
        while(true)
        {
            for(int i = 0; i < n; ++i)
            {
                int cur = senate[i];
                if(cur == ' ') continue;
                if(cur == 'R')
                {
                    // 看 R 是否被限制权力
                    if(!st_d.empty())
                    {
                        // 被限制
                        senate[i] = ' ';
                        --nr;
                        if(nr == 0)
                            return "Dire";
                        st_d.pop();
                    }
                    else
                    {
                        // 未被限制
                        st_r.push(i);
                    }
                }
                else
                {
                    // 看 D 是否被限制权利
                    if(!st_r.empty())
                    {
                        // 被限制
                        senate[i] = ' ';
                        --nd;
                        if(nd == 0)
                            return "Radiant";
                        st_r.pop();
                    }
                    else
                    {
                        // 未被限制
                        st_d.push(i);
                    }
                }
            }
        }
    }
};
