
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> sums(m + 1, vector<int>(n + 1));
        priority_queue<int, vector<int>, greater<int>> pq;
        for(int i = 1; i <= m; ++i)
            for(int j = 1; j <= n; ++j)
            {
                sums[i][j] = sums[i - 1][j] ^ sums[i][j - 1] ^ sums[i - 1][j - 1] ^ matrix[i - 1][j - 1];
                if((int)pq.size() < k)
                    pq.push(sums[i][j]);
                else
                {
                    if(pq.top() < sums[i][j])
                    {
                        pq.pop();
                        pq.push(sums[i][j]);
                    }
                }
            }
        return pq.top();
    }
};
