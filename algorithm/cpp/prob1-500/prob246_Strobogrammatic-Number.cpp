// prob246: Strobogrammatic Number

/*
 * A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
 * Write a function to determine if a number is strobogrammatic. The number is represented as a string.
 */

/*
 * Example 1:
 * Input:  "69"
 * Output: true
 * Example 2:
 * Input:  "88"
 * Output: true
 * Example 3:
 * Input:  "962"
 * Output: false
 */

#include <string>

using namespace std;

class Solution {
public:
    bool isStrobogrammatic(string num) {
        int n = num.size();
        int left = 0, right = n - 1;
        while(left < right)
        {
            if(num[left] == '6' && num[right] == '9')
            {
                ++left;
                --right;
            }
            else if(num[left] == '9' && num[right] == '6')
            {
                ++left;
                --right;
            }
            else if(num[left] == '8' && num[right] == '8')
            {
                ++left;
                --right;
            }
            else if(num[left] == '1' && num[right] == '1')
            {
                ++left;
                --right;
            }
            else if(num[left] == '0' && num[right] == '0')
            {
                ++left;
                --right;
            }
            else
                return false;
        }
        if(left == right)
        {
            if(num[left] == '8' || num[left] == '1' || num[left] == '0')
                return true;
            else
                return false;
        }
        return true;
    }
};
