
#include <map>
#include <vector>

using namespace std;

class Solution {
public:
    int findLatestStep(vector<int>& arr, int m) {
        int n = arr.size();
        string str(n, '0');
        map<int, int> ranges;
        for(int i = 0; i < n; ++i)
        {
            str[arr[i] - 1] = '1';
        }
        int left = 0;
        int ans = n;
        while(left < n)
        {
            while(left < n && str[left] == '0')
                ++left;
            if(left == n)
                break;
            int right = left + 1;
            while(right < n && str[right] == '1')
                ++right;
            if(right - left == m)
                return ans;
            ranges[left] = right - 1;
            left = right;
        }
        for(int i = n - 1; i >= 0; --i)
        {
            --ans;
            int mid = arr[i] - 1;
            auto it = ranges.upper_bound(mid);
            if(it != ranges.begin())
                --it;
            int l = it -> first;
            int r = it -> second;
            ranges.erase(it);
            if(l < mid)
            {
                int len_left = mid - l;
                if(len_left == m)
                    return ans;
                ranges[l] = mid - 1;
            }
            if(mid < r)
            {
                int len_right = r - mid;
                if(len_right == m)
                    return ans;
                ranges[mid + 1] = r;
            }
        }
        return -1;
    }
};
