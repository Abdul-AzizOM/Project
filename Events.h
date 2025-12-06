#pragma once
#include <string>
#include <iostream>

enum Event_Active { ACTIVE, NOT_ACTIVE , CANCELED};


struct Event {
    size_t ID = 0;
    std::string title = "NotEvailable";
    size_t capacity = 0;
    Event_Active active = NOT_ACTIVE;
};


const size_t EventsLimits = 10;


Event events[10]= {
    { 1, "Music Festival", 15, ACTIVE },
    { 2, "Tech Conference", 20, ACTIVE },
    { 3, "Art Expo", 30, CANCELED },
    { 4, "Book Fair", 40, ACTIVE }
};