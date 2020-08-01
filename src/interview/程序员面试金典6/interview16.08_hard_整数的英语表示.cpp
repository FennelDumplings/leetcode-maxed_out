// interview16.08: 整数的英语表示

/*
 * https://leetcode-cn.com/problems/english-int-lcci/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string numberToWords(int num) {
        if(num == 0) return "Zero";
        vector<int> digits;
        while(num > 0)
        {
            digits.push_back(num % 10);
            num /= 10;
        }
        string word[10] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
        string word1[10] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
        string word10[10] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        int n = digits.size(); // digits 从低位到高位
        bool flag_71 = false, flag_41 = false, flag_11 = false;
        string result;
        for(int i = n - 1; i >= 0; --i)
        {
            // 9, 8, ..., 1, 0
            // 1, 4, 7 有特判
            if(i == 9)
            {
                if(digits[i] == 0) continue;
                result += word[digits[i]] + ' ';
                result += "Billion ";
            }
            else if(i == 8)
            {
                if(digits[i] == 0) continue;
                result += word[digits[i]] + ' ';
                result += "Hundred ";
            }
            else if(i == 7)
            {
                if(digits[i] == 1)
                {
                    result += word1[digits[i - 1]] + ' ';
                    flag_71 = true;
                    continue;
                }
                if(digits[i] != 0)
                    result += word10[digits[i]] + ' ';
            }
            else if(i == 6)
            {
                if(digits[i] == 0 && digits[i + 1] == 0 && digits[i + 2] == 0)
                    continue;
                if(digits[i] != 0 && !flag_71)
                    result += word[digits[i]] + ' ';
                result += "Million ";
            }
            else if(i == 5)
            {
                if(digits[i] == 0) continue;
                result += word[digits[i]] + ' ';
                result += "Hundred ";
            }
            else if(i == 4)
            {
                if(digits[i] == 1)
                {
                    result += word1[digits[i - 1]] + ' ';
                    flag_41 = true;
                    continue;
                }
                if(digits[i] != 0)
                    result += word10[digits[i]] + ' ';
            }
            else if(i == 3)
            {
                if(digits[i] == 0 && digits[i + 1] == 0 && digits[i + 2] == 0)
                    continue;
                if(digits[i] != 0 && !flag_41)
                    result += word[digits[i]] + ' ';
                result += "Thousand ";
            }
            else if(i == 2)
            {
                if(digits[i] == 0) continue;
                result += word[digits[i]] + ' ';
                result += "Hundred ";
            }
            else if(i == 1)
            {
                if(digits[i] == 1)
                {
                    result += word1[digits[i - 1]] + ' ';
                    flag_11 = true;
                    continue;
                }
                if(digits[i] != 0)
                    result += word10[digits[i]] + ' ';
            }
            else if(i == 0)
            {
                if(digits[i] != 0 && !flag_11)
                    result += word[digits[i]] + ' ';
            }
        }
        result.pop_back();
        return result;
    }
};
