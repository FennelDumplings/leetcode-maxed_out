// prob447: Number of Boomerangs

/*
 * Given n points in the plane that are all pairwise distinct, a "boomerang" is a tuple of points (i, j, k)
 * such that the distance between i and j equals the distance between i and k (the order of the tuple matters).
 * Find the number of boomerangs. You may assume that n will be at most 500 and coordinates of points are
 * all in the range [-10000, 10000] (inclusive).
 */

/*
 * Example:
 * Input:
 * [[0,0],[1,0],[2,0]]
 * Output:
 * 2
 * Explanation:
 * The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]]
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        if(points.empty()) return 0;
        int n = points.size();
        if(n < 3) return 0;
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            unordered_map<int, int> mapping; // 距离 -> 个数
            for(int j = 0; j < n; ++j)
            {
                if(j == i) continue;
                int d = dist(points[i], points[j]);
                ans += mapping[d] * 2;
                ++mapping[d];
            }
        }
        return ans;
    }

private:
    int dist(const vector<int>& p1, const vector<int>& p2)
    {
        int x = p1[0] - p2[0];
        int y = p1[1] - p2[1];
        return x * x + y * y;
    }
};

// 双重循环优化
class Solution_2 {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        if(points.empty()) return 0;
        int n = points.size();
        if(n < 3) return 0;
        vector<unordered_map<PVV, int, MyHash, MyCmp> > mappings(n, unordered_map<PVV, int, MyHash, MyCmp>()); //  点对 -> 距离相等的个数
        int result = 0;
        for(int i = 0; i < n - 1; ++i)
        {
            const vector<int> &point_i = points[i];
            for(int j = i + 1; j < n; ++j)
            {
                const vector<int> &point_j = points[j];
                result += mappings[i][PVV({point_i, point_j})] * 2;
                result += mappings[j][PVV({point_j, point_i})] * 2;
                ++mappings[i][PVV({point_i, point_j})];
                ++mappings[j][PVV({point_j, point_i})];
            }
        }
        return result;
    }

private:
    // 500 个点，固定一个点时，有 499 中距离，哈希表开1000以上, 找1000 以上的质数
    // const static int MOD = 5e5 + 9;
    const static int MOD = 1009;
    using ll = long long;
    using PVV = pair<vector<int>, vector<int> >; // 点对

    struct MyHash
    {
        int operator()(const PVV& point_pair) const
        {
            int x = point_pair.first[0] - point_pair.second[0];
            int y = point_pair.first[1] - point_pair.second[1];
            return (((ll)x * x) + ((ll)y * y)) % MOD;
        }
    };

    struct MyCmp
    {
        bool operator()(const PVV& point_pair1, const PVV& point_pair2) const
        {
            int x1 = point_pair1.first[0] - point_pair1.second[0];
            int y1 = point_pair1.first[1] - point_pair1.second[1];
            int x2 = point_pair2.first[0] - point_pair2.second[0];
            int y2 = point_pair2.first[1] - point_pair2.second[1];
            return (ll)x1 * x1 + (ll)y1 * y1 == (ll)x2 * x2 + (ll)y2 * y2;
        }
    };
};

// 直接用距离做键可以过
// 前面的自定义哈希自寻麻烦了
class Solution_3 {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        if(points.empty()) return 0;
        int n = points.size();
        if(n < 3) return 0;
        vector<unordered_map<int, int> > mappings(n, unordered_map<int, int>()); //  点对 -> 距离相等的个数
        int result = 0;
        for(int i = 0; i < n - 1; ++i)
        {
            const vector<int> &point_i = points[i];
            for(int j = i + 1; j < n; ++j)
            {
                // j = i + 1 用到了距离的自反性
                const vector<int> &point_j = points[j];
                int x = point_i[0] - point_j[0];
                int y = point_i[1] - point_j[1];
                int dist = x * x + y * y;
                result += mappings[i][dist] * 2;
                result += mappings[j][dist] * 2;
                ++mappings[i][dist];
                ++mappings[j][dist];
            }
        }
        return result;
    }
};
