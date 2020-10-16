// prob1196: How Many Apples Can You Put into the Basket

/*
 * https://leetcode-cn.com/problems/how-many-apples-can-you-put-into-the-basket/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxNumberOfApples(vector<int>& arr) {
        int V = 5000;
        sort(arr.begin(), arr.end());
        int cnt = 0;
        for(int i: arr)
        {
            if(V < i)
                break;
            ++cnt;
            V -= i;
        }
        return cnt;
    }
};
