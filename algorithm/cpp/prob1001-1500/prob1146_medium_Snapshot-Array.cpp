// prob1146: Snapshot Array

/*
 * Implement a SnapshotArray that supports the following interface:
 * SnapshotArray(int length) initializes an array-like data structure with the given length.  Initially, each element equals 0.
 * void set(index, val) sets the element at the given index to be equal to val.
 * int snap() takes a snapshot of the array and returns the snap_id: the total number of times we called snap() minus 1.
 * int get(index, snap_id) returns the value at the given index, at the time we took the snapshot with the given snap_id
 */

/*
 * Example 1:
 * Input: ["SnapshotArray","set","snap","set","get"]
 * [[3],[0,5],[],[0,6],[0,0]]
 * Output: [null,null,0,null,5]
 * Explanation:
 * SnapshotArray snapshotArr = new SnapshotArray(3); // set the length to be 3
 * snapshotArr.set(0,5);  // Set array[0] = 5
 * snapshotArr.snap();  // Take a snapshot, return snap_id = 0
 * snapshotArr.set(0,6);
 * snapshotArr.get(0,0);  // Get the value of array[0] with snap_id = 0, return 5
 */

/*
 * Constraints:
 * 1 <= length <= 50000
 * At most 50000 calls will be made to set, snap, and get.
 * 0 <= index < length
 * 0 <= snap_id < (the total number of times we call snap())
 * 0 <= val <= 10^9
 */

#include <vector>
#include <map>
#include <unordered_set>

using namespace std;

class SnapshotArray {
public:
    SnapshotArray(int length) {
        vec = vector<Item>(length, Item(0));
        cnt = 0;
        changes = unordered_set<int>();
    }

    void set(int index, int val) {
        vec[index].val = val;
        changes.insert(index);
    }

    int snap() {
        for(int change: changes)
        {
            Item &item = vec[change];
            item.snapshots[cnt] = item.val;
            item.prev_snap_id = cnt;
        }
        changes.clear();
        return cnt++;
    }

    int get(int index, int snap_id) {
        map<int, int> &target_snaps = vec[index].snapshots;
        // 在 target_snaps 找小于等于 snap_id 的第一个 id
        // 例如 snap_id = 10 ，找 10，9, 8, 7, ..., 0 中最大的
        if(target_snaps.empty()) // 任意一次快照时，vec[i].val 均为变过，即一直是0
            return 0;
        auto it = target_snaps.lower_bound(snap_id);
        if(it != target_snaps.end() && it -> first == snap_id)
            return it -> second;
        // it 前移一位
        if(it == target_snaps.begin())
            return 0;
        --it;
        return it -> second;
    }

private:
    using PII = pair<int, int>;

    struct Item
    {
        map<int, int> snapshots;
        int prev_snap_id;
        int val;
        Item(int val):val(val)
        {
            snapshots = map<int, int>();
            prev_snap_id = -1;
        }
    };
    vector<Item> vec;
    int cnt;
    unordered_set<int> changes;
};

// TLE
class SnapshotArray_2 {
public:
    SnapshotArray_2(int length) {
        vec = vector<Item>(length, Item(0));
        cnt = 0;
    }

    void set(int index, int val) {
        vec[index].val = val;
    }

    int snap() {
        for(int i = 0; i < (int)vec.size(); ++i)
        {
            Item &item = vec[i];
            if(item.snapshots.empty())
            {
                if(item.val != 0)
                    item.snapshots[cnt] = item.val;
                continue;
            }
            if(item.snapshots[item.prev_snap_id] != item.val)
            {
                item.snapshots[cnt] = item.val;
                item.prev_snap_id = cnt;
            }
        }
        return cnt++;
    }

    int get(int index, int snap_id) {
        map<int, int> &target_snaps = vec[index].snapshots;
        // 在 target_snaps 找小于等于 snap_id 的第一个 id
        // 例如 snap_id = 10 ，找 10，9, 8, 7, ..., 0 中最大的
        if(target_snaps.empty()) // 任意一次快照时，vec[i].val 均为变过，即一直是0
            return 0;
        auto it = target_snaps.lower_bound(snap_id);
        if(it != target_snaps.end() && it -> first == snap_id)
            return it -> second;
        // it 前移一位
        if(it == target_snaps.begin())
            return 0;
        --it;
        return it -> second;
    }

private:
    using PII = pair<int, int>;

    struct Item
    {
        map<int, int> snapshots;
        int prev_snap_id;
        int val;
        Item(int val):val(val)
        {
            snapshots = map<int, int>();
            prev_snap_id = -1;
        }
    };
    vector<Item> vec;
    int cnt;
};
