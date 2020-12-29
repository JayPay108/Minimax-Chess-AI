#pragma once

#include "Index.h"
#include "Piece.h"

class Move
{
public:
	Move(Index startIndex, Index endIndex);
	Move(Index startIndex, Index endIndex, Piece *m_pcAttackedPiece);
	bool operator==(Move move2);

	Index m_iStartIndex;
	Index m_iEndIndex;
	Piece *m_pcAttackedPiece;
	bool m_bPromotion;
	bool m_bCastle;

	Move* m_pNext;
};