// prob1353: Maximum Number of Events That Can Be Attended

/*
 * Given an array of events where events[i] = [startDayi, endDayi]. Every event i starts at startDayi and ends at endDayi.
 * You can attend an event i at any day d where startTimei <= d <= endTimei. Notice that you can only attend one event at any time d.
 * Return the maximum number of events you can attend.
 */

/*
 * Example 1:
 * Input: events = [[1,2],[2,3],[3,4]]
 * Output: 3
 * Explanation: You can attend all the three events.
 * One way to attend them all is as shown.
 * Attend the first event on day 1.
 * Attend the second event on day 2.
 * Attend the third event on day 3.
 * Example 2:
 * Input: events= [[1,2],[2,3],[3,4],[1,2]]
 * Output: 4
 * Example 3:
 * Input: events = [[1,4],[4,4],[2,2],[3,4],[1,1]]
 * Output: 4
 * Example 4:
 * Input: events = [[1,100000]]
 * Output: 1
 * Example 5:
 * Input: events = [[1,1],[1,2],[1,3],[1,4],[1,5],[1,6],[1,7]]
 * Output: 7
 */

/*
 * Constraints:
 * 1 <= events.length <= 10^5
 * events[i].length == 2
 * 1 <= events[i][0] <= events[i][1] <= 10^5
 */

#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <queue>
#include <functional>
#include <climits>

using namespace std;

// 枚举所有可能的左端点
class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        int n = events.size();
        // map<int, vector<int>> ranges; // 左端点 -> 右端点列表
        vector<vector<int>> ranges(1e5 + 1); // 左端点 -> 右端点列表
        priority_queue<int, vector<int>, greater<int>> pq;
        for(const vector<int>& range: events)
            ranges[range[0]].push_back(range[1]);
        int result = n;
        for(int i = 1; i <= 1e5; ++i)
        {
            for(int right: ranges[i])
                pq.push(right);
            while(!pq.empty() && pq.top() < i)
            {
                pq.pop();
                --result;
            }
            if(!pq.empty())
                pq.pop();
        }
        return result;
    }
};

//----------------------------------------------

// 平衡树
// TLE
struct Range
{
    int left;
    int right;
    Range(int l, int r):left(l),right(r){}
};

struct Cmp
{
    bool operator()(const Range& r1, const Range& r2) const
    {
        if(r1.left == r2.left)
            return r1.right < r2.right;
        return r1.left < r2.left;
    }
};

class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        multiset<Range, Cmp> ranges;
        for(const vector<int>& range: events)
            ranges.insert(Range(range[0], range[1]));

        auto it = ranges.begin();
        int line = it -> left;
        while(it != ranges.end())
        {
            line = it -> left + 1;
            // 此时应该把 it 之后所有的 [left, right] 中 left < line 的都置为 line
            // 也即所有 left 等于当前 it -> left 的区间(it 之后的连续若干个), 把它们的 left + 1
            auto iter = it;
            ++iter;
            while(iter != ranges.end() && iter -> left < line)
            {
                int r = iter -> right;
                iter = ranges.erase(iter);
                if(line <= r)
                    ranges.insert(Range(line, r));
            }
            ++it;
        }
        return ranges.size();
    }
};

