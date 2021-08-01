#pragma once

#include "MoveStack.h"

class Piece
{
public:
	explicit Piece(char name, Index index, int color);
	bool isValidMove(Move* move, Piece* board[][8]);
	virtual void getMoves(MoveStack* moves, Piece* board[][8]);

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
};

class Rook : public Piece
{
public:
	using Piece::Piece;
	void getMoves(MoveStack* moves, Piece* board[][8]);
};

class Knight : public Piece
{
public:
	using Piece::Piece;
	void getMoves(MoveStack* moves, Piece* board[][8]);
};

class Bishop : public Piece
{
public:
	using Piece::Piece;
	void getMoves(MoveStack* moves, Piece* board[][8]);
};

class Queen : public Piece
{
public:
	using Piece::Piece;
	void getMoves(MoveStack* moves, Piece* board[][8]);
};

class King : public Piece
{
public:
	using Piece::Piece;
	void getMoves(MoveStack* moves, Piece* board[][8]);
};
