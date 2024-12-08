#include <iostream>
#include <cstring>
#include <cctype>
#include "chessGame.h"
#include "chessPiece.h"//remove if I have all the other pieces? 
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

std::ostream& operator << ( std::ostream &out, const Turn& turn)
{
 if(turn == Turn::BLACK) {
  out << "BLACK";
 } else {
  out << "WHITE";
 }
 return out;
}


ChessGame::ChessGame() : playerToMove(Turn::WHITE), whiteKingPosition(-1, -1), blackKingPosition(-1, -1)// do I need to set it to null when I initialise?. king position to 0,0)
{
  // initialise chessBoard to be nul pointers. 
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      chessBoard[i][j] = nullptr; //nullptr
    }
  }
  cout << "chess Game initialised" << endl;
}

void ChessGame::loadState(const char fen[]) 
{

  enum class FenState{PIECE_PLACEMENT, ACTIVE_COLOUR, CASTLING}; //insde the
								//funciton or not.
  FenState currentState = FenState::PIECE_PLACEMENT;

  cout << "begining reading string in" << endl;

  //  is the position within the fen string.
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
          assignKing(fen[n], rowCounter, colCounter);
        }

        colCounter--;
	      }
	    //if number, empty space
	    else if (isdigit(fen[n])) {
		int no_empty_space = fen[n] - '0';
		for(int k = 0; k < no_empty_space; k++) {
		    // reset to null again if playin
		    // setting it to null above necessary?) 
		    chessBoard[rowCounter][colCounter] = nullptr;
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
		cout << "switch state to ACTIVE_COLOUR";
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
		cout << " switch state to CASTLING ";
	      }
	      n++;
	     break; 
	  }
	case FenState::CASTLING:
	  {
	    cout << fen[n];
	    n++;
	    break; 
	  }
      }
    }

  cout << "\n" << "exiting loop" << endl;
  cout << this;
  cout << "current turn: " << playerToMove << endl;


}

ChessPiece * ChessGame:: placePiece(const char fen)
{

PieceColour colour = isupper(fen) ? PieceColour::WHITE : PieceColour::BLACK;

  ChessPiece * new_piece = nullptr;

  switch(toupper(fen)){
  case 'R':
   new_piece = new Rook(colour);
    break;
  case 'N':
   new_piece = new Knight(colour);
    break;
  case 'B':
    new_piece = new Bishop(colour);
    break;
  case 'Q':
    new_piece = new Queen(colour);
    break;
  case 'K':
    new_piece = new King(colour);
    break;
  case 'P':
    new_piece = new Pawn(colour);
    break;
  }
  return new_piece;
}

void ChessGame::assignKing(const char fen, const int &rowPosition, const int &colPosition)
  {
    if (isupper(fen)) {
      whiteKingPosition.first = rowPosition;
      whiteKingPosition.second = colPosition;
      cout << "white king is at position " << whiteKingPosition.first << whiteKingPosition.second << endl;
    } 
    else {
      blackKingPosition.first = rowPosition;
      blackKingPosition.second = colPosition;
      cout << "black's king is at position " << blackKingPosition.first << blackKingPosition.second << endl;
    }

 }


void ChessGame::assignTurn(const char fen)
{
  if (fen == 'w')
    playerToMove = Turn::WHITE;
  else
    playerToMove = Turn::BLACK;
}

