// prob1603: Design Parking System

/*
 * https://leetcode-cn.com/problems/design-parking-system/
 */


class ParkingSystem {
public:
    ParkingSystem(int big, int medium, int small) {
        b = big;
        m = medium;
        s = small;
    }

    bool addCar(int carType) {
        if(carType == 1)
        {
            if(b > 0)
            {
                --b;
                return true;
            }
            else
                return false;
        }
        else if(carType == 2)
        {
            if(m > 0)
            {
                --m;
                return true;
            }
            else
                return false;
        }
        else if(carType == 3)
        {
            if(s > 0)
            {
                --s;
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }

private:
    int b, m, s;
};
