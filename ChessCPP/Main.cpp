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

	while (true)
	{
		clearConsole();

		lastMove = board.m_msMoveHistory.m_pHead;

		std::cout << "Board evaluation for you: " << board.evaluate() << std::endl;
		if (lastMove != nullptr)
		{
			std::cout << lastMove->toString() << std::endl;
		}

		board.print();

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
			
			move = new Move();
			move = minimax.getNextMove(&board);
			std::cout << "here" << std::endl; // debug
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
