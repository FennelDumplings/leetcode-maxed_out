// prob1349: Maximum Students Taking Exam

/*
 * Given a m * n matrix seats  that represent seats distributions in a classroom. If a seat is broken,
 * it is denoted by '#' character otherwise it is denoted by a '.' character.
 * Students can see the answers of those sitting next to the left, right, upper left and upper right,
 * but he cannot see the answers of the student sitting directly in front or behind him. Return the maximum
 * number of students that can take the exam together without any cheating being possible..
 * Students must be placed in seats in good condition.
 */

/*
 * Constraints:
 * seats contains only characters '.' and'#'.
 * m == seats.length
 * n == seats[i].length
 * 1 <= m <= 8
 * 1 <= n <= 8
 */

/*
 * Example 1:
 * Input: seats = [["#",".","#","#",".","#"],
 *                 [".","#","#","#","#","."],
 *                 ["#",".","#","#",".","#"]]
 * Output: 4
 * Explanation: Teacher can place 4 students in available seats so they don't cheat on the exam.
 * Example 2:
 * Input: seats = [[".","#"],
 *                 ["#","#"],
 *                 ["#","."],
 *                 ["#","#"],
 *                 [".","#"]]
 * Output: 3
 * Explanation: Place all students in available seats.
 * Example 3:
 * Input: seats = [["#",".",".",".","#"],
 *                 [".","#",".","#","."],
 *                 [".",".","#",".","."],
 *                 [".","#",".","#","."],
 *                 ["#",".",".",".","#"]]
 * Output: 10
 * Explanation: Place students in available seats in column 1, 3 and 5.
 */

#include <vector>

using namespace std;



// 答案不对
class Solution_2 {
public:
    int maxStudents(vector<vector<char> >& seats) {
        int m = seats.size(), n = seats[0].size();
        vector<int> available(n + 1, 0);
        for(int j = 0; j < n; ++j)
        {
            int avail = 0;
            for(int i = 0; i < m; ++i)
                if(seats[i][j] == '.')
                    avail |= (1 << i);
            available[j + 1] = avail;
        }

        vector<vector<int> > dp(n + 1, vector<int>((1 << m), 0));
        int subset = available[n];
        dp[n][subset] = _count1(subset);
        // 枚举子集的写法
        subset = ((subset - 1) & available[n]);
        for(; subset != available[n]; subset = ((subset - 1) & available[n]))
            dp[n][subset] = _count1(subset);

        for(int j = n - 1; j >= 0; --j)
        {
            // 可选 available[j], available[0] = 0
            subset = available[j];
            do
            {
                dp[j][subset] = _count1(subset);
                int subset_right = available[j + 1];
                do
                {
                    if(_check(subset, subset_right, m))
                        dp[j][subset] = max(dp[j][subset], _count1(subset) + dp[j + 1][subset_right]);
                    subset_right = (subset_right - 1) & available[j + 1];
                }while(subset_right != available[j + 1]);
                subset = (subset - 1) & available[j];
            }while(subset != available[j]);
        }

        return dp[0][0];
    }

private:
    bool _check(int state1, int state2, int m)
    {
        // state2[0] == 1 则 state1[0] != 1 && state1[1] != 1
        if(state2 & 1)
        {
            if((state1 & 1) || (state1 & (1 << 1)))
                return false;
        }
        // state2[m - 1] == 1 则 state1[m - 1] != 1 && state1[m - 2] != 1
        if(state2 & (1 << (m - 1)))
        {
            if((state1 & (1 << (m - 1))) || (state1 & (1 << (m - 2))))
                return false;
        }
        // state2[i] == 1 则 state1[i] != 1 && state1[i - 1] != 1 && state1[i + 1] != 1 (1 <= i <= m - 2)
        for(int k = 1; k <= m - 2; ++k)
        {
            if(state2 & (1 << k))
            {
                if((state1 & (1 << k)) || (state1 & (1 << (k - 1))) || (state1 & (1 << (k + 1))))
                    return false;
            }
        }
        return true;
    }

    int _count1(int n)
    {
        int result = 0;
        while(n)
        {
            ++result;
            n &= (n - 1);
        }
        return result;
    }
};
