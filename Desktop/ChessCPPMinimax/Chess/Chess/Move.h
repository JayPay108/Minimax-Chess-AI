#pragma once
#include <string>
#include "Index.h"
#include "charFunctions.h"

class Piece; // Dummy class to let compiler know it exists

class Move
{
public:
	Move();
	Move(Index startIndex, Index endIndex);
	Move(Index startIndex, Index endIndex, Piece* m_pcAttackedPiece);
	bool generateMove(std::string input); // Constructor for player input string (example input: "b1a3")
	bool operator==(Move move2);

	Index m_iStartIndex;
	Index m_iEndIndex;
	Piece* m_pcAttackedPiece;
	bool m_bPromotion;
	bool m_bCastle;

	Move* m_pNext;
};
