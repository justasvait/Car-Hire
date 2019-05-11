/**
 * Car.h
 *
 * Details: Car class holds main information about the car (i.e. ID, hired or not, hired period, drop-off location, when hired)
 *          Use set and get commands to manipulate with car information.
 *          This class also has function to generate random integer number in specified range.
 *
 * Author: Justas Vaitkevicius
 * Date: 07/03/2017
**/

#ifndef CAR_H
#define CAR_H

class Car
{
private:
    int identifier;     // unique car ID
    bool hired;         // hired = true, means a car is hired; false - car is available to hire.
    int period;         // holds integer of days remaining on hire
    int location;       // drop-off location
    int hiredDay;       // indicates the day in which the car was hired

public:
    /* Constructors */
    Car(int inputID, bool inputHired, int inputPeriod, int inputLocation);
    Car();

    /* Set and get functions */
    int GetIdentifier() { return identifier; }
    void SetIdentifier(int val) { identifier = val; }

    bool GetHired() { return hired; }
    void SetHired(bool val) { hired = val; }

    int GetPeriod() { return period; }
    void SetPeriod(int val) { period = val; }

    int GetLocation() { return location; }
    void SetLocation(int val) { location = val; }

    int GetHiredDay() { return hiredDay; }
    void SetGetHiredDay(int val) { hiredDay = val; }

    /* Other functions */
    int getRand(int maxRand, int minRand);  // produces random number within given range
};

#endif // CAR_H
