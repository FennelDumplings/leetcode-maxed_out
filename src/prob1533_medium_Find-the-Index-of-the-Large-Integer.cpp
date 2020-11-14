// prob1533: Find the Index of the Large Integer

/*
 * https://leetcode-cn.com/problems/find-the-index-of-the-large-integer/
 */

/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 */

class ArrayReader {
  public:
    // Compares the sum of arr[l..r] with the sum of arr[x..y]
    // return 1 if sum(arr[l..r]) > sum(arr[x..y])
    // return 0 if sum(arr[l..r]) == sum(arr[x..y])
    // return -1 if sum(arr[l..r]) < sum(arr[x..y])
    int compareSub(int l, int r, int x, int y);

    // Returns the length of the array
    int length();
};


class Solution {
public:
    int getIndex(ArrayReader &reader) {
        int n = reader.length();
        return solve(reader, 0, n - 1);
    }

private:
    int solve(ArrayReader &reader, int l, int r)
    {
        if(l == r)
            return l;
        int mid = (l + r) / 2;
        if((r - l + 1) & 1)
        {
            int res = reader.compareSub(l, mid - 1, mid + 1, r);
            if(res == 0)
                return mid;
            else if(res > 0)
                return solve(reader, l, mid - 1);
            else
                return solve(reader, mid + 1, r);
        }
        else
        {
            int res = reader.compareSub(l, mid, mid + 1, r);
            if(res > 0)
                return solve(reader, l, mid);
            else
                return solve(reader, mid + 1, r);
        }
    }
};
