#include "Move.h"

Move::Move(Index startIndex, Index endIndex)
{
	m_iStartIndex = startIndex;
	m_iEndIndex = endIndex;
	m_pcAttackedPiece = nullptr;
	m_bPromotion = false;
	m_bCastle = false;

	m_pNext = nullptr;
}

Move::Move(Index startIndex, Index endIndex, Piece *attackedPiece)
{
	m_iStartIndex = startIndex;
	m_iEndIndex = endIndex;
	m_pcAttackedPiece = attackedPiece;
	m_bPromotion = false;
	m_bCastle = false;

	m_pNext = nullptr;
}

bool Move::operator==(Move move2)
{
	return ((m_iStartIndex == move2.m_iStartIndex) && (m_iEndIndex == move2.m_iEndIndex));
}