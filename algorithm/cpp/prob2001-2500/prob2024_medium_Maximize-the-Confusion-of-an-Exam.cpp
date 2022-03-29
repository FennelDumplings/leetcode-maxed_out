#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        int n = answerKey.size();
        vector<int> sums(n + 1); // sums[i + 1] := [0..i] 的 T 的个数
        for(int i = 0; i < n; ++i)
            sums[i + 1] = sums[i] + (answerKey[i] == 'T');
        int left = 1;
        int right = n;
        while(left < right)
        {
            int mid = (left + right + 1) / 2;
            if(check(mid, sums, k))
                left = mid;
            else
                right = mid - 1;
        }
        return left;
    }

    bool check(int len, const vector<int>& sums, const int k)
    {
        int n = sums.size() - 1;
        for(int left = 0; left + len - 1 < n; ++left)
        {
            int right = left + len - 1;
            int nT = sums[right + 1] - sums[left];
            if(nT <= k)
                return true;
            if(len - nT <= k)
                return true;
        }
        return false;
    }
};
