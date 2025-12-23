#pragma once
#include <string>
#include <iostream>

enum Event_Active { 
    ACTIVE,//Currently active
    NOT_ACTIVE, // Event is not active (scheduled, paused, or completed)
    CANCELED // Event has been canceled and will not take place
};

//structure for events array
struct Event {
    size_t ID = 0;
    std::string title = "NotEvailable";
    size_t capacity = 0;
    Event_Active active = NOT_ACTIVE;
};
