#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <iterator>
#include <ctime>

using namespace std;

#include "classes.hpp"

Game::Game(){ //initializing game board
	for (int i=0;i<9;i++){
		board[i] = 0;
	}
	turn = -1; }

int Game::get_turn(){return turn;}

void Game::change_turn()
{
	if(turn == 1) turn = -1;
	else if (turn == -1) turn = 1;
}

void Game::view_board(){
for(int i=0;i<7;){
	cout << board[i]<<board[i+1]<<board[i+2]<<endl;
	i+=3;
}
}



Game Ai::hypothetical_move(Game g, int a){ //the transition model that returns the result of an action on a given state
	int i = g.get_turn();
	g.board[a] = i;
	g.change_turn();
	return g;
}

vector<int> Game::actions(){
	vector<int> possible_actions; 
	for(int i = 0; i < 9; i++){ //add all open positions to list of possible actions and return that list. Use Vector Class for easy management of list
		if (board[i] == 0)
		{
			possible_actions.push_back(i);
		}
	}
	return possible_actions;
}

User::User(){
	id = -1;
}

void User::make_move(Game& current_game){
	current_game.view_board();
	int move;
	cin >> move;

	while (current_game.board[move-1] != 0 || move > 9 || move < 1){
		if(move > 9 or move < 1){
			cerr <<"Error: Invalid move location. Please select an integer between 1 and 9."<<endl;
			cin.clear();
			cin.ignore(10000,'\n');
			cin >> move;
		}
		else if (current_game.board[move-1] != 0){
			cerr << "Error: Player/AI has already played at selected position. Please select a valid move."<< endl;
			cin.clear();
			cin.ignore(10000,'\n');
			cin >> move;
		}
	}

	current_game.board[move - 1] = -1;
	current_game.change_turn();
};

void User::make_9_board_move(NBoard& n){
	int board, position;
	cin >> board >> position;
	cout << "Allowed board: " << n.get_allowed_ttt_board() << endl; 
	while(n.is_position_taken(board-1,position-1) || !n.is_valid_move(board-1,position-1)){
		if(n.is_position_taken(board-1,position-1)){
		cerr << "Error: Player/AI has already played at selected position. Please select a valid move." << endl;
		cin.clear();
		cin.ignore(10000,'\n');
		cin >> board >> position;
		}
		else if (!n.is_valid_move(board-1,position-1)){
		cerr << "That move was not valid, either because the entered values were out of range or because that board cannot be played on. Please enter a correct pair of numbers (which board:      which position:    )" << endl;
		cin.clear();
		cin.ignore(10000,'\n');
		cin >> board >> position;
		}
	}
	n.change_most_recently_played_board(board-1); 
	n.change_board(board-1, position-1,-1);
	n.change_turn();
	n.change_allowed_ttt_board(position - 1); 
}

void Ai::make_move(Game& actual_game){
	Game g(actual_game); //making copy of game to use in decision-making
	int move = minimax(g);
	if (move < 0 || move > 8){
		cerr << "Error: AI move out of range selected in Ai make_move method." << endl;
	}
	actual_game.board[move] = 1;
	actual_game.change_turn();
	cout << move+1<<endl;
}

void Ai::make_9_board_move(NBoard& actual_game){
	NBoard b(actual_game); //making copy to use in decision-making
	pair<int,int> move = minimax_h(b);
	actual_game.change_most_recently_played_board(actual_game.get_allowed_ttt_board());
	actual_game.change_board(move.first, move.second, 1);
	actual_game.change_allowed_ttt_board(move.second);
	cout << "Board: " << move.first + 1 << "Position: " << move.second + 1 << endl; 
}

pair<int,int> Ai::minimax_h(NBoard b){ 
	if (b.get_allowed_ttt_board() == -100) b.change_allowed_ttt_board(0); 
	vector<int> possible_moves = b.actions(); //returns possible actions for a given 9 board.
	int v = -100;
	int move=0;
	int util_val = 0;
	int counter = 0;
	if (possible_moves.size() == 0){
		cerr << "Error: No possible moves for AI but game has not been terminated." <<endl;
	}
	for (int i = 0; i < possible_moves.size();i++){
		util_val = minvalue_9_board(hypothetical_9_board_move(b,possible_moves[i],1),counter, -10000, 10000);
		if (util_val > v){
			move = possible_moves[i];
			v = util_val;
		}
	}

	return make_pair(b.get_allowed_ttt_board(), move); 
}


