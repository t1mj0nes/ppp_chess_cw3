#include <iostream>
#include <cstring>
#include <cctype>
#include "chessGame.h"
#include "chessPiece.h"//remove if I have all the other pieces? 
#include "colour.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h" 
#include "queen.h"
#include "rook.h"
//chessPiece.h will contain the header files for the
			//individual pieces so this is all I need to bring in?

using namespace std;



// this is set up for pointers, but it will be letters rather than pointers to positions
ostream& operator << (ostream &out, const ChessGame * cg) {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
	if (cg->chessBoard[row][col] != nullptr) {
	    out << cg->chessBoard[row][col]->getPieceName() << " "; //I will need overloading for the
					   //pieces output.
	  }
	else {
	    out << " . "; //. instead where nullpointers are.
	  }
	  
      }
    out << endl;
    }
      return out;
}

ChessGame::ChessGame()
{
  resetGame();
}

void ChessGame::resetGame(){

  gameOver = false;


  //set king default position to not on the board
  whiteKingPosition = {-1, -1};
  blackKingPosition = {-1, -1};

  // set default to castling not being allowed
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

void ChessGame::loadState(const char fen[]) 
{

  if(resetRequired)
  {
    resetGame();
  }

  enum class FenState{PIECE_PLACEMENT, ACTIVE_COLOUR, CASTLING}; //insde the
								//funciton or not.
  FenState currentState = FenState::PIECE_PLACEMENT;
  //  n is the position within the fen string.
  int n = 0;

  //loading in a board from blacks perspective. A1 is top right corner.  
  int rowCounter = 7;
  int colCounter = 7;

  while (fen[n] != '\0') {
      switch (currentState)
	  {
    case FenState::PIECE_PLACEMENT:
      {
        // check if a letter 
        if(isalpha(fen[n])) {
          chessBoard[rowCounter][colCounter] = placePiece(fen[n]);
          if ((fen[n] == 'K') || (fen[n] == 'k')){
            //this is the same as update king position, so do this step in the placePiece part. 
            updateKingPosition(static_cast<King*>(chessBoard[rowCounter][colCounter]), rowCounter, colCounter);
          }

          colCounter--;
          }
        //if number, empty space
        else if (isdigit(fen[n])) {
      int no_empty_space = fen[n] - '0';
      for(int k = 0; k < no_empty_space; k++) {
          // empty spaces are ignored and kept as null pointers. 
          colCounter--;
        }
          }
        else if (fen[n] == '/') {
      rowCounter--;
      //reset column counter
      colCounter = 7;
          }
        else if (fen[n] == ' ')  {
      currentState = FenState::ACTIVE_COLOUR;
          }
        n++;
        break;
      }
      case FenState::ACTIVE_COLOUR:
      {
        if (isalpha(fen[n])) {
      assignTurn(fen[n]);
          }
        if (fen[n] == ' ') {
      currentState=FenState::CASTLING;
          }
          n++;
        break; 
      }
    case FenState::CASTLING:
      {
        assignCastling(fen[n]);
        n++;
        break; 
      }
    }
  }

  //new game state has been loaded. If a new game is loaded, the game needs to be reset. 
  resetRequired = true;

  cout << "A new board state is loaded!" << endl;

 //delete
  cout << this;

}

ChessPiece * ChessGame:: placePiece(const char fen)
{

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

void ChessGame::assignTurn(const char fen)
{
  if (fen == 'w')
    activeColour = Colour::WHITE;
  else if (fen == 'b')
    activeColour = Colour::BLACK;
  // assumed that fen string will always be valid, therefore no need to catch edge cases.
}

void ChessGame::assignCastling(const char fen) {
    // Reset castling rights by default if '-' is encountered
    if (fen == '-') {
        whiteCastlingRights = {false, false};
        blackCastlingRights = {false, false};
    }
    else if (isalpha(fen)) {
        // Use a switch-case to directly map the castling rights
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
        // If the character is not recognized, reset to no castling rights
        whiteCastlingRights = {false, false};
        blackCastlingRights = {false, false};
    }
}


void ChessGame::submitMove( const char initialPosition[], const char targetPosition[])
{
  if (gameOver == true) {
    //KEEP
    cout << "error, game over. Please load in a new game." << endl;
    return;
  }
//check if these exceed the board, or are smaller then the board and if the move is an uppercase letter followed by a number. 
// bool validInputs (initialPosition, targetPosition);

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
  		cout << "There is no piece at position " << initialPosition << "!" << endl;
		return;
	}
        // check if trying to move a piece of the wrong turn - reword
    else if (movingPiece->getPieceColour() != activeColour) {
          cout << "It is not " << movingPiece->getPieceColour()
				<< "'s turn to move!" <<endl;
          return;
    } 

    if (isLegalMove(movingPiece, targetPiece, initialRowNumber, initialColNumber, targetRowNumber, targetColNumber, isCapture)) {
        cout << activeColour <<"'s " << movingPiece->getPieceName() << " moves from " << initialPosition << " to " << targetPosition << endl;
        if (isCapture) {
      // change is it is getPiece type.
        Colour capturedPieceColour = getOppositeColour(activeColour);
          cout << "taking " << capturedPieceColour << "'s " <<targetPiece->getPieceName() << endl;
          delete targetPiece; // Remove the captured piece from memory
        }
      
      cout << "Move successful!" << endl;
      //update the kings position if necessary
  

      switchTurn();
    }
    else {
      cout << "invalid move" << endl;
      //change to be more descriptive.
      cout << " colours piece cannot move to " << targetPosition << endl;
      return;
    }

  //check check of opponent
  bool isIncheck = inCheck();
  if (isIncheck){
    cout << "checking for check mate" << endl;
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
      cout << "Stalemate occurs, match drawn" << endl;
      gameOver = true;
    }
  }


  //if check check checkmate and then stalemate. 
 cout << this;
 cout << "current turn changed to: " << activeColour << "\n" << endl;

 return;

}

