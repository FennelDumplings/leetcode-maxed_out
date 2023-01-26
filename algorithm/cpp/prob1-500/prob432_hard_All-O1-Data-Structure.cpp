// prob432: All O`one Data Structure`

/*
 * https://leetcode-cn.com/problems/all-oone-data-structure/
 */

#include <vector>
#include <list>
#include <unordered_map>
#include <string>

using namespace std;

struct Bucket
{
    int val;
    list<string> keys;
    Bucket(int val):val(val)
    {
        keys = list<string>();
    }
};

struct Index
{
    list<Bucket>::iterator bucket_it;
    list<string>::iterator key_it;
    Index(list<Bucket>::iterator bucket_it, list<string>::iterator key_it):bucket_it(bucket_it),key_it(key_it){}
    Index(){}
};

class AllOne {
public:
    /** Initialize your data structure here. */
    AllOne() {
        buckets = list<Bucket>();
        mapping = unordered_map<string, Index>();
    }

    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        if(mapping.count(key) == 0)
        {
            if(buckets.empty() || buckets.front().val > 1)
                buckets.emplace_front(1);
            buckets.front().keys.push_back(key);
            list<string>::iterator key_it = --buckets.front().keys.end();
            list<Bucket>::iterator bucket_it = buckets.begin();
            mapping[key] = Index(bucket_it, key_it);
        }
        else
        {
            Index idx = mapping[key];
            int val = idx.bucket_it -> val;
            auto nxt_bucket_it = next(idx.bucket_it, 1);
            if(nxt_bucket_it == buckets.end() || nxt_bucket_it -> val > val + 1)
            {
                nxt_bucket_it = buckets.insert(nxt_bucket_it, Bucket(val + 1));
            }
            (nxt_bucket_it -> keys).push_back(key);
            list<string>::iterator key_it = --(nxt_bucket_it -> keys).end();
            mapping[key] = Index(nxt_bucket_it, key_it);
            (idx.bucket_it -> keys).erase(idx.key_it);
            if((idx.bucket_it -> keys).empty())
            {
                buckets.erase(idx.bucket_it);
            }
        }
    }

    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        if(mapping.count(key) == 0)
            return;
        Index idx = mapping[key];
        mapping.erase(key);
        int val = idx.bucket_it -> val;
        if(val == 1)
        {
            (idx.bucket_it -> keys).erase(idx.key_it);
            if((idx.bucket_it -> keys).empty())
                buckets.erase(idx.bucket_it);
        }
        else
        {
            auto prev_bucket_it = prev(idx.bucket_it, 1);
            if(idx.bucket_it == buckets.begin() || prev_bucket_it -> val < val - 1)
            {
                prev_bucket_it = buckets.insert(idx.bucket_it, Bucket(val - 1));
            }
            (prev_bucket_it -> keys).push_back(key);
            list<string>::iterator key_it = --(prev_bucket_it -> keys).end();
            mapping[key] = Index(prev_bucket_it, key_it);
            (idx.bucket_it -> keys).erase(idx.key_it);
            if((idx.bucket_it -> keys).empty())
                buckets.erase(idx.bucket_it);
        }
    }

    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        if(buckets.empty())
            return "";
        return (buckets.back().keys).back();
    }

    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        if(buckets.empty())
            return "";
        return (buckets.front().keys).back();
    }

private:
    list<Bucket> buckets;
    unordered_map<string, Index> mapping;
};