int Ai::minvalue_9_board(NBoard b, int counter, int alpha, int beta){
	counter += 1;
	if (b.is_game_over()) return b.who_won();
	else if(counter > 7){ return b.eval_heuristic_utility_value();}
	else{
		vector<int> possible_moves = b.actions();
		int v = 1000;
		for(int a = 0; a < possible_moves.size();a++){
			v = min(v,maxvalue_9_board(hypothetical_9_board_move(b,possible_moves[a],-1),counter, alpha, beta));
			if(v <= alpha) return v;
			beta = min(beta, v);
		}
		return v;
	}
}

int Ai::maxvalue_9_board(NBoard b, int counter, int alpha, int beta){
	counter += 1; 
	if (b.is_game_over()) return b.who_won();
	else if (counter > ) { return b.eval_heuristic_utility_value();}
	else{
		vector<int> possible_moves = b.actions();
		int v = -1000;
		for(int a = 0; a < possible_moves.size(); a++){
			v = max(v,minvalue_9_board(hypothetical_9_board_move(b,possible_moves[a],1),counter, alpha, beta));
			if(v >= beta) return v;
			alpha = max(alpha, v);
		}
		return v;
	}
}

NBoard Ai::hypothetical_9_board_move(NBoard b, int move, int value){
	b.change_board(b.get_allowed_ttt_board(),move,value);
	b.change_most_recently_played_board(b.get_allowed_ttt_board());
	b.change_allowed_ttt_board(move);
	return b;
}

int Ai::maxvalue(Game g){ //returns maximum utility value possible from the given state g
	if(g.is_game_over()) {return g.who_won(); }
	else{
		vector<int> possible_moves = g.actions();
		int v = -5;
		for(int a=0; a <possible_moves.size();a++){
			Game g2 = hypothetical_move(g,possible_moves[a]);
			v = max(v,minvalue(g2)); 
		}
	
	return v; 
}
}

int Ai::minvalue(Game g){
	if(g.is_game_over()) return g.who_won();
	else{
	vector<int> possible_moves = g.actions();
	int v = 5;
		for(int a=0; a < possible_moves.size();a++){
			v = min(v,maxvalue(hypothetical_move(g,possible_moves[a])));
		}

	return v; 
}
}

int Ai::max(int i, int j){
	if(i>j) return i;
	else if (i<j) return j;
	else return i;
}

int Ai::min(int i, int j){
	if(i>j) return j;
	else if (j>i) return i;
	else return j;
}

int Ai::minimax(Game g){
	int v = -100;
	int move=0;
	int util_val = 0;
	vector<int>  possible_moves = g.actions();
	if (possible_moves.size() == 0){
		cerr << "Error: No possible moves for AI but game has not been terminated." <<endl;
	}
	for (int i = 0; i < possible_moves.size();i++){
		util_val = minvalue(hypothetical_move(g,possible_moves[i]));
		if (util_val > v){
			move = possible_moves[i];
			v = util_val;
		}
	}
	return move; 
}






bool Game::is_game_over(){
	for(int i=0; i<7;i+=3){
		if(board[i] == board[i+1] && board[i] ==board[i+2] && board[i]!= 0) return true;
	}
	for(int i=0;i<3;i++){
		if(board[i] == board[i+3] && board[i] == board[i+6] && board[i] != 0) return true;
	}
	if(board[0] == board[4] && board[0] == board[8] && board[0] != 0) return true;
	else if(board[2] == board[4] && board[2] == board[6] && board[2] != 0) return true;

	for(int i=0;i<9;i++){
		if (board[i] == 0)
			return false;
	}
return true;
}

