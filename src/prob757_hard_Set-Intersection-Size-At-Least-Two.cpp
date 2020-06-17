// prob757: Set Intersection Size At Least Two

/*
 * An integer interval [a, b] (for integers a < b) is a set of all consecutive integers from a to b, including a and b.
 * Find the minimum size of a set S such that for every integer interval A in intervals, the intersection of S with A has size at least 2.
 */

/*
 * Example 1:
 * Input: intervals = [[1, 3], [1, 4], [2, 5], [3, 5]]
 * Output: 3
 * Explanation:
 * Consider the set S = {2, 3, 4}.  For each interval, there are at least 2 elements from S in the interval.
 * Also, there isn't a smaller size set that fulfills the above condition.
 * Thus, we output the size of this set, which is 3.
 * Example 2:
 * Input: intervals = [[1, 2], [2, 3], [2, 4], [4, 5]]
 * Output: 5
 * Explanation:
 * An example of a minimum sized set is {1, 2, 3, 4, 5}.
 */

/*
 * Note:
 *
 * intervals will have length in range [1, 3000].
 * intervals[i] will have length 2, representing some integer interval.
 * intervals[i][j] will be an integer in [0, 10^8].
 */

#include <vector>
#include <set>

using namespace std;

struct Interval
{
    int l, r;
    Interval(int l, int r):l(l),r(r){}
};

struct Cmp
{
    bool operator()(const Interval& i1, const Interval& i2) const
    {
        if(i1.l == i2.l)
            return i1.r > i2.r;
        return i1.l < i2.l;
    }
};

class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        set<Interval, Cmp> intervals_set;
        for(const vector<int>& i: intervals)
        {
            intervals_set.insert(Interval(i[0], i[1]));
        }
        auto it = intervals_set.begin();
        int pre_right = -1;
        while(it != intervals_set.end())
        {
            int right = it -> r;
            if(right <= pre_right)
            {
                --it;
                it = intervals_set.erase(it);
                if(it == intervals_set.begin())
                    pre_right = -1;
                else
                {
                    --it;
                    pre_right = it -> r;
                    ++it;
                }
                continue;
            }
            else
            {
                pre_right = right;
                ++it;
            }
        }
        int result = 0;
        vector<int> setting;
        for(auto it = intervals_set.begin(); it != intervals_set.end(); ++it)
        {
            int r = it -> r, l = it -> l;
            if(result == 0 || setting[result - 1] < l)
            {
                auto iter = it;
                while(iter != intervals_set.end() && iter -> l < r)
                    ++iter;
                --iter;
                setting.push_back(iter -> l);
                setting.push_back(r);
                result += 2;
            }
            else if(result == 1 || setting[result - 2] < l)
            {
                setting.push_back(r);
                ++result;
            }
        }
        return result;
    }
};
