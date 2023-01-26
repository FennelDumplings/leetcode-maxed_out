// prob349: Intersection of Two Arrays

/*
 * Given two arrays, write a function to compute their intersection.
 */

/*
 * Example 1:
 * Input: nums1 = [1,2,2,1], nums2 = [2,2]
 * Output: [2]
 * Example 2:
 * Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
 * Output: [9,4]
 */

/*
 * Note:
 * Each element in the result must be unique.
 * The result can be in any order.
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.empty() || nums2.empty()) return vector<int>();
        unordered_set<int> setting1, setting2;
        for(int num: nums1) setting1.insert(num);
        for(int num: nums2) setting2.insert(num);
        vector<int> result;
        for(auto it1 = setting1.begin(); it1 != setting1.end(); ++it1)
        {
            if(setting2.find(*it1) != setting2.end())
                result.push_back(*it1);
        }
        return result;
    }
};
