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
	void getMoves(int color, MoveStack* moves);
	bool isCheck(int checkColor);
	bool isCheckMate(int checkColor);
	int evaluate(int evaluateForColor);

	Piece* m_pcBoard[8][8];
	int m_cTurn;
	MoveStack m_msMoveHistory;

private:
	void addPiece(char name, Index index, int color);
};