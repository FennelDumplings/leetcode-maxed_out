
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

struct Token
{
    string id;
    int t;
    Token(string id, int t):id(id),t(t){}
};

struct Cmp
{
    bool operator()(const Token& t1, const Token& t2) const
    {
        if(t1.t == t2. t)
            return t1.id < t2.id;
        return t1.t < t2.t;
    }
};


class AuthenticationManager {
public:
    AuthenticationManager(int timeToLive) {
        this -> timeToLive = timeToLive;
        tokens = set<Token, Cmp>();
        mapping = unordered_map<string, int>();
    }

    void generate(string tokenId, int currentTime) {
        mapping[tokenId] = currentTime;
        tokens.insert(Token(tokenId, currentTime));
    }

    void renew(string tokenId, int currentTime) {
        if(mapping.count(tokenId) == 0 || currentTime - mapping[tokenId] >= timeToLive)
            return;
        tokens.erase(tokens.find(Token(tokenId, mapping[tokenId])));
        tokens.insert(Token(tokenId, currentTime));
        mapping[tokenId] = currentTime;
    }

    int countUnexpiredTokens(int currentTime) {
        auto it = tokens.begin();
        while(it != tokens.end() && currentTime - (*it).t >= timeToLive)
            it = tokens.erase(it);
        return tokens.size();
    }

private:
    set<Token, Cmp, Equal> tokens;
    unordered_map<string, int> mapping;
    int timeToLive;
};

/**
 * Your AuthenticationManager object will be instantiated and called as such:
 * AuthenticationManager* obj = new AuthenticationManager(timeToLive);
 * obj->generate(tokenId,currentTime);
 * obj->renew(tokenId,currentTime);
 * int param_3 = obj->countUnexpiredTokens(currentTime);
 */
