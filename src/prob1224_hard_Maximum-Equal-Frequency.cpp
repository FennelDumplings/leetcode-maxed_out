// prob1224: Maximum Equal Frequency

/*
 * https://leetcode-cn.com/problems/maximum-equal-frequency/
 */

#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class LFUCache {
public:
    LFUCache(int capacity) {
        cap = capacity;
        cnt_list.push_back({});
    }

    int get(int key) {
        auto it = mapping.find(key);
        if(it == mapping.end())
            return -1;
        int ans = (it -> second).first;
        list<PII>::iterator key_node = (it -> second).second;
        int cnt = key_node -> second;
        if((int)cnt_list.size() == cnt + 1)
            cnt_list.push_back({});
        list<PII> &new_key_list = cnt_list[cnt + 1];
        PII new_val = *key_node;
        ++new_val.second;
        cnt_list[cnt].erase(key_node);
        if(cnt_list[cnt].empty())
            active_bucket.erase(cnt);
        if(new_key_list.empty())
            active_bucket.insert(cnt + 1);
        new_key_list.insert(new_key_list.begin(), new_val);
        mapping[key].second = new_key_list.begin();
        return ans;
    }

    void put(int key, int value) {
        if(cap == 0) return;
        auto it = mapping.find(key);
        if(it != mapping.end())
        {
            mapping[key].first = value;
            get(key);
            return;
        }
        if(cnt_list.size() == 1)
            cnt_list.push_back({});
        if(cnt_list[1].empty())
            active_bucket.insert(1);
        cnt_list[1].insert(cnt_list[1].begin(), PII(key, 1));
        mapping[key] = PIL(value, cnt_list[1].begin());
    }

    bool check()
    {
        int c = active_bucket.size();
        if(c > 2)
            return false;
        if(c == 1)
        {
            int cnt = *active_bucket.begin();
            if(cnt == 1)
                return true;
            return cnt_list[cnt].size() == 1;
        }
        // c == 2
        vector<int> cnts(active_bucket.begin(), active_bucket.end());
        int min_cnt = min(cnts[0], cnts[1]);
        int max_cnt = max(cnts[0], cnts[1]);
        if(min_cnt == 1 && cnt_list[min_cnt].size() == 1)
            return true;
        if(max_cnt == min_cnt + 1 && cnt_list[max_cnt].size() == 1)
            return true;
        return false;
    }

private:
    using PII = pair<int, int>;
    using PIL = pair<int, list<PII>::iterator>;
    int cap;
    unordered_map<int, PIL> mapping;
    vector<list<PII>> cnt_list;
    unordered_set<int> active_bucket; // 有元素的桶
};

class Solution {
public:
    int maxEqualFreq(vector<int>& nums) {
        LFUCache lfu(5e4 + 1);
        int n = nums.size();
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            lfu.put(nums[i], 1);
            if(lfu.check())
                ans = i + 1;
        }
        return ans;
    }
};
