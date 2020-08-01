// interview10.03: 搜索旋转数组

/*
 * https://leetcode-cn.com/problems/search-rotate-array-lcci/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& arr, int target) {
        if(arr.empty()) return -1;
        int n = arr.size();
        int left = 0, right = n - 1;
        while(left <= right)
        {
            if(arr[left] == target)
                return left;
            // arr[left] != target
            int mid = (left + right) / 2;
            if(arr[mid] == target)
            {
                right = mid;
                continue;
            }
            if(arr[left] < arr[right])
            {
                if(arr[mid] > target)
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            else
            {
                if(arr[left] < target)
                {
                    if(arr[mid] > target)
                        right = mid - 1;
                    else
                        ++left;
                }
                else
                {
                    if(arr[mid] < target)
                        left = mid + 1;
                    else
                        ++left;
                }
            }
        }
        return -1;
    }
};
