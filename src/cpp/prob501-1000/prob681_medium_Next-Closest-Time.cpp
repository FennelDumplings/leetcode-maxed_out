// prob681: Next Closest Time

/*
 * https://leetcode-cn.com/problems/next-closest-time/
 */

#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>

using namespace std;

void get_hm(const string& s, int& h, int& m)
{
    stringstream ss;
    ss << s.substr(0, 2) + ' ';
    ss << s.substr(3);
    ss >> h;
    ss >> m;
}

void get_digits(int num, unordered_set<int>& digits)
{
    if(num < 10)
        digits.insert(0);
    while(num)
    {
        digits.insert(num % 10);
        num /= 10;
    }
}

const int H = 60 * 24;

int get_dist(int start, int nxt)
{
    if(start >= nxt)
        nxt += H;
    return nxt - start;
}


class Solution {
public:
    string nextClosestTime(string time) {
        int h, m;
        get_hm(time, h, m);

        digits = unordered_set<int>();
        get_digits(h, digits);
        get_digits(m, digits);

        vector<int> cands = nxt_cands();

        int start = h * 60 + m;
        int ans = -1;
        int min_dist = H + 1;
        for(int nxt: cands)
        {
            int dist = get_dist(start, nxt);
            if(dist < min_dist)
            {
                min_dist = dist;
                ans = nxt;
            }
        }

        if(ans == -1) return "-1";
        int ans_h = ans / 60;
        string str_h = to_string(ans_h);
        if(str_h.size() == 1)
            str_h = '0' + str_h;
        int ans_m = ans % 60;
        string str_m = to_string(ans_m);
        if(str_m.size() == 1)
            str_m = '0' + str_m;
        string result = str_h + ':' + str_m;
        return result;
    }

private:
    unordered_set<int> digits;

    vector<int> nxt_cands()
    {
        vector<int> cands;
        for(int hi: digits)
            for(int hj: digits)
            {
                int h = hi * 10 + hj;
                if(h >= 24) continue;
                for(int mi: digits)
                    for(int mj: digits)
                    {
                        int m = mi * 10 + mj;
                        if(m >= 60) continue;
                        cands.push_back(h * 60 + m);
                    }
            }
        return cands;
    }
};
