// prob247: Strobogrammatic Number II

/*
 * A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
 * Find all strobogrammatic numbers that are of length = n.
 */

/*
 * Example:
 * Input:  n = 2
 * Output: ["11","69","88","96"]
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> findStrobogrammatic(int n) {
        vector<string> result;
        int left = 0, right = n - 1;
        string item(n, '#');
        dfs(left, right, item, result);
        return result;
    }
private:
    void  dfs(int left, int right, string& item, vector<string>& result)
    {
        if(left > right)
        {
            result.push_back(item);
            return;
        }
        if(left == right)
        {
            for(char ch: vector<char>{'1', '0', '8'})
            {
                item[left] = ch;
                result.push_back(item);
            }
            return;
        }
        // left < right
        item[left] = '6';
        item[right] = '9';
        dfs(left + 1, right - 1, item, result);
        item[left] = '9';
        item[right] = '6';
        dfs(left + 1, right - 1, item, result);
        for(char ch: vector<char>{'1', '0', '8'})
        {
            if(left == 0 && ch == '0') continue;
            item[left] = ch;
            item[right] = ch;
            dfs(left + 1, right - 1, item, result);
        }
    }
};
