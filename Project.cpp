#include <iostream>
#include <cstdlib>
#include <functional>

#include <string>
#include "Attendees.h"
#include "Events.h"
#include "Registration.h"


// -----------------------------------------------------  
// add a limit for the attendee ,events and registration

void Menu()
{
    std::cout << "Select an option: (Number)\n";
    std::cout << "1.Add attendees.\n";
    std::cout << "2.Add events.\n";
    std::cout << "3.Register attendee for event.\n";
    std::cout << "4.Mark check-in for a registration.\n";
    std::cout << "5.Show event statistics.\n"; //show :1.capacity 2.regiters 3.percentage
    std::cout << "6.Show per-attendee list of registered events.\n";
    std::cout << "7.Search attendees.\n";//add search by name2
    std::cout << "8.manage attendee/event.\n";
    std::cout << "9.show attendees/events.\n";
    std::cout << "10.Exit\n";
}

// ----------------------------------------------------- 
//input checking if it is valid

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

// ----------------------------------------------------- 
//return menu

// strings are passed by value here, consider passing by const reference to avoid unnecessary copies
// also this project size doesn't need a function pointer, you can just call the function directly in the main loop
void returnOptions(std::string condition="", std::string option2 = "", std::function<void()> function)
{
    size_t ReturnOption = 0;
    std::cout << condition << "\nEnter(1) to return to the main menu  " << option2 << std::endl;
    ReturnOption = ValidInput(1, 2); 
    if (ReturnOption == 1)
    {
        return;// restart the programme
    }
    else
    {
        function();//start over 
    }

}

// ----------------------------------------------------- 
//number of registers in event

size_t RegPerEvent(size_t ID)
{
    size_t count = 0;
    for (int i = 1; i < RegistrationLimit; i++) 
    {
        if (registrations[i].eventID == ID) { count++; }
    }
    return count;
}

// ----------------------------------------------------- 
//adding attendees

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

     if (!(AttendeesList[AttendeesLimit-1].ID ==0))//last element / 0 is the defaul if it does change that means the list is full
    {
        returnOptions("There is no Space", "", addattendees);
    }
    else if (ID_Exists_attendees(ID))
    {
        returnOptions("ID already exists","or (2) to add another attendee", addattendees);
    }
    else
    {
        std::cout << "Enter the name: ";
        std::cin >> name;
        std::cout << "Enter the status (0: IDLE, 1: IN_EVENT, 2: WITHDRAWN, 3: UNDEFINED): ";
        active_option = ValidInput(0, 3);
        active = getAtendeeActiveStatus(active_option);
        AttendeesList[available_index_attendees()] = { ID, name, active };
        returnOptions("Done!", "or (2) to add another attendee", addattendees);
    }

}

// ----------------------------------------------------- 
//add event

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

    if (events[EventsLimits-1].ID != 0) // if the last element is taken means its full
    {
        returnOptions("There is no space!"," ", addevents);
    }


    if (ID_Exists_events(ID))
    {
        returnOptions("This ID already exists!", "or (2) to add another event", addevents);

    }
    else 
    {
        std::cout << "Enter the title: ";
        std::cin >> title;
        std::cout << "Enter the status (0: ACTIVE, 1: NOT_ACTIVE): ";
        active_option = ValidInput(0, 1);

        active = getEventActiveStatus(active_option);

        std::cout << "Enter the capacity: ";
        capacity = ValidInput(0, AttendeesLimit);

        events[available_index_events()] = { ID, title, capacity,active };

        returnOptions("Done!", "or (2) to add another event", addevents);
    }
}

// ----------------------------------------------------- 
//Register attendee for event

size_t eventID_index(size_t eventID)
{
    for(int i = 0;i < EventsLimits;++i)
    {
        if (eventID == events[i].ID) {return i;}
    }
    return 0;
}

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

    std::cout << "Enter event ID: ";
    eventID = ValidInput(0, 9999999999);

    
    if (!(ID_Exists_attendees(attendeeID)))
    {
        returnOptions("This ID doesn't exist!", "or (2) to register another attendees", RegisterAttendee);
    }
    
    else if (!(ID_Exists_events(eventID)))
    {
        returnOptions("This event ID doesn't exist!", "or (2) to register another attendees", RegisterAttendee);
    }

    else if (Registercheck(attendeeID, eventID, status, registrations))
    {
        returnOptions("Already Enrolled!", "or (2) to register another attendees", RegisterAttendee);

    }
    else if(RegPerEvent(eventID) == events[eventID_index(eventID)].capacity)
    {
        returnOptions("This event is full!", "or (2) to register another attendees", RegisterAttendee);
    }
    else {
        status = Enrolled;
        registrations[available_index_rig()] = { attendeeID,eventID, status };
        returnOptions("Done!", "or (2) to register another attendees", RegisterAttendee);
    }
}

// ----------------------------------------------------- 
//check if enrolled

void CheckIfEnrolled()
{
    size_t attendeeID;
    size_t eventID;
    Regist_status status = NotEnrolled;


    std::cout << "Enter the attendee ID: ";
    attendeeID = ValidInput(0, 9999999999);
    if (!(ID_Exists_attendees(attendeeID)))
    {
        returnOptions("This ID doesn't exist!","or (2) to check another attendees", CheckIfEnrolled);
    }


    else {
        std::cout << "Enter event ID: ";
        eventID = ValidInput(0, 9999999999);
        if (!(ID_Exists_events(eventID)))
        {
            returnOptions("This event ID doesn't exist!", "or (2) to check another attendees", CheckIfEnrolled);
        }

        else if (Registercheck(attendeeID, eventID, status, registrations))
        {
            returnOptions("Enrolled!", "or (2) to check another attendees", CheckIfEnrolled);
        }
        else if (!(Registercheck(attendeeID, eventID, status, registrations)))
        {
            returnOptions("Not Enrolled!", "or (2) to check another attendees", CheckIfEnrolled);
        }
    }
}

// ----------------------------------------------------- 
//events statistics

void evenstat()
{
    size_t eventID = 0;
    void (*function)() = &evenstat;

    std::cout << "Enter event ID to check: ";
    eventID = ValidInput(1, 999999999999);

    if (!(ID_Exists_events(eventID)))
    {
        returnOptions("This event ID doesn't exist!", "or (2) to check another event", function);
    }

    else {
        std::cout << "Title: " << events[eventID_index(eventID)].title << std::endl;
        std::cout << "The capacity: " << events[eventID_index(eventID)].capacity << std::endl;
        std::cout << "The Attendance: " << RegPerEvent(eventID) << std::endl;
        std::cout << "Attendance Rate: " << (float(RegPerEvent(eventID)) / float(events[eventID_index(eventID)].capacity)) * 100 << "%" << std::endl; // add the number of register for event
        returnOptions("Done!", "or (2) to check another event", function);
    }
}

// ----------------------------------------------------- 
//the attendee registerations

void ListofEnrolledEvents()
{
    size_t attendeeID = 0;
    size_t numOfenrolled = 1;
    void (*function)() = &ListofEnrolledEvents;
    
    std::cout << "Enter the ID: ";
    attendeeID = ValidInput(1, 9999999999);
    
    for (int i = 0; i < RegistrationLimit;++i)
    {
        if(attendeeID == registrations[i].attendeeID)
        {
            std::cout << numOfenrolled <<"."  << events[eventID_index(registrations[i].eventID)].title<<std::endl;
            numOfenrolled++;

        }
    }
    returnOptions("Done!", "or (2) to check another event", function);        
}

// ----------------------------------------------------- 
//search



std::string returnAttendeeActive(Attendee_Active ID)
{
    if (AttendeesList[ID].active == IDLE) { return "IDLE"; }
    else if (AttendeesList[ID].active == IN_EVENT) { return "IN_EVENT"; }
    else if (AttendeesList[ID].active == WITHDRAWN) { return "WITHDRAWN"; }
    else { return "UNDEFINED"; }

}

size_t attendeeIndexByID(size_t ID)
{
    for (int i = 0; i < AttendeesLimit; i++)
    {
        if (ID == AttendeesList[i].ID)
        {
            return i;
        }
    }
    return 0;
}

void EnrolledEvents(size_t ID)
{
    int count = 1;
    for (int i = 0; i<RegistrationLimit;i++)
    {
        if(registrations[i].attendeeID == ID &&
            registrations[i].status==Enrolled)
        {
            std::cout << count<<". "<< events[eventID_index(registrations[i].eventID)].title << std::endl;
            count++;
        }

    }
    if (count==1)
    {
        std::cout << "Not Enrolled in any event!"<<std::endl;
    }
}

// Logic is over engineered here, you can just call the function directly in the main loop
void attendeeSearch()
{
    size_t ID = 0;
    std::cout << "Enter the ID: ";
    ID = ValidInput(1, 99999999);

    if (!(ID_Exists_attendees(ID)))
    {
        returnOptions("This ID doesn't exist!", "or (2) to check another attendees", attendeeSearch);

    }

	// Do you need to call attendeeIndexByID twice? you can store the result in a variable

    size_t Index = attendeeIndexByID(ID);

    std::cout << "Name: "<< AttendeesList[Index].name <<std::endl;
    std::cout << "Status: " << returnAttendeeActive(AttendeesList[attendeeIndexByID(ID)].active) << std::endl;
    std::cout << "Enrolled Events:"<<std::endl;
    EnrolledEvents(ID);



    returnOptions("Done!", "or (2) to check another attendees", attendeeSearch);
    
}

//////////////////////////////////////////////Enable/Disable


