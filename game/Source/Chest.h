#pragma once
#include "CSword.h"
namespace game_framework {
	class Chest
	{
	public:
		Chest();
		bool HitEraser(CEraser *eraser);						// 是否碰到擦子
		bool HitCSword(CSword *sword);
		bool HitOthers(Chest *ball);
		bool IsAlive();
		CAnimation run;
		void LoadBitmap();										// 載入圖形
		void OnMove();											// 移動
		void OnShow();											
		void SetXY(int nx, int ny);							
		void SetIsAlive(bool alive);						
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
		int delay_counter;		
		int delay;				
		bool is_alive;				// 是否活著
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};
}
