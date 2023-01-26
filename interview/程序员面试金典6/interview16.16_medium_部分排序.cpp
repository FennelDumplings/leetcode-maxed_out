// interview16.16: 部分排序

/*
 * https://leetcode-cn.com/problems/sub-sort-lcci/
 */

#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    vector<int> subSort(vector<int>& array) {
        if(array.empty()) return {-1, -1};
        int n = array.size();
        if(n == 1) return {-1, -1};
        map<int, int> mapping; // num -> 最左 idx
        mapping[array[0]] = 0;
        int left = n, right = -1;
        for(int i = 1; i < n; ++i)
        {
            if(left == n && array[i] > mapping.rbegin() -> first)
            {
                mapping[array[i]] = i;
            }
            else if(array[i] < mapping.rbegin() -> first)
            {
                auto it = mapping.upper_bound(array[i]);
                left = min(left, it -> second);
            }
        }
        mapping.clear();
        mapping[array[n - 1]] = n - 1;
        for(int i = n - 2; i >= 0; --i)
        {
            if(right == -1 && array[i] < mapping.begin() -> first)
                mapping[array[i]] = i;
            else if(array[i] > mapping.begin() -> first)
            {
                auto it = mapping.lower_bound(array[i]);
                right = max(right, (--it) -> second);
            }
        }
        if(left == n)
            return {-1, -1};
        return {left, right};
    }
};

#include <algorithm>

class Solution_2 {
public:
    vector<int> subSort(vector<int>& array) {
        if(array.empty()) return {-1, -1};
        int n = array.size();
        if(n == 1) return {-1, -1};
        vector<int> arr(array.begin(), array.end());
        sort(arr.begin(), arr.end());
        int left = -1;
        for(int i = 0; i < n; ++i)
            if(array[i] != arr[i])
            {
                left = i;
                break;
            }
        if(left == -1)
            return {-1, -1};
        int right = n;
        for(int i = n - 1; i >= 0; --i)
            if(array[i] != arr[i])
            {
                right = i;
                break;
            }
        return {left, right};
    }
};
