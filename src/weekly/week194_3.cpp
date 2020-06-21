
#include <unordered_map>
#include <set>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size();
        unordered_map<int, set<int>> mapping;
        for(int i = 0; i < n; ++i)
        {
            if(rains[i] != 0)
                mapping[rains[i]].insert(i);
        }
        vector<int> result(n, -1);
        priority_queue<PII, vector<PII>, greater<PII>> pq;
        for(int i = 0; i < n; ++i)
        {
            if(rains[i] != 0)
            {
                int id = rains[i];
                if(!pq.empty() && pq.top().second == id)
                    return {};
                // 湖 id 下一次下雨是 t
                auto it = mapping[id].upper_bound(i);
                if(it != mapping[id].end())
                {
                    // t, id 入堆
                    // 堆中都是后续还会下雨的，堆头是最早的，如果 pq.top().t 到来是仍为出堆，则返回 []
                    pq.push(PII(*it, id));
                }
            }
            else
            {
                if(!pq.empty())
                {
                    result[i] = pq.top().second;
                    pq.pop();
                }
                else
                    result[i] = 1;
            }
        }
        return result;
    }

private:
    using PII = pair<int, int>;
};
