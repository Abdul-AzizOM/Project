#pragma once
#include <iostream>

size_t ValidInput(size_t NotSmallerThan, size_t NotBiggerThan)
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