#pragma once
#include <string>
#include <iostream>

enum Attendee_Acite { IDLE, IN_EVENT, WITHDRAWN, UNDEFINED };


struct Attendee {
    int ID = -1;
    std::string name = "Invalid";
    Attendee_Acite active = UNDEFINED;

};


Attendee AttendeesList[100] = {  //The capacity of the attendees is 100
    {1, "Ahmed Hassan", IDLE},
    {2, "Omar Khalid", IN_EVENT},
    {3, "Youssef Ibrahim", WITHDRAWN},
    {4, "Hassan Omar", UNDEFINED},
    {5, "Faisal Saud", IN_EVENT},
    {6, "Khalid Nasser", IDLE},
    {7, "Salim Rashid", IN_EVENT},
    {8, "Mansour Ahmed", IDLE},
    {9, "Tariq Abdullah", WITHDRAWN},
    {10, "Zayd Hamad", IN_EVENT},
    {11, "Rami Sami", IDLE},
    {12, "Majed Faris", IN_EVENT},
    {13, "Adnan Bashir", UNDEFINED},
    {14, "Bassam Zayd", WITHDRAWN},
    {15, "Anas Talal", IDLE},
    {16, "Jamal Khalaf", IN_EVENT},
    {17, "Saeed Yassin", IDLE},
    {18, "Nasser Mishal", IN_EVENT},
    {19, "Ibrahim Jaber", WITHDRAWN},
    {20, "Sultan Murad", UNDEFINED},
    {21, "Ali Hassan", IDLE},
    {22, "Hadi Majed", IN_EVENT},
    {23, "Walid Tariq", WITHDRAWN},
    {24, "Rashid Saeed", IDLE},
    {25, "Kamil Yusuf", IN_EVENT},
    {26, "Latif Omar", WITHDRAWN},
    {27, "Zahir Musa", UNDEFINED},
    {28, "Imran Rashed", IN_EVENT},
    {29, "Mustafa Kareem", IDLE},
    {30, "Karim Adnan", WITHDRAWN},
    {31, "Nabil Malik", IDLE},
    {32, "Adel Fawzi", IN_EVENT},
    {33, "Fahad Shaker", UNDEFINED},
    {34, "Raed Munir", IN_EVENT},
    {35, "Malik Samir", IDLE},
    {36, "Hamza Luqman", WITHDRAWN},
    {37, "Tamer Raed", IN_EVENT},
    {38, "Bilal Khalid", IDLE},
    {39, "Yahya Mahmud", IN_EVENT},
    {40, "Harith Saqr", WITHDRAWN},
    {41, "Zaki Farid", IDLE},
    {42, "Mahmoud Yusuf", UNDEFINED},
    {43, "Hussein Taha", IN_EVENT},
    {44, "Jad Rashad", IDLE},
    {45, "Mazin Faisal", WITHDRAWN},
    {46, "Laith Murad", IN_EVENT},
    {47, "Rami Zahir", IDLE},
    {48, "Yasir Jamil", IN_EVENT},
    {49, "Shadi Adel", WITHDRAWN},
    {50, "Qasim Nasser", IDLE}
};
