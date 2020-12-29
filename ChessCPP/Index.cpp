#include "Index.h"

Index::Index()
{
	m_iRow = 0;
	m_iCol = 0;
}

Index::Index(int row, int col)
{
	m_iRow = row;
	m_iCol = col;
}

bool Index::operator==(Index index2)
{
	return ((m_iRow == index2.m_iRow) && (m_iCol == index2.m_iCol));
}