#include "MiniMax.h"
#include <iostream>
#include <ctime>

MiniMax::MiniMax(int depth)
{
	m_iDepth = depth;

	m_iAlpha = -9999999;
	m_iBeta = 9999999;

	m_mBestMove = nullptr;
	m_iMovesSearched = 0;
	m_fTimeSearched = 0;
}

Move* MiniMax::getNextMove(Board* board)
{
	m_iMovesSearched = 0;
	m_mBestMove = nullptr;

	std::time_t startTime, endTime;
	std::time(&startTime);

	searchMoves(board, true, m_iDepth, -9999999, 9999999);

	std::time(&endTime);
	m_fTimeSearched = endTime - startTime;

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

	if (currentDepth == 0)
	{
		return board->evaluate(board->m_cTurn);
	}

	float boardValue;
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
			m_iMovesSearched += 1;

			board->makeMove(currentMove);

			if (board->isCheck(!board->m_cTurn))
			{
				delete board->undoMove();
				currentMove = moves->removeMove();
				continue;
			}

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
			m_iMovesSearched += 1;

			board->makeMove(currentMove);

			if (board->isCheck(board->m_cTurn))
			{
				delete board->undoMove();
				currentMove = moves->removeMove();
				continue;
			}

			boardValue = searchMoves(board, !maximize, currentDepth - 1, alpha, beta);
			board->undoMove();	// does not need return value, currentMove already last move applied to board

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