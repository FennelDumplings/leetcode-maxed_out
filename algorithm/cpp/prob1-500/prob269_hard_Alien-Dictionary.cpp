// prob269: Alien Dictionary

/*
 * There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you.
 * You receive a list of non-empty words from the dictionary, where words are sorted lexicographically by the rules of this new language.
 * Derive the order of letters in this language.
 */

/*
 * Example 1:
 * Input:
 * [
 *   "wrt",
 *   "wrf",
 *   "er",
 *   "ett",
 *   "rftt"
 * ]
 * Output: "wertf"
 * Example 2:
 * Input:
 * [
 *   "z",
 *   "x"
 * ]
 * Output: "zx"
 * Example 3:
 * Input:
 * [
 *   "z",
 *   "x",
 *   "z"
 * ]
 * Output: "" 
 * Explanation: The order is invalid, so return "".
 */

/*
 * Note:
 * You may assume all letters are in lowercase.
 * If the order is invalid, return an empty string.
 * There may be multiple valid order of letters, return any one of them is fine.
 */

#include <string>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    string alienOrder(vector<string>& words) {
        if(words.empty()) return "";
        int n = words.size();
        if(n == 1) return words[0];
        vector<vector<int> > g(26, vector<int>());
        vector<int> indegrees(26, -1);
        for(int i = 1; i < n; ++i)
            if(!_build_edge(g, indegrees, words[i - 1], words[i]))
                return "";
        queue<int> q;
        string result = "";
        int cnt = 0;
        for(int i = 0; i < 26; ++i)
        {
            if(indegrees[i] == 0)
                q.push(i);
            if(indegrees[i] >= 0)
                ++cnt;
        }
        while(!q.empty())
        {
            int cur = q.front();
            result += cur + 'a';
            q.pop();
            for(int son: g[cur])
            {
                --indegrees[son];
                if(indegrees[son] == 0)
                    q.push(son);
            }
        }
        if(cnt != (int)result.size()) return "";
        return result;
    }

private:
    bool _build_edge(vector<vector<int> >& g, vector<int>& indegrees, const string& s1, const string& s2)
    {
        // s1 < s2
        int n1 = s1.size(), n2 = s2.size();
        int i1 = 0, i2 = 0;
        // 出现不满足 s1[i1] == s2[i2] 有以下几种情况
        // i1 == n1 && i2 == n2 不建边直接返回 true
        // i1 < n1 && i2 == n2 返回 false
        // i1 == n1 && i2 < n2 更新 s2[i2] 入度为 -1 ,返回 true
        // i1 < n1 && i2 < n2 建边，更新入度
        while(i1 < n1 && i2 < n2 && s1[i1] == s2[i2])
        {
            if(indegrees[s1[i1] - 'a'] == -1)
                indegrees[s1[i1] - 'a'] = 0;
            ++i1, ++i2;
        }
        if(i1 == n1 && i2 == n2) return true;
        if(i1 < n1 && i2 == n2) return false;
        if(i1 == n1 && i2 < n2)
        {
            while(i2 < n2)
            {
                if(indegrees[s2[i2] - 'a'] == -1)
                    indegrees[s2[i2] - 'a'] = 0;
                ++i2;
            }
            return true;
        }
        g[s1[i1] - 'a'].push_back(s2[i2] - 'a');
        if(indegrees[s1[i1] - 'a'] == -1)
            indegrees[s1[i1] - 'a'] = 0;
        if(indegrees[s2[i2] - 'a'] == -1)
            indegrees[s2[i2] - 'a'] = 1;
        else
            ++indegrees[s2[i2] - 'a'];
        while(i1 < n1)
        {
            if(indegrees[s1[i1] - 'a'] == -1)
                indegrees[s1[i1] - 'a'] = 0;
            ++i1;
        }
        while(i2 < n2)
        {
            if(indegrees[s2[i2] - 'a'] == -1)
                indegrees[s2[i2] - 'a'] = 0;
            ++i2;
        }
        return true;
    }
};
