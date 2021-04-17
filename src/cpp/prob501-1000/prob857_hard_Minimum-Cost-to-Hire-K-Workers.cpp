// prob857: Minimum Cost to Hire K Workers

/*
 * There are N workers.  The i-th worker has a quality[i] and a minimum wage expectation wage[i].
 * Now we want to hire exactly K workers to form a paid group.  When hiring a group of K workers,
 * we must pay them according to the following rules:
 * Every worker in the paid group should be paid in the ratio of their quality compared to other workers in the paid group.
 * Every worker in the paid group must be paid at least their minimum wage expectation.
 * Return the least amount of money needed to form a paid group satisfying the above conditions.
 */

/*
 * Example 1:
 * Input: quality = [10,20,5], wage = [70,50,30], K = 2
 * Output: 105.00000
 * Explanation: We pay 70 to 0-th worker and 35 to 2-th worker.
 * Example 2:
 * Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], K = 3
 * Output: 30.66667
 * Explanation: We pay 4 to 0-th worker, 13.33333 to 2-th and 3-th workers seperately.
 */

/*
 * Note:
 * 1 <= K <= N <= 10000, where N = quality.length = wage.length
 * 1 <= quality[i] <= 10000
 * 1 <= wage[i] <= 10000
 * Answers within 10^-5 of the correct answer will be considered correct.
 */

#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Worker
{
    int q, w;
    Worker(int q, int w):q(q),w(w){}
};

// k 个人分别是 i1, i2, ..., ik
// 总工资 = (q[i1] + q[i2] + ... + q[ik]) * x
// x 为常数且为 w[i] / q[i] 之一
//
// 若 i 选了，则 x[i] >= w[i] / q[i]
// 因此随着 w[i] / q[i] 越来越大，满足的候选越来越多
//
// 若选定了 x，即当前枚举到的 x(当前所有后选中最大)
// 选择所有候选中 q 最小的 k 个

struct Sort_cmp
{
    // 按 w[i] / q[i] 从大到小排序
    bool operator()(const Worker& worker1, const Worker& worker2) const
    {
        return (double)worker1.w / worker1.q < (double)worker2.w / worker2.q;
    }
};

struct Heap_cmp
{
    bool operator()(const Worker& worker1, const Worker& worker2) const
    {
        return worker1.q < worker2.q;
    }
};

class Solution {
public:
    // 若招的人为
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K) {
        int n = quality.size();
        vector<Worker> workers;
        for(int i = 0; i < n; ++i)
            workers.emplace_back(quality[i], wage[i]);
        sort(workers.begin(), workers.end(), Sort_cmp());
        priority_queue<Worker, vector<Worker>, Heap_cmp> pq;
        int sum_q = 0;
        for(int i = 0; i < K; ++i)
        {
            sum_q += workers[i].q;
            pq.push(workers[i]);
        }
        double result = sum_q * (double)workers[K - 1].w / workers[K - 1].q;
        for(int i = K; i < n; ++i)
        {
            if(pq.top().q > workers[i].q)
            {
                sum_q -= pq.top().q;
                pq.pop();
                pq.push(workers[i]);
                sum_q += workers[i].q;
                result = min(result, sum_q * (double)workers[i].w / workers[i].q);
            }
        }
        return result;
    }
};
