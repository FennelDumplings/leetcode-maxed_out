// prob1606: Find Servers That Handled Most Number of Requests

/*
 * https://leetcode-cn.com/problems/find-servers-that-handled-most-number-of-requests/
 */

#include <vector>
#include <map>
#include <set>

using namespace std;

class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        set<int> free; // 空闲 id
        for(int i = 0; i < k; ++i)
            free.insert(i);
        map<int, vector<int>> busy; // 结束时间 -> ids
        int n = arrival.size();
        vector<int> requests(k);
        int max_cnt = 0;
        for(int i = 0; i < n; ++i)
        {
            int s = arrival[i];
            auto it_busy = busy.begin();
            while(it_busy != busy.end())
            {
                int end_time = it_busy -> first;
                if(end_time <= s)
                {
                    vector<int> ids = it_busy -> second;
                    for(int id: ids)
                        free.insert(id);
                    it_busy = busy.erase(it_busy);
                }
                else
                    break;
            }
            if(free.empty())
                continue;
            int target = i % k;
            auto it_free = free.lower_bound(target);
            if(it_free == free.end())
                it_free = free.begin();
            int id = *it_free;
            busy[s + load[i]].push_back(id);
            ++requests[id];
            max_cnt = max(max_cnt, requests[id]);
            free.erase(it_free);
        }
        vector<int> result;
        for(int i = 0; i < k; ++i)
            if(requests[i] == max_cnt)
                result.push_back(i);
        return result;
    }
};
