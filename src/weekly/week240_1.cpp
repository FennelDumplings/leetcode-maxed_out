#include <vector>
#include <algorithm>

using namespace std;

struct Event
{
    int kind; // -1: 死亡, 1: 出生
    int year;
    Event(int kind, int y):kind(kind), year(y){}
    bool operator<(const Event& e) const
    {
        if(year == e.year)
            return kind < e.kind;
        return year < e.year;
    }
};

class Solution {
public:
    int maximumPopulation(vector<vector<int>>& logs) {
        vector<Event> events;
        for(const vector<int> &log: logs)
        {
            events.emplace_back(1, log[0]);
            events.emplace_back(-1, log[1]);
        }
        sort(events.begin(), events.end());
        int ans = 0;
        int max_sum = 0;
        int sum = 0;
        for(const Event &e: events)
        {
            sum += e.kind;
            if(sum > max_sum)
            {
                max_sum = sum;
                ans = e.year;
            }
        }
        return ans;
    }
};
