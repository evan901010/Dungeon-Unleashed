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
		return x + runr.Width();
	}

	int CEraser::GetY2()
	{
		return y + runr.Height();
	}

	void CEraser::Initialize()
	{
		const int X_POS = 280;
		const int Y_POS = 400;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isrun = 0;
		top = 30;
		lift = 70;
		down = 475;
		right = 535;
		isstop = 1;
	}

	void CEraser::LoadBitmap()
	{
		char *filename[4] = { ".\\bitmaps\\knight_run1.bmp",".\\bitmaps\\knight_run2.bmp",".\\bitmaps\\knight_run3.bmp",".\\bitmaps\\knight_run4.bmp" };
		char *filename2[4] = { ".\\bitmaps\\knight_run01.bmp",".\\bitmaps\\knight_run02.bmp",".\\bitmaps\\knight_run03.bmp",".\\bitmaps\\knight_run04.bmp" };
		char *filename3[4] = { ".\\bitmaps\\knight_stand1.bmp",".\\bitmaps\\knight_stand2.bmp",".\\bitmaps\\knight_stand3.bmp",".\\bitmaps\\knight_stand4.bmp" };
		char *filename4[4] = { ".\\bitmaps\\knight_stand01.bmp",".\\bitmaps\\knight_stand02.bmp",".\\bitmaps\\knight_stand03.bmp",".\\bitmaps\\knight_stand04.bmp" };
		char *filename5[1] = { ".\\bitmaps\\sword\\swordl.bmp" };
		char *filename6[7] = { ".\\bitmaps\\sword\\swordl_ani1.bmp", ".\\bitmaps\\sword\\swordl_ani2.bmp", ".\\bitmaps\\sword\\swordl_ani3.bmp",
							  ".\\bitmaps\\sword\\swordl_ani4.bmp", ".\\bitmaps\\sword\\swordl_ani5.bmp", ".\\bitmaps\\sword\\swordl_ani6.bmp", ".\\bitmaps\\sword\\swordl_ani7.bmp", };
		for (int i = 0; i < 4; i++) {
			runr.AddBitmap(filename[i], RGB(0, 0, 0));
		}
		for (int i = 0; i < 4; i++) {
			runl.AddBitmap(filename2[i], RGB(0, 0, 0));
		}
		for (int i = 0; i < 4; i++) {
			stopr.AddBitmap(filename3[i], RGB(0, 0, 0));
		}
		for (int i = 0; i < 4; i++) {
			stopl.AddBitmap(filename4[i], RGB(0, 0, 0));
		}

		sword.AddBitmap(filename5[0], RGB(0, 0, 0));

		for (int i = 0; i < 7; i++) {
			attackl.AddBitmap(filename6[i], RGB(0, 0, 0));
		}
	}

	void CEraser::OnMove()
	{
		const int STEP_SIZE = 2;

		runr.OnMove();
		runl.OnMove();
		stopr.OnMove();
		stopl.OnMove();
		attackl.OnMove();
		isrun = 0;
		if (isMovingLeft){
			if (x > lift) {
				x -= STEP_SIZE;
			}
			isrun =  2;
			isstop = 2;

		}	
		else if (isMovingRight) {
			if (x < right) {
				x += STEP_SIZE;
			}
			isrun = 1;
			isstop = 1;
		}
		else if (isMovingUp) {
			if (y > top) {
				y -= STEP_SIZE;
			}
			isrun = isstop;
		}
		else if (isMovingDown) {
			if (y < down) {
				y += STEP_SIZE;
			}
			isrun = isstop;
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
		runr.SetTopLeft(x, y);
		runl.SetTopLeft(x, y);
		stopr.SetTopLeft(x, y);
		stopl.SetTopLeft(x, y);
		attackl.SetTopLeft(x-65, y-10);
		//sword.OnShow();
		if (isrun == 1) {
			runr.OnShow();
			attackl.OnShow();
		}
		if(isrun == 2) {
			runl.OnShow();
			attackl.OnShow();
		}
		if(isstop == 1){
			stopr.OnShow();
			attackl.OnShow();
		}
		if (isstop == 2) {
			stopl.OnShow();
			attackl.OnShow();
		}
		
	}
}