ll gcd(ll a,ll b)
{
    if(b == 0)
        return a;
    return gcd(b, a % b);
}

ll lcm(ll x, ll y)
{
    return x * y / gcd(x, y);
}

class Solution {
public:
    int subarrayLCM(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            int range_lcm = nums[i];
            if(k < range_lcm || k % range_lcm != 0)
                continue;
            if(range_lcm == k)
                ans += 1;
            for(int j = i + 1; j < n; ++j)
            {
                range_lcm = lcm(range_lcm, nums[j]);
                if(k < range_lcm || k % range_lcm != 0)
                    break;
                if(range_lcm == k)
                    ans += 1;
            }
        }
        return ans;
    }
};
