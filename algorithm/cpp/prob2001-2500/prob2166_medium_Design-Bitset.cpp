
class Bitset {
private:
    int n1;
    int n;
    string setting;
    int n_flip;

public:
    Bitset(int size) {
        n1 = 0;
        n = size;
        n_flip = 0;
        setting = string(size, '0');
    }

    void fix(int idx) {
        if(setting[idx] != '1' && (n_flip % 2 == 0))
        {
            setting[idx] = '1';
            ++n1;
        }
        else if(setting[idx] == '1' && (n_flip % 2 == 1))
        {
            setting[idx] = '0';
            ++n1;
        }
    }

    void unfix(int idx) {
        if(setting[idx] != '0' && (n_flip % 2 == 0))
        {
            setting[idx] = '0';
            --n1;
        }
        else if(setting[idx] == '0' && (n_flip % 2 == 1))
        {
            setting[idx] = '1';
            --n1;
        }
    }

    void flip() {
        n1 = n - n1;
        n_flip += 1;
    }

    bool all() {
        return n1 == n;
    }

    bool one() {
        return n1 > 0;
    }

    int count() {
        return n1;
    }

    string toString() {
        if(n_flip & 1)
        {
            string result(n, '1');
            for(int i = 0; i < n; ++i)
                if(setting[i] == '1')
                    result[i] = '0';
            return result;
        }
        else
            return setting;
    }
};
