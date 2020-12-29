#pragma once

class Index
{
public:
	Index();
	Index(int row, int col);
	bool operator==(Index index2);

	int m_iRow;
	int m_iCol;
};