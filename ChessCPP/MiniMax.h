#pragma once
#include "Board.h"

class MiniMax
{
public:
	MiniMax(int depth);
	Move* getNextMove(Board* board);
	
	int m_iDepth;
	int m_iAlpha;
	int m_iBeta;
	Move m_mBestMove;

private:
	int searchMoves(Board* board, bool maximize, int currentDepth, int alpha, int beta);
};
