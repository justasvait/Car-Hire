/**
 * Car.cpp
 *
 * Details: Car class holds information about the car.
 *          "getRand" function generates random number in specified range.
 *          "getRand" function has a random seed each time it executes.
 *
 * Author: Justas Vaitkevicius
 * Date: 07/03/2017
**/

#include "Car.h"       // include class header file
#include <stdlib.h>    // rand(), srand()
#include <time.h>      // time to randomise seed

/// Constructors
Car::Car(int inputID, bool inputHired, int inputPeriod, int inputLocation)
{
    identifier = inputID;
    hired = inputHired;
    period = inputPeriod;
    location = inputLocation;
}
Car::Car()
{
    identifier = 0;
    hired = false;
    period = 0;
    location = 0;
}
/// Other functions

/* Function to get a random number within given range. */
int Car::getRand(int maxRand, int minRand)
{
    srand(time(NULL));      // selects a new seed from a time stamp value to create more randomness.
    return rand() % maxRand + minRand;  // generates random number within given range.
}
