// prob1616: Split Two Strings to Make Palindrome

/*
 * https://leetcode-cn.com/problems/split-two-strings-to-make-palindrome/
 */

#include <string>

using namespace std;

class Solution {
public:
    bool checkPalindromeFormation(string a, string b) {
        return check(a, b) || check(b, a);
    }

private:
    bool check(const string& a, const string& b)
    {
        int n = a.size();
        // 从 a 中心扩散，直至不能扩散的位置 idx : a[idx] != a[n - 1 - idx]
        // b.substr(0, idx + 1) + a.substr(idx + 1)
        // a.substr(0, n - 1 - idx) + b.substr(n - 1 - idx)
        int idx = n / 2 - 1;
        while(idx >= 0 && a[idx] == a[n - 1 - idx])
            --idx;
        if(idx == -1)
            return true;
        int iter = idx;
        while(iter >= 0 && b[iter] == a[n - 1 - iter])
            --iter;
        if(iter == -1)
            return true;
        iter = idx;
        while(iter >= 0 && a[iter] == b[n - 1 - iter])
            --iter;
        if(iter == -1)
            return true;
        return false;
    }
};
