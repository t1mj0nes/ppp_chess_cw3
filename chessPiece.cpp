/**
 * @file chesPiece.cpp
 * 
 * @brief Implementation of the ChessPiece class, which serves as a 
 *        base class for all chess pieces. It provides common functionality
 *        such as colour management.
 */

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
