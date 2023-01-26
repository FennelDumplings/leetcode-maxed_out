// prob48: Rotate Image

/*
 * You are given an n x n 2D matrix representing an image.
 * Rotate the image by 90 degrees (clockwise).
 */

/*
 * Note:
 * You have to rotate the image in-place, which means you have to modify the input 2D matrix directly.
 * DO NOT allocate another 2D matrix and do the rotation.
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        if(matrix.empty()) return;
        int n = matrix.size();
        if(n == 1) return;
        for(int i = 0; i < n / 2 - 1; ++i)
            _rotate(matrix, i);
    }

private:
    void _rotate(vector<vector<int>>& matrix, int topleft)
    {
        int n = matrix.size();
        for(int i = 0; i <= n - 2 * topleft - 2; ++i)
        {
            // (topleft, topleft + i) -> (topleft + i, n - 1 - topleft)
            // -> (n - 1 - topleft, n - 1 - topleft - i) -> (n - 1 - topleft - i, topleft)
            int tmp = matrix[topleft][topleft + i];
            matrix[topleft][topleft + i] = matrix[n - 1 - topleft - i][topleft];
            matrix[n - 1 - topleft - i][topleft] = matrix[n - 1 - topleft][n - 1 - topleft - i];
            matrix[n - 1 - topleft][n - 1 - topleft - i] = matrix[topleft + i][n - 1 - topleft];
            matrix[topleft + i][n - 1 - topleft] = tmp;
        }
    }
};

class Solution_2 {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int a = 0;
        int b = n - 1;
        while(a < b){
            for(int i = 0; i < (b - a); ++i){
                swap(matrix[a][a + i], matrix[a + i][b]);
                swap(matrix[a][a + i], matrix[b][b - i]);
                swap(matrix[a][a + i], matrix[b - i][a]);
            }
            ++a;
            --b;
        }
    }
};
