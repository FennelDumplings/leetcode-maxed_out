// prob131: Palindrome Partitioning

/*
 * Given a string s, partition s such that every substring of the partition is a palindrome.
 * Return all possible palindrome partitioning of s.
 */

/*
 * Example:
 * Input: "aab"
 * Output:
 * [
 *   ["aa","b"],
 *   ["a","a","b"]
 * ]
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        if(s.empty()) return vector<vector<string> >();
        int n = s.size();
        if(n == 1) return vector<vector<string>>{{s}};
        vector<vector<vector<vector<string> > > > dp(n, vector<vector<vector<string> > >(n, vector<vector<string> >()));
        vector<vector<int> > is_palindrome(n, vector<int>(n, 0));
        vector<vector<string> > result = _solve(s, 0, n - 1, dp, is_palindrome);
        return result;
    }

private:
    vector<vector<string> > _solve(const string& s, int left, int right, vector<vector<vector<vector<string> > > >& dp,
            vector<vector<int> >& is_palindrome)
    {
        if(left > right)
        {
            return {{}};
        }

        if(!dp[left][right].empty())
        {
            return dp[left][right];
        }

        if(left == right)
        {
            dp[left][right] = {{string(1, s[left])}};
            return dp[left][right];
        }

        for(int i = left; i <= right; ++i)
        {
            if(!_check(s, left, i, is_palindrome)) continue;
            vector<string> item_left = vector<string>{s.substr(left, i - left + 1)};
            vector<vector<string> > items_right = _solve(s, i + 1, right, dp, is_palindrome);
            if(items_right.empty())
            {
                dp[left][right] = {item_left};
                continue;
            }
            for(const vector<string>& item_right: items_right)
            {
                vector<string> item(item_left);
                item.insert(item.end(), item_right.begin(), item_right.end());
                dp[left][right].push_back(item);
            }
        }
        return dp[left][right];
    }

    bool _check(const string& s, int left, int right, vector<vector<int> >& is_palindrome)
    {
        if(is_palindrome[left][right] != 0)
            return is_palindrome[left][right] == 1;
        while(left < right)
        {
            if(s[left] == s[right])
            {
                ++left;
                --right;
            }
            else
            {
                is_palindrome[left][right] = -1;
                return false;
            }
        }
        is_palindrome[left][right] = 1;
        return true;
    }
};


class Solution_2 {
public:
    vector<vector<string>> partition(string s) {
        if(s.empty()) return vector<vector<string> >();
        int n = s.size();
        if(n == 1) return vector<vector<string>>{{s}};
        vector<vector<int> > is_palindrome(n, vector<int>(n, 0)); // dp
        vector<vector<string> > result;
        vector<string> path;
        dfs(s, 0, n - 1, is_palindrome, path, result);
        return result;
    }

private:
    void dfs(const string& s, int left, int right, vector<vector<int> >& is_palindrome,
            vector<string>& path, vector<vector<string> >& result)
    {
        if(left > right)
        {
            result.push_back(path);
            return;
        }

        for(int i = left; i <= right; ++i)
        {
            if(!_check(s, left, i, is_palindrome)) continue;
            path.push_back(s.substr(left, i - left + 1));
            dfs(s, i + 1, right, is_palindrome, path, result);
            path.pop_back();
        }
    }

    bool _check(const string& s, int left, int right, vector<vector<int> >& is_palindrome)
    {
        if(is_palindrome[left][right] != 0)
            return is_palindrome[left][right] == 1;
        while(left < right)
        {
            if(s[left] == s[right])
            {
                ++left;
                --right;
            }
            else
            {
                is_palindrome[left][right] = -1;
                return false;
            }
        }
        is_palindrome[left][right] = 1;
        return true;
    }
};
