#pragma once
#include <iostream>

enum Regist_status { 
    Enrolled,//the attendee is enrolled to the event
    NotEnrolled //the attendee is not enrolled to the event
};

//sturcture for registration array
struct Registration {
    size_t attendeeID = 0;
    size_t eventID = 0;
    Regist_status status = NotEnrolled;
};