int Game::who_won()
{
	for(int i=0; i<7;i+=3){
		if(board[i] == board[i+1] && board[i] ==board[i+2] && board[i] == 1) return 1;
		else if(board[i] == board[i+1] && board[i] ==board[i+2] && board[i] == -1) return -1;
	}
	for(int i=0;i<3;i++){
		if(board[i] == board[i+3] && board[i] == board[i+6] && board[i] == 1) return 1;
		else if(board[i] == board[i+3] && board[i] == board[i+6] && board[i] == -1) return -1;
	}

	if(board[0] == board[4] && board[0] == board[8] && board[0] == 1) return 1;
	else if(board[2] == board[4] && board[2] == board[6] && board[2] == 1) return 1;
	if(board[0] == board[4] && board[0] == board[8] && board[0] == -1) return -1;
	else if(board[2] == board[4] && board[2] == board[6] && board[2] == -1) return -1;
	bool all_squares_covered = true; 
	for(int i=0;i<9;i++){
		if(board[i] == 0)
			all_squares_covered = false;
	}
	if (all_squares_covered) return 0; //a draw
	else if (!all_squares_covered) return -5000; //a check used in 9_board is_game_over method
}

pair<bool,bool> Game::two_in_a_row_exists(){ 

/*essentially this method checks to see if any row/column/diagonal sums to 2 indicating two 1's and a 0 or sums to -2 indicating
two -1's and a 0. It then returns a pair of booleans corresponding to the truth value of those two statements. */

	pair<bool,bool> two_in_a_row = make_pair(false,false);
	for(int i=0; i<7;i+=3){
		if(board[i] + board[i+1] + board[i+2] == 2) two_in_a_row.first = true;
		if(board[i] + board[i+1] + board[i+2] == -2) two_in_a_row.second=true;
	}
	for(int i=0;i<3;i++){
		if(board[i] + board[i+3] + board[i+6] == 2) two_in_a_row.first = true;
		if(board[i] + board[i+3] + board[i+6] == -2) two_in_a_row.second=true;
	}

	if(board[0] + board[4] + board[8] == 2) two_in_a_row.first = true;
	if(board[0] + board[4] + board[8] == -2) two_in_a_row.second=true;
	if(board[2] + board[4] + board[6] == 2) two_in_a_row.first = true;
	if(board[2] + board[4] + board[6] == -2) two_in_a_row.second=true;
	return two_in_a_row;
}


void play_game(){

  // User user1;

	//Timing AI move length
  	clock_t start;
	double time_elapsed;
	// Ai comp;
	//   Game new_game;

	 // int first_mover = who_is_first();
	  cerr << "Would you like to play X or O?" << endl;
	  char x_or_o;
	  cin >> x_or_o; 
	//   while (! new_game.is_game_over()){
	//     // if (first_mover == 1){
	//   	if (x_or_o == 'x' || 'X')
	//   	{
	//       user1.make_move(new_game);
	//       if(new_game.is_game_over())
	//       	break;

	//       start = clock();
	//       comp.make_move(new_game);
	//       time_elapsed = (clock() - start) / (double) CLOCKS_PER_SEC;
	//       cerr << "The AI took " << time_elapsed << "s to make a move" << endl;
	//   	}
	//   	else 

	//  	{
	    
	// 		start = clock();
	// 		comp.make_move(new_game);
	// 		time_elapsed = (clock() - start) / (double) CLOCKS_PER_SEC;
	// 		cerr << "The AI took " << time_elapsed << "s to make a move" << endl;	
	// 		if(new_game.is_game_over())
	// 		      	break;
	// 		else user1.make_move(new_game);

	//  	}

	//   }
	 
	//  int winner = new_game.who_won();

	//   if (winner == -1)
	//   {

	//   	cerr << "The Player Wins!"<<endl;
	  	
	//   }
	//   else if (winner == 1)
	//   	cerr << "The computer wins!" << endl;

	//   else if (winner ==0)
	//   	cerr << "It was a Draw!"<< endl;
	// }

		User user1;
		Ai comp;
		NBoard b;
		while (! b.is_game_over()){
			if(x_or_o == 'X' | x_or_o == 'x'){
		
			user1.make_9_board_move(b);
				if(b.is_game_over())
					break;

			start = clock();

			comp.make_9_board_move(b);

			time_elapsed = (clock() - start) / (double) CLOCKS_PER_SEC;
	      	cerr << "The AI took " << time_elapsed << "s to make a move" << endl;
			}
			else {
				start = clock();

			comp.make_9_board_move(b);

			time_elapsed = (clock() - start) / (double) CLOCKS_PER_SEC;
	      	cerr << "The AI took " << time_elapsed << "s to make a move" << endl;

	      	if(b.is_game_over())
					break;

			user1.make_9_board_move(b);	
			}
		}

		int winner = b.who_won();
		if (winner == -100)
			cerr << "The Player Wins!" << endl;
		else if (winner == 100)
			cerr << "The computer Wins!" << endl;
		else if (winner == 0)
			cerr << "It was a Draw!" << endl; 
	
}


