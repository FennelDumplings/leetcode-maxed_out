// prob632: Smallest Range Covering Elements from K Lists

/*
 * You have k lists of sorted integers in ascending order. Find the smallest range that includes at least one number from each of the k lists.
 *
 * We define the range [a,b] is smaller than range [c,d] if b-a < d-c or a < c if b-a == d-c.
 */

/*
 * Example 1:
 * Input: [[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
 * Output: [20,24]
 * Explanation:
 * List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
 * List 2: [0, 9, 12, 20], 20 is in range [20,24].
 * List 3: [5, 18, 22, 30], 22 is in range [20,24].
 */

/*
 * Note:
 *
 * The given list may contain duplicates, so ascending order means >= here.
 * 1 <= k <= 3500
 * -105 <= value of elements <= 105.
 */

#include <vector>
#include <queue>
#include <functional>

using namespace std;

// Corner Case
struct Event
{
    int num;
    int id;
    Event(int num, int id):num(num),id(id){}
};

using PEI = pair<Event, int>;

struct Heap_Cmp
{
    bool operator()(const PEI& pei1, const PEI& pei2) const
    {
        return pei1.first.num > pei2.first.num; // 小顶堆
    }
};

struct Range
{
    int left, right;
    Range(int l, int r):left(l),right(r){}
};

bool operator<(const Range& r1, const Range& r2)
{
    if(r1.right - r1.left == r2.right - r2.left)
        return r1.left < r2.left;
    return r1.right - r1.left < r2.right - r2.left;
}

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int K = nums.size();
        priority_queue<PEI, vector<PEI>, Heap_Cmp> pq; // 存的是 Event
        for(int i = 0; i < K; ++i)
        {
            pq.push(PEI(Event(nums[i][0], i), 0));
        }
        vector<Event> events;
        while(!pq.empty())
        {
            PEI cur = pq.top();
            pq.pop();
            events.push_back(cur.first);
            if(cur.second + 1 < (int)nums[cur.first.id].size())
            {
                pq.push(PEI(Event(nums[cur.first.id][cur.second + 1], cur.first.id), cur.second + 1));
            }
        }
        int N = events.size();
        if(N == 1)
            return vector<int>(2, events[0].num);
        vector<int> cnt(K, 0);
        int left = 0;
        cnt[events[left].id] = 1;
        int color_cnt = 1;
        Range result(-1e5, 1e5 + 5);
        int right = left + 1;
        while(left < N && right < N)
        {
            while(right < N && events[left].id != events[right].id && color_cnt < K)
            {
                if(cnt[events[right].id] == 0)
                    ++color_cnt;
                ++cnt[events[right].id];
                ++right;
            }
            // right == N || cnt[events[left].id] > 1 || color_cnt == K
            if(color_cnt == K)
            {
                Range cur_range(events[left].num, events[right - 1].num);
                if(cur_range < result)
                    result = cur_range;
                --cnt[events[left].id];
                if(cnt[events[left].id] == 0)
                    --color_cnt;
                ++left;
            }
            while(left < right && ((right < N && events[left].id == events[right].id) || cnt[events[left].id] > 1))
            {
                --cnt[events[left].id];
                if(cnt[events[left].id] == 0)
                    --color_cnt;
                ++left;
            }
            // left == right || cnt[events[left].id] == 1
            if(left == right && left < N)
            {
                cnt[events[left].id] = 1;
                ++color_cnt;
                right = left + 1;
            }
        }
        return vector<int>({result.left, result.right});
    }
};
