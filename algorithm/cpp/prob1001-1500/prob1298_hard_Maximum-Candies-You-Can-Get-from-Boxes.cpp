// prob1298: Maximum Candies You Can Get from Boxes

/*
 * https://leetcode-cn.com/problems/maximum-candies-you-can-get-from-boxes/
 */

#include <vector>
#include <unordered_set>

using namespace std;

struct State
{
    int cnt; // 已经取得的糖果数目
    unordered_set<int> boxes; // 在手中尚未打开的盒子
    unordered_set<int> keys; // 手中的钥匙
    State(int cnt):cnt(cnt){}
};

class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        State s(0);
        s.boxes = unordered_set<int>(initialBoxes.begin(), initialBoxes.end());
        bool flag = false; // 当前轮行动是否解锁了新盒子
        do{
            flag = false;
            vector<int> new_keys;
            vector<int> new_boxes;
            for(int id: s.boxes)
            {
                if(status[id] == 1)
                {
                    // 盒子是开的
                    flag = true;
                    s.cnt += candies[id];
                    for(int key: keys[id])
                        new_keys.push_back(key);
                    for(int box: containedBoxes[id])
                        new_boxes.push_back(box);
                }
                else
                {
                    // 盒子是关的
                    if(s.keys.count(id))
                    {
                        // 有钥匙
                        flag = true;
                        s.cnt += candies[id];
                        for(int key: keys[id])
                            new_keys.push_back(key);
                        for(int box: containedBoxes[id])
                            new_boxes.push_back(box);
                    }
                    else
                        new_boxes.push_back(id);
                }
            }
            State nxt(s.cnt);
            for(int k: s.keys)
                nxt.keys.insert(k);
            for(int k: new_keys)
                nxt.keys.insert(k);
            for(int b: new_boxes)
                nxt.boxes.insert(b);
            s = nxt;
        }while(flag);
        return s.cnt;
    }
};
