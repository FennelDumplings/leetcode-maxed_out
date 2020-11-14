// prob1118: Number of Days in a Month

/*
 * https://leetcode-cn.com/problems/number-of-days-in-a-month/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int numberOfDays(int Y, int M) {
        vector<int> months({31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31});
        if(is_leap_year(Y))
            months[1] = 29;
        else
            months[1] = 28;
        return months[M - 1];
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
