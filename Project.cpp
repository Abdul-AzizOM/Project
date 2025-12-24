//TODO:I recommend arranging the includes alphabitaclly for better readability
#include <iostream>
#include <cstdlib>
#include <functional>
#include <string>
#include <iomanip>
#include <fstream>

#include "Attendees.h"
#include "Events.h"
#include "Registration.h"

// -----------------------------------------------------  
// constants

// TODO:try to split the functions into smaller files for better organization
// TODO:The functions can be grouped based on their functionality into separate files

//TODO: const to constexpr where applicable, also explain what these constants represent
const size_t maxID = 9999999;
const size_t AttendeesLimit = 70; //The max capacity of attendees
const size_t EventsLimits = 10;
const size_t RegistrationLimit = AttendeesLimit * EventsLimits;//each attendee has the chance to take a part in each event


//TODO: these should be in a class or namespace to avoid global namespace pollution
//TODO: for your level maybe in main() is acceptable but in larger projects this will lead to name clashes
Event events[EventsLimits];
Attendee AttendeesList[AttendeesLimit];
Registration registrations[RegistrationLimit];
// -----------------------------------------------------  
// add a limit for the attendee ,events and registration


//TODO: change Menu name to displayMenu for better clarity 
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
    std::cout << "10.Save and Exit\n";
}

// ----------------------------------------------------- 
//input checking if it is valid

size_t ValidInput(const size_t NotSmallerThan, const size_t NotBiggerThan)
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

// --------------------
//return menu

void returnOptions(const std::string condition, const std::string option2, const std::function<void()>& function)
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

//-----------------------------
// attendees secondary fuctions

//get the active 
Attendee_Active getAtendeeActiveStatus(const size_t option)
{
    if (option == 0) { return IDLE; }

    else if (option == 1) { return IN_EVENT; }

    else if (option == 2) { return WITHDRAWN; }

    else { return UNDEFINED; }
}




//check if the id exists or not
bool ID_Exists_attendees(const size_t ID)//true--> avialble , false--> not avialble
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

//check for avialable index for attendee
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

//retrun active to print it
std::string returnAttendeeActive(const size_t index)
{
    if (AttendeesList[index].active == IDLE) { return "IDLE"; }
    else if (AttendeesList[index].active == IN_EVENT) { return "IN_EVENT"; }
    else if (AttendeesList[index].active == WITHDRAWN) { return "WITHDRAWN"; }
    else { return "UNDEFINED"; }

}

//return the active (string to active)
Attendee_Active string_to_active_attendee(const std::string status)
{
    if (status == "IDLE") { return IDLE; }
    else if (status == "IN_EVENT") { return IN_EVENT; }
    else if (status == "WITHDRAWN") { return WITHDRAWN; }
    else { return UNDEFINED; }
}

//return the index of a specific id
size_t attendeeIndexByID(const size_t ID)
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

// ----------------------------------------------------- 
// event secondary functions

//check if the id is already exists
bool ID_Exists_events(const size_t ID)
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

//number of registers in event

size_t RegPerEvent(const size_t ID)
{
    size_t count = 0;
    for (int i = 1; i < RegistrationLimit; i++)
    {
        if (registrations[i].eventID == ID) { count++; }
    }
    return count;
}

//check for available index for events

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

//get the active of the event

Event_Active getEventActiveStatus(const size_t option)
{
    if (option == 0) { return ACTIVE; }

    else if (option == 1) { return NOT_ACTIVE; }

    else { return CANCELED; }
}

//get the index of spicific event

size_t eventID_index(const size_t eventID)
{
    for (int i = 0; i < EventsLimits; ++i)
    {
        if (eventID == events[i].ID) { return i; }
    }
    return 0;
}

//return string of active to print it
std::string returneventsActive(const size_t ID)
{
    if (events[ID].active == ACTIVE) { return "ACTIVE"; }
    else if (events[ID].active == NOT_ACTIVE) { return "NOT_ACTIVE"; }
    else { return "CANCELED"; }

}
//return active when the input is string

