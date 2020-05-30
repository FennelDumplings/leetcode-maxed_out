// prob1122: Relative Sort Array

/*
 * Given two arrays arr1 and arr2, the elements of arr2 are distinct, and all elements in arr2 are also in arr1.
 * Sort the elements of arr1 such that the relative ordering of items in arr1 are the same as in arr2.  Elements that don't appear in arr2 should be placed at the end of arr1 in ascending order.
 */

/*
 * Example 1:
 * Input: arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
 * Output: [2,2,2,1,4,3,3,9,6,7,19]
 */

/*
 * Constraints:
 * arr1.length, arr2.length <= 1000
 * 0 <= arr1[i], arr2[i] <= 1000
 * Each arr2[i] is distinct.
 * Each arr2[i] is in arr1.
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        Cmp cmp(arr2);
        vector<int> result(arr1.begin(), arr1.end());
        sort(result.begin(), result.end(), cmp);
        return result;
    }

private:
    struct Cmp
    {
        vector<int> mapping;
        Cmp(const vector<int>& vec)
        {
            mapping = vector<int>(1001, -1);
            int n = vec.size();
            for(int i = 0; i < n; ++i)
                mapping[vec[i]] = i;
        }
        bool operator()(const int& a, const int& b)
        {
            if(mapping[a] != -1 && mapping[b] != -1)
                return mapping[a] < mapping[b];
            if(mapping[a] != -1)
                return true;
            if(mapping[b] != -1)
                return false;
            return a < b;
        }
    };
};

// 计数排序
class Solution_2 {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        vector<bool> in_arr2(1001, false);
        for(int num: arr2)
            in_arr2[num] = true;
        vector<int> cnt(1001, 0);
        for(int num: arr1)
            ++cnt[num];
        vector<int> result;
        for(int num: arr2)
        {
            if(cnt[num] > 0)
            {
                for(int i = 0; i < cnt[num]; ++i)
                    result.push_back(num);
            }
        }
        for(int num = 0; num <= 1000; ++num)
        {
            if(in_arr2[num]) continue;
            if(cnt[num] == 0) continue;
            for(int i = 0; i < cnt[num]; ++i)
                result.push_back(num);
        }
        return result;
    }
};
