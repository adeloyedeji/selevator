#include <iostream>
#include "dispatch.h"

int
main(void)
{
    std::cout << "Hello World" << std::endl;
    if (DEBUG_MODE == 1)
        std::cout << "Application is in Debug mode." << std::endl;
    else
        std::cout << "Debug mode is not enabled." << std::endl;
    
    std::cout << "Elevator instance count: " << SELEVATOR_ELEVATOR_INSTANCE << std::endl;
    std::cout << "Return value: " << hello_there() << std::endl;

    dispatch_init();
    dispatch_print_all();
    dispatch_shutdown();
    return 0;
}