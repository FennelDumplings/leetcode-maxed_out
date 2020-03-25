// prob401: Binary Watch

/*
 * A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs on the bottom represent the minutes (0-59).
 * Each LED represents a zero or one, with the least significant bit on the right.
 * For example, the above binary watch reads "3:25".
 * Given a non-negative integer n which represents the number of LEDs that are currently on, return all possible times the
 * watch could represent.
 */

/*
 * Example:
 * Input: n = 1
 * Return: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
 */

/*
 * Note:
 * The order of output does not matter.
 * The hour must not contain a leading zero, for example "01:00" is not valid, it should be "1:00".
 * The minute must be consist of two digits and may contain a leading zero, for example "10:2" is not valid, it should be "10:02".
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> readBinaryWatch(int num) {
        vector<string> result;
        for(int i = 0; i < min(num, 4); ++i)
        {
            int j = num - i;
            for(int hour = 0; hour <= 11; ++hour)
            {
                if(_count1(hour) != i) continue;
                for(int minute = 0; minute <= 59; ++minute)
                {
                    if(_count1(minute) != j) continue;
                    string item_hour = to_string(hour);
                    string item_minute;
                    if(minute < 10)
                        item_minute = '0' + to_string(minute);
                    else
                        item_minute = to_string(minute);
                    result.push_back(item_hour + ':' + item_minute);
                }
            }
        }
        return result;
    }

private:
    int _count1(int n)
    {
        int result = 0;
        while(n)
        {
            ++result;
            n &= n - 1;
        }
        return result;
    }
};
