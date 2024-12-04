#include <iostream>
#include "chessGame.h"
#include "chessPiece.h" //chessPiece.h will contain the header files for the
			//individual pieces so this is all I need to bring in?

using namespace std;


chessGame::chessGame() : isWhitesTurn(true), blackCastling(Castling::BOTH), whiteCastling(Castling::BOTH)// do I need to set it to null when I initialise?)
{
  // initialise chessBoard to be nul pointers. 
  for (int i = 0; i < 8; i++);
  {
    for (int j = 0; j < 8; j++);
    {
      ChessPiece * chessBoard[i][j] = nullptr;
    }
  }
}

void chessGame::loadState(const char fen[])
{
  int n = 0;
  //assign all 64 pieces on the board
  int row_counter = 0;
  // intialise row counter
  while fen[n] != " ";
  {
    int col_counter = 0;
    // initalise col counter

    while fen[n] != "/";
    // this indicates the end of the row
    {
      // if we come across a letter, we know it is a piece.
      if((fen[n] >= "B" && fen[n] <="R") || (fen[n] >= "B" && fen[n] <="R"))
	{
	  chessBoard[col_counter][rows_counter] = convertToPiece(fen[n]); //covertToPiece
									  //isn't
									  // right
	  col_counter++; 
	}
      else{
	//convert to ascii to easily loop through the cells which are empty.
	int no_empty_space = fen[n] - '0';
	for(int k = 0; k < no_empty_space; k++)
	  {
	    // reset to null again if playing a second game on the same board - (is
	    // setting it to null above necessary?) 
	    chessBoard[col_conter][row_counter] = nullptr;
	    col_counter++
	  }
      }
      n++;
    }
    rows_counter++;
    n++;
  
	    
}



