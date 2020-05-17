// 20200517
// 3. 收藏清单

/*
 * 给你一个数组 favoriteCompanies ，其中 favoriteCompanies[i] 是第 i 名用户收藏的公司清单（下标从 0 开始）。
 * 请找出不是其他任何人收藏的公司清单的子集的收藏清单，并返回该清单下标。下标需要按升序排列。
 */

/*
 * 示例 1：
 * 输入：favoriteCompanies = [["leetcode","google","facebook"],["google","microsoft"],["google","facebook"],["google"],["amazon"]]
 * 输出：[0,1,4]
 * 解释：
 * favoriteCompanies[2]=["google","facebook"] 是 favoriteCompanies[0]=["leetcode","google","facebook"] 的子集。
 * favoriteCompanies[3]=["google"] 是 favoriteCompanies[0]=["leetcode","google","facebook"] 和 favoriteCompanies[1]=["google","microsoft"] 的子集。
 * 其余的收藏清单均不是其他任何人收藏的公司清单的子集，因此，答案为 [0,1,4] 。
 * 示例 2：
 * 输入：favoriteCompanies = [["leetcode","google","facebook"],["leetcode","amazon"],["facebook","google"]]
 * 输出：[0,1]
 * 解释：favoriteCompanies[2]=["facebook","google"] 是 favoriteCompanies[0]=["leetcode","google","facebook"] 的子集，因此，答案为 [0,1] 。
 * 示例 3：
 * 输入：favoriteCompanies = [["leetcode"],["google"],["facebook"],["amazon"]]
 * 输出：[0,1,2,3]
 */

/*
 * 提示：
 * 1 <= favoriteCompanies.length <= 100
 * 1 <= favoriteCompanies[i].length <= 500
 * 1 <= favoriteCompanies[i][j].length <= 20
 * favoriteCompanies[i] 中的所有字符串 各不相同 。
 * 用户收藏的公司清单也 各不相同 ，也就是说，即便我们按字母顺序排序每个清单， favoriteCompanies[i] != favoriteCompanies[j] 仍然成立。
 * 所有字符串仅包含小写英文字母。
 */

#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

// includes 函数
class Solution {
public:
    vector<int> peopleIndexes(vector<vector<string>>& favoriteCompanies) {
        int n = favoriteCompanies.size();
        vector<bool> flags(n, true);
        for(vector<string>& item: favoriteCompanies)
            sort(item.begin(), item.end());
        for(int i = 0; i < n; ++i)
        {
            const vector<string> &item1 = favoriteCompanies[i];
            for(int j = 0; j < i; ++j)
            {
                if(flags[j])
                {
                    const vector<string> &item2 = favoriteCompanies[j];
                    if(item1.size() > item2.size())
                    {
                        // item1 比较长
                        if(includes(item1.begin(), item1.end(), item2.begin(), item2.end()))
                            flags[j] = false;
                    }
                    else
                    {
                        // item2 比较长
                        if(includes(item2.begin(), item2.end(), item1.begin(), item1.end()))
                        {
                            flags[i] = false;
                            break;
                        }
                    }
                }
            }
        }
        vector<int> result;
        for(int i = 0; i < n; ++i)
            if(flags[i])
                result.push_back(i);
        return result;
    }
};
