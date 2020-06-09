// prob321: Create Maximum Number

/*
 * Given two arrays of length m and n with digits 0-9 representing two numbers. Create the maximum number of length k <= m + n
 * from digits of the two. The relative order of the digits from the same array must be preserved. Return an array of the k digits.
 * Note: You should try to optimize your time and space complexity.
 */

/*
 * Example 1:
 * Input:
 * nums1 = [3, 4, 6, 5]
 * nums2 = [9, 1, 2, 5, 8, 3]
 * k = 5
 * Output:
 * [9, 8, 6, 5, 3]
 * Example 2:
 * Input:
 * nums1 = [6, 7]
 * nums2 = [6, 0, 4]
 * k = 5
 * Output:
 * [6, 7, 6, 0, 4]
 * Example 3:
 * Input:
 * nums1 = [3, 9]
 * nums2 = [8, 9]
 * k = 3
 * Output:
 * [9, 8, 9]
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int n1 = nums1.size(), n2 = nums2.size();
        vector<queue<int> > pos1(10), pos2(10);
        for(int i = 0; i < n1; ++i)
            pos1[nums1[i]].push(i);
        for(int i = 0; i < n2; ++i)
            pos2[nums2[i]].push(i);
        vector<int> result(k, -1);
        int iter = 0;
        int it1 = 0, it2 = 0;
        while(iter < k)
        {
            PII nxt = _nxt(nums1, it1, pos1, nums2, it2, pos2, k - iter);
            if(nxt.first == 1)
            {
                result[iter] = nums1[nxt.second];
                it1 = nxt.second + 1;
            }
            else
            {
                result[iter] = nums2[nxt.second];
                it2 = nxt.second + 1;
            }
            ++iter;
        }
        return result;
    }

private:
    using PII = pair<int, int>;

    PII _nxt(const vector<int>& nums1, int it1, vector<queue<int> >& pos1, const vector<int>& nums2, int it2, vector<queue<int> >& pos2, int k)
    {
        cout << it1 << " " << it2 << endl;
        int n1 = nums1.size(), n2 = nums2.size();
        for(int digit = 9; digit >= 0; --digit)
        {
            int idx1 = -1, idx2 = -1;
            while(!pos1[digit].empty() && pos1[digit].front() < it1)
                pos1[digit].pop();
            if(!pos1[digit].empty())
                idx1 = pos1[digit].front();
            if(idx1 != -1 && n2 - it2 + n1 - idx1 < k)
                idx1 = -1;
            while(!pos2[digit].empty() && pos2[digit].front() < it2)
                pos2[digit].pop();
            if(!pos2[digit].empty())
                idx2 = pos2[digit].front();
            if(idx2 != -1 && n2 - idx2 + n1 - it1 < k)
                idx2 = -1;

            if(idx1 == -1 && idx2 == -1)
                continue;
            if(idx1 == -1)
            {
                cout << pos2[digit].front() << " ";
                pos2[digit].pop();
                if(pos2[digit].empty()) cout << "empty";
                else cout << pos2[digit].front() << " ";
                cout << endl;
                cout << "===" << endl;
                return PII({2, idx2});
            }
            if(idx2 == -1)
            {
                cout << pos1[digit].front() << " " << it1 << " ";
                pos1[digit].pop();
                if(pos1[digit].empty()) cout << "empty";
                else cout << pos1[digit].front() << " ";
                cout << endl;
                cout << "===" << endl;
                return PII({1, idx1});
            }
            // idx1, idx2
            // nums1[it1..idx1), nums2[it2..idx2) 谁舍弃的更小
            vector<int> cnt1(10, 0), cnt2(10, 0); // 舍弃的数字
            for(int i = it1; i < idx1; ++i)
                ++cnt1[nums1[i]];
            for(int i = it2; i < idx2; ++i)
                ++cnt2[nums2[i]];
            for(int num = 9; num >= 0; --num)
            {
                if(cnt1[num] < cnt2[num])
                {
                    cout << pos1[digit].front() << " ";
                    pos1[digit].pop();
                    if(pos1[digit].empty()) cout << "empty";
                    else cout << pos1[digit].front() << " ";
                    cout << endl;
                    cout << "===" << endl;
                    return PII({1, idx1});
                }
                else if(cnt1[num] > cnt2[num])
                {
                    cout << pos2[digit].front() << " ";
                    pos2[digit].pop();
                    if(pos2[digit].empty()) cout << "empty";
                    else cout << pos2[digit].front() << " ";
                    cout << endl;
                    cout << "===" << endl;
                    return PII({2, idx2});
                }
            }
            // 比 idx1 + 1..n1 与 idx2 + 1..n2
            cout << pos1[digit].front() << " ";
            int i1 = idx1 + 1, i2 = idx2 + 1;
            while(i1 < n1 && i2 < n2)
            {
                if(nums1[i1] < nums2[i2])
                {
                    pos2[digit].pop();
                    return PII({2, idx2});
                }
                else if (nums1[i1] > nums2[i2])
                {
                    pos1[digit].pop();
                    return PII({1, idx1});
                }
                ++i1;
                ++i2;
            }
            if(i1 == n1)
            {
                pos2[digit].pop();
                return PII({2, idx2});
            }
            else
            {
                pos1[digit].pop();
                return PII({1, idx1});
            }
        }
        return PII({-1, -1});
    }
};
