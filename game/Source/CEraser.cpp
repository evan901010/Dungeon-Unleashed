#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CEraser::CEraser()
	{
		Initialize();
	}

	int CEraser::GetX1()
	{
		return x;
	}

	int CEraser::GetY1()
	{
		return y;
	}

	int CEraser::GetX2()
	{
		return x + run.Width();
	}

	int CEraser::GetY2()
	{
		return y + run.Height();
	}

	void CEraser::Initialize()
	{
		const int X_POS = 280;
		const int Y_POS = 400;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isrun = 0;
		top = 60;
		lift = 75;
	}

	void CEraser::LoadBitmap()
	{
		char *filename[4] = { ".\\bitmaps\\knight_run1.bmp",".\\bitmaps\\knight_run2.bmp",".\\bitmaps\\knight_run3.bmp",".\\bitmaps\\knight_run4.bmp" };
		char *filename2[4] = { ".\\bitmaps\\knight_stand1.bmp",".\\bitmaps\\knight_stand2.bmp",".\\bitmaps\\knight_stand3.bmp",".\\bitmaps\\knight_stand4.bmp" };
		for (int i = 0; i < 4; i++) {
			run.AddBitmap(filename[i], RGB(0, 0, 0));
<<<<<<< HEAD
			
=======
>>>>>>> fee80173471cbaa3521d89b01a2e17bbf441f1b4
		}
<<<<<<< HEAD

		stop.AddBitmap(filename[1], RGB(0, 0, 0));
=======
		for (int i = 0; i < 4; i++) {
			stop.AddBitmap(filename2[i], RGB(0, 0, 0));
		}
>>>>>>> 7443350c29c81b304ae5a96b8de569512b9dd975
	}

	void CEraser::OnMove()
	{
		const int STEP_SIZE = 2;
		isrun = 0;
		run.OnMove();
		stop.OnMove();
		if (isMovingLeft){
			if (x > lift) {
				x -= STEP_SIZE;
			}
			isrun =  1;
		}
			
		if (isMovingRight) {
			x += STEP_SIZE;
			isrun = 1;
		}
			
		if (isMovingUp) {
			if (y > top) {
				y -= STEP_SIZE;
			}
			isrun = 1;
		}
			
		if (isMovingDown) {
			y += STEP_SIZE;
			isrun = 1;
		}
		
	}

	void CEraser::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CEraser::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CEraser::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CEraser::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void CEraser::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CEraser::OnShow()
	{
		run.SetTopLeft(x, y);
		stop.SetTopLeft(x, y);
		if (isrun) {
			run.OnShow();
		}
		else {
			stop.OnShow();
		}
		
	}
}