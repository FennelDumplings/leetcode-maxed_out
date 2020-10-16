// prob1185: Day of the Week

/*
 * https://leetcode-cn.com/problems/day-of-the-week/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string dayOfTheWeek(int day, int month, int year) {
        vector<int> months = {
            31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
        };
        vector<string> result = {
            "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
        };
        if(is_leap_year(year))
            months[1] = 29;
        else
            months[1] = 28;
        int iter = s_ans - 1;
        for(int y = s_year; y < year; ++y)
        {
            if(is_leap_year(y))
                iter = (iter + 366) % 7;
            else
                iter = (iter + 365) % 7;
        }
        for(int m = s_month; m < month; ++m)
        {
            iter = (iter + months[m - 1]) % 7;
        }
        iter = (iter + day) % 7;
        return result[iter];
    }

private:
    const int s_year = 1971;
    const int s_month = 1;
    const int s_day = 1;
    const int s_ans = 4;

    bool is_leap_year(int year)
    {
        if(year % 400 == 0)
            return true;
        if(year % 100 == 0)
            return false;
        return year % 4 == 0;
    }
};
