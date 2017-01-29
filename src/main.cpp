#include "classes.cpp"
#include "play_game.cpp"
using namespace std;

int main(){
int winner =  play_game();
 if (winner == 1)
   cerr << "Congratulations! You've won.";
   else if (winner == 2)
     cerr << "Sorry, you've been beaten by the AI.";
  return 0;
}
