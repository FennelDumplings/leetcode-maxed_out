// prob302: Smallest Rectangle Enclosing Black Pixels

/*
 * An image is represented by a binary matrix with 0 as a white pixel and 1 as a black pixel. The black pixels are connected, i.e., there is only one black region. Pixels are connected horizontally and vertically. Given the location (x, y) of one of the black pixels, return the area of the smallest (axis-aligned) rectangle that encloses all black pixels.
 */

/*
 * Example:
 * Input:
 * [
 *   "0010",
 *   "0110",
 *   "0100"
 * ]
 * and x = 0, y = 2
 * Output: 6
 */

#include <vector>

using namespace std;

// 二分
class Solution {
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        if(image.empty()) return 0;
        int n = image.size(), m = image[0].size();
        int most_left = m, most_right = -1;
        int most_up = n, most_down = -1;

        // [0, x] 找 most_up
        int left = 0, right = x;
        while(left < right)
        {
            int mid = (left + right) / 2;
            if(check_row_vector(image, mid))
                right = mid;
            else
                left = mid + 1;
        }
        most_up = left;

        // [x, m - 1] 找 most_down
        left = x, right = n - 1;
        while(left < right)
        {
            int mid = (left + right + 1) / 2;
            if(check_row_vector(image, mid))
                left = mid;
            else
                right = mid - 1;
        }
        most_down = right;

        // [0, y] 找 most_left
        left = 0, right = y;
        while(left < right)
        {
            int mid = (left + right) / 2;
            if(check_col_vector(image, mid))
                right = mid;
            else
                left = mid + 1;
        }
        most_left = left;

        // [y, n - 1] 找 most_right
        left = y, right = m - 1;
        while(left < right)
        {
            int mid = (left + right + 1) / 2;
            if(check_col_vector(image, mid))
                left = mid;
            else
                right = mid - 1;
        }
        most_right = left;

        return (most_down - most_up + 1) * (most_right - most_left + 1);
    }

private:
    bool check_col_vector(const vector<vector<char>>& image, int j)
    {
        int n = image.size();
        for(int i = 0; i < n; ++i)
            if(image[i][j] == '1')
                return true;
        return false;
    }

    bool check_row_vector(const vector<vector<char>>& image, int i)
    {
        int m = image[0].size();
        for(int j = 0; j < m; ++j)
            if(image[i][j] == '1')
                return true;
        return false;
    }
};
