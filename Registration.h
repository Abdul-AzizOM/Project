#pragma once
#include <iostream>
enum Regist_status { Enrolled, NotEnrolled };

struct Registration {
    int attendeeId = -1;
    int eventId = -1;
    Regist_status status = NotEnrolled;
};