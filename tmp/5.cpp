#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

/*
 * 当前走子方为 x，另一方为 y
 *
 * if (x 再走一步就赢)
 *     x 赢
 * else
 *     if(y 有两个点可以一步就赢)
 *         y 赢
 *     else if(y 有一个点可以一步就赢)
 *         x 走该点
 *     else
 *         ...
 */

class Solution {
public:
    string gobang(vector<vector<int>>& pieces) {
        setting.push_back(unordered_set<ll>());
        setting.push_back(unordered_set<ll>());
        for(const vector<int> &piece: pieces)
            setting[piece[2]].insert(key(piece[0], piece[1]));
        if(one_move_win(0).size() > 0)
            return "Black";
        else
        {
            vector<vector<int>> white_win_point = one_move_win(1);
            if(white_win_point.size() > 1)
                return "White";
            else if(white_win_point.size() == 1)
            {
                setting[0].insert(key(white_win_point[0][0], white_win_point[0][1]));
                vector<vector<int>> white_win_point = one_move_win(0);
                if(white_win_point.size() > 1)
                    return "Black";
                else
                    return "None";
            }
            else
            {
                // 枚举黑第一步下(x, y)
                // 距离(x, y)一步的地方得有至少一个黑棋，
                // 或者距离(x, y)两步的地方，得有至少两个黑棋
                for(int piece: setting[0])
                {
                    int y = piece % p;
                    int x = (piece - (ll)y) / p;
                    for(int d = 0; d < 8; ++d)
                    {
                        int new_x = x + dx[d];
                        int new_y = y + dy[d];
                        int k = key(new_x, new_y);
                        if(setting[0].count(k) == 0 && setting[0].count(k) == 0)
                        {
                            setting[0].insert(k);
                            vector<vector<int>> white_win_point = one_move_win(0);
                            if(white_win_point.size() > 1)
                                return "Black";
                            setting[0].erase(k);
                        }
                    }
                    for(int d = 0; d < 16; ++d)
                    {
                        int new_x = x + ddx[d];
                        int new_y = y + ddy[d];
                        int k = key(new_x, new_y);
                        bool flag = false;
                        if(setting[0].count(k) == 0 && setting[0].count(k) == 0)
                        {
                            for(int dd = 0; dd < 16; ++dd)
                            {
                                int xx = new_x + ddx[dd];
                                int yy = new_y + ddy[dd];
                                if(xx != x || yy != y)
                                {
                                    flag = true;
                                    break;
                                }
                            }
                        }
                        if(flag)
                        {
                            setting[0].insert(k);
                            vector<vector<int>> white_win_point = one_move_win(0);
                            if(white_win_point.size() > 1)
                                return "Black";
                            setting[0].erase(k);
                        }
                    }
                }
            }
        }
        return "None";
    }

private:
    using ll = long long;
    const ll p = 1e9 + 7;
    vector<unordered_set<ll>> setting;
    int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
    int dy[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int ddx[16] = {-2, -2, -2, -2, -2,  2,  2,  2,  2,  2, -1,  0,  1, -1,  0,  1};
    int ddy[16] = {-2, -1,  0,  1,  2, -2, -1,  0,  1,  2, -2, -2, -2,  2,  2,  2};

    ll key(int x, int y)
    {
        // x 从小到大，x 相等时 y 从小到大
        return (ll)x * p + (ll)y;
    }

    vector<vector<int>> one_move_win(int color)
    {
        // color 走一步就赢的点的个数
        // 0: 没有
        // 1: 有一个
        // 2: 大于一个
        vector<vector<int>> result;
        for(ll piece: setting[color])
        {
            int y = piece % p;
            int x = (piece - (ll)y) / p;
            // 向八个方向走四个
            for(int d = 0; d < 8; ++d)
            {
                vector<int> res = check(color, x, y, d);
                if(!res.empty())
                {
                    if(result.empty())
                        result.push_back(res);
                    else if(result[0][0] != res[0] || result[0][1] != res[1])
                    {
                        result.push_back(res);
                        return result;
                    }
                }
            }
        }
        return result;
    }

    vector<int> check(int color, int x, int y, int d)
    {
        int flag = 1;
        int x0 = - 1e9 - 7;
        int y0 = - 1e9 - 7;
        for(int i = 1; i <= 4; ++i)
        {
            x += dx[d];
            y += dy[d];
            if(setting[color ^ 1].count(key(x, y)) > 0)
                return {};
            else if(setting[color].count(key(x, y)) > 0)
                continue;
            else
            {
                --flag;
                if(flag < 0)
                    return {};
                x0 = x;
                y0 = y;
            }
        }
        return {x0, y0};
    }
};
