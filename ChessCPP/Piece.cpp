#include "Piece.h"
#include <string>
#include <iostream>


Piece::Piece(char name, Index index, Color color)
{
	if (color == white)
	{
		m_cName = toLower(name);
		m_iDirection = -1;
	}
	else
	{
		m_cName = toUpper(name);
		m_iDirection = 1;
	}

	m_iIndex = index;
	m_cColor = color;
	m_iNumOfMoves = 0;
	m_iValue = 0;
}

bool Piece::isValidMove(Move* move, Piece* board[][8])
{
	MoveStack* allValidMoves = new MoveStack;

	getMoves(allValidMoves, board);

	bool validMove = allValidMoves->hasMove(move);
	delete allValidMoves;

	return validMove;
}

// Virtual fuction to be defined by child piece classes
void Piece::getMoves(MoveStack* moves, Piece* board[][8]) {}

// PAWN

void Pawn::getMoves(MoveStack* moves, Piece* board[][8])
{
	int currentRow;
	int currentCol;
	Index startPos;
	Index endPos;
	int direction;

	for (int i = 1; i < 3; i++)
	{
		currentRow = m_iIndex.m_iRow + (m_iDirection * i);

		if (currentRow < 0 || currentRow > 7)
		{
			break;
		}

		if (board[currentRow][m_iIndex.m_iCol] != nullptr)
		{
			break;
		}

		startPos = m_iIndex;
		endPos = Index(currentRow, m_iIndex.m_iCol);

		moves->addMove(new Move(startPos, endPos));

		if (m_iNumOfMoves > 0)
		{
			break;
		}
	}

	Piece* attackedPiece;

	for (int i = -1; i < 2; i += 2)
	{
		currentRow = m_iIndex.m_iRow + m_iDirection;
		currentCol = m_iIndex.m_iCol + i;

		if (currentCol < 0 || currentCol > 7)
		{
			continue;
		}
		if (currentRow < 0 || currentRow > 7)
		{
			break;
		}

		attackedPiece = board[currentRow][currentCol];

		if (attackedPiece != nullptr && attackedPiece->m_cColor != m_cColor)
		{
			startPos = m_iIndex;
			endPos = Index(currentRow, currentCol);

			moves->addMove(new Move(startPos, endPos, attackedPiece));
		}
	}
}

// ROOK

void Rook::getMoves(MoveStack* moves, Piece* board[][8])
{
	int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

	int row;
	int col;
	Index startPos;
	Index endPos;
	Piece* attackedPiece;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j < 8; j++)
		{
			row = m_iIndex.m_iRow + (directions[i][0] * j);
			col = m_iIndex.m_iCol + (directions[i][1] * j);
			startPos = m_iIndex;
			endPos = Index(row, col);

			if (row < 0 || row > 7 || col < 0 || col > 7)
			{
				break;
			}

			if (board[row][col] != nullptr)
			{
				if (board[row][col]->m_cColor != m_cColor)
				{
					attackedPiece = board[row][col];
					moves->addMove(new Move(startPos, endPos, attackedPiece));
				}

				break;
			}

			moves->addMove(new Move(startPos, endPos));
		}
	}
}

// BISHOP

void Bishop::getMoves(MoveStack* moves, Piece* board[][8])
{
	int directions[4][2] = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

	int row;
	int col;
	Index startPos;
	Index endPos;
	Piece* attackedPiece;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j < 8; j++)
		{
			row = m_iIndex.m_iRow + (directions[i][0] * j);
			col = m_iIndex.m_iCol + (directions[i][1] * j);
			startPos = m_iIndex;
			endPos = Index(row, col);

			if (row < 0 || row > 7 || col < 0 || col > 7)
			{
				break;
			}

			if (board[row][col] != nullptr)
			{
				if (board[row][col]->m_cColor != m_cColor)
				{
					attackedPiece = board[row][col];
					moves->addMove(new Move(startPos, endPos, attackedPiece));
				}

				break;
			}

			moves->addMove(new Move(startPos, endPos));
		}
	}
}

// Knight

void Knight::getMoves(MoveStack* moves, Piece* board[][8])
{
	int directions[8][2] = { {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1} };

	int row;
	int col;
	Index startPos;
	Index endPos;
	Piece* attackedPiece;

	for (int i = 0; i < 8; i++)
	{
		row = m_iIndex.m_iRow + (directions[i][0]);
		col = m_iIndex.m_iCol + (directions[i][1]);
		startPos = m_iIndex;
		endPos = Index(row, col);

		if (row < 0 || row > 7 || col < 0 || col > 7)
		{
			continue;
		}

		if (board[row][col] != nullptr)
		{
			if (board[row][col]->m_cColor != m_cColor)
			{
				attackedPiece = board[row][col];
				moves->addMove(new Move(startPos, endPos, attackedPiece));
			}

			continue;
		}

		moves->addMove(new Move(startPos, endPos));
	}
}

// Queen

void Queen::getMoves(MoveStack* moves, Piece* board[][8])
{
	int directions[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

	int row;
	int col;
	Index startPos;
	Index endPos;
	Piece* attackedPiece;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 1; j < 8; j++)
		{
			row = m_iIndex.m_iRow + (directions[i][0] * j);
			col = m_iIndex.m_iCol + (directions[i][1] * j);
			startPos = m_iIndex;
			endPos = Index(row, col);

			if (row < 0 || row > 7 || col < 0 || col > 7)
			{
				break;
			}

			if (board[row][col] != nullptr)
			{
				if (board[row][col]->m_cColor != m_cColor)
				{
					attackedPiece = board[row][col];
					moves->addMove(new Move(startPos, endPos, attackedPiece));
				}

				break;
			}

			moves->addMove(new Move(startPos, endPos));
		}
	}
}

// King

void King::getMoves(MoveStack* moves, Piece* board[][8])
{
	int directions[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

	int row;
	int col;
	Index startPos;
	Index endPos;
	Piece* attackedPiece;

	for (int i = 0; i < 8; i++)
	{
		row = m_iIndex.m_iRow + (directions[i][0]);
		col = m_iIndex.m_iCol + (directions[i][1]);
		startPos = m_iIndex;
		endPos = Index(row, col);

		if (row < 0 || row > 7 || col < 0 || col > 7)
		{
			break;
		}

		if (board[row][col] != nullptr)
		{
			if (board[row][col]->m_cColor != m_cColor)
			{
				attackedPiece = board[row][col];
				moves->addMove(new Move(startPos, endPos, attackedPiece));
			}

			continue;
		}

		moves->addMove(new Move(startPos, endPos));
	}
}
