/**
 * @file chessGame.cpp
 * 
 * @brief Implements the chessGame class
 * 
 * This file contains the implementation for handling the chessGame and the 
 * corresponding outputs. 
 */

#include <iostream>
#include <cstring>
#include <cctype>
#include "chessGame.h"
#include "chessPiece.h" 
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h" 
#include "queen.h"
#include "rook.h"
#include "colour.h"


using namespace std;

//chessGame Constructor.
ChessGame::ChessGame() {
  //resetGame does the heavy lifting.
  resetGame();
}


void ChessGame::resetGame() {
  //new game, therefore it has not finished.
  gameOver = false;


  //set king default position to not on the board
  whiteKingPosition = {-1, -1};
  blackKingPosition = {-1, -1};

  // set default to castling to not being allowed
  whiteCastlingRights = {false, false};
  blackCastlingRights = {false, false};


  //default is that white starts
  activeColour = Colour::WHITE;

  // set the board to be empty
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      chessBoard[i][j] = nullptr;
    }
  }

  resetRequired = false;
}

//loads the fen string into the chessGame
void ChessGame::loadState(const char fen[]) {
  //checking if the board has been just been initialised
  if(resetRequired)
    {
      resetGame();
    }


  // Flags provide a signa  between the fen string  and game state elements.
  enum class FenState{PIECE_PLACEMENT, ACTIVE_COLOUR, CASTLING};
  FenState currentState = FenState::PIECE_PLACEMENT;
  //  n is the position within the fen string.
  int n = 0;

  //loading in a board from blacks perspective. A1 is top right corner.  
  int rowCounter = 7;
  int colCounter = 7;

  //continue until your reach the end of the fen string. 
  while (fen[n] != '\0') {
    switch (currentState) {
      case FenState::PIECE_PLACEMENT:{
	  // check if a letter 
	  if(isalpha(fen[n])) {
	    chessBoard[rowCounter][colCounter] = placePiece(fen[n]);
	    if ((fen[n] == 'K') || (fen[n] == 'k')) {
	      // King position is stored for improved efficiency for 'check'.
	      updateKingPosition(static_cast<King*>
				 (chessBoard[rowCounter][colCounter]), 
				 rowCounter, colCounter);
	    }
	    // move across the board for the next piece
	    colCounter--;
          }
	  //if number, empty spaces equating to the value of the number
	  else if (isdigit(fen[n])) {
	    int no_empty_space = fen[n] - '0';
	    for(int k = 0; k < no_empty_space; k++) {
	      // empty spaces are ignored and kept as null pointers.
	      colCounter--;
	    }
          }
	  else if (fen[n] == '/') {
	    rowCounter--;
	    //reset column counter as we are moving to a knew row.
	    colCounter = 7;
          }
	  else if (fen[n] == ' ')  {
	    currentState = FenState::ACTIVE_COLOUR;
          }
	  n++;
	  break;
      }
    case FenState::ACTIVE_COLOUR: {
      if (isalpha(fen[n])) {
	assignTurn(fen[n]);
      }
      if (fen[n] == ' ') {
	currentState=FenState::CASTLING;
      }
      n++;
      break; 
    }
    case FenState::CASTLING:{
        assignCastling(fen[n]);
        n++;
        break; 
      }
    }
  }

  //a fresh game state has been loaded so any new game will require reseting. 
  resetRequired = true;

  cout << "A new board state is loaded!" << endl;

}

ChessPiece * ChessGame:: placePiece(const char fen) {
  //uppercase letters are white pieces, lowercase are black
  Colour pieceColour = isupper(fen) ? Colour::WHITE : Colour::BLACK;
  
  ChessPiece * new_piece = nullptr;

  switch(toupper(fen)){
  case 'R':
    new_piece = new Rook(pieceColour);
    break;
  case 'N':
    new_piece = new Knight(pieceColour);
    break;
  case 'B':
    new_piece = new Bishop(pieceColour);
    break;
  case 'Q':
    new_piece = new Queen(pieceColour);
    break;
  case 'K':
    new_piece = new King(pieceColour);
    break;
  case 'P':
    new_piece = new Pawn(pieceColour);
    break;
  }
  return new_piece;
}

void ChessGame::assignTurn(const char fen) {
  if (fen == 'w')
    activeColour = Colour::WHITE;
  else if (fen == 'b')
    activeColour = Colour::BLACK;
}

