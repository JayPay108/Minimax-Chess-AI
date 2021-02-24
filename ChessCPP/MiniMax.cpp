#include "MiniMax.h"
#include <iostream>

MiniMax::MiniMax(int depth)
{
	m_iDepth = depth;

	m_iAlpha = -9999;
	m_iBeta = 9999;
}

Move* MiniMax::getNextMove(Board* board)
{
	m_mBestMove = new Move();
	searchMoves(board, true, m_iDepth, -9999, 9999);
	return m_mBestMove;
}

int MiniMax::searchMoves(Board* board, bool maximize, int currentDepth, int alpha, int beta)
{
	if (currentDepth == 0)	// TODO: end when game is over
	{
		return board->evaluate();
	}

	int boardValue;
	Move* currentMove;
	Move bestMove;

	if (!maximize)
	{
		board->swapTurn();
		int minValue = 9999;
		
		MoveStack* moves = new MoveStack;
		board->getMoves(moves);

		currentMove = moves->removeMove();
		while (currentMove != nullptr)
		{
			board->makeMove(currentMove);
			boardValue = searchMoves(board, !maximize, currentDepth - 1, -9999, 9999);
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
		
		board->swapTurn();
		return minValue;
	}
	else
	{
		int maxValue = -9999;

		MoveStack* moves = new MoveStack;
		board->getMoves(moves);

		currentMove = moves->removeMove();
		while (currentMove != nullptr)
		{
			board->makeMove(currentMove);
			boardValue = searchMoves(board, !maximize, currentDepth - 1, -9999, 9999);
			currentMove = board->undoMove();

			//debug
			if (currentDepth == DEPTH)
			{
				std::cout << std::endl << boardValue << " - ";
			}

			if (boardValue > maxValue)
			{
				maxValue = boardValue;

				if (currentDepth == DEPTH)
				{
					delete m_mBestMove;
					m_mBestMove = new Move();
					m_mBestMove = currentMove;
					std::cout << currentMove->toString(); // debug
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