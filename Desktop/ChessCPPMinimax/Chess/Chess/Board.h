#pragma once

#include "Piece.h"

class Board
{
public:
	Board();
	void print();
	void makeMove(Move* move);
	bool undoMove();
	bool isValidMove(Move* move);

	Piece* m_pcBoard[8][8];
	Color m_cTurn;
	MoveStack m_msMoveHistory;

private:
	void addPiece(char name, Index index, Color color);
};