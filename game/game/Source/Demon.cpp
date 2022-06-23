#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "Demon.h"

namespace game_framework {
	Demon::Demon()
	{
		is_alive = true;
		x = y = dx = dy = index = delay_counter = 0;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown  = false;
		ittouch = 0;
	}
	int Demon::GetX1()
	{
		return x + dx;
	}
	int Demon::GetY1()
	{
		return y + dy;
	}
	int Demon::GetX2()
	{	
		return x + runr.Width();
	}
	int Demon::GetY2()
	{
		return y + runr.Height();
	}
	bool Demon::HitEraser(CEraser *eraser)
	{
		// 檢測擦子所構成的矩形是否碰到球
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}
	bool Demon::HitCSword(CSword *sword)
	{
		return HitRectangle(sword->GetX1(), sword->GetY1(), sword->GetX2(), sword->GetY2());
	}
	bool Demon::HitOthers(Demon *ball)
	{
		return HitRectangle(ball->GetX1(), ball->GetY1(), ball->GetX2(), ball->GetY2());
	}
	bool Demon::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		if (!is_alive) {
			x = 0;
			y = 0;
		}
		int x1 = x + dx;				
		int y1 = y + dy;				
		int x2 = x1 + runr.Width();	
		int y2 = y1 + runr.Height();	
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	bool Demon::IsAlive()
	{
		return is_alive;
	}
	void Demon::getxy(int x2,int y2)
	{
		inx = x - x2;
		iny = y - y2;
	}
	void Demon::LoadBitmap()
	{
		char *filename1[4] = { ".\\bitmaps\\enemy\\demon1.bmp",".\\bitmaps\\enemy\\demon2.bmp",".\\bitmaps\\enemy\\demon3.bmp", ".\\bitmaps\\enemy\\demon4.bmp" };
		char *filename2[4] = { ".\\bitmaps\\enemy\\orc_run01.bmp",".\\bitmaps\\enemy\\orc_run02.bmp",".\\bitmaps\\enemy\\orc_run03.bmp", ".\\bitmaps\\enemy\\orc_run04.bmp" };
		for (int i = 0; i < 4; i++) {	
			runr.AddBitmap(filename1[i], RGB(0, 0, 0));
			runr.SetTopLeft(x1, y1);
			runl.AddBitmap(filename1[i], RGB(0, 0, 0));
			runl.SetTopLeft(x1, y1);
		}
		bmp.LoadBitmap(IDB_BALL, RGB(0, 0, 0));			
	}
	void Demon::forward() 
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
	void Demon::back() 
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
	void Demon::OnMove()
	{		
		runr.OnMove();
		runl.OnMove();
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
	void Demon::istach()
	{
		ittouch = 1;
	}
	void Demon::SetDelay(int d)
	{
		delay = d;
	}
	void Demon::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}
	void Demon::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}
	void Demon::OnShow()
	{
		if (is_alive  /*主角x座標相減和小怪的x座標，若為正，則小怪往右*/) {
			runr.SetTopLeft(x, y);
			runr.OnShow();
		}
		if (is_alive  /*主角x座標相減和小怪的x座標，若為正，則小怪往右*/) {
			runl.SetTopLeft(x, y);
			runl.OnShow();
		}
	}
}