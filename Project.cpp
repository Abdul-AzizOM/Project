#include <iostream>
#include "Attendees.h"
#include "Events.h"
#include "Registration.h"



void Menu()
{
    std::cout << "Select an option: (Number)\n";
    std::cout << "1.Add attendees.\n";
    std::cout << "2.Add events.\n";
    std::cout << "3.Register attendee for event.\n";
    std::cout << "4.Show event statistics.\n";
    std::cout << "5.Mark check-in for a registration.\n";
    std::cout << "6.Show event statistics.\n";
    std::cout << "7.Show per-attendee list of registered events.\n";
    std::cout << "8.Search attendees/events.\n";
    std::cout << "9.Exit\n";
}

size_t OptionInput()
{
    
    size_t option;
    while (!(std::cin >> option) || ( option <  1 || option > 10))  //Check the vadility of the input
    {
        std::cout << "Invalid input. Try again\n"; //send a massage to the user to try a valid input
        std::cin.clear(); //clear the input
        std::cin.ignore(100,'\n'); //ignore the whole input
    };
    return option;
}


int main()
{
    Menu();
    size_t option = 9;

    option = OptionInput();

    std::cout << AttendeesList[2].name;
    return 0;
}