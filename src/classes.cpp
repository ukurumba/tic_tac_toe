#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


class User {
  int id;
  bool turn;
public:
  User(){turn = false;}
  void make_move(Game& current_game);
};

class Ai{};
class Game{

public:
	int board[9];
	Game(){for (int i=0;i<9;i++)
		{board[i] = 0;};}
	};


void User::make_move(Game& current_game){
	int move;
	cin >> move;

	while (type(move) != int) {
		cerr << "Error: Please input an integer." << endl;
		cin >> move;
	}
	while (move > 9 or move <1){
		cin >> move;
	cerr <<"Error: Invalid move location. Please select an integer between 1 and 9."<<endl;}
	while (current_game.board[move] != 0){
		cerr << "Error: Player/AI has already played at selected position. Please select a valid move."<< endl;
		cin >> move;
	}
	current_game.board[move - 1] = 1;
}

