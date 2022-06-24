#pragma once
#include "CSword.h"
namespace game_framework {
	class Trap
	{
	public:
		Trap();
		bool HitEraser(CEraser *eraser);						
		bool HitCSword(CSword *sword);
		bool HitOthers(Trap *ball);
		bool IsAlive();
		CAnimation run;
		void LoadBitmap();										// 載入圖形
		void OnMove();											// 移動
		void OnShow();											// 將圖形貼到畫面
		void SetXY(int nx, int ny);								
		void SetIsAlive(bool alive);							// 設定是否活著
		void SetDelay(int d);									
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
		CMovingBitmap bmp;			
		CMovingBitmap bmp_center;	
		int x, y;					
		int x1, y1;
		int dx, dy;					
		int inx, iny;
		int index;					
		int delay_counter;			// 調整旋轉速度的計數器
		int delay;					// 旋轉的速度
		bool is_alive;				// 是否活著
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};
}
