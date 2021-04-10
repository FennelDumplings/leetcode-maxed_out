
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int guardCastle(vector<string>& grid) {
        // 判定是否必败：
        //    城堡周围的3个点中有瞬移点；且其中某个恶魔周围3个点中有瞬移点
        //    城堡周围的3个点中有恶魔
        //    这样的话必败。返回 -1
        // 从城堡点开始 DFS，如果没有 DFS 到任何恶魔或瞬移点，则返回 0，否则:
        //  (0) 加障碍把城堡围住(如果城堡不挨着瞬移点)
        //  (1) 把所有恶魔围住
        //  (2) 把所有瞬移点围住

    }
};
