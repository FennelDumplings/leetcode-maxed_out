// prob65: Valid Number

/*
 *
 * Validate if a given string can be interpreted as a decimal number.
 * Some examples:
 * "0" => true
 * " 0.1 " => true
 * "abc" => false
 * "1 a" => false
 * "2e10" => true
 * " -90e3   " => true
 * " 1e" => false
 * "e3" => false
 * " 6e-1" => true
 * " 99e2.5 " => false
 * "53.5e93" => true
 * " --6 " => false
 * "-+3" => false
 * "95a54e53" => false
 */

/*
 * Note: It is intended for the problem statement to be ambiguous.
 * You should gather all requirements up front before implementing one.
 * However, here is a list of characters that can be in a valid decimal number:
 * Numbers 0-9
 * Exponent - "e"
 * Positive/negative sign - "+"/"-"
 * Decimal point - "."
 */

#include <vector>
#include <string>

using namespace std;

class Solution_2 {
public:
    bool isNumber(string s) {
        if(s.empty()) return false;
        int n = s.size();

        int state = 0;
        vector<bool> finals({0, 0, 0, 1, 0, 1, 1, 0, 1}); // 合法的终止状态
        vector<vector<int> > transfer({
                {0,  1,  6,  2,  -1, -1},
                {-1, -1, 6,  2,  -1, -1},
                {-1, -1, 3,  -1, -1, -1},
                {8,  -1, 3,  -1, 4,  -1},
                {-1, 7,  5,  -1, -1, -1},
                {8,  -1, 5,  -1, -1, -1},
                {8,  -1, 6,  3,  4,  -1},
                {-1, -1, 5,  -1, -1, -1},
                {8,  -1, -1, -1, -1, -1},
                });

        for(int i = 0; i < n; ++i)
        {
            state = transfer[state][_make(s[i])];
            if(state < 0) return false;
        }
        return finals[state];
    }

private:
    int _make(const char& c)
    {
        switch(c)
        {
            case ' ': return 0;
            case '+': return 1;
            case '-': return 1;
            case '.': return 3;
            case 'e': return 4;
            default: return _number(c);
        }
    }

    int _number(char c)
    {
        if(c >= '0' && c <= '9')
            return 2;
        else
            return 5;
    }
};

#include <regex>

class Solution_1 {
public:
    bool isNumber(string s) {
        regex reg("^\\s*[+-]?(\\.\\d+|\\d+\\.?\\d*)([eE][+-]?\\d+)?\\s*$");
        bool flag = regex_match(s, reg);
        return flag;
    }
};

// ---------------------------
class Validator
{
public:
    virtual ~Validator(){}
    virtual bool validate(const string&) const =0;
};

class FalseValidator:public Validator
{
public:
    bool validate(const string& s) const
    {
        return false;
    }
};

class EmptyValidator:public Validator
{
public:
    EmptyValidator(Validator* p=nullptr):nxt(p){}
    bool validate(const string& s) const
    {
        if(s.empty())
            return false;
        int n = s.size();
        int i = 0;
        while(i < n)
        {
            if(s[i] != ' ')
                return nxt -> validate(s);
            ++i;
        }
        return false;
    }

private:
    Validator *nxt;
};

class IntegerValidator:public Validator
{
public:
    IntegerValidator(Validator* p=nullptr):nxt(p){}
    bool validate(const string& s) const
    {
        int i = s.find_first_not_of(' ');
        if(s[i] == '+' || s[i] == '-') ++i;
        int d = 0;
        while(i < (int)s.length() && isdigit(s[i]))
        {
            ++d;
            ++i;
        }
        while(i < (int)s.length() && s[i]==' ')
            ++i;
        if(i == (int)s.length() && d > 0)
            return true;
        else
            return nxt -> validate(s);
    }

private:
    Validator *nxt;
};

class FloatValidator:public Validator
{
public:
    FloatValidator(Validator* p=nullptr):nxt(p){}
    bool validate(const string& s) const
    {
        if(s.empty()) return nxt -> validate(s);
        int i = s.find_first_not_of(' ');
        if(s[i] == '+' || s[i] == '-') ++i;
        int d1 = 0, point = 0, d2 = 0;
        while(i < (int)s.length() && isdigit(s[i]))
        {
            ++d1;
            ++i;
        }
        while(i < (int)s.length() && s[i] == '.')
        {
            ++point;
            ++i;
        }
        if(point !=0 && point != 1) return false;
        while(i < (int)s.length() && isdigit(s[i]))
        {
            ++d2;
            ++i;
        }
        while(i < (int)s.length() && s[i] == ' ')
        {
            ++point;
            ++i;
        }
        if(i == (int)s.length() && ((point && (d1 || d2)) || d1))
            return true;
        else
            return nxt -> validate(s);
    }

private:
    Validator *nxt;
};

class ScienceValidator:public Validator
{
public:
    ScienceValidator(Validator* p=nullptr):nxt(p){}
    bool validate(const string& s) const
    {
        int i = s.find_first_of('e');
        FalseValidator false_validator;
        FloatValidator before(&false_validator);
        IntegerValidator after(&false_validator);
        string before_e = s.substr(0, i);
        string after_e = s.substr(i + 1, s.size() - i - 1);
        if(before_e.size() - 1 == before_e.find_last_of(' '))
            return false;
        if(after_e.find_first_of(' ') == 0)
            return false;
        if(before_e.empty() || after_e.empty())
            return false;
        if(before.validate(before_e) && after.validate(after_e))
            return true;
        else
            return nxt -> validate(s);
    }

private:
    Validator *nxt;
};

class NumberValidator
{
private:
    FalseValidator false_validator;
    IntegerValidator integer_validator;
    EmptyValidator empty_validator;
    FloatValidator float_validator;
    ScienceValidator science_validator;
public:
    NumberValidator()
    {
        false_validator = FalseValidator();
        empty_validator = EmptyValidator(&integer_validator);
        integer_validator = IntegerValidator(&float_validator);
        float_validator = FloatValidator(&science_validator);
        science_validator = ScienceValidator(&false_validator);
    }
    bool operator()(const string& s) const
    {
        return empty_validator.validate(s);
    }
};

class Solution {
public:
    bool isNumber(string &s) {
        NumberValidator validator;
        return validator(s);
    }
};
