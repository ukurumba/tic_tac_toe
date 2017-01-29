#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include  "../src/classes.cpp"
#include "../src/play_game.cpp"

TEST_CASE( "checking classes" )
{
    User user1;
    REQUIRE( user1.is_turn() == false );
}