void ChessGame::submitMove( const char initialPosition[], const char targetPosition[])
{
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


	cout << initialRowNumber << " " << initialColNumber << " " << endl;
  cout << "chess board position " << initialPosition << endl;


	cout << "current turn: " << playerToMove << endl;


	// check if there is a piece there.
	if (movingPiece== nullptr) {
  		cout << "There is no piece at position " << initialPosition << endl;
		return;
	}
        // check if trying to move a piece of the wrong turn - reword
    else if ((static_cast<int>(movingPiece->getPieceColour())) != (static_cast<int>(playerToMove))) {
          cout << "It is not " << movingPiece->getPieceColour()
				<< "'s turn to move!" <<endl;
          return;
    } 

      cout << "we get here" << endl;
    if (isLegalMove(movingPiece, targetPiece, initialRowNumber, initialColNumber, targetRowNumber, targetColNumber, isCapture)) {
        if (isCapture) {
      // change is it is getPiece type.
          cout << "Capture: " << targetPiece->getPieceName() << " taken!" << endl;
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
      cout << playerToMove << " is in checkmate" << endl;
    }
    else { 
      cout << playerToMove << " is in check" << endl;
    }
  } 
  else {
    if(isStalemate()) {
      cout << "Stalemate occurs, match drawn" << endl;
    }
  }


  //if check check checkmate and then stalemate. 
 cout << this;
 cout << "current turn changed to: " << playerToMove << "\n" << endl;

 return;

}

bool ChessGame::isBoardClear(const int initialRowNumber, const int initialColNumber, const int targetRowNumber, const int targetColNumber)
{
  // cout << "checking if board is clear" << endl;
  // check if i move of a knight, doesn't need to b checkd.
 if (((abs(targetRowNumber - initialRowNumber) == 2) && (abs(targetColNumber - initialColNumber) == 1)) || (
      abs(targetRowNumber - initialRowNumber) == 1 && (abs(targetColNumber - initialColNumber) == 2))) {
        // cout << "piece moving is a knight, so no need to check if board is clear" << endl;
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
            cout << "diagonal route not clear" << endl;
            return false;
           }
           row = row + rowStep;
           column = column + colStep;
       	}
    }
   cout << "board is clear" << endl;
  return true;
}


void ChessGame::makeMove(const int initialRowNumber, const int initialColNumber, const int targetRowNumber, const int targetColNumber, ChessPiece * pieceMoved)
{
    chessBoard[targetRowNumber][targetColNumber] = pieceMoved;
    chessBoard[initialRowNumber][initialColNumber] = nullptr;
     if(King* king = dynamic_cast<King*>(pieceMoved)) {
      updateKingPosition(king, targetRowNumber, targetColNumber);
        }
}


void ChessGame::undoMove(const int initialRowNumber, const int initialColNumber, const int targetRowNumber, const int targetColNumber,  ChessPiece *pieceMoved, ChessPiece *pieceTaken)
{
  chessBoard[initialRowNumber][initialColNumber] = pieceMoved;
  chessBoard[targetRowNumber][targetColNumber] = pieceTaken;
  if(King* king = dynamic_cast<King*>(pieceMoved)) {
      updateKingPosition(king, initialRowNumber, initialColNumber);
        }
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
          // cout << "invalid move, attempting to take its own piece" << endl;
          return false;
	}
  //may want to only pass in the absolute differece to these functions as they all seem to need that (as in I do that maths when I'm in them)

  if (pieceMoved->isValidPieceMove(row, col, targetRow, targetCol, pieceTaken) && (isBoardClear(row, col, targetRow, targetCol))) {
			

      //should make move be bool? then if it passes check you actually make the move>
      makeMove(row, col, targetRow, targetCol, pieceMoved);
      cout << "make move fine, checking if move results in check" << endl;

      if(inCheck()) {
        //undo the move if invalid
        cout << "undoing move" << endl;
        undoMove(row, col, targetRow, targetCol,  pieceMoved, targetPiece);
        cout << "Ivalid move: leaves you in check" << endl;
        return false;
      }
      cout << "leaving is valid move" << endl;
      return true;
    }
    else {
        return false;
      }
}

void ChessGame::updateKingPosition(const King* king, const int newRow, const int newCol)

{
    if (king->getPieceColour() == PieceColour::WHITE) {
        whiteKingPosition.first = newRow;
        whiteKingPosition.second = newCol;
        cout << " white king is at " << whiteKingPosition.first << whiteKingPosition.second << endl;
    } else {
        blackKingPosition.first = newRow;
        blackKingPosition.second = newCol;
        cout << " black king is at " << blackKingPosition.first << blackKingPosition.second << endl;

    }
}

