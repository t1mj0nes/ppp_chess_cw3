x#include <iostream>
#include <cstring>
#include <cctype>
#include "chessGame.h"
#include "chessPiece.h" //chessPiece.h will contain the header files for the
			//individual pieces so this is all I need to bring in?

using namespace std;



// this is set up for pointers, but it will be letters rather than pointers to positions
ostream& operator << (ostream &out, const ChessGame * cg){
  for (int i = 0; i < 8; i++)
    {
    for (int j = 0; j < 8; j++)
      {
	if (cg->chessBoard[i][j] != nullptr)
	  {
	    out << (cg->chessBoard[i][j]); //I will need overloading for the
					   //pieces output.
	  }
	else
	  {
	    out << "."; //. instead where nullpointers are.
	  }
	  
      }
    out << endl;
    }
      return out;
}



ChessGame::ChessGame() : isWhitesTurn(true) // do I need to set it to null when I initialise?)
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

  int row_counter = 0;
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
		row_counter++;
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
		cout << "switch state to CASTLING";
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
  // cout << this;
  //cout << playerToMove << " turn" << endl; - make work to testcolour. 

}

ChessPiece * ChessGame:: placePiece(const char fen);
{

  ChessPiece::Colour PieceColour = static_cast<PieceColour>(isupper(fen));

  ChessPiece * new_piece = null;

  switch(toupper(fen)){
  case 'R':
    new_piece = new Rook(PieceColour);
    break;
  case 'N':
    new_piece = new Knight(PieceColour);
    break;
  case 'B':
    new_piece = new Bishop(PieceColour);
    break;
  case 'Q':
    new_piece = new Queen(PieceColour);
    break;
  case 'K':
    new_piece = new King(PieceColour);
    break;
  case 'P':
    new_piece = new Pawn(Piececolour);
  }
  return new_piece;
}

void ChessGame::assignTurn(const char fen);
{
  if (fen == 'w')
    playerToMove = Turn::WHITE;
  else
    playerToMove = Turn::BLACK;

}

void ChessGame::submitMove( const char whiteMove[], const char blackMove[])
{
  cout << "make move" << endl;
}
