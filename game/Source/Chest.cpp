#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "Chest.h"
namespace game_framework {
	Chest::Chest()
	{
		is_alive = true;
		x = y = dx = dy = index = delay_counter = 0;
		ittouch = 0;
	}
	int Chest::GetX1()
	{
		return x + dx;
	}
	int Chest::GetY1()
	{
		return y + dy;
	}
	int Chest::GetX2()
	{
		return x + run.Width();
	}
	int Chest::GetY2()
	{
		return y + run.Height();
	}
	bool Chest::HitEraser(CEraser *eraser)
	{
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}
	bool Chest::HitCSword(CSword *sword)
	{
		return HitRectangle(sword->GetX1(), sword->GetY1(), sword->GetX2(), sword->GetY2());
	}
	bool Chest::HitOthers(Chest *ball)
	{
		return HitRectangle(ball->GetX1(), ball->GetY1(), ball->GetX2(), ball->GetY2());
	}
	bool Chest::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		if (!is_alive) {
			x = 0;
			y = 0;
		}
		int x1 = x + dx;				// �y�����W��x�y��
		int y1 = y + dy;				// �y�����W��y�y��
		int x2 = x1 + run.Width();	// �y���k�U��x�y��
		int y2 = y1 + run.Height();	// �y���k�U��y�y��
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	bool Chest::IsAlive()
	{
		return is_alive;
	}
	void Chest::getxy(int x2, int y2)
	{
		inx = x - x2;
		iny = y - y2;
	}
	void Chest::LoadBitmap()
	{
		char *filename1[4] = { ".\\bitmaps\\enemy\\chest1.bmp",".\\bitmaps\\enemy\\chest2.bmp",".\\bitmaps\\enemy\\chest3.bmp"};

		for (int i = 0; i < 3; i++) {	// ���J�ʵe(��4�i�ϧκc��)
			run.AddBitmap(filename1[i], RGB(0, 0, 0));
			run.SetTopLeft(x1, y1);
		}
		//bmp.LoadBitmap(IDB_BALL, RGB(0, 0, 0));			// ���J�y���ϧ�
		//bmp_center.LoadBitmap(IDB_CENTER, RGB(0, 0, 0));	// ���J�y��ߪ��ϧ�
	}
	void Chest::forward()
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
	void Chest::back()
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
	void Chest::OnMove()
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
	void Chest::istach()
	{
		ittouch = 1;
	}
	void Chest::SetDelay(int d)
	{
		delay = d;
	}
	void Chest::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}
	void Chest::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}
	void Chest::OnShow()
	{
		if (is_alive) {
			run.SetTopLeft(x, y);
			run.OnShow();
		}
	}
}