// prob436: Find Right Intervals

/*
 * Given a set of intervals, for each of the interval i, check if there exists an interval j whose start point is bigger than or equal to the end point of the interval i, which can be called that j is on the "right" of i.
 * For any interval i, you need to store the minimum interval j's index, which means that the interval j has the minimum start point to build the "right" relationship for interval i. If the interval j doesn't exist, store -1 for the interval i. Finally, you need output the stored value of each interval as an array.
 * Note:
 * You may assume the interval's end point is always bigger than its start point.
 * You may assume none of these intervals have the same start point.
 */

/*
 * Example 1:
 * Input: [ [1,2]  ]
 * Output: [-1]
 * Explanation: There is only one interval in the collection, so it outputs -1.
 * Example 2:
 * Input: [ [3,4], [2,3], [1,2]  ]
 * Output: [-1, 0, 1]
 * Explanation: There is no satisfied "right" interval for [3,4].
 * For [2,3], the interval [3,4] has minimum-"right" start point;
 * For [1,2], the interval [2,3] has minimum-"right" start point.
 * Example 3:
 * Input: [ [1,4], [2,3], [3,4]  ]
 * Output: [-1, 2, -1]
 * Explanation: There is no satisfied "right" interval for [1,4] and [3,4].
 * For [2,3], the interval [3,4] has minimum-"right" start point.
 */

#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        map<int, int> mapping; // left -> id
        int n = intervals.size();
        for(int i = 0; i < n; ++i)
        {
            int left = intervals[i][0];
            mapping[left] = i;
        }
        vector<int> result(n, -2);
        for(int i = 0; i < n; ++i)
        {
            int right = intervals[i][1];
            // 从所有区间中找左端点大于等于 right 的最小的 left 对应的 id
            auto it = mapping.lower_bound(right);
            if(it == mapping.end())
                result[i] = -1;
            else
            {
                result[i] = it -> second;
            }
        }
        return result;
    }
};
