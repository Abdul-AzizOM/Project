#pragma once
#include <string>
#include <iostream>

enum Event_Active { ACITIVE, NOT_ACTIVE, CANCEDLED };


struct Event {
    int ID = -1;
    std::string title = "NotEvailable";
    size_t capacity = 0;
    Event_Active active = NOT_ACTIVE;
};