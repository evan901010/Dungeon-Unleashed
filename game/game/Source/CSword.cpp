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
		isClick = 0;
		isstop = 1;
		n = 7;
		attack1 = 0;
		attack2 = 0;
		time = 70;
		attackl.SetDelayCount(1);
		attackr.SetDelayCount(1);
	}

	void CSword::LoadBitmap()
	{
		char *filename6[7] = { ".\\bitmaps\\sword\\swordl_ani1.bmp", ".\\bitmaps\\sword\\swordl_ani2.bmp", ".\\bitmaps\\sword\\swordl_ani3.bmp",
							  ".\\bitmaps\\sword\\swordl_ani4.bmp", ".\\bitmaps\\sword\\swordl_ani5.bmp", ".\\bitmaps\\sword\\swordl_ani6.bmp", ".\\bitmaps\\sword\\swordl_ani7.bmp" };
		char *filename7[7] = { ".\\bitmaps\\sword\\swordr_ani1.bmp", ".\\bitmaps\\sword\\swordr_ani2.bmp", ".\\bitmaps\\sword\\swordr_ani3.bmp",
							  ".\\bitmaps\\sword\\swordr_ani4.bmp", ".\\bitmaps\\sword\\swordr_ani5.bmp", ".\\bitmaps\\sword\\swordr_ani6.bmp", ".\\bitmaps\\sword\\swordr_ani7.bmp" };
		char *filename5[2] = { ".\\bitmaps\\sword\\swordl.bmp",".\\bitmaps\\sword\\swordr.bmp" };
		for (int i = 0; i < 7; i++) {
			attackl.AddBitmap(filename6[i], RGB(0, 0, 0));
		}
		for (int i = 0; i < 7; i++) {
			attackr.AddBitmap(filename7[i], RGB(0, 0, 0));
		}
		attackstopr.AddBitmap(filename5[1], RGB(0, 0, 0));
		attackstopl.AddBitmap(filename5[0], RGB(0, 0, 0));
	}

	void CSword::OnMove()
	{
		attackstopr.SetTopLeft(x + 40, y - 10);
		attackstopl.SetTopLeft(x - 20, y - 10);
		const int STEP_SIZE = 2;
		if (isClick == 1) {
			if (isstop == 1) {
				attackr.SetTopLeft(x + 40, y - 10);
				attack1 = 0;
				attack2 = 100;
			}
			else if (isstop == 2) {
				attackl.SetTopLeft(x - 65, y - 10);
				attack1 = 100;
				attack2 = 0;
			}
		}
		else {
			x = 0;
			y = 0;
			attackl.SetTopLeft(x, y);
			attackr.SetTopLeft(x, y);
		}

		if (isClick == 1) {
			attackl.OnMove();
			attackr.OnMove();
			n--;
			if (n == 0) {
				n = 7;
				x = 0;
				y = 0;
				isClick = 2;
				
			}
		}
		else if (isClick == 2) {
			wait();
		}
		
	}
	void CSword::wait()
	{
		if (time == 0) {
			isClick = 0;
			time = 75;
		}
		time--;
		
	}
	void CSword::Setisstop(int nisstop)
	{
		isstop = nisstop;
	}

	void CSword::SetClick(bool flag)
	{
		if (isClick == 0) {
			isClick = 1;
		}
		
	}
	void CSword::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	
	void CSword::OnShow()
	{

		if (isClick == 1) {
			if (isstop == 1) {
				attackr.OnShow();
			}
			else if (isstop == 2) {
				attackl.OnShow();
			}
		}
		if (isClick == 0) {
			if (isstop == 1) {
				attackstopr.OnShow();
			}
			else if (isstop == 2) {
				attackstopl.OnShow();
			}
		}
	}
}