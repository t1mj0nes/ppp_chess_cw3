#include <iostream>
#ifndef CHESSGAME_H
#define CHESSGAME_H
#include "chessPiece.h"

// enum class Castling {NONE, QUEENSIDE, KINGSIDE, BOTH};
/*feel bitwise operator or something would work better. do I change it to "-, Q,
  K, QK" as it does in FEN*/


/**
 * @enum colour.
 * @brief Represents the possible colors of a traffic light.
 *
 */
enum class Turn {BLACK, WHITE};


class ChessGame {

 public:

  ChessGame();
  
  void loadState(const char fen[]); //simliar initialisatin to sudoku (i.e. its a char array

  void submitMove(const char whiteMove[], const char blackMove[]);

  // support function for personal use (Delete later!)
  friend std::ostream& operator<< ( std::ostream &out, const ChessGame* cg); // refer to safe
								// array example
  //does this need to be a pointer to ChesGame 

 private:

  void assignTurn(const char fen);

  ChessPiece * placePiece(const char fen);
  
  ChessPiece * chessBoard[8][8]; //temporarily made it a char array
  Turn  playerToMove;

  /*
  Castling blackCastling; //may need to move this. Does this need to be its own
			  //class etc. 
  Castling whiteCastling;
  */
};


#endif
