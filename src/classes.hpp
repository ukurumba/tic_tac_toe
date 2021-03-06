#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <iterator>

using namespace std;



class Game{
	int turn;

public:
	int board[9];
	Game(); //didn't see a use for using a 2D array here. also easier i/o this way
	bool is_game_over();
	int who_won();
	vector<int> actions();
	int get_turn();
	void change_turn();
	void view_board();
	pair<bool,bool> two_in_a_row_exists();
	
};

class NBoard {
	vector<Game> board;
	int turn; 
	int allowed_ttt_board;
	int most_recently_played_board;
	char ai_X_or_O;
	char user_X_or_O;


public:
	NBoard();
	bool is_game_over();
	int who_won();
	vector<Game> get_board();
	void change_board(int which_board, int which_position, int what_value);
	void add_board(Game g);
	bool is_valid_move(int ttt_board, int position);
	bool is_position_taken(int ttt_board, int position);
	void change_turn();
	void change_allowed_ttt_board(int ttt_board);
	void change_most_recently_played_board(int ttt_board);
	int get_most_recently_played_board();
	int get_allowed_ttt_board();
	vector<int> actions();
	int eval_heuristic_utility_value();
	void print_board(); 
	void set_xo(char user_xo); 
	char print_x_or_o(int val);
};

class User {
  int id;
public:
  User();
  void make_move(Game& current_game);
  void make_9_board_move(NBoard& n);
};

class Ai{
	int move_count;
public:
	Ai();
	void make_move(Game& actual_game);
	void make_9_board_move(NBoard& actual_game);
	int minimax(Game g);
	pair<int,int> minimax_h(NBoard b);
	Game hypothetical_move(Game g, int a);
	NBoard hypothetical_9_board_move(NBoard b, int which_position, int what_value);
	int maxvalue(Game g);
	int minvalue(Game g);
	int maxvalue_9_board(NBoard b, int counter, int alpha, int beta);
	int minvalue_9_board(NBoard b, int counter, int alpha, int beta); 
	int max(int i, int j);
	int min(int i, int j);
	void add_to_move_count();
	int depth_limit(); 
};



void play_game(int type_of_game);