#include "Game.h"
#include <time.h>

Game::Game()
{
	pBoard = nullptr;
	CurrentPiece.SetFigure(GetRandom(0,PIECE_TYPES-1));

	Time = timeGetTime();
	LastTime = Time;

	GameOver = false;

	Level = 1;
	Scores = 0;

	srand ( (unsigned int)time(NULL) );


}

void Game::LoadResource()
{

	float WIDTH = (float)Graphics::Instance()->GetWidth();
	float HEIGHT = (float)Graphics::Instance()->GetHeight();

	pBoard = new Board(BOARD_SIZE_X,BOARD_SIZE_Y);


	// Graphics configure

	mFont.Load(L"Data/Fonts/HardPixel.fnt");
	QuadTex.LoadFromFile(L"Data/Quad.png");

	
	mTextLevel.SetFont(&mFont);
	mTextLevel.SetPosition(WIDTH-10,10);
	mTextLevel.SetHorizontalAlign(HRIGHT);
	AttachChild(&mTextLevel);

	mTextScores.SetFont(&mFont);
	mTextScores.SetPosition(10,10);
	mTextScores.SetText(L"ololo");
	AttachChild(&mTextScores);

	
	mTextMessage.SetFont(&mFont);
	mTextMessage.SetPosition(WIDTH/2,HEIGHT/2);
	mTextMessage.SetHorizontalAlign(HCENTER);
	mTextMessage.SetVisible(false);
	AttachChild(&mTextMessage);

	Quad.SetTextureAtlas(&QuadTex);
}


void Game::Release()
{
	if(pBoard != nullptr) 
		delete pBoard;

	mTextScores.Release();
	mFont.Release();

}

int Game::GetRandom(int a, int b)
{
	return (rand() % (b - a + 1)) + a;
}

void Game::Update()
{
	mTextScores	.SetText( (wstring(L"Scores:") + IntToWString(Scores)).c_str() );
	mTextLevel	.SetText( (wstring(L"Level:" ) + IntToWString(Level)) .c_str() );

	if(!GameOver)
	{
		if(pInput->KeyHit(Key::W))
		{
			CurrentPiece.Rotate(1);
			if(IsCollide())
				CurrentPiece.Rotate(-1);
		}


		if(pInput->KeyHit(Key::A))	MovePiece(true); // Move Left
		if(pInput->KeyHit(Key::D))	MovePiece(false); // Move Right

		if(pInput->KeyHit(Key::S))	
			DropPieceDown();
	}
	else
	{
		if(pInput->KeyHit(Key::SPACE))	
		{
			delete pBoard;
			pBoard = new Board(BOARD_SIZE_X,BOARD_SIZE_Y);
			GameOver = false;

			mTextMessage.SetVisible(false);
			Quad.SetVisible(true);
			mTextLevel.SetVisible(true);
			mTextScores.SetVisible(true);
		}
	}

	


	Time = timeGetTime();
	if(Level && (Time - LastTime > (500)/(Level*0.5f)) )
	{
		if(!GameOver)
		{
			DoNextStep();
			LastTime = Time;
		}
	}

	Scene::Update();
}

void Game::DoNextStep()
{
	int y = CurrentPiece.GetY();
	CurrentPiece.SetY( y + 1);


	if( IsCollide() )
	{
		CurrentPiece.SetY(y);

		// Write data to board

		for(int x=0; x < PIECE_MAX_SIZE; x++) {
			for(int y=0; y < PIECE_MAX_SIZE; y++) {
				if( CurrentPiece.GetData(x,y) )
					pBoard->SetCell(
					x+CurrentPiece.GetX(),
					y+CurrentPiece.GetY(),
					CurrentPiece.GetData(x,y));
			}
		}

		// If we lose
		if(pBoard->IsRedZoneAlarm(PIECE_MAX_SIZE))
		{
			wstring message = L"Your scores: ";
			message.append(IntToWString(Scores));

			MessageBox(0,message.c_str(),L"Game over!",0);

			GameOver = true;
			Scores = 0;
			Level = 1;

			Quad.SetVisible(false);
			mTextLevel.SetVisible(false);
			mTextScores.SetVisible(false);

			mTextMessage.SetVisible(true);
			mTextMessage.SetText(L"Press SPACE\nto play again...");

			return;
		}

		// If filled line
		for(int y=0; y < pBoard->GetSize().y; y++) 
		{

			if(pBoard->CheckFullLine(y)) 
			{

				pBoard->ClearLine(y);
				Scores += 100;

				// Change level
				if(Scores%500==0) Level++;
			}
		}

		// Generate new piece
		CurrentPiece.SetX( GetRandom(1, pBoard->GetSize().x-1-PIECE_MAX_SIZE));
		CurrentPiece.SetY( 0 );
		CurrentPiece.SetFigure(GetRandom(0,PIECE_TYPES-1));
		CurrentPiece.Rotate(GetRandom(-1,1));
	}
}

