class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> answer(n);
        for(int i = 0; i < n; ++i)
        {
            int x = nums[i];
            int max_or = x;
            answer[i] = 1;
            for(int j = i + 1; j < n; ++j)
            {
                x = x | nums[j];
                if(max_or > x)
                {
                    max_or = x;
                    answer[i] = j - i + 1;
                }
            }
        }
        return answer;
    }
};
