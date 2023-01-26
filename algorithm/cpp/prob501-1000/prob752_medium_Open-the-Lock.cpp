// prob725: Open the Lock

/*
 * You have a lock in front of you with 4 circular wheels. Each wheel has 10
 * slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. The wheels can rotate freely and wrap around:
 * for example we can turn '9' to be '0', or '0' to be '9'. Each move consists of turning one wheel one slot.
 * The lock initially starts at '0000', a string representing the state of the 4 wheels.
 * You are given a list of deadends dead ends, meaning if the lock displays any of these codes, the wheels of
 * the lock will stop turning and you will be unable to open it.
 * Given a target representing the value of the wheels that will unlock the lock,
 * return the minimum total number of turns required to open the lock, or -1 if it is impossible.
 */

/*
 * Example 1:
 * Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
 * Output: 6
 * Explanation:
 * A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
 * Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
 * because the wheels of the lock become stuck after the display becomes the dead end "0102".
 * Example 2:
 * Input: deadends = ["8888"], target = "0009"
 * Output: 1
 * Explanation:
 * We can turn the last wheel in reverse to move from "0000" -> "0009".
 * Example 3:
 * Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
 * Output: -1
 * Explanation:
 * We can't reach the target without getting stuck.
 * Example 4:
 * Input: deadends = ["0000"], target = "8888"
 * Output: -1
 */

/*
 * Note:
 * The length of deadends will be in the range [1, 500].
 * target will not be in the list deadends.
 * Every string in deadends and the string target will be a string of 4 digits from the 10,000 possibilities '0000' to '9999'.
 */

#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <unordered_set>
#include <cmath>

using namespace std;

// 建图+bfs
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<int> setting;
        for(const string& num_str: deadends)
        {
            int num;
            stringstream ss;
            ss << num_str;
            ss >> num;
            setting.insert(num);
        }
        int start = 0;
        int end;
        stringstream ss;
        ss << target;
        ss >> end;
        const int n = 10000;
        vector<vector<int> > g(n);
        for(int i = 0; i < n; ++i)
        {
            // 对一个数字 from，相邻的数字有 8 种
            int from = i;
            if(setting.find(from) != setting.end())
                continue;
            for(int to: _get_next(i))
            {
                if(setting.find(to) != setting.end())
                    continue;
                g[from].push_back(to);
            }
        }
        return bfs(g, start, end);
    }

private:
    vector<int> _get_next(int num)
    {
        // num 为 4 位数
        vector<int> result;
        int iter = num;
        for(int i = 0; i < 4; ++i)
        {
            int digit = iter % 10;
            iter /= 10;
            int new_num = num - digit * pow(10, i);
            int new_digit1 = (digit - 1 + 10) % 10;
            int new_digit2 = (digit + 1 + 10) % 10;
            result.push_back(new_num + new_digit1 * pow(10, i));
            result.push_back(new_num + new_digit2 * pow(10, i));
        }
        return result;
    }

    int bfs(const vector<vector<int> >& g, int start, int end)
    {
        int n = g.size();
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        int d = 0;
        vector<int> level_nodes;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            ++d;
            for(int node: level_nodes)
            {
                for(int son: g[node])
                {
                    if(son == end)
                        return d;
                    if(visited[son]) continue;
                    visited[son] = true;
                    q.push(son);
                }
            }
        }
        return -1;
    }
};

// 不建图 + BFS
class Solution_2 {
public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<int> setting;
        for(const string& num_str: deadends)
        {
            int num;
            stringstream ss;
            ss << num_str;
            ss >> num;
            setting.insert(num);
        }
        int start = 0;
        int end;
        stringstream ss;
        ss << target;
        ss >> end;
        return bfs(start, end, setting);
    }

private:
    const int N = 10000;

    vector<int> _get_next(int num)
    {
        // num 为 4 位数
        vector<int> result;
        int iter = num;
        for(int i = 0; i < 4; ++i)
        {
            int digit = iter % 10;
            iter /= 10;
            int new_num = num - digit * pow(10, i);
            int new_digit1 = (digit - 1 + 10) % 10;
            int new_digit2 = (digit + 1 + 10) % 10;
            result.push_back(new_num + new_digit1 * pow(10, i));
            result.push_back(new_num + new_digit2 * pow(10, i));
        }
        return result;
    }

    int bfs(int start, int end, const unordered_set<int>& setting)
    {
        if(setting.find(start) != setting.end()) return -1;
        vector<bool> visited(N, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        int d = 0;
        vector<int> level_nodes;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            ++d;
            for(int node: level_nodes)
            {
                for(int son: _get_next(node))
                {
                    if(son == end)
                        return d;
                    if(setting.find(son) != setting.end()) continue;
                    if(visited[son]) continue;
                    visited[son] = true;
                    q.push(son);
                }
            }
        }
        return -1;
    }
};


// 双向BFS
class Solution_3 {
public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<int> setting;
        for(const string& num_str: deadends)
        {
            int num;
            stringstream ss;
            ss << num_str;
            ss >> num;
            setting.insert(num);
        }
        int start = 0;
        int end;
        stringstream ss;
        ss << target;
        ss >> end;
        return bfs(start, end, setting);
    }

private:
    const int N = 10000;

    vector<int> _get_next(int num)
    {
        // num 为 4 位数
        vector<int> result;
        int iter = num;
        for(int i = 0; i < 4; ++i)
        {
            int digit = iter % 10;
            iter /= 10;
            int new_num = num - digit * pow(10, i);
            int new_digit1 = (digit - 1 + 10) % 10;
            int new_digit2 = (digit + 1 + 10) % 10;
            result.push_back(new_num + new_digit1 * pow(10, i));
            result.push_back(new_num + new_digit2 * pow(10, i));
        }
        return result;
    }

    int bfs(int start, int end, const unordered_set<int>& setting)
    {
        if(setting.find(start) != setting.end()) return -1;
        queue<int> q1;
        q1.push(start);
        queue<int> q2;
        q2.push(end);
        vector<int> visited(N, 0);
        visited[start] = 1;
        visited[end] = -1;
        int d = 0;
        vector<int> level_nodes;
        while(!q1.empty() && !q2.empty())
        {
            level_nodes.clear();
            while(!q1.empty())
            {
                level_nodes.push_back(q1.front());
                q1.pop();
            }
            ++d;
            for(int node: level_nodes)
            {
                for(int son: _get_next(node))
                {
                    if(setting.find(son) != setting.end()) continue;
                    if(visited[son] == 1) continue;
                    if(visited[son] == -1)
                        return d;
                    visited[son] = 1;
                    q1.push(son);
                }
            }
            level_nodes.clear();
            while(!q2.empty())
            {
                level_nodes.push_back(q2.front());
                q2.pop();
            }
            ++d;
            for(int node: level_nodes)
            {
                for(int son: _get_next(node))
                {
                    if(setting.find(son) != setting.end()) continue;
                    if(visited[son] == -1) continue;
                    if(visited[son] == 1)
                        return d;
                    visited[son] = -1;
                    q2.push(son);
                }
            }
        }
        return -1;
    }
};
