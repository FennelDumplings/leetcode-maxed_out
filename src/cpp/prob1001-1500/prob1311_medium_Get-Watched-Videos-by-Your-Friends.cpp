// prob1311: Get Watched Videos by Your Friends

/*
 * There are n people, each person has a unique id between 0 and n-1. Given the arrays watchedVideos and friends, where watchedVideos[i] and friends[i] contain the list of watched videos and the list of friends respectively for the person with id = i.
 * Level 1 of videos are all watched videos by your friends, level 2 of videos are all watched videos by the friends of your friends and so on. In general, the level k of videos are all watched videos by people with the shortest path exactly equal to k with you. Given your id and the level of videos, return the list of videos ordered by their frequencies (increasing). For videos with the same frequency order them alphabetically from least to greatest. 
 */

/*
 * Example 1:
 * Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 1
 * Output: ["B","C"]
 * Explanation:
 * You have id = 0 (green color in the figure) and your friends are (yellow color in the figure):
 * Person with id = 1 -> watchedVideos = ["C"] 
 * Person with id = 2 -> watchedVideos = ["B","C"] 
 * The frequencies of watchedVideos by your friends are: 
 * B -> 1 
 * C -> 2
 * Example 2:
 * Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 2
 * Output: ["D"]
 * Explanation:
 * You have id = 0 (green color in the figure) and the only friend of your friends is the person with id = 3 (yellow color in the figure).
 */

/*
 * Constraints:
 * n == watchedVideos.length == friends.length
 * 2 <= n <= 100
 * 1 <= watchedVideos[i].length <= 100
 * 1 <= watchedVideos[i][j].length <= 8
 * 0 <= friends[i].length < n
 * 0 <= friends[i][j] < n
 * 0 <= id < n
 * 1 <= level < n
 * if friends[i] contains j, then friends[j] contains i
 */

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

struct Video
{
    string name;
    int frequency;
    Video(const string& name, int frequency):name(name),frequency(frequency){}
};

struct Cmp
{
    bool operator()(const Video& v1, const Video& v2)
    {
        if(v1.frequency == v2.frequency)
            return v1.name < v2.name;
        return v1.frequency < v2.frequency;
    }
};

class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {
        int n = friends.size();
        queue<int> q;
        q.push(id);
        vector<bool> visited(n, false);
        visited[id] = true;
        int l = 0;
        vector<int> level_nodes;
        unordered_map<string, int> cnts; // name -> frequency
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            if(l == level)
            {
                for(int node: level_nodes)
                {
                    for(const string& name: watchedVideos[node])
                        ++cnts[name];
                }
                break;
            }
            for(int node: level_nodes)
            {
                for(int son: friends[node])
                {
                    if(visited[son])
                        continue;
                    visited[son] = true;
                    q.push(son);
                }
            }
            ++l;
        }
        vector<Video> videos;
        for(const auto item: cnts)
            videos.push_back(Video(item.first, item.second));
        sort(videos.begin(), videos.end(), Cmp());
        vector<string> result((int)videos.size());
        for(int i = 0; i < (int)videos.size(); ++i)
            result[i] = videos[i].name;
        return result;
    }
};
