#include "Board.h"
#include <iostream>
#include <string>
#include <iomanip>

void clearConsole();

int main()
{
	Board board;
	std::string input;
	Move *move = new Move;
	bool undo = false;

	while (true)
	{
		clearConsole();
		board.print();
		std::cout << std::endl;

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
			board.undoMove();
			undo = false;
		}
		else
		{
			board.makeMove(move);
		}
	}

	return 0;
}


void clearConsole()
{
	std::cout << std::string(10, '\n') << std::endl;
}
