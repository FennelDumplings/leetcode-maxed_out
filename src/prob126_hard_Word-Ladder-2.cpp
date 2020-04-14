// prob126: Word Ladder II

/*
 * Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:
 * Only one letter can be changed at a time
 * Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
 * Note:
 * Return an empty list if there is no such transformation sequence.
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
 * Output:
 * [
 *   ["hit","hot","dot","dog","cog"],
 *     ["hit","hot","lot","log","cog"]
 *   ]
 * ]
 * Example 2:
 * Input:
 * beginWord = "hit"
 * endWord = "cog"
 * wordList = ["hot","dot","dog","lot","log"]
 * Output: []
 * Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
 */

#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// 建图单向
class Solution {
public:
    vector<vector<string> > findLadders(string beginWord, string endWord, vector<string>& wordList) {
        int ed = -1, s = -1;
        int n = wordList.size();
        for(int i = 0; i < n; ++i)
        {
            if(wordList[i] == endWord)
                ed = i;
            if(wordList[i] == beginWord)
                s = i;
        }
        if(ed == -1) return vector<vector<string> >();
        if(s == -1)
        {
            wordList.push_back(beginWord);
            s = n;
            ++n;
        }
        vector<int> colors(n, 0); // 0: 未选; 1: 属于起点; 2: 属于终点; 3: 临时标记
        queue<int> q1, q2;
        q1.push(s);
        colors[s] = 1;
        q2.push(ed);
        colors[ed] = 2;
        vector<int> level_nodes; // 当前层的节点
        vector<vector<int> > prev1(n), prev2(n); // 分别记录起点侧和终点侧各个点的前驱列表
        unordered_set<int> joints; // 记录关节点, 同一 level 的关节点都要记进来
        while(!q1.empty() && !q2.empty())
        {
            // 更新起点侧的下一个 level 的节点
            bfs_step(q1, level_nodes, colors, 1, joints, prev1, wordList);
            if(!joints.empty()) break;
            // 更新终点侧的下一个 level 的节点
            bfs_step(q2, level_nodes, colors, 2, joints, prev2, wordList);
            if(!joints.empty()) break;
        }
        if(joints.empty()) return vector<vector<string> >();
        vector<vector<int> > prefixs, postfixs;
        vector<int> path;
        vector<vector<string> > result;
        vector<string> item;
        for(int joint: joints)
        {
            prefixs.clear();
            postfixs.clear();
            path.push_back(joint);
            dfs(prev1, joint, prefixs, path, s);
            dfs(prev2, joint, postfixs, path, ed);
            path.pop_back();
            for(vector<int> &prefix: prefixs)
                for(vector<int> &postfix: postfixs)
                {
                    item.clear();
                    for(int i = (int)prefix.size() - 1; i >= 1; --i)
                        item.push_back(wordList[prefix[i]]);
                    for(int i: postfix)
                        item.push_back(wordList[i]);
                    result.push_back(item);
                }
        }
        return result;
    }

private:
    void dfs(const vector<vector<int> >& prev, int cur, vector<vector<int> >& paths, vector<int>& path, int e)
    {
        if(cur == e)
        {
            paths.push_back(path);
            return;
        }

        for(int son: prev[cur])
        {
            path.push_back(son);
            dfs(prev, son, paths, path, e);
            path.pop_back();
        }
    }

    void bfs_step(queue<int>& q, vector<int>& level_nodes, vector<int>& colors, int color,
            unordered_set<int>& joints, vector<vector<int> >& prev, const vector<string>& wordList)
    {
        int n = colors.size();
        level_nodes.clear();
        while(!q.empty())
        {
            level_nodes.push_back(q.front());
            q.pop();
        }
        for(int node: level_nodes)
        {
            for(int i = 0; i < n; ++i)
            {
                if(i == node || colors[i] == color) continue;
                if(_check(wordList[i], wordList[node]))
                {
                    if(colors[i] == 0)
                        q.push(i);
                    if(colors[i] != 0 && colors[i] != 3)
                        joints.insert(i);
                    colors[i] = 3;
                    prev[i].push_back(node);
                }
            }
        }
        for(int i = 0; i < n; ++i)
            if(colors[i] == 3)
                colors[i] = color;
    }