bool ChessGame::inCheck() {
    PieceColour opponentColour = (playerToMove == Turn::WHITE) ? PieceColour::BLACK : PieceColour::WHITE;

    cout << opponentColour << " is attacking the king after " << playerToMove << " move " << endl;
    // Get the position of the current player's King
    int kingRow, kingCol;
    if (playerToMove == Turn::WHITE) {
      kingRow = whiteKingPosition.first;
      kingCol = whiteKingPosition.second;
    } 
    else {
      kingRow = blackKingPosition.first;
      kingCol =  blackKingPosition.second;
    }

    //debugging line
    cout << playerToMove << "'s king is in position " << kingRow << " " << kingCol << endl;

    // If the King's position is invalid, return false (no check can be detected)
    if (kingRow == -1 || kingCol == -1) {
        return false;
    }

    // Now check if any opponent pieces can attack the current player's King - turn into a helper function if required for check? (underattack.)
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = chessBoard[row][col];
            if (piece != nullptr && piece->getPieceColour() == opponentColour) {
                // Check if this piece can attack the current player's King
                cout << "checking for" << piece->getPieceName() << endl;
                if (piece->isValidPieceMove(row, col, kingRow, kingCol, true)) {
                cout << piece->getPieceName() << " valid move " << endl;
                cout << "now check if path is clear" << endl;

                    // Check if the path is clear for Rooks, Bishops, or Queens
                    if (isBoardClear(row, col, kingRow, kingCol)) {
                      cout << piece->getPieceName() << " path is clear " << endl;

                        return true; 
                    }
                }
            }
        }
    }

    return false; 
}

bool ChessGame::isCheckmate(){
  PieceColour pieceColour_ = (playerToMove == Turn::WHITE) ? PieceColour::WHITE : PieceColour::BLACK;

// Try every possible move for pieces of this color
  for (int row = 0; row < 8; ++row) {
      for (int col = 0; col < 8; ++col) {
          // Look for pieces of the same colour as the king
          if (chessBoard[row][col] && 
              chessBoard[row][col]->getPieceColour() == pieceColour_) {
               cout << chessBoard[row][col]->getPieceName() << " is the same colour as" << pieceColour_ << endl;

              // Try moving this piece to every square
              for (int targetRow = 0; targetRow < 8; ++targetRow) {
                  for (int targetCol = 0; targetCol < 8; ++targetCol) {
                      // Check if this move is legal and resolves the check
                      ChessPiece* originalTarget = chessBoard[targetRow][targetCol];
                      ChessPiece* movingPiece = chessBoard[row][col];
                        //set defaul that no piece is being taken. 
                        cout << chessBoard[row][col]->getPieceName() << " is going from " << row << col << " to " << targetRow << targetCol << endl;
                      bool capture = false;
                      if (isLegalMove(movingPiece, originalTarget, row, col, targetRow, targetCol, capture)) {
                          // Legal finds a legal way to get out of chess so implements the move. Therefore it needs to be undone (as it is not the other players turn yet)
                          undoMove(row, col, targetRow, targetCol, movingPiece, originalTarget);
                          cout << "valid move " << row << col << " to " << targetRow << targetCol << endl;
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
    PieceColour pieceColour_ = (playerToMove == Turn::WHITE) ? PieceColour::WHITE : PieceColour::BLACK;

    // Check if the king is not in check
    if (inCheck()) {
        return false; // If the king is in check, it's not stalemate
    }

    // Try every possible move for pieces of the current player's color
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // Look for pieces of the current player's color
            if (chessBoard[row][col] && 
                chessBoard[row][col]->getPieceColour() == pieceColour_) {

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
                            cout << "valid move " << row << col << " to " << targetRow << targetCol << endl;
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
  playerToMove = (playerToMove == Turn::WHITE) ? Turn::BLACK : Turn::WHITE;
}


ChessGame::~ChessGame(){
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      delete chessBoard[i][j];
      chessBoard[i][j] = nullptr;
      }
    }
  }











