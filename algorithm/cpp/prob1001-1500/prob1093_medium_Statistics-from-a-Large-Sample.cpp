// prob1093: Statistics from a Large Sample

/*
 * We sampled integers between 0 and 255, and stored the results in an array count:  count[k] is the number of integers we sampled equal to k.
 *
 * Return the minimum, maximum, mean, median, and mode of the sample respectively, as an array of floating point numbers.  The mode is guaranteed to be unique.
 *
 * (Recall that the median of a sample is:
 *
 * The middle element, if the elements of the sample were sorted and the number of elements is odd;
 * The average of the middle two elements, if the elements of the sample were sorted and the number of elements is even.)
 */

/*
 * Example 1:
 *
 * Input: count = [0,1,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 * Output: [1.00000,3.00000,2.37500,2.50000,3.00000]
 * Example 2:
 *
 * Input: count = [0,4,3,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 * Output: [1.00000,4.00000,2.18182,2.00000,1.00000]
 */

/*
 * Constraints:
 *
 * count.length == 256
 * 1 <= sum(count) <= 10^9
 * The mode of the sample that count represents is unique.
 * Answers within 10^-5 of the true value will be accepted as correct.
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<double> sampleStats(vector<int>& count) {
        using ll = long long;
        int maxx = -1, minx = 256;
        ll sum = 0;
        ll all_cnt = 0;
        int max_cnt = 0;
        int majority = -1;
        vector<int> nums;
        for(int i = 0; i <= 255; ++i)
        {
            if(count[i] == 0) continue;
            nums.push_back(i);
            maxx = i;
            if(minx == 256)
                minx = i;
            sum += (ll)count[i] * i;
            all_cnt += count[i];
            if(count[i] > max_cnt)
            {
                max_cnt = count[i];
                majority = i;
            }
        }
        if(maxx == -1) return {}; // count 全零
        vector<double> result(5);
        result[0] = (double)minx;
        result[1] = (double)maxx;
        result[2] = (double)sum / all_cnt;
        result[4] = (double)majority;
        // 1,2,3,4,5 -> 3
        // 1,2,3,4,5,6 -> 3;
        ll idx = (all_cnt + 1) / 2;
        ll iter = 0;
        for(int k = 0; k < (int)nums.size(); ++k)
        {
            int i = nums[k];
            iter += count[i];
            if(iter >= idx)
            {
                if(all_cnt & 1 || iter > idx)
                {
                    result[3] = (double)i;
                    break;
                }
                else
                {
                    result[3] = ((double)nums[k + 1] + i) / 2;
                    break;
                }
            }
        }
        return result;
    }
};
