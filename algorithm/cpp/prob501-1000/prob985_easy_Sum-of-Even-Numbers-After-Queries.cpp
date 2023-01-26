
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> sumEvenAfterQueries(vector<int>& A, vector<vector<int>>& queries) {
        int n = A.size();
        int sum = 0;
        for(int i = 0; i < n; ++i)
            if((A[i] & 1) == 0)
                sum += A[i];
        int m = queries.size();
        vector<int> result(m, -1);
        for(int i = 0; i < m; ++i)
        {
            int val = queries[i][0];
            int idx = queries[i][1];
            if((A[idx] & 1) == 0)
                sum -= A[idx];
            A[idx] += val;
            if((A[idx] & 1) == 0)
                sum += A[idx];
            result[i] = sum;
        }
        return result;
    }
};