Event_Active string_to_active_event(const std::string status)
{
    if (status == "ACTIVE") { return  ACTIVE; }
    else if (status == "NOT_ACTIVE") { return NOT_ACTIVE; }
    else { return CANCELED; }
}



// -----------------------------------------------------
//Rigister secondary functions

//check if the attendee is register in a certian event
bool Registercheck(const size_t attendeeID, const size_t eventID, const Regist_status status, Registration arr[])//check if the user is enrolled or not
{
    for (int i = 0; i < RegistrationLimit; i++)
    {
        if (arr[i].attendeeID == attendeeID &&
            arr[i].eventID == eventID &&
            arr[i].status == Enrolled) {
            return true;
        }
    }
    return false;
}

//avialable index in rigsteration 
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


Regist_status string_to_active_rigistration(const std::string status)
{
    if (status == "Enrolled") { return Enrolled; }
    else  { return NotEnrolled; }
}


// -----------------------------------------------------
//manage secordary functions

void manage_attendee()
{
    std::cout << "Enter attendee ID: ";
    size_t ID;
    size_t option;
    size_t index;
    ID = ValidInput(1, maxID);

    index = attendeeIndexByID(ID);

    if (!(ID_Exists_attendees(ID)))
    {
        returnOptions("This ID doesn't exist!", "or (2) to check another event", manage_attendee);
    }
    else if (AttendeesList[index].active == IDLE)
    {
        std::cout << "This attendee is IDLE.\npress (1) to Go in event it or (2) to withdraw: " << std::endl;
        option = ValidInput(1, 2);
        if (option == 1)
        {
            AttendeesList[index].active = IN_EVENT;
        }
        else
        {
            AttendeesList[index].active = WITHDRAWN;
        }
    }
    else if (AttendeesList[index].active == IN_EVENT)
    {
        std::cout << "This event is active.\npress (1) to go Idle or (2) to withdraw: " << std::endl;

        option = ValidInput(1, 2);

        if (option == 1)
        {
            AttendeesList[index].active = IDLE;
        }
        else
        {
            AttendeesList[index].active = WITHDRAWN;
        }
    }

    else { std::cout << "This attendee was withdrawn or undefined" << std::endl; }

    returnOptions("Done!", "or (2) to manage menu", manage_attendee);
}


void manage_event()
{
    size_t ID;
    size_t option;
    size_t index;
    ID = ValidInput(1, maxID);

    std::cout << "Enter Event ID: ";
    ID = ValidInput(1, maxID);

    index = eventID_index(ID);

    if (!(ID_Exists_events(ID)))
    {
        returnOptions("This event ID doesn't exist!", "or (2) to check another event", manage_event);
    }


    else if (events[index].active == ACTIVE)
    {
        std::cout << "This event is active.\npress (1) to disactivate it or (2) to cancel it" << std::endl;
        option = ValidInput(1, 2);

        if (option == 1) { events[index].active = NOT_ACTIVE; }

        else { events[index].active = CANCELED; }
    }

    else if (events[index].active == NOT_ACTIVE)
    {
        std::cout << "This event is not active.\npress (1) to activate it or (2) to cancel it" << std::endl;
        option = ValidInput(1, 2);
        if (option == 1)
        {
            events[index].active = ACTIVE;
        }
        else
        {
            events[index].active = CANCELED;
        }
    }
    else
    {
        std::cout << "This event was canceled" << std::endl;
    }

    returnOptions("Done!", "or (2) to manage menu", manage_event);
}


// ----------------------------------------------------- 
//adding attendees

