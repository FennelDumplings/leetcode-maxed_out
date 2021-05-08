// prob281: Zigzag Iterator

/*
 * Given two 1d vectors, implement an iterator to return their elements alternately.
 */

/*
 * Example:
 *
 * Input:
 * v1 = [1,2]
 * v2 = [3,4,5,6]
 * Output: [1,3,2,4,5,6]
 * Explanation: By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,3,2,4,5,6].
 */

/*
 * 拓展：假如给你 k 个一维向量呢？你的代码在这种情况下的扩展性又会如何呢?
 * 拓展声明：
 *  “锯齿” 顺序对于 k > 2 的情况定义可能会有些歧义。所以，假如你觉得 “锯齿” 这个表述不妥，也可以认为这是一种 “循环”。例如：
 * 输入:
 * [1,2,3]
 * [4,5,6,7]
 * [8,9]
 * 输出: [1,4,8,2,5,9,3,6,7].
 */

#include <vector>

using namespace std;

class ZigzagIterator {
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        n = 2;
        nums = vector<vector<int>>({v1, v2});
        N = 0;
        for(int i = 0; i < n; ++i)
        {
            lens[i] = nums[i].size();
            N += lens[i];
        }

        i = 0; j = 0;
        iter = 0;
    }

    int next() {
        int result = nums[i][j];
        ++iter;
        if(hasNext())
            for(int k = 0; k < n; ++k)
            {
                ++i;
                if(i == n)
                {
                    i = 0;
                    ++j;
                }
                if(j < lens[i])
                    break;
            }
        return result;
    }

    bool hasNext() {
        return iter != N;
    }

private:
    int n; // vector 数量
    vector<int> lens; // 各个 vector 长度
    int i, j; // 第 i 个 vector, 第 j 个元素
    vector<vector<int>> nums;
    int N; // 总元素数
    int iter; // [0..n-1] 当前待访问元素, 为 N 时为 end
};
