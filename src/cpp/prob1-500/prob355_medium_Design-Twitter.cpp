// prob355: Design Twitter

/*
 * Design a simplified version of Twitter where users can post tweets, follow/unfollow another user and is
 * able to see the 10 most recent tweets in the user's news feed. Your design should support the following methods:
 * postTweet(userId, tweetId): Compose a new tweet.
 * getNewsFeed(userId): Retrieve the 10 most recent tweet ids in the user's news feed.
 * Each item in the news feed must be posted by users who the user followed or by the user herself.
 * Tweets must be ordered from most recent to least recent.
 * follow(followerId, followeeId): Follower follows a followee.
 * unfollow(followerId, followeeId): Follower unfollows a followee.
 */

/*
 * Example:
 * Twitter twitter = new Twitter();
 * // User 1 posts a new tweet (id = 5).
 * twitter.postTweet(1, 5);
 * // User 1's news feed should return a list with 1 tweet id -> [5].
 * twitter.getNewsFeed(1);
 * // User 1 follows user 2.
 * twitter.follow(1, 2);
 * // User 2 posts a new tweet (id = 6).
 * twitter.postTweet(2, 6);
 * // User 1's news feed should return a list with 2 tweet ids -> [6, 5].
 * // Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
 * twitter.getNewsFeed(1);
 * // User 1 unfollows user 2.
 * twitter.unfollow(1, 2);
 * // User 1's news feed should return a list with 1 tweet id -> [5],
 * // since user 1 is no longer following user 2.
 * twitter.getNewsFeed(1);
 */


#include <vector>
#include <queue>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

using namespace std;

struct TwitterInfo
{
    TwitterInfo(int tweetid=-1, int time=-1): tweetid(tweetid), time(time) {}
    int tweetid;
    int time;
};

struct UserInfo
{
    UserInfo()
    {
        followees = unordered_set<int>();
        twitters = list<TwitterInfo>();
    }
    unordered_set<int> followees; // 当前用户关注的用户集合
    list<TwitterInfo> twitters; // 当前用户推特列表，越靠前越新
};

class Twitter {
public:
    /** Initialize your data structure here. */
    Twitter() {
        usersinfo = unordered_map<int, UserInfo>();
        twitter_cnt = 0;
    }

    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        // 若用户id没见过则新建用户
        if(usersinfo.find(userId) == usersinfo.end())
            usersinfo[userId] = UserInfo();
        // 在用户信息中更新当前推特
        usersinfo[userId].twitters.push_front(TwitterInfo(tweetId, twitter_cnt));
        ++twitter_cnt;
    }

    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        vector<list<TwitterInfo>*> cand;
        cand.push_back(&usersinfo[userId].twitters);
        for(int followee_id: usersinfo[userId].followees)
            cand.push_back(&usersinfo[followee_id].twitters);
        return _mergeKLists(cand);
    }

    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        // 若用户id没见过则新建用户
        if(usersinfo.find(followerId) == usersinfo.end())
            usersinfo[followerId] = UserInfo();
        if(usersinfo.find(followeeId) == usersinfo.end())
            usersinfo[followeeId] = UserInfo();
        // 处理关注
        unordered_set<int> &followees = usersinfo[followerId].followees;
        if(followerId == followeeId || followees.find(followeeId) != followees.end())
            return;
        usersinfo[followerId].followees.insert(followeeId);
    }

    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        // 若用户id没见过则新建用户
        if(usersinfo.find(followerId) == usersinfo.end())
            usersinfo[followerId] = UserInfo();
        if(usersinfo.find(followeeId) == usersinfo.end())
            usersinfo[followeeId] = UserInfo();
        // 处理取关
        unordered_set<int> &followees = usersinfo[followerId].followees;
        if(followerId == followeeId || followees.find(followeeId) == followees.end())
            return;
        usersinfo[followerId].followees.erase(followeeId);
    }

private:
    unordered_map<int, UserInfo> usersinfo;
    int twitter_cnt; // 记录次序

    using lTi = list<TwitterInfo>::iterator;
    using PLL = pair<lTi, lTi>;

    vector<int> _mergeKLists(const vector<list<TwitterInfo>*>& lists) {
        if(lists.empty()) return {};
        priority_queue<PLL, vector<PLL>, Cmp> pq;
        for(list<TwitterInfo> *l : lists)
        {
            if(!(l -> empty()))
                pq.push(PLL({l -> begin(), l -> end()}));
        }
        if(pq.empty()) return {};
        vector<int> result;
        while(!pq.empty())
        {
            PLL top = pq.top();
            pq.pop();
            result.push_back(top.first -> tweetid);
            if((int)result.size() == 10)
                return result;
            ++top.first;
            if(top.first != top.second)
                pq.push(top);
        }
        return result;
    }

    struct Cmp
    {
        bool operator () (const PLL& left, const PLL& right)
        {
            return (left.first -> time) < (right.first -> time); // > 是小顶堆；< 是大顶堆
        }
    };
};
