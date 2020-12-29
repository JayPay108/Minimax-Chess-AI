#pragma once

/*
MoveStack will, in most cases, be used as a pointer to easily clear it and pass trough functions
Piece needs an isValidMove function to pass into the attempted move instead of a getAllMoves function
A getAllMoves function is still needed, but only to pass into the getAllMoves board function...
*/

#include "MoveStack.h"
#include "Board.h"

enum Color{white, black};

class Piece
{
public:
	Piece();
	Piece(char name, Index index, Color color);
	bool isValidMove(Move *move, Board board);
	virtual void setValue();
	virtual void getMoves(MoveStack *moves, Board board);

	char m_cName;
	Index m_iIndex;
	Color m_cColor;
	int m_iValue;
	bool m_bHasMoved;
};

class Pawn : public Piece
{
public:
	void setValue();
	void getMoves(MoveStack *moves, Board board);
};

class Rook : public Piece
{
public:
	void setValue();
	void getMoves(MoveStack* moves, Board board);
};

class Knight : public Piece
{
public:
	void setValue();
	void getMoves(MoveStack* moves, Board board);
};

class Bishop : public Piece
{
public:
	void setValue();
	void getMoves(MoveStack* moves, Board board);
};

class Queen : public Piece
{
public:
	void setValue();
	void getMoves(MoveStack* moves, Board board);
};

class King : public Piece
{
public:
	void setValue();
	void getMoves(MoveStack* moves, Board board);
};