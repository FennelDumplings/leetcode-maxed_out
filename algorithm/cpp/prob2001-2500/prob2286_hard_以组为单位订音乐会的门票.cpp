#include <vector>
#include <set>
#include <map>

using ll = long long;
using namespace std;

class BIT {
public:
    BIT():sums(1, 0){}
    BIT(int n):sums(n + 1, 0){}

    void update(int index, int delta)
    {
        int n = sums.size();
        while(index < n)
        {
            sums[index] += delta;
            index += _lowbit(index);
        }
    }

    ll query(int i)
    {
        ll sum = 0;
        while(i > 0)
        {
            sum += sums[i];
            i -= _lowbit(i);
        }
        return sum;
    }

private:
    vector<ll> sums;

    int _lowbit(int x)
    {
        return x & (-x);
    }
};

class SUMS {
public:
    SUMS(){}
    SUMS(vector<int> nums):vec(move(nums)),bit(vec.size()) {
        int n = vec.size();
        for(int i = 0; i < n; ++i)
            bit.update(i + 1, vec[i]);
    }

    void update(int i, int val) {
        bit.update(i + 1, val - vec[i]);
        vec[i] = val;
    }

    ll sumRange(int i, int j) {
        return bit.query(j + 1) - bit.query(i);
    }

private:
    vector<int> vec;
    BIT bit;
};

class BookMyShow {
public:
    BookMyShow(int n, int m) {
        this -> n = n;
        this -> m = m;
        rows = vector<int>(n, m);
        this -> sums = SUMS(rows);
        mapping = map<int, set<int>>();
        mapping[m] = set<int>();
        for(int i = 0; i < n; ++i)
            mapping[m].insert(i);
        min_l = 0;
    }

    vector<int> gather(int k, int maxRow) {
        auto r_set_iter = mapping.lower_bound(k);
        if(r_set_iter == mapping.end())
            return {};
        // 存在满足条件的行号，最小的那个是 r，最左边的列号为 c
        int R = r_set_iter -> first;
        int c = m - r_set_iter -> first;
        auto min_r_iter = (r_set_iter -> second).begin();
        int r = *min_r_iter;
        if(r > maxRow)
            return {};
        // 更新：第 r 行消耗 k 个座位
        R -= k;
        (r_set_iter -> second).erase(min_r_iter);
        if((r_set_iter -> second).empty())
            mapping.erase(r_set_iter);
        if(R > 0)
            mapping[R].insert(r);
        // rows 同步更新
        // 可能减到 0，min_l 的更新到 scatter 操作时再进行
        rows[r] -= k;
        sums.update(r, rows[r]);
        return {r, c};
    }

    bool scatter(int k, int maxRow) {
        if(sums.sumRange(0, maxRow) < k)
            return false;
        // 肯定能满足，逐行更新直至 k 耗尽即可
        while(k > 0)
        {
            int c = rows[min_l];
            if(c == 0)
            {
                min_l++;
                continue;
            }
            // 第 min_l 行肯定要操作，因此先将 mapping 对应节点删除
            // 后续是否插入新的节点看情况
            // 如果 c 为 0，则 mapping 中相应节点已经删掉了
            auto it = mapping.find(c);
            (it -> second).erase(min_l);
            if((it -> second).empty())
                mapping.erase(it);
            if(c >= k)
            {
                // 第 min_l 行已经可以满足所有需求
                rows[min_l] -= k;
                k = 0;
                sums.update(min_l, rows[min_l]);
                // 更新 mapping
                if(rows[min_l] > 0)
                    mapping[rows[min_l]].insert(min_l);
                if(rows[min_l] == 0)
                    min_l++;
            }
            else
            {
                // 第 min_l 行剩余的 c 尚不满足需求，将剩余数清零
                k -= c;
                rows[min_l] = 0;
                sums.update(min_l, rows[min_l]);
                min_l++;
            }
        }
        return true;
    }

private:
    int n, m;
    int min_l; // 有座位的最小行号
    vector<int> rows; // rows[i] 为第 i 行还剩多少座位
    SUMS sums; // sums[i] 为前 0 ~ i-1 行还剩的总座位数
    // mapping[c] 表示剩余座位数为 c 的行号集合，行号集合是另一个平衡树
    map<int, set<int>> mapping;
};
