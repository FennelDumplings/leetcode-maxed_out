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
        int ed = -1; // 终点

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

