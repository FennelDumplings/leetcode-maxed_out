#include <vector>

using namespace std;

class Solution {
public:
    int orchestraLayout(int num, int xPos, int yPos) {
        // 所属圈号(剥几层)
        // 圈号范围：0 ~ (num - 1) / 2
        ll idx = get_idx(num, xPos, yPos);
        ll start = get_start(num, idx);
        ll step = get_step(num - 2 * idx, xPos - idx, yPos - idx);
        return (start + step) % 9;
    }

private:
    using ll = long long;

    ll get_step(ll len, ll xPos, ll yPos)
    {
        if(xPos == 0)
            return yPos;
        else if(yPos == len - 1)
            return len - 1 + xPos;
        else if(xPos == len - 1)
            return 2 * (len - 1) + len - 1 - yPos;
        else
            return 3 * (len - 1) + len - 1 - xPos;
    }

    ll get_start(const ll num, ll idx)
    {
        if(idx == 0)
            return 1;
        return (1 + (4 * (num - 1) + (4 * (num - (idx * 2 - 1)))) * idx / 2) % 9;
    }

    ll get_idx(const ll num, ll xPos, ll yPos)
    {
        ll max_idx = (num - 1) / 2;
        if(xPos > max_idx)
            xPos = num - xPos - 1;
        if(yPos > max_idx)
            yPos = num - yPos - 1;
        return min(xPos, yPos);
    }
};
