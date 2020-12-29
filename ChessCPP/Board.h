#pragma once

class Board
{
public:
	Board();
	void print();
	void makeMove(Move* move);
	bool undoMove();

	Piece **m_pcBoard;
	Color m_cTurn;
	MoveStack m_msMoveHistory;
};