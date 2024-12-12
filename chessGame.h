/**
 * @file chessGame.h
 * 
 * @brief Defines the chessGame class
 * 
 * This file contains the declaration of the `ChessGame` class, which handles 
 * the functionality and the state of the chessboard. It includes methods for
 * validating moves, checking the status of the game (e.g., check, checkmate, 
 * stalemate), and managing the chessboard's setup and manipulation. 
 * The class also provides functionality to load a chessboard from a valid FEN 
 * string.
 */


#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <iostream>
#include <utility>

#include "chessPiece.h"
#include "colour.h"
#include "king.h" 

/**
 * @brief Defines the `ChessGame` class.
 * 
 * The `ChessGame` class represents the core logic of a chess game. It handles 
 * the game state, including the chessboard setup, the management of moves, 
 * castling rights, and player turns. The class includes methods for 
 * validating moves, making moves, checking for check and checkmate, 
 * and handling special moves such as castling. It also provides functionality 
 * to load and reset the game state from a FEN string.
 */
class ChessGame {

public:

  ChessGame();
  
  /**
   * @brief Loads the chess game state from a FEN string.
   * 
   * This method parses the given FEN string to set up the chessboard and piece 
   * positions. It also assigns turn, castling rights, and other game 
   * parameters based on the FEN string.
   * 
   * @param fen The FEN string representing the chessboard's state.
   */
  void loadState(const char fen[]); 

  /**
   * @brief Submits a move to the game.
   * 
   * This method handles the logic of moving a piece from one position to 
   * another. It ensures that the move is legal and updates the game state 
   * accordingly.
   * 
   * @param initialPosition The position of the piece to move (e.g., "E2").
   * @param targetPosition The target position for the move (e.g., "E4").
   */
  void submitMove(const char initialPosition[3], const char targetPosition[3]);

  /**
   * @brief Destructor for the `ChessGame` class.
   * 
   * Cleans up resources associated with the `ChessGame` object.
   */
  virtual ~ChessGame();

private:

  /** 
   * @brief Resets the game to its initial state.
   * 
   * This method reinitializes the game, clearing the board and resetting 
   * all parameters. It is used both in the constructor and seperately.
   */
  void resetGame();

  /**
   * @brief Places a chess piece on the board based on the FEN character.
   * 
   * Given a FEN character, this method creates the appropriate piece and 
   * places it on the board at the corresponding location.
   * 
   * @param fen The FEN character representing the piece to place.
   * @return A pointer to the newly created `ChessPiece`.
   */
  ChessPiece * placePiece(const char fen);

  /**
   * @brief Assigns the turn of the game based on the FEN string.
   * 
   * This method determines which player's turn it is (white or black) by 
   * parsing the FEN string.
   * 
   * @param fen The FEN string containing the turn information.
   */
  void assignTurn(const char fen);

  /**
   * @brief Assigns the castling rights based on the FEN string.
   * 
   * This method updates the castling rights of both players based on the 
   * FEN string.
   * 
   * @param fen The FEN string containing the castling rights information.
   */

  void assignCastling(const char fen);

  /**
   * @brief Validates the input move.
   * 
   * This method checks if the given move is in a valid format (e.g., "E2").
   * 
   * @param move The move to validate.
   * 
   * @return `true` if the input move is valid, otherwise `false`.
   */
  bool validInput(const char move[3]);

  /**
   * @brief Checks if a move is legal.
   * 
   * This method determines whether a move is valid for the given piece, 
   * considering whether the target square is empty or occupied by an 
   * opponent's piece, if there are any pieces blocking the move on the board 
   * and if the moving piece has the attributes to make the move.
   * 
   * @param pieceMoved The piece being moved.
   * @param targetPiece The piece occupying the target square (if any).
   * @param row The row of the piece being moved.
   * @param col The column of the piece being moved.
   * @param targetRow The row of the target square.
   * @param targetCol The column of the target square.
   * @param pieceTaken Reference to a boolean indicating whether a piece is 
   *                   taken.
   * 
   * @return `true` if the move is legal, otherwise `false`.
   */
  bool isLegalMove(ChessPiece * pieceMoved, ChessPiece * targetPiece, 
		   const int row, const int col, const int targetRow, 
		   const int targetCol, bool & pieceTaken);



  /**
   * @brief Checks if castling is allowed for a given move.
   * 
   * This method checks whether castling is a legal move based on the position 
   * of the pieces, whether the king or rook have moved, and whether the s
   * quares are clear.
   * 
   * @param startRow The starting row of the piece.
   * @param startCol The starting column of the piece.
   * @param targetCol The target column of the move.
   * @param pieceTaken Indicates if a piece has been captured.
   * @param pieceMove The piece being moved.
   * @param direction The direction of the move (left or right).
   * 
   * @return `true` if castling is allowed, otherwise `false`.
   */
  bool canCastle(int startRow, int startCol, int targetCol, bool pieceTaken, 
		 ChessPiece * pieceMove, int & direction);

