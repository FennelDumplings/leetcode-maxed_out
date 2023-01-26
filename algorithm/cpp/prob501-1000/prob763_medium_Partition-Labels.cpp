// prob763: Partition Labels

/*
 * A string S of lowercase English letters is given. We want to partition this string into as many parts as possible so that each letter appears in at most one part, and return a list of integers representing the size of these parts.
 */

/*
 * Example 1:
 *
 * Input: S = "ababcbacadefegdehijhklij"
 * Output: [9,7,8]
 * Explanation:
 * The partition is "ababcbaca", "defegde", "hijhklij".
 * This is a partition so that each letter appears in at most one part.
 * A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.
 */

/*
 * Note:
 *
 * S will have length in range [1, 500].
 * S will consist of lowercase English letters ('a' to 'z') only.
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Interval
{
    int start, end;
    Interval(int s, int e):start(s),end(e){}
};

struct Event
{
    int idx;
    bool side;
    Event(int idx, bool side):idx(idx),side(side){}
};

struct Cmp
{
    bool operator()(const Event& e1, const Event& e2) const
    {
        if(e1.idx == e2.idx)
            return e1.side < e2.side;
        return e1.idx < e2.idx;
    }
};

class Solution {
public:
    vector<int> partitionLabels(string S) {
        int n = S.size();
        vector<PII> info(26, PII(n, -1)); // 字母 -> 范围
        for(int i = 0; i < n; ++i)
        {
            char ch = S[i];
            if(info[ch - 'a'].first == n)
                info[ch - 'a'].first = i;
            info[ch - 'a'].second = i;
        }
        vector<Event> events;
        for(const PII& range: info)
        {
            if(range.first != n)
            {
                events.push_back(Event(range.first, false));
                events.push_back(Event(range.second, true));
            }
        }
        sort(events.begin(), events.end(), Cmp());
        vector<Interval> ranges = merge(events);
        vector<int> result;
        for(const Interval& i: ranges)
        {
            result.push_back(i.end - i.start + 1);
        }
        return result;
    }

private:
    using PII = pair<int, int>;

    vector<Interval> merge(const vector<Event>& events)
    {
        int n = events.size();
        vector<Interval> result;
        int sum = 0;
        for(int i = 0; i < n; ++i)
        {
            const Event &e = events[i];
            if(sum == 0)
                result.push_back(Interval(e.idx, -1));
            if(!e.side)
                ++sum;
            else
                --sum;
            if(sum == 0)
                result.back().end = e.idx;
        }
        return result;
    }
};
