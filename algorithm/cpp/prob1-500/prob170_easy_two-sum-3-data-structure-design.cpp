// prob170: two-sum-3-data-structure-design

/*
 * Design and implement a TwoSum class. It should support the following operations: add and find.
 * add - Add the number to an internal data structure.
 * find - Find if there exists any pair of numbers which sum is equal to the value.
 */

/*
 * Example 1:
 * add(1); add(3); add(5);
 * find(4) -> true
 * find(7) -> false
 * Example 2:
 * add(3); add(1); add(2);
 * find(3) -> true
 * find(6) -> false
 */

#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

// 1144ms
class TwoSum {
public:
    /** Initialize your data structure here. */
    TwoSum() {
        vec = vector<int>();
    }

    /** Add the number to an internal data structure.. */
    void add(int number) {
        vec.push_back(number);
    }

    /** Find if there exists any pair of numbers which sum is equal to the value. */
    bool find(int value) {
        if(vec.empty()) return false;
        int n = vec.size();
        if(n == 1) return false;
        unordered_set<int> setting;
        setting.insert(vec[0]);
        for(int i = 1; i < n; ++i)
        {
            int gap = value - vec[i];
            if(setting.find(gap) != setting.end())
                return true;
            setting.insert(vec[i]);
        }
        return false;
    }

private:
    vector<int> vec;
};


class TwoSum_2 {
public:
    /** Initialize your data structure here. */
    TwoSum_2() {
        vec = unordered_map<int, int>();
    }

    /** Add the number to an internal data structure.. */
    void add(int number) {
        if(vec.find(number) != vec.end())
            ++vec[number];
        else
            vec[number] = 1;;
    }

    /** Find if there exists any pair of numbers which sum is equal to the value. */
    bool find(int value) {
        if(vec.empty()) return false;

        for(pair<int, int> p: vec)
        {
            int gap = value - p.first;
            if(gap == p.first || p.second == 1) continue;
            auto it = vec.find(gap);
            if(it != vec.end())
                return true;
        }
        return false;
    }

private:
    unordered_map<int, int> vec; // 元素，出现次数
};
