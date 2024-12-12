/**
 * @file chessGame.h
 * 
 * @brief Defines the chessGame class
 * 
 * This file contains the declaration of the chessGame class for handling the 
 * functionality and the knolwedge of the board. This include validating moves
 * as being valid or not as well as the state of the game such as whether 
 * a piece has been taken, whether a player is in check, checkmate or 
 * stalemate. The file also sets up the game, allowing the user to load a 
 * chess board in the form of a valid fen string. 
 */

#ifndef CHESSGAME_H
#define CHESSGAME_H
#include <iostream>
#include <utility>

#include "chessPiece.h"
#include "colour.h"
#include "king.h" 


class ChessGame {

 public:

  ChessGame();
  
  void loadState(const char fen[]); 

  void submitMove(const char initialPosition[3], const char targetPosition[3]);

  virtual ~ChessGame();

 private:

  void resetGame();

  ChessPiece * placePiece(const char fen);

  void assignTurn(const char fen);

  void assignCastling(const char fen);

  bool isLegalMove(ChessPiece * pieceMoved, ChessPiece * targetPiece, 
                  const int row, const int col, const int targetRow, 
                  const int targetCol, bool & pieceTaken);

  bool validInput(const char move[3]);

  bool canCastle(int startRow, int startCol, int targetCol, bool pieceTaken, 
                ChessPiece * pieceMove, int & direction);

  void castlingMove(int row, int col, int targetCol, int & direction, 
                    ChessPiece * pieceMoved);
  
  bool inCheck();

  void switchTurn();

  bool isBoardClear(const int initialrownumber, const int initialColNumber, 
                    const int targetRowNumber, const int targetColNumber);

  void makeMove(const int initialRowNumber, const int initialColNumber, 
                const int targetRowNumber, const int targetColNumber,  
                ChessPiece *pieceMoved);

  void undoMove(const int initialRowNumber, const int initialColNumber, 
                const int targetRowNumber, const int targetColNumber,  
                ChessPiece *pieceMoved, ChessPiece *pieceTaken);

  void updateKingPosition(const King* king, const int newRow, 
                          const int newCol);

  bool isCheckmate();

  bool isStalemate();

  bool resetRequired;

  void updateCastlingRights(int initialRowNumber, int initialColNumber,
                            ChessPiece* pieceMoved);

  void revertCastlingRights(int initialRowNumber, int initialColNumber, 
                                                ChessPiece* pieceMoved);
  
  bool gameOver;

  Colour activeColour;

  ChessPiece * chessBoard[8][8]; 

  std::pair<int, int> whiteKingPosition;

  std::pair<int, int> blackKingPosition;

  std::pair<bool, bool> whiteCastlingRights;

  std::pair<bool, bool> blackCastlingRights; 
};


#endif
