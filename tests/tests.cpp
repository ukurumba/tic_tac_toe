#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include  "../src/classes.hpp"



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

TEST_CASE("Testing 9_Board Implementation")
{
	NBoard b;
	REQUIRE(b.get_board()[0].board[0] == 0);
}

// TEST_CASE("Testing 9_Board User Move Method")
// {
// 	NBoard b;
// 	User u;
// 	u.make_9_board_move(b);
// 	REQUIRE(b.get_board()[0].board[0] == -1);
// 	REQUIRE(b.get_allowed_ttt_board() == 0);

// }

TEST_CASE("Testing AI 9_Board Make Move Method")
{
	Ai comp;
	NBoard b;
	comp.make_9_board_move(b);
	bool bool_val = false;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if (b.get_board()[i].board[j] != 0)
				bool_val = true;
		}
	}
	REQUIRE(bool_val == true);

}

TEST_CASE("Testing AI NBoard Hypothetical Move Method"){
	Ai comp;
	NBoard b;
	b.change_allowed_ttt_board(2);
	NBoard b2 = comp.hypothetical_9_board_move(b,3,1);
	REQUIRE(b2.get_board()[2].board[3] == 1);
	REQUIRE(b2.get_allowed_ttt_board() == 3);
}

TEST_CASE("Testing Terminal Test and Who_Won 9 Board Methods")
{
	Ai comp;
	NBoard b,b2;
	for(int i=0;i<2;i++){
		b.change_board(0,i,1);
	}
	b.change_allowed_ttt_board(0);
	b2 = comp.hypothetical_9_board_move(b,2,1);
	REQUIRE(b.is_game_over() == false);
	REQUIRE(b2.is_game_over() == true);
	REQUIRE(b2.who_won() == 100);
}

TEST_CASE("Testing eval_utility_value heuristic method")
{
	NBoard b;
	Ai comp;
	for(int i=0;i<3;i++){
		for(int j=0;j<2;j++){
			b.change_board(i,j,1);
		}
	}
	REQUIRE(b.eval_heuristic_utility_value() == 21);
}

TEST_CASE("Timing AI Make_Move method")
{

clock_t start;
double time_elapsed;
Ai comp;
vector<NBoard> boards;
vector<double> timings; 
for (int i=0;i<10;i++){
	boards.push_back(NBoard());
	start = clock();
	comp.make_9_board_move(boards[i]);
	time_elapsed = (clock() - start) / (double) CLOCKS_PER_SEC;
	timings.push_back(time_elapsed);
}
double avg_time=0;
for(int i=0;i<10;i++){
	avg_time+=timings[i];
}
cerr << "Average time per move: " << avg_time/10 << endl;
REQUIRE(3 == 3); 
}
TEST_CASE("playing game")
{
	play_game();
	REQUIRE(3==3);
}