
#include <vector>
#include <unordered_map>

using namespace std;

class FindSumPairs {
public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
        this -> nums2 = nums2;
        for(int x: nums1)
            ++mapping1[x];
        for(int x: nums2)
            ++mapping2[x];
    }

    void add(int index, int val) {
        --mapping2[nums2[index]];
        nums2[index] += val;
        ++mapping2[nums2[index]];
    }

    int count(int tot) {
        int ans = 0;
        for(auto item: mapping1)
        {
            int x = item.first, nx = item.second;
            int y = tot - x;
            if(mapping2.count(y) == 0)
                continue;
            int ny = mapping2[y];
            ans += nx * ny;
        }
        return ans;
    }

private:
    unordered_map<int, int> mapping1;
    unordered_map<int, int> mapping2;
    vector<int> nums2;
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */
