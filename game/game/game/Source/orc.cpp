#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "orc.h"
#include "CEraser.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBouncingBall: BouncingBall class
	/////////////////////////////////////////////////////////////////////////////

	orc::orc()
	{
		x = 120; y = 120;				// y座標比地板高1點(站在地板上)
		n = 0;
	}

	void orc::LoadBitmap()
	{
		char *filename1[4] = { ".\\bitmaps\\enemy\\orc_run1.bmp",".\\bitmaps\\enemy\\orc_run2.bmp",".\\bitmaps\\enemy\\orc_run3.bmp", ".\\bitmaps\\enemy\\orc_run4.bmp" };
		char *filename2[4] = { ".\\bitmaps\\enemy\\orc_run01.bmp",".\\bitmaps\\enemy\\orc_run02.bmp",".\\bitmaps\\enemy\\orc_run03.bmp", ".\\bitmaps\\enemy\\orc_run04.bmp" };
								
		for (int i = 0; i < 4; i++) {	// 載入動畫(由4張圖形構成)
				runr.AddBitmap(filename1[i], RGB(0, 0, 0));
				runr.SetTopLeft(x, y);
				runl.AddBitmap(filename2[i], RGB(0, 0, 0));
				runl.SetTopLeft(x, y);
			}
			

	}


	void orc::OnMove()
	{
		runr.OnMove();
		runl.OnMove();
		
	}

	void orc::OnShow()
	{
		runr.OnShow();
		runl.OnShow();
	}
}