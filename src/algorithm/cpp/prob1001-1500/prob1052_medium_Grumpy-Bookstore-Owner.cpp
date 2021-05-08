// prob1052: Grumpy Bookstore Owner

/*
 * https://leetcode-cn.com/problems/grumpy-bookstore-owner/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int X) {
        int n = customers.size();
        int sum = 0;
        int sum0 = 0;
        for(int i = 0; i < X; ++i)
        {
            if(grumpy[i] == 1)
                sum += customers[i];
            else
                sum0 += customers[i];
        }
        int max_x = sum;
        for(int i = X; i < n ; ++i)
        {
            if(grumpy[i - X] == 1)
                sum -= customers[i - X];
            if(grumpy[i] == 1)
                sum += customers[i];
            else
                sum0 += customers[i];
            max_x = max(max_x, sum);
        }
        return max_x + sum0;
    }
};
