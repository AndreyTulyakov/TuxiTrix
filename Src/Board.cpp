#include "..\Headers\Board.h"


Board::Board(int xCount, int yCount)
{
	if(xCount>0 && yCount>0)
	{
		Size(xCount,yCount);

		// Allocate memory
		Data = new byte*[Size.x];
		for(int i=0; i<Size.x; i++)
		{
			Data[i] = new byte[Size.y];
		}

		// Fill null 
		for(int x=0; x<Size.x; x++)
			for(int y=0; y<Size.y; y++)
				Data[x][y] = 0;
	}
	else
		throw "Board::Board: strange board size";
}


byte Board::GetCell(int x, int y)
{
	if(x>=0 && y>=0 && x<Size.x && y<Size.y)
	{
		return Data[x][y];
	}
	else
		throw "Board::GetCell: out of range";
}


void Board::SetCell(int x, int y, byte value)
{
	if(x>=0 && y>=0 && x<Size.x && y<Size.y)
	{
		Data[x][y]=value;
	}
	else
		throw "Board::SetCell: out of range";
}


int2 Board::GetSize()
{
	return Size;
}


Board::~Board(void)
{
	for(int i=0; i<Size.x; i++)
	{
		delete[] Data[i];
	}
	delete[] Data;
}


void Board::ClearLine(int num)
{
	if(num>=0 && num<Size.y)
	{
		// Clear Line
		for(int i=0; i<Size.x; i++)
			Data[i][num] = 0;

		// Offset upper to down
		for(int y=num-1; y > 0; y--) 
		{
			for(int x=0; x < Size.x; x++) 
			{
				Data[x][y+1] = Data[x][y];
			}
		}
		for(int i=0; i<Size.x; i++)
			Data[i][0] = 0;
	}
	else
		throw "Board::ClearLine: out of range";
}


bool Board::IsRedZoneAlarm(int zone)
{
	for(int x=0; x<Size.x; x++)
			for(int y=0; y<Size.y && y<zone; y++)
				if(Data[x][y]) return true;

	return false;
}

bool Board::CheckFullLine(int n)
{
	if(n>=0 && n<Size.y)
	{
		for(int x=0; x<Size.x; x++)
		{
			if(Data[x][n]==0) return false;
		}
		return true;
	}
	else
		throw "Board::CheckFullLine: out of range";
}