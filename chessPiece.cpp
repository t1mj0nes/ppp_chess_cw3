#include "chessPiece.h"
#include "colour.h"

using namespace std;

ChessPiece::ChessPiece(Colour _pieceColour) : pieceColour(_pieceColour)
{}

ChessPiece::~ChessPiece(){}


const Colour ChessPiece::getPieceColour() const{
    return pieceColour;
    }
