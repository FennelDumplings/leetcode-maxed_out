// prob347: Top K Frequent Elements

/*
 * Given a non-empty array of integers, return the k most frequent elements.
 */

/*
 * Example 1:
 * Input: nums = [1,1,1,2,2,3], k = 2
 * Output: [1,2]
 * Example 2:
 * Input: nums = [1], k = 1
 * Output: [1]
 */

/*
 * Note:
 * You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
 * Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
 */

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>

using namespace std;

// 有 （cnt, num) 的 vec 之后，排序
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> mapping; // num -> cnt
        for(int num: nums)
            ++mapping[num];
        using PII = pair<int, int>;
        vector<PII> cnt_num;
        for(auto it = mapping.begin(); it != mapping.end(); ++it)
            cnt_num.push_back(PII(it -> second, it -> first));
        sort(cnt_num.begin(), cnt_num.end(), greater<PII>());
        vector<int> result(k, -1);
        for(int i = 0; i < k; ++i)
            result[i] = cnt_num[i].second;
        return result;
    }
};


// 有 （cnt, num) 的 vec 之后，自定义< 用堆
class Solution_2 {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> mapping; // num -> cnt
        for(int num: nums)
            ++mapping[num];
        using PII = pair<int, int>;
        vector<PII> cnt_num;
        for(auto it = mapping.begin(); it != mapping.end(); ++it)
            cnt_num.push_back(PII(it -> second, it -> first));
        priority_queue<PII, vector<PII>, greater<PII> > pq;
        for(int i = 0; i < k; ++i)
            pq.push(cnt_num[i]);
        for(int i = k; i < (int)cnt_num.size(); ++i)
        {
            if(pq.top().first < cnt_num[i].first)
            {
                pq.pop();
                pq.push(cnt_num[i]);
            }
        }
        vector<int> result;
        while(!pq.empty())
        {
            result.push_back(pq.top().second);
            pq.pop();
        }
        return result;
    }
};

// 有 （cnt, num) 的 vec 之后，用快排 partition
class Solution_3 {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> mapping; // num -> cnt
        for(int num: nums)
            ++mapping[num];
        using PII = pair<int, int>;
        vector<PII> cnt_num;
        for(auto it = mapping.begin(); it != mapping.end(); ++it)
            cnt_num.push_back(PII(it -> second, it -> first));

        int left = 0;
        int right = cnt_num.size() - 1;
        int index = partition(cnt_num, left, right);
        while(index != k - 1)
        {
            if(index > k - 1)
                right = index - 1;
            else
                left = index + 1;
            index = partition(cnt_num, left, right);
        }

        vector<int> res(k);
        for(int i = 0; i < k; i++)
            res[i] = cnt_num[i].second;
        return res;
    }

private:
    int partition(vector<pair<int, int> >& data, int left, int right){
        int randIdx = rand() % (right - left + 1) + left; // 随机选择 pivot
        swap(data[randIdx], data[right]);
        int pivot = data[right].first;
        int index = left;
        for(int i = left; i <= right - 1; i++)
        {
            if(data[i].first > pivot)
            {
                if(index != i) swap(data[index], data[i]);
                index++;
            }
        }
        swap(data[index], data[right]);
        return index;
    }
};

// 桶排序
class Solution_4 {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> mapping; // num -> cnt
        for(int num: nums)
            ++mapping[num];
        int n = nums.size();
        vector<vector<int> > buckets(n + 1, vector<int>());
        for(auto it = mapping.begin(); it != mapping.end(); ++it)
            buckets[it -> second].push_back(it -> first);
        vector<int> result;
        for(int i = n; i >= 1 && k > 0; --i)
        {
            int cur_cnt = buckets[i].size();
            if(cur_cnt > 0)
                result.insert(result.end(), buckets[i].begin(), buckets[i].end());
            k -= cur_cnt;
        }
        return result;
    }
};
