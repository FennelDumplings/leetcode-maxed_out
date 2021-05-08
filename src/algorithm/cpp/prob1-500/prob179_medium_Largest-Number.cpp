// prob179: Largest Number

/*
 * Given a list of non negative integers, arrange them such that they form the largest number.
 */

/*
 * Example 1:
 * Input: [10,2]
 * Output: "210"
 * Example 2:
 * Input: [3,30,34,5,9]
 * Output: "9534330"
 */

/*
 * Note: The result may be very large, so you need to return a string instead of an integer.
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        if(nums.empty()) return "";
        int n = nums.size();
        if(n == 1) return to_string(nums[0]);
        vector<string> nums_str(n, "");
        for(int i = 0; i < n; ++i)
            nums_str[i] = to_string(nums[i]);
        sort(nums_str.begin(), nums_str.end(), dictionary_order_greater);
        if(nums_str[0] == "0") return "0";
        string result = "";
        for(string item: nums_str)
            result += item;
        return result;
    }

private:
    static bool dictionary_order_greater(const string& s1, const string& s2)
    {
        int n1 = s1.size(), n2 = s2.size();
        int i1 = 0, i2 = 0;
        while(i1 < n1 && i2 < n2)
        {
            if(s1[i1] < s2[i2])
                return false;
            else if(s1[i1] > s2[i2])
                return true;
            else
            {
                ++i1;
                ++i2;
            }
        }
        if(i1 == n1 && i2 == n2) return false;
        if(i2 == n2) return dictionary_order_greater(s1.substr(i1), s2.substr(0, i2));
        return dictionary_order_greater(s1.substr(0, i1), s2.substr(i2));
    }
};

// 比较函数可以写的更简洁
class Solution_2 {
public:
    string largestNumber(vector<int>& nums) {
        if(nums.empty()) return "";
        int n = nums.size();
        if(n == 1) return to_string(nums[0]);
        vector<string> nums_str(n, "");
        for(int i = 0; i < n; ++i)
            nums_str[i] = to_string(nums[i]);
        sort(nums_str.begin(), nums_str.end(), dictionary_order_greater);
        if(nums_str[0] == "0") return "0";
        string result = "";
        for(string item: nums_str)
            result += item;
        return result;
    }

private:
    static bool dictionary_order_greater(const string& s1, const string& s2)
    {
        return s1 + s2 > s2 + s1;
    }
};
