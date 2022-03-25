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
		x = 60; y = 10;				// y�y�Ф�a�O��1�I(���b�a�O�W)
		level = 0;
		n = 0;
	}

	void CGamemap::LoadBitmap()
	{
		char *filename[2][3] = { { ".\\bitmaps\\place1.bmp",".\\bitmaps\\place2.bmp",".\\bitmaps\\place3.bmp" },
								 { ".\\bitmaps\\place2_1.bmp",".\\bitmaps\\place2_2.bmp",".\\bitmaps\\place2_3.bmp"} };
		for (int i = 0; i < 2; i++) {	// ���J�ʵe(��4�i�ϧκc��)
			for (int j = 0; j < 3; j++) {
				all[i].AddBitmap(filename[i][j]);
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