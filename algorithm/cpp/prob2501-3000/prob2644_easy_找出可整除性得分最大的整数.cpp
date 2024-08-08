class Solution {
public:
    int maxDivScore(vector<int>& nums, vector<int>& divisors) {
        int n = nums.size();
        int m = divisors.size();
        int ans = -1;
        int max_score = -1;
        for(int i = 0; i < m; ++i)
        {
            int score = 0;
            for(int x: nums)
                if(x % divisors[i] == 0)
                    score++;
            if(score > max_score)
            {
                max_score = score;
                ans = divisors[i];
            }
            else if(score == max_score)
                ans = min(ans, divisors[i]);
        }
        return ans;
    }
};

