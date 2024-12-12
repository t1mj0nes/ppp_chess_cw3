#include "chessPiece.h"
#include "colour.h"

using namespace std;

/**
 * chessPice constructor
 */
ChessPiece::ChessPiece(Colour _pieceColour) : pieceColour(_pieceColour)
{}

/**
 * chessPice destructor
 */
ChessPiece::~ChessPiece(){}

/**
 * chessPice getter, returns the colour of a piece.
 */
const Colour ChessPiece::getPieceColour() const{
    return pieceColour;
    }
