#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class Solution {
public:
    vector<int> sortEvenOdd(vector<int>& nums) {
        int n = nums.size();
        int na = (n + 1) / 2;
        int nb = n / 2;
        vector<int> A(na), B(nb);
        for(int i = 0; i < na; ++i)
            A[i] = nums[i * 2];
        for(int i = 0; i < nb; ++i)
            B[i] = nums[i * 2 + 1];
        sort(A.begin(), A.end());
        sort(B.begin(), B.end(), greater<int>());
        vector<int> result(n);
        for(int i = 0; i < n; ++i)
        {
            if(i & 1)
                result[i] = B[(i - 1) / 2];
            else
                result[i] = A[i / 2];
        }
        return result;
    }
};