NBoard::NBoard(){
	for(int i=0;i<9;i++){
		Game g;
		add_board(g);
	}
	turn = -1;
	allowed_ttt_board = -100;
	most_recently_played_board = -100;
}
vector<Game> NBoard::get_board(){return board;}
void NBoard::change_board(int which_board, int which_position, int what_value){board[which_board].board[which_position] = what_value;}
void NBoard::add_board(Game g){board.push_back(g);}
	
void NBoard::change_turn(){
	if (turn == 1) turn = -1;
	else if (turn == -1) turn = 1;
	for(int i=0;i<9;i++) board[i].change_turn();
}

bool NBoard::is_position_taken(int ttt_board, int position){
	if(board[ttt_board].board[position] != 0) return true;
	else return false; 
}

bool NBoard::is_valid_move(int ttt_board, int position){
	if(allowed_ttt_board != ttt_board && allowed_ttt_board != -100) return false; //return false if not new board or not correct board. 
	else if (position > 8 || position < 0) return false;
	else return true; 
}

void NBoard::change_allowed_ttt_board(int ttt_board){ allowed_ttt_board = ttt_board;}

int NBoard::get_allowed_ttt_board(){ return allowed_ttt_board;}

bool NBoard::is_game_over(){
	int ttt_board = most_recently_played_board;
	if(ttt_board == -100) return false; //newly intialized boards cannot be over yet
	else {
		bool win_or_loss_or_tie = board[ttt_board].is_game_over(); //checking to see if win/loss/draw on previously played board
		if (win_or_loss_or_tie){
			int winner = who_won(); 
			if (winner == 0){ //if previous board was a draw then must check if every single board was a draw
				bool all_boards_are_draw = true;
				for(int i=0;i<9;i++){ //checking all 9 tic_tac_toe boards
					if (board[i].who_won() == -5000) //Game who_won method returns -5000 if nobody has won and not every space is covered.
						return false;
				}
			}
			else return true; 
		}
	}
}

int NBoard::who_won(){
	int ttt_board = most_recently_played_board;
	return 100 * board[ttt_board].who_won(); //scale by 100 so that a terminal state is more valuable than any heuristic state

}

int NBoard::get_most_recently_played_board(){return most_recently_played_board;}
void NBoard::change_most_recently_played_board(int board){ most_recently_played_board = board;}

int NBoard::eval_heuristic_utility_value(){
	/* This heuristic evaluates based on the number of ttt_boards that have a winning move if moved to. For example, if the top
	left board has 2 X's in a row, then the top left position is blocked off for O on all 8 of the other boards. The count of all 
	open top left positions for the other boards is taken and summed with such a count for every other position (top middle, top right, etc.).
	From this is subtracted the analogous total count for 2 O's in a row. This is then returned as the utility value of 
	the board for X. */
	int util_value = 0;
	for(int i=0;i<9;i++){ //for every tic_tac_toe board i: 
		pair<bool,bool> two_in_a_row=board[i].two_in_a_row_exists(); //returns pair of booleans, first corresponding to if two_in_a_row exists for AI, second for player
		if(two_in_a_row.first || two_in_a_row.second){ //if any two in a row exists in board i:
			int count = 0; 
			for(int j=0;j<9;j++){
				if (board[j].board[i] == 0){
					count += 1;
				}
			}
			if(two_in_a_row.first&& !two_in_a_row.second){ //if two in a row exists only for AI:
				util_value += count;
			}
			else if(!two_in_a_row.first && two_in_a_row.second){ //if two in a row exists only for player:
				util_value -= count;
			}//otherwise utility value of two in a rows cancels out 
		}
	}
	return util_value;
}

vector<int> NBoard::actions(){
	int ttt_board = allowed_ttt_board;
	return board[ttt_board].actions();
}