bool ChessGame::isLegalMove(ChessPiece * pieceMoved, ChessPiece * targetPiece, const int row, const int col, const int targetRow, const int targetCol, bool & pieceTaken)
{


	if (chessBoard[targetRow][targetCol] != nullptr) {
          pieceTaken = true;
        }
        else {
          pieceTaken =false;
        }

if ((pieceTaken == true) &&
        ((pieceMoved->getPieceColour())
         == (chessBoard[targetRow][targetCol]->getPieceColour()))) {
          return false;
	}
  //may want to only pass in the absolute differece to these functions as they all seem to need that (as in I do that maths when I'm in them)

  // checking if any piece on the board is able to compete the move.
  if (pieceMoved->isValidPieceMove(row, col, targetRow, targetCol, pieceTaken))  {

    // using abs targetCol - col so much.    - using something else
    // checking if castling is occuring
    if ((dynamic_cast<King*>(pieceMoved)) && (abs(targetCol - col) == 2)){
      cout << "piece recognised as a King that is trying to castle" << endl;
      int direction;
      if (!canCastle(row, col, targetCol, pieceTaken, pieceMoved, direction)) {
        return false;
      }
      castlingMove(row, col, targetCol, direction, pieceMoved);
      return true;
    }

    // check for all other pieces
    if (!isBoardClear(row, col, targetRow, targetCol)) {
        // if the board isn't clear between the piece and its target square, move is not valid.
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

bool ChessGame::isBoardClear(const int initialRowNumber, const int initialColNumber, const int targetRowNumber, const int targetColNumber)
{
  // check if i move of a knight, doesn't need to b checkd.
  //dynamic cast instead? 
 if (((abs(targetRowNumber - initialRowNumber) == 2) && (abs(targetColNumber - initialColNumber) == 1)) || (
      abs(targetRowNumber - initialRowNumber) == 1 && (abs(targetColNumber - initialColNumber) == 2))) {
        return true;
      }

int rowDiff = (targetRowNumber - initialRowNumber);
int colDiff = (targetColNumber - initialColNumber);

int rowStep = (rowDiff > 0) ? 1 : -1;
int colStep = (colDiff > 0) ? 1 : -1;
// checking if horizontal
 if (rowDiff == 0) {
   for (int column = initialColNumber + colStep; column != targetColNumber; column += colStep){
     if (chessBoard[targetRowNumber][column] != nullptr){
        // cout << "rows not clear" << endl;
        return false;
        }
     }
     // no obstruction was found, return true.
     return true;
 }
 //checking if vertical path is clear
 else if (colDiff == 0) {
   for (int row = initialRowNumber + rowStep; row != targetRowNumber; row += rowStep){
     if (chessBoard[row][targetColNumber] != nullptr){
        // cout << "columns not clear" << endl;
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

bool ChessGame::canCastle(int startRow, int startCol, int targetCol, bool pieceTaken, ChessPiece * pieceMoved, int & direction) {
  cout << "assessing if " << activeColour << "can castle in the 'canCastle' function" << endl;

  bool castlingQueenside;

  if(pieceTaken){
    // you can't take a piece while trying to castle
    return false;
  }

  // castling queenside when the target colum is less then the kings starting position.
  castlingQueenside = (startCol > targetCol);
  
  // determine which colour is castling. Pass by reference to direclty modify that attribute.
  cout << activeColour << endl;
  std::pair<bool, bool>& colourCastling = (activeColour == Colour::WHITE) ? whiteCastlingRights : blackCastlingRights;

  std::cout << "Kingside: " << colourCastling.first 
          << ", Queenside: " << colourCastling.second << std::endl;

  //check if the king or rook has already moved.
  if (castlingQueenside) {
      if (!colourCastling.second) {
          // Queenside castling not allowed
         std::cout << "Queenside castling not allowed!" << std::endl;

          return false; 
      }
  } else {
    cout << "not castling queenside" << endl;
      if (!colourCastling.first) {
          // Kingside castling not allowed
          std::cout << "Kingside castling not allowed!" << std::endl;

          return false; 
      }
  }

cout << "finished checkign previous castling" << endl;
   // Determine the rook's expected position
    int rookCol = castlingQueenside ? 0 : 7;

    // Verify the piece at the rook's position is a rook of the same color
    ChessPiece* rook = chessBoard[startRow][rookCol];
    if (!rook || !dynamic_cast<Rook*>(rook) || rook->getPieceColour() != activeColour) {
        return false;
    }

  
  //Check if all squares between the king and rook are clear
  if(!isBoardClear(startRow, startCol, startRow, rookCol))
  {
    return false;
  }

  // check if the king is in check in its current posigion
   if(inCheck()) {
      //undo the move if invalid
      cout << "king cannot castle while in check" << endl;
      return false;
    }

    direction = (castlingQueenside) ? -1 : 1;


  // move thorugh the start column until it is not in the final position
  for (int position = startCol + direction; position != targetCol + direction; position += direction) {
    makeMove(startRow, startCol, startRow, position, pieceMoved);
    if (inCheck()) {
          //undo the move if invalid
          undoMove(startRow, startCol, startRow,  position, pieceMoved, nullptr);
          cout << "king is attempting to castle across a square in check" << endl;
          return false;
        }
    // revert back to the starting state of the board (canCastle doesn't execute the move)
    undoMove(startRow, startCol, startRow,  position, pieceMoved, nullptr);

  }

  return true;


}  

void ChessGame::makeMove(const int initialRowNumber, const int initialColNumber, const int targetRowNumber, const int targetColNumber, ChessPiece * pieceMoved)
{
    
    
    chessBoard[targetRowNumber][targetColNumber] = pieceMoved;
    chessBoard[initialRowNumber][initialColNumber] = nullptr;

    if(dynamic_cast<King*>(pieceMoved)) {
      updateKingPosition(dynamic_cast<King*>(pieceMoved), targetRowNumber, targetColNumber);
      updateCastlingRights(initialRowNumber, initialColNumber, pieceMoved);
    } else if(dynamic_cast<Rook*>(pieceMoved) ) {
      updateCastlingRights(initialRowNumber, initialColNumber, pieceMoved);
    }
      
}

void ChessGame::updateCastlingRights(int initialRowNumber, int initialColNumber, ChessPiece* pieceMoved)
{
    // Use activeColour to determine which color's castling rights to update
    std::pair<bool, bool>& colourCastling = (activeColour == Colour::WHITE) ? whiteCastlingRights : blackCastlingRights;

    // If it's a Rook, increment the move counter
    if (Rook* rook = dynamic_cast<Rook*>(pieceMoved)) {
        rook->incrementCounter();

        // Update castling rights based on the rook's position
        if (initialColNumber == 7) { // Kingside rook
            colourCastling.second = false;  // No castling on this side anymore
        } else if (initialColNumber == 0) { // Queenside rook
            colourCastling.first = false;   // No castling on this side anymore
        }
    }

    // If it's a King, revoke castling rights
    else if (dynamic_cast<King*>(pieceMoved)) {
      cout << "king moved, both set to false" << endl;
        colourCastling.first = false;  // Revoke queenside castling
        colourCastling.second = false; // Revoke kingside castling
    }
}



void ChessGame::undoMove(const int initialRowNumber, const int initialColNumber, const int targetRowNumber, const int targetColNumber,  ChessPiece *pieceMoved, ChessPiece *pieceTaken)
{
  chessBoard[initialRowNumber][initialColNumber] = pieceMoved;
  chessBoard[targetRowNumber][targetColNumber] = pieceTaken;
  
 if (dynamic_cast<King*>(pieceMoved)) {
    updateKingPosition(dynamic_cast<King*>(pieceMoved), initialRowNumber, initialColNumber);
    revertCastlingRights(initialRowNumber, initialColNumber, pieceMoved);
} else if (dynamic_cast<Rook*>(pieceMoved)) {
    revertCastlingRights(initialRowNumber, initialColNumber, pieceMoved);
}
}

void ChessGame::revertCastlingRights(int initialRowNumber, int initialColNumber, ChessPiece* pieceMoved)
{
    // Use activeColour to determine which colour's castling rights to update
    std::pair<bool, bool>& colourCastling = (activeColour == Colour::WHITE) ? whiteCastlingRights : blackCastlingRights;

    // If it is a Rook, decrement the move counter, as undoing a move.
    if (Rook* rook = dynamic_cast<Rook*>(pieceMoved)) {
        rook->decrementCounter();

        // If the rook hasn't moved yet, restore castling rights for that side
        if (rook->getMoves() == 0) {
          // Kingside rook
            if (initialColNumber == 7) { 
              // Re-enable kingside castling
                colourCastling.second = true; 
                cout << activeColour << "queenside castling reverted to true (1)" << endl;
                // Queenside rook 
            } else if (initialColNumber == 0) { 
              // Re-enable queenside castling
                colourCastling.first = true; 
                cout << activeColour << "kingside castling reverted to true (1)" << endl;
            }
        }
    }
    // If it's a King, check for the movement of the rooks
    else if (dynamic_cast<King*>(pieceMoved)) {
        // Check if the rooks have moved 
        bool kingsideRookNotMoved = false;
        cout << activeColour << "kingside castling reverted to false (0)" << endl;

        bool queensideRookNotMoved = false;
        cout << activeColour << "queenside castling reverted to false (0))" << endl;


        // Check the kingside rook (col 7)
        if (Rook* kingsideRook = dynamic_cast<Rook*>(chessBoard[initialRowNumber][7])) {
            if (kingsideRook->getMoves() == 0) {
                kingsideRookNotMoved = true;
            }
        }

        // Check the queenside rook (col 0)
        if (Rook* queensideRook = dynamic_cast<Rook*>(chessBoard[initialRowNumber][0])) {
            if (queensideRook->getMoves() == 0) {
                queensideRookNotMoved = true;
            }
        }

        // Revert castling rights based on rook movement
        colourCastling.first = kingsideRookNotMoved; 
        colourCastling.second = queensideRookNotMoved;

    }
}



void ChessGame::castlingMove(int row, int col, int targetCol, int & direction, ChessPiece * pieceMoved) {

  // move king
  makeMove(row, col, row, targetCol, pieceMoved);

    // Move the rook
    
  // Determine rook's target column
  int rookStartCol = (direction == 1) ? 7 : 0; 
  int rookTargetCol = targetCol - direction; 
  
  ChessPiece * rookCastling = chessBoard[row][rookStartCol];
  // move the rook
  makeMove(row, rookStartCol, row, rookTargetCol, rookCastling);

}


void ChessGame::updateKingPosition(const King* king, const int newRow, const int newCol)

{
    if (king->getPieceColour() == Colour::WHITE) {
        whiteKingPosition.first = newRow;
        whiteKingPosition.second = newCol;
        // cout << " white king is at " << whiteKingPosition.first << whiteKingPosition.second << endl;
    } else {
        blackKingPosition.first = newRow;
        blackKingPosition.second = newCol;
        //cout << " black king is at " << blackKingPosition.first << blackKingPosition.second << endl;
    }
}

bool ChessGame::inCheck() {
    Colour opponentColour = (activeColour == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;

    // cout << opponentColour << " is attacking the king after " << activeColour << " move " << endl;
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

    //debugging line
   // cout << activeColour << "'s king is in position " << kingRow << " " << kingCol << endl;

    // If the King's position is invalid, return false (no check can be detected)
    if (kingRow == -1 || kingCol == -1) {
        cout << "error " << activeColour << "'s king is not on the baord" << endl;
        return false;
    }

    // Now check if any opponent pieces can attack the current player's King - turn into a helper function if required for check? (underattack.)
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = chessBoard[row][col];
            if (piece != nullptr && piece->getPieceColour() == opponentColour) {
                // Check if this piece can attack the current player's King
                // cout << "checking for" << piece->getPieceName() << endl;
                if (piece->isValidPieceMove(row, col, kingRow, kingCol, true)) {
                // cout << piece->getPieceName() << " valid move " << endl;
                //cout << "now check if path is clear" << endl;

                    // Check if the path is clear for Rooks, Bishops, or Queens
                    if (isBoardClear(row, col, kingRow, kingCol)) {
                      // cout << piece->getPieceName() << " path is clear " << endl;

                        return true; 
                    }
                }
            }
        }
    }

    return false; 
}

bool ChessGame::isCheckmate(){

// Try every possible move for the player in check
  for (int row = 0; row < 8; ++row) {
      for (int col = 0; col < 8; ++col) {
          // Look for pieces of the same colour as the king
          if (chessBoard[row][col] && 
              chessBoard[row][col]->getPieceColour() == activeColour) {
               // cout << chessBoard[row][col]->getPieceName() << " is the same colour as" << activeColour << endl;

              // Try moving this piece to every square
              for (int targetRow = 0; targetRow < 8; ++targetRow) {
                  for (int targetCol = 0; targetCol < 8; ++targetCol) {
                      // Check if this move is legal and resolves the check
                      ChessPiece* originalTarget = chessBoard[targetRow][targetCol];
                      ChessPiece* movingPiece = chessBoard[row][col];
                        //set defaul that no piece is being taken. 
                      bool capture = false;
                      if (isLegalMove(movingPiece, originalTarget, row, col, targetRow, targetCol, capture)) {
                          // Legal finds a legal way to get out of chess so implements the move. Therefore it needs to be undone (as it is not the other players turn yet)
                          undoMove(row, col, targetRow, targetCol, movingPiece, originalTarget);
                          //cout << "valid move " << row << col << " to " << targetRow << targetCol << endl;
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

    // Try every possible move for pieces of the current player's color
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // Look for pieces of the current player's color
            if (chessBoard[row][col] && 
                chessBoard[row][col]->getPieceColour() == activeColour) {

                // Try moving this piece to every square
                for (int targetRow = 0; targetRow < 8; ++targetRow) {
                    for (int targetCol = 0; targetCol < 8; ++targetCol) {
                        // Check if this move is legal
                        ChessPiece* originalTarget = chessBoard[targetRow][targetCol];
                        ChessPiece* movingPiece = chessBoard[row][col];

                        bool capture = false;
                        if (isLegalMove(movingPiece, originalTarget, row, col, targetRow, targetCol, capture)) {
                            // If there's a legal move, return false (it's not stalemate)
                            undoMove(row, col, targetRow, targetCol, movingPiece, originalTarget);
                            //cout << "valid move " << row << col << " to " << targetRow << targetCol << endl;
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
  activeColour = (activeColour == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
}


ChessGame::~ChessGame(){
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      delete chessBoard[i][j];
      chessBoard[i][j] = nullptr;
      }
    }
  }











