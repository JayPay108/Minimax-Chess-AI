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

void MoveStack::sort()
{
	bool sorted = false;
	while (!sorted)
	{
		Move* previousMove = nullptr;
		Move* currentMove = m_pHead;
		Move* nextMove;

		sorted = true;
		while (currentMove != nullptr)
		{
			nextMove = currentMove->m_pNext;
			if (nextMove != nullptr && (nextMove->value > currentMove->value))
			{
				currentMove->m_pNext = nextMove->m_pNext;
				nextMove->m_pNext = currentMove;
				if (previousMove == nullptr)
				{
					m_pHead = nextMove;
				}
				else
				{
					previousMove->m_pNext = nextMove;
				}

				sorted = false;
			}

			previousMove = currentMove;
			currentMove = nextMove;
		}
	}
}


// DEBUG FUNCTION
#include <iostream>
void MoveStack::print()
{
	std::cout << "Size: " << m_iSize << std::endl; 

	Move* location = m_pHead;

	while (location != nullptr)
	{
		std::cout << location << std::endl;
		std::cout << "(" << location->m_iStartIndex.m_iRow << ", " << location->m_iStartIndex.m_iCol << ")" << std::endl;
		std::cout << "(" << location->m_iEndIndex.m_iRow << ", " << location->m_iEndIndex.m_iCol << ")"  << std::endl;
		location = location->m_pNext;
	}
}