void manageEvent()
{

    size_t ID = 0;
    void (*function)() = &manageEvent;
    size_t managEventOption;
    size_t choice = 0;

    std::cout << "Enter (1) for attendee or (2) for events: ";
    choice = ValidInput(1, 2);

	// Too long function, consider breaking it into smaller functions
	// I am sure the logic could be simplified as well
    if (choice ==1)//attendee manage
    {
        std::cout << "Enter attendee ID: ";
		// why 9999999999?
        ID = ValidInput(1, 9999999999);

        if (!(ID_Exists_attendees(ID)))
        {
            returnOptions("This ID doesn't exist!", "or (2) to check another event", function);
        }
        else if (AttendeesList[attendeeIndexByID(ID)].active == IDLE)
        {
            std::cout << "This attendee is IDLE.\npress (1) to Go in event it or (2) to withdraw: " << std::endl;
            managEventOption = ValidInput(1, 2);
            if (managEventOption == 1)
            {
                AttendeesList[attendeeIndexByID(ID)].active = IN_EVENT;
            }
            else
            {
                AttendeesList[attendeeIndexByID(ID)].active = WITHDRAWN;
            }
        }
        else if (AttendeesList[attendeeIndexByID(ID)].active == IN_EVENT)
        {
            std::cout << "This event is active.\npress (1) to go Idle or (2) to withdraw: " << std::endl;
            managEventOption = ValidInput(1, 2);
            if (managEventOption == 1)
            {
                AttendeesList[attendeeIndexByID(ID)].active = IDLE;
            }
            else
            {
                AttendeesList[attendeeIndexByID(ID)].active = WITHDRAWN;
            }
        }
        else
        {
            std::cout << "This attendee was withdrawn or undefined" << std::endl;
        }

        returnOptions("Done!", "or (2) to manage menu", function);
    }


    else {
        std::cout << "Enter Event ID: ";
        ID = ValidInput(1, 9999999999);

        if (!(ID_Exists_events(ID)))
        {
            returnOptions("This event ID doesn't exist!", "or (2) to check another event", function);
        }


        else if (events[eventID_index(ID)].active == ACTIVE)
        {
            std::cout << "This event is active.\npress (1) to disactivate it or (2) to cancel it" << std::endl;
            managEventOption = ValidInput(1, 2);
            if (managEventOption == 1)
            {
                events[eventID_index(ID)].active = NOT_ACTIVE;
            }
            else
            {
                events[eventID_index(ID)].active = CANCELED;
            }
        }
        else if (events[eventID_index(ID)].active == NOT_ACTIVE)
        {
            std::cout << "This event is not active.\npress (1) to activate it or (2) to cancel it" << std::endl;
            managEventOption = ValidInput(1, 2);
            if (managEventOption == 1)
            {
                events[eventID_index(ID)].active = ACTIVE;
            }
            else
            {
                events[eventID_index(ID)].active = CANCELED;
            }
        }
        else
        {
            std::cout << "This event was canceled" << std::endl;
        }

        returnOptions("Done!", "or (2) to manage menu", function);
    }

}

// ----------------------------------------------------- 
//show events or attendees


std::string returneventsActive(Event_Active ID)
{
    if (events[ID].active == ACTIVE) { return "ACTIVE"; }
    else if (events[ID].active == NOT_ACTIVE) { return "NOT_ACTIVE"; }
    else{ return "CANCELED"; }

}

void show()
{
    void (*function)() = &show;
    size_t choice = 0;
    std::cout << "Enter (1) for attendees or (2) for events: ";
    choice = ValidInput(1, 2);
    if (choice==1)
    {
        std::cout << "ID     Name     Active"<<std::endl;
        int i = 0;
        while (AttendeesList[i].ID !=0 && i < AttendeesLimit)
        {
            std::cout << AttendeesList[i].ID<<"     "<< AttendeesList[i].name<<"     "<< returnAttendeeActive(AttendeesList[i].active) <<std::endl;
            i++;
        }
        returnOptions("Done", " or (2) to show another attendees/events", function);
    }
    else 
    {
        std::cout << "ID     Title        Capacity     Active" << std::endl;
        int i = 0;
        while (events[i].ID != 0 && i < EventsLimits)
        {
            std::cout << events[i].ID << "     " << events[i].title << "          " << events[i].capacity<< "     " << returneventsActive(events[i].active) << std::endl;
            i++;
        }
        returnOptions("Done", " or (2) to show another attendees/events", function);
    }
}

////////////////////////////////////////////////////

int main()
{
    while (true)
    {
        system("cls"); // Clears the console on Windows
        Menu();
        size_t option = 0;
        option = ValidInput(1, 10);

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
            CheckIfEnrolled();
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
            attendeeSearch();
        }
        else if(option == 8)
        {
            manageEvent();
        }
        else if(option == 9)
        {
            show();
        }
        else
        {
            return false;
        }

    }


}
