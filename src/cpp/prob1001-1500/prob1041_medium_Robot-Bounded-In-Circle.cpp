// prob1041: Robot Bounded In Circle

/*
 * https://leetcode-cn.com/problems/robot-bounded-in-circle/
 */

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

struct State
{
    int x, y;
    int ori;
    int pos;
    State(int x, int y, int ori, int pos):x(x),y(y),ori(ori),pos(pos){}
};

struct MyCmp
{
    bool operator()(const State& s1, const State& s2) const
    {
        return s1.x == s2.x && s1.y == s2.y && s1.ori == s2.ori && s1.pos == s2.pos;
    }
};

struct MyHash
{
    int operator()(const State& s) const
    {
        return s.ori + s.pos * 101 + s.x * 1001 + s.y * 1000001;
    }
};


class Solution {
public:
    bool isRobotBounded(string instructions) {
        int n = instructions.size();
        int max_depth = n * n * 4;
        State s(0, 0, 0, 0);
        setting = unordered_set<State, MyHash, MyCmp>();
        return dfs(s, 0, max_depth, instructions);
    }

private:
    // 上右下左
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    unordered_set<State, MyHash, MyCmp> setting;

    bool dfs(State& s, int depth, int max_depth, const string& instructions)
    {
        if(depth == max_depth)
            return false;
        if(setting.count(s) > 0)
            return true;
        setting.insert(s);
        int n = instructions.size();
        int x = s.x, y = s.y, ori = s.ori;
        if(instructions[s.pos] == 'G')
        {
            x += dx[s.ori];
            y += dy[s.ori];
        }
        else if(instructions[s.pos] == 'L')
            ori = (ori - 1 + 4) % 4;
        else
            ori = (ori + 1) % 4;
        State nxt(x, y, ori, (s.pos + 1) % n);
        return dfs(nxt, depth + 1, max_depth, instructions);
    }
};
