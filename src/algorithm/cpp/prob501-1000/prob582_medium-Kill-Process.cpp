// prob582: Kill Process

/*
 * Given n processes, each process has a unique PID (process id) and its PPID (parent process id).
 * Each process only has one parent process, but may have one or more children processes.
 * This is just like a tree structure. Only one process has PPID that is 0, which means this process has no
 * parent process. All the PIDs will be distinct positive integers.
 * We use two list of integers to represent a list of processes, where the first list contains PID for each
 * process and the second list contains the corresponding PPID.
 * Now given the two lists, and a PID representing a process you want to kill, return a list of PIDs of
 * processes that will be killed in the end. You should assume that when a process is killed, all its children
 * processes will be killed. No order is required for the final answer.
 */

/*
 * Example 1:
 * Input:
 * pid =  [1, 3, 10, 5]
 * ppid = [3, 0, 5, 3]
 * kill = 5
 * Output: [5,10]
 * Explanation:
 *            3
 *          /   \
 *         1     5
 *              /
 *             10
 * Kill 5 will also kill 10.
 */

/*
 * Note:
 * The given kill id is guaranteed to be one of the given PIDs.
 * n >= 1.
 */

#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        int n = pid.size();
        if(n == 1) return vector<int>({kill});
        unordered_map<int, vector<int> > mapping;
        for(int i = 0; i < n; ++i)
            mapping[ppid[i]].push_back(pid[i]);
        queue<int> q;
        q.push(kill);
        vector<int> result;
        vector<int> level_nodes;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                int cur = q.front();
                q.pop();
                level_nodes.push_back(cur);
                result.push_back(cur);
            }
            for(int node: level_nodes)
                for(int son: mapping[node])
                    q.push(son);
        }
        return result;
    }
};
