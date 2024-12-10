//check the order.
#include <iostream>
#include <utility>
#ifndef CHESSGAME_H
#define CHESSGAME_H
#include "chessPiece.h"
#include "colour.h"
#include "king.h" 



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

  void resetGame();

  void assignTurn(const char fen);

  void assignCastling(const char fen);

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

  bool doesGameNeedToBeReset;  // Flag to track if the game needs to be reset

  bool resetRequired;

  Colour activeColour;

  ChessPiece * placePiece(const char fen);

  ChessPiece * chessBoard[8][8]; 

  std::pair<int, int> whiteKingPosition;

  std::pair<int, int> blackKingPosition;

  std::pair<bool, bool> whiteCastling;

  std::pair<bool, bool> blackCastling; 



 

  // bool GameOver
  /* this funciton changes from yes to no when a new game is loaded. It changes from no to yes when checkmate occurs
    then there is a check in submit move like ("Game over...shake hands with your opponent and accept defeat")
  */

  /*
  std::pair<bool, bool> blackCastling; //may need to move this. Does this need to be its own
			  //class etc. 
  std::pair<bool, bool> whiteCastling;

  G
  */
};


#endif
