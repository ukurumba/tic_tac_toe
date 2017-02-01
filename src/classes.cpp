#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>

using namespace std;



class Game{
	int turn;

public:
	int board[9];
	Game(){
		for (int i=0;i<9;i++){
			board[i] = 0;
		}
		turn = -1; 
	;} //didn't see a use for using a 2D array here. also easier i/o this way
	bool is_game_over();
	int who_won();
	vector<int> actions();
	int get_turn(){ return turn;}
	void change_turn(){
		if(turn == 1) turn = -1;
		else if (turn == -1) turn = 1;
	}
	void view_board(){
		for(int i=0;i<7;){
			cout << board[i]<<board[i+1]<<board[i+2]<<endl;
			i+=3;
		}
	}
};

class User {
  int id;
  bool turn;
public:
  User(){turn = false;}
  void make_move(Game& current_game);
};

class Ai{
public:
	void make_move(Game& g);
	int minimax(Game g);
	Game hypothetical_move(Game g, int a){
		int i = g.get_turn();
		g.board[a] = i;
		g.change_turn();
		return g;
	}
	int maxvalue(Game g);
	int minvalue(Game g);
	int max(int i, int j);
	int min(int i, int j);

};

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

void User::make_move(Game& current_game){
	current_game.view_board();
	int move;
	cin >> move;

	while (move > 9 or move <1){
		cin >> move;
	cerr <<"Error: Invalid move location. Please select an integer between 1 and 9."<<endl;
}
	while (current_game.board[move-1] != 0){
		cerr << "Error: Player/AI has already played at selected position. Please select a valid move."<< endl;
		cin >> move;
	}
	current_game.board[move - 1] = -1;
	current_game.change_turn();
};

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

int Ai::maxvalue(Game g){
	if(g.is_game_over()) return g.who_won();
		vector<int> possible_moves = g.actions();
		int v = -1;
		for(int a=0; a <possible_moves.size();a++){
			v = max(v,minvalue(hypothetical_move(g,possible_moves[a])));
		}

	return v; 
}

int Ai::minvalue(Game g){
	if(g.is_game_over()) return g.who_won();
	vector<int> possible_moves = g.actions();
	int v = -1;
		for(int a=0; a < possible_moves.size();a++){
			v = min(v,maxvalue(hypothetical_move(g,possible_moves[a])));
		}
	return v; 
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
		util_val = maxvalue(hypothetical_move(g,possible_moves[i]));
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

int Game::who_won(){
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


return 0;
}

// int who_is_first(){int i = rand(); if (floor(rand/2) == rand/2) return 1; else return 2;}


void play_game(){

  User user1;
Ai comp;
  Game new_game;
 // int first_mover = who_is_first();
  while (! new_game.is_game_over()){
    // if (first_mover == 1){
      user1.make_move(new_game);
      if(new_game.is_game_over())
      	break;
      comp.make_move(new_game);
          // }
    // else {
    //   comp.make_move(new_game);
    //   user1.make_move(new_game);
    // }
  }
 
 int winner = new_game.who_won();

  if (winner == -1)
  {

  	cerr << "The Player Wins!"<<endl;
  	
  }
  else if (winner == 1)
  	cerr << "The computer wins!" << endl;

  else if (winner ==0)
  	cerr << "It was a Draw!"<< endl;
}

