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
		x = 60; y = 10;				// y座標比地板高1點(站在地板上)
		velocity = initial_velocity;
	}

	void CBouncingBall::LoadBitmap()
	{
		char *filename[3] = { ".\\bitmaps\\place1.bmp",".\\bitmaps\\place2.bmp",".\\bitmaps\\place3.bmp" };
		for (int i = 0; i < 3; i++)	// 載入動畫(由4張圖形構成)
			animation.AddBitmap(filename[i], RGB(0, 0, 0));
	}

	void CBouncingBall::OnMove()
	{
		animation.OnMove();		// 執行一次animation.OnMove()，animation才會換圖
	}

	void CBouncingBall::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}