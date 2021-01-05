#include "Board.h"
#include <iostream>
#include <string>
#include <iomanip>

char lower(char c);
std::string toLower(std::string string);
int toNum(char c);
Move toMove(std::string input);

int main()
{
	Board board;
	std::string input;
	Move *move = new Move;
	bool undo = false;

	while (true)
	{
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
			board.undoMove();
			undo = false;
		}
		else
		{
			board.makeMove(move);
		}
	}

	while (true) {} // will crash as soon as program finishes????????????????
	return 0;
}
