// prob353: Design Snake Game

/*
 * https://leetcode-cn.com/problems/design-snake-game/
 */

#include <vector>
#include <queue>
#include <string>
#include <unordered_set>

using namespace std;

class SnakeGame {
public:
    /** Initialize your data structure here.
        @param width - screen width
        @param height - screen height
        @param food - A list of food positions
        E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
    SnakeGame(int width, int height, vector<vector<int>>& food) {
        W = width;
        H = height;
        score = 0;
        body.push(Point(0, 0));
        for(const vector<int> &item: food)
            (this -> food).push(Point(item[0], item[1]));
        setting = unordered_set<Point, MyHash>();
        setting.insert(Point(0, 0));
    }

    /** Moves the snake.
        @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
        @return The game's score after the move. Return -1 if game over.
        Game over when snake crosses the screen boundary or bites its body. */
    int move(string direction) {
        Point cur = body.back();
        Point nxt(-1, -1);
        switch(direction[0])
        {
        case 'D':
            {
                nxt = Point(cur.x + 1, cur.y);
                break;
            }
        case 'U':
            {
                nxt = Point(cur.x - 1, cur.y);
                break;
            }
        case 'L':
            {
                nxt = Point(cur.x, cur.y - 1);
                break;
            }
        case 'R':
            {
                nxt = Point(cur.x, cur.y + 1);
                break;
            }
        default:
            break;
        }
        if(nxt.x < 0 || nxt.x >= H || nxt.y < 0 || nxt.y >= W)
            return -1;
        if(!food.empty() && nxt.x == food.front().x && nxt.y == food.front().y)
        {
            ++score;
            food.pop();
        }
        else
        {
            setting.erase(setting.find(body.front()));
            body.pop();
        }
        if(setting.count(nxt) > 0)
            return -1;
        body.push(nxt);
        setting.insert(nxt);
        return score;
    }

private:
    struct Point
    {
        int x, y;
        Point(int x, int y):x(x),y(y){}
        bool operator==(const Point& p) const
        {
            return (x == p.x && y == p.y);
        }
    };

    struct MyHash
    {
        bool operator()(const Point& p) const
        {
            return p.x * 10007 + p.y;
        }
    };

    int W, H;
    int score;
    queue<Point> body;
    queue<Point> food;
    unordered_set<Point, MyHash> setting;
};
