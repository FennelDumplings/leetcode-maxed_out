// prob1095: Find in Mountain Array

/*
 * https://leetcode-cn.com/problems/find-in-mountain-array/
 */

/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 */

class MountainArray {
  public:
    int get(int index);
    int length();
};


class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int n = mountainArr.length();
        // 三分查找，得最大值点
        int l = 1, r = n - 2;
        while(l < r)
        {
            int m1 = l + (r - l) / 2;
            int m2 = (m1 + 1) + (r - (m1 + 1)) / 2;
            int a_m1 = mountainArr.get(m1);
            int a_m2 = mountainArr.get(m2);
            if(a_m1 > a_m2)
                r = m2 - 1;
            else if(a_m1 < a_m2)
                l = m1 + 1;
            else
            {
                l = m1 + 1;
                r = m2 - 1;
            }
        }
        int max_idx = l;
        if(mountainArr.get(max_idx) == target)
            return max_idx;
        int left = _bisearch(0, max_idx - 1, true, mountainArr, target);
        if(left != -1)
            return left;
        int right = _bisearch(max_idx + 1, n - 1, false, mountainArr, target);
        if(right != -1)
            return right;
        return -1;
    }

private:
    int _bisearch(int l, int r, bool up, MountainArray &mountainArr, const int target)
    {
        while(l <= r)
        {
            int m = (l + r) / 2;
            int mx = mountainArr.get(m);
            if(mx == target)
                return m;
            else if(mx < target)
            {
                if(up)
                    l = m + 1;
                else
                    r = m - 1;
            }
            else
            {
                if(up)
                    r = m - 1;
                else
                    l = m + 1;
            }
        }
        return -1;
    }
};
