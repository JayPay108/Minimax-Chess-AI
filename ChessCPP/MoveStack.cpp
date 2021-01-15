#include "MoveStack.h"

MoveStack::MoveStack()
{
	m_pHead = nullptr;
	m_iSize = 0;
}

MoveStack::~MoveStack()
{
	empty();
}

bool MoveStack::isEmpty()
{
	return (m_pHead == nullptr);
}

void MoveStack::addMove(Move* move)
{
	move->m_pNext = m_pHead;
	m_pHead = move;

	m_iSize++;
}

Move* MoveStack::removeMove()
{
	Move* removedMove = m_pHead;

	if (m_pHead != nullptr)
	{
		m_pHead = m_pHead->m_pNext;
		m_iSize--;
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

void MoveStack::empty()
{
	Move* removedMove = removeMove();

	while (removedMove != nullptr)
	{
		delete removedMove;
		removedMove = removeMove();
	}
}