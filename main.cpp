#ifndef UNIT_TEST


#include <iostream>


int main()
{
    std::cin.ignore();
    return 0;
}

#else

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#endif
