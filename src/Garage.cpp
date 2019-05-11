/**
 * Garage.cpp
 *
 * Details: To initialise stack (of cars), you need external file with car IDs in single row.
 *          In external file n-th row corresponds to n-th garage.
 *          When exporting garage information to a file, the file is appended.
 *
 *          Use functions: int GetCarID(), void PopCarID(), void AddCarID(int val), to manipulate with stacks.
 *
 * Author: Justas Vaitkevicius
 * Date: 07/03/2017
**/

#include "Garage.h"     // class header

#include <iostream>     // for printing error message (i.e. missing data)
#include <fstream>      // file operations
#include <string>       // string for file name
#include <stack>        // for stacking cars
#include <sstream>      // for reading line as integers
using namespace std;

/// Constructors
Garage::Garage(int inputID, int inputCarCount, int inputMaxCars)
{
    identifier = inputID;
    carCount = inputCarCount;
    maxCars = inputMaxCars;
}
Garage::Garage()
{
    identifier = 0;
    carCount = 0;
    maxCars = 25;
}
/// Functions

/* Function to print out the list of cars in the garage. */
void Garage::toString()
{
    cout << "Garage " << identifier << " has these cars inside: ";
    stack <int> output = carIDs;    // duplicate of carIDs stack to be printed out
    for (int i=0; i<carCount;i++)
    {
        cout << output.top() << " ";    // prints top member of stack
        output.pop();   // removes top member of stack
    }
    cout << endl;
}

/* Function to print to a file (end of the simulation) cars in the garage.
 * -Need to provide file name to function.
 */
void Garage::toFile(string fileName)
{
    ofstream outfile;
    outfile.open(fileName, ios_base::app);  // open file to append
    stack <int> output = carIDs;    // duplicate stack which can be printed out
    if ( outfile.good() )       // file check. Only output if a file is open.
    {
        for (int i=0; i<carCount;i++)           /* prints out cars to a file*/
        {                                       //
            outfile << output.top() << " ";     // prints top car
            output.pop();                       // removes top car from stack
        }                                       /* */
    outfile << endl;
    outfile.close();    // closes the file
    }
}

/* Function to get initial information from a file.
 * -Need to provide:
 *      -file name
 *      -number of garage (previous garages are ignored)
 */
int Garage::inFromFile(string fileName, int noOfGarage)
{
    ifstream infile;    // input from file
    infile.open(fileName); // open file

    if ( infile.fail() )    // checking file existence
    {
        cout << "Cannot open \"" << fileName << "\" file! " << endl;
        return 1;   // return 1 to indicate error
    }
    else    // file exists
    {
        string buffer;  // string to read from file
        stringstream inputStream;   // string stream to split line into integers
        int stackValue;     // temporary integer to pass data to a stack

        // reads the noOfGarage (x-th) line.
        for (int i=0; i<noOfGarage; i++)
            getline(infile,buffer);

        inputStream << buffer;  // converts string into string stream

        while ( inputStream >> stackValue)  // gets integers from sting stream until it is empty.
        {
            if ( carCount < maxCars)    // protects against too many cars in a single garage
            {
                carIDs.push(stackValue);    // add the value to a stack
                carCount++;     // adds 1 to a car counter
            }
        }

        infile.close(); // close file
        return 0;   // return 0 to indicate success
    }
}

/* Function to get top car's ID. */
int Garage::GetCarID()
{
    if(carIDs.size()!=0)    // checks if stack is not empty
        return carIDs.top();    // returns top value of stack
    else
        return 0;   // if stack is empty returns 0
}

/* Function to remove top value (car) of a stack and decrease car counter by 1.*/
void Garage::PopCarID()
{
    if(carIDs.size()!=0)
    {
        carIDs.pop();   // remove top car if there are cars left
        carCount--;     // decreases car counter by 1
    }
}

/* Function to add a value (car ID) to a stack. */
void Garage::AddCarID(int val)
{
    if ( carCount < maxCars)    // protects against too many cars in a single garage
    {
        carIDs.push(val);   // adds car to the top of the stack
        carCount++;     // increases car counter by 1
    }
}
