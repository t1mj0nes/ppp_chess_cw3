//check the order.
#include <iostream>
#include <utility>
#ifndef CHESSGAME_H
#define CHESSGAME_H
#include "chessPiece.h"
#include "king.h" //add to makefile



// enum class Castling {NONE, QUEENSIDE, KINGSIDE, BOTH};
/*feel bitwise operator or something would work better. do I change it to "-, Q,
  K, QK" as it does in FEN*/

/**
 * @enum colour.
 * @brief Represents the possible colors of a traffic light.
 *
 */
enum class Turn {BLACK, WHITE};

std::ostream& operator<< ( std::ostream &out, const Turn& turn);


class ChessGame {

 public:

  ChessGame();
  
  void loadState(const char fen[]); //simliar initialisatin to sudoku (i.e. its a char array

  void submitMove(const char initialPosition[], const char targetPosition[]);


  // support function for personal use (Delete later!)
  friend std::ostream& operator<< ( std::ostream &out, const ChessGame* cg); // refer to safe

  virtual ~ChessGame();

 private:
//order these alphabettically or as they are used?

// what is this used for? srename?
  void assignKing(const char fen, const int &rowPosition, const int &colPosition);

  void assignTurn(const char fen);
  
  bool isLegalMove(ChessPiece * pieceMoved, ChessPiece * targetPiece, const int row, const int col, const int targetRow, const int targetCol, bool & pieceTaken);
  
  bool inCheck();

  void switchTurn();

  bool isBoardClear(const int initialrownumber, const int initialColNumber, const int targetRowNumber, const int targetColNumber);

  void makeMove(const int initialRowNumber, const int initialColNumber, const int targetRowNumber, const int targetColNumber,  ChessPiece *pieceMoved);

  void undoMove(const int initialRowNumber, const int initialColNumber, const int targetRowNumber, const int targetColNumber,  ChessPiece *pieceMoved, ChessPiece *pieceTaken);

//CHECK THIS IS FINE
  void updateKingPosition(const King* king, const int newRow, const int newCol);

  bool isCheckmate();

  bool isStalemate();

  ChessPiece * placePiece(const char fen);

  ChessPiece * chessBoard[8][8]; //temporarily made it a char array


  Turn  playerToMove;
  std::pair<int, int> whiteKingPosition;
  std::pair<int, int> blackKingPosition;
 

  // bool GameOver
  /* this funciton changes from yes to no when a new game is loaded. It changes from no to yes when checkmate occurs
    then there is a check in submit move like ("Game over...shake hands with your opponent and accept defeat")
  */

  /*
  Castling blackCastling; //may need to move this. Does this need to be its own
			  //class etc. 
  Castling whiteCastling;

  G
  */
};


#endif
