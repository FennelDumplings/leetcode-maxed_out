// prob949: Largest Time for Given Digits

/*
 * https://leetcode-cn.com/problems/largest-time-for-given-digits/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string largestTimeFromDigits(vector<int>& arr) {
        int h = -1, m = -1;
        for(int i = 0; i < 4; ++i)
        {
            int hour1 = arr[i];
            for(int j = 0; j < 4; ++j)
            {
                if(i == j)
                    continue;
                int hour2 = arr[j];
                int cur_hour = hour1 * 10 + hour2;
                if(cur_hour < 24 && cur_hour > h)
                {
                    int minute = -1;
                    for(int k = 0; k < 4; ++k)
                    {
                        if(k == i || k == j)
                            continue;
                        int minute1 = arr[k];
                        for(int l = 0; l < 4; ++l)
                        {
                            if(l == k || l == i || l == j)
                                continue;
                            int minute2 = arr[l];
                            int cur_minute = minute1 * 10 + minute2;
                            if(cur_minute < 60 && cur_minute > minute)
                                minute = cur_minute;
                        }
                    }
                    if(minute != -1)
                    {
                        h = cur_hour;
                        m = minute;
                    }
                }
            }
        }
        if(h == -1)
            return "";
        string h_str = to_string(h);
        if((int)h_str.size() < 2)
            h_str = '0' + h_str;
        string m_str = to_string(m);
        if((int)m_str.size() < 2)
            m_str = '0' + m_str;
        return h_str + ':' + m_str;
    }
};
