#include "./classes.cpp"
void play_game(){

  User user1;
  Ai comp;
  Game new_game;
  int turn = 1;
  // int first_mover = who_is_first();
  while (! new_game.is_game_over()){
    // if (first_mover == 1){
    user1.make_move(new_game);
    turn = 1;
    if(new_game.is_game_over())
      break;
    comp.make_move(new_game);
    turn = 2;
    // }
    // else {
    //   comp.make_move(new_game);
    //   user1.make_move(new_game);
    // }
  }
  if (turn == 1)
    {

  cerr << "The Player Wins!"<<endl;
  
}
  else if (turn == 2)
    cerr << "The computer wins!" << endl;
}#include "classes.cpp"
void play_game(){

  User user1;
  Ai comp;
 int first_mover = who_is_first();
  while (! is_game_over()){
    if (first_mover == 0){
      user1.make_move();
      comp.make_move();
    }
    else {
      comp.make_move();
      user1.make_move();
    }

  }