void ChessGame::assignCastling(const char fen) {
  // Reset castling rights by default if '-' is encountered
  if (fen == '-') {
    whiteCastlingRights = {false, false};
    blackCastlingRights = {false, false};
  }
  else if (isalpha(fen)) {
    switch (fen) {
    case 'K':
      // kingside castling
      whiteCastlingRights.first = true; 
      break;
    case 'Q':
      //queenside castling
      whiteCastlingRights.second = true; 
      break;
    case 'k':
      blackCastlingRights.first = true; 
      break;
    case 'q':
      blackCastlingRights.second = true; 
      break;
    }
  }
  else {
    // If the character is not recognised, reset to no castling rights
    whiteCastlingRights = {false, false};
    blackCastlingRights = {false, false};
  }
}


void ChessGame::submitMove( const char initialPosition[3], 
                            const char targetPosition[3]) {
  if (gameOver == true) {

    cout << "error, game over. Please load in a new game." << endl;
    return;
  }

  if(!validInput(initialPosition) || !validInput(targetPosition)) {
    cout << "Error: provide a valid position on a chess board" << endl;
    return;
  }

  // converting the moves into the corresponding board positions. 
  int initialRowNumber = initialPosition[1] - '0' - 1;
  int initialColNumber = 7 - (initialPosition[0] - 'A');
  int targetRowNumber = targetPosition[1] - '0' - 1;
  int targetColNumber = 7 - (targetPosition[0] - 'A');
  bool isCapture = false;
  
  ChessPiece* movingPiece = chessBoard[initialRowNumber][initialColNumber];
  ChessPiece * targetPiece = chessBoard[targetRowNumber][targetColNumber];

  // check if there is a piece there.
  if (movingPiece== nullptr) {
    cout << "There is no piece at position " << initialPosition
	 << "!" << endl;
    return;
  }
  // check if trying to move a piece of the wrong turn - reword
  else if (movingPiece->getPieceColour() != activeColour) {
    cout << "It is not " << movingPiece->getPieceColour()
	 << "'s turn to move!" <<endl;
    return;
  } 
  //check if it is a legal move.
  if (isLegalMove(movingPiece, targetPiece, initialRowNumber, 
		  initialColNumber, targetRowNumber, targetColNumber,
		  isCapture)) {
    cout << activeColour << "'s " << movingPiece->getPieceName() 
	 << " moves from " << initialPosition << " to " << targetPosition;
    if (isCapture) {
      // add extra print statement for when a capture occurs.
      Colour capturedPieceColour = getOppositeColour(activeColour);
      cout << " taking " << capturedPieceColour << "'s " 
	   << targetPiece->getPieceName();
      delete targetPiece; // Remove the captured piece from memory
    }
    cout << endl;

    switchTurn();
  }
  else {
    cout << activeColour << "'s " << movingPiece->getPieceName() 
	 << " cannot move from " << initialPosition << " to " 
	 << targetPosition << "!" << endl;
    return;
  }

  //check check of opponent
  bool isIncheck = inCheck();
  if (isIncheck){
    if(isCheckmate()){
      cout << activeColour << " is in checkmate" << endl;
      gameOver = true;
    }
    else { 
      cout << activeColour << " is in check" << endl;
    }
  } 
  else {
    if(isStalemate()) {
      cout << "Stalemate! Match drawn" << endl;
      gameOver = true;
    }
  }
  return;
}

/**
 * function to confirm the inputs into the submitMove method are valid
 */
bool ChessGame::validInput(const char move[3]) {
  //check there aren't more than 2 characters
  if (move[2] != '\0') {
    return false;
  }
  //Check first character is a vliad column letter (A-H)
  if (move[0] < 'A' || move[0] > 'H') {
    return false;
  }

  // Check if the second character is a valid row number (1-8)
  if (move[1] < '1' || move[1] > '8') {
    return false;
  }

  return true;
}


bool ChessGame::isLegalMove(ChessPiece * pieceMoved, ChessPiece * targetPiece, 
                            const int row, const int col, const int targetRow, 
                            const int targetCol, bool & pieceTaken){
  if (chessBoard[targetRow][targetCol] != nullptr) {
    pieceTaken = true;
  }
  else {
    pieceTaken =false;
  }
  // check if the piece taken is the same as the piece being moved.
  if ((pieceTaken == true) &&
      ((pieceMoved->getPieceColour())
       == (chessBoard[targetRow][targetCol]->getPieceColour()))) {
    return false;
  }

  // checking if any piece on the board is able to compete the move.
  if (pieceMoved->isValidPieceMove(row, col, targetRow, targetCol, pieceTaken))
    {

      // checking if castling is occuring
      if ((dynamic_cast<King*>(pieceMoved)) && (abs(targetCol - col) == 2)){
	int direction;
	if (!canCastle(row, col, targetCol, pieceTaken, pieceMoved, direction)){
	  // if castling can't occur it is an invalid move
	  return false;
	}
	// if castling can occur, execute the move
	castlingMove(row, col, targetCol, direction, pieceMoved);
	return true;
      }

      // check for all other pieces
      if (!isBoardClear(row, col, targetRow, targetCol)) {
        // check board is clear between the piece start and target position.
        return false;
      }

      // piece is able to move so make the move
      makeMove(row, col, targetRow, targetCol, pieceMoved);

      //now check if the move leaves the king in check.
      if(inCheck()) {
        //undo the move if invalid
        undoMove(row, col, targetRow, targetCol,  pieceMoved, targetPiece);
        return false;
      }
      return true;
    }

  return false;
}

