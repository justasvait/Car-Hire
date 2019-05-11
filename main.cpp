/**
 * main.cpp
 * (Car Hire Company program)
 *
 * Details: The program to simulate car rental company.

 *          A user is able to select a garage from which (s)he wants to rent a car from. (S)he needs to provide drop-off period.
 *          It is possible to hire up to 1 vehicle in a single day.

 *          The program provides with a list of all hired cars along with information of hired period,
 *          drop-off location, when it was hired.
 *
 * Author: Justas Vaitkevicius
 * Date: 07/03/2017
**/

/* Classes */
#include "Garage.h"
#include "Car.h"

/* Libraries */
#include <iostream>    // cin, cout...
#include <fstream>     // using files
#include <string>      // using strings
#include <vector>      // using vector
#include <algorithm>   // using for deleting specific value from vector
#include <stack>       // using stacks
using namespace std;

/* Constants */
#define MIN_RAND 1     // minimum hire period
#define MAX_RAND 25    // maximum hire period
#define NUMBER_OF_GARAGES 5 // number of garages
#define NUMBER_OF_CARS 25 // number of cars
#define SIMULATION_TIME 30  // simulation duration
#define IN_FILE_NAME "Cars in garages.txt"  // input file name
#define OUT_FILE_NAME "End of the simulation.txt"   // output file name

/// Functions

/* Function to input integer which is in specified range. Invalid entries are rejected.*/
void inputInRange(int &val, int minval, int maxval)
{
    cin >> val; // input initial value
    while (cin.fail() || (val < minval || val > maxval))    // execute when input is invalid or out of range
    {
        if (cin.fail())
        {
            /* The input is invalid (not an integer) */
            cout << "Wrong input." << endl;
            cin.clear();            // clears cin stream
            cin.ignore(256,'\n');   //
            cin >> val;         // gets a new input value
        }
        else if (val>maxval || val<minval)
        {
            /* The input is out of range */
            cout << "Out of range." << endl;    // error message
            cin >> val; // gets a new input value
        }
    }
    cin.clear();            // Clears any excess inputs from cin stream
    cin.ignore(256,'\n');   // to prevent from unwanted behaviour.
}

