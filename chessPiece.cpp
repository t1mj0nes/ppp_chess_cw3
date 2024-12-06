#include "chessPiece.h"

using namespace std;

ChessPiece::ChessPiece(PieceColour BlackOrWhite) : colour(BlackOrWhite)
{}

std::ostream& operator<< ( std::ostream &out, const PieceColour& colour)
{
 if(colour == PieceColour::BLACK){
  out << "BLACK";
 } else {
  out << "WHITE";
 }
 return out;
}


const PieceColour ChessPiece::getPieceColour() const{
    return colour;
    }