bool ChessGame::isBoardClear(const int initialRowNumber,
			     const int initialColNumber,
			     const int targetRowNumber,
			     const int targetColNumber) {
  
  // If piece is a knight, check is irrelevant as knights can fly. 
  if (dynamic_cast<Knight*>(chessBoard[initialRowNumber][initialColNumber])){
    return true;
  }

  int rowDiff = (targetRowNumber - initialRowNumber);
  int colDiff = (targetColNumber - initialColNumber);

  int rowStep = (rowDiff > 0) ? 1 : -1;
  int colStep = (colDiff > 0) ? 1 : -1;
  // checking if horizontal route is clear
  if (rowDiff == 0) {
    for (int column = initialColNumber + colStep; column !=
	   targetColNumber; column += colStep){
      if (chessBoard[targetRowNumber][column] != nullptr){
        return false;
      }
    }
    // no obstruction was found, return true.
    return true;
  }
  //checking if vertical path is clear
  else if (colDiff == 0) {
    for (int row = initialRowNumber + rowStep; row != targetRowNumber;
	 row += rowStep){
      if (chessBoard[row][targetColNumber] != nullptr){
        return false;
      }
    }
    //no obstruction was found, return true
    return true;
  }
  //checking if diagonal route is clear.
  else if (abs(rowDiff/colDiff) == 1) {
    int row = initialRowNumber + rowStep;
    int column = initialColNumber + colStep;
    while (row != targetRowNumber && column != targetColNumber) {
      if (chessBoard[row][column] != nullptr){
	return false;
      }
      row = row + rowStep;
      column = column + colStep;
    }
  }
  return true;
}

bool ChessGame::canCastle(int startRow, int startCol, int targetCol, 
                          bool pieceTaken, ChessPiece * pieceMoved, 
                          int & direction) {
  //boolean returns true if a queenside castling is occuring.
  bool castlingQueenSide;

  if(pieceTaken){
    // you can't take a piece while trying to castle
    return false;
  }

  // queenside when the target colum is less then the kings starting position.
  castlingQueenSide = (startCol > targetCol);
  
  // determine which colour is castling.
  std::pair<bool, bool>& colourCastling = 
    (activeColour == Colour::WHITE) ? whiteCastlingRights : blackCastlingRights;

  //check if the king or rook has already moved.
  if (castlingQueenSide) {
    if (!colourCastling.second) {
      // Queenside castling not allowed
      return false; 
    }
  }
  else {
    if (!colourCastling.first) {
      // Kingside castling not allowed
      return false; 
    }
  }

  // Determine the rook's expected position
  int rookCol = castlingQueenSide ? 0 : 7;

  // Verify the piece at the rook's position is a rook of the same colour
  ChessPiece* rook = chessBoard[startRow][rookCol];
  if (!rook || !dynamic_cast<Rook*>(rook) || 
      rook->getPieceColour() != activeColour) {
    return false;
  }
  
  //Check if all squares between the king and rook are clear
  if(!isBoardClear(startRow, startCol, startRow, rookCol)) {
      return false;
    }

  // check if the king is in check in its current position
  if(inCheck()) {
    return false;
  }
  
  //if castlingQueenSide Kings column position is decrimenting.
  direction = (castlingQueenSide) ? -1 : 1;


  // move thorugh the start column until it is not in the final position
  for (int position = startCol + direction; position != targetCol + direction; 
       position += direction) {
    makeMove(startRow, startCol, startRow, position, pieceMoved);
    if (inCheck()) {
      //undo the move if invalid
      undoMove(startRow, startCol, startRow,  position, pieceMoved, 
	       nullptr);
      return false;
    }
    // revert back to the starting state of the board.
    undoMove(startRow, startCol, startRow,  position, pieceMoved, nullptr);
  }

  return true;
}  

