#pragma once
#include <string>
#include <iostream>


enum Attendee_Active { 
    IDLE,//IDLE-->didn't enter any event
    IN_EVENT,//IN_EVENT--> currently in event
    WITHDRAWN,//withdrawn from the events
    UNDEFINED//not known
}; 

//structure for attendees array
struct Attendee {
    size_t ID = 0 ;
    std::string name = "Invalid";
    Attendee_Active active = UNDEFINED;

};

