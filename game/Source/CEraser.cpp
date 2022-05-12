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
	int CEraser::Getstop()
	{
		return(isstop);
	}
	void CEraser::Initialize()
	{
		const int X_POS = 280;
		const int Y_POS = 400;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = isClick = false;
		isrun = 0;
		top = 30;
		lift = 70;
		down = 475;
		right = 535;
		isstop = 1;
		n = 70;
	}

	void CEraser::LoadBitmap()
	{
		char *filename[4] = { ".\\bitmaps\\knight_run1.bmp",".\\bitmaps\\knight_run2.bmp",".\\bitmaps\\knight_run3.bmp",".\\bitmaps\\knight_run4.bmp" };
		char *filename2[4] = { ".\\bitmaps\\knight_run01.bmp",".\\bitmaps\\knight_run02.bmp",".\\bitmaps\\knight_run03.bmp",".\\bitmaps\\knight_run04.bmp" };
		char *filename3[4] = { ".\\bitmaps\\knight_stand1.bmp",".\\bitmaps\\knight_stand2.bmp",".\\bitmaps\\knight_stand3.bmp",".\\bitmaps\\knight_stand4.bmp" };
		char *filename4[4] = { ".\\bitmaps\\knight_stand01.bmp",".\\bitmaps\\knight_stand02.bmp",".\\bitmaps\\knight_stand03.bmp",".\\bitmaps\\knight_stand04.bmp" };
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
	}

	void CEraser::OnMove()
	{
		const int STEP_SIZE = 2;

		runr.OnMove();
		runl.OnMove();
		stopr.OnMove();
		stopl.OnMove();

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
	void CEraser::SetClick(bool flag)
	{
		isClick = true;
	}

	void CEraser::OnShow()
	{
		runr.SetTopLeft(x, y);
		runl.SetTopLeft(x, y);
		stopr.SetTopLeft(x, y);
		stopl.SetTopLeft(x, y);
		if (isrun == 1) {
			runr.OnShow();

		}
		if(isrun == 2) {
			runl.OnShow();

		}
		if(isstop == 1){
			stopr.OnShow();
		}
		if (isstop == 2) {
			stopl.OnShow();
		}
		
	}
}