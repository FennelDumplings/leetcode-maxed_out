// prob1338: reduce Array Size to The Half

/*
 * https://leetcode-cn.com/problems/reduce-array-size-to-the-half/
 */

#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int minSetSize(vector<int>& arr) {
        unordered_map<int, int> mapping;
        for(int a: arr)
            ++mapping[a];
        priority_queue<int> pq;
        for(auto item: mapping)
            pq.push(item.second);
        int n = arr.size();
        int K = n - n / 2;
        int ans = 0;
        while(K > 0)
        {
            K -= pq.top();
            pq.pop();
            ++ans;
        }
        return ans;
    }
};
