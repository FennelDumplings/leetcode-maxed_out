// interview16.11: 跳水板

/*
 * 你正在使用一堆木板建造跳水板。有两种类型的木板，其中长度较短的木板长度为shorter，长度较长的木板长度为longer。你必须正好使用k块木板。编写一个方法，生成跳水板所有可能的长度。
 * 返回的长度需要从小到大排列。
 */

#include <set>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> divingBoard(int shorter, int longer, int k) {
        if(k == 0) return {};
        set<int> lens;
        for(int i = 0; i <= k; ++i)
        {
            // 用 i 块长的，k - i 块短的
            lens.insert(longer * i + shorter * (k - i));
        }
        vector<int> result(lens.begin(), lens.end());
        return result;
    }
};

// 不用 set
// longer == shorter 特判就行
class Solution_2 {
public:
    vector<int> divingBoard(int shorter, int longer, int k) {
        if(k == 0) return {};
        if(shorter == longer) return {longer * k};
        vector<int> result(k + 1);
        for(int i = 0; i <= k; ++i)
        {
            // 用 i 块长的，k - i 块短的
            result[i] = longer * i + shorter * (k - i);
        }
        return result;
    }
};
