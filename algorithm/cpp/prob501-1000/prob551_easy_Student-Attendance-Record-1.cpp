// prob551: Student Attendance Record I

/*
 * https://leetcode-cn.com/problems/student-attendance-record-i/
 */

#include <string>

using namespace std;

class Solution {
public:
    bool checkRecord(string s) {
        if(s.empty()) return true;
        int n = s.size();
        int cnt = 0;
        int left = 0;
        while(left < n)
        {
            if(s[left] == 'A')
            {
                ++cnt;
                if(cnt > 1)
                    return false;
                ++left;
            }
            else if(s[left] == 'L')
            {
                int right = left + 1;
                while(right < n && s[right] == 'L')
                    ++right;
                if(right - left > 2)
                    return false;
                left = right;
            }
            else
                ++left;
        }
        return true;
    }
};
