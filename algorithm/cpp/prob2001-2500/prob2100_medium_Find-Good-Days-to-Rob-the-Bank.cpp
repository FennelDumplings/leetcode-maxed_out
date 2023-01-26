#include <vector>

using namespace std;

class Solution {
public:
    vector<int> goodDaysToRobBank(vector<int>& security, int time) {
        int n = security.size();
        // L[i] := 以 i 结尾的最长非递增长度
        vector<int> L(n, 1);
        // R[i] := 以 i 开头的最长非递减长度
        vector<int> R(n, 1);
        for(int i = 1; i < n; ++i)
        {
            if(security[i - 1] >= security[i])
                L[i] += L[i - 1];
        }
        for(int i = n - 2; i >= 0; --i)
        {
            if(security[i] <= security[i + 1])
                R[i] += R[i + 1];
        }
        vector<int> result;
        for(int i = 0; i < n; ++i)
        {
            if(L[i] >= time + 1 && R[i] >= time + 1)
                result.push_back(i);
        }
        return result;
    }
};
