// prob630: Course Schedule III

/*
 * https://leetcode-cn.com/problems/course-schedule-iii/
 */

#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

// 固定

struct Course
{
    int t;
    int d;
    Course(int t, int d):t(t),d(d){}
};

struct Sort_cmp
{
    bool operator()(const Course& c1, const Course& c2) const
    {
        return c1.d < c2.d;
    }
};

struct Heap_cmp
{
    bool operator()(const Course& c1, const Course& c2) const
    {
        return c1.t < c2.t;
    }
};

class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        int n = courses.size();
        vector<Course> cs;
        for(int i = 0; i < n; ++i)
            cs.emplace_back(courses[i][0], courses[i][1]);
        sort(cs.begin(), cs.end(), Sort_cmp());
        priority_queue<Course, vector<Course>, Heap_cmp> pq;
        int left = 1;
        for(const Course& c: cs)
        {
            pq.push(c);
            left += c.t;
            if(left - 1 > c.d)
            {
                left -= pq.top().t;
                pq.pop();
            }
        }
        return pq.size();
    }
};
