// 20200607
// 3. 设计浏览器历史记录

/*
 * 你有一个只有一个标签页的 浏览器 ，一开始你浏览的网页是 homepage ，你可以访问其他的网站 url ，也可以在浏览历史中后退 steps 步或前进 steps 步。
 *
 * 请你实现 BrowserHistory 类：
 *
 * BrowserHistory(string homepage) ，用 homepage 初始化浏览器类。
 * void visit(string url) 从当前页跳转到访问页面 url 。执行此操作会把浏览历史前进的记录全部删除。
 * string back(int steps) 在浏览历史中后退 steps 步。如果你只能在浏览历史中后退至多 x 步且 steps > x ，那么你只后退 x 步。请返回后退 至多 steps 步以后的 url 。
 * string forward(int steps) 在浏览历史中前进 steps 步。如果你只能在浏览历史中前进至多 x 步且 steps > x ，那么你只前进 x 步。请返回前进 至多 steps步以后的 url 。
 */

#include <vector>
#include <string>

using namespace std;

class BrowserHistory {
public:
    BrowserHistory(string homepage) {
        cache = vector<string>({homepage});
        pos = 0;
        max_pos = pos;
    }

    void visit(string url) {
        cache.erase(cache.begin() + pos + 1, cache.end());
        cache.push_back(url);
        ++pos;
        max_pos = pos;
    }

    string back(int steps) {
        if(pos - steps >= 0)
            pos -= steps;
        else
            pos = 0;
        return cache[pos];
    }

    string forward(int steps) {
        if(pos + steps <= max_pos)
            pos += steps;
        else
            pos = max_pos;
        return cache[pos];
    }

private:
    vector<string> cache;
    int pos;
    int max_pos;
};