void addattendees()
{
    size_t ID;
    std::string name;
    size_t active_option;
    Attendee_Active active;


    std::cout << "Enter the ID: "; // Massage to tell the user to enter the ID

    ID = ValidInput(1, maxID);

    if (!(AttendeesList[AttendeesLimit - 1].ID == 0))//last element / 0 is the defaul if it does change that means the list is full
    {
        returnOptions("There is no Space", "", addattendees);
    }
    else if (ID_Exists_attendees(ID))
    {
        returnOptions("ID already exists", "or (2) to add another attendee", addattendees);
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


void addevents()
{
    size_t ID = 0;
    std::string title;
    size_t capacity;
    Event_Active active;
    size_t active_option;

    std::cout << "Enter the event ID: ";
    ID = ValidInput(1, maxID);

    if (events[EventsLimits - 1].ID != 0) // if the last element is taken means its full
    {
        returnOptions("There is no space!", " ", addevents);
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

void RegisterAttendee()
{
    size_t attendeeID;
    size_t eventID;
    Regist_status status = NotEnrolled;


    std::cout << "Enter the attendee ID: ";
    attendeeID = ValidInput(1, maxID);

    std::cout << "Enter event ID: ";
    eventID = ValidInput(1, maxID);


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
    else if (RegPerEvent(eventID) == events[eventID_index(eventID)].capacity)
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
    attendeeID = ValidInput(1, maxID);
    if (!(ID_Exists_attendees(attendeeID)))
    {
        returnOptions("This ID doesn't exist!", "or (2) to check another attendees", CheckIfEnrolled);
    }


    else {
        std::cout << "Enter event ID: ";
        eventID = ValidInput(1, maxID);
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

    std::cout << "Enter event ID to check: ";
    eventID = ValidInput(1, maxID);

    if (!(ID_Exists_events(eventID)))
    {
        returnOptions("This event ID doesn't exist!", "or (2) to check another event", evenstat);
    }

    else {
        std::cout << "Title: " << events[eventID_index(eventID)].title << std::endl;
        std::cout << "The capacity: " << events[eventID_index(eventID)].capacity << std::endl;
        std::cout << "The Attendance: " << RegPerEvent(eventID) << std::endl;
        std::cout << "Attendance Rate: " << (float(RegPerEvent(eventID)) / float(events[eventID_index(eventID)].capacity)) * 100 << "%" << std::endl; // add the number of register for event
        returnOptions("Done!", "or (2) to check another event", evenstat);
    }
}

// ----------------------------------------------------- 
//the attendee registerations

void ListofEnrolledEvents()
{
    size_t attendeeID = 0;
    size_t numOfenrolled = 1;

    std::cout << "Enter the ID: ";
    attendeeID = ValidInput(1, maxID);

    for (int i = 0; i < RegistrationLimit; ++i)
    {
        if (attendeeID == registrations[i].attendeeID)
        {
            std::cout << numOfenrolled << "." << events[eventID_index(registrations[i].eventID)].title << std::endl;
            numOfenrolled++;

        }
    }
    returnOptions("Done!", "or (2) to check another event", ListofEnrolledEvents);
}

// ----------------------------------------------------- 
//search

void EnrolledEvents(size_t ID)
{
    int count = 1;
    for (int i = 0; i < RegistrationLimit; i++)
    {
        if (registrations[i].attendeeID == ID &&
            registrations[i].status == Enrolled)
        {
            std::cout << count << ". " << events[eventID_index(registrations[i].eventID)].title << std::endl;
            count++;
        }

    }
    if (count == 1)
    {
        std::cout << "Not Enrolled in any event!" << std::endl;
    }
}

// Logic is over engineered here, you can just call the function directly in the main loop
void attendeeSearch()
{
    size_t ID = 0;
    std::cout << "Enter the ID: ";
    ID = ValidInput(1, maxID);

    if (!(ID_Exists_attendees(ID)))
    {
        returnOptions("This ID doesn't exist!", "or (2) to check another attendees", attendeeSearch);

    }


    size_t Index = attendeeIndexByID(ID);
    std::cout << "Name: " << AttendeesList[Index].name << std::endl;
    std::cout << "Status: " << returnAttendeeActive(AttendeesList[Index].active) << std::endl;
    std::cout << "Enrolled Events:" << std::endl;
    EnrolledEvents(ID);

    returnOptions("Done!", "or (2) to check another attendees", attendeeSearch);

}

//----------
// Enable/Disable


void manager()
{

    size_t ID = 0;
    size_t managEventOption;
    size_t choice = 0;

    std::cout << "Enter (1) for attendee or (2) for events: ";
    choice = ValidInput(1, 2);

    // Too long function, consider breaking it into smaller functions--break it to two functions (events and attendees)
    // I am sure the logic could be simplified as well
    if (choice == 1)//attendee manage
    {
        manage_attendee();
    }


    else {
        manage_event();
    }

}

// ----------------------------------------------------- 
//show events or attendees




void show()
{

    size_t choice = 0;
    const int idWidth = 8;//depend on the maxID (has 7 digits) and +1 to better appearance
    const int nameWidth = 20;
    const int activeWidth = 8;//tallest active length is 11 and +1 to better apearance
    const int capacityWidth = 8;
    int index = 0;



    std::cout << "Enter (1) for attendees or (2) for events: ";
    choice = ValidInput(1, 2);

    std::cout << std::endl;//for better appearance

    if (choice == 1)
    {
        std::cout << std::left << std::setw(idWidth) << "ID"
            << std::left << std::setw(nameWidth) << "Name"
            << std::left << std::setw(activeWidth) << "Active" << std::endl;
        while (AttendeesList[index].ID != 0 && index < AttendeesLimit)
        {
            std::cout << std::left << std::setw(idWidth) << AttendeesList[index].ID
                << std::left << std::setw(nameWidth) << AttendeesList[index].name
                << std::left << std::setw(activeWidth) << returnAttendeeActive(index) << std::endl;
            ++index;

        }
        returnOptions("Done", " or (2) to show another attendees/events", show);
    }
    else
    {
        std::cout << std::left << std::setw(idWidth) << "ID"
            << std::left << std::setw(nameWidth) << "Name"
            << std::left << std::setw(activeWidth) << "Active"
            << std::left << std::setw(capacityWidth) << "Capacity" << std::endl;

        while (events[index].ID != 0 && index < EventsLimits)
        {
            std::cout << std::left << std::setw(idWidth) << events[index].ID
                << std::left << std::setw(nameWidth) << events[index].title
                << std::left << std::setw(activeWidth) << events[index].active
                << std::left << std::setw(capacityWidth) << events[index].capacity << std::endl;
            ++index;
        }
        returnOptions("Done", " or (2) to show another attendees/events", show);
    }
}

//--------
//load / save

void load_attendees()
{
    int location;
    int line_len;
    size_t index = 0;
    std::string ID;
    std::string name;
    std::string active;
    std::string line;
    std::ifstream AttendeesFile("Attendees.csv");

    std::getline(AttendeesFile, line);//skip the headers

    if (!(AttendeesFile.is_open()))
    {
        std::cout << "Error opening attendees file for reading!" << std::endl;
        return;

    }
    while (std::getline(AttendeesFile, line)) {
        line_len = line.length();//avoid repeating the function in each new line

        location = line.find(",");//find the comma location to take what is before it
        ID = line.substr(0, location);//take all the string before the comma 
        AttendeesList[index].ID = stoi(ID);
        line = line.substr(location + 1, line_len); //cut the make a substring that does'nt include the first comma

        //repeat the prevous pattern to get the other virables

        location = line.find(",");
        AttendeesList[index].name = line.substr(0, location);
        line = line.substr(location + 1, line_len);

        AttendeesList[index].active = string_to_active_attendee(line);

        ++index;
    }
    AttendeesFile.close();
}

void load_events()
{
    int location;
    int line_len;
    size_t index = 0;
    std::string ID;
    std::string capacity;
    std::string line;

    std::ifstream EventsFile("Events.csv");

    std::getline(EventsFile, line);//skip the headers

    if (!(EventsFile.is_open()))
    {
        std::cout << "Error opening events file for reading!" << std::endl;
        return;
    }
    while (std::getline(EventsFile, line)) {
        line_len = line.length();//avoid repeating the function in each new line

        location = line.find(",");//find the comma location to take what is before it
        ID = line.substr(0, location);//take all the string before the comma 
        events[index].ID = stoi(ID);
        line = line.substr(location + 1, line_len); //cut the make a substring that does'nt include the first comma

        //repeat the prevous pattern to get the other virables

        location = line.find(",");
        events[index].title = line.substr(0, location);
        line = line.substr(location + 1, line_len);

        location = line.find(",");
        capacity = line.substr(0, location);
        events[index].capacity = stoi(capacity);
        line = line.substr(location + 1, line_len);

        events[index].active = string_to_active_event(line);

        ++index;
    }

    EventsFile.close();
}

void load_Registration()
{
    int location;
    int line_len;
    size_t index = 0;
    std::string AttendeeID;
    std::string EventID;
    std::string Status;
    std::string line;

    std::ifstream RegistrationFile("Registration.csv");

    std::getline(RegistrationFile, line);//skip the headers

    if (!(RegistrationFile.is_open()))
    {
        std::cout << "Error opening events file for reading!" << std::endl;
        return;
    }
    while (std::getline(RegistrationFile, line)) {
        line_len = line.length();//avoid repeating the function in each new line

        location = line.find(",");//find the comma location to take what is before it
        AttendeeID = line.substr(0, location);//take all the string before the comma 
        registrations[index].attendeeID = stoi(AttendeeID);
        line = line.substr(location + 1, line_len); //cut the make a substring that does'nt include the first comma

        //repeat the prevous pattern to get the other virables

        location = line.find(",");
        EventID = line.substr(0, location);
        registrations[index].eventID = stoi(EventID);
        line = line.substr(location + 1, line_len);

        registrations[index].status = string_to_active_rigistration(line);

        ++index;
    }

    RegistrationFile.close();
}

// ----------------------------------------------------- 
//save data
void save()
{
    //save Attendees
    size_t ArrayElements = available_index_attendees();

    std::ofstream AttendeesFile("Attendees.csv", std::ofstream::trunc);//turnc is used for erase all data

    if (!(AttendeesFile.is_open()))
    {
        std::cout << "Error opening attendees file for writing!" << std::endl;
        return;
    }
    AttendeesFile << "id,name,status" << std::endl;//rewrite the headers

    for (int index = 0; index < ArrayElements; ++index) {
        AttendeesFile << AttendeesList[index].ID << ","
            << AttendeesList[index].name << ","
            << returnAttendeeActive(index) << std::endl;
    }
    AttendeesFile.close();


    //save Events
    std::ofstream EventsFile("Events.csv", std::ofstream::trunc);

    if (!(EventsFile.is_open()))
    {
        std::cout << "Error opening events file for writing!" << std::endl;
        return;
    }

    ArrayElements = available_index_events();

    EventsFile << "id,title,capacity,status" << std::endl;//rewrite the headers

    for (int index = 0; index < ArrayElements; ++index) {
        EventsFile << events[index].ID << ","
            << events[index].title << ","
            << events[index].capacity << ","
            << returneventsActive(index) << std::endl;
    }
    EventsFile.close();

    //save registrations
    ArrayElements = available_index_rig();

    EventsFile << "id,title,capacity,status" << std::endl;//rewrite the headers

    for (int index = 0; index < ArrayElements; ++index) {
        EventsFile << registrations[index].attendeeID << ","
            << registrations[index].eventID << ","
            << registrations[index].status << ","
            << returneventsActive(index) << std::endl;
    }
    EventsFile.close();
}



int main()
{
    load_attendees();
    load_events();
    load_Registration();


    while (true)
    {
        system("cls"); // Clears the console on Windows
        Menu();
        size_t option = 0;
		// TODO: avoid magic numbers, use named constants instead
		// get user option seperately from the validation point.
        option = ValidInput(1, 10);

		// TODO: avoid long if-else chains, use switch-case
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
        else if (option == 8)
        {
            manager();
        }
        else if (option == 9)
        {
            show();
        }
        else
        {
            //save();
            return false;
        }

    }

}