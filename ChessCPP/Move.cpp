#include "Move.h"

Move::Move()
{
	m_iStartIndex = Index();
	m_iEndIndex = Index();
	m_pcAttackedPiece = nullptr;
	m_bPromotion = false;
	m_bCastle = false;

	m_pNext = nullptr;
}

Move::Move(Index startIndex, Index endIndex)
{
	m_iStartIndex = startIndex;
	m_iEndIndex = endIndex;
	m_pcAttackedPiece = nullptr;
	m_bPromotion = false;
	m_bCastle = false;

	m_pNext = nullptr;
}

Move::Move(Index startIndex, Index endIndex, Piece* attackedPiece)
{
	m_iStartIndex = startIndex;
	m_iEndIndex = endIndex;
	m_pcAttackedPiece = attackedPiece;
	m_bPromotion = false;
	m_bCastle = false;

	m_pNext = nullptr;
}

bool Move::generateMove(std::string input, Piece* board[][8])
{
	if (input.length() < 4)
	{
		return false;
	}

	input[0] = toLower(input[0]);
	input[2] = toLower(input[2]);

	if (input[0] < 97 || input[0] > 104 || input[2] < 97 || input[2] > 104 ||
		input[1] < 49 || input[1] > 56 || input[3] < 49 || input[3] > 56)
	{
		return false;
	}

	m_iStartIndex = Index(-input[1] + 56, input[0] - 97);
	m_iEndIndex = Index(-input[3] + 56, input[2] - 97);

	m_pcAttackedPiece = board[m_iEndIndex.m_iRow][m_iEndIndex.m_iCol];

	return true;
}

std::string Move::toString()
{
	std::string moveString = "----";

	moveString[0] = m_iStartIndex.m_iCol + 97;
	moveString[1] = 56 - m_iStartIndex.m_iRow;

	moveString[2] = m_iEndIndex.m_iCol + 97;
	moveString[3] = 56 - m_iEndIndex.m_iRow;

	return moveString;
}

bool Move::operator==(Move move2)
{
	return ((m_iStartIndex == move2.m_iStartIndex) && (m_iEndIndex == move2.m_iEndIndex));
}