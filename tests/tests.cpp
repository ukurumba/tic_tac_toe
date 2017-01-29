#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include  "../src/classes.cpp"

TEST_CASE( "checking classes" )
{
  User user1;
  Game new_game;
  user1.make_move(new_game); //put move as 1
    REQUIRE( new_game.board[0]==1 );
}

