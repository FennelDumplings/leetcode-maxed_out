// prob164: Maximum Gap

/*
 * Given an unsorted array, find the maximum difference between the successive elements in its sorted form.
 * Return 0 if the array contains less than 2 elements.
 */

/*
 * Example 1:
 * Input: [3,6,9,1]
 * Output: 3
 * Explanation: The sorted form of the array is [1,3,6,9], either
 *              (3,6) or (6,9) has the maximum difference 3.
 * Example 2:
 * Input: [10]
 * Output: 0
 * Explanation: The array contains less than 2 elements, therefore return 0.
 */

/*
 * Note:
 * You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.
 * Try to solve it in linear time/space.
 */

#include <vector>
#include <climits>

using namespace std;

// 桶排序
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if(n < 2) return 0;
        int MAX = INT_MIN, MIN = INT_MAX;
        for(int num: nums)
        {
            MAX = max(MAX, num);
            MIN = min(MIN, num);
        }
        if(MAX - MIN == 0) return 0;
        int b = max(1, (MAX - MIN) / (n - 1)); // 桶宽下取整
        int nb = 1 + (MAX - MIN) / b; // 桶个数上取整
        // int nb = ceil((double)(MAX - MIN) / b); // 桶个数上取整
        vector<Bucket> buckets(nb, Bucket());
        // 第 i 个桶的取值范围 [MIN + i * b, MIN + (i + 1) * b)
        // i = 0 .. nb - 1 (共 nb 个桶)
        // 给定 val 的桶 id: bucket_id = (val - MIN) / b 下取整
        for(int num: nums)
        {
            int bucket_id = (num - MIN) / b;
            buckets[bucket_id].maxx = max(buckets[bucket_id].maxx, num);
            buckets[bucket_id].minx = min(buckets[bucket_id].minx, num);
            buckets[bucket_id].used = true;
        }
        int result = 0;
        int iter = 0;
        int prev_max = 0;
        while(iter < nb && !buckets[iter].used)
            ++iter;
        if(iter == nb) return result;
        prev_max = buckets[iter].maxx;
        while(iter < nb)
        {
            while(iter < nb && !buckets[iter].used)
                ++iter;
            if(iter == nb) break;
            result = max(result, buckets[iter].minx - prev_max);
            prev_max = buckets[iter].maxx;
            ++iter;
        }
        return result;
    }

private:
    struct Bucket {
        int maxx;
        int minx;
        bool used;
        Bucket():maxx(INT_MIN), minx(INT_MAX), used(false){}
    };
};
