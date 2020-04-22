// prob402: Remove K Digits

/*
 * Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.
 * Note:
 * The length of num is less than 10002 and will be ≥ k.
 * The given num does not contain any leading zero.
 */

/*
 * Example 1:
 * Input: num = "1432219", k = 3
 * Output: "1219"
 * Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
 * Example 2:
 * Input: num = "10200", k = 1
 * Output: "200"
 * Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
 * Example 3:
 * Input: num = "10", k = 2
 * Output: "0"
 * Explanation: Remove all the digits from the number and it is left with nothing which is 0.
 */

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    string removeKdigits(string num, int k) {
        int n = num.size();
        if(n == k) return "0";

        vector<vector<int> > digit_idxs(10, vector<int>());
        for(int i = 0; i <= n - 1; ++i)
            digit_idxs[num[i] - '0'].push_back(i);
        unordered_set<int> delete_idxs;

        int left = 0, right = n - 1, cur_min = 0;
        removeKdigits(num, digit_idxs, left, right, k, delete_idxs, cur_min);

        string result;
        for(int i = 0; i < n; ++i)
        {
            if(delete_idxs.find(i) != delete_idxs.end() || (result.empty() && num[i] == '0'))
                continue;
            result += num[i];
        }
        if(result.empty()) result = "0";
        return result;
    }

private:
    void _removeKdigits(const string& num, vector<vector<int> > digit_idxs, int left, int right, int k, unordered_set<int>& delete_idxs, int cur_min)
    {
        if(k == 0) return;
        // right - left + 1 > k
        if((int)digit_idxs[cur_min].size() >= k)
        {
            for(int idx = left; idx <= right; ++idx)
            {
                if(num[idx] - '0' > cur_min)
                {
                    delete_idxs.insert(idx);
                    --k;
                }
            }
        }
        for(int digit = cur_min; digit <= 9; ++digit)
        {
            if(digit_idxs[digit].empty()) continue;
            digit_idxs.push_back()
            for(int i = 1; i < (int)digit_idxs[digit].size(); ++i)
            {
                int r = digit_idxs[digit][i];
                int l = digit_idxs[digit][i - 1];
                if(1 > r - l - 1) continue;
                if(r - l - 1 <= k)
                {
                    for(int j = l + 1; j <= r - 1; ++j)
                    {
                        //if(delete_idxs.find(j) == delete_idxs.end())
                        if(delete_idxs.find(j) == delete_idxs.end() && num[j] > digit)
                        {
                            delete_idxs.insert(j);
                            --k;
                            if(k == 0) return;
                        }
                    }
                }
                else
                {
                    _removeKdigits(num, l + 1, r - 1, k, delete_idxs, digit);
                    if(k == 0) return;
                }
            }
        }
    }
};
