#pragma once
#include <string>
#include <iostream>

enum Event_Active { ACTIVE, NOT_ACTIVE , CANCELED};

// This file lacks any comments.
struct Event {
    size_t ID = 0;
    std::string title = "NotEvailable";
    size_t capacity = 0;
    Event_Active active = NOT_ACTIVE;
};

// Header file conatin a global value in the middle of it
// Think if you really need it and if this is the correct place for it.
const size_t EventsLimits = 10;


// you are creating a global array in a header file, is it really neede here? and why?
Event events[EventsLimits]= {
    { 1, "Music Festival", 15, ACTIVE },
    { 2, "Tech Conference", 20, ACTIVE },
    { 3, "Art Expo", 30, CANCELED },
    { 4, "Book Fair", 40, ACTIVE }
};