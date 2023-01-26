// interview17.14: 最小K个数

/*
 * https://leetcode-cn.com/problems/smallest-k-lcci/
 */

#include <vector>
#include <random>

using namespace std;

class Solution {
public:
    // [0..n - 1]
    // [0..mid] [mid + 1, n - 1]
    vector<int> smallestK(vector<int>& arr, int k) {
        vector<int> result;
        int n = arr.size();
        dre = std::default_random_engine();
        topk(arr, 0, n - 1, k, result);
        return result;
    }

private:
    std::default_random_engine dre;

    void topk(vector<int>& arr, const int left, const int right, int k, vector<int>& result)
    {
        if(k <= 0 || left > right) return;
        std::uniform_int_distribution<int> di(left, right);
        int p = di(dre);
        int pivot = arr[p];
        swap(arr[left], arr[p]);
        int partition = left;
        int l = left + 1, r = right;
        // 保持 partition + 1 == left
        while(l <= r)
        {
            if(arr[l] <= pivot)
            {
                swap(arr[partition], arr[l]);
                ++l;
                ++partition;
            }
            else
            {
                swap(arr[r], arr[l]);
                --r;
            }
        }
        if(partition - left + 1 == k) // [l .. partition] 均小于等于 pivot, [partition + 1, right] 均大于 pivot
        {
            for(int i = left; i <= partition; ++i)
                result.push_back(arr[i]);
            return;
        }
        else if(partition - left + 1 < k)
        {
            for(int i = left; i <= partition; ++i)
                result.push_back(arr[i]);
            topk(arr, partition + 1, right, k - (partition - left + 1), result);
        }
        else
        {
            topk(arr, left, partition - 1, k, result);
        }
    }
};
