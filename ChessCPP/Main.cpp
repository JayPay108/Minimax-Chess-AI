#include "Board.h"
#include "MiniMax.h"
#include <iostream>
#include <string>
#include <iomanip>

void clearConsole();

int main()
{
	Board board;
	MiniMax minimax(DEPTH);
	std::string input;
	Move* move = new Move;
	Move* lastMove;
	bool undo = false;
	bool gameOver = false;

	while (true)
	{
		clearConsole();

		if (board.m_msMoveHistory.m_iSize > 0)
		{
			std::cout << "Craig's move: " << board.m_msMoveHistory.m_pHead->toString() << std::endl;

			if (board.isCheckMate(board.m_cTurn))
			{
				std::cout << "Checkmate! You lose!" << std::endl;
				gameOver = true;
			}
			else if (board.isCheck(board.m_cTurn))
			{
				std::cout << "You are in check!" << std::endl;
			}

			std::cout << std::endl;
		}

		// std::cout << "Board value: " << board.evaluate() << std::endl << std::endl << std::endl;

		board.print();

		if (gameOver)
		{
			return 0;
		}

		do
		{
			std::cout << std::endl << "Enter your move: ";
			std::getline(std::cin, input);

			input = toLower(input);
			if (input == "undo" || input == "z")
			{
				undo = true;
				break;
			}

			move = new Move;
			if (!move->generateMove(input, board.m_pcBoard))
			{
				continue;
			}

		} while (!board.isValidMove(move));

		if (undo)
		{
			delete board.undoMove();
			delete board.undoMove();
			undo = false;
		}
		else
		{
			board.makeMove(move);
			
			board.swapTurn();
			std::cout << "Craig is thinking...";
			
			move = new Move();
			move = minimax.getNextMove(&board);
			board.makeMove(move);
			board.swapTurn();

			for (int i = 0; i < 20; i++)
			{
				std::cout << '\b' << ' ' << '\b';
			}
			
		}
	}

	return 0;
}
using namespace std;

void clearConsole()
{	
	std::cout << std::string(20, '\n') << std::endl;
}
