// prob460: LFU Cache

/*
 * https://leetcode-cn.com/problems/lfu-cache/
 */

#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

class LFUCache {
public:
    LFUCache(int capacity) {
        cap = capacity;
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
        if((int)mapping.size() == cap)
        {
            int cnt = 0;
            while(cnt < (int)cnt_list.size() && cnt_list[cnt].empty())
                ++cnt;
            list<PII>::iterator to_be_removed_node = --(cnt_list[cnt].end());
            int to_be_removed_key = to_be_removed_node -> first;
            cnt_list[cnt].erase(to_be_removed_node);
            mapping.erase(to_be_removed_key);
        }
        if(cnt_list.empty())
            cnt_list.push_back({});
        cnt_list[0].insert(cnt_list[0].begin(), PII(key, 0));
        mapping[key] = PIL(value, cnt_list[0].begin());
    }

private:
    using PII = pair<int, int>;
    using PIL = pair<int, list<PII>::iterator>;
    int cap;
    unordered_map<int, PIL> mapping;
    list<PII> key_list;
    vector<list<PII>> cnt_list;
};


class LFUCache {
public:
    LFUCache(int capacity) {
        cap = capacity;
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
        if((int)mapping.size() == cap)
        {
            int cnt = 0;
            while(cnt < (int)cnt_list.size() && cnt_list[cnt].empty())
                ++cnt;
            list<PII>::iterator to_be_removed_node = --(cnt_list[cnt].end());
            int to_be_removed_key = to_be_removed_node -> first;
            cnt_list[cnt].erase(to_be_removed_node);
            mapping.erase(to_be_removed_key);
        }
        if(cnt_list.empty())
            cnt_list.push_back({});
        cnt_list[0].insert(cnt_list[0].begin(), PII(key, 0));
        mapping[key] = PIL(value, cnt_list[0].begin());
    }

private:
    using PII = pair<int, int>;
    using PIL = pair<int, list<PII>::iterator>;
    int cap;
    unordered_map<int, PIL> mapping;
    list<PII> key_list;
    vector<list<PII>> cnt_list;
};
