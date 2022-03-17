#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CBouncingBall.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBouncingBall: BouncingBall class
	/////////////////////////////////////////////////////////////////////////////

	CBouncingBall::CBouncingBall()
	{
		x = 60; y = 10;				// y�y�Ф�a�O��1�I(���b�a�O�W)
		velocity = initial_velocity;
	}

	void CBouncingBall::LoadBitmap()
	{
		char *filename[3] = { ".\\bitmaps\\place1.bmp",".\\bitmaps\\place2.bmp",".\\bitmaps\\place3.bmp" };
		for (int i = 0; i < 3; i++)	// ���J�ʵe(��4�i�ϧκc��)
			animation.AddBitmap(filename[i], RGB(0, 0, 0));
	}

	void CBouncingBall::OnMove()
	{
		animation.OnMove();		// ����@��animation.OnMove()�Aanimation�~�|����
	}

	void CBouncingBall::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}