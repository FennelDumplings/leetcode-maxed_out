// interview08.10: 颜色填充

/*
 * 编写函数，实现许多图片编辑软件都支持的「颜色填充」功能。
 * 待填充的图像用二维数组 image 表示，元素为初始颜色值。初始坐标点的横坐标为 sr 纵坐标为 sc。需要填充的新颜色为 newColor 。
 * 「周围区域」是指颜色相同且在上、下、左、右四个方向上存在相连情况的若干元素。
 * 请用新颜色填充初始坐标点的周围区域，并返回填充后的图像。
 */

/*
 * 示例：
 *
 * 输入：
 * image = [[1,1,1],[1,1,0],[1,0,1]]
 * sr = 1, sc = 1, newColor = 2
 * 输出：[[2,2,2],[2,2,0],[2,0,1]]
 * 解释:
 * 初始坐标点位于图像的正中间，坐标 (sr,sc)=(1,1) 。
 * 初始坐标点周围区域上所有符合条件的像素点的颜色都被更改成 2 。
 * 注意，右下角的像素没有更改为 2 ，因为它不属于初始坐标点的周围区域。
 */

/*
 * 提示：
 * image 和 image[0] 的长度均在范围 [1, 50] 内。
 * 初始坐标点 (sr,sc) 满足 0 <= sr < image.length 和 0 <= sc < image[0].length 。
 * image[i][j] 和 newColor 表示的颜色值在范围 [0, 65535] 内。
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int n = image.size(), m = image[0].size();
        vector<vector<bool> > visited(n, vector<bool>(m, false));
        queue<PII> q;
        q.push(PII(sr, sc));
        visited[sr][sc] = true;
        int prev = image[sr][sc];
        while(!q.empty())
        {
            PII cur = q.front();
            q.pop();
            for(int d = 0; d < 4; ++d)
            {
                int x = cur.first + dx[d], y = cur.second + dy[d];
                if(x < 0 || x >= n || y < 0 || y >= m) continue;
                if(visited[x][y]) continue;
                if(image[x][y] != prev) continue;
                visited[x][y] = true;
                q.push(PII(x, y));
            }
        }
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(visited[i][j])
                    image[i][j] = newColor;
        return image;
    }

private:
    using PII = pair<int, int>;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
};
