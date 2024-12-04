
#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "chessPiece.h"

enum class Castling {NONE, QUEENSIDE, KINGSIDE, BOTH};
/*feel bitwise operator or something would work better. do I change it to "-, Q,
  K, QK" as it does in FEN*/

class ChessGame {

 public:

  ChessGame();
  
  void loadState(const char fen[]); //simliar initialisatin to sudoku (i.e. its a char array

  void submitMove();

  // support function for personal use (Delete later!)
  friend ostream& operator<< (ostream &out, const ChessGame cg) // refer to safe
								// array example

 private:
  ChessPiece * chessBoard[8][8];
  bool isWhitesTurn; // !isWhitesTurn to change to black turn
  Castling blackCastling; //may need to move this. Does this need to be its own
			  //class etc. 
  Castling whiteCastling;
};


#endif
