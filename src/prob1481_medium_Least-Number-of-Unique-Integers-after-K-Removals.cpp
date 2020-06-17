// prob1481: Least Number of Unique Integers after K Removals

/*
 * Given an array of integers arr and an integer k. Find the least number of unique integers after removing exactly k elements.
 */

/*
 * Example 1:
 * Input: arr = [5,5,4], k = 1
 * Output: 1
 * Explanation: Remove the single 4, only 5 is left.
 * Example 2:
 * Input: arr = [4,3,1,1,3,3,2], k = 3
 * Output: 2
 * Explanation: Remove 4, 2 and either one of the two 1s or three 3s. 1 and 3 will be left.
 */

/*
 * Constraints:
 * 1 <= arr.length <= 10^5
 * 1 <= arr[i] <= 10^9
 * 0 <= k <= arr.length
 */

#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        unordered_map<int, int> cnt;
        for(int a: arr)
            ++cnt[a];
        vector<int> cnts;
        for(auto item: cnt)
            cnts.push_back(item.second);
        sort(cnts.begin(), cnts.end());
        int N = cnts.size();
        for(int i = 1; i < N; ++i)
            cnts[i] += cnts[i - 1];
        auto it = lower_bound(cnts.begin(), cnts.end(), k + 1);
        return cnts.end() - it;
    }
};
