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


TEST_CASE("testing game_over_method")
{
	Game g1,g2,g3, g4, g5,g6;
	for(int i=0;i<3;i++)
		g1.board[i] = 1;
	g2.board[0] =1;
	g2.board[4] = 1;
	g2.board[8] = 1;
	g3.board[2] = 1;
	g3.board[5] = 1;
	g3.board[8] = 1;
	g4.board[0]=g4.board[4] = g4.board[8] = 1;
	for(int i =0;i<9;i++) g6.board[i] = 3;

	REQUIRE(g1.is_game_over() == true);
	REQUIRE(g2.is_game_over() == true);
	REQUIRE(g3.is_game_over() == true);
	REQUIRE(g4.is_game_over() == true);
	REQUIRE(g5.is_game_over() == false);
	REQUIRE(g6.is_game_over() == true);
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

// TEST_CASE("testing ai make_move method")
// {
// 	Game g;
// 	Ai comp;
// 	for(int i =0; i<5; i++){
// 	comp.make_move(g);
// 	g.change_turn();
// 	// cout << "Current Board:";
// 	// for(int j=0;j<9;j++) {cout<< g.board[j];}
// 	// cout << endl;
// 	}

// 	vector<int> possible_moves = g.actions();
// 	REQUIRE(possible_moves.size() == 4); //this testcase makes sure that the same gameboard 
// 										// is updated each time and not different copies
// }

TEST_CASE("Testing Hypothetical Move method")
{
	Ai comp;
	Game g,g2;
	g2 = comp.hypothetical_move(g,2);
	REQUIRE(g2.board[2] == -1);
	REQUIRE(g2.get_turn() == 1);
}

TEST_CASE("Testing Actions method")
{
	Game g,g2;
	vector<int> possible_moves = g.actions();
for(int i=0;i<8;i++){
	g2.board[i] = 1;
}

	vector<int> possible_moves2 = g2.actions();
	REQUIRE(possible_moves[8] == 8);
	REQUIRE(possible_moves2.size() == 1);
}

TEST_CASE("Testing max/min methods")
{
	Ai comp;
	REQUIRE(comp.max(7,3) == 7);
	REQUIRE(comp.min(7,3) == 3);
}

TEST_CASE("playing game")
{
	play_game();
	REQUIRE(3==3);
}

TEST_CASE("Testing maxvalue/minvalue methods")
{
	Ai comp;
	Game g,g2,g3;
	g.board[0] = g.board[4] = 1;
	g.change_turn();
	g2.board[0] = g2.board[2]=g2.board[3]=g2.board[7]=g2.board[8]=1;
	g2.board[1]=g2.board[4]=g2.board[5]=g2.board[6]=-1;
	g3.board[0] =g3.board[4] = -1;
	g3.board[8] = 1;
	g3.change_turn();
	REQUIRE(comp.maxvalue(g2) == 0);
	REQUIRE(comp.minvalue(g2) == 0);
	REQUIRE(comp.maxvalue(g)==1);
	REQUIRE(comp.maxvalue(g3) == 0);

}
