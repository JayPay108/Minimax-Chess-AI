#include "Board.h"

#include <fstream>
#include <iostream>

Board::Board()
{
	std::ifstream inFile;
	inFile.open("StartingBoard.txt");

	char pieceChar;
	int pieceColor;
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
				pieceColor = 0;
			}
			else
			{
				pieceColor = 1;
			}

			addPiece(pieceChar, Index(row, col), pieceColor);
		}
	}

	inFile.close();

	m_cTurn = 1;
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
	m_cTurn = !m_cTurn;
}

void Board::makeMove(Move* move)
{
	Piece* movedPiece = m_pcBoard[move->m_iStartIndex.m_iRow][move->m_iStartIndex.m_iCol];

	m_pcBoard[move->m_iStartIndex.m_iRow][move->m_iStartIndex.m_iCol] = nullptr;
	m_pcBoard[move->m_iEndIndex.m_iRow][move->m_iEndIndex.m_iCol] = movedPiece;

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

	if (piece == nullptr)
	{
		return false;
	}

	if (piece->m_cColor != m_cTurn)
	{
		return false;
	}

	if (!piece->isValidMove(move, m_pcBoard))
	{
		return false;
	}

	makeMove(move);
	if (isCheck(m_cTurn))
	{
		undoMove();
		return false;
	}
	undoMove();

	return true;
}

void Board::getMoves(int color, MoveStack* moves)
{
	Piece* piece;
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			piece = m_pcBoard[row][col];

			if (piece == nullptr || piece->m_cColor != color)
			{
				continue;
			}

			piece->getMoves(moves, m_pcBoard);
		}
	}
}

bool Board::isCheck(int checkColor)
{
	MoveStack* moves = new MoveStack;
	getMoves(!checkColor, moves);

	Index attackingIndex;
	Move* currentMove = moves->removeMove();
	while (currentMove != nullptr)
	{
		if (currentMove->m_pcAttackedPiece != nullptr)
		{
			if (checkColor == 1 && toLower(currentMove->m_pcAttackedPiece->m_cName) == 'k')
			{
				delete currentMove;
				delete moves;
				return true;
			}
			if (checkColor == 0 && currentMove->m_pcAttackedPiece->m_cName == 'K')
			{
				delete currentMove;
				delete moves;
				return true;
			}
		}

		delete currentMove;
		currentMove = moves->removeMove();
	}
	delete moves;
	return false;
}

bool Board::isCheckMate(int checkColor)
{
	if (!isCheck(checkColor))
	{
		return false;
	}

	MoveStack* moves = new MoveStack;
	getMoves(checkColor, moves);

	Move* currentMove = moves->removeMove();
	while (currentMove != nullptr)
	{
		makeMove(currentMove);
		if (!isCheck(checkColor))
		{
			undoMove();
			delete currentMove;
			delete moves;
			return false;
		}
		undoMove();

		delete currentMove;
		currentMove = moves->removeMove();
	}
	delete moves;
	return true;
}

int Board::evaluate(int evaluateForColor)
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

			if (piece->m_cColor == evaluateForColor)
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

	getMoves(evaluateForColor, moves);
	numOfMoves = moves->m_iSize;

	delete moves; // stupid me forgot this line...
	moves = new MoveStack;
	getMoves(!evaluateForColor, moves);
	enemyNumOfMoves = moves->m_iSize;

	int agressiveness = ((numOfMoves - enemyNumOfMoves) * AGRESSIVENESS);
	boardValue += agressiveness;
	delete moves;

	// Pawn stuff
	int blockedPawns = 0;
	int enemyBlockedPawns = 0;

	int pawnsPerCol[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int enemyPawnsPerCol[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	int nextRow;
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			piece = m_pcBoard[row][col];

			if (piece != nullptr && piece->m_iValue == 1)
			{
				if (piece->m_cColor == evaluateForColor)
				{
					pawnsPerCol[col]++;

					nextRow = row + piece->m_iDirection;
					if (m_pcBoard[nextRow][col] != nullptr)
					{
						blockedPawns++;
					}
				}
				else
				{
					enemyPawnsPerCol[col]++;

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
	
	for (int col = 0; col < 8; col++)
	{
		if (pawnsPerCol[col] > 1)
		{
			doubledPawns++;
		}
		if (enemyPawnsPerCol[col] > 1)
		{
			enemyDoubledPawns++;
		}

		if (pawnsPerCol[col] > 0 && (col == 0 || pawnsPerCol[col - 1] == 0) && (col == 7 || pawnsPerCol[col + 1] == 0))
		{
			isolatedPawns++;
		}
		if (enemyPawnsPerCol[col] > 0 && (col == 0 || enemyPawnsPerCol[col - 1] == 0) && (col == 7 || enemyPawnsPerCol[col + 1] == 0))
		{
			enemyIsolatedPawns++;
		}
	}

	int pawnStuff = ((isolatedPawns - enemyIsolatedPawns) + (doubledPawns - enemyDoubledPawns) + (blockedPawns - enemyBlockedPawns)) * PAWNSTUFF;
	boardValue -= pawnStuff;

	return boardValue;
}

void Board::addPiece(char name, Index index, int color)
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