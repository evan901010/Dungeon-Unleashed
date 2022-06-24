#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "Trap.h"
namespace game_framework {
	Trap::Trap()
	{
		is_alive = true;
		x = y = dx = dy = index = delay_counter = 0;
		ittouch = 0;
	}
	int Trap::GetX1()
	{
		return x + dx;
	}
	int Trap::GetY1()
	{
		return y + dy;
	}
	int Trap::GetX2()
	{
		return x + run.Width();
	}
	int Trap::GetY2()
	{
		return y + run.Height();
	}
	bool Trap::HitEraser(CEraser *eraser)
	{
		// 檢測擦子所構成的矩形是否碰到球
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}
	bool Trap::HitCSword(CSword *sword)
	{
		return HitRectangle(sword->GetX1(), sword->GetY1(), sword->GetX2(), sword->GetY2());
	}
	bool Trap::HitOthers(Trap *ball)
	{
		return HitRectangle(ball->GetX1(), ball->GetY1(), ball->GetX2(), ball->GetY2());
	}
	bool Trap::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		if (!is_alive) {
			x = 0;
			y = 0;
		}
		int x1 = x + dx;				
		int y1 = y + dy;				
		int x2 = x1 + run.Width();	
		int y2 = y1 + run.Height();
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	bool Trap::IsAlive()
	{
		return is_alive;
	}
	void Trap::getxy(int x2, int y2)
	{
		inx = x - x2;
		iny = y - y2;
	}
	void Trap::LoadBitmap()
	{
		char *filename1[4] = { ".\\bitmaps\\enemy\\trap1.bmp",".\\bitmaps\\enemy\\trap2.bmp",".\\bitmaps\\enemy\\trap3.bmp", ".\\bitmaps\\enemy\\trap4.bmp" };

		for (int i = 0; i < 4; i++) {	// 載入動畫(由4張圖形構成)
			run.AddBitmap(filename1[i], RGB(0, 0, 0));
			run.SetTopLeft(x1, y1);
		}
	}
	void Trap::forward()
	{
		if (inx < 0) {
			x = x + 0;
		}
		else {
			x = x - 0;
		}
		if (iny < 0) {
			y = y + 0;
		}
		else {
			y = y - 0;
		}
	}
	void Trap::back()
	{
		if (inx < 0) {
			x = x - 0;
		}
		else {
			x = x + 0;
		}
		if (iny < 0) {
			y = y - 0;
		}
		else {
			y = y + 0;
		}
		ittouch = 0;
	}
	void Trap::OnMove()
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
	void Trap::istach()
	{
		ittouch = 1;
	}
	void Trap::SetDelay(int d)
	{
		delay = d;
	}
	void Trap::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}
	void Trap::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}
	void Trap::OnShow()
	{
		if (is_alive) {
			run.SetTopLeft(x, y);
			run.OnShow();
		}
	}
}