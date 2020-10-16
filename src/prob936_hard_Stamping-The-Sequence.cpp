// prob936: Stamping The Sequence

/*
 * https://leetcode-cn.com/problems/stamping-the-sequence/
 */

#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;


// 主串含通配符的话，如何改 KMP
class Solution_2 {
public:
    vector<int> movesToStamp(string stamp, string target) {
        int n = target.size();
        int m = stamp.size();
        if(m > n)
            return {};
        mpnext = get_kmp_next(stamp);
        vector<int> path;
        dfs(target, stamp, path);
        reverse(path.begin(), path.end());
        return path;
    }

private:
    bool dfs(string& board, const string& stamp, vector<int>& path)
    {
        int n = board.size();
        bool getit = true;
        // 终点判断 O(N)
        for(const char &ch: board)
            if(ch != '?')
            {
                getit = false;
                break;
            }
        if(getit)
            return true;
        if((int)path.size() == n * 10)
            return false;
        // 找所有匹配的位置，? 可以匹配任何字符 O(N)
        vector<int> next_idxs = kmp_match(board, stamp, mpnext);
        int m = stamp.size();
        for(int idx: next_idxs)
        {
            string nxt_s = board;
            bool all_question_mark = true;
            for(int i = 0; i < m; ++i)
            {
                if(nxt_s[idx + i] != '?')
                {
                    all_question_mark = false;
                    nxt_s[idx + i] = '?';
                }
            }
            if(!all_question_mark)
            {
                path.push_back(idx);
                if(dfs(nxt_s, stamp, path))
                    return true;
                path.pop_back();
            }
        }
        return false;
    }

    vector<int> mpnext;

    vector<int> kmp_match(const string& s, const string& p, const vector<int>& kmpnext)
    {
        int n = s.size(), m = p.size();
        vector<int> result;
        for(int i = 0, j = 0; i < n; ++i)
        {
            while(j > -1 && s[i] != p[j] && s[i] != '?') // && s[i] != '?' 是新加的
                j = kmpnext[j];
            ++j;
            if(j == m)
            {
                result.push_back(i - m + 1);
                j = kmpnext[j];
            }
        }
        return result;
    }

    vector<int> get_kmp_next(const string& p)
    {
        int m = p.size();
        vector<int> kmpnext(m + 1, -1);
        for(int i = 0, j = -1; i < m; ++i)
        {
            while(j > -1 && p[i] != p[j])
                j = kmpnext[j];
            // j == -1 或 p[i] == p[j]
            ++j;
            if(p[i + 1] == p[j])
                kmpnext[i + 1] = kmpnext[j];
            else
                kmpnext[i + 1] = j;
        }
        return kmpnext;
    }
};


class Solution {
public:
    vector<int> movesToStamp(string stamp, string target) {
        int n = target.size();
        int m = stamp.size();
        if(m > n)
            return {};
        vector<int> path;
        if(!dfs(target, stamp, path))
            return {};
        reverse(path.begin(), path.end());
        return path;
    }

private:
    bool dfs(string& board, const string& stamp, vector<int>& path)
    {
        int n = board.size();
        bool getit = true;
        // 终点判断 O(N)
        for(const char &ch: board)
            if(ch != '?')
            {
                getit = false;
                break;
            }
        if(getit)
            return true;
        if((int)path.size() == n * 10)
            return false;
        // 找到 board 中不全是 ? 的与 target 匹配的位置
        int idx = match(board, stamp);
        if(idx == -1)
            return false;
        int m = stamp.size();
        for(int offset = 0; offset < m; ++offset)
            board[idx + offset] = '?';
        path.push_back(idx);
        if(dfs(board, stamp, path))
            return true;
        return false;
    }

    int match(const string& board, const string& pattern)
    {
        int n = board.size();
        int m = pattern.size();
        for(int i = 0; i <= n - m; ++i)
        {
            bool all_question_mark = true;
            bool is_match = true;
            for(int offset = 0; offset < m; ++offset)
            {
                if(board[i + offset] != pattern[offset] && board[i + offset] != '?')
                {
                    is_match = false;
                    break;
                }
                if(board[i + offset] != '?')
                    all_question_mark = false;
            }
            if(is_match && !all_question_mark)
                return i;
        }
        return -1;
    }
};
