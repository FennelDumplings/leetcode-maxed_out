// prob777: Swap Adjacent in LR String

/*
 * In a string composed of 'L', 'R', and 'X' characters, like "RXXLRXRXL",
 * a move consists of either replacing one occurrence of "XL" with "LX", or replacing one occurrence of "RX" with "XR".
 * Given the starting string start and the ending string end, return True if and only if there exists a sequence
 * of moves to transform one string to the other.
 */

/*
 * Example:
 * Input: start = "RXXLRXRXL", end = "XRLXXRRLX"
 * Output: True
 * Explanation:
 * We can transform start to end following these steps:
 * RXXLRXRXL ->
 * XRXLRXRXL ->
 * XRLXRXRXL ->
 * XRLXXRRXL ->
 * XRLXXRRLX
 */

/*
 * Note:
 * 1 <= len(start) = len(end) <= 10000.
 * Both start and end will only consist of characters in {'L', 'R', 'X'}.
 */

#include <string>

using namespace std;

class Solution {
public:
    bool canTransform(string start, string end) {
        int ns = start.size();
        int ne = end.size();
        if(ns != ne) return false;
        int sL = 0;
        int sR = 0;
        int eL = 0;
        int eR = 0;
        for(int i = 0; i < ne; ++i)
        {
            if(start[i] == 'L')
                ++sL;
            else if(start[i] == 'R')
                ++sR;
            if(end[i] == 'L')
                ++eL;
            else if(end[i] == 'R')
                ++eR;
            if(sL > eL || sR < eR) return false;
        }
        return (sL == eL && sR == eR && sL + sR < ns);
    }
};
