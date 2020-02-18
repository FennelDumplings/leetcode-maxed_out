// prob12: Integer to Roman

/*
 * Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
 * Symbol       Value
 * I             1
 * V             5
 * X             10
 * L             50
 * C             100
 * D             500
 * M             1000
 * For example, two is written as II in Roman numeral, just two one's added together.
 * Twelve is written as, XII, which is simply X + II.
 * The number twenty seven is written as XXVII, which is XX + V + II.
 *
 * Roman numerals are usually written largest to smallest from left to right.
 * However, the numeral for four is not IIII. Instead, the number four is written as IV.
 * Because the one is before the five we subtract it making four.
 * The same principle applies to the number nine, which is written as IX.
 * There are six instances where subtraction is used:
 *
 * I can be placed before V (5) and X (10) to make 4 and 9.
 * X can be placed before L (50) and C (100) to make 40 and 90.
 * C can be placed before D (500) and M (1000) to make 400 and 900.
 * Given an integer, convert it to a roman numeral. Input is guaranteed to be within the range from 1 to 3999.
 */

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        string result = "";
        int iter = 0;
        if(num == 0) return  result;

        iter = num % 10;
        result = mapping_1[iter] + result;
        num /= 10;
        if(num == 0) return result;

        iter = num % 10;
        result = mapping_2[iter] + result;
        num /= 10;
        if(num == 0) return result;

        iter = num % 10;
        result = mapping_3[iter] + result;
        num /= 10;
        if(num == 0) return result;

        iter = num % 10;
        result = mapping_4[iter] + result;
        num /= 10;
        return result;
    }

private:
    unordered_map<int, string> mapping_1 = {
        pair<int, string>(0, ""),
        pair<int, string>(1, "I"),
        pair<int, string>(2, "II"),
        pair<int, string>(3, "III"),
        pair<int, string>(4, "IV"),
        pair<int, string>(5, "V"),
        pair<int, string>(6, "VI"),
        pair<int, string>(7, "VII"),
        pair<int, string>(8, "VIII"),
        pair<int, string>(9, "IX")
    };
    unordered_map<int, string> mapping_2 = {
        pair<int, string>(0, ""),
        pair<int, string>(1, "X"),
        pair<int, string>(2, "XX"),
        pair<int, string>(3, "XXX"),
        pair<int, string>(4, "XL"),
        pair<int, string>(5, "L"),
        pair<int, string>(6, "LX"),
        pair<int, string>(7, "LXX"),
        pair<int, string>(8, "LXXX"),
        pair<int, string>(9, "XC")
    };
    unordered_map<int, string> mapping_3 = {
        pair<int, string>(0, ""),
        pair<int, string>(1, "C"),
        pair<int, string>(2, "CC"),
        pair<int, string>(3, "CCC"),
        pair<int, string>(4, "CD"),
        pair<int, string>(5, "D"),
        pair<int, string>(6, "DC"),
        pair<int, string>(7, "DCC"),
        pair<int, string>(8, "DCCC"),
        pair<int, string>(9, "CM")
    };
    unordered_map<int, string> mapping_4 = {
        pair<int, string>(0, ""),
        pair<int, string>(1, "M"),
        pair<int, string>(2, "MM"),
        pair<int, string>(3, "MMM"),
    };
};

// 思想类似于给钱的时候尽量先给大面值的
class Solution_2 {
public:
    string intToRoman(int num) {
        // 把阿拉伯数字与罗马数字可能出现的所有情况和对应关系，放在两个数组中
        // 并且按照阿拉伯数字的大小降序排列，这是贪心选择思想
        vector<int> nums = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        vector<string> romans = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

        string result = "";
        int index = 0;
        while (index < 13) {
            // 13种面值
            // 特别注意：这里是等号
            while (num >= nums[index]) {
                // 注意：这里是等于号，表示尽量使用大的"面值"
                result += romans[index];
                num -= nums[index];
            }
            index++;
        }
        return result;
    }
};
