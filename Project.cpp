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
////////////////////////////////////////////////////////////////////////////////input checking if it is valid
size_t ValidInput(size_t NotSmallerThan, size_t NotBiggerThan)
{
    size_t option;
    while (!(std::cin >> option) || (option < NotSmallerThan || option > NotBiggerThan))  //Check the vadility of the input
    {
        std::cout << "Invalid input. Try again\n"; //send a massage to the user to try a valid input
        std::cin.clear(); //clear the input
        std::cin.ignore(100, '\n'); //ignore the whole input
    };
    return option;
}

////////////////////////////////////////////////////////////////////////////////adding attendees

Attendee_Acite getActiveStatus(size_t option)
{
    if (option == 0)
    {
        return IDLE;
    }
    else if (option == 1)
    {
        return IN_EVENT;
    }
    else if (option == 2)
    {
        return WITHDRAWN;
    }
    else
    {
        return UNDEFINED;
    }
}



bool ID_Exists(size_t ID)
{
    for (size_t i = 0; i < AttendeesLimit; i++)
    {
        if (ID == AttendeesList[i].ID)
        {
            return true;
        }
    }
    return false;

}

size_t available_index()
{
    size_t AvailableIndex = AttendeesLimit + 1; // +1 <-- to make the index out of range so it doesn't return a random index(more likely to be the last one)
    for (size_t j = 0; j < AttendeesLimit; j++)
    {
        if (AttendeesList[j].ID == 0)
        {
            return AvailableIndex;
        }
    }
    return AvailableIndex;
}





void addattendees()
{
    size_t ID;
    std::string name;
    size_t active_option;
    Attendee_Acite active;




    std::cout << "Enter the ID: "; // Massage to Take the input


    ID = ValidInput(1, 999999999);

    if (ID_Exists(ID))
    {
        size_t ReturnOption = 0;

        std::cout << "This ID already exists!\n Enter (1) to return to the main menu or (2) to add another attendees";
        ReturnOption = ValidInput(1, 2); // future plan :make a third option to go to the id that exists
        if (ReturnOption == 1)
        {
            return Menu();// restart the programme
        }
        else
        {
            return addattendees();//start over 
        }

    }
    std::cout << "Enter the name: ";
    std::cin >> name;
    std::cout << "Enter the status (0: IDLE, 1: IN_EVENT, 2: WITHDRAWN, 3: UNDEFINED): ";
    active_option = ValidInput(0, 3);
    active = getActiveStatus(active_option);


    AttendeesList[available_index()] = {ID, name, active};
    

}




//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Menu();
    size_t option = 9;

    option = ValidInput(1,9);

    if (option == 1)
    {
        addattendees();
	};
    return 0;
}


// note:add availability function to returnn bool if the array is full or not