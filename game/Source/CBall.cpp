#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "CBall.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	CBall::CBall()
	{
		is_alive = true;
		x = y = dx = dy = index = delay_counter = 0;
		ittouch = 0;
	}
	int CBall::GetX1()
	{
		return x + dx;
	}
	int CBall::GetY1()
	{
		return y + dy;
	}
	int CBall::GetX2()
	{
		return x + run.Width();
	}
	int CBall::GetY2()
	{
		return y + run.Height();
	}
	bool CBall::HitEraser(CEraser *eraser)
	{
		// 檢測擦子所構成的矩形是否碰到球
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}
	bool CBall::HitCSword(CSword *sword)
	{
		return HitRectangle(sword->GetX1(), sword->GetY1(), sword->GetX2(), sword->GetY2());
	}
	bool CBall::HitOthers(CBall *ball)
	{
		return HitRectangle(ball->GetX1(), ball->GetY1(), ball->GetX2(), ball->GetY2());
	}
	bool CBall::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		if (!is_alive) {
			x = 0;
			y = 0;
		}
		int x1 = x + dx;				// 球的左上角x座標
		int y1 = y + dy;				// 球的左上角y座標
		int x2 = x1 + run.Width();	// 球的右下角x座標
		int y2 = y1 + run.Height();	// 球的右下角y座標
									//
									// 檢測球的矩形與參數矩形是否有交集
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool CBall::IsAlive()
	{
		return is_alive;
	}
	void CBall::getxy(int x2,int y2)
	{
		inx = x - x2;
		iny = y - y2;
	}
	void CBall::LoadBitmap()
	{
		char *filename1[4] = { ".\\bitmaps\\enemy\\orc_run1.bmp",".\\bitmaps\\enemy\\orc_run2.bmp",".\\bitmaps\\enemy\\orc_run3.bmp", ".\\bitmaps\\enemy\\orc_run4.bmp" };

		for (int i = 0; i < 4; i++) {	// 載入動畫(由4張圖形構成)
			run.AddBitmap(filename1[i], RGB(0, 0, 0));
			run.SetTopLeft(x1, y1);
		}
		bmp.LoadBitmap(IDB_BALL, RGB(0, 0, 0));			// 載入球的圖形
		//bmp_center.LoadBitmap(IDB_CENTER, RGB(0, 0, 0));	// 載入球圓心的圖形
	}
	void CBall::forward() 
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
	void CBall::back() 
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
	void CBall::OnMove()
	{		
		run.OnMove();
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
	void CBall::istach()
	{
		ittouch = 1;
	}
	void CBall::SetDelay(int d)
	{
		delay = d;
	}

	void CBall::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void CBall::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CBall::OnShow()
	{
		if (is_alive) {
			run.SetTopLeft(x, y);
			run.OnShow();
		}
	}
}