    bool _check(const string& s1, const string& s2)
    {
        int cnt = 0;
        for(int i = 0; i < (int)s1.size(); ++i)
            if(s1[i] != s2[i])
                ++cnt;
        return cnt == 1;
    }
};


// 枚举边找点
class Solution_2 {
public:
    vector<vector<string> > findLadders(string beginWord, string endWord, vector<string>& wordList) {
        int ed = -1, s = -1;
        int n = wordList.size();
        unordered_map<string, int> mapping;
        for(int i = 0; i < n; ++i)
        {
            if(wordList[i] == endWord)
                ed = i;
            if(wordList[i] == beginWord)
                s = i;
            mapping[wordList[i]] = i;
        }
        if(ed == -1) return vector<vector<string> >();
        if(s == -1)
        {
            wordList.push_back(beginWord);
            s = n;
            mapping[beginWord] = s;
            ++n;
        }
        vector<int> colors(n, 0); // 0: 未选; 1: 属于起点; 2: 属于终点; 3: 临时标记
        queue<int> q1, q2;
        q1.push(s);
        colors[s] = 1;
        q2.push(ed);
        colors[ed] = 2;
        vector<int> level_nodes; // 当前层的节点
        vector<vector<int> > prev1(n), prev2(n); // 分别记录起点侧和终点侧各个点的前驱列表
        unordered_set<int> joints; // 记录关节点, 同一 level 的关节点都要记进来
        while(!q1.empty() && !q2.empty())
        {
            // 更新起点侧的下一个 level 的节点
            bfs_step(q1, level_nodes, colors, 1, joints, prev1, wordList, mapping);
            if(!joints.empty()) break;
            // 更新终点侧的下一个 level 的节点
            bfs_step(q2, level_nodes, colors, 2, joints, prev2, wordList, mapping);
            if(!joints.empty()) break;
        }
        if(joints.empty()) return vector<vector<string> >();
        vector<vector<int> > prefixs, postfixs;
        vector<int> path;
        vector<vector<string> > result;
        vector<string> item;
        for(int joint: joints)
        {
            prefixs.clear();
            postfixs.clear();
            path.push_back(joint);
            dfs(prev1, joint, prefixs, path, s);
            dfs(prev2, joint, postfixs, path, ed);
            path.pop_back();
            for(vector<int> &prefix: prefixs)
                for(vector<int> &postfix: postfixs)
                {
                    item.clear();
                    for(int i = (int)prefix.size() - 1; i >= 1; --i)
                        item.push_back(wordList[prefix[i]]);
                    for(int i: postfix)
                        item.push_back(wordList[i]);
                    result.push_back(item);
                }
        }
        return result;
    }

private:
    void dfs(const vector<vector<int> >& prev, int cur, vector<vector<int> >& paths, vector<int>& path, int e)
    {
        if(cur == e)
        {
            paths.push_back(path);
            return;
        }

        for(int son: prev[cur])
        {
            path.push_back(son);
            dfs(prev, son, paths, path, e);
            path.pop_back();
        }
    }

    void bfs_step(queue<int>& q, vector<int>& level_nodes, vector<int>& colors, int color,
            unordered_set<int>& joints, vector<vector<int> >& prev, const vector<string>& wordList, const unordered_map<string, int>& mapping)
    {
        int L = wordList[0].size();
        int n = colors.size();
        level_nodes.clear();
        while(!q.empty())
        {
            level_nodes.push_back(q.front());
            q.pop();
        }
        for(int node: level_nodes)
        {
            string nxt = wordList[node];
            for(int pos = 0; pos < L; ++pos)
            {
                for(char c = 'a'; c <= 'z'; ++c)
                {
                    if(wordList[node][pos] == c) continue;
                    nxt[pos] = c;
                    auto it = mapping.find(nxt);
                    if(it != mapping.end())
                    {
                        int i = it -> second;
                        if(colors[i] != color)
                        {
                            if(colors[i] == 0)
                                q.push(i);
                            if(colors[i] != 0 && colors[i] != 3)
                                joints.insert(i);
                            colors[i] = 3;
                            prev[i].push_back(node);
                        }
                    }
                    nxt[pos] = wordList[node][pos];
                }
            }
        }
        for(int i = 0; i < n; ++i)
            if(colors[i] == 3)
                colors[i] = color;
    }
};
