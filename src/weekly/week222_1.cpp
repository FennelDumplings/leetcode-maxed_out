
#include <vector>
#include <algorithm>

using namespace std;

struct Box
{
    int num;
    int V;
    Box(int num, int V):num(num),V(V){}
};

struct Cmp
{
    bool operator()(const Box& b1, const Box& b2) const
    {
        return b1.V > b2.V;
    }
};

class Solution {
public:
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        vector<Box> boxes;
        for(const vector<int>& box: boxTypes)
            boxes.emplace_back(box[0], box[1]);
        sort(boxes.begin(), boxes.end(), Cmp());
        int ans = 0;
        int i = 0;
        int n = boxes.size();
        while(truckSize > 0 && i < n)
        {
            if(boxes[i].num >= truckSize)
            {
                ans += truckSize * boxes[i].V;
                truckSize = 0;
            }
            else
            {
                ans += boxes[i].num * boxes[i].V;
                truckSize -= boxes[i].num;
            }
            ++i;
        }
        return ans;
    }
};
