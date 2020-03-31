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
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.empty() || nums2.empty()) return vector<int>();
        unordered_map<int, int> mapping1, mapping2;
        for(int num: nums1) ++mapping1[num];
        for(int num: nums2) ++mapping2[num];
        vector<int> result;
        for(int it1 = mapping1.begin(); it != mapping1.end(); ++it)
        {
            if(mapping2.find(it1 -> first) != mapping2.end())
            {
                vector<int> item(min(it1 -> second, mapping2[it1 -> first]), it1 -> first);
                result.insert(result.end(), item.begin(), item.end());
            }
        }
        return result;
    }
};
