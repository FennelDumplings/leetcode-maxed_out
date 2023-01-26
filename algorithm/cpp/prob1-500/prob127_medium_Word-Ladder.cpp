// prob127: Word Ladder

/*
 * Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:
 * Only one letter can be changed at a time.
 * Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
 */

/*
 * Note:
 * Return 0 if there is no such transformation sequence.
 * All words have the same length.
 * All words contain only lowercase alphabetic characters.
 * You may assume no duplicates in the word list.
 * You may assume beginWord and endWord are non-empty and are not the same.
 */

/*
 * Example 1:
 * Input:
 * beginWord = "hit",
 * endWord = "cog",
 * wordList = ["hot","dot","dog","lot","log","cog"]
 * Output: 5
 * Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
 * return its length 5.
 * Example 2:
 * Input:
 * beginWord = "hit"
 * endWord = "cog"
 * wordList = ["hot","dot","dog","lot","log"]
 * Output: 0
 * Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
 */

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// 建图 再BFS最短路
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if(wordList.empty()) return 0;
        int n = wordList.size();

        vector<int> d; // 到起点的距离, 同时 -1 表示未被访问过
        vector<vector<int> > g; // 邻接表
        d.assign(n + 1, -1);
        g.assign(n + 1, vector<int>());
        int ed = -1; // 终点, 可能取不到

        // 建图过程
        for(int i = 0; i < n; ++i)
        {
            for(int j = i + 1; j < n; ++j)
            {
                if(_check(wordList[i], wordList[j]))
                {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
            }
            if(_check(wordList[i], beginWord))
            {
                g[n].push_back(i); // n 是起点
                g[i].push_back(n);
            }
            if(wordList[i] == endWord)
                ed = i;
        }

        // BFS
        queue<int> q;
        q.push(n); // 起点
        d[n] = 0; // 与起点的距离
        while(!q.empty())
        {
            int u = q.front(); // 当前点
            q.pop();
            for(int v: g[u]) // 下一点
            {
                if(d[v] == -1) // 未访问过
                {
                    q.push(v);
                    d[v] = d[u] + 1;
                    if(v == ed)
                        return d[v] + 1;
                }
            }
        }
        return 0;
    }

private:
    bool _check(string& s1, string& s2)
    {
        int cnt = 0;
        for(int i = 0; i < (int)s1.size(); ++i)
            if(s1[i] != s2[i])
                ++cnt;
        return cnt == 1;
    }
};

// 不建图，直接通过每步的可行状态 BFS
class Solution_2 {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if(wordList.empty()) return 0;
        int n = wordList.size();

        vector<int> d; // 到起点的距离
        d.assign(n + 1, -1);
        d[n] = 1;

        wordList.push_back(beginWord);

        // BFS
        queue<int> q;
        q.push(n); // 起点
        while(!q.empty())
        {
            int u = q.front(); // 当前点
            q.pop();
            for(int v = 0; v < n; ++v) // 下一点
            {
                if(d[v] == -1) // 未访问过
                {
                    if(_check(wordList[u], wordList[v]))
                    {
                        if(wordList[v] == endWord)
                            return d[u] + 1;
                        d[v] = d[u] + 1;
                        q.push(v);
                    }
                }
            }
        }
        return 0;
    }

private:
    bool _check(string& s1, string& s2)
    {
        int cnt = 0;
        for(int i = 0; i < (int)s1.size(); ++i)
            if(s1[i] != s2[i])
                ++cnt;
        return cnt == 1;
    }
};


// 不建图，直接通过每步的可行状态 BFS
// 双向 BFS
class Solution_3 {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if(wordList.empty()) return 0;
        int n = wordList.size();

        vector<int> d; // 到起点的距离
        d.assign(n + 1, 0); // 双向BFS, 节点染色，<0 和 >0 是两种颜色

        wordList.push_back(beginWord);

        // BFS
        queue<int> q;
        d[n] = 1;
        q.push(n); // 起点

        // 双向 BFS -- 赵到终点进队
        // 若没有点进队，则连接不到终点，退化成单向BFS
        for(int i = 0; i < n; ++i)
        {
            if(wordList[i] == endWord)
            {
                d[i] = -1; // 给终点染色
                q.push(i);
                break;
            }
        }

        while(!q.empty())
        {
            int u = q.front(); // 当前点
            q.pop();
            for(int v = 0; v <= n; ++v) // 下一点
            {
                if(_check(wordList[u], wordList[v]))
                {
                    if(d[v] == 0) // 未访问过
                    {
                        d[v] = (d[u] > 0 ? d[u] + 1 : d[u] - 1);
                        q.push(v);
                    }
                    else
                    {
                        if((d[u] ^ d[v]) < 0) // 异号，颜色不同
                            return abs(d[u]) + abs(d[v]);
                    }
                }
            }
        }
        return 0;
    }

private:
    bool _check(string& s1, string& s2)
    {
        int cnt = 0;
        for(int i = 0; i < (int)s1.size(); ++i)
            if(s1[i] != s2[i])
                ++cnt;
        return cnt == 1;
    }
};

// 另一思路：枚举边找点
class Solution_4 {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if(wordList.empty()) return 0;
        int n = wordList.size();
        int l = beginWord.size();
        unordered_map<string, int> id;
        wordList.push_back(beginWord);

        int ed = -1;
        for(int i = 0; i <=n; ++i)
        {
            id[wordList[i]] = i;
            if(wordList[i] == endWord)
                ed = i;
        }
        if(ed == -1) return 0;

        vector<int> d(n + 1, 0);
        queue<int> q;
        d[n] = 1;
        q.push(n);
        d[ed] = -1;
        q.push(ed);
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            string cur = wordList[u];
            for(int i = 0; i < l; ++i)
            {
                char nc = cur[i];
                for(char c = 'a'; c <= 'z'; ++c)
                {
                    if(c == nc) continue;
                    cur[i] = c;
                    if(id.count(cur)) // 枚举边找点
                    {
                        int v = id[cur];
                        if(d[v])
                        {
                            if((d[u] ^ d[v]) < 0)
                                return abs(d[u]) + abs(d[v]);
                        }
                        else
                        {
                            d[v] = (d[u] > 0 ? d[u] + 1 : d[u] - 1);
                            q.push(v);
                        }
                    }
                }
                cur[i] = nc;
            }
        }
        return 0;
    }
};
