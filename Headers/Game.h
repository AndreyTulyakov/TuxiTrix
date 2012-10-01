#pragma once

#include "TuxisEngine/TuxisEngine.h"
#include "InputModule/Input.h"
using namespace Tuxis;

#include "Board.h"
#include "Piece.h"

#ifndef nullptr
#define nullptr 0
#endif

#define BOARD_SIZE_X 10
#define BOARD_SIZE_Y 20



/*
CONTROLLS:

ESC - exit
W - rotate piece
S - prop piece
A,D - move piece

*/


class Game : public Scene
{
public:
	int Scores;
	int Level;

	Input* pInput;
	Game();

	void LoadResource();
	void Release();

	void Update();
	void Draw();

private:
	void DrawBoard();
	void DrawPiece();
	int GetRandom(int a, int b);


	// Game Specific
	void DropPieceDown();
	void MovePiece(bool left);
	int IsCollide();
	void DoNextStep();

	DWORD Time;
	DWORD LastTime;
	bool GameOver;


	Board *pBoard;
	Piece CurrentPiece;

	BitmapFont mFont;
	Text mTextScores;
	Text mTextLevel;
	Text mTextMessage;

	Sprite Quad;
	TextureAtlas QuadTex;
};