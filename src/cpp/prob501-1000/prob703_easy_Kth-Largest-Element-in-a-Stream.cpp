// prob703: Kth Largest Element in a Stream

/*
 * Design a class to find the kth largest element in a stream. Note that it is the kth largest element in the sorted order, not the kth distinct element.
 * Your KthLargest class will have a constructor which accepts an integer k and an integer array nums, which contains initial elements from the stream.
 * For each call to the method KthLargest.add, return the element representing the kth largest element in the stream.
 */

/*
 * Example:
 * int k = 3;
 * int[] arr = [4,5,8,2];
 * KthLargest kthLargest = new KthLargest(3, arr);
 * kthLargest.add(3);   // returns 4
 * kthLargest.add(5);   // returns 5
 * kthLargest.add(10);  // returns 5
 * kthLargest.add(9);   // returns 8
 * kthLargest.add(4);   // returns 8
 */

/*
 * Note:
 * You may assume that nums' length ≥ k-1 and k ≥ 1.
 */

#include <vector>
#include <queue>
#include <set>

using namespace std;

class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) {
        K = k;
        int n = nums.size();
        pq = priority_queue<int, vector<int>, greater<int> >();
        for(int i = 0; i < n; ++i)
        {
            if((int)pq.size() < K)
            {
                pq.push(nums[i]);
                continue;
            }
            if(nums[i] > pq.top())
            {
                pq.pop();
                pq.push(nums[i]);
            }
        }
    }

    int add(int val) {
        if((int)pq.size() < K)
        {
            pq.push(val);
            return pq.top();
        }
        if(val > pq.top())
        {
            pq.pop();
            pq.push(val);
        }
        return pq.top();
    }

private:
    priority_queue<int, vector<int>, greater<int> > pq;
    int K;
};

// multiset
class KthLargest_2 {
public:
    KthLargest_2(int k, vector<int>& nums) {
        for (int n : nums) {
            st.insert(n);
            if((int)st.size() > k) st.erase(st.begin());
        }
        K = k;
    }

    int add(int val) {
        st.insert(val);
        if((int)st.size() > K) st.erase(st.begin());
        return *st.begin();
    }

private:
    int K;
    multiset<int> st;
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
