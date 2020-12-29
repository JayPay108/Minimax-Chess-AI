#include "Board.h"
#include "Piece.h"

Board::Board()
{
	for (int row = 0; row < 7; row++)
	{
		m_pcBoard[row] = new Piece[8];

		for (int col = 0; col < 7; col++)
		{
			m_pcBoard[row][col] = Piece('-', Index(row, col), white);
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
	// Apply move to board
}

bool Board::undoMove()
{
	// Undo last move in move history, remove from stack
}

Piece *Board::operator[](int row)
{
	return m_pcBoard[row];
}