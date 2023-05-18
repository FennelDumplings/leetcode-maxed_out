struct Event
{
    int idx;
    int side; // 0 表示左，1 表示右
    Event(){}
    Event(int idx, int side):idx(idx),side(side){}
};

struct Cmp
{
    bool operator()(const Event& e1, const Event& e2) const
    {
        if(e1.idx == e2.idx)
            return e1.side < e2.side; // 左排前面
        return e1.idx < e2.idx;
    }
};

class Solution {
public:
    bool haveConflict(vector<string>& event1, vector<string>& event2) {
        vector<Event> events;
        events.push_back(Event(parse(event1[0]), 0));
        events.push_back(Event(parse(event1[1]), 1));
        events.push_back(Event(parse(event2[0]), 0));
        events.push_back(Event(parse(event2[1]), 1));
        sort(events.begin(), events.end(), Cmp());
        int cnt = 0;
        for(const Event &e: events)
        {
            if(e.side == 0)
                cnt++;
            else
                cnt--;
            if(cnt > 1)
                return true;
        }
        return false;
    }

    int parse(const string& s)
    {
        int m = 0;
        m += (s[0] - '0') * 10 * 60;
        m += (s[1] - '0') * 60;
        m += (s[3] - '0') * 10;
        m += (s[4] - '0');
        return m;
    }
};
