#include "Piece.h"

#include <string>


char toLower(char c)
{
	if (c < 65 || c > 90)
	{
		return c;
	}

	return c += 32;
}

char toUpper(char c)
{
	if (c < 97 || c > 122)
	{
		return c;
	}

	return c -= 32;
}

Piece::Piece()
{
	m_cName = '-';
	m_iIndex = Index();
	m_cColor = white;
	m_iValue = 0;
	m_bHasMoved = false;
}

Piece::Piece(char name, Index index, Color color)
{
	if (color == white)
	{
		m_cName = toLower(name);
	}
	else
	{
		m_cName = toUpper(name);
	}

	m_iIndex = index;
	m_cColor = color;
	m_bHasMoved = false;

	setValue();
}

bool Piece::isValidMove(Move *move, Board board)
{
	MoveStack *allValidMoves;

	getMoves(allValidMoves, board);

	bool validMove = allValidMoves->hasMove(move);
	delete allValidMoves;

	return validMove;
}

void Piece::setValue() {}
void Piece::getMoves(MoveStack* moves, Board board) {}

// PAWN
void Pawn::setValue()
{
	m_iValue = 1;
}

void Pawn::getMoves(MoveStack* moves, Board board)
{
	int currentRow;
	int currentCol;
	Index startPos;
	Index endPos;
	int direction;

	if (m_cColor == white)
	{
		direction = -1;
	}
	else
	{
		direction = 1;
	}

	for (int i = 1; i < 3; i++)
	{
		currentRow = m_iIndex.m_iRow + (direction * i);

		if (currentRow < 0 || currentRow > 7)
		{
			break;
		}

		if (board.m_pcBoard[currentRow][m_iIndex.m_iCol].m_cName != '-')
		{
			break;
		}

		startPos = m_iIndex;
		endPos = Index(currentRow, m_iIndex.m_iCol);

		moves->addMove(new Move(startPos, endPos));

		if (m_bHasMoved)
		{
			break;
		}
	}

	Piece attackedPiece;
	Move *move;

	for (int i = -1; i < 2; i += 2)
	{
		currentRow = m_iIndex.m_iRow + direction;
		currentCol = m_iIndex.m_iCol + i;

		if (currentCol < 0 || currentCol > 7)
		{
			continue;
		}
		if (currentRow < 0 || currentRow > 7)
		{
			break;
		}

		attackedPiece = board.m_pcBoard[currentRow][currentCol];

		if (attackedPiece.m_cName != '-' && attackedPiece.m_cColor != m_cColor)
		{
			startPos = m_iIndex;
			endPos = Index(currentRow, currentCol);

			moves->addMove(new Move(startPos, endPos, &attackedPiece));
		}
	}
}

// ROOK
void Rook::setValue()
{
	m_iValue = 5;
}

void Rook::getMoves(MoveStack* moves, Board board)
{
	int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

	int row;
	int col;
	Index startPos;
	Index endPos;
	Piece attackedPiece;

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

			if (board[row][col].m_cName != '-')
			{
				if (board[row][col].m_cColor != m_cColor)
				{
					attackedPiece = board[row][col];
					moves->addMove(new Move(startPos, endPos, &attackedPiece));
				}

				break;
			}

			moves->addMove(new Move(startPos, endPos));
		}
	}
}

// BISHOP
void Bishop::setValue()
{
	m_iValue = 3;
}

void Bishop::getMoves(MoveStack* moves, Board board)
{
	int directions[4][2] = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

	int row;
	int col;
	Index startPos;
	Index endPos;
	Piece attackedPiece;

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

			if (board[row][col].m_cName != '-')
			{
				if (board[row][col].m_cColor != m_cColor)
				{
					attackedPiece = board[row][col];
					moves->addMove(new Move(startPos, endPos, &attackedPiece));
				}

				break;
			}

			moves->addMove(new Move(startPos, endPos));
		}
	}
}

// Knight
void Knight::setValue()
{
	m_iValue = 3;
}

void Knight::getMoves(MoveStack* moves, Board board)
{
	int directions[8][2] = { {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1} };

	int row;
	int col;
	Index startPos;
	Index endPos;
	Piece attackedPiece;

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

		if (board[row][col].m_cName != '-')
		{
			if (board[row][col].m_cColor != m_cColor)
			{
				attackedPiece = board[row][col];
				moves->addMove(new Move(startPos, endPos, &attackedPiece));
			}

			continue;
		}

		moves->addMove(new Move(startPos, endPos));
	}
}

// Queen
void Queen::setValue()
{
	m_iValue = 9;
}

void Queen::getMoves(MoveStack* moves, Board board)
{
	int directions[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

	int row;
	int col;
	Index startPos;
	Index endPos;
	Piece attackedPiece;

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

			if (board[row][col].m_cName != '-')
			{
				if (board[row][col].m_cColor != m_cColor)
				{
					attackedPiece = board[row][col];
					moves->addMove(new Move(startPos, endPos, &attackedPiece));
				}

				break;
			}

			moves->addMove(new Move(startPos, endPos));
		}
	}
}

// King
void King::setValue()
{
	m_iValue = 3;
}

void King::getMoves(MoveStack* moves, Board board)
{
	int directions[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

	int row;
	int col;
	Index startPos;
	Index endPos;
	Piece attackedPiece;

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

		if (board[row][col].m_cName != '-')
		{
			if (board[row][col].m_cColor != m_cColor)
			{
				attackedPiece = board[row][col];
				moves->addMove(new Move(startPos, endPos, &attackedPiece));
			}

			continue;
		}

		moves->addMove(new Move(startPos, endPos));
	}
}

