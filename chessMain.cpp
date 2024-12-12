#include"chessGame.h"

#include<iostream>

using std::cout;

int main() {
  
	cout << "========================\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n\n";

	ChessGame cg;
       	cg.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
	cout << '\n';

	cg.submitMove("D7", "D8");
	cout << '\n';

	cg.submitMove("D4", "H6");
	cout << '\n';

	cg.submitMove("D2", "D4");
	cout << '\n';	

	cg.submitMove("F8", "B4");
	cout << '\n';

	cout << "=========================\n";
	cout << "Alekhine vs. Vasic (1931)\n";
	cout << "=========================\n\n";


	cg.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
	cout << '\n';

	cg.submitMove("E2", "E4");
	cg.submitMove("E7", "E6");
	cout << '\n';

	cg.submitMove("D2", "D4");
	cg.submitMove("D7", "D5");
	cout << '\n';

	cg.submitMove("B1", "C3");
	cg.submitMove("F8", "B4");
	cout << '\n';

	cg.submitMove("F1", "D3");
	cg.submitMove("B4", "C3");
	cout << '\n';

	cg.submitMove("B2", "C3");
	cg.submitMove("H7", "H6");
	cout << '\n';

	cg.submitMove("C1", "A3");
	cg.submitMove("B8", "D7");
	cout << '\n';

	cg.submitMove("D1", "E2");
	cg.submitMove("D5", "E4");
	cout << '\n';

	cg.submitMove("D3", "E4");
	cg.submitMove("G8", "F6");
	cout << '\n';

	cg.submitMove("E4", "D3");
	cg.submitMove("B7", "B6");
	cout << '\n';

	cg.submitMove("E2", "E6");
	cg.submitMove("F7", "E6");
	cout << '\n';

	cg.submitMove("D3", "G6");
	cout << '\n';



 /*
--------------------------------------------------------- 
					additional Tests
*/
cout << "=========================\n";
cout << "     additional tests    \n";
cout << "=========================\n\n";

//game cannot continue after checkmate
cg.submitMove("H5", "H6");
cout << '\n';
cout << '\n';

// castling checks 1 - dealing with check and when the board isn't empty
cg.loadState("r3k2r/8/6p1/5Q2/8/2q5/1P6/R3K2R b KQkq");
cout << '\n';

//first check for invalid inputs
cg.submitMove("E8G", "C82");
cg.submitMove("Y8", "Z8");
cg.submitMove("A9", "B10");

// blackcastles attempts to queenside, but can't (castling across check)
cg.submitMove("E8", "C8");
//black now takes the white queen
cg.submitMove("G6", "F5");
//white tries to castles kingside, but can't (it is in check)
cg.submitMove("E1", "G1");  
//white pawn now takes the black queen (enaabling castling)
cg.submitMove("B2", "C3");
cout << '\n';
// black now successfuly castles
cg.submitMove("E8", "C8");
//white now successfuly castles
cg.submitMove("E1", "G1");  
cout << '\n';
// blacking rook moves out of the way
cg.submitMove("D8", "D7");
//White queen attempts to castle other way (rook is in the way)
cg.submitMove("G1", "E1"); 
//valid white move made
cg.submitMove("G1", "G2");
cout << '\n';
//Black king attempts to castle other way (nothing in the way but too long)
cg.submitMove("C8", "E8");
cout << '\n';
cout << '\n';



//castling checks 2 - castling when the king has moved or a rook has moved
cg.loadState("r3k2r/8/8/8/8/8/8/R3K2R  w KQkq");
cout << '\n';

// White rook captures black rook, black is in check.
cg.submitMove("H1", "H8");  
// Black king attempts to castle with white rook (illegal).
cg.submitMove("E8", "G8"); 
// Black king moves to E7 to get out of check.
cg.submitMove("E8", "E7");  
cout << '\n';
// White rook moves back to H1.
cg.submitMove("H8", "H1");  
// Black king moves back to E8.
cg.submitMove("E7", "E8");  
cout << '\n';
// White king attempts to castle with rook (illegal, rook has moved).
cg.submitMove("E1", "G1");  
//white makes valid move
cg.submitMove("H1", "H2");  
// Black king attempts to castle with own rook (illegal, king has moved).
cg.submitMove("E8", "C8"); 
//black king makes a valid move
cg.submitMove("E8", "E7"); 
cout << '\n';
//White king castles with the other white rook (legal move)
cg.submitMove("E1", "C1");  
cout << '\n';
cout << '\n';

//Stalemate checks
cg.loadState("k7/6Q1/8/3K4/8/8/8/8 w  w KQkq");
//White queen moves createing stalemate
cg.submitMove("G7", "C7"); 
cout << '\n';
//Black attempts to move (but can't)
cg.submitMove("A8", "A7"); 
cout << '\n';
cout << '\n';

//check for making a move without loading the game.
ChessGame cg1;
cg.submitMove("E2", "E4");
cout << '\n';


	return 0;
}
