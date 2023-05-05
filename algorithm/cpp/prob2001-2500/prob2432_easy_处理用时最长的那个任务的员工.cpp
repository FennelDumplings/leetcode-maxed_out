class Solution {
public:
    int hardestWorker(int n, vector<vector<int>>& logs) {
        int max_d = 0;
        int ans = -1;
        int m = logs.size();
        int start = 0;
        for(int i = 0; i < m; ++i)
        {
            if(logs[i][1] - start > max_d)
            {
                ans = logs[i][0];
                max_d = logs[i][1] - start;
            }
            else if(logs[i][1] - start == max_d)
            {
                ans = min(ans, logs[i][0]);
            }
            start = logs[i][1];
        }
        return ans;
    }
};
