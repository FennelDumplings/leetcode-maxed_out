// prob855: Exam Room

/*
 * In an exam room, there are N seats in a single row, numbered 0, 1, 2, ..., N-1.
 * When a student enters the room, they must sit in the seat that maximizes the distance to the closest person.  If there are multiple such seats, they sit in the seat with the lowest number.  (Also, if no one is in the room, then the student sits at seat number 0.)
 * Return a class ExamRoom(int N) that exposes two functions: ExamRoom.seat() returning an int representing what seat the student sat in, and ExamRoom.leave(int p) representing that the student in seat number p now leaves the room.  It is guaranteed that any calls to ExamRoom.leave(p) have a student sitting in seat p.
 */

/*
 * Example 1:
 * Input: ["ExamRoom","seat","seat","seat","seat","leave","seat"], [[10],[],[],[],[],[4],[]]
 * Output: [null,0,9,4,2,null,5]
 * Explanation:
 * ExamRoom(10) -> null
 * seat() -> 0, no one is in the room, then the student sits at seat number 0.
 * seat() -> 9, the student sits at the last seat number 9.
 * seat() -> 4, the student sits at the last seat number 4.
 * seat() -> 2, the student sits at the last seat number 2.
 * leave(4) -> null
 * seat() -> 5, the student sits at the last seat number 5.
 */

#include <set>

using namespace std;

struct Range
{
    int left, right;
    Range(int l, int r):left(l),right(r){}
};

struct Cmp
{
    bool operator()(const Range& r1, const Range& r2) const
    {
        int len1 = (r1.right - r1.left) / 2;
        int len2 = (r2.right - r2.left) / 2;
        if(len1 == len2)
            return r1.left < r2.left;
        return len1 > len2;
    }
};

class ExamRoom {
public:
    ExamRoom(int N):N(N) {
        set<int> used; // 有人的座位
        set<Range, Cmp> ranges;
        // ranges 按照区间长度排序, 按照左端点查找
    }

    int seat() {
        if(used.empty())
        {
            int result = 0;
            used.insert(result);
            return result;
        }
        if(used.size() == 1)
        {
            int pos = *used.begin();
            if(pos >= N - 1 - pos)
            {
                used.insert(0);
                ranges.insert(Range(0, pos));
                return 0;
            }
            else
            {
                used.insert(N - 1);
                ranges.insert(Range(pos, N - 1));
                return N - 1;
            }
        }
        int kind = 1; // 1: 两个人之间, 2: 最左, 3: 最右
        auto middle_range_it = ranges.begin();
        int cand = middle_range_it -> left;
        int cand_space = ((middle_range_it -> right) + cand) / 2 - cand;
        auto left_most = used.begin();
        auto right_most = used.rbegin();
        if(*left_most != 0)
        {
            if(*left_most >= cand_space)
            {
                kind = 2;
                cand_space = *left_most;
                cand = 0;
            }
        }
        if(*right_most != N - 1)
        {
            int right_most_pos = *right_most;
            int len = (N - 1) - right_most_pos;
            if(len > cand_space)
            {
                cand_space = len;
                cand = N - 1;
                kind = 3;
            }
        }
        if(kind == 1)
        {
            int right = middle_range_it -> right;
            int result = cand + cand_space;
            ranges.erase(middle_range_it); // middle_range_it 左端有区间的化需要修改
            ranges.insert(Range(cand, result));
            ranges.insert(Range(result, right));
            used.insert(result);
            return result;
        }
        else if(kind == 2)
        {
            ranges.insert(Range(cand, cand + cand_space));
            used.insert(cand);
            return cand;
        }
        else
        {
            used.insert(cand);
            ranges.insert(Range(cand - cand_space, cand));
            return cand;
        }
    }

    void leave(int p) {
        auto it = used.find(p);
        if(used.size() == 1)
        {
            used.erase(it);
            return;
        }
        if(used.size() == 2)
        {
            ranges.erase(ranges.begin());
            used.erase(it);
            return;
        }
        // ranges 里至少两个区间 (3 个人)
        if(it == used.begin())
        {
            int l = *it;
            ++it;
            int r = *it;
            --it;
            used.erase(it);
            ranges.erase(ranges.find(Range(l, r)));
        }
        else if(it == (--used.end()))
        {
            int r = *it;
            --it;
            int l = *it;
            ++it;
            used.erase(it);
            ranges.erase(ranges.find(Range(l, r)));
        }
        else
        {
            int mid = *it;
            ++it;
            int r = *it;
            --it;
            --it;
            int l = *it;
            ++it;
            used.erase(it);
            ranges.erase(ranges.find(Range(mid, r)));
            ranges.erase(ranges.find(Range(l, mid)));
            ranges.insert(Range(l, r));
        }
    }

private:
    set<int> used; // 有人的座位
    set<Range, Cmp> ranges;
    // ranges 按照区间长度排序, 按照左端点查找
    int N;
};
