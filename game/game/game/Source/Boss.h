#pragma once

#include "CSword.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class Boss
	{
	public:
		Boss();
		bool HitEraser(CEraser *eraser);						// 是否碰到擦子
		bool HitCSword(CSword *sword);
		bool HitOthers(Boss *ball);
		bool IsAlive();
		bool IsAttack();
		CAnimation run;
		CAnimation attack;
		void LoadBitmap();										// 載入圖形
		void OnMove();											// 移動
		void OnShow();											// 將圖形貼到畫面
		void SetXY(int nx, int ny);								// 設定圓心的座標
		void SetIsAlive(bool alive);							// 設定是否活著
		void SetDelay(int d);									// 設定旋轉的速度
		void getxy(int x2, int y2);
		void forward();
		void back();
		void istach();
		int GetX1();
		int GetX2();
		int GetY1();
		int GetY2();
		bool ittouch;
	protected:
		CMovingBitmap bmp;			// 球的圖
		CMovingBitmap bmp_center;	// 圓心的圖			
		int x, y;					// 圓心的座標
		int x1, y1;
		int dx, dy;					// 球距離圓心的位移量
		int inx, iny;
		int index;					// 球的「角度」，0-17表示0-360度
		int delay_counter;			// 調整旋轉速度的計數器
		int delay;					// 旋轉的速度
		bool is_alive;				// 是否活著
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};
}