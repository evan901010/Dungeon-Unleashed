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

	CGamemap::CGamemap()
	{
		x = 60; y = 10;				// y座標比地板高1點(站在地板上)
		level = 0;
		n = 0;
	}

	void CGamemap::LoadBitmap()
	{
		char *filename[3] = { ".\\bitmaps\\place1.bmp",".\\bitmaps\\place2.bmp",".\\bitmaps\\place3.bmp" };
		for (int i = 0; i < 3; i++) {	// 載入動畫(由4張圖形構成)
			all[level][i].LoadBitmap(filename[i]);
		}

		temp = &all[level][n];
	}


	void CGamemap::OnMove()
	{
		n++;
		n %= 3;
		temp = &all[level][n];
	}

	void CGamemap::OnShow()
	{
		(*temp).ShowBitmap();
	}
}