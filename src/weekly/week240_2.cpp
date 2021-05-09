#include <vector>

using namespace std;

class Solution {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        int i = 0, j = 0;
        int ans = 0;
        while(i < n1 && j < n2)
        {
            // 此时保证 i <= j
            // 尽可能往前推进 j
            while(j < n2 && nums1[i] <= nums2[j])
                ++j;
            ans = max(ans, (j - 1) - i);
            if(j == n2)
                break;
            // 向前调整 i
            while(i < n1 && nums1[i] > nums2[j])
                ++i;
            // 调整 i 后如果 i > j，需要调整 j
            j = max(j, i);
            // 此时 j 可能 >= n2
        }
        return ans;
    }
};
