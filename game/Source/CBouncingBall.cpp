#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CBouncingBall.h"

namespace game_framework {
	

	CGamemap::CGamemap()
	{
		x = 60; y = 10;				
		level = 0;
		n = 0;
	}

	void CGamemap::LoadBitmap()
	{
		char *filename[2][3] = { { ".\\bitmaps\\map\\map1_1.bmp",".\\bitmaps\\map\\map1_2.bmp",".\\bitmaps\\map\\map1_3.bmp" },
								 { ".\\bitmaps\\map\\map2_1.bmp",".\\bitmaps\\map\\map2_2.bmp",".\\bitmaps\\map\\map2_3.bmp"} };
		for (int i = 0; i < 2; i++) {	
			for (int j = 0; j < 3; j++) {
				all[i].AddBitmap(filename[0][j]);
			}
			all[i].SetTopLeft(x, y);	
		}
		
	}


	void CGamemap::OnMove()
	{
		all[n].OnMove();
	}

	void CGamemap::OnShow()
	{
		all[n].OnShow();
	}
}