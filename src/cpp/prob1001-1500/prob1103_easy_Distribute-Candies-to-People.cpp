// prob1103: Distribute Candies to People

/*
 * https://leetcode-cn.com/problems/distribute-candies-to-people/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> distributeCandies(int candies, int num_people) {
        int C = candies, N = num_people;
        int i = 1;
        int require = f(i, N);
        while(C >= require)
        {
            C -= require;
            ++i;
            require = f(i, N);
        }
        // 在当前第 i 轮不够了 此前分别发了 1, ..., i - 1 共 i - 1 轮
        vector<int> result(N);
        for(int j = 1; j <= N; ++j)
        {
            result[j - 1] = (i - 2) * (i - 1) * N / 2 + (i - 1) * j;
        }
        require = (i - 1) * N + 1;
        for(int j = 1; j <= N; ++j)
        {
            if(C >= require)
            {
                result[j - 1] += require;
                C -= require;
                ++require;
            }
            else
            {
                result[j - 1] += C;
                break;
            }
        }
        return result;
    }

private:
    int f(int i, int N)
    {
        // 第 i 轮所需
        return (((i - 1) * N + 1) + i * N) * N / 2;
    }
};
