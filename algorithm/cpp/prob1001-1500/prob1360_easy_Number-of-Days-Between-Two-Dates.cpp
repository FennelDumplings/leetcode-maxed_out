// prob1360: Number of Days Between Two Dates

/*
 * https://leetcode-cn.com/problems/number-of-days-between-two-dates/
 */

#include <string>
#include <vector>
#include <sstream>

using namespace std;

bool is_leap_year(int year)
{
    // 四年一闰,百年不闰,四百年再闰
    if(year % 4 != 0)
        return false;
    if(year % 100 == 0 && year % 400 != 0)
        return false;
    return true;
}

bool lessthan(int y1, int m1, int d1, int y2, int m2, int d2)
{
    if(y1 == y2)
    {
        if(m1 == m2)
            return d1 < d2;
        return m1 < m2;
    }
    return y1 < y2;
}

void get_ymd(const string& date, int& y, int& m, int& d)
{
    stringstream ss;
    ss << date.substr(0, 4) + ' ';
    ss << date.substr(5, 2) + ' ';
    ss << date.substr(8, 2);
    ss >> y;
    ss >> m;
    ss >> d;
}

int day_of_year(int y, int m, int d)
{
    vector<int> months({31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31});
    if(is_leap_year(y))
        months[1] = 29;
    else
        months[1] = 28;
    int ans = 0;
    for(int i = 1; i < m; ++i)
        ans += months[i - 1];
    ans += d;
    return ans;
}

class Solution {
public:
    int daysBetweenDates(string date1, string date2) {
        int y1, m1, d1;
        get_ymd(date1, y1, m1, d1);
        int y2, m2, d2;
        get_ymd(date2, y2, m2, d2);
        if(!lessthan(y1, m2, d1, y2, m2, d2))
        {
            swap(y1, y2);
            swap(m1, m2);
            swap(d1, d2);
        }
        int day1 = day_of_year(y1, m1, d1);
        int day2 = day_of_year(y2, m2, d2);
        if(y1 == y2)
            return day2 - day1;
        // y1 < y2
        int ans = 365 - day1;
        if(is_leap_year(y1))
            ++ans;
        ans += day2;
        for(int y = y1 + 1; y < y2; ++y)
        {
            ans += 365;
            if(is_leap_year(y))
                ++ans;
        }
        return ans;
    }
};
