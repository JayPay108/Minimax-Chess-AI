#include "Board.h"

Board::Board()
{
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			m_pcBoard[row][col] = nullptr;
		}
	}

	m_cTurn = white;
}

void Board::print()
{
	// print board
}

void Board::makeMove(Move* move)
{
	Piece movedPiece = m_pcBoard[move->m_iStartIndex.m_iRow][move->m_iStartIndex.m_iCol];

	m_pcBoard[move->m_iStartIndex.m_iRow][move->m_iStartIndex.m_iCol] = Piece();
	m_pcBoard[move->m_iEndIndex.m_iRow][move->m_iEndIndex.m_iCol] = movedPiece;

	movedPiece.m_iIndex.m_iRow = move->m_iEndIndex.m_iRow;
	movedPiece.m_iIndex.m_iCol = move->m_iEndIndex.m_iCol;

	movedPiece.m_bHasMoved = true;

	m_msMoveHistory.addMove(move);
}

bool Board::undoMove()
{
	// Undo last move in move history, remove from stack
}