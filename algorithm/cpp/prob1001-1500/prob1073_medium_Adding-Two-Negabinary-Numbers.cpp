// prob1073: Adding Two Negabinary Numbers

/*
 * https://leetcode-cn.com/problems/adding-two-negabinary-numbers/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> addNegabinary(vector<int>& arr1, vector<int>& arr2) {
        int N1 = arr1.size();
        int N2 = arr2.size();
        reverse(arr1.begin(), arr1.end());
        reverse(arr2.begin(), arr2.end());
        vector<int> res;
        int i1 = 0, i2 = 0;
        int carry = 0;
        while(i1 < N1 || i2 < N2 || carry != 0)
        {
            int c = carry;
            int a = 0, b = 0;
            if(i1 < N1) a = arr1[i1++];
            if(i2 < N2) b = arr2[i2++];
            int v = a + b - c;
            carry = v >> 1;
            res.push_back(v & 1);
        }
        auto it = res.end() - 1;
        while(it != res.begin() && *it == 0)
        {
            res.pop_back();
            --it;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

