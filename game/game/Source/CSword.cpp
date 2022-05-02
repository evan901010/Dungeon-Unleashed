#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CSword.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CSword::CSword()
	{
		Initialize();
	}

	int CSword::GetX1()
	{
		return x - attack1;
	}

	int CSword::GetY1()
	{
		return y;
	}

	int CSword::GetX2()
	{
		return x + attack2;
	}

	int CSword::GetY2()
	{
		return y + 100;
	}

	void CSword::Initialize()
	{
		const int X_POS = 0;
		const int Y_POS = 0;
		x = X_POS;
		y = Y_POS;
		isClick = false;
		isstop = 1;
		n = 70;
		attack1 = 0;
		attack2 = 0;
	}

	void CSword::LoadBitmap()
	{
		char *filename6[7] = { ".\\bitmaps\\sword\\swordl_ani1.bmp", ".\\bitmaps\\sword\\swordl_ani2.bmp", ".\\bitmaps\\sword\\swordl_ani3.bmp",
							  ".\\bitmaps\\sword\\swordl_ani4.bmp", ".\\bitmaps\\sword\\swordl_ani5.bmp", ".\\bitmaps\\sword\\swordl_ani6.bmp", ".\\bitmaps\\sword\\swordl_ani7.bmp" };
		char *filename7[7] = { ".\\bitmaps\\sword\\swordr_ani1.bmp", ".\\bitmaps\\sword\\swordr_ani2.bmp", ".\\bitmaps\\sword\\swordr_ani3.bmp",
							  ".\\bitmaps\\sword\\swordr_ani4.bmp", ".\\bitmaps\\sword\\swordr_ani5.bmp", ".\\bitmaps\\sword\\swordr_ani6.bmp", ".\\bitmaps\\sword\\swordr_ani7.bmp" };
		for (int i = 0; i < 7; i++) {
			attackl.AddBitmap(filename6[i], RGB(0, 0, 0));
		}
		for (int i = 0; i < 7; i++) {
			attackr.AddBitmap(filename7[i], RGB(0, 0, 0));
		}
	}

	void CSword::OnMove()
	{
		const int STEP_SIZE = 2;
		if (isClick) {
			n--;
			attackl.OnMove();
			attackr.OnMove();
			if (n == 0) {
				n = 70;
				isClick = false;
				x = 0;
				y = 0;
			}
		}

	}

	void CSword::Setisstop(int nisstop)
	{
		isstop = nisstop;
	}

	void CSword::SetClick(bool flag)
	{
		isClick = 1;
	}
	void CSword::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	
	void CSword::OnShow()
	{
		
		if (isClick) {
			if (isstop == 1) {
				attackr.SetTopLeft(x + 40, y - 10);
				attackr.OnShow();
				attack1 = 0;
				attack2 = 100;
			}
			else if (isstop == 2) {
				attackl.SetTopLeft(x - 65, y - 10);
				attackl.OnShow();
				attack1 = 100;
				attack2 = 0;
			}
		}
		else {
			x = 0;
			y = 0;
		}

	}
}