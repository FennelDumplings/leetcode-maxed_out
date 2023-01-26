// prob1213: Intersection of Three Sorted Arrays

/*
 * Given three integer arrays arr1, arr2 and arr3 sorted in strictly increasing order, return a sorted array of only the integers
 * that appeared in all three arrays.
 */

/*
 * Example 1:
 *
 * Input: arr1 = [1,2,3,4,5], arr2 = [1,2,5,7,9], arr3 = [1,3,4,5,8]
 * Output: [1,5]
 * Explanation: Only 1 and 5 appeared in the three arrays.
 *
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/intersection-of-three-sorted-arrays
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

/*
 * Constraints:
 * 1 <= arr1.length, arr2.length, arr3.length <= 1000
 * 1 <= arr1[i], arr2[i], arr3[i] <= 2000
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> arraysIntersection(vector<int>& arr1, vector<int>& arr2, vector<int>& arr3) {
        int n1 = arr1.size(), n2 = arr2.size(), n3 = arr3.size();
        if(n1 == 0 || n2 == 0 || n3 == 0) return vector<int>();
        int i1 = 0, i2 = 0, i3 = 0;
        vector<int> result;
        while(i1 < n1 && i2 < n2 && i3 < n3)
        {
            if(arr1[i1] == arr2[i2] && arr2[i2] == arr3[i3])
            {
                result.push_back(arr1[i1]);
                ++i1, ++i2, ++i3;
                continue;
            }
            int maxx = max(arr1[i1], max(arr2[i2], arr3[i3]));
            if(arr1[i1] < maxx) ++i1;
            if(arr2[i2] < maxx) ++i2;
            if(arr3[i3] < maxx) ++i3;
        }
        return result;
    }
};
