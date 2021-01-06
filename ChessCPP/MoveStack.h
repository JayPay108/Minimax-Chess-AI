#pragma once

#include "Move.h"

class MoveStack
{
public:
	MoveStack();
	~MoveStack();
	bool isEmpty();
	void addMove(Move* move);
	Move* removeMove();
	bool hasMove(Move* move);
	void empty();

	Move* m_pHead;
	int m_iSize;
};
