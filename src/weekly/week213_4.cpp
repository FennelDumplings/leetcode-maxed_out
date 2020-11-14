
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string kthSmallestPath(vector<int>& destination, int k) {
        int n = destination[0], m = destination[1];
        // n + 1 个 V，m + 1 个 H
        int kV = n, kH = m;
        c = vector<vector<int>>(kV + kH + 1, vector<int>(kH + 1, 0));
        preprocess(kV + kH, kH);
        string result;
        int remain = kV + kH;
        int kh = kH;
        for(int i = 0; i < kV + kH; ++i)
        {
            // 当前放 H 型成的前缀对应的串数目
            if(remain == kh)
            {
                result += string(remain, 'H');
                break;
            }
            if(kh == 0)
            {
                result += string(remain, 'V');
                break;
            }
            int cnt_H = c[remain - 1][kh - 1];
            if(cnt_H >= k)
            {
                result += 'H';
                --kh;
            }
            else
            {
                result += 'V';
                k -= cnt_H;
            }
            --remain;
        }
        return result;
    }

private:
    vector<vector<int>> c;

    void preprocess(int n, int m)
    {
        for(int i = 0; i <= n; ++i)
            c[i][0] = 1;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= min(i, m); ++j)
                c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]);
    }
};
