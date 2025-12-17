#pragma once
#include <string>
#include <iostream>

// This file lacks comments as well

enum Attendee_Active { IDLE, IN_EVENT, WITHDRAWN, UNDEFINED };


struct Attendee {
    size_t ID = 0 ;
    std::string name = "Invalid";
    Attendee_Active active = UNDEFINED;

};

// Header file conatin a global value in the middle of it
// Think if you really need it and if this is the correct place for it.
const size_t AttendeesLimit = 70; //The max capacity of attendees


// Seems you are using header files for creating data? that is not the right way to do it.
// You should use source files for that unless this is a must have fixed data

Attendee AttendeesList[AttendeesLimit] = {  //The capacity of the attendees is 100
    {1, "Ahmed", IDLE},
    {2, "Omar", IN_EVENT},
    {3, "Youssef", WITHDRAWN},
    {4, "Hassan", UNDEFINED},
    {5, "Faisal", IN_EVENT},
    {6, "Khalid", IDLE},
    {7, "Salim", IN_EVENT},
    {8, "Mansour", IDLE},
    {9, "Tariq", WITHDRAWN},
    {10, "Zayd", IN_EVENT},
    {11, "Rami", IDLE},
    {12, "Majed", IN_EVENT},
    {13, "Adnan", UNDEFINED},
    {14, "Bassam", WITHDRAWN},
    {15, "Anas", IDLE},
    {16, "Jamal", IN_EVENT},
    {17, "Saeed", IDLE},
    {18, "Nasser", IN_EVENT},
    {19, "Ibrahim", WITHDRAWN},
    {20, "Sultan", UNDEFINED},
    {21, "Ali", IDLE},
    {22, "Hadi", IN_EVENT},
    {23, "Walid", WITHDRAWN},
    {24, "Rashid", IDLE},
    {25, "Kamil", IN_EVENT},
    {26, "Latif", WITHDRAWN},
    {27, "Zahir", UNDEFINED},
    {28, "Imran", IN_EVENT},
    {29, "Mustafa", IDLE},
    {30, "Karim", WITHDRAWN},
    {31, "Nabil", IDLE},
    {32, "Adel", IN_EVENT},
    {33, "Fahad", UNDEFINED},
    {34, "Raed", IN_EVENT},
    {35, "Malik", IDLE},
    {36, "Hamza", WITHDRAWN},
    {37, "Tamer", IN_EVENT},
    {38, "Bilal", IDLE},
    {39, "Yahya", IN_EVENT},
    {40, "Harith", WITHDRAWN},
    {41, "Zaki", IDLE},
    {42, "Mahmoud", UNDEFINED},
    {43, "Hussein", IN_EVENT},
    {44, "Jad", IDLE},
    {45, "Mazin", WITHDRAWN},
    {46, "Laith", IN_EVENT},
    {47, "Rami", IDLE},
    {48, "Yasir", IN_EVENT},
    {49, "Shadi", WITHDRAWN},
    {50, "Qasim", IDLE}
};