void ChessGame::makeMove(const int initialRowNumber, 
			 const int initialColNumber, const int targetRowNumber,
			 const int targetColNumber, ChessPiece * pieceMoved) {
  
  chessBoard[targetRowNumber][targetColNumber] = pieceMoved;
  chessBoard[initialRowNumber][initialColNumber] = nullptr;

  // Have to update kings position and the castling rights
  if(dynamic_cast<King*>(pieceMoved)) {
    updateKingPosition(dynamic_cast<King*>(pieceMoved), targetRowNumber, 
		       targetColNumber);
    updateCastlingRights(initialRowNumber, initialColNumber, pieceMoved);
  }
  else if(dynamic_cast<Rook*>(pieceMoved) ) {
    updateCastlingRights(initialRowNumber, initialColNumber, pieceMoved);
  }
      
}

void ChessGame::updateCastlingRights(int initialRowNumber, 
				     int initialColNumber, 
				     ChessPiece* pieceMoved)
{
  // Use activeColour to determine which colour's castling rights to update
  std::pair<bool, bool>& colourCastling = 
    (activeColour == Colour::WHITE) ? whiteCastlingRights : blackCastlingRights;

  // If it's a Rook, increment the move counter
  if (Rook* rook = dynamic_cast<Rook*>(pieceMoved)) {
    rook->incrementCounter();

    // Update castling rights based on the rook's position
    if (initialColNumber == 7) { // Kingside rook
      colourCastling.second = false;  // No castling on this side anymore
    }
    else if (initialColNumber == 0) { // Queenside rook
      colourCastling.first = false;   // No castling on this side anymore
    }
  }

  // If it's a King, revoke castling rights
  else if (dynamic_cast<King*>(pieceMoved)) {
    colourCastling.first = false;  // Revoke queenside castling
    colourCastling.second = false; // Revoke kingside castling
  }
}



void ChessGame::undoMove(const int initialRowNumber, 
                         const int initialColNumber, const int targetRowNumber, 
                         const int targetColNumber,  ChessPiece *pieceMoved, 
                         ChessPiece *pieceTaken){
  
  chessBoard[initialRowNumber][initialColNumber] = pieceMoved;
  chessBoard[targetRowNumber][targetColNumber] = pieceTaken;
  // Have to update kings position and the castling rights
  if (dynamic_cast<King*>(pieceMoved)) {
    updateKingPosition(dynamic_cast<King*>(pieceMoved), initialRowNumber, 
		       initialColNumber);
    revertCastlingRights(initialRowNumber, initialColNumber, pieceMoved);
  }
  else if (dynamic_cast<Rook*>(pieceMoved)) {
    revertCastlingRights(initialRowNumber, initialColNumber, pieceMoved);
  }
}

void ChessGame::revertCastlingRights(int initialRowNumber, 
				     int initialColNumber, 
				     ChessPiece* pieceMoved) {
  // Use activeColour to determine which colour's castling rights to update
  std::pair<bool, bool>& colourCastling = 
    (activeColour == Colour::WHITE) ? whiteCastlingRights : blackCastlingRights;

  // If it is a Rook, decrement the move counter, as undoing a move.
  if (Rook* rook = dynamic_cast<Rook*>(pieceMoved)) {
    rook->decrementCounter();

    // If the rook hasn't moved yet, restore castling rights for that side
    if (rook->getMoves() == 0) {
      // Kingside rook
      if (initialColNumber == 7) { 
	// Re-enable kingside castling
	colourCastling.second = true; 
	// Queenside rook 
      } else if (initialColNumber == 0) { 
	// Re-enable queenside castling
	colourCastling.first = true; 
      }
    }
  }
  // If it's a King, check for the movement of the rooks
  else if (dynamic_cast<King*>(pieceMoved)) {
    // Check if the rooks have moved 
    bool kingsideRookNotMoved = false;

    bool queensideRookNotMoved = false;

    // Check the kingside rook (col 7)
    if (Rook* kingsideRook = 
	dynamic_cast<Rook*>(chessBoard[initialRowNumber][7])) {
      if (kingsideRook->getMoves() == 0) {
	kingsideRookNotMoved = true;
      }
    }

    // Check the queenside rook (col 0)
    if (Rook* queensideRook = 
	dynamic_cast<Rook*>(chessBoard[initialRowNumber][0])) {
      if (queensideRook->getMoves() == 0) {
	queensideRookNotMoved = true;
      }
    }

    // Revert castling rights based on rook movement
    colourCastling.first = kingsideRookNotMoved; 
    colourCastling.second = queensideRookNotMoved;

  }
}



