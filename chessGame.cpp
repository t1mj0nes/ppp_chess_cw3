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
ostream& operator << (ostream &out, const ChessGame * cg){
  for (int row = 0; row < 8; row++)
    {
    for (int col = 0; col < 8; col++)
      {
	if (cg->chessBoard[row][col] != nullptr)
	  {
	    out << cg->chessBoard[row][col]->getPieceName() << " "; //I will need overloading for the
					   //pieces output.
	  }
	else
	  {
	    out << " . "; //. instead where nullpointers are.
	  }
	  
      }
    out << endl;
    }
      return out;
}

std::ostream& operator << ( std::ostream &out, const Turn& turn)
{
 if(turn == Turn::BLACK){
  out << "BLACK";
 } else {
  out << "WHITE";
 }
 return out;
}


ChessGame::ChessGame() : playerToMove(Turn::WHITE) // do I need to set it to null when I initialise?)
{
  // initialise chessBoard to be nul pointers. 
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      chessBoard[i][j] = nullptr; //nullptr
    }
  }
  cout << "chess Game initialised" << endl;
}

void ChessGame::loadState(const char fen[]) //could use states (look at in
					    //comments part)
{

  enum class FenState{PIECE_PLACEMENT, ACTIVE_COLOUR, CASTLING}; //insde the
								//funciton or not.
  FenState currentState = FenState::PIECE_PLACEMENT;

  cout << "begining reading string in" << endl;

  //  is the position within the fen string.
  int n = 0;

  int row_counter = 7;
  int col_counter = 0;

  while (fen[n] != '\0')
    {
      switch (currentState)
	{
	case FenState::PIECE_PLACEMENT:
	  {
	    // check if a letter 
	    if(isalpha(fen[n]))
	      {
		chessBoard[row_counter][col_counter] = placePiece(fen[n]);
		col_counter++;
	      }
	    //if number, empty space
	    else if (isdigit(fen[n]))
	      {
		int no_empty_space = fen[n] - '0';
		for(int k = 0; k < no_empty_space; k++)
		  {
		    // reset to null again if playin
		    // setting it to null above necessary?) 
		    chessBoard[row_counter][col_counter] = nullptr;
		    col_counter++;
		  }
	      }
	    else if (fen[n] == '/')
	      {
		row_counter--;
		//reset column counter
		col_counter = 0;
	      }
	    else if (fen[n] == ' ')
	      {
		currentState = FenState::ACTIVE_COLOUR;
		cout << "switch state to ACTIVE_COLOUR";
	      }
	    n++;
	    break;
	  }
	   case FenState::ACTIVE_COLOUR:
	  {
	    if (isalpha(fen[n]))
	      {
		assignTurn(fen[n]);
	      }
	     if (fen[n] == ' ')
	      {
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

void ChessGame::assignTurn(const char fen)
{
  if (fen == 'w')
    playerToMove = Turn::WHITE;
  else
    playerToMove = Turn::BLACK;
}

void ChessGame::submitMove( const char initialPosition[], const char targetPosition[])
{
//check if these exceed the board, or are smaller then the board.
	int initial_row_number = initialPosition[1] - '0' - 1;
  	int initial_col_number = initialPosition[0] - 'A';
	int target_row_number = targetPosition[1] - '0' - 1;
	int target_col_number = targetPosition[0] - 'A';
    bool isCapture;
    ChessPiece* piece =chessBoard[initial_row_number][initial_col_number];

	cout << initial_col_number << " " << initial_row_number << " " << endl;
    cout << "chess board position " << initialPosition << endl;

	cout << "current turn: " << playerToMove << endl;


	if (chessBoard[target_row_number][target_col_number] != nullptr) {
          isCapture = true;
        }
        else
          isCapture =false;
	// detecting if there is a piece there.
	if (piece == nullptr) {
  		cout << "There is no piece at position " << initialPosition << endl;
		return;
	}
        // trying to move a pice of the wrong turn - reword
    else if ((static_cast<int>(piece->getPieceColour())) != (static_cast<int>(playerToMove))) {
          cout << "It is not " << piece->getPieceColour()
				<< "'s turn to move!" <<endl;
          return;
    }
        // attempting to take own piece
	else if ((isCapture == true) &&
        ((piece->getPieceColour())
         == (chessBoard[target_row_number][target_col_number]->getPieceColour()))) {
          cout << "invalid move, attempting to take its own piece" << endl;
          return;
	}
   else {
    	if (piece->isValidPieceMove(initial_row_number, initial_col_number, target_row_number, target_col_number, isCapture) && (isBoardClear(initial_row_number, initial_col_number, target_row_number, target_col_number)))
			cout << "valid move" << endl;
    }







  cout << "make move" << endl;

	//put all of this into one function and then call that with both whiteMove and blackMove



	//bool piceValidMove =
 cout << this;
 cout << "current turn: " << playerToMove << endl;

 return;

}

bool ChessGame::isBoardClear(const int initial_row_number, const int initial_col_number, const int target_row_number, const int target_col_number)
{
  // check if i move of a knight, doesn't need to b checkd.
 if (((abs(target_row_number - initial_row_number) == 2) && (abs(target_col_number - initial_col_number) == 1)) || (
      abs(target_row_number - initial_row_number) == 1 && (abs(target_col_number - initial_col_number) == 2)))
	return true;

//these all need step in - are they incrementing or decrementing, then that can be applied to the loop.


int rowDiff = (target_row_number - initial_row_number);
int colDiff = (target_col_number - initial_col_number);

int rowStep = (rowDiff > 0) ? 1 : -1;
int colStep = (colDiff > 0) ? 1 : -1;

 if (target_row_number - initial_row_number == 0) {
   for (int column = initial_col_number + colStep; column != target_col_number; column += colStep){
     if (chessBoard[target_row_number][column] != nullptr)
       return false;
     }
 }
 else if (target_col_number - initial_col_number == 0) {
   for (int row = initial_row_number + rowStep; row != target_row_number; row += rowStep){
     if (chessBoard[rowStep][target_col_number] != nullptr)
       return false;
     }
  }
 else if (abs((target_row_number - initial_row_number)/(target_col_number - initial_col_number)) == 1) {
 		int row = initial_row_number + rowStep;
 		int column = initial_col_number + colStep;
        while (row != target_row_number && column != target_col_number) {
          if (chessBoard[row][column] != nullptr){
            return false;
           }
           row = row + rowStep;
           column = column + colStep;
       	}
    }
  return true;
}



ChessGame::~ChessGame(){
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      delete chessBoard[i][j];
      chessBoard[i][j] = nullptr;
      }
    }
  }











