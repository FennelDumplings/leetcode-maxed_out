// prob715: Range Module

/*
 * A Range Module is a module that tracks ranges of numbers. Your task is to design and implement the following interfaces in an efficient manner.
 * addRange(int left, int right) Adds the half-open interval [left, right), tracking every real number in that interval. Adding an interval that partially overlaps with currently tracked numbers should add any numbers in the interval [left, right) that are not already tracked.
 * queryRange(int left, int right) Returns true if and only if every real number in the interval [left, right) is currently being tracked.
 * removeRange(int left, int right) Stops tracking every real number currently being tracked in the interval [left, right).
 */

/*
 * Example 1:
 * addRange(10, 20): null
 * removeRange(14, 16): null
 * queryRange(10, 14): true (Every number in [10, 14) is being tracked)
 * queryRange(13, 15): false (Numbers like 14, 14.03, 14.17 in [13, 15) are not being tracked)
 * queryRange(16, 17): true (The number 16 in [16, 17) is still being tracked, despite the remove operation)
 */

/*
 * Note:
 * A half open interval [left, right) denotes all real numbers left <= x < right.
 * 0 < left < right < 10^9 in all calls to addRange, queryRange, removeRange.
 * The total number of calls to addRange in a single test case is at most 1000.
 * The total number of calls to queryRange in a single test case is at most 5000.
 * The total number of calls to removeRange in a single test case is at most 1000.
 */

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */

#include <vector>
#include <map>

using namespace std;

// 416ms
// 借用 prob56, 57的写法
class RangeModule {
public:
    RangeModule() {}

    void addRange(int left, int right) {
        vector<pair<int, int> > new_ranges;
        bool inserted = false;
        for(const auto& kv: ranges_)
        {
            if(kv.first > right && !inserted)
            {
                new_ranges.emplace_back(left, right);
                inserted = true;
            }
            if(kv.second < left || kv.first > right)
            {
                new_ranges.push_back(kv);
            }
            else
            {
                left = min(left, kv.first);
                right = max(right, kv.second);
            }
        }
        if(!inserted) new_ranges.emplace_back(left, right);

        ranges_.swap(new_ranges);
    }

    bool queryRange(int left, int right) {
        // 二分地找 l
        int n = ranges_.size();
        if(n < 1) return false;
        int l = 0, r = n - 1;
        while(l <= r)
        {
            int mid = l + (r - l) / 2;
            if(ranges_[mid].first > right)
                r = mid - 1;
            else if(ranges_[mid].second < left)
                l = mid + 1;
            else
                return ranges_[mid].first <= left && ranges_[mid].second >= right;
        }
        return false;
    }

    void removeRange(int left, int right) {
        vector<pair<int, int> > new_ranges;
        for(const auto& kv: ranges_)
        {
            if(kv.second <= left || kv.first >= right) // 没有 overlap
                new_ranges.push_back(kv);
            else
            {
                if(kv.first < left)
                    new_ranges.emplace_back(kv.first, left);
                if(kv.second > right)
                    new_ranges.emplace_back(right, kv.second);
            }
        }
        ranges_.swap(new_ranges);
    }

private:
    vector<pair<int, int> >  ranges_;
};

// 平衡树写法
// 250ms
class RangeModule_2 {
public:
    RangeModule_2() {}

    void addRange(int left, int right) {
        IT l, r;
        getoverlapranges(left, right, l, r);
        if(l != r) // 至少一个 overlap
        {
            auto last = r;
            --last;
            left = min(left, l -> first);
            right = max(right, last -> second);
            ranges_.erase(l, r);
        }
        // add/merged range
        ranges_[left] = right;
    }

    bool queryRange(int left, int right) {
        IT l, r;
        getoverlapranges(left, right, l, r);
        if(l == r) return false;
        return l -> first <= left && l -> second >= right; // 看第一个 overlap 的区间是不是把输入全包含了
    }

    void removeRange(int left, int right) {
        IT l, r;
        getoverlapranges(left, right, l, r);
        if(l == r) return;
        auto last = r;
        --last;
        int start = min(left, l -> first);
        int end = max(right, last -> second);
        ranges_.erase(l, r);
        if(start < left) ranges_[start] = left;
        if(end > right) ranges_[right] = end;
    }

private:
    using IT = map<int, int>::iterator;
    map<int, int> ranges_;
    void getoverlapranges(int left, int right, IT& l, IT& r)
    {
        l = ranges_.upper_bound(left);
        r = ranges_.upper_bound(right);
        if(l != ranges_.begin())
            if((--l) -> second < left) l++;
    }
};
