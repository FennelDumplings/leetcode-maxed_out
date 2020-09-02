// 2. 找出数组游戏的赢家

#include <vector>

using namespace std;

class Solution {
public:
    int getWinner(vector<int>& arr, int k) {
        int n = arr.size();
        // n >= 2
        if(arr[0] > arr[1])
            swap(arr[0], arr[1]);
        int ans = arr[1];
        int idx = 1;
        int i = 1;
        while(i < n)
        {
            bool flag = true;
            for(int c = 1; c <= k - 1; ++c)
            {
                // arr[i] 若要是答案，要后面 k - 1 个数均比其小，或者不足 k - 1 个数
                if(i + c >= n)
                    return ans;
                if(arr[i + c] > arr[i])
                {
                    ans = arr[i + c];
                    idx = i + c;
                    flag = false;
                    break;
                }
            }
            if(flag)
                return ans;
            i = idx;
        }
        return -1;
    }
};
