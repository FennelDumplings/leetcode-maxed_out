// prob1243: Array Transformation

/*
 * https://leetcode-cn.com/problems/array-transformation/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> transformArray(vector<int>& arr) {
        int n = arr.size();
        if(n < 3) return arr;
        vector<int> result(arr.begin(), arr.end());
        bool flag = false;
        while(!flag)
        {
            if(transfer(result))
                flag = true;
        }
        return result;
    }

private:
    bool transfer(vector<int>& arr)
    {
        int n = arr.size();
        bool flag = true;
        for(int i = 1; i < n - 1; ++i)
        {
            if(arr[i] > (arr[i - 1] & ((1 << 7) - 1)) && arr[i] > arr[i + 1])
            {
                arr[i] |= ((arr[i] - 1) << 7);
                flag = false;
            }
            else if(arr[i] < (arr[i - 1] & ((1 << 7) - 1)) && arr[i] < arr[i + 1])
            {
                arr[i] |= ((arr[i] + 1) << 7);
                flag = false;
            }
        }
        if(!flag)
            for(int i = 1; i < n - 1; ++i)
                if((arr[i] >> 7) != 0)
                    arr[i] >>= 7;
        return flag;
    }
};
