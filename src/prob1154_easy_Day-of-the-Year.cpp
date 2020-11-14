// prob1154: Day of the Year

/*
 * Given a string date representing a Gregorian calendar date formatted as YYYY-MM-DD, return the day number of the year.
 */

/*
 * Example 1:
 * Input: date = "2019-01-09"
 * Output: 9
 * Explanation: Given date is the 9th day of the year in 2019.
 * Example 2:
 * Input: date = "2019-02-10"
 * Output: 41
 * Example 3:
 * Input: date = "2003-03-01"
 * Output: 60
 * Example 4:
 * Input: date = "2004-03-01"
 * Output: 61
 */

/*
 * Constraints:
 * date.length == 10
 * date[4] == date[7] == '-', and all other date[i]'s are digits
 * date represents a calendar date between Jan 1st, 1900 and Dec 31, 2019.
 */

#include <string>
#include <vector>
#include <sstream>

using namespace std;


class Solution {
public:
    int dayOfYear(string date) {
        int y, m, d;
        stringstream ss;
        ss << date.substr(0, 4) + ' ';
        ss << date.substr(5, 2) + ' ';
        ss << date.substr(8, 2);
        ss >> y;
        ss >> m;
        ss >> d;
        vector<int> months({31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31});
        if(is_leap_year(y))
            months[1] = 29;
        else
            months[1] = 28;
        int result = 0;
        for(int i = 1; i < m; ++i)
            result += months[i - 1];
        result += d;
        return result;
    }

private:
    bool is_leap_year(int year)
    {
        // 四年一闰,百年不闰,四百年再闰
        if(year % 4 != 0)
            return false;
        if(year % 100 == 0 && year % 400 != 0)
            return false;
        return true;
    }
};
