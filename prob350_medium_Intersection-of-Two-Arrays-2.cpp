// prob350: Intersection of Two Arrays II

/*
 * Given two arrays, write a function to compute their intersection.
 */

/*
 * Example 1:
 * Input: nums1 = [1,2,2,1], nums2 = [2,2]
 * Output: [2,2]
 * Example 2:
 * Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
 * Output: [4,9]
 */

/*
 * Follow up:
What if the given array is already sorted? How would you optimize your algorithm?
What if nums1's size is small compared to nums2's size? Which algorithm is better?
What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?
 */

#include <vector>
#include <unordered_map>

// 用两个 HashMap
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.empty() || nums2.empty())
            return vector<int>();
        unordered_map<int, int> mapping1, mapping2;
        for(int num: nums1) ++mapping1[num];
        for(int num: nums2) ++mapping2[num];
        vector<int> result;
        for(auto it1 = mapping1.begin(); it1 != mapping1.end(); ++it1)
        {
            auto it2 = mapping2.find(it1 -> first);
            if(it2 == mapping2.end()) continue;
            vector<int> item(min(it1 -> second, it2 -> second), it1 -> first);
            result.insert(result.begin(), item.begin(), item.end());
        }
        return result;
    }
};

// 用一个 hashmap
class Solution_2 {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.empty() || nums2.empty())
            return vector<int>();
        unordered_map<int, int> mapping;
        int n1 = nums1.size(), n2 = nums2.size();
        if(n1 <= n2)
        {
            _record(nums1, mapping);
            _stat(nums2, mapping, result);
        }
        else
        {
            _record(nums2, mapping);
            _stat(nums1, mapping, result);
        }
        return result;
    }

private:
    void _record(const vector<int>& nums, unordered_map<int, int>& mapping)
    {
        for(int num: nums)
            ++mapping[num];
    }

    void _stat(const vector<int>& nums, unordered_map<int, int>& mapping, vector<int>& result)
    {
        for(int num: nums)
        {
            auto it = mapping.find(num);
            if(it == mapping.end() || mapping[num] == 0) continue;
            --mapping[num];
            result.push_back(num);
        }
    }
};
