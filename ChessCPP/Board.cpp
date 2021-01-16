#include "Board.h"

#include <fstream>
#include <iostream>

Board::Board()
{
	std::ifstream inFile;
	inFile.open("StartingBoard.txt");

	char pieceChar;
	Color pieceColor;
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			inFile >> pieceChar;

			if (pieceChar == '-')
			{
				m_pcBoard[row][col] = nullptr;
				continue;
			}

			if (isupper(pieceChar))
			{
				pieceColor = black;
			}
			else
			{
				pieceColor = white;
			}

			addPiece(pieceChar, Index(row, col), pieceColor);
		}
	}

	inFile.close();

	m_cTurn = white;
}

void Board::print()
{
	Piece* currentPiece;

	std::cout << "    a b c d e f g h" << std::endl
		<< "   -----------------" << std::endl;

	for (int row = 0; row < 8; row++)
	{
		std::cout << (8 - row) << " | ";

		for (int col = 0; col < 8; col++)
		{
			currentPiece = m_pcBoard[row][col];

			if ((currentPiece) == nullptr)
			{
				std::cout << '-';
			}
			else
			{
				std::cout << currentPiece->m_cName;
			}

			std::cout << ' ';
		}

		std::cout << "| " << (8 - row) << std::endl;
	}

	std::cout << "   -----------------" << std::endl
		<< "    a b c d e f g h" << std::endl;
}

void Board::swapTurn()
{
	if (m_cTurn == white)
	{
		m_cTurn = black;
	}
	else
	{
		m_cTurn = white;
	}
}

void Board::makeMove(Move* move)
{
	Piece* movedPiece = m_pcBoard[move->m_iStartIndex.m_iRow][move->m_iStartIndex.m_iCol];

	m_pcBoard[move->m_iStartIndex.m_iRow][move->m_iStartIndex.m_iCol] = nullptr;
	m_pcBoard[move->m_iEndIndex.m_iRow][move->m_iEndIndex.m_iCol] = movedPiece;

	if (movedPiece == nullptr)
	{
		std::cout << move->m_iStartIndex.m_iRow << "   " << move->m_iStartIndex.m_iCol << std::endl;
	}

	movedPiece->m_iIndex.m_iRow = move->m_iEndIndex.m_iRow;
	movedPiece->m_iIndex.m_iCol = move->m_iEndIndex.m_iCol;


	movedPiece->m_iNumOfMoves++;

	m_msMoveHistory.addMove(move);
}

Move* Board::undoMove()
{
	Move* lastMove = m_msMoveHistory.removeMove();

	if (lastMove == nullptr)
	{
		return nullptr;
	}

	Piece* movedPiece = m_pcBoard[lastMove->m_iEndIndex.m_iRow][lastMove->m_iEndIndex.m_iCol];

	m_pcBoard[lastMove->m_iStartIndex.m_iRow][lastMove->m_iStartIndex.m_iCol] = movedPiece;
	m_pcBoard[lastMove->m_iEndIndex.m_iRow][lastMove->m_iEndIndex.m_iCol] = lastMove->m_pcAttackedPiece;

	movedPiece->m_iIndex.m_iRow = lastMove->m_iStartIndex.m_iRow;
	movedPiece->m_iIndex.m_iCol = lastMove->m_iStartIndex.m_iCol;

	movedPiece->m_iNumOfMoves--;

	return lastMove;
}

bool Board::isValidMove(Move *move)
{
	Piece* piece = m_pcBoard[move->m_iStartIndex.m_iRow][move->m_iStartIndex.m_iCol];

	if (piece->m_cColor != m_cTurn)
	{
		return false;
	}

	return piece->isValidMove(move, m_pcBoard);
}

void Board::getMoves(MoveStack* moves)
{
	Piece* piece;
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			piece = m_pcBoard[row][col];

			if (piece == nullptr || piece->m_cColor != m_cTurn)
			{
				continue;
			}

			piece->getMoves(moves, m_pcBoard);
		}
	}
}

int Board::evaluate()
{
	int boardValue = 0;

	// Summing up all the piece values
	int pieceValues = 0;

	Piece* piece;
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			piece = m_pcBoard[row][col];

			if (piece == nullptr)
			{
				continue;
			}

			if (piece->m_cColor == m_cTurn)
			{
				pieceValues += piece->m_iValue;
			}
			else
			{
				pieceValues -= piece->m_iValue;
			}
		}
	}
	
	int defense = (pieceValues * DEFENSE);
	boardValue += defense;

	// Summing up all valid moves
	MoveStack* moves = new MoveStack;
	int numOfMoves;
	int enemyNumOfMoves;

	getMoves(moves);
	numOfMoves = moves->m_iSize;
	swapTurn();

	delete moves; // THE LACK OF THIS LINE CAUSED ME A WEEK OF STRESS
	moves = new MoveStack;
	getMoves(moves);
	enemyNumOfMoves = moves->m_iSize;
	swapTurn();

	int agresiveness = ((numOfMoves - enemyNumOfMoves) * AGRESSIVENESS);
	boardValue += agresiveness;
	delete moves;

	// Pawn stuff
	int blockedPawns = 0;
	int enemyBlockedPawns = 0;

	int pawnsPerRow[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int enemyPawnsPerRow[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	int nextRow;
	for (int col = 0; col < 8; col++)
	{
		for (int row = 0; row < 8; row++)
		{
			piece = m_pcBoard[row][col];

			if (piece != nullptr && piece->m_iValue == 1)
			{
				if (piece->m_cColor == m_cTurn)
				{
					pawnsPerRow[row]++;

					nextRow = row + piece->m_iDirection;
					if (m_pcBoard[nextRow][col] != nullptr)
					{
						blockedPawns++;
					}
				}
				else
				{
					enemyPawnsPerRow[row]++;

					nextRow = row + piece->m_iDirection;
					if (m_pcBoard[nextRow][col] != nullptr)
					{
						enemyBlockedPawns++;
					}
				}
			}
		}
	}

	int isolatedPawns = 0;
	int enemyIsolatedPawns = 0;

	int doubledPawns = 0;
	int enemyDoubledPawns = 0;

	for (int row = 0; row < 8; row++)
	{
		if (pawnsPerRow[row] > 1)
		{
			doubledPawns++;
		}
		if (enemyPawnsPerRow[row] > 1)
		{
			enemyDoubledPawns++;
		}

		if ((row == 0 || pawnsPerRow[row - 1] == 0) && (row == 7 || pawnsPerRow[row + 1] == 0))
		{
			isolatedPawns++;
		}
		if ((row == 0 || enemyPawnsPerRow[row - 1] == 0) && (row == 7 || enemyPawnsPerRow[row + 1] == 0))
		{
			enemyIsolatedPawns++;
		}
	}

	int pawnStuff = ((isolatedPawns - enemyIsolatedPawns) + (doubledPawns - enemyDoubledPawns) + (blockedPawns - enemyBlockedPawns)) * PAWNSTUFF;
	boardValue -= pawnStuff;

	return boardValue;
}

void Board::addPiece(char name, Index index, Color color)
{
	name = toLower(name);

	switch (name)
	{
	case 'p':
		m_pcBoard[index.m_iRow][index.m_iCol] = new Pawn(name, index, color);
		m_pcBoard[index.m_iRow][index.m_iCol]->m_iValue = 1;
		break;
	case 'r':
		m_pcBoard[index.m_iRow][index.m_iCol] = new Rook(name, index, color);
		m_pcBoard[index.m_iRow][index.m_iCol]->m_iValue = 5;
		break;
	case 'n':
		m_pcBoard[index.m_iRow][index.m_iCol] = new Knight(name, index, color);
		m_pcBoard[index.m_iRow][index.m_iCol]->m_iValue = 3;
		break;
	case 'b':
		m_pcBoard[index.m_iRow][index.m_iCol] = new Bishop(name, index, color);
		m_pcBoard[index.m_iRow][index.m_iCol]->m_iValue = 3;
		break;
	case 'q':
		m_pcBoard[index.m_iRow][index.m_iCol] = new Queen(name, index, color);
		m_pcBoard[index.m_iRow][index.m_iCol]->m_iValue = 9;
		break;
	case 'k':
		m_pcBoard[index.m_iRow][index.m_iCol] = new King(name, index, color);
		m_pcBoard[index.m_iRow][index.m_iCol]->m_iValue = 999;
		break;
	}
}