  /**
   * @brief Executes the castling move.
   * 
   * This method performs the actual movement of the king and rook during a 
   * castling move.
   * 
   * @param row The row of the king.
   * @param col The column of the king.
   * @param targetCol The target column of the castling move.
   * @param direction The direction of castling (left or right).
   * @param pieceMoved The piece being moved.
   */
  void castlingMove(int row, int col, int targetCol, int & direction, 
                    ChessPiece * pieceMoved);

  /**
   * @brief Updates the castling rights of the current player.
   * 
   * This method is called after a move is made to update the castling rights 
   * of the player. It disables castling rights for the current player if 
   * the king or rook has moved.
   * 
   * @param initialRowNumber The starting row of the piece that was moved.
   * @param initialColNumber The starting column of the piece that was moved.
   * @param pieceMoved A pointer to the piece that was moved.
   */
  void updateCastlingRights(int initialRowNumber, int initialColNumber,
                            ChessPiece* pieceMoved);

  /**
   * @brief Reverts the castling rights to their previous state.
   * 
   * This method is called when undoing a move, restoring the castling rights 
   * of the current player to their state prior to the move. It ensures that 
   * castling rights are accurately maintained after a move is undone.
   * 
   * @param initialRowNumber The starting row of the piece that was moved.
   * @param initialColNumber The starting column of the piece that was moved.
   * @param pieceMoved A pointer to the piece that was moved.
   */
  void revertCastlingRights(int initialRowNumber, int initialColNumber, 
			    ChessPiece* pieceMoved);
  
  /**
   * @brief Switches the turn between players.
   * 
   * This method changes the active player's turn 
   * (from white to black or vice versa).
   */
  void switchTurn();
   
  /**
   * @brief Checks if the path between two squares is clear of pieces.
   * 
   * This method checks whether there are any pieces blocking the path between
   * the initial and target positions of a move.
   * 
   * @param initialRowNumber The starting row.
   * @param initialColNumber The starting column.
   * @param targetRowNumber The target row.
   * @param targetColNumber The target column.
   * 
   * @return `true` if the path is clear, otherwise `false`.
   */
  bool isBoardClear(const int initialrownumber, const int initialColNumber, 
                    const int targetRowNumber, const int targetColNumber);

  /**
   * @brief Makes the move on the board.
   * 
   * This method updates the board state by moving a piece from one square to
   * another. It also handles the case where a piece is captured.
   * 
   * @param initialRowNumber The starting row.
   * @param initialColNumber The starting column.
   * @param targetRowNumber The target row.
   * @param targetColNumber The target column.
   * @param pieceMoved The piece being moved.
   */
  void makeMove(const int initialRowNumber, const int initialColNumber, 
                const int targetRowNumber, const int targetColNumber,  
                ChessPiece *pieceMoved);

  /**
   * @brief Undoes the last move.
   * 
   * This method restores the game to its state before the last move, reversing
   * any changes made to the board and castling rights.
   * 
   * @param initialRowNumber The starting row of the undone move.
   * @param initialColNumber The starting column of the undone move.
   * @param targetRowNumber The target row of the undone move.
   * @param targetColNumber The target column of the undone move.
   * @param pieceMoved The piece that was moved.
   * @param pieceTaken The piece that was taken, if any.
   */
  void undoMove(const int initialRowNumber, const int initialColNumber, 
                const int targetRowNumber, const int targetColNumber,  
                ChessPiece *pieceMoved, ChessPiece *pieceTaken);

  /** 
   * @brief Updates the king's position after a move.
   * 
   * This method updates the position of the king after it has moved.
   * 
   * @param king The king piece being moved.
   * @param newRow The new row for the king.
   * @param newCol The new column for the king.
   */
  void updateKingPosition(const King* king, const int newRow, 
                          const int newCol);

  /**
   * @brief Checks if the current player is in check.
   * 
   * This method determines if the current player has their king in check.
   * 
   * @return `true` if the current player is in check, otherwise `false`.
   */
  bool inCheck();

  /**
   * @brief Checks if the game is in a checkmate state.
   * 
   * This method determines if the current player is in checkmate.
   * 
   * @return `true` if the current player is in checkmate, otherwise `false`.
   */
  bool isCheckmate();

  /**
   * @brief Checks if the game is in a stalemate state.
   * 
   * This method determines if the current player is in stalemate.
   * 
   * @return `true` if the current player is in stalemate, otherwise `false`.
   */
  bool isStalemate();
  
  // Indicates whether a reset of the game is required.
  bool resetRequired;

  // Indicates whether the game is over.
  bool gameOver;

  // The current active player's colour (white or black).
  Colour activeColour;

  // The 8x8 chessboard.
  ChessPiece * chessBoard[8][8]; 

  // The position of the white king.
  std::pair<int, int> whiteKingPosition;

  // The position of the black king
  std::pair<int, int> blackKingPosition;

  // Castling rights for the white player.
  std::pair<bool, bool> whiteCastlingRights;

  // Castling rights for the black player
  std::pair<bool, bool> blackCastlingRights; 
};


#endif