void ChessGame::castlingMove(int row, int col, int targetCol, 
			     int & direction, ChessPiece * pieceMoved) {

  // move king
  makeMove(row, col, row, targetCol, pieceMoved);
    
  // Determine rook's target column
  int rookStartCol = (direction == 1) ? 7 : 0; 
  int rookTargetCol = targetCol - direction; 
  
  ChessPiece * rookCastling = chessBoard[row][rookStartCol];
  // move the rook
  makeMove(row, rookStartCol, row, rookTargetCol, rookCastling);

}


void ChessGame::updateKingPosition(const King* king, const int newRow, 
				   const int newCol) {
  if (king->getPieceColour() == Colour::WHITE) {
    whiteKingPosition.first = newRow;
    whiteKingPosition.second = newCol;
  }
  else {
    blackKingPosition.first = newRow;
    blackKingPosition.second = newCol;
  }
}

bool ChessGame::inCheck() {
  Colour opponentColour = 
    (activeColour == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;

  // Get the position of the current player's King
  int kingRow, kingCol;
  if (activeColour == Colour::WHITE) {
    kingRow = whiteKingPosition.first;
    kingCol = whiteKingPosition.second;
  } 
  else {
    kingRow = blackKingPosition.first;
    kingCol =  blackKingPosition.second;
  }

  // If the King's position is invalid, return false 
  if (kingRow == -1 || kingCol == -1) {
    cout << "error " << activeColour 
	 << "'s king is not on the baord" << endl;
    return false;
  }

  // Now check if any opponent pieces can attack the current player's King
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      ChessPiece* piece = chessBoard[row][col];
      // search for pieces of the oppents colour
      if (piece != nullptr && piece->getPieceColour() == opponentColour) {
	// Check if this piece can attack the current player's King
	if (piece->isValidPieceMove(row, col, kingRow, kingCol, true)) {
                
	  // Check if the path is clear
	  if (isBoardClear(row, col, kingRow, kingCol)) {
	    // in check
	    return true; 
	  }
	}
      }
    }
  }
  // not in check
  return false; 
}

bool ChessGame::isCheckmate(){

  // Try every possible move for the player in check
  for (int row = 0; row < 8; ++row) {
    for (int col = 0; col < 8; ++col) {
      // Look for pieces of the same colour as the king
      if (chessBoard[row][col] && 
	  chessBoard[row][col]->getPieceColour() == activeColour) {
	// Try moving this piece to every square
	for (int targetRow = 0; targetRow < 8; ++targetRow) {
	  for (int targetCol = 0; targetCol < 8; ++targetCol) {
	    // Check if this move is legal and resolves the check
	    ChessPiece* originalTarget 
	      = chessBoard[targetRow][targetCol];
	    ChessPiece* movingPiece = chessBoard[row][col];
	    //set defaul that no piece is being taken. 
	    bool capture = false;
	    if (isLegalMove(movingPiece, originalTarget, row, col, 
			    targetRow, targetCol, capture)) {
	      // Undo the move as don't want to implement it
	      undoMove(row, col, targetRow, targetCol, movingPiece, 
		       originalTarget);
	      return false;
	    }
	  }
	}
      }
    }
  }
  // If no move can get out of check, it's checkmate
  return true;
}


bool ChessGame::isStalemate() {

  // Check if the king is not in check
  if (inCheck()) {
    return false; // If the king is in check, it's not stalemate
  }

  // Try every possible move for pieces of the current player's colour
  for (int row = 0; row < 8; ++row) {
    for (int col = 0; col < 8; ++col) {
      // Look for pieces of the current player's colour
      if (chessBoard[row][col] && 
	  chessBoard[row][col]->getPieceColour() == activeColour) {

	// Try moving this piece to every square
	for (int targetRow = 0; targetRow < 8; ++targetRow) {
	  for (int targetCol = 0; targetCol < 8; ++targetCol) {
	    // Check if this move is legal
	    ChessPiece* originalTarget =
	      chessBoard[targetRow][targetCol];
	    ChessPiece* movingPiece = chessBoard[row][col];

	    bool capture = false;
	    if (isLegalMove(movingPiece, originalTarget, row, col, 
                            targetRow, targetCol, capture)) {
	      // If legal move, return false (not stalemate)
	      undoMove(row, col, targetRow, targetCol, 
		       movingPiece, originalTarget);
	      return false;
	    }
	  }
	}
      }
    }
  }

  // If no legal moves exist, and the king is not in check, it's stalemate
  return true;
}

void ChessGame::switchTurn() 
{
  activeColour =
    (activeColour == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
}

/*
 * Chess Game destructor
 */
ChessGame::~ChessGame(){
  //cycle thorugh the board
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      //delete any piece on a position
      delete chessBoard[i][j];
      //set the position to null.
      chessBoard[i][j] = nullptr;
    }
  }
}


