// interview40: 最小的k个数

/*
 * https://leetcode-cn.com/problems/zui-xiao-de-kge-shu-lcof/
 */

#include <vector>
#include <queue>
#include <functional>

using namespace std;

class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        // 最大堆
        // 小于队头的，出堆进队
        if(k == 0) return {};
        priority_queue<int, vector<int>, less<int>> pq;
        for(int i = 0; i < k; ++i)
        {
            pq.push(arr[i]);
        }
        int n = arr.size();
        for(int i = k; i < n; ++i)
        {
            if(arr[i] < pq.top())
            {
                pq.pop();
                pq.push(arr[i]);
            }
        }
        vector<int> result;
        while(!pq.empty())
        {
            result.push_back(pq.top());
            pq.pop();
        }
        return result;
    }
};
