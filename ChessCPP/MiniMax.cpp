#include "MiniMax.h"
#include <iostream>

MiniMax::MiniMax(int depth)
{
	m_iDepth = depth;

	m_iAlpha = -9999999;
	m_iBeta = 9999999;
}

Move* MiniMax::getNextMove(Board* board)
{
	m_mBestMove = new Move();
	searchMoves(board, true, m_iDepth, -9999999, 9999999);
	return m_mBestMove;
}

int MiniMax::searchMoves(Board* board, bool maximize, int currentDepth, int alpha, int beta)
{
	if (board->isCheckMate(!board->m_cTurn))
	{
		return 9999999;
	}
	if (board->isCheckMate(board->m_cTurn))
	{
		return -9999999;
	}

	if (currentDepth == 0)	// TODO: end when game is over
	{
		return board->evaluate(board->m_cTurn);
	}

	int boardValue;
	Move* currentMove;
	Move bestMove;

	if (!maximize)
	{
		int minValue = 9999999;
		
		MoveStack* moves = new MoveStack;

		board->getMoves(!board->m_cTurn, moves);

		currentMove = moves->removeMove();
		while (currentMove != nullptr)
		{
			board->makeMove(currentMove);
			boardValue = searchMoves(board, !maximize, currentDepth - 1, alpha, beta);
			delete board->undoMove();

			if (boardValue < minValue)
			{
				minValue = boardValue;
			}

			if (boardValue < beta)
			{
				beta = boardValue;
			}

			if (beta <= alpha)
			{
				break;
			}

			currentMove = moves->removeMove();
		}
		
		return minValue;
	}
	else
	{
		int maxValue = -9999999;

		MoveStack* moves = new MoveStack;
		board->getMoves(board->m_cTurn, moves);

		currentMove = moves->removeMove();
		while (currentMove != nullptr)
		{
			board->makeMove(currentMove);
			boardValue = searchMoves(board, !maximize, currentDepth - 1, alpha, beta);
			currentMove = board->undoMove();

			if (boardValue > maxValue)
			{
				maxValue = boardValue;

				if (currentDepth == DEPTH)
				{
					delete m_mBestMove;
					m_mBestMove = new Move();
					m_mBestMove = currentMove;
				}
				else
				{
					delete currentMove;
				}
			}
			else
			{
				delete currentMove;
			}

			if (boardValue > alpha)
			{
				alpha = boardValue;
			}

			if (beta <= alpha)
			{
				break;
			}

			currentMove = moves->removeMove();
		}

		return maxValue;
	}
}