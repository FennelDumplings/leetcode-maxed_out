// prob248: Strobogrammatic Number III

/*
 * A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
 * Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high.
 */

/*
 * Example:
 * Input: low = "50", high = "100"
 * Output: 3
 * Explanation: 69, 88, and 96 are three strobogrammatic numbers.
 */

/*
 * Note:
 * Because the range might be a large number, the low and high numbers are represented as string.
 */

#include <string>
#include <vector>

using namespace std;


class Solution {
public:
    int strobogrammaticInRange(string low, string high) {
        int min_len = low.size(), max_len = high.size();
        int result = 0;
        string item;
        for(int len = min_len; len <= max_len; ++len)
        {
            int left = 0, right = len - 1;
            item.assign(len, '0');
            dfs(left, right, len, low, high, result, item);
        }
        return result;
    }

private:
    vector<char> chars = {'0','1','6','8','9'};
    vector<char> chars_reverse = {'0','1','9','8','6'};

    void dfs(int left, int right, int len, const string& low, const string& high, int& result, string& item)
    {
        int min_len = low.size(), max_len = high.size();

        if(left > right)
        {
            if((len > min_len || item >= low) && (len < max_len || item <= high))
            ++result;
            return;
        }

        if(left == right)
        {
            for(char ch: vector<char>{'0', '1', '8'})
            {
                item[left] = ch;
                if((len > min_len || item >= low) && (len < max_len || item <= high))
                    ++result;
                item[left] = '0';
            }
            return;
        }

        // left < right
        for(int i = 0; i < (int)chars.size(); ++i)
        {
            char ch = chars[i];
            if(left == 0 && ch == '0') continue;
            item[left] = ch;
            item[right] = chars_reverse[i];
            dfs(left + 1, right - 1, len, low, high, result, item);
            item[left] = '0';
            item[right] = '0';
        }
    }
};
