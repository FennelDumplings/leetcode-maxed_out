// prob1500: Design a File Sharing System

/*
 * https://leetcode-cn.com/problems/design-a-file-sharing-system/
 */

#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>

using namespace std;

class FileSharing {
public:
    FileSharing(int m) {
        chunks_info = vector<set<int>>(m + 1);
        users_info = unordered_map<int, vector<int>>();
        pq = priority_queue<int, vector<int>, greater<int>>();
        max_id = 0;
    }

    int join(vector<int> ownedChunks) {
        int id = get_id();
        users_info[id] = ownedChunks;
        for(int chunkID: ownedChunks)
            chunks_info[chunkID].insert(id);
        return id;
    }

    void leave(int userID) {
        for(int chunkID: users_info[userID])
            chunks_info[chunkID].erase(userID);
        users_info[userID].clear();
        release_id(userID);
    }

    vector<int> request(int userID, int chunkID) {
        vector<int> users(chunks_info[chunkID].begin(), chunks_info[chunkID].end());
        if(!users.empty())
        {
            users_info[userID].push_back(chunkID);
            chunks_info[chunkID].insert(userID);
        }
        return users;
    }

    int get_id()
    {
        // 如果 pq 中有系统回收的 id，分配 pq 里的
        // pq 为空，则说明尚未有已分配的 id 回收，或者回收的 id 再次分配出去了，此时分派 max_id + 1
        if(!pq.empty())
        {
            int id = pq.top();
            pq.pop();
            return id;
        }
        return ++max_id;
    }

    void release_id(int userID)
    {
        // 释放的如果为 max_id，则 --max_id
        // 否则将释放的 id 压堆
        if(userID == max_id)
            --max_id;
        else
            pq.push(userID);
    }

private:
    vector<set<int>> chunks_info; // chunks_info[chunkID] := 持有 chunkID 的 userID 升序
    unordered_map<int, vector<int>> users_info; // users_info[userID] := userID 持有的所有 chunkID
    int max_id; // 系统中的最大 id
    priority_queue<int, vector<int>, greater<int>> pq; // 回收的 id
};
