// prob765: Couples Holding Hands

/*
 * https://leetcode-cn.com/problems/couples-holding-hands/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int N = row.size();
        int ans = 0;
        vector<int> idxs(N, -1);
        for(int i = 0; i < N; ++i)
            idxs[row[i]] = i;
        for(int i = 0; i < N; i += 2)
        {
            if(row[i] == -1)
                continue;
            int len = 1;
            int cur = row[i];
            int target;
            if(cur & 1)
                target = cur - 1;
            else
                target = cur + 1;
            int iter = row[i + 1];
            row[i] = -1;
            row[i + 1] = -1;
            while(iter != target)
            {
                ++len;
                int nxt;
                if(iter & 1)
                    nxt = iter - 1;
                else
                    nxt = iter + 1;
                int nxt_idx = idxs[nxt];
                row[nxt_idx] = -1;
                if(nxt_idx & 1)
                {
                    iter = row[nxt_idx - 1];
                    row[nxt_idx - 1] = -1;
                }
                else
                {
                    iter = row[nxt_idx + 1];
                    row[nxt_idx + 1] = -1;
                }
            }
            ans += len - 1;
        }
        return ans;
    }
};
