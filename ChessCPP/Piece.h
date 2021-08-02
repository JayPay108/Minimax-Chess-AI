#pragma once

#include "MoveStack.h"
#include "PieceSquareTables.h"

class Piece
{
public:
	explicit Piece(char name, Index index, int color);
	bool isValidMove(Move* move, Piece* board[][8]);
	virtual void getMoves(MoveStack* moves, Piece* board[][8]);
	virtual float getPieceSquareValue();

	char m_cName;
	Index m_iIndex;
	int m_cColor;
	int m_iValue;
	int m_iNumOfMoves;
	int m_iDirection;
};

class Pawn : public Piece
{
public:
	using Piece::Piece;
	void getMoves(MoveStack* moves, Piece* board[][8]);
	float getPieceSquareValue();
};

class Rook : public Piece
{
public:
	using Piece::Piece;
	void getMoves(MoveStack* moves, Piece* board[][8]);
	float getPieceSquareValue();
};

class Knight : public Piece
{
public:
	using Piece::Piece;
	void getMoves(MoveStack* moves, Piece* board[][8]);
	float getPieceSquareValue();
};

class Bishop : public Piece
{
public:
	using Piece::Piece;
	void getMoves(MoveStack* moves, Piece* board[][8]);
	float getPieceSquareValue();
};

class Queen : public Piece
{
public:
	using Piece::Piece;
	void getMoves(MoveStack* moves, Piece* board[][8]);
	float getPieceSquareValue();
};

class King : public Piece
{
public:
	using Piece::Piece;
	void getMoves(MoveStack* moves, Piece* board[][8]);
	float getPieceSquareValue();
};
