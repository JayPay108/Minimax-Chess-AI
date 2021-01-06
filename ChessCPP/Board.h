#pragma once

#include "Piece.h"
#include "Config.h"

class Board
{
public:
	Board();
	void print();
	void swapTurn();
	void makeMove(Move* move);
	Move* undoMove();
	bool isValidMove(Move* move);
	void getMoves(MoveStack* moves);
	int evaluate();

	Piece* m_pcBoard[8][8];
	Color m_cTurn;
	MoveStack m_msMoveHistory;

private:
	void addPiece(char name, Index index, Color color);
};