// 20200614
// 2. 不同整数的最少数目

/*
 * 给你一个整数数组 arr 和一个整数 k 。现需要从数组中恰好移除 k 个元素，请找出移除后数组中不同整数的最少数目。
 */

/*
 * 提示：
 *
 * 1 <= arr.length <= 10^5
 * 1 <= arr[i] <= 10^9
 * 0 <= k <= arr.length
 */

#include <vector>
#include <unordered_map>
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
