#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    string nearestPalindromic(string n) {
        int len = n.size();
        int i = 0, j = len - 1;
        bool flag = false;
        while(i < j)
        {
            if(n[i] == n[j])
                continue;
            flag = true;
            result[j] = n[i];
            ++i;
            --j;
        }
        if(i == j)
        {
            if(flag)
                return result;
            string result1 = result;
            string result2 = result;
            result1[i] = n[i] - 1;
            result2[i] = n[i] + 1;
            if(diff(n, result1) <= diff(n, result2))
                return result1;
            else
                return result2;
        }
        else
        {
            // j, i
        }
    }

private:
    int get_diff(string& a, string& b)
    {
        int len = a.size();
        int diff = 0;
        for(int i = 0; i < len; ++i)
        {
            diff *= 10;
            diff += abs((a[i] - '0') - (b[i] - '0'));
        }
        return diff;
    }
};
