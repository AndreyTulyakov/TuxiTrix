#pragma once

#ifndef byte
typedef unsigned char byte;
#endif



#include "TuxisEngine\Types.h"
using namespace Tuxis;


class Board
{
private:
	byte **Data;
	int2 Size;

public:
	Board(int xCount, int yCount);

	byte GetCell(int x, int y);
	void SetCell(int x, int y, byte value);

	bool IsRedZoneAlarm(int zone);

	int2 GetSize();

	bool CheckFullLine(int n);
	void ClearLine(int num);

	~Board(void);
};

