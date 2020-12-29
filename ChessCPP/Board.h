#pragma once
#include "Piece.h"

class Board
{
public:
	Board();
	void print();
	void makeMove(Move* move);
	bool undoMove();

	Piece *m_pcBoard[8][8];
	Color m_cTurn;
	MoveStack m_msMoveHistory;
};