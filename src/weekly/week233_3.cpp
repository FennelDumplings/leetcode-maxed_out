

class Solution {
public:
    int maxValue(int n, int index, int maxSum) {
        left_n = index; // [0..index-1] 的个数
        right_n = n - index - 1; // [index+1..n-1] 的个数
        int left = 1, right = n;
        while(left < right)
        {
            int mid = (left + right + 1) / 2;
            ll sum = get_min_sum(mid);
            if(sum > maxSum)
            {
                right = mid - 1;
            }
            else
            {
                left = mid;
            }
        }
        return left;
    }

private:
    int left_n, right_n;
    using ll = long long;

    ll get_min_sum(int x)
    {
        // nums[index] 取 x 时，sum(nums) 可以取的最小值
        ll left = 0, right = 0;
        if(x - left_n >= 1)
        {
            left = (x - left_n + x - 1) * (ll)left_n / 2;
        }
        else
        {
            left = (1 + x - 1) * (ll)(x - 1) / 2;
            left += left_n - (x - 1);
        }
        if(x - right_n >= 1)
        {
            right = (x - right_n + x - 1) * (ll)right_n / 2;
        }
        else
        {
            right = (1 + x - 1) * (ll)(x - 1) / 2;
            right += right_n - (x - 1);
        }
        return left + right + x;
    }
};
