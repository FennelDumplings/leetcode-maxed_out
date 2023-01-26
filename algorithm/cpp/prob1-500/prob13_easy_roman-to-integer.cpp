// Prob13 Roman to Integer

/* Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
 *
 * Symbol       Value
 * I             1
 * V             5
 * X             10
 * L             50
 * C             100
 * D             500
 * M             1000
 *
 * For example, two is written as II in Roman numeral, just two one's added together.
 * Twelve is written as, XII, which is simply X + II. The number twenty seven is written
 * as XXVII, which is XX + V + II.
 *
 * Roman numerals are usually written largest to smallest from left to right. However,
 * the numeral for four is not IIII. Instead, the number four is written as IV. Because
 * the one is before the five we subtract it making four. The same principle applies to
 * the number nine, which is written as IX. There are six instances where subtraction is used:
 *
 * I can be placed before V (5) and X (10) to make 4 and 9.
 * X can be placed before L (50) and C (100) to make 40 and 90.
 * C can be placed before D (500) and M (1000) to make 400 and 900.
 * Given a roman numeral, convert it to an integer. Input is guaranteed to be within the range from 1 to 3999
 */

/* Examples:
 * Example 1:
 * Input: "III"
 * Output: 3
 *
 * Example 2:
 * Input: "IV"
 * Output: 4
 *
 * Example 3:
 * Input: "IX"
 * Output: 9
 *
 * Example 4:
 * Input: "LVIII"
 * Output: 58
 * Explanation: L = 50, V= 5, III = 3.
 *
 * Example 5:
 * Input: "MCMXCIV"
 * Output: 1994
 * Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        if(s.empty()) return 0;
        vector<string> romans = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        vector<int> nums = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

        int n = s.size();
        int j = 0;
        int result = 0;
        for(int i = 0; i < 13; ++i)
        {
            string roman = romans[i];
            int m = roman.size();
            int num = nums[i];
            while(beginwithstr(s, j, roman))
            {
                result += num;
                j += m;
            }
            if(j >= n) break;
        }
        return result;
    }

private:
    bool beginwithstr(const string& s, int start, const string& target)
    {
        int n = s.size();
        int m = target.size();
        for(int i = 0; i < m; ++i)
            if(start + i >= n || s[start + i] != target[i])
                return false;
        return true;
    }
};


class Solution_old {
public:
    int romanToInt(string s) {
        string::iterator iter1 = s.begin();
        string::iterator iter2 = s.begin();
        int result = 0;
        while(iter1 != s.end())
        {
            string segment;
            iter2 = iter1 + 1;
            if(*iter1 == 'I')
            {
                if(iter2 != s.end() && *iter2 == 'V')
                {
                    segment = string(iter1, iter2 + 1);
                    ++iter1;
                    ++iter1;
                }
                else if(iter2 != s.end() && *iter2 == 'X')
                {
                    segment = string(iter1, iter2 + 1);
                    ++iter1;
                    ++iter1;
                }
                else
                {
                    segment = string(iter1, iter2);
                    ++iter1;
                }
            }
            else if(*iter1 == 'X')
            {
                if(iter2 != s.end() && *iter2 == 'L')
                {
                    segment = string(iter1, iter2 + 1);
                    ++iter1;
                    ++iter1;
                }
                else if(iter2 != s.end() && *iter2 == 'C')
                {
                    segment = string(iter1, iter2 + 1);
                    ++iter1;
                    ++iter1;
                }
                else
                {
                    segment = string(iter1, iter2);
                    ++iter1;
                }
            }
            else if(*iter1 == 'C')
            {
                if(iter2 != s.end() && *iter2 == 'D')
                {
                    segment = string(iter1, iter2 + 1);
                    ++iter1;
                    ++iter1;
                }
                else if(iter2 != s.end() && *iter2 == 'M')
                {
                    segment = string(iter1, iter2 + 1);
                    ++iter1;
                    ++iter1;
                }
                else
                {
                    segment = string(iter1, iter2);
                    ++iter1;
                }
            }
            else
            {
                segment = string(iter1, iter2);
                ++iter1;
            }
            result += mapping[segment];
        }
        return result;
    }

    Solution()
    {
        mapping.insert(pair<string, int>("M", 1000));
        mapping.insert(pair<string, int>("C", 100));
        mapping.insert(pair<string, int>("D", 500));
        mapping.insert(pair<string, int>("CD", 400));
        mapping.insert(pair<string, int>("CM", 900));
        mapping.insert(pair<string, int>("X", 10));
        mapping.insert(pair<string, int>("L", 50));
        mapping.insert(pair<string, int>("XL", 40));
        mapping.insert(pair<string, int>("XC", 90));
        mapping.insert(pair<string, int>("I", 1));
        mapping.insert(pair<string, int>("V", 5));
        mapping.insert(pair<string, int>("IV", 4));
        mapping.insert(pair<string, int>("IX", 9));
    }

private:
    unordered_map<string, int> mapping;
/*
 * 千位: M
 * MMM, MM, M
 * 百位: C, D, CD, CM
 * CM, DCCC, DCC, DC, D, CD, CCC, CC, C
 * 十位: X, L, XL, XC
 * XC, LXXX, LXX, LX, L, XL, XXX, XX, X
 * 个位: I, V, IV, IX
 * IX, VIII, VII, VI, V, IV, III, II, I
 */
};


int main()
{
    string roman;
    cout << "input roman: " << endl;
    cin >> roman;

    Solution solution;
    int result;
    result = solution.romanToInt(roman);
    cout << result << endl;
}
