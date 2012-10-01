/**
===============================================================================
Tuxis Project
Copyright (C) 2011-2012, Andrew Tulay
===============================================================================
Input Module based on DirectInput
===============================================================================
*/

#pragma once


#include "_DllExport.h"
#include "InputKeycodes.h"
#include <windows.h>

namespace Tuxis
{
	typedef unsigned char BYTE;


	class DLL_EXPORT Input
	{
	public:
		Input(HWND pHWND);
		~Input();

		void Update();

		bool KeyDown(BYTE key);		
		bool KeyHit(BYTE key);	
		bool KeyUp(BYTE key);	

		bool MouseDown(BYTE mouse_key); 
		bool MouseHit(BYTE mouse_key);	
		bool MouseUp(BYTE mouse_key);

		void SetMousePosition(int x, int y);
		void GetMousePosition(int& x, int& y);

		int MouseSpeedX();
		int MouseSpeedY();
		int MouseSpeedZ();

	};

}