// prob1577: Number of Ways Where Square of Number Is Equal to Product of Two Numbers

/*
 * https://leetcode-cn.com/problems/number-of-ways-where-square-of-number-is-equal-to-product-of-two-numbers/
 */

#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int numTriplets(vector<int>& nums1, vector<int>& nums2) {
        using ll = long long;
        int n1 = nums1.size();
        int n2 = nums2.size();
        unordered_map<int, int> cnts1;
        unordered_map<int, int> cnts2;
        int ans = 0;
        for(int i = 0; i < n1; ++i)
        {
            for(int j = 0; j < n2; ++j)
            {
                if(((ll)nums2[j] * nums2[j]) % nums1[i] == 0)
                {
                    int t1 = (ll)nums2[j] * nums2[j] / nums1[i];
                    ans += cnts1[t1];
                }
            }
            cnts1[nums1[i]]++;
        }
        for(int j = 0; j < n2; ++j)
        {
            for(int i = 0; i < n1; ++i)
            {
                if(((ll)nums1[i] * nums1[i]) % nums2[j] == 0)
                {
                    int t2 = (ll)nums1[i] * nums1[i] / nums2[j];
                    ans += cnts2[t2];
                }
            }
            cnts2[nums2[j]]++;
        }
        return ans;
    }
};
