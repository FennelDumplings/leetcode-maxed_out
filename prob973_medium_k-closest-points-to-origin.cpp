// Prob973 K Closest Points to Origin

/*
 * We have a list of points on the plane.  Find the K closest points to the origin (0, 0).
 * (Here, the distance between two points on a plane is the Euclidean distance.)
 * You may return the answer in any order.  The answer is guaranteed to be unique
 * (except for the order that it is in.)
 */

/*
 * Example1
 * Input: points = [[1,3],[-2,2]], K = 1
 * Output: [[-2,2]]
 * Explanation:
 * The distance between (1, 3) and the origin is sqrt(10).
 * The distance between (-2, 2) and the origin is sqrt(8).
 * Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
 * We only want the closest K = 1 points from the origin, so the answer is just [[-2,2]].
 * Example2
 * Input: points = [[3,3],[5,-1],[-2,4]], K = 2
 * Output: [[3,3],[-2,4]]
 * (The answer [[-2,4],[3,3]] would also be accepted.)
 */

/*
 * 1 <= K <= points.length <= 10000
 * -10000 < points[i][0] < 10000
 * -10000 < points[i][1] < 10000
 */


#include <queue>
#include <vector>
#include <iostream>
using namespace std;

// 基于堆排
class Solution {
public:
    vector<vector<int> > kClosest(vector<vector<int> >& points, int K) {
        // 大顶堆
        priority_queue<vector<int>, vector<vector<int> >, PointLess> pq;
        vector<vector<int> > result(K, vector<int>(2, 0));
        int n = points.size();
        for(int i = 0; i < K; ++i)
            pq.push(points[i]);
        for(int i = K; i < n; ++i)
        {
            if(pointLess(points[i], pq.top()))
            {
                pq.pop();
                pq.push(points[i]);
            }
        }
        for(int i = K - 1; i >= 0; --i)
        {
            result[i] = pq.top();
            pq.pop();
        }
        return result;
    }

private:
    struct PointLess {
        bool operator()(const vector<int>& a, const vector<int>& b)
        {
            // 小于号是大顶堆
            return (a[0] * a[0] + a[1] * a[1]) < (b[0] * b[0] + b[1] * b[1]);
        }
    };

    bool pointLess(const vector<int>& a, const vector<int>& b) {
        return (a[0] * a[0] + a[1] * a[1]) < (b[0] * b[0] + b[1] * b[1]);
    }
};

// 基于快排
class Solution_2 {
public:
    vector<vector<int> > kClosest(vector<vector<int> >& points, int K) {
        int n = points.size();
        _quicksort(points, 0, n - 1, K - 1);
        return vector<vector<int> >(points.begin(), points.begin() + K);
    }

private:
    // 0..left..K..right..n-1
    void _quicksort(vector<vector<int> >& points, int l, int r, int K) {
        if(l >= r) return;
        vector<int> pivot = points[l];
        int left = l, right = r;
        while(left < right)
        {
            // pivot 在 left
            while(left < right && !pointGreater(pivot, points[right])) --right;
            if(left < right)
            {
                _swap(points, left, right);
                ++left;
            }
            // pivot 在 right
            while(left < right && !pointGreater(points[left], pivot)) ++left;
            if(left < right)
            {
                _swap(points, left, right);
                --right;
            }
        }
        // left = right 是 pivot 的索引
        // K 和 left 的对应关系易错
        if(left == K) return;
        else if(left > K) _quicksort(points, l, left - 1, K);
        else _quicksort(points, left + 1, r, K);
    }

    void _swap(vector<vector<int> >& points, int a, int b) {
        vector<int> tmp = points[a];
        points[a] = points[b];
        points[b] = tmp;
    }

    bool pointLess(const vector<int>& a, const vector<int>& b) {
        return (a[0] * a[0] + a[1] * a[1]) < (b[0] * b[0] + b[1] * b[1]);
    }


    bool pointGreater(const vector<int>& a, const vector<int>& b) {
        return (a[0] * a[0] + a[1] * a[1]) > (b[0] * b[0] + b[1] * b[1]);
    }
};
