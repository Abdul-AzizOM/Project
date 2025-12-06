#include <iostream>
#include <cstdlib>
#include "Attendees.h"
#include "Events.h"
#include "Registration.h"

void Menu()
{
    std::cout << "Select an option: (Number)\n";
    std::cout << "1.Add attendees.\n";
    std::cout << "2.Add events.\n";
    std::cout << "3.Register attendee for event.\n";
    std::cout << "4.Mark check-in for a registration.\n";
    std::cout << "5.Show event statistics.\n"; //show :1.capacity 2.regiters 3.percentage
    std::cout << "6.Show per-attendee list of registered events.\n";
    std::cout << "7.Search attendees/events.\n";
    std::cout << "9.Enable/Disable event.\n";
    std::cout << "8.Exit\n";
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
////////////////////////////////////////////////////////////////////////////////////////number of registers in event


size_t RegPerEvent(size_t ID)
{
    size_t count = 0;
    for (int i = 1; i < RegistrationLimit; i++) 
    {
        if (registrations[i].eventID == ID) { count++; }
    }
    return count;
}

////////////////////////////////////////////////////////////////////////////////adding attendees

Attendee_Active getAtendeeActiveStatus(size_t option)
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


bool ID_Exists_attendees(size_t ID)
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


size_t available_index_attendees()
{
    size_t AvailableIndex = AttendeesLimit + 1; // +1 <-- to make the index out of range so it doesn't return a random index(more likely to be the last one)
    for (size_t j = 0; j < AttendeesLimit; j++)
    {
        if (AttendeesList[j].ID == 0)
        {
            AvailableIndex = j;
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
    Attendee_Active active;




    std::cout << "Enter the ID: "; // Massage to Take the input


    ID = ValidInput(1, 999999999);

    if (ID_Exists_attendees(ID))
    {
        size_t ReturnOption = 0;

        std::cout << "This ID already exists!\nEnter (1) to return to the main menu or (2) to add another attendees\n";
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

    active = getAtendeeActiveStatus(active_option);


    AttendeesList[available_index_attendees()] = {ID, name, active};
    

}

//////////////////////////////////////////////////////////////////////////////////////////add event

bool ID_Exists_events(size_t ID)
{
    for (size_t i = 0; i < EventsLimits; i++)
    {
        if (ID == events[i].ID)
        {
            return true;
        }
    }
    return false;

}


size_t available_index_events()
{
    size_t AvailableIndex = EventsLimits + 1; // +1 <-- to make the index out of range so it doesn't return a random index(more likely to be the last one)
    for (size_t j = 0; j < EventsLimits; j++)
    {
        if (events[j].ID == 0)
        {
            AvailableIndex = j;
            return AvailableIndex;
        }
    }
    return AvailableIndex;
}


Event_Active getEventActiveStatus(size_t option)
{
    if (option == 0)
    {
        return ACTIVE;
    }
    else if (option == 1)
    {
        return NOT_ACTIVE;
    }
    else
    {
        return CANCELED;
    }
}

void addevents()
{
    size_t ID = 0;
    std::string title;
    size_t capacity;
    Event_Active active;
    size_t active_option;

    std::cout << "Enter the event ID: ";
    ID = ValidInput(1, 999999999);

    if (ID_Exists_events(ID))
    {
        size_t ReturnOption = 0;

        std::cout << "This ID already exists!\nEnter (1) to return to the main menu or (2) to add another attendees\n";
        ReturnOption = ValidInput(1, 2); // future plan :make a third option to go to the id that exists
        if (ReturnOption == 1)
        {return Menu();}// restart the programme
        else{return addevents();}//start over 

    }
    std::cout << "Enter the title: ";
    std::cin >> title;
    std::cout << "Enter the status (0: ACTIVE, 1: NOT_ACTIVE): ";
    active_option = ValidInput(0, 1);

    active = getEventActiveStatus(active_option);

    std::cout << "Enter the capacity: ";
    capacity = ValidInput(0, AttendeesLimit);

    events[available_index_events()] = { ID, title, capacity,active };


}











//////////////////////////////////////////////////////////////Register attendee for event


bool Registercheck(size_t attendeeID, size_t eventID, Regist_status status, Registration arr[])//check if the user is enrolled or not
{
    for(int i=0;i< RegistrationLimit;i++)
    {
        if (arr[i].attendeeID == attendeeID &&
            arr[i].eventID == eventID &&
            arr[i].status == Enrolled) {return true;}
    }
    return false;
}

size_t available_index_rig()
{
    size_t AvailableIndex = RegistrationLimit + 1; // +1 <-- to make the index out of range so it doesn't return a random index(more likely to be the last one)
    for (size_t j = 0; j < RegistrationLimit; j++)
    {
        if (registrations[j].eventID == 0)
        {
            AvailableIndex = j;
            return AvailableIndex;
        }
    }
    return AvailableIndex;
}

void RegisterAttendee()
{
    size_t attendeeID;
    size_t eventID;
    Regist_status status = NotEnrolled;


    std::cout << "Enter the attendee ID: ";
    attendeeID = ValidInput(0, 9999999999);
    if (!(ID_Exists_attendees(attendeeID)))
    {
        size_t ReturnOption = 0;
        std::cout << "This ID doesn't exist!\nEnter (1) to return to the main menu or (2) to register another attendees\n";
        ReturnOption = ValidInput(1, 2); // future plan :make a third option to go to the id that exists
        if (ReturnOption == 1) { return Menu(); }// restart the programme
        else { return RegisterAttendee(); }//start over 
    }



    std::cout << "Enter event ID: ";
    eventID = ValidInput(0, 9999999999);
    if (!(ID_Exists_events(eventID)))
    {
        size_t ReturnOption = 0;
        std::cout << "This event ID doesn't exist!\nEnter (1) to return to the main menu or (2) to register another attendees\n";
        ReturnOption = ValidInput(1, 2);
        if (ReturnOption == 1)
        {
            return Menu();
        }// restart the programme
        else { return RegisterAttendee(); }//start over 
    }


    
    if (Registercheck(attendeeID, eventID, status, registrations))
    {
        size_t ReturnOption = 0;
        std::cout << "Already Enrolled!\nEnter (1) to return to the main menu or (2) to register another attendees\n";
        ReturnOption = ValidInput(1, 2);
        if (ReturnOption == 1)
        {
            return Menu();
        }// restart the programme
        else { return RegisterAttendee(); }//start over 

    }

    registrations[available_index_rig()] = {attendeeID,eventID, status };

}






//////////////////////////////////////////////////////////check if enrolled





void Erolled()
{
    size_t attendeeID;
    size_t eventID;
    Regist_status status = NotEnrolled;
    std::cout << "Enter the attendee ID: ";
    attendeeID = ValidInput(0, 9999999999);
    if (!(ID_Exists_attendees(attendeeID)))
    {
        size_t ReturnOption = 0;
        std::cout << "This ID doesn't exist!\nEnter (1) to return to the main menu or (2) to check another attendees\n";
        ReturnOption = ValidInput(1, 2); // future plan :make a third option to go to the id that exists
        if (ReturnOption == 1) { return Menu(); }// restart the programme
        else { return Erolled(); }//start over 
    }



    std::cout << "Enter event ID: ";
    eventID = ValidInput(0, 9999999999);
    if (!(ID_Exists_events(eventID)))
    {
        size_t ReturnOption = 0;
        std::cout << "This event ID doesn't exist!\nEnter (1) to return to the main menu or (2) to check another attendees\n";
        ReturnOption = ValidInput(1, 2);
        if (ReturnOption == 1)
        {
            return Menu();
        }// restart the programme
        else { return Erolled(); }//start over 
    }

    if (Registercheck(attendeeID, eventID, status, registrations))
    {
        size_t ReturnOption = 0;
        std::cout << "Enrolled!\nEnter (1) to return to the main menu or (2) to check another attendees\n";
        ReturnOption = ValidInput(1, 2);
        if (ReturnOption == 1)
        {
            return Menu();
        }// restart the programme
        else { return Erolled(); }//start over 

    }
    if (!(Registercheck(attendeeID, eventID, status, registrations)))
    {
        size_t ReturnOption = 0;
        std::cout << "Not Enrolled!\nEnter (1) to return to the main menu or (2) to check another attendees\n";
        ReturnOption = ValidInput(1, 2);
        if (ReturnOption == 1)
        {
            return Menu();
        }// restart the programme
        else { return Erolled(); }//start over 

    }

}




















////////////////////////////////////////////////////////////////events statistics


size_t eventID_index(size_t eventID)
{
    for(int i = 0;i < EventsLimits;i++)
    {
        if (eventID == events[i].ID) {return i;}
    }
}



void evenstat()
{
    size_t eventID = 0;

    std::cout << "Enter event ID to check: ";
    eventID = ValidInput(1, 999999999999);

    if (!(ID_Exists_events(eventID)))
    {
        size_t ReturnOption = 0;
        std::cout << "This event ID doesn't exist!\nEnter (1) to return to the main menu or (2) to check another event\n";
        ReturnOption = ValidInput(1, 2);
        if (ReturnOption == 1)
        {
            return Menu();
        }// restart the programme
        else { return evenstat(); }//start over 
    }


    std::cout << "The capacity: " << events[eventID_index(eventID)].capacity << std::endl;
    std::cout << "The Attendance: " << RegPerEvent(eventID)<<std::endl;
    std::cout << "Attendance Rate: " << (float(RegPerEvent(eventID))/ float(events[eventID_index(eventID)].capacity))*100 << "%" << std::endl; // add the number of register for event


    size_t ReturnOption = 0;
    std::cout << "Done!\nEnter (1) to return to the main menu or (2) to Check another event\n";
    ReturnOption = ValidInput(1, 9999999999);
    if (ReturnOption == 1)
    {
        return Menu();
    }// restart the programme
    else { return evenstat(); }//start over 

}
    








//////////////////////////////////////////////////////////// the attendee registerations





void ListofEnrolledEvents()
{
    size_t attendeeID = 0;
    size_t numOfenrolled = 1;
    attendeeID = ValidInput(1, 9999999999);
    
    for (int i = 0; i < RegistrationLimit;i++)
    {
        if(attendeeID == registrations[i].attendeeID)
        {
            std::cout << numOfenrolled <<"."  << events[eventID_index(registrations[i].eventID)].title<<std::endl;
            numOfenrolled++;

        }
    }

    size_t ReturnOption = 0;
    std::cout << "Done!\nEnter (1) to return to the main menu or (2) to Check another event\n";
    ReturnOption = ValidInput(1, 9999999999);
    if (ReturnOption == 1)
    {
        return Menu();
    }// restart the programme
    else { return evenstat(); }//start over 
         
}







/////////////////////////////////////////////////////////////search



void attendeeSearch()
{
    size_t ID = 0;
    std::cout << "Enter the ID";
    ID = ValidInput(1, 99999999);

    if (!(ID_Exists_attendees(ID)))
    {
        size_t ReturnOption = 0;
        std::cout << "This ID doesn't exist!\nEnter (1) to return to the main menu or (2) to check another attendees\n";
        ReturnOption = ValidInput(1, 2); // future plan :make a third option to go to the id that exists
        if (ReturnOption == 1) { return Menu(); }// restart the programme
        else { return Erolled(); }//start over 
    }

    for ()

    
}

void search()
{
    size_t option;
    std::cout << "1.For Attendee.\n2.For Event";
    option = ValidInput(1, 2);
    if(option == 1)
    {
        
    }
}


















///////////////////////////////////


int main()
{
    while (true)
    {
        system("cls"); // Clears the console on Windows
        Menu();
        size_t option = 9;
        option = ValidInput(1, 9);

        if (option == 1)
        {
            addattendees();
        }
        else if (option == 2)
        {
            addevents();
        }
        else if (option == 3)
        {
            RegisterAttendee();
        }
        else if (option == 4)
        {
            Erolled();
        }
        else if (option == 5)
        {
            evenstat();
        }
        else if (option == 6)
        {
            ListofEnrolledEvents();
        }
        else if (option == 7)
        {
            search();
        }
        else
        {
            return false;
        }

    }


}


// note:add availability function to returnn bool if the array is full or not