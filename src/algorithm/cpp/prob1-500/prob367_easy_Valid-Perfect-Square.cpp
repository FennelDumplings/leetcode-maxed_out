// prob367: Valid Perfect Square

/*
 * https://leetcode-cn.com/problems/valid-perfect-square/
 */

class Solution {
public:
    bool isPerfectSquare(int num) {
        using ll = long long;
        int left = 1, right = num;
        while(left <= right)
        {
            int mid = left + (right - left) / 2;
            ll product = (ll)mid * mid;
            if(product == num)
                return true;
            else if(product > num)
                right = mid - 1;
            else
                left = mid + 1;
        }
        return false;
    }
};
