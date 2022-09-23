//
// Created by bear on 9/18/2022.
//

#include <cstdio>
#include "everydo.hh"
#include <catch2/catch_all.hpp>

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE("Open Database", "[Database]") {
    char filename[500];
    errno_t err = tmpnam_s(filename, sizeof(filename));

    SqlDatabase sdb(filename);



}
