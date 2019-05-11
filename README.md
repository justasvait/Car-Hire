# Car Hire Project
The program to simulate car rental company.

The car rental company's garage information is read from a file. Then, the user can choose to rent a car from any garage of his/her choice that has available cars or simply skip the day without renting any cars. The user must select drop-off location of the rented car. The duration of the rent is automatically assigned from 1 to 25 days using rand() function. The simulation runs for 30 days (i.e. 30 loops). Before program closes, it saves last day's garage information to a file called "End of the simulation.txt".

# Configurations
In main.cpp, you can change definitions of minimum hire period, maximum hire period, number of garages, number of cars, simulation duration. When number of cars and garages are changed, the "Cars in garages.txt" file should be updated accordingly (where rows - number of garages number, columns - number of cars).

# What I learned
- Object-Oriented Programming
- Input validation against wrong input type and out of range inputs
- Using stacks
- Using files
