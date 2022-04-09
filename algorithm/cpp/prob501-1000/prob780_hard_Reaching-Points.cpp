class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        if(sx > tx || sy > ty)
            return false;
        if(sx == tx && sy == ty)
            return true;
        int x = tx, y = ty;
        while(sx < x && sy < y)
        {
            if(x > y)
            {
                x = x % y;
                if(x == 0)
                    x = y;
            }
            else if(x < y)
            {
                y = y % x;
                if(y == 0)
                    y = x;
            }
            if(x == y)
                break;
        }
        if(sx == x && sy == y)
            return true;
        if(sx == x && ((y - sy) % x == 0))
            return true;
        if(((x - sx) % y == 0) && sy = y)
            return true;
        return false;
    }
};
