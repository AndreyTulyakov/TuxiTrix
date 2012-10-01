#pragma once

#ifndef byte
typedef unsigned char byte;
#endif

#define PIECE_TYPES 7
#define PIECE_MAX_SIZE 3


class Piece
{
public:
	

	Piece(void);
	~Piece(void);

	inline int GetX() {return posX;}
	inline int GetY() {return posY;}

	inline void SetX( int x ) {posX=x;}
	inline void SetY( int y ) {posY=y;}
	
	int GetData(int pX, int pY);

	int GetXInitialPosition(int pPiece, int pRotation);
	int GetYInitialPosition(int pPiece, int pRotation);
	void Rotate(int x);

	void SetFigure(int i);

private:
	byte Data[PIECE_MAX_SIZE][PIECE_MAX_SIZE];
	int posX,posY;
};

