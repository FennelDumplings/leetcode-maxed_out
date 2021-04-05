
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool robot(string command, vector<vector<int>>& obstacles, int x, int y) {
        nU = 0, nR = 0;
        for(const char& ch: command)
        {
            if(ch == 'U')
            {
                mapping.push_back(nR);
                ++nU;
            }
            else
                ++nR;
        }
        mapping.push_back(nR);
        if(!check(x, y))
            return false;
        for(vector<int> o: obstacles)
        {
            if(o[0] <= x && o[1] <= y && check(o[0], o[1]))
                return false;
        }
        return true;
    }

private:
    vector<int> mapping; // mapping[i] := command 前缀中第 i+1 个 U 之前最多有多少个 R
    int nU, nR; // command 中 U 的个数，R 的个数
    bool check(int x0, int y0)
    {
        int n_total = y0 / nU;
        int y = y0 - n_total * nU;
        int x = x0 - n_total * nR;
        if(y == 0 && x < 0)
            return base_check(x + nR, y + nU);
        return base_check(x, y);
    }

    bool base_check(int x0, int y0)
    {
        // 0 <= y0 <= nU
        int right = mapping[y0];
        int left = 0;
        if(y0 > 0)
            left = mapping[y0 - 1];
        if(left <= x0 && x0 <= right)
            return true;
        else
            return false;
    }
};
