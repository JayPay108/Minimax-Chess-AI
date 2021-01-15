#include "Board.h"
#include "MiniMax.h"
#include <iostream>
#include <string>
#include <iomanip>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

void clearConsole();

int main()
{
	Board board;
	MiniMax minimax(DEPTH);
	std::string input;
	Move *move = new Move;
	bool undo = false;

	for (int i = 1; true; i++)
	{
		std::cout << std::endl << "Starting " << i << std::endl;
		std::cout << "Move history size: " << board.m_msMoveHistory.m_iSize << std::endl;
		move = minimax.getNextMove(&board);
		std::cout << "Done searching for moves for " << i << std::endl;
	}

	while (true)
	{
		clearConsole();
		board.print();
		std::cout << std::endl << "Board evaluation = " << board.evaluate() << std::endl; // DEBUG?

		do
		{
			std::cout << "Enter your move: ";
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
			undo = false;
		}
		else
		{
			board.makeMove(move);

			board.swapTurn();
			
			std::cout << "beep boop bop" << std::endl; // frick you this is how i debug
			move = new Move();
			move = minimax.getNextMove(&board);
			std::cout << "row: " << move->m_iStartIndex.m_iRow << ", col: " << move->m_iStartIndex.m_iCol << std::endl
					  << "row: " << move->m_iEndIndex.m_iRow << ", col: " << move->m_iEndIndex.m_iCol << std::endl;
			board.makeMove(move);
			
			board.swapTurn();
		}
	}

	return 0;
}


void clearConsole()
{
	std::cout << std::string(20, '\n') << std::endl;
}
