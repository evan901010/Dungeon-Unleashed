#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "Boss.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Boss: Ball class
	/////////////////////////////////////////////////////////////////////////////

	Boss::Boss()
	{
		is_alive = true;
		x = y = dx = dy = index = delay_counter = 0;
		ittouch = 0;
	}
	int Boss::GetX1()
	{
		return x + dx;
	}
	int Boss::GetY1()
	{
		return y + dy;
	}
	int Boss::GetX2()
	{
		return x + run.Width();
	}
	int Boss::GetY2()
	{
		return y + run.Height();
	}
	bool Boss::HitEraser(CEraser *eraser)
	{
		// 檢測擦子所構成的矩形是否碰到球
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}
	bool Boss::HitCSword(CSword *sword)
	{
		return HitRectangle(sword->GetX1(), sword->GetY1(), sword->GetX2(), sword->GetY2());
	}
	bool Boss::HitOthers(Boss *ball)
	{
		return HitRectangle(ball->GetX1(), ball->GetY1(), ball->GetX2(), ball->GetY2());
	}
	bool Boss::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		if (!is_alive) {
			x = 0;
			y = 0;
		}
		int x1 = x + dx;				// 球的左上角x座標
		int y1 = y + dy;				// 球的左上角y座標
		int x2 = x1 + run.Width();	// 球的右下角x座標
		int y2 = y1 + run.Height();	// 球的右下角y座標

		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool Boss::IsAlive()
	{
		return is_alive;
	}

	void Boss::getxy(int x2, int y2)
	{
		inx = x - x2;
		iny = y - y2;
	}
	void Boss::LoadBitmap()
	{
		char *filename1[4] = { ".\\bitmaps\\enemy\\boss_run1.bmp",".\\bitmaps\\enemy\\boss_run2.bmp",".\\bitmaps\\enemy\\boss_run3.bmp", ".\\bitmaps\\enemy\\boss_run4.bmp" };
		char *filename2[4] = { ".\\bitmaps\\enemy\\boss_attack1.bmp",".\\bitmaps\\enemy\\boss_attack2.bmp",".\\bitmaps\\enemy\\boss_attack3.bmp", ".\\bitmaps\\enemy\\boss_attack4.bmp" };
		for (int i = 0; i < 4; i++) {	// 載入動畫(由4張圖形構成)
			run.AddBitmap(filename1[i], RGB(0, 0, 0));
			run.SetTopLeft(x1, y1);
			attack.AddBitmap(filename2[i], RGB(0, 0, 0));
			attack.SetTopLeft(x1, y1);
		}
		bmp.LoadBitmap(IDB_BALL, RGB(0, 0, 0));			// 載入球的圖形
		//bmp_center.LoadBitmap(IDB_CENTER, RGB(0, 0, 0));	// 載入球圓心的圖形
	}
	void Boss::forward()
	{
		if (inx < 0) {
			x = x + 1;
		}
		else {
			x = x - 1;
		}
		if (iny < 0) {
			y = y + 1;
		}
		else {
			y = y - 1;
		}
	}
	void Boss::back()
	{
		if (inx < 0) {
			x = x - 5;
		}
		else {
			x = x + 5;
		}
		if (iny < 0) {
			y = y - 5;
		}
		else {
			y = y + 5;
		}
		ittouch = 0;
	}
	void Boss::OnMove()
	{
		run.OnMove();
		attack.OnMove();
		if (!is_alive) {
			return;
		}
		if (ittouch) {
			back();
		}
		else {
			forward();
		}


	}
	void Boss::istach()
	{
		ittouch = 1;
	}
	void Boss::SetDelay(int d)
	{
		delay = d;
	}

	void Boss::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void Boss::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Boss::OnShow()
	{
		if (is_alive) {
			run.SetTopLeft(x, y);
			run.OnShow();
		}

	}
}