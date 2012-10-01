#include "..\Headers\Piece.h"



// 7 types, 16 bytes
byte AllPieces[PIECE_TYPES][PIECE_MAX_SIZE*PIECE_MAX_SIZE] = 
{
	{ // Square
		0, 0, 0,
		0, 1, 0,
		0, 0, 0
		
	},{ // I
		0, 0, 0,
		1, 1, 1,
		0, 0, 0
		

	},{ // L
		0, 0, 0, 
		0, 1, 1,
		0, 1, 0
		

	},{ // mirror - L
		0, 0, 0,
		1, 1, 0,
		0, 1, 0

	},{ // S
		0, 1, 0,
		0, 1, 0,
		1, 1, 0

	},{ // T
		0, 0, 0,
		0, 1, 0,
		1, 1, 1

	},{ // Z
		0, 1, 0,
		0, 1, 0,
		0, 1, 1

	}

};



Piece::Piece(void)
{
	for(int x=0; x<PIECE_MAX_SIZE; x++)
		for(int y=0; y<PIECE_MAX_SIZE; y++)
		{
			Data[x][y] = 0;
		}
	posX=0; posY=0;
}


Piece::~Piece(void)
{
}


void Piece::SetFigure(int i)
{
	if( i>0 && i<PIECE_TYPES)
		for(int x=0; x<PIECE_MAX_SIZE; x++)
			for(int y=0; y<PIECE_MAX_SIZE; y++)
			{
				Data[x][y] = AllPieces[i][x*PIECE_MAX_SIZE+y];
			}
}


int Piece::GetData(int pX, int pY)
{
	if( !((pX>=0 && pX<PIECE_MAX_SIZE) && (pY>=0 && pY<PIECE_MAX_SIZE)) )
		return 0;
	return Data[pX][pY];
}


void Piece::Rotate(int i)
{
	i = i%4;

	if(i)
	{
		byte t[PIECE_MAX_SIZE][PIECE_MAX_SIZE];

		for(int x=0; x<PIECE_MAX_SIZE; x++)
			for(int y=0; y<PIECE_MAX_SIZE; y++)
			{
				t[x][y] = Data[x][y];
			}

		switch(i)
		{
		case -1: // 90 pro
		
			for(int x=0; x<PIECE_MAX_SIZE; x++)
			for(int y=0; y<PIECE_MAX_SIZE; y++)
				{
					Data[x][y] = t[(PIECE_MAX_SIZE-1)-y][x];
				}
			break;

		case 1: // 90 po
		
			for(int x=0; x<PIECE_MAX_SIZE; x++)
			for(int y=0; y<PIECE_MAX_SIZE; y++)
				{
					Data[x][y] = t[y][(PIECE_MAX_SIZE-1)-x];
				}
			break;
		}
	}
}





