#define CATCH_CONFIG_MAIN
#include "catch.hpp"
// #include  "../src/classes.cpp"
#include "../src/play_game.cpp"

// TEST_CASE("checking user make_move")
// {
//   User user1;
//   Game new_game;
//   user1.make_move(new_game); //put move as 1
//     REQUIRE( new_game.board[0]==1 );
// }


TEST_CASE("testing game_over_function")
{
	Game g1,g2,g3;
	for(int i=0;i<3;i++)
		g1.board[i] = 1;
	g2.board[0] =1;
	g2.board[4] = 1;
	g2.board[8] = 1;
	g3.board[2] = 1;
	g3.board[5] = 1;
	g3.board[8] = 1;
	REQUIRE(g1.is_game_over() == true);
	REQUIRE(g2.is_game_over() == true);
	REQUIRE(g3.is_game_over() == true);
}

// TEST_CASE("playing game")
// {
// 	play_game();
// 	REQUIRE(3==3);
// }