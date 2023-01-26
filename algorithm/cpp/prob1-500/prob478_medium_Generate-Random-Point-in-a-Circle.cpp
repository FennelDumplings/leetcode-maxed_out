// prob478: Generate Random Point in a Circle

/*
 * https://leetcode-cn.com/problems/generate-random-point-in-a-circle/
 */

#include <vector>
#include <random>

using namespace std;

class Solution_2 {
public:
    Solution_2(double radius, double x_center, double y_center) {
        r = radius;
        x = x_center;
        y = y_center;
        dre = std::default_random_engine();
        x1 = x_center - r;
        x2 = x_center + r;
        y1 = y_center - r;
        y2 = y_center + r;
        dr_x = std::uniform_real_distribution<double>(x1, x2);
        dr_y = std::uniform_real_distribution<double>(y1, y2);
    }

    vector<double> randPoint() {
        double i, j;
        while(true)
        {
            i = dr_x(dre);
            j = dr_y(dre);
            if(sqrt(pow((x - i), 2) + pow((y - j), 2)) <= r)
                break;
        }
        return vector<double>{i, j};
    }

private:
    double r, x, y;
    // 左下 (x1, y1) 右上 (x2, y2)
    double x1, y1, x2, y2;
    std::default_random_engine dre;
    std::uniform_real_distribution<double> dr_x;
    std::uniform_real_distribution<double> dr_y;
};


#include <cmath>

class Solution {
public:
    Solution(double radius, double x_center, double y_center) {
        x = x_center;
        y = y_center;
        r = radius;
        dre = std::default_random_engine();
        d_theta = std::uniform_real_distribution<double>(0, 2 * PI);
        d_r = std::uniform_real_distribution<double>(0.0, std::nextafter(1.0, std::numeric_limits<double>::max()));
    }

    vector<double> randPoint() {
        double r = sqrt(d_r(dre)) * (this -> r);
        double theta = d_theta(dre);
        double x = r * cos(theta);
        double y = r * sin(theta);
        return {this -> x + x, this -> y + y};
    }

private:
    const long double PI = 3.14159265358979323846;
    double r, x, y;
    std::default_random_engine dre;
    std::uniform_real_distribution<double> d_theta;
    std::uniform_real_distribution<double> d_r;
};
