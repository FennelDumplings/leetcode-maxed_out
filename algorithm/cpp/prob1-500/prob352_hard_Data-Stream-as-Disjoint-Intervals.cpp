// prob352: Data Stream as Disjoint Intervals

/*
 * Given a data stream input of non-negative integers a1, a2, ..., an, ..., summarize the numbers seen so far as a list of disjoint intervals.
 *
 * For example, suppose the integers from the data stream are 1, 3, 7, 2, 6, ..., then the summary will be:
 * [1, 1]
 * [1, 1], [3, 3]
 * [1, 1], [3, 3], [7, 7]
 * [1, 3], [7, 7]
 * [1, 3], [6, 7]
 */

/*
 * Follow up:
 * What if there are lots of merges and the number of disjoint intervals are small compared to the data stream's size?
 */

#include <vector>
#include <map>

using namespace std;

class SummaryRanges {
public:
    /** Initialize your data structure here. */
    SummaryRanges() {
        ranges = map<int, int>();
    }

    void addNum(int val) {
        if(ranges.empty())
        {
            ranges[val] = val;
            return;
        }
        auto it = ranges.lower_bound(val);
        if(it == ranges.end())
        {
            int a = (--it) -> second;
            if(val == a + 1)
            {
                it -> second  = val;
                return;
            }
            else if(val > a + 1)
                ranges[val] = val;
            return;
        }
        else if(it == ranges.begin())
        {
            int b = it -> first;
            if(val + 1 == b)
            {
                int tmp = ranges[b];
                ranges.erase(it);
                ranges[val] = tmp;
            }
            else if(val + 1 < b)
            {
                ranges[val] = val;
            }
            return;
        }
        else
        {
            int b = it -> first;
            int a = (--it) -> second;
            if(val == a + 1 && val + 1 == b)
            {
                it -> second = ranges[b];
                ranges.erase(++it);
                return;
            }
            if(val == a + 1)
            {
                it -> second = val;
                return;
            }
            if(val + 1 == b)
            {
                int tmp = ranges[b];
                ranges.erase(++it);
                ranges[val] = tmp;
                return;
            }
            if(a + 1 < val && val + 1 < b)
                ranges[val] = val;
        }
    }

    vector<vector<int>> getIntervals() {
        vector<vector<int> > result;
        for(const PII& range: ranges)
        {
            result.push_back({range.first, range.second});
        }
        return result;
    }

private:
    using PII = pair<int, int>;
    map<int, int> ranges;
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(val);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */
