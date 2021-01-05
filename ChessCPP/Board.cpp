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

bool Board::undoMove()
{
	if (m_msMoveHistory.isEmpty())
	{
		return false;
	}

	Move* lastMove = m_msMoveHistory.removeMove();
	Piece* movedPiece = m_pcBoard[lastMove->m_iEndIndex.m_iRow][lastMove->m_iEndIndex.m_iCol];

	m_pcBoard[lastMove->m_iStartIndex.m_iRow][lastMove->m_iStartIndex.m_iCol] = movedPiece;
	m_pcBoard[lastMove->m_iEndIndex.m_iRow][lastMove->m_iEndIndex.m_iCol] = lastMove->m_pcAttackedPiece;

	movedPiece->m_iIndex.m_iRow = lastMove->m_iStartIndex.m_iRow;
	movedPiece->m_iIndex.m_iCol = lastMove->m_iStartIndex.m_iCol;

	movedPiece->m_iNumOfMoves--;

	delete lastMove;
	return true;
}

bool Board::isValidMove(Move *move)
{
	Piece* piece = m_pcBoard[move->m_iStartIndex.m_iRow][move->m_iStartIndex.m_iCol];

	return piece->isValidMove(move, m_pcBoard);
}

void Board::addPiece(char name, Index index, Color color)
{
	switch (name)
	{
	case 'P':
	case 'p':
		m_pcBoard[index.m_iRow][index.m_iCol] = new Pawn(name, index, color);
		break;
	case 'R':
	case 'r':
		m_pcBoard[index.m_iRow][index.m_iCol] = new Rook(name, index, color);
		break;
	case 'N':
	case 'n':
		m_pcBoard[index.m_iRow][index.m_iCol] = new Knight(name, index, color);
		break;
	case 'B':
	case 'b':
		m_pcBoard[index.m_iRow][index.m_iCol] = new Bishop(name, index, color);
		break;
	case 'Q':
	case 'q':
		m_pcBoard[index.m_iRow][index.m_iCol] = new Queen(name, index, color);
		break;
	case 'K':
	case 'k':
		m_pcBoard[index.m_iRow][index.m_iCol] = new King(name, index, color);
		break;
	}
}