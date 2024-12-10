#include "chessPiece.h"
#include "colour.h"

using namespace std;

ChessPiece::ChessPiece(Colour _pieceColour) : pieceColour(_pieceColour)
{}

const Colour ChessPiece::getPieceColour() const{
    return pieceColour;
    }
