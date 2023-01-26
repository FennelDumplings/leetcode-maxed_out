// prob1274: Number of Ships in a Rectangle

/*
 * (This problem is an interactive problem.)
 * On the sea represented by a cartesian plane, each ship is located at an integer point, and each integer point may contain at most 1 ship.
 * You have a function Sea.hasShips(topRight, bottomLeft) which takes two points as arguments and returns true if and only if there is at least one ship in the rectangle represented by the two points, including on the boundary.
 * Given two points, which are the top right and bottom left corners of a rectangle, return the number of ships present in that rectangle.  It is guaranteed that there are at most 10 ships in that rectangle.
 * Submissions making more than 400 calls to hasShips will be judged Wrong Answer.  Also, any solutions that attempt to circumvent the judge will result in disqualification.
 */

/*
 * Input:
 * ships = [[1,1],[2,2],[3,3],[5,5]], topRight = [4,4], bottomLeft = [0,0]
 * Output: 3
 * Explanation: From [0,0] to [4,4] we can count 3 ships within the range.
 */

/*
 * Constraints:
 * On the input ships is only given to initialize the map internally. You must solve this problem "blindfolded". In other words, you must find the answer using the given hasShips API, without knowing the ships position.
 * 0 <= bottomLeft[0] <= topRight[0] <= 1000
 * 0 <= bottomLeft[1] <= topRight[1] <= 1000
 */

#include <vector>

using namespace std;

class Sea {
  public:
    bool hasShips(vector<int> topRight, vector<int> bottomLeft);
};

class Solution {
public:
    //
    //          [x2, y2]
    //
    // [x1, y1]
    int countShips(Sea sea, vector<int> topRight, vector<int> bottomLeft) {
        int x1 = bottomLeft[0], x2 = topRight[0];
        int y1 = bottomLeft[1], y2 = topRight[1];
        return _countShips(sea, x1, x2, y1, y2);
    }

private:
    int _countShips(Sea sea, int x1, int x2, int y1, int y2)
    {
        // cout << x1 << " " << x2 << " " << y1 << " " << y2 << endl;
        // 调用方保证 x1 <= x2, y1 <= y2
        if(!sea.hasShips(vector<int>({x2, y2}), vector<int>({x1, y1})))
            return 0;
        if(x1 == x2 && y1 == y2)
            return 1;

        int midx = (x1 + x2) / 2;
        int midy = (y1 + y2) / 2;

        int topleft = 0;
        int topright = 0;
        int bottomleft = 0;
        int bottomright = 0;
        topleft = _countShips(sea, x1, midx, y1, midy);
        if(y1 < y2)
            topright = _countShips(sea, x1, midx, midy + 1, y2);
        if(x1 < x2)
            bottomleft = _countShips(sea, midx + 1, x2, y1, midy);
        if(x1 < x2 && y1 < y2)
            bottomright = _countShips(sea, midx + 1, x2, midy + 1, y2);
        return topleft + topright + bottomleft + bottomright;
    }
};


