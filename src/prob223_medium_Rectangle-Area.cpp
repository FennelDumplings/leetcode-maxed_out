// prob223: Rectangle Area

/*
 * Find the total area covered by two rectilinear rectangles in a 2D plane.
 * Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.
 */

/*
 * Example:
 * Input: A = -3, B = 0, C = 3, D = 4, E = 0, F = -1, G = 9, H = 2
 * Output: 45
 */

/*
 * Note:
 * Assume that the total area is never beyond the maximum possible value of int.
 */

#include <algorithm>

using namespace std;

class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        long long X = min(C, G) + 0ll - max(A, E);
        long long Y = min(D, H) + 0ll - max(B, F);
        return (C - A) * (D - B) - max(0ll, X) * max(0ll, Y) + (G - E) * (H - F);
    }
};



