#include "classes.cpp"
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