void Game::DropPieceDown()
{
	int y = CurrentPiece.GetY();
	while(IsCollide()==0)
	{
		y++;
		CurrentPiece.SetY(y);


	}
	if(IsCollide()==0) LastTime = Time-333;

	if(y-1>=0)
		CurrentPiece.SetY(y-1);
}

void Game::MovePiece(bool left)
{
	int x = CurrentPiece.GetX();
	int y = CurrentPiece.GetY();

	if(left)
	{
		CurrentPiece.SetX( x-1 );
		if(IsCollide()!=0)
			CurrentPiece.SetX( x );
	}
	else
	{
		CurrentPiece.SetX( x+1 );
		if(IsCollide()!=0)
			CurrentPiece.SetX( x );
	}

}

int Game::IsCollide()
{
	for(int x=0; x < PIECE_MAX_SIZE; x++) {
		for(int y=0; y < PIECE_MAX_SIZE; y++) {
			if( CurrentPiece.GetData(x,y) )
			{
				// Collision with walls
				if( (x + CurrentPiece.GetX()) > (pBoard->GetSize().x-1) )
					return 1;

				if( (x + CurrentPiece.GetX()) < 0 )
					return 1;

				// Collision with bottom
				if( (y + CurrentPiece.GetY()) > (pBoard->GetSize().y-1) )
					return 1;


				// Collision with cells
				if( pBoard->GetCell(x + CurrentPiece.GetX(),y + CurrentPiece.GetY()) )
					return 2;
			}
		}
	}
	return 0;
}

void Game::Draw()
{
	// Draw Hexagonal field
	DrawBoard();
	DrawPiece();

	Scene::Draw();
}

void Game::DrawBoard()
{
	int2 FieldSize = pBoard->GetSize();
	float tunelColor=0.0f;

	// Draw quad field
	float2 sQuadPos(50,50);
	float2 QuadSize(16,16);

	for(int x=0; x<FieldSize.x; x++)
		for(int y=0; y<FieldSize.y; y++)
		{

			// Quadrant
			Quad.SetPosition(sQuadPos.x+(QuadSize.x+1)*x,sQuadPos.y+(QuadSize.y+1)*y,0);

			if( pBoard->GetCell(x,y) )
			{
				Quad.SetAlpha(1.0f);
				Quad.SetColorModulation(0.8f, 0.8f, 1.0f);
			}
			else
			{
				tunelColor =  1.0f-(abs(x+0.5f-((FieldSize.x)/2.0f)))/((FieldSize.x)/2.0f);
				tunelColor/=2.0f;
				Quad.SetAlpha(0.8f);

				// if SIDES
				if(x==0 || x==FieldSize.x-1 || y==FieldSize.y-1)
					tunelColor*=0.3f;

				// if RED ZONE
				if(y<PIECE_MAX_SIZE)
					Quad.SetColorModulation(1.0f, tunelColor, tunelColor);
				else
					Quad.SetColorModulation(tunelColor, tunelColor*1.2f, tunelColor);
			}

			Quad.Update();
			Quad.Draw();
		}
}

void Game::DrawPiece()
{
	int2 FieldSize = pBoard->GetSize();

	float2 sQuadPos(50,50);
	float2 QuadSize(16,16);
	

	for(int x=0; x<PIECE_MAX_SIZE; x++)
		for(int y=0; y<PIECE_MAX_SIZE; y++)
		{
			if(CurrentPiece.GetData(x,y))
			{
				int cX=x+CurrentPiece.GetX();
				int cY=y+CurrentPiece.GetY();

				// Quadrant
				Quad.SetPosition(
					sQuadPos.x+(QuadSize.x+1)*(x+CurrentPiece.GetX()),
					sQuadPos.y+(QuadSize.y+1)*(y+CurrentPiece.GetY()),
					0);

				Quad.SetAlpha(1.0f);
				Quad.SetColorModulation(1.0f, 1.0f, 1.0f);
				Quad.Update();
				Quad.Draw();
			}
		}

}