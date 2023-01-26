class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int sum = 0;
        int ans = 0;
        for(int x: gain)
        {
            sum += x;
            ans = max(ans, sum);
        }
        return ans;
    }
};
