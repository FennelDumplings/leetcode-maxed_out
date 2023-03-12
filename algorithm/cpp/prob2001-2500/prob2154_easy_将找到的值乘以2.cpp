class Solution {
public:
    int findFinalValue(vector<int>& nums, int original) {
        unordered_set<int> setting;
        for(int x: nums)
            setting.insert(x);
        while(setting.count(original) > 0)
            original *= 2;
        return original;
    }
};
