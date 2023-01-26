// prob702: Search in a Sorted Array of Unknown Size

/*
 * https://leetcode-cn.com/problems/search-in-a-sorted-array-of-unknown-size/
 */

#include <climits>

using namespace std;

// This is the ArrayReader's API interface.
// You should not implement it, or speculate about its implementation
class ArrayReader {
  public:
    int get(int index) const;
};

class Solution {
public:
    int search(const ArrayReader& reader, int target) {
        int i = 0, step = 1;
        if(reader.get(0) == target)
            return 0;
        while(step > 0)
        {
            int cur = reader.get(i + step);
            if(cur == target)
                return i + step;
            else if(cur < target)
            {
                i += step;
                step *= 2;
            }
            else
                step /= 2;
        }
        return -1;
    }
};
