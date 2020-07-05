// prob488: Zuma Game

/*
 * https://leetcode-cn.com/problems/zuma-game/
 */

#include <string>
#include <climits>
#include <iostream>
#include <chrono>
#include <vector>
#include <list>

using namespace std;
using namespace chrono;

class Solution {
public:
    int findMinStep(string board, string hand) {
        int ans = INT_MAX;
        dfs(board, hand, ans, 0);
        //string s = "arrtttr";
        //shrink(s);
        //cout << s << endl;
        if(ans == INT_MAX) return -1;
        return ans;
    }

private:
    void dfs(const string& board, const string& hand, int& min_step, int step)
    {
        //cout << board << " " << hand << endl;
        if(board.empty())
        {
            // cout << "ddd" << endl;
            min_step = min(min_step, step);
            return;
        }
        if(hand.empty())
        {
            return;
        }
        int n = board.size(), m = hand.size();
        for(int j = 0; j < m; ++j)
        {
            const char &ch = hand[j];
            string new_hand = hand;
            new_hand.erase(j, 1);
            for(int i = 0; i <= n; ++i)
            {
                string tmp(1, ch);
                string new_board = board;
                new_board.insert(new_board.begin() + i, tmp.begin(), tmp.end());
                shrink(new_board);
                dfs(new_board, new_hand, min_step, step + 1);
            }
        }
    }

    void shrink(string& s)
    {
        int n = s.size();
        int left = 0;
        bool flag = false;
        while(left < n)
        {
            char cur = s[left];
            int right = left + 1;
            while(right < n && s[right] == cur)
                ++right;
            int len = right - left;
            if(len >= 3)
            {
                s.erase(left, len);
                flag = true;
                break;
            }
            else
                left = right;
        }
        if(flag)
            shrink(s);
    }
};

// 在新颜色的位置插入 1 - 2 个球使其直接消除
// 如果相邻的两个球颜色相同，考虑在中间插入一个其他颜色的球分割
// 1888ms
class Solution_2 {
public:
    int findMinStep(string board, string hand) {
        int ans = INT_MAX;
        dfs(board, hand, ans, 0);
        //string s = "arrtttr";
        //shrink(s);
        //cout << s << endl;
        if(ans == INT_MAX) return -1;
        return ans;
    }

private:
    void dfs(const string& board, const string& hand, int& min_step, int step)
    {
        //cout << board << " " << hand << endl;
        if(board.empty())
        {
            // cout << "ddd" << endl;
            min_step = min(min_step, step);
            return;
        }
        if(hand.empty())
        {
            return;
        }
        int n = board.size(), m = hand.size();
        for(int j = 0; j < m; ++j)
        {
            const char &ch = hand[j];
            string new_hand = hand;
            new_hand.erase(j, 1);
            for(int i = 0; i <= n; ++i)
            {
                if(i < n && board[i] == ch)
                    continue;
                if(i > 0 && i < n && board[i - 1] != ch && board[i - 1] != board[i])
                    continue;
                string tmp(1, ch);
                string new_board = board;
                new_board.insert(new_board.begin() + i, tmp.begin(), tmp.end());
                shrink(new_board);
                dfs(new_board, new_hand, min_step, step + 1);
            }
        }
    }

    void shrink(string& s)
    {
        int n = s.size();
        int left = 0;
        bool flag = false;
        while(left < n)
        {
            char cur = s[left];
            int right = left + 1;
            while(right < n && s[right] == cur)
                ++right;
            int len = right - left;
            if(len >= 3)
            {
                s.erase(left, len);
                flag = true;
                break;
            }
            else
                left = right;
        }
        if(flag)
            shrink(s);
    }
};

// 在新颜色的位置插入 1 - 2 个球使其直接消除
// 如果相邻的两个球颜色相同，考虑在中间插入一个其他颜色的球分割
// hand 改成哈希表
// 612ms
class Solution_3 {
public:
    int findMinStep(string board, string hand) {
        int ans = INT_MAX;
        vector<int> hand_cnts(128);
        for(const char& ch: hand)
            ++hand_cnts[ch];
        dfs(board, hand_cnts, ans, 0);;
        if(ans == INT_MAX) return -1;
        return ans;
    }

private:
    void dfs(const string& board, vector<int>& hand_cnts, int& min_step, int step)
    {
        if(board.empty())
        {
            min_step = min(min_step, step);
            return;
        }
        int n = board.size();
        for(char ch: {'R', 'Y', 'B', 'G', 'W'})
        {
            if(hand_cnts[ch] == 0)
                continue;
            --hand_cnts[ch];
            for(int i = 0; i <= n; ++i)
            {
                if(i < n && board[i] == ch)
                    continue;
                if(i > 0 && i < n && board[i - 1] != ch && board[i - 1] != board[i])
                    continue;
                string tmp(1, ch);
                string new_board = board;
                new_board.insert(new_board.begin() + i, tmp.begin(), tmp.end());
                shrink(new_board);
                dfs(new_board, hand_cnts, min_step, step + 1);
            }
            ++hand_cnts[ch];
        }
    }

    void shrink(string& s)
    {
        int n = s.size();
        int left = 0;
        bool flag = false;
        while(left < n)
        {
            char cur = s[left];
            int right = left + 1;
            while(right < n && s[right] == cur)
                ++right;
            int len = right - left;
            if(len >= 3)
            {
                s.erase(left, len);
                flag = true;
                break;
            }
            else
                left = right;
        }
        if(flag)
            shrink(s);
    }
};

int main()
{
    Solution_3 solution;
    while(true)
    {
        string board, hand;
        cin >> board;
        cin >> hand;
        auto start = system_clock::now();
        cout << solution.findMinStep(board, hand) << endl;
        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << "花费了" << double(duration.count()) * microseconds::period::num / microseconds::period::den   << "秒" << endl;
    }
}
