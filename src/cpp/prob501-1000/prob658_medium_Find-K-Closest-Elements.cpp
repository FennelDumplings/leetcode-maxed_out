// prob658: Find K Closest Elements

/*
 * Given a sorted array, two integers k and x, find the k closest elements to x in the array. The
 * result should also be sorted in ascending order. If there is a tie, the smaller elements are always preferred.
 */

/*
 * Example 1:
 * Input: [1,2,3,4,5], k=4, x=3
 * Output: [1,2,3,4]
 * Example 2:
 * Input: [1,2,3,4,5], k=4, x=-1
 * Output: [1,2,3,4]
 */

/*
 * Note:
 * The value k is positive and will always be smaller than the length of the sorted array.
 * Length of the given array is positive and will not exceed 104
 * Absolute value of elements in the array and x will not exceed 104
 */

#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();
        // n > 1
        if(arr[0] >= x) return vector<int>(arr.begin(), arr.begin() + k);
        if(arr[n - 1] <= x) return vector<int>(arr.end() - k, arr.end());
        int left = 0, right = n - 1;
        int idx = -1; // 最接近 x 的下标
        while(left < right)
        {
            int mid = (left + right) / 2;
            if(arr[mid] == x)
            {
                idx = mid;
                break;
            }
            else if(arr[mid] > x)
                right = mid;
            else
                left = mid + 1;
        }
        if(idx == -1)
        {
            if(right > 0 && _check(arr, right - 1, right, x))
                idx = right - 1;
            else
                idx = right;
        }
        deque<int> dq(1, arr[idx]);
        int iter_l = idx - 1;
        int iter_r = idx + 1;
        for(int i = 1; i <= k - 1; ++i)
        {
            if(iter_l < 0)
            {
                dq.push_back(arr[iter_r]);
                ++iter_r;
                continue;
            }
            if(iter_r >= n)
            {
                dq.push_front(arr[iter_l]);
                --iter_l;
                continue;
            }
            if(_check(arr, iter_l, iter_r, x))
            {
                dq.push_front(arr[iter_l]);
                --iter_l;
            }
            else
            {
                dq.push_back(arr[iter_r]);
                ++iter_r;
            }
        }
        vector<int> result(dq.begin(), dq.end());
        return result;
    }

private:
    bool _check(vector<int>& arr, int left, int right, int x)
    {
        // arr[left] <= x <= arr[right]
        return x - arr[left] <= arr[right] - x;
    }
};

class Solution_2 {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();
        int l = 0, r = n - 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (x <= arr[mid])
                r = mid;
            else
                l = mid + 1;
        }
        l--;
        while (r - l - 1 < k && (l >= 0 || r < n)) {
            if (l >= 0 && r < n) {
                if (x - arr[l] <= arr[r] - x)
                    l--;
                else
                    r++;
            }
            else if (l >= 0)
                l--;
            else
                r++;
        }

        vector<int> ans;
        for (int i = l + 1; i < r; i++)
            ans.push_back(arr[i]);
        return ans;
    }
};