int main()
{
    /// Initialisation
    cout << "***CAR RENTAL***\n" << endl;
    cout << "Initial car locations:" << endl;
    int error = 0;
    vector <int> hiredCars; // vector that holds hired car IDs

    Garage garage[NUMBER_OF_GARAGES];   // initialises garage class objects
    for (int i=0; i<NUMBER_OF_GARAGES; i++) // loops through all objects to initialise data
    {
        garage[i].Setidentifier(i+1);   // sets unique ID
        error = garage[i].inFromFile(IN_FILE_NAME, i+1);    // inputs car stack from file
        if ( error != 0 )
        {
            /* Error occurred, program is terminated. */
            cout << "\nError occurred while reading a file \"" << IN_FILE_NAME << "\".\nProgram terminated!" << endl;
            return 1;
        }
        garage[i].toString();   // prints initial car information in garage.
    }

    Car car[NUMBER_OF_CARS];    // initialises car class
    for (int i=0; i<NUMBER_OF_CARS; i++)
    {
        car[i].SetIdentifier(i+1);  // sets unique ID
        car[i].SetHired(false);     // sets to available cars by default
        car[i].SetPeriod(0);        // sets period to 0 (car is not hired)
    }

    cout << string(3,'\n');     // additional line breaks

    /// main for loop
    int id;     // hired car's id
    int loc;    // drop off location

    for ( int n=0; n<SIMULATION_TIME; n++)
    {
        cout << "Day " << n+1 << "\n______" << endl;
        cout << endl << "Please select garage id [1-" << NUMBER_OF_GARAGES << "] to hire a car or [0] to skip a day." << endl;

        inputInRange(id,0,NUMBER_OF_GARAGES); // inputs garage ID to rent a car from (only 0 to NUMBER_OF_GARAGES numbers are allowed)
        if (id == 0)
        {
            /* No rentals today. Skipping a day */
            cout << "\nSkipped a day..." << endl;
        }
        else if ( garage[id-1].GetcarCount() == 0 )
        {
            /* The garage is empty, cannot hire from this garage */
            cout << endl << "Please select another garage. This one is empty." << endl;
            n--;        //
            continue;   // restarts the loop
        }
        else if (id >= 1 && id <= NUMBER_OF_GARAGES)
        {
            /* The car has been hired */
            cout << "Please enter drop off location [1-" << NUMBER_OF_GARAGES << "]." << endl;
            inputInRange(loc,1,NUMBER_OF_GARAGES);      // inputs location <int> in range 1 to NUMBER_OF_GARAGES only.
            for(int i=1;i<=NUMBER_OF_CARS;i++)      // starts with 1 to make it same as id index.
            {
                /* search for selected car */
                if(garage[id-1].GetCarID()==car[i-1].GetIdentifier())
                {
                    /* the correct car has been found */
                    car[i-1].SetHired(true);    // set car to hired
                    car[i-1].SetPeriod(car[i-1].getRand(MAX_RAND,MIN_RAND)+1);  // generates random hire period
                    car[i-1].SetLocation(loc);  // sets drop-off location
                    garage[id-1].PopCarID();    // removes a car from garage
                    car[i-1].SetGetHiredDay(n+1);   // sets a day on which a car was rented
                    hiredCars.push_back(i);     // adds the car to hired car list
                }
            }
        }
        /* end of the day calculations */
        cout << string(3,'\n') << "Cars on hire:";
        int index;  // holds current index value of the vector
        vector <int>::iterator vectorPtr;   // creates new vector iterator
        for (vectorPtr=hiredCars.begin(); vectorPtr!=hiredCars.end(); ++vectorPtr)
        {
            if (hiredCars.empty())break; // if hired car vector is empty, skips this part

            index = *vectorPtr-1;   // assigns index value
            if (car[index].GetHired() == true)  // additional protection against incorrect vector values
            {
                /* The car is hired */
                car[index].SetPeriod(car[index].GetPeriod()-1); // decreases hired period by 1 at the end of the day
                if (car[index].GetPeriod() == 0)
                {
                    /* The car is returned today */
                    car[index].SetHired(false);     // sets a car to available
                    garage[car[index].GetLocation()-1].AddCarID(car[index].GetIdentifier());    // returns a car to drop-off garage
                    {
                        int val = car[index].GetIdentifier();   // assigns car ID
                        hiredCars.erase(remove(hiredCars.begin(),hiredCars.end(),val),hiredCars.end()); // removes car from hired vector list
                        vectorPtr--;    // reduces iterator by 1 as a member is removed
                    }
                }
                cout << "\n\t\t" << car[index].GetIdentifier();
                if ( car[index].GetPeriod()>0 )
                {
                    /* A car is still hired */
                    cout << " (hired for: " << car[index].GetPeriod() << ", drop-off location: ";
                    cout << car[index].GetLocation() << ", hired on: " << car[index].GetHiredDay() << " day)";
                }
                else    // A car is returned today
                    cout << " (returned today)";
            }
        }
        /* Prints current available cars in each garage */
        cout << endl << endl;
        for (int i=0; i<NUMBER_OF_GARAGES;i++)
        {
            garage[i].toString();   // prints garage information
        }
        cout << string(5,'\n');     // leaves a gap to split days
    } // END OF MAIN LOOP

    /// Write info to a file.
    ofstream outfile;                                   //
    outfile.open(OUT_FILE_NAME,ios_base::out);          // clean the file.
    outfile.close();                                    //

    /* Prints information to a file */
    for ( int i=0; i<NUMBER_OF_GARAGES; i++)
    {
        garage[i].toFile(OUT_FILE_NAME);    // prints each garage at a time
    }

    return 0;
}
