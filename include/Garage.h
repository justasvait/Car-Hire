/**
 * Garage.h
 *
 * Details: Garage class holds information about garage (has specific ID, car counter, maximum car capacity
                                                         and stack of car ID).
 *          Has functionality to input information from file and extract to file, print garage content to a scope
 *          and manipulate with stack.
 *
 * Author: Justas Vaitkevicius
 * Date: 07/03/2017
**/

#ifndef GARAGE_H
#define GARAGE_H

#include <string>
#include <stack>
using namespace std;

class Garage
{
private:
    int identifier;     // unique ID
    int carCount;       // counter for cars
    int maxCars;        // maximum garage capacity
    stack <int> carIDs;     // stack to hold car IDs
public:
    Garage(int inputID, int inputCarCount, int inputMaxCars);
    Garage();

    /* get and set functions */
    int Getidentifier() { return identifier; }
    void Setidentifier(int val) { identifier = val; }

    int GetcarCount() { return carCount; }
    void SetcarCount(int val) { carCount = val; }

    /* other functions */
    void toString();    // prints content of garage to scope
    void toFile(string fileName);   // prints content of garage to file
    int inFromFile(string fileName, int noOfGarage);    // initialises cars in garage from file
    int GetCarID();     // returns top member of stack
    void PopCarID();    // removes top member of stack
    void AddCarID(int val); // adds a member to a stack
};

#endif // GARAGE_H
