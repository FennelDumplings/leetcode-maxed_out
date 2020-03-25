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

// 状态压缩DP
// 以行为状态
// Ref: https://www.acwing.com/solution/LeetCode/content/8328/
class Solution {
public:
    bool check(const vector<vector<char>>& seats, int i, int s1, int s2, int n) {
        for (int j = 0; j < n; j++)
            if (s2 & (1 << j)) {
                if (seats[i][j] == '#')
                    return false;

                if (j > 0 && ((s1 & (1 << (j - 1))) || (s2 & (1 << (j - 1)))))
                    return false;

                if (j < n - 1 && ((s1 & (1 << (j + 1))) || (s2 & (1 << (j + 1)))))
                    return false;
            }

        return true;
    }

    int maxStudents(vector<vector<char>>& seats) {
        int m = seats.size(), n = seats[0].size();
        vector<vector<int>> f(m + 1, vector<int>(1 << n, 0));
        vector<int> c(1 << n, 0);

        for (int s = 0; s < (1 << n); s++)
            for (int j = 0; j < n; j++)
                if (s & (1 << j))
                    c[s]++;

        f[0][0] = 0;
        for (int i = 1; i <= m; i++)
            for (int s1 = 0; s1 < (1 << n); s1++)
                for (int s2 = 0; s2 < (1 << n); s2++)
                    if (check(seats, i - 1, s1, s2, n))
                        f[i][s2] = max(f[i][s2], f[i - 1][s1] + c[s2]);

        int ans = 0;

        for (int s = 0; s < (1 << n); s++)
            ans = max(ans, f[m][s]);

        return ans;
    }
};

// 状态压缩 + 记忆化递归
// Ref: https://leetcode-cn.com/problems/maximum-students-taking-exam/solution/can-jia-kao-shi-de-zui-da-xue-sheng-shu-by-leetcod/
class Solution_1 {
    int memory[8][1 << 8];
    vector<int> compressed_seats;
    int f(int X, int row_num, int width) {
        if (memory[row_num][X] != -1)
            return memory[row_num][X];
        int ans = 0;
        for (int scheme = 0; scheme != (1 << width); ++scheme) {
            if (scheme & ~X || scheme & (scheme << 1))
                continue;
            int curans = 0;
            for (int j = 0; j != width; ++j)
                if ((1 << j) & scheme)
                    ++curans;
            if (row_num == compressed_seats.size() - 1)
                ans = max(ans, curans);
            else {
                int next_seats = compressed_seats[row_num + 1];
                next_seats &= ~(scheme << 1);
                next_seats &= ~(scheme >> 1);
                ans = max(ans, curans + f(next_seats, row_num + 1, width));
            }
        }
        memory[row_num][X] = ans;
        return ans;
    }

    int compress(vector<char>& row) {
        int ans = 0;
        for (char c : row) {
            ans <<= 1;
            if (c == '.')
                ++ans;
        }
        return ans;
    }

public:
    int maxStudents(vector<vector<char>>& seats) {
        for (int i = 0; i != seats.size(); ++i)
            for (int j = 0; j != (1 << seats[0].size()); ++j)
                memory[i][j] = -1;
        for (auto row: seats)
            compressed_seats.push_back(compress(row));
        return f(compressed_seats[0], 0, seats[0].size());
    }
};

// 状态压缩DP
// 以列做状态
// 36ms, 击败26.51%
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
