// interview16.20: 交换和

/*
 * https://leetcode-cn.com/problems/sum-swap-lcci/
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> findSwapValues(vector<int>& array1, vector<int>& array2) {
        int sum1 = 0, sum2 = 0;
        for(int i: array1) sum1 += i;
        for(int i: array2) sum2 += i;
        if((sum1 + sum2) & 1) return {};
        int x = (sum2 - sum1) >> 1;
        unordered_set<int> setting;
        for(int i: array2)
            setting.insert(i);
        for(int i: array1)
        {
            int gap = i + x;
            if(setting.find(gap) != setting.end())
                return {i, gap};
        }
        return {};
    }
};
