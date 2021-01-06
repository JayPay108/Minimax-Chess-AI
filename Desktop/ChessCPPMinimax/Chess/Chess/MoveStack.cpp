#include "MoveStack.h"

MoveStack::MoveStack()
{
	m_pHead = nullptr;
}

MoveStack::~MoveStack()
{
	Move* removedMove = removeMove();

	while (removedMove != nullptr)
	{
		delete removedMove;
		removedMove = removeMove();
	}
}

bool MoveStack::isEmpty()
{
	return (m_pHead == nullptr);
}

void MoveStack::addMove(Move* move)
{
	move->m_pNext = m_pHead;
	m_pHead = move;
}

Move* MoveStack::removeMove()
{
	Move* removedMove = m_pHead;

	if (m_pHead != nullptr)
	{
		m_pHead = m_pHead->m_pNext;
	}

	return removedMove;
}

bool MoveStack::hasMove(Move* move)
{
	Move* location = m_pHead;

	while (location != nullptr)
	{
		if (*location == *move)
		{
			return true;
		}

		location = location->m_pNext;
	}

	return false;
}