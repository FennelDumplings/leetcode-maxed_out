// prob1570: Dot Product of Two Sparse Vectors

/*
 * https://leetcode-cn.com/problems/dot-product-of-two-sparse-vectors/
 */


#include <vector>

using namespace std;

class SparseVector {
public:

    SparseVector(vector<int> &nums) {
        this -> n = nums.size();
        for(int i = 0; i < n; ++i)
        {
            sparse_vec.emplace_back(i, nums[i]);
        }
    }

    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec) {
        int n1 = (this -> sparse_vec).size();
        int n2 = vec.sparse_vec.size();
        int i1 = 0, i2 = 0;
        int ans = 0;
        while(i1 < n1 && i2 < n2)
        {
            if(i1 == i2)
            {
                ans += sparse_vec[i1].w * vec.sparse_vec[i2].w;
                ++i1;
                ++i2;
            }
            else
            {
                if(sparse_vec[i1].w < vec.sparse_vec[i2].w)
                    ++i1;
                else
                    ++i2;
            }
        }
        return ans;
    }

private:
    struct SparseItem
    {
        int idx;
        int w;
        SparseItem(int i, int w):idx(i),w(w){}
    };

    int n;
    vector<SparseItem> sparse_vec;
};
