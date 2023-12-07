
class FrontMiddleBackQueue {
public:
    FrontMiddleBackQueue() {
        l = list<int>();
        n = 0;
        it_mid = l.end();
    }

    void pushFront(int val) {
        l.push_front(val);
        n++;
        if(n == 1)
            it_mid = l.begin();
        else if(n % 2 == 1)
            it_mid = prev(it_mid);
    }

    void pushMiddle(int val) {
        n++;
        it_mid = l.insert(it_mid, val);
        if(n == 1)
            it_mid = l.begin();
        if(n % 2 == 0)
            it_mid = next(it_mid);
    }

    void pushBack(int val) {
        n++;
        l.push_back(val);
        if(n == 1)
            it_mid = l.begin();
        else if(n % 2 == 0)
            it_mid = next(it_mid);
    }

    int popFront() {
        if(l.empty())
            return -1;
        int ans = l.front();
        l.pop_front();
        n--;
        if(n == 0)
            it_mid = l.end();
        else if(n % 2 == 0)
            it_mid = next(it_mid);
        return ans;
    }

    int popMiddle() {
        if(l.empty())
            return -1;
        int ans;
        if(n % 2 == 1)
        {
            ans = *it_mid;
            it_mid = l.erase(it_mid);
        }
        else
        {
            ans = *(prev(it_mid));
            it_mid = l.erase(prev(it_mid));
        }
        n--;
        if(n == 0)
            it_mid = l.end();
        return ans;
    }

    int popBack() {
        if(l.empty())
            return -1;
        int ans = l.back();
        l.pop_back();
        n--;
        if(n == 0)
            it_mid = l.end();
        else if(n == 1)
            it_mid = l.begin();
        else if(n % 2 == 1)
            it_mid = prev(it_mid);
        return ans;
    }

    void show()
    {
        cout << "len " << l.size() << endl;

        for(const auto& x: l) cout << x << " ";
        cout << endl;
    }

private:
    list<int> l;
    int n;
    list<int>::iterator it_mid;
};
