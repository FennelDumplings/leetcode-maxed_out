// prob278: First Bad Version

/*
 * Suppose you have n versions [1, 2, ..., n]
 * and you want to find out the first bad one,
 * which causes all the following ones to be bad.
 */

/*
 * Example:
 * Given n = 5, and version = 4 is the first bad version.
 * call isBadVersion(3) -> false
 * call isBadVersion(5) -> true
 * call isBadVersion(4) -> true
 * Then 4 is the first bad version.
 */

// 假设一定存在错误版本


// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        if(n <= 0) return 0;
        int left = 1, right = n;
        // using ll = long long;
        while(left < right)
        {
            // int mid = ((ll)left + (ll)right) / 2;
            int mid = left + (right - left) / 2; // 求平均数更好的写法
            if(isBadVersion(mid))
                right = mid - 1;
            else
                left = mid + 1;
        }
        if(isBadVersion(right))
            return right;
        else
            return right + 1;
    }
};
