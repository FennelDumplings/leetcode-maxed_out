// prob1231: Divide Chocolate

/*
 * You have one chocolate bar that consists of some chunks. Each chunk has its own sweetness given by the array sweetness.
 * You want to share the chocolate with your K friends so you start cutting the chocolate bar into K+1 pieces using K cuts, each piece consists of some consecutive chunks.
 * Being generous, you will eat the piece with the minimum total sweetness and give the other pieces to your friends.
 * Find the maximum total sweetness of the piece you can get by cutting the chocolate bar optimally.
 */

/*
 * Example 1:
 * Input: sweetness = [1,2,3,4,5,6,7,8,9], K = 5
 * Output: 6
 * Explanation: You can divide the chocolate to [1,2,3], [4,5], [6], [7], [8], [9]
 * Example 2:
 * Input: sweetness = [5,6,7,8,9,1,2,3,4], K = 8
 * Output: 1
 * Explanation: There is only one way to cut the bar into 9 pieces.
 * Example 3:
 * Input: sweetness = [1,2,2,1,2,2,1,2,2], K = 2
 * Output: 5
 * Explanation: You can divide the chocolate to [1,2,2], [1,2,2], [1,2,2]
 */

#include <vector>

using namespace std;

class Solution {
public:
    int maximizeSweetness(vector<int>& sweetness, int K) {
        int n = sweetness.size();
        int minx = sweetness[0], sum = sweetness[0];
        for(int i = 1; i < n; ++i)
        {
            sum += sweetness[i];
            minx = min(minx, sweetness[i]);
        }
        int left = minx, right = sum;
        while(left < right)
        {
            int mid = (left + right + 1) / 2;
            int cnt = cut(sweetness, mid);
            if(cnt >= K + 1)
                left = mid;
            else
                right = mid - 1;
        }
        return left;
    }

private:
    int cut(const vector<int>& sweetness, int x)
    {
        int n = sweetness.size();
        int left = 0;
        int cnt = 0;
        while(left < n)
        {
            int right = left;
            int sum = 0;
            while(right < n && sum < x)
            {
                sum += sweetness[right];
                ++right;
            }
            if(sum >= x)
                ++cnt;
            left = right;
        }
        return cnt;
    }
};
