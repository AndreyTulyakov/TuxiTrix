#include "TuxisEngine/TuxisEngine.h"
#include "InputModule/Input.h"
using namespace Tuxis;



#include "Game.h"


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	const int WIDTH		=  50+170+50;
	const int HEIGHT	=  50+340+20;

	Log mLog;
	//mLog.EnableConsoleLogging(false);

	Window mWindow;
	Camera mCamera2D,mCamera3D;

	Engine mEngine;
	

	mWindow.Create(WIDTH,HEIGHT,L"TuxiTrix", false  );
	mCamera2D.SetOrthoProjection(0,(float)WIDTH,0,(float)HEIGHT,0.0f,1.0f);
	mCamera3D.SetPerspectiveProjection(60,WIDTH/HEIGHT,0.1f,1000.0f);

	Input mInput(mWindow.GetHWND());

	EngineDescription mEngineDesc;
	mEngineDesc._Window		= &mWindow;
	mEngineDesc._Camera2D	= &mCamera2D;
	mEngineDesc._Camera3D	= &mCamera3D;
	mEngineDesc._VSync		= true;
	mEngineDesc._Windowed	= true;

	mEngine.Initialize(mEngineDesc);


	Game mMainScene;


	mMainScene.pInput = &mInput;

	mEngine.SetRootScene(&mMainScene);


	mMainScene.LoadResource();

	Graphics::Instance()->SetClearColor( Color(0.8f, 0.8f, 0.9f, 1.0f) );


	try
	{
		while(!mInput.KeyDown(Key::ESCAPE) && mWindow.IsRunning())
		{

			Graphics::Instance()->Clear();

			// Update Section ==============================================================
			mEngine.Update();



			// Render Section ==============================================================
			mEngine.Draw();
			Graphics::Instance()->Flip();
			mInput.Update();

			Sleep(10);
		}
	}
	catch(const char* e)
	{
		mLog << e << "\n";
	}

	

	// RELEASE SECTION ==============================================================
	mMainScene.Release();
	mEngine.Release();
	mWindow.Release();

	return 0;
}