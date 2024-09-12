#include <iostream>
#include <vector>
using namespace std;

class ConnectFour{

  public:
  vector<vector<int>> grid;
  bool firstPlayer;

  ConnectFour(){
    grid.resize(6, vector<int> (7, 0));
    firstPlayer = true;
  }

  void dropToken(int column){
    if(column < 0 or column >= (int) grid[0].size()){
      cout << "Invalid column drop at " << column << endl;
      return ;
    }

    cout << "Dropping token at " << column << " for player " << (firstPlayer ? 1 : 2) << endl;

    for(int i = (int) grid.size()-1; i >= 0; i--){
      if(grid[i][column] == 0){
        grid[i][column] = (firstPlayer ? 1 : 2);
        break;
      }
    }

    checkIfWinnerExists();

    firstPlayer = !firstPlayer;
  }

  void checkIfWinnerExists(){

    for(int i = 0; i < 6; i++){
      for(int j = 0; j < 7; j++){
        cout << grid[i][j] << " " ;
      } cout << endl;
    }

    // row-wise

    int winner = -1;
    for(int i = 0; i < (int) grid.size(); i++){
      for(int j = 0; j <= (int) grid[i].size()-4; j++){
        if(grid[i][j] != 0 and grid[i][j] == grid[i][j+1] and grid[i][j] == grid[i][j+2] 
            and grid[i][j] == grid[i][j+3]){
          winner = grid[i][j];
          break;
        }
      }
    }

    if(winner != -1){ 
      cout << "Player " << winner << " has won!" << endl;
      return;
    }
    
    // col-wise
    for(int j = 0; j < (int) grid[0].size(); j++){
      for(int i = 0; i <= (int) grid.size()-4; i++){
        if(grid[i][j] != 0 and grid[i][j] == grid[i+1][j] and grid[i][j] == grid[i+2][j] 
            and grid[i][j] == grid[i+3][j]){
          winner = grid[i][j];
          break;
        }
      }
    }

    if(winner != -1){ 
      cout << "Player " << winner << " has won!" << endl;
      return;
    }

    // diagonal wise - forward
    for(int i = 0; i < (int) grid.size()-3; i++){
      for(int j = 0; j < (int) grid[i].size()-3; j++){
        if(grid[i][j] != 0 and grid[i][j] == grid[i+1][j+1] 
            and grid[i][j] == grid[i+2][j+2] 
            and grid[i][j] == grid[i+3][j+3]){
          winner = grid[i][j];
          break;
        }
      }
    }

    if(winner != -1){ 
      cout << "Player " << winner << " has won!" << endl;
      return;
    }

    // diagonal wise - backward
    for(int i = 0; i < (int) grid.size()-3; i++){
      for(int j = 3; j < (int) grid[i].size(); j++){
        if(grid[i][j] != 0 and grid[i][j] == grid[i+1][j-1] and grid[i][j] == grid[i+2][j-2] 
            and grid[i][j] == grid[i+3][j-3]){
          winner = grid[i][j];
          break;
        }
      }
    }

    if(winner != -1){ 
      cout << "Player " << winner << " has won!" << endl;
      return;
    }

  }
};

// To execute C++, please define "int main()"
int main() {
  ConnectFour* myGame = new ConnectFour();

  // myGame->dropToken(0);

  // // invalid
  // myGame->dropToken(-1);
  // myGame->dropToken(9);

  // myGame->dropToken(1);
  // myGame->dropToken(0);
  // myGame->dropToken(2);
  // myGame->dropToken(0);
  // myGame->dropToken(3);
  // myGame->dropToken(0);   // --> expecting player 1 to win.
  // // myGame->dropToken(4);

  myGame->dropToken(1);
  myGame->dropToken(2);
  myGame->dropToken(2);
  myGame->dropToken(3);
  myGame->dropToken(3);
  myGame->dropToken(4);
  myGame->dropToken(3);
  myGame->dropToken(4);
  myGame->dropToken(4);
  myGame->dropToken(6);
  myGame->dropToken(4);

  return 0;
}


// Your previous Plain Text content is preserved below:

// # Connect Four

// ## Problem
// Design a program that allows playing the game of Connect Four. 

// Connect Four is a game where two players take turns dropping colored tokens into a seven column six row grid. If one 
// player's tokens form a line that is four long, that player wins. Lines can be horizontal, vertical, or diagonal.

// Write a program that has a function `dropToken(column)` and prints the board after each token drop. When a token drop
// results in a player winning, print `Player X has won!`.

// ## Examples

// At the start of the game the board is empty,

// 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0

// After executing dropToken(0) the first token is displayed,

// 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0
// 1 0 0 0 0 0 0

// If dropToken(0) is called again, player two's token is placed on top of player one's.

// 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0
// 2 0 0 0 0 0 0
// 1 0 0 0 0 0 0

// On player one's second turn they call dropToken(1)

// 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0
// 2 0 0 0 0 0 0
// 1 1 0 0 0 0 0