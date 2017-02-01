#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include  "../src/classes.cpp"


// TEST_CASE("checking user make_move")
// {
//   User user1;
//   Game new_game;
//   user1.make_move(new_game); //put move as 1
//     REQUIRE( new_game.board[0]==1 );
// }


TEST_CASE("testing game_over_function")
{
	Game g1,g2,g3, g4, g5;
	for(int i=0;i<3;i++)
		g1.board[i] = 1;
	g2.board[0] =1;
	g2.board[4] = 1;
	g2.board[8] = 1;
	g3.board[2] = 1;
	g3.board[5] = 1;
	g3.board[8] = 1;
	g4.board[0]=g4.board[4] = g4.board[8] = 1;

	REQUIRE(g1.is_game_over() == true);
	REQUIRE(g2.is_game_over() == true);
	REQUIRE(g3.is_game_over() == true);
	REQUIRE(g4.is_game_over() == true);
	REQUIRE(g5.is_game_over() == false);
}

TEST_CASE("testing who_won method")
{
		Game g1,g2,g3, g4, g5;
	for(int i=0;i<3;i++)
		g1.board[i] = 1;
	g2.board[0] =1;
	g2.board[4] = 1;
	g2.board[8] = 1;
	g3.board[2] = -1;
	g3.board[5] = -1;
	g3.board[8] = -1;
	g4.board[0]=g4.board[4] = g4.board[8] = -1;
	for(int i=0;i<9;i++)
		g5.board[i] = 11;

	REQUIRE(g1.who_won() == 1);
	REQUIRE(g2.who_won() == 1);
	REQUIRE(g3.who_won() == -1);
	REQUIRE(g4.who_won() == -1);
	REQUIRE(g5.who_won() == 0);
}

TEST_CASE("testing ai make_move method")
{
	Game g;
	Ai comp;
	comp.make_move(g);
	bool move_made = false;
	for (int i=0;i<9;i++){
		if (g.board[i] != 0)
			move_made = true;
	}

	REQUIRE(move_made == true );

}

// TEST_CASE("playing game")
// {
// 	play_game();
// 	REQUIRE(3==3);